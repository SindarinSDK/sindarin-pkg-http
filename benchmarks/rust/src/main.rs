use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use std::collections::HashMap;
use std::io::Read;
use std::sync::{Arc, Mutex};
use tiny_http::{Header, Method, Request, Response, Server, StatusCode};

#[derive(Clone, Serialize, Deserialize)]
struct Item {
    id: i32,
    #[serde(flatten)]
    data: Value,
}

struct AppState {
    items: HashMap<i32, Item>,
    next_id: i32,
}

fn main() {
    let state = Arc::new(Mutex::new(AppState {
        items: HashMap::new(),
        next_id: 1,
    }));

    let server = Server::http("0.0.0.0:8081").expect("Failed to start server");
    println!("Rust Server listening on port 8081");

    for request in server.incoming_requests() {
        let state = Arc::clone(&state);
        std::thread::spawn(move || {
            handle_request(request, state);
        });
    }
}

fn handle_request(mut request: Request, state: Arc<Mutex<AppState>>) {
    let path = request.url().to_string();
    let method = request.method().clone();

    let response = match (method, path.as_str()) {
        (Method::Get, "/items") => list_items(&state),
        (Method::Post, "/items") => {
            if !is_json_content_type(&request) {
                json_response(
                    400,
                    json!({"error": "Content-Type must be application/json"}),
                )
            } else {
                let body = read_body(&mut request);
                create_item(&state, &body)
            }
        }
        (Method::Get, path) if path.starts_with("/items/") => {
            let id = parse_id(path);
            get_item(&state, id)
        }
        (Method::Put, path) if path.starts_with("/items/") => {
            if !is_json_content_type(&request) {
                json_response(
                    400,
                    json!({"error": "Content-Type must be application/json"}),
                )
            } else {
                let id = parse_id(path);
                let body = read_body(&mut request);
                update_item(&state, id, &body)
            }
        }
        (Method::Delete, path) if path.starts_with("/items/") => {
            let id = parse_id(path);
            delete_item(&state, id)
        }
        _ => text_response(404, "Not found"),
    };

    let _ = request.respond(response);
}

fn is_json_content_type(request: &Request) -> bool {
    request
        .headers()
        .iter()
        .any(|h| {
            h.field.as_str().to_ascii_lowercase() == "content-type"
                && h.value.as_str().contains("application/json")
        })
}

fn read_body(request: &mut Request) -> String {
    let mut body = String::new();
    let _ = request.as_reader().read_to_string(&mut body);
    body
}

fn parse_id(path: &str) -> i32 {
    path.strip_prefix("/items/")
        .and_then(|s| s.parse().ok())
        .unwrap_or(-1)
}

fn json_response(status: u16, value: Value) -> Response<std::io::Cursor<Vec<u8>>> {
    let body = serde_json::to_string(&value).unwrap_or_default();
    let header = Header::from_bytes(&b"Content-Type"[..], &b"application/json"[..]).unwrap();
    Response::new(
        StatusCode(status),
        vec![header],
        std::io::Cursor::new(body.into_bytes()),
        None,
        None,
    )
}

fn text_response(status: u16, text: &str) -> Response<std::io::Cursor<Vec<u8>>> {
    let header = Header::from_bytes(&b"Content-Type"[..], &b"text/plain"[..]).unwrap();
    Response::new(
        StatusCode(status),
        vec![header],
        std::io::Cursor::new(text.as_bytes().to_vec()),
        None,
        None,
    )
}

fn list_items(state: &Arc<Mutex<AppState>>) -> Response<std::io::Cursor<Vec<u8>>> {
    let state = state.lock().unwrap();
    let items: Vec<&Item> = state.items.values().collect();
    json_response(200, json!(items))
}

fn create_item(state: &Arc<Mutex<AppState>>, body: &str) -> Response<std::io::Cursor<Vec<u8>>> {
    let mut state = state.lock().unwrap();

    let mut data: Value = serde_json::from_str(body).unwrap_or(json!({}));

    let id = state.next_id;
    state.next_id += 1;

    if let Value::Object(ref mut map) = data {
        map.insert("id".to_string(), json!(id));
    }

    let item = Item {
        id,
        data: data.clone(),
    };

    state.items.insert(id, item);

    json_response(201, data)
}

fn get_item(state: &Arc<Mutex<AppState>>, id: i32) -> Response<std::io::Cursor<Vec<u8>>> {
    let state = state.lock().unwrap();

    match state.items.get(&id) {
        Some(item) => {
            let mut value = item.data.clone();
            if let Value::Object(ref mut map) = value {
                map.insert("id".to_string(), json!(item.id));
            }
            json_response(200, value)
        }
        None => json_response(404, json!({"error": "Item not found"})),
    }
}

fn update_item(
    state: &Arc<Mutex<AppState>>,
    id: i32,
    body: &str,
) -> Response<std::io::Cursor<Vec<u8>>> {
    let mut state = state.lock().unwrap();

    if !state.items.contains_key(&id) {
        return json_response(404, json!({"error": "Item not found"}));
    }

    let mut data: Value = serde_json::from_str(body).unwrap_or(json!({}));

    if let Value::Object(ref mut map) = data {
        map.insert("id".to_string(), json!(id));
    }

    let item = Item {
        id,
        data: data.clone(),
    };

    state.items.insert(id, item);

    json_response(200, data)
}

fn delete_item(state: &Arc<Mutex<AppState>>, id: i32) -> Response<std::io::Cursor<Vec<u8>>> {
    let mut state = state.lock().unwrap();

    match state.items.remove(&id) {
        Some(_) => json_response(200, json!({"deleted": true})),
        None => json_response(404, json!({"error": "Item not found"})),
    }
}

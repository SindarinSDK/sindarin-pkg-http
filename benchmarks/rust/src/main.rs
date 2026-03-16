use actix_web::{web, App, HttpServer, HttpResponse, HttpRequest};
use serde::{Deserialize, Serialize};
use serde_json::{json, Value};
use std::collections::HashMap;
use std::sync::RwLock;

#[derive(Clone, Serialize, Deserialize)]
struct Item {
    id: i32,
    #[serde(flatten)]
    data: Value,
}

struct AppState {
    items: RwLock<HashMap<i32, Item>>,
    counter: RwLock<i32>,
}

async fn list_items(data: web::Data<AppState>) -> HttpResponse {
    let items = data.items.read().unwrap();
    let list: Vec<&Item> = items.values().collect();
    HttpResponse::Ok().json(list)
}

async fn create_item(
    data: web::Data<AppState>,
    req: HttpRequest,
    body: web::Bytes,
) -> HttpResponse {
    let content_type = req
        .headers()
        .get("content-type")
        .and_then(|v| v.to_str().ok())
        .unwrap_or("");
    if !content_type.contains("application/json") {
        return HttpResponse::BadRequest()
            .json(json!({"error": "Content-Type must be application/json"}));
    }

    let mut input: Value = serde_json::from_slice(&body).unwrap_or(json!({}));

    let id = {
        let mut counter = data.counter.write().unwrap();
        let id = (*counter % 1000) + 1;
        *counter += 1;
        id
    };

    if let Value::Object(ref mut map) = input {
        map.insert("id".to_string(), json!(id));
    }

    let item = Item {
        id,
        data: input.clone(),
    };

    data.items.write().unwrap().insert(id, item);

    HttpResponse::Ok().json(input)
}

async fn get_item(data: web::Data<AppState>, path: web::Path<i32>) -> HttpResponse {
    let id = path.into_inner();
    let items = data.items.read().unwrap();

    match items.get(&id) {
        Some(item) => {
            let mut value = item.data.clone();
            if let Value::Object(ref mut map) = value {
                map.insert("id".to_string(), json!(item.id));
            }
            HttpResponse::Ok().json(value)
        }
        None => HttpResponse::Ok().json(json!({"id": id, "name": "", "value": 0})),
    }
}

async fn update_item(
    data: web::Data<AppState>,
    path: web::Path<i32>,
    req: HttpRequest,
    body: web::Bytes,
) -> HttpResponse {
    let content_type = req
        .headers()
        .get("content-type")
        .and_then(|v| v.to_str().ok())
        .unwrap_or("");
    if !content_type.contains("application/json") {
        return HttpResponse::BadRequest()
            .json(json!({"error": "Content-Type must be application/json"}));
    }

    let id = path.into_inner();
    let mut input: Value = serde_json::from_slice(&body).unwrap_or(json!({}));

    if let Value::Object(ref mut map) = input {
        map.insert("id".to_string(), json!(id));
    }

    let item = Item {
        id,
        data: input.clone(),
    };

    data.items.write().unwrap().insert(id, item);

    HttpResponse::Ok().json(input)
}

async fn delete_item(data: web::Data<AppState>, path: web::Path<i32>) -> HttpResponse {
    let id = path.into_inner();
    data.items.write().unwrap().remove(&id);
    HttpResponse::Ok().json(json!({"deleted": true}))
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    let mut initial_items = HashMap::new();
    for i in 1..=1000 {
        initial_items.insert(
            i,
            Item {
                id: i,
                data: json!({"name": format!("Item {}", i), "value": i}),
            },
        );
    }

    let data = web::Data::new(AppState {
        items: RwLock::new(initial_items),
        counter: RwLock::new(0),
    });

    println!("Rust Server listening on port 8081");

    HttpServer::new(move || {
        App::new()
            .app_data(data.clone())
            .route("/items", web::get().to(list_items))
            .route("/items", web::post().to(create_item))
            .route("/items/{id}", web::get().to(get_item))
            .route("/items/{id}", web::put().to(update_item))
            .route("/items/{id}", web::delete().to(delete_item))
    })
    .bind("0.0.0.0:8081")?
    .run()
    .await
}

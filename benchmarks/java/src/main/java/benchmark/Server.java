package benchmark;

import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpExchange;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;
import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

public class Server {
    private static final Map<Integer, String> items = new ConcurrentHashMap<>();
    private static final AtomicInteger counter = new AtomicInteger(0);

    static {
        for (int i = 1; i <= 1000; i++) {
            items.put(i, "\"name\":\"Item " + i + "\",\"value\":" + i);
        }
    }

    public static void main(String[] args) throws IOException {
        HttpServer server = HttpServer.create(new InetSocketAddress(8081), 0);
        server.createContext("/items", new ItemsHandler());
        server.setExecutor(Executors.newCachedThreadPool());
        System.out.println("Java Server listening on port 8081");
        server.start();
    }

    static class ItemsHandler implements HttpHandler {
        @Override
        public void handle(HttpExchange exchange) throws IOException {
            String path = exchange.getRequestURI().getPath();
            String method = exchange.getRequestMethod();

            try {
                if (path.equals("/items")) {
                    handleItems(exchange, method);
                } else if (path.startsWith("/items/")) {
                    int id = parseId(path);
                    if (id <= 0) {
                        sendResponse(exchange, 400, "{\"error\":\"Invalid ID\"}");
                    } else {
                        handleItem(exchange, method, id);
                    }
                } else {
                    sendResponse(exchange, 404, "Not found");
                }
            } catch (Exception e) {
                sendResponse(exchange, 500, "{\"error\":\"Internal error\"}");
            }
        }

        private void handleItems(HttpExchange exchange, String method) throws IOException {
            switch (method) {
                case "GET":
                    listItems(exchange);
                    break;
                case "POST":
                    createItem(exchange);
                    break;
                default:
                    sendResponse(exchange, 405, "Method not allowed");
            }
        }

        private void handleItem(HttpExchange exchange, String method, int id) throws IOException {
            switch (method) {
                case "GET":
                    getItem(exchange, id);
                    break;
                case "PUT":
                    updateItem(exchange, id);
                    break;
                case "DELETE":
                    deleteItem(exchange, id);
                    break;
                default:
                    sendResponse(exchange, 405, "Method not allowed");
            }
        }

        private int parseId(String path) {
            try {
                return Integer.parseInt(path.substring("/items/".length()));
            } catch (NumberFormatException e) {
                return -1;
            }
        }

        private void listItems(HttpExchange exchange) throws IOException {
            StringBuilder sb = new StringBuilder("[");
            boolean first = true;
            for (Map.Entry<Integer, String> entry : items.entrySet()) {
                if (!first) sb.append(",");
                sb.append("{\"id\":").append(entry.getKey());
                String data = entry.getValue();
                if (data != null && !data.isEmpty()) {
                    sb.append(",").append(data);
                }
                sb.append("}");
                first = false;
            }
            sb.append("]");
            sendJsonResponse(exchange, 200, sb.toString());
        }

        private void createItem(HttpExchange exchange) throws IOException {
            String contentType = exchange.getRequestHeaders().getFirst("Content-Type");
            if (contentType == null || !contentType.contains("application/json")) {
                sendJsonResponse(exchange, 400, "{\"error\":\"Content-Type must be application/json\"}");
                return;
            }

            String body = readBody(exchange);
            String data = extractJsonContent(body);

            int id = (counter.getAndIncrement() % 1000) + 1;
            items.put(id, data);

            StringBuilder response = new StringBuilder("{\"id\":").append(id);
            if (data != null && !data.isEmpty()) {
                response.append(",").append(data);
            }
            response.append("}");

            sendJsonResponse(exchange, 200, response.toString());
        }

        private void getItem(HttpExchange exchange, int id) throws IOException {
            String data = items.get(id);
            if (data == null) {
                sendJsonResponse(exchange, 200, "{\"id\":" + id + ",\"name\":\"\",\"value\":0}");
                return;
            }

            StringBuilder response = new StringBuilder("{\"id\":").append(id);
            if (!data.isEmpty()) {
                response.append(",").append(data);
            }
            response.append("}");

            sendJsonResponse(exchange, 200, response.toString());
        }

        private void updateItem(HttpExchange exchange, int id) throws IOException {
            String contentType = exchange.getRequestHeaders().getFirst("Content-Type");
            if (contentType == null || !contentType.contains("application/json")) {
                sendJsonResponse(exchange, 400, "{\"error\":\"Content-Type must be application/json\"}");
                return;
            }

            String body = readBody(exchange);
            String data = extractJsonContent(body);
            items.put(id, data);

            StringBuilder response = new StringBuilder("{\"id\":").append(id);
            if (data != null && !data.isEmpty()) {
                response.append(",").append(data);
            }
            response.append("}");

            sendJsonResponse(exchange, 200, response.toString());
        }

        private void deleteItem(HttpExchange exchange, int id) throws IOException {
            items.remove(id);
            sendJsonResponse(exchange, 200, "{\"deleted\":true}");
        }

        private String readBody(HttpExchange exchange) throws IOException {
            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(exchange.getRequestBody(), StandardCharsets.UTF_8))) {
                return reader.lines().collect(Collectors.joining("\n"));
            }
        }

        private String extractJsonContent(String json) {
            if (json == null || json.isEmpty()) return "";
            json = json.trim();
            if (json.startsWith("{") && json.endsWith("}")) {
                String inner = json.substring(1, json.length() - 1).trim();
                return inner;
            }
            return "";
        }

        private void sendJsonResponse(HttpExchange exchange, int status, String body) throws IOException {
            exchange.getResponseHeaders().set("Content-Type", "application/json");
            sendResponse(exchange, status, body);
        }

        private void sendResponse(HttpExchange exchange, int status, String body) throws IOException {
            byte[] bytes = body.getBytes(StandardCharsets.UTF_8);
            exchange.sendResponseHeaders(status, bytes.length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(bytes);
            }
        }
    }
}

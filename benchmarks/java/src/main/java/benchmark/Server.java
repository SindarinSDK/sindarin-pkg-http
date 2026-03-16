package benchmark;

import io.javalin.Javalin;
import io.javalin.http.Context;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.JsonNode;

import java.util.*;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class Server {
    private static final Map<Integer, Map<String, Object>> items = new HashMap<>();
    private static final ReadWriteLock rwLock = new ReentrantReadWriteLock();
    private static final ObjectMapper mapper = new ObjectMapper();
    private static int counter = 0;

    static {
        for (int i = 1; i <= 1000; i++) {
            Map<String, Object> item = new LinkedHashMap<>();
            item.put("name", "Item " + i);
            item.put("value", i);
            items.put(i, item);
        }
    }

    public static void main(String[] args) {
        Javalin app = Javalin.create(config -> {
            config.showJavalinBanner = false;
        }).start(8081);

        System.out.println("Java Server listening on port 8081");

        app.get("/items", Server::listItems);
        app.post("/items", Server::createItem);
        app.get("/items/{id}", Server::getItem);
        app.put("/items/{id}", Server::updateItem);
        app.delete("/items/{id}", Server::deleteItem);
    }

    private static void listItems(Context ctx) {
        List<Map<String, Object>> result;
        rwLock.readLock().lock();
        try {
            result = new ArrayList<>(items.size());
            for (Map.Entry<Integer, Map<String, Object>> entry : items.entrySet()) {
                Map<String, Object> item = new LinkedHashMap<>();
                item.put("id", entry.getKey());
                item.putAll(entry.getValue());
                result.add(item);
            }
        } finally {
            rwLock.readLock().unlock();
        }
        ctx.json(result);
    }

    @SuppressWarnings("unchecked")
    private static void createItem(Context ctx) {
        String contentType = ctx.contentType();
        if (contentType == null || !contentType.contains("application/json")) {
            ctx.status(400).json(Map.of("error", "Content-Type must be application/json"));
            return;
        }

        Map<String, Object> data;
        try {
            data = mapper.readValue(ctx.body(), LinkedHashMap.class);
        } catch (Exception e) {
            data = new LinkedHashMap<>();
        }

        int id;
        rwLock.writeLock().lock();
        try {
            id = (counter % 1000) + 1;
            counter++;
            items.put(id, data);
        } finally {
            rwLock.writeLock().unlock();
        }

        Map<String, Object> result = new LinkedHashMap<>();
        result.put("id", id);
        result.putAll(data);
        ctx.json(result);
    }

    private static void getItem(Context ctx) {
        int id = Integer.parseInt(ctx.pathParam("id"));

        Map<String, Object> data;
        rwLock.readLock().lock();
        try {
            data = items.get(id);
        } finally {
            rwLock.readLock().unlock();
        }

        if (data == null) {
            ctx.json(Map.of("id", id, "name", "", "value", 0));
            return;
        }

        Map<String, Object> result = new LinkedHashMap<>();
        result.put("id", id);
        result.putAll(data);
        ctx.json(result);
    }

    @SuppressWarnings("unchecked")
    private static void updateItem(Context ctx) {
        int id = Integer.parseInt(ctx.pathParam("id"));

        String contentType = ctx.contentType();
        if (contentType == null || !contentType.contains("application/json")) {
            ctx.status(400).json(Map.of("error", "Content-Type must be application/json"));
            return;
        }

        Map<String, Object> data;
        try {
            data = mapper.readValue(ctx.body(), LinkedHashMap.class);
        } catch (Exception e) {
            data = new LinkedHashMap<>();
        }

        rwLock.writeLock().lock();
        try {
            items.put(id, data);
        } finally {
            rwLock.writeLock().unlock();
        }

        Map<String, Object> result = new LinkedHashMap<>();
        result.put("id", id);
        result.putAll(data);
        ctx.json(result);
    }

    private static void deleteItem(Context ctx) {
        int id = Integer.parseInt(ctx.pathParam("id"));

        rwLock.writeLock().lock();
        try {
            items.remove(id);
        } finally {
            rwLock.writeLock().unlock();
        }

        ctx.json(Map.of("deleted", true));
    }
}

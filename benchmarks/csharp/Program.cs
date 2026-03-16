using System.Collections.Concurrent;
using System.Text.Json;

var items = new ConcurrentDictionary<int, Dictionary<string, JsonElement>>();
var idLock = new object();
var nextId = 1;

// Pre-populate 1000 items
for (int i = 1; i <= 1000; i++)
{
    var item = new Dictionary<string, JsonElement>
    {
        ["name"] = JsonSerializer.SerializeToElement($"Item {i}"),
        ["value"] = JsonSerializer.SerializeToElement(i)
    };
    items[i] = item;
}

var builder = WebApplication.CreateSlimBuilder(args);
builder.WebHost.UseUrls("http://0.0.0.0:8081");
builder.Logging.ClearProviders();
var app = builder.Build();

// GET /items - list all
app.MapGet("/items", () =>
{
    var list = items.Select(kvp =>
    {
        var dict = new Dictionary<string, JsonElement>(kvp.Value)
        {
            ["id"] = JsonSerializer.SerializeToElement(kvp.Key)
        };
        return dict;
    }).ToList();

    return Results.Json(list);
});

// POST /items - create
app.MapPost("/items", async (HttpRequest request) =>
{
    var contentType = request.ContentType ?? "";
    if (!contentType.Contains("application/json"))
        return Results.Json(new { error = "Content-Type must be application/json" }, statusCode: 400);

    Dictionary<string, JsonElement> data;
    try
    {
        data = await request.ReadFromJsonAsync<Dictionary<string, JsonElement>>()
               ?? new Dictionary<string, JsonElement>();
    }
    catch
    {
        data = new Dictionary<string, JsonElement>();
    }

    int id;
    lock (idLock)
    {
        id = ((nextId - 1) % 1000) + 1;
        nextId++;
    }

    items[id] = data;

    var result = new Dictionary<string, JsonElement>(data)
    {
        ["id"] = JsonSerializer.SerializeToElement(id)
    };

    return Results.Json(result);
});

// GET /items/{id}
app.MapGet("/items/{id:int}", (int id) =>
{
    if (!items.TryGetValue(id, out var data))
    {
        return Results.Json(new { id, name = "", value = 0 });
    }

    var result = new Dictionary<string, JsonElement>(data)
    {
        ["id"] = JsonSerializer.SerializeToElement(id)
    };

    return Results.Json(result);
});

// PUT /items/{id}
app.MapPut("/items/{id:int}", async (int id, HttpRequest request) =>
{
    var contentType = request.ContentType ?? "";
    if (!contentType.Contains("application/json"))
        return Results.Json(new { error = "Content-Type must be application/json" }, statusCode: 400);

    Dictionary<string, JsonElement> data;
    try
    {
        data = await request.ReadFromJsonAsync<Dictionary<string, JsonElement>>()
               ?? new Dictionary<string, JsonElement>();
    }
    catch
    {
        data = new Dictionary<string, JsonElement>();
    }

    items[id] = data;

    var result = new Dictionary<string, JsonElement>(data)
    {
        ["id"] = JsonSerializer.SerializeToElement(id)
    };

    return Results.Json(result);
});

// DELETE /items/{id}
app.MapDelete("/items/{id:int}", (int id) =>
{
    items.TryRemove(id, out _);
    return Results.Json(new { deleted = true });
});

Console.WriteLine("C# Server listening on port 8081");
app.Run();

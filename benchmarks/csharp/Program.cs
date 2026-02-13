using System.Collections.Concurrent;
using System.Net;
using System.Text;
using System.Text.Json;

class Server
{
    private static readonly ConcurrentDictionary<int, Dictionary<string, JsonElement>> Items = new();
    private static int _nextId = 1;
    private static readonly object IdLock = new();

    static async Task Main()
    {
        var listener = new HttpListener();
        listener.Prefixes.Add("http://localhost:8081/");
        listener.Start();

        Console.WriteLine("C# Server listening on port 8081");

        while (true)
        {
            var context = await listener.GetContextAsync();
            _ = Task.Run(() => HandleRequest(context));
        }
    }

    static async Task HandleRequest(HttpListenerContext context)
    {
        var request = context.Request;
        var response = context.Response;

        try
        {
            var path = request.Url?.AbsolutePath ?? "/";
            var method = request.HttpMethod;

            response.ContentType = "application/json";

            if (path == "/items")
            {
                await HandleItems(request, response, method);
            }
            else if (path.StartsWith("/items/"))
            {
                var idStr = path["/items/".Length..];
                if (int.TryParse(idStr, out var id) && id > 0)
                {
                    await HandleItem(request, response, method, id);
                }
                else
                {
                    await SendResponse(response, 400, "{\"error\":\"Invalid ID\"}");
                }
            }
            else
            {
                response.ContentType = "text/plain";
                await SendResponse(response, 404, "Not found");
            }
        }
        catch
        {
            await SendResponse(response, 500, "{\"error\":\"Internal error\"}");
        }
        finally
        {
            response.Close();
        }
    }

    static async Task HandleItems(HttpListenerRequest request, HttpListenerResponse response, string method)
    {
        switch (method)
        {
            case "GET":
                await ListItems(response);
                break;
            case "POST":
                await CreateItem(request, response);
                break;
            default:
                response.ContentType = "text/plain";
                await SendResponse(response, 405, "Method not allowed");
                break;
        }
    }

    static async Task HandleItem(HttpListenerRequest request, HttpListenerResponse response, string method, int id)
    {
        switch (method)
        {
            case "GET":
                await GetItem(response, id);
                break;
            case "PUT":
                await UpdateItem(request, response, id);
                break;
            case "DELETE":
                await DeleteItem(response, id);
                break;
            default:
                response.ContentType = "text/plain";
                await SendResponse(response, 405, "Method not allowed");
                break;
        }
    }

    static async Task ListItems(HttpListenerResponse response)
    {
        var list = Items.Select(kvp =>
        {
            var dict = new Dictionary<string, JsonElement>(kvp.Value)
            {
                ["id"] = JsonSerializer.SerializeToElement(kvp.Key)
            };
            return dict;
        }).ToList();

        var json = JsonSerializer.Serialize(list);
        await SendResponse(response, 200, json);
    }

    static async Task CreateItem(HttpListenerRequest request, HttpListenerResponse response)
    {
        var contentType = request.ContentType ?? "";
        if (!contentType.Contains("application/json"))
        {
            await SendResponse(response, 400, "{\"error\":\"Content-Type must be application/json\"}");
            return;
        }

        using var reader = new StreamReader(request.InputStream, Encoding.UTF8);
        var body = await reader.ReadToEndAsync();

        Dictionary<string, JsonElement> data;
        try
        {
            data = JsonSerializer.Deserialize<Dictionary<string, JsonElement>>(body)
                   ?? new Dictionary<string, JsonElement>();
        }
        catch
        {
            data = new Dictionary<string, JsonElement>();
        }

        int id;
        lock (IdLock)
        {
            id = _nextId++;
        }

        Items[id] = data;

        var result = new Dictionary<string, JsonElement>(data)
        {
            ["id"] = JsonSerializer.SerializeToElement(id)
        };

        response.StatusCode = 201;
        await SendResponse(response, 201, JsonSerializer.Serialize(result));
    }

    static async Task GetItem(HttpListenerResponse response, int id)
    {
        if (!Items.TryGetValue(id, out var data))
        {
            await SendResponse(response, 404, "{\"error\":\"Item not found\"}");
            return;
        }

        var result = new Dictionary<string, JsonElement>(data)
        {
            ["id"] = JsonSerializer.SerializeToElement(id)
        };

        await SendResponse(response, 200, JsonSerializer.Serialize(result));
    }

    static async Task UpdateItem(HttpListenerRequest request, HttpListenerResponse response, int id)
    {
        if (!Items.ContainsKey(id))
        {
            await SendResponse(response, 404, "{\"error\":\"Item not found\"}");
            return;
        }

        var contentType = request.ContentType ?? "";
        if (!contentType.Contains("application/json"))
        {
            await SendResponse(response, 400, "{\"error\":\"Content-Type must be application/json\"}");
            return;
        }

        using var reader = new StreamReader(request.InputStream, Encoding.UTF8);
        var body = await reader.ReadToEndAsync();

        Dictionary<string, JsonElement> data;
        try
        {
            data = JsonSerializer.Deserialize<Dictionary<string, JsonElement>>(body)
                   ?? new Dictionary<string, JsonElement>();
        }
        catch
        {
            data = new Dictionary<string, JsonElement>();
        }

        Items[id] = data;

        var result = new Dictionary<string, JsonElement>(data)
        {
            ["id"] = JsonSerializer.SerializeToElement(id)
        };

        await SendResponse(response, 200, JsonSerializer.Serialize(result));
    }

    static async Task DeleteItem(HttpListenerResponse response, int id)
    {
        if (!Items.TryRemove(id, out _))
        {
            await SendResponse(response, 404, "{\"error\":\"Item not found\"}");
            return;
        }

        await SendResponse(response, 200, "{\"deleted\":true}");
    }

    static async Task SendResponse(HttpListenerResponse response, int status, string body)
    {
        response.StatusCode = status;
        var bytes = Encoding.UTF8.GetBytes(body);
        response.ContentLength64 = bytes.Length;
        await response.OutputStream.WriteAsync(bytes);
    }
}

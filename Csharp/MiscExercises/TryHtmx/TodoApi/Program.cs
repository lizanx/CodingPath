using Microsoft.AspNetCore.Html;
using TodoApi;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

var db = new List<TodoItem>()
{
    new() { Id = Guid.NewGuid(), Name = "abc", IsCompleted = true },
    new() { Id = Guid.NewGuid(), Name = "123", IsCompleted = false },
};

app.MapGet("/", () =>
{
    var builder = new HtmlContentBuilder();
    builder.AppendHtml("<body hx-get=\"/todos\" hx-trigger=\"load\" hw-swap=\"innerHTML\">");
    builder.AppendHtml("</body>");
    return new HtmlContentResult(Components.Document(builder));
});

app.MapGet("/todos", () => new HtmlContentResult(Components.TodoList(db)));

app.MapPost("/todos", (AddTodoItem command) =>
{
    var newTodo = new TodoItem { Id = Guid.NewGuid(), Name = command.Name, IsCompleted = false };
    db.Add(newTodo);
    return new HtmlContentResult(Components.TodoItem(newTodo));
});

app.MapPost("/todos/{id}/toggle", (string id) =>
{
    var todo = db.First(item => item.Id.ToString() == id);
    todo.IsCompleted = !todo.IsCompleted;
    return new HtmlContentResult(Components.TodoItem(todo));
});

app.MapDelete("/todos/{id}", (string id) =>
{
    var todo = db.First(item => item.Id.ToString() == id);
    db.Remove(todo);
});

app.MapGet("/hello-world", () => new HtmlResult(@"<!doctype html>
<html>
    <head>
        <meta charset=""UTF-8"">
        <meta name=""viewport"" content=""width=device-width, initial-scale=1.0"">
        <script src=""https://unpkg.com/htmx.org@1.9.6""
        integrity=""sha384-FhXw7b6AlE/jyjlZH5iHa/tTe9EpJ1Y55RjcgPbjeWMskSxZt1v9qkxLJWNJaGni""
        crossorigin=""anonymous""></script>
    </head>
    <body>
        <button hx-post=""/hello-world"" hx-swap=""outerHTML"">Get time</button>
    </body>
</html>
"));

app.MapPost("/hello-world", () =>
    new HtmlResult($@"<div>Hello World {DateTimeOffset.UtcNow}</div>"));

app.Run();

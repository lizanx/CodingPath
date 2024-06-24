using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using TaskManager.Server.Data;
using TaskManager.Shared;

namespace TaskManager.Server.Controllers;

[ApiController]
[Route("api/[controller]")]
public class TaskItemsController : ControllerBase
{
    private readonly ILogger<TaskItemsController> _logger;
    private readonly TaskManagerServerDb _db;

    public TaskItemsController(ILogger<TaskItemsController> logger, TaskManagerServerDb db)
    {
        _logger = logger;
        _db = db;
    }

    [HttpGet]
    public async Task<ActionResult<IEnumerable<TaskItem>>> GetTaskItemsAsync()
    {
        return await _db.TaskItems.ToListAsync();
    }

    [HttpGet("{id}")]
    public async Task<ActionResult<TaskItem>> GetTaskItemAsync(int id)
    {
        var taskItem = await _db.TaskItems.FindAsync(id);

        if (taskItem == null)
        {
            return NotFound();
        }
        return taskItem;
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> PutTaskItemAsync(int id, TaskItem item)
    {
        var taskItem = await _db.TaskItems.FindAsync(id);
        if (taskItem == null)
        {
            return NotFound();
        }

        taskItem.TaskName = item.TaskName;
        taskItem.IsCompleted = item.IsCompleted;

        await _db.SaveChangesAsync();

        return NoContent();
    }

    [HttpPost]
    public async Task<ActionResult<TaskItem>> PostTaskItemAsync(TaskItem item)
    {
        _db.TaskItems.Add(item);
        await _db.SaveChangesAsync();
        return CreatedAtAction("GetTaskItem", new { id = item.Id }, item);
    }

    [HttpDelete("{id}")]
    public async Task<IActionResult> DeleteTaskItemAsync(int id)
    {
        var taskItem = await _db.TaskItems.FindAsync(id);
        if (taskItem == null)
        {
            return NotFound();
        }

        _db.TaskItems.Remove(taskItem);
        await _db.SaveChangesAsync();

        return NoContent();
    }
}

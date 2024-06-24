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
    public async Task<ActionResult<IEnumerable<TaskItem>>> GetTaskItemAsync()
    {
        return await _db.TaskItems.ToListAsync();
    }
}

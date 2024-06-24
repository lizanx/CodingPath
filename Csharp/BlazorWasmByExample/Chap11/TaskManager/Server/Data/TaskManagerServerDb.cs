using Microsoft.EntityFrameworkCore;
using TaskManager.Shared;

namespace TaskManager.Server.Data;

public class TaskManagerServerDb : DbContext
{
    public TaskManagerServerDb(DbContextOptions<TaskManagerServerDb> options) : base(options)
    {}

    public DbSet<TaskItem> TaskItems { get; set; }
}

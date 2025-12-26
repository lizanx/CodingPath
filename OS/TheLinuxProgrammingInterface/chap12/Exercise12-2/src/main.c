#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <ctype.h>
#include <errno.h>

#define PROC_DIR "/proc"
#define MAX_PID 4194304 // /proc/sys/kernel/pid_max 通常为 4194304

typedef struct ProcessNode
{
    pid_t pid;
    pid_t ppid;
    char *name;
    char *cmdline;
    struct ProcessNode *children; // 指向第一个子节点
    struct ProcessNode *sibling;  // 指向下一个兄弟节点
} ProcessNode;

// 创建新节点
static ProcessNode *create_node(pid_t pid, pid_t ppid, const char *name, const char *cmdline)
{
    ProcessNode *node = calloc(1, sizeof(ProcessNode));
    if (!node)
        return NULL;
    node->pid = pid;
    node->ppid = ppid;
    node->name = name ? strdup(name) : strdup("(unknown)");
    node->cmdline = cmdline ? strdup(cmdline) : strdup("");
    return node;
}

// 释放单个节点（不递归）
static void destroy_node(ProcessNode *node)
{
    if (!node)
        return;
    free(node->name);
    free(node->cmdline);
    free(node);
}

// 递归释放整棵树
static void destroy_tree(ProcessNode *node)
{
    if (!node)
        return;
    destroy_tree(node->children);
    destroy_tree(node->sibling);
    destroy_node(node);
}

// 将 child 挂到 parent 的 children 链表末尾
static void append_child(ProcessNode *parent, ProcessNode *child)
{
    if (!parent || !child)
        return;
    if (!parent->children)
    {
        parent->children = child;
    }
    else
    {
        ProcessNode *last = parent->children;
        while (last->sibling)
            last = last->sibling;
        last->sibling = child;
    }
}

// 从 /proc/PID/status 读取 Name, Pid, PPid
static int read_status_fields(const char *pid_dir, pid_t *out_pid, pid_t *out_ppid, char **out_name)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/status", pid_dir);

    FILE *fp = fopen(path, "r");
    if (!fp)
        return -1;

    char line[512];
    pid_t pid = -1, ppid = -1;
    char *name = NULL;

    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, "Name:", 5) == 0)
        {
            char *start = line + 5;
            while (isspace((unsigned char)*start))
                start++;
            char *end = strchr(start, '\n');
            if (end)
                *end = '\0';
            name = strdup(start);
        }
        else if (strncmp(line, "Pid:", 4) == 0)
        {
            pid = atoi(line + 4);
        }
        else if (strncmp(line, "PPid:", 5) == 0)
        {
            ppid = atoi(line + 5);
        }
        if (pid != -1 && ppid != -1 && name)
            break;
    }
    fclose(fp);

    if (pid == -1 || ppid == -1 || !name)
    {
        free(name);
        return -1;
    }

    *out_pid = pid;
    *out_ppid = ppid;
    *out_name = name;
    return 0;
}

// 从 /proc/PID/cmdline 读取命令行（\0 分隔，转换为空格）
static char *read_cmdline(const char *pid_dir)
{
    char path[256];
    snprintf(path, sizeof(path), "%s/cmdline", pid_dir);

    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return strdup(""); // 无权限或已退出

    char buf[4096];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    close(fd);

    if (n <= 0)
        return strdup("");

    // 替换 \0 为 ' '，便于显示
    for (ssize_t i = 0; i < n; i++)
    {
        if (buf[i] == '\0')
            buf[i] = ' ';
    }

    // 去掉末尾多余空格
    while (n > 0 && buf[n - 1] == ' ')
        n--;
    buf[n] = '\0';

    return strdup(buf);
}

// 打印树（缩进）
static void print_tree(ProcessNode *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        putchar(' ');
    printf("%s (%d) [parent: %d] -- %s\n",
           node->name, (int)node->pid, (int)node->ppid, node->cmdline);

    // 先递归打印所有子节点（它们通过 sibling 连接）
    for (ProcessNode *child = node->children; child; child = child->sibling)
    {
        print_tree(child, depth + 2);
    }
}

int main(int argc, char *argv[])
{
    ProcessNode **nodes = calloc(MAX_PID, sizeof(ProcessNode *));
    if (!nodes)
    {
        perror("calloc nodes");
        return 1;
    }

    DIR *dir = opendir(PROC_DIR);
    if (!dir)
    {
        perror("opendir /proc");
        free(nodes);
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (!isdigit(entry->d_name[0]))
            continue;

        pid_t pid = atoi(entry->d_name);
        if (pid <= 0 || pid >= MAX_PID)
            continue;

        char pid_dir[512];
        snprintf(pid_dir, sizeof(pid_dir), "%s/%s", PROC_DIR, entry->d_name);

        struct stat st;
        if (stat(pid_dir, &st) != 0 || !S_ISDIR(st.st_mode))
            continue;

        pid_t read_pid, ppid;
        char *name = NULL;
        if (read_status_fields(pid_dir, &read_pid, &ppid, &name) != 0)
        {
            free(name);
            continue;
        }

        // 确保读取的 pid 与目录名一致（防止 race condition）
        if (read_pid != pid)
        {
            free(name);
            continue;
        }

        char *cmdline = read_cmdline(pid_dir);
        nodes[pid] = create_node(pid, ppid, name, cmdline);

        free(name);
        free(cmdline);
    }
    closedir(dir);

    // 创建虚拟根节点（用于挂载所有顶级进程）
    ProcessNode *root = create_node(-1, -1, "<root>", "");

    // 建立父子关系
    for (pid_t i = 1; i < MAX_PID; i++)
    {
        if (!nodes[i])
            continue;

        ProcessNode *parent = NULL;
        if (nodes[i]->ppid > 0 && nodes[i]->ppid < MAX_PID)
        {
            parent = nodes[nodes[i]->ppid];
        }
        if (!parent)
        {
            parent = root; // 孤儿进程（如守护进程、父进程已退出）
        }
        append_child(parent, nodes[i]);
    }

    // 打印所有顶级子树（通常是 init/systemd 及其后代）
    for (ProcessNode *child = root->children; child; child = child->sibling)
    {
        print_tree(child, 0);
        printf("\n");
    }

    // 清理
    for (pid_t i = 0; i < MAX_PID; i++)
    {
        // 节点已被挂入树中，由 destroy_tree 释放
        // 这里不重复 free
    }
    destroy_tree(root);
    free(nodes);

    return 0;
}

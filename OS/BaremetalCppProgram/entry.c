extern void SetVMem(long addr, unsigned char data);

// 定义光标信息
typedef struct
{
    long offset; // 暂时只需要一个偏移量
} CursorInfo;

CursorInfo g_cursor_info = {0}; // 全局变量，保存光标信息

int putchar(int ch)
{
    if (ch == '\n')
    {                                                                  // 处理换行
        g_cursor_info.offset += 80 * 2;                                // 一行是80字符
        g_cursor_info.offset -= ((g_cursor_info.offset / 2) % 80) * 2; // 回到行首
    }
    else
    {
        SetVMem(g_cursor_info.offset++, (unsigned char)ch);
        SetVMem(g_cursor_info.offset++, 0x0f);
    }
    return ch;
}

int puts(const char *str)
{
    // 处理C字符串，需要向后找到0结尾，逐一调用putchar
    for (const char *p = str; *p != '\0'; p++)
    {
        putchar(*p);
    }
    return 0;
}

void Entry()
{
    // putchar('X');
    puts("Hello, World!\nThe 2nd line.");
    // putchar('Y');
}

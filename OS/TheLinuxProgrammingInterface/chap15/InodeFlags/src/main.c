#define _DEFAULT_SOURCE
#include <fcntl.h>
#include <linux/fs.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <time.h>
#include "tlpi_hdr.h"

#define MY_FILE "myfile"

int main(int argc, char *argv[])
{
    int fd = open(MY_FILE, O_CREAT | O_RDWR, 0660);
    if (fd < 0)
        errExit("Failed to open %s", MY_FILE);
    write(fd, "Hello world", 12);

    long attr = 0;
    if (ioctl(fd, FS_IOC_GETFLAGS, &attr))
        errExit("Failed to get flags.");
    printf("i-node flag: %#lX\n", attr);
    struct stat st;
    if (fstat(fd, &st))
        errExit("Failed to stat %s", MY_FILE);
    time_t lastAccessTime = st.st_atim.tv_sec;
    printf("Last access time: %s\n", ctime(&lastAccessTime));
    attr |= FS_NOATIME_FL;
    if (ioctl(fd, FS_IOC_SETFLAGS, &attr))
        errExit("Failed to set flags.");
    else
        printf("No-access-time flag set.\n");
    if (close(fd))
        errMsg("Failed to close %s\n", MY_FILE);

    printf("\n===== Sleep 3s ... =====\n\n");
    sleep(3);

    fd = open(MY_FILE, O_RDONLY);
    if (fd < 0)
        errExit("Failed to open %s", MY_FILE);
    char buf[32];
    ssize_t n = read(fd, buf, sizeof(buf));
    buf[n] = '\0';
    printf("Read content: %s\n", buf);
    if (fstat(fd, &st))
        errExit("Failed to stat %s\n", MY_FILE);
    lastAccessTime = st.st_atim.tv_sec;
    printf("Last access time(should not change): %s\n", ctime(&lastAccessTime));
    close(fd);

    if (unlink(MY_FILE))
        errMsg("Failed to remove %s\n", MY_FILE);

    return 0;
}

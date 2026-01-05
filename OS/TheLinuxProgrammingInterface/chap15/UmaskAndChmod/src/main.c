#include <fcntl.h>
#include <sys/stat.h>
#include <file_perms.h>
#include "tlpi_hdr.h"

#define MY_FILE "myfile"
#define MY_DIR "mydir"
#define FILE_PERMISSION (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) // rw-rw----
#define DIR_PERMISSION (S_IRWXU | S_IRWXG | S_IRWXO)            // rwxrwxrwx
#define UMASK_SETTING (S_IWGRP | S_IXGRP | S_IWOTH | S_IXOTH)   // forbid grp-write/grp-exec/other-write/other-exec

int main(int argc, char *argv[])
{
    mode_t u = umask(UMASK_SETTING);
    printf("Original umask setting: %s\n", filePermStr(u, 0));

    int fd = open(MY_FILE, O_CREAT | O_RDWR | O_EXCL, FILE_PERMISSION);
    if (fd < 0)
        errExit("Failed to open %s\n", MY_FILE);
    if (mkdir(MY_DIR, DIR_PERMISSION) < 0)
        errExit("Failed to make dir %s\n", MY_DIR);

    u = umask(0); // clear umask setting

    printf("\n===== Check permission of newly created file =====\n\n");

    struct stat st;
    if (stat(MY_FILE, &st))
        errExit("Failed to stat %s\n", MY_FILE);
    printf("Request file permission: %s\n", filePermStr(FILE_PERMISSION, 0));
    printf("Process umask: %s\n", filePermStr(u, 0));
    printf("Actual file permission: %s\n", filePermStr(st.st_mode, 0));

    printf("\n===== Check permission of newly created directory =====\n\n");

    if (stat(MY_DIR, &st))
        errExit("Failed to stat %s\n", MY_DIR);
    printf("Request dir permission: %s\n", filePermStr(DIR_PERMISSION, 0));
    printf("Process umask: %s\n", filePermStr(u, 0));
    printf("Actual dir permission: %s\n", filePermStr(st.st_mode, 0));

    if (close(fd))
        errMsg("Failed to close %s\n", MY_FILE);

    printf("\n===== Change permission via chmod and check file permission again =====\n\n");

    if (chmod(MY_FILE, FILE_PERMISSION))
        errMsg("Failed to change file permission for %s\n", MY_FILE);
    if (stat(MY_FILE, &st))
        errExit("Failed to stat %s\n", MY_FILE);
    printf("Request file permission: %s\n", filePermStr(FILE_PERMISSION, 0));
    printf("Process umask: %s\n", filePermStr(u, 0));
    printf("Actual file permission: %s\n", filePermStr(st.st_mode, 0));

    if (unlink(MY_FILE))
        errMsg("Failed to remove file %s\n", MY_FILE);
    if (rmdir(MY_DIR))
        errMsg("Failed to remove dir %s\n", MY_DIR);

    return EXIT_SUCCESS;
}

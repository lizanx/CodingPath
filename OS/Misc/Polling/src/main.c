#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <sys/select.h>
#include <poll.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int select_demo()
{
    int efd = eventfd(0, 0);
    if (efd < 0)
    {
        perror("eventfd");
        return -1;
    }

    if (fork() == 0)
    {
        // Child
        sleep(1);
        uint64_t val = 3;
        write(efd, &val, sizeof(val));
        printf("Child: write %lu\n", val);
        exit(0);
    }

    // Parent
    while (true)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(efd, &fds);
        int nfds = efd + 1;
        int ret = select(nfds, &fds, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select");
            break;
        }
        if (FD_ISSET(efd, &fds))
        {
            uint64_t val = 0;
            read(efd, &val, sizeof(val));
            printf("Parent: got event %lu\n", val);
            break;
        }
    }

    close(efd);
    return 0;
}

static int poll_demo()
{
    int efd = eventfd(0, 0);
    if (efd < 0)
    {
        perror("eventfd");
        return -1;
    }

    if (fork() == 0)
    {
        // Child
        sleep(1);
        uint64_t val = 5;
        write(efd, &val, sizeof(val));
        printf("Child: write %lu\n", val);
        exit(0);
    }

    struct pollfd fds[1];
    fds[0].fd = efd;
    fds[0].events = POLLIN;
    while (true)
    {
        int ret = poll(fds, 1, -1);
        if (ret < 0)
        {
            perror("poll");
            break;
        }
        if (fds[0].revents & POLLIN)
        {
            uint64_t val = 0;
            read(fds[0].fd, &val, sizeof(val));
            printf("Parent: got event %lu\n", val);
            break;
        }
    }

    close(efd);
    return 0;
}

static int epoll_demo()
{
    int efd = eventfd(0, 0);
    if (efd < 0)
    {
        perror("eventfd");
        return -1;
    }

    int epfd = epoll_create1(0);
    if (epfd < 0)
    {
        perror("epoll_create1");
        return -2;
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = efd;
    if (epoll_ctl(epfd, EPOLL_CTL_ADD, efd, &ev) < 0)
    {
        perror("epoll_ctl");
        return -3;
    }

    if (fork() == 0)
    {
        // Child
        sleep(1);
        uint64_t val = 7;
        write(efd, &val, sizeof(val));
        printf("Child: write %lu\n", val);
        exit(0);
    }

    // Parent
    struct epoll_event events[10];
    while (true)
    {
        int n = epoll_wait(epfd, events, 10, -1);
        if (n < 0)
        {
            perror("epoll_wait");
            break;
        }
        for (int i = 0; i < n; ++i)
        {
            if (events[i].data.fd == efd)
            {
                uint64_t val = 0;
                read(efd, &val, sizeof(val));
                printf("Parent: got event %lu\n", val);
                goto out;
            }
        }
    }
out:
    close(efd);
    close(epfd);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: program <1|2|3>\n Where 1-select, 2-poll, 3-epoll\n");
        exit(0);
    }

    int ret = 0;
    if (argv[1][0] == '1')
    {
        ret = select_demo();
        if (ret)
        {
            printf("Fail, ret = %d\n", ret);
            exit(ret);
        }
    }
    else if (argv[1][0] == '2')
    {
        ret = poll_demo();
        if (ret)
        {
            printf("Fail, ret = %d\n", ret);
            exit(ret);
        }
    }
    else if (argv[1][0] == '3')
    {
        ret = epoll_demo();
        if (ret)
        {
            printf("Fail, ret = %d\n", ret);
            exit(ret);
        }
    }
    else
    {
        fprintf(stderr, "Unknown args[1]: %s\n", argv[1]);
    }

    return 0;
}

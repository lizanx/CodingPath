# Exercises Answers

## Chapter 1
1. Manage hardware resources and offer programming interfaces for user programs.
2. Mainframe: Multics, Server: Linux, PC: Windows/MacOS, Handheld: Android/iOS, Embedded/Realtime: freeRTOS
3. 
    - Timesharing: The system can be shared among multiple users, where each can communicate with it as if he/she totally owns the system.
    - Multiprogramming: The system can run multiple programs in turn rather than sequentially, as if multiple programs run at the same time.
4. Due to spatial locality, close data may be used soon. And it's faster for cpu to read 32/64 aligned data.
5. IO intensive programs may occupy too much cpu time.
6. Because kernel should manage all IO requests to avoid conflicts and resolve other issues like ordering, keeping user programs away from messing up the system.
7. It lives on, as today all Windows-PC are family-of-computers and so are Android phones.
8. 
    - 25 * 80 / 8 = 250byte -> $1250(1980)
    - 1200 * 900 * 24 / 8 = 3240000byte -> $16million(1980) 
9. Robustness and flexibility: more robust means less flexible, more flexible means less robust(usually).
10. The two layers restrict what user programs can do and manage all hardware resources in kernel, which greatly improves robustness. Besides, kernel offers abstraction of hardware, which simplifies user programs a lot.
    - Kernel Mode: have access to all hardware resources, manage them and offer API to upper layer.
    - User Mode: cannot operate hardware directly, communicate with kernel to acquire certain capabilities.
11. 
12. a,b,c,d
13. 20ms
14. 1 billion instructions.
15. About 5us.
16. For writing no blocking is needed, the written data can be buffered in cache and writing is actually done later.
17. It's used to enter kernel mode: user program put syscall number and parameters somewhere and use `trap` to invoke actual syscall action in kernel.
18. Yes, it's always needed. For multiprogramming, process table is used to track relations of processes and cope with them properly(scheduling, switching...).
19. No.
20. `fork`: will always succeed. `exec`: fails when the given program is not executable. `unlink`: fails when the target file doesn't exist.
21. 
    - CPU: time multiplexing
    - memory: space multiplexing
    - disk: space multiplexing
    - network card: time multiplexing
    - printer: time multiplexing
    - keyboard: time multiplexing
    - display: space multiplexing
22. Yes: if writing fails, `count` is -1; else if actual written bytes is less than `nbytes`, `count < nbytes`.
23. 1, 5, 9, 2
24. 100ms
25. Block file supports random read/write, while character file only support sequential read/write.
26. No need to be the same, the library procedure call name is more important since most programs use them to do tasks and it should be stable.
27. OS can allocate memory for each process dynamically to save physical memory, and user program always has the whole address space without worrying about execeeding certain limit.
28. Often it's unimportant, but in case of critical performance programming and strictly portable programming it matters.
29. If the program only uses libraries that support both UNIX and Windows, it's fine. Otherwise, programmer must find an alternative way to realize corresponding functionalities on different operating systems.
30. OS can never be completely portrable since it manages hardware directly which involves architecture-dependent instructions. Layers that can be portale: process scheduler/file system/device driver framework.
31. Separation of mechanism and policy make it easy to design different policies for different modules, and this flexibility/modularity is exactly what micro-kernel needs.
32. They're complex and there's always performance overhead.

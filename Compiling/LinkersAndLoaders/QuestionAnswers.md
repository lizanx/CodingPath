# Questions and Answers
## Chap1
1. What is the advantage of separating a linker and loader into separate programs? Under what circumstances would a combined linking loader be useful?
> 分离 linker/loader 的优点：
> - 模块化设计：linker/loader 职责分离，便于维护和调试；
> - 灵活性：链接后生成的文件可适用于不同的硬件或操作系统平台，而加载器可以独立适应不同的内存布局；
> - 复用性：同一 linker 为不同 OS 生成目标文件，同一 loader 加载不同 linker 生成的可执行文件；
> - 便于实现动态链接：linker 只处理静态链接部分，loader 可在运行时配合 DLL 工作。
>
> 把 linker/loader 整合的适用场景：
> - 嵌入式环境：内存受限，减少程序体积；
> - JIT 或动态代码生成：运行时生成代码并立即执行，linker/loader 紧密结合，难以分离；
> - 简易系统或教学场景；
> - 动态重定位需求：某些系统中，加载时需要根据当前内存情况做链接时未确定的地址重定位，合并可以避免两次扫描目标文件。

2. Nearly every programming system produced in the past 50 years includes a linker. Why?
> - 模块开发的需要
> - 分离编译与提高效率
> - 代码复用与库支持
> - 地址绑定与重定位
> - 解决跨模块引用
> - 支持不同的内存模型和硬件平台

3. In this chapter we’ve discussed linking and loading assembled or compiled machine code. Would a linker or loader be useful in a purely interpretive system that directly interprets source language code? How about in a interpretive system that turns the source into an intermediate representation like P-code or the Java Virtual Machine?
> - 对于解释型语言，链接和加载的工程都被集成到解释器中去了：
>   - 解释执行代码时，对于外部符号的解析过程即为 linker 的功能（重定位）；
>   - 加载代码时，需要解析代码、构建运行时环境、准备资源等，这些即对应 loader 的功能。
>
> - 对于中间代码语言(Java/C#)：
>   - 生成中间代码时，需要生成对外部符号(class)的引用，并在加载时解析该引用并重定位到实际引用地址，此即对应 linker 的工作；
>   - 虚拟机加载中间代码时，需要做一系列环境构建和资源初始化，并将中间代码转化为虚拟机内部的运行时数据结构，此即对应 loader 的工作。

## Chap2
3. Does a linker or loader need to ‘‘understand’’ every instruction in the target architecture’s instruction set? If a new model of the target adds new instructions, will the linker need to be changed to support them? What if it adds new addressing modes to existing instructions, like the 386 did relative to the 286?
> - linker/loader 做的是地址引用解析和重定位工作，因此需要理解 ISA 对应的寻址模式和涉及到跳转、重定位的指令(`jmp/call`)，而对于纯计算用的指令(`add/sub`)不需要关注；
> - 新增指令的话，参考上述，纯计算指令无需修改 linker/loader，但如果是涉及跳转、重定位的指令，需要更新 linker/loader；
> - 寻址模式修改的话，必定要更新 linker/loader 以支持新的寻址模式。

4. Back in the Golden Age of computing, when programmers worked in the middle of the night because that was the only time they could get computer time, rather than because that’s when they woke up, many computers used word rather than byte addresses. The PDP-6 and 10, for example had 36 bit words and 18 bit addressing, with each instruction being a word with the operand address in the low half of the word. (Programs could also store addresses in the high half of a data word, although there was no direct instruction set support for that.) How different is linking for a word addressed architecture compared to linking for a byte addressed architecture?
> 字节寻址模式：更灵活，内存利用效率更高，但 linker/loader 对重定位的处理更复杂；
> 字寻址模式：对齐更简单，linker/loader 实现更简单，但内存利用效率相对较低。

5. How hard would it be to build a retargetable linker, that is, one that could be built to handle different target architectures by changing a few specific parts of the source code for the linker? How about a multi-target linker, that could handle code for a variety of different architectures (although not in the same linker job)?
> linker/loader 的实现必须适配固有的不同硬件架构差异，包括不同的 ABI、不同的寻址方式等，还需要平衡通用性和性能，比较困难。

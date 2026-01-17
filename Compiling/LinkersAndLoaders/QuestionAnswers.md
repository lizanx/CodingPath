# Liners and Loaders
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

## Chap4
1. Why does a linker shuffle around segments to put segments of the same type next to each other? Wouldn’t it be easier to leave them in the original order?
> - 将同类型的段组合有利于加载时一次性 `mmap` 一整个段而仅浪费最后一页内存的部分 padding，如果按照原样不进行组合，由于内存分页且访问权限仅可以以页为单位设置，就会浪费很多内存页；
> - 可以减少 program header 数量，节省磁盘空间；
> - 提升缓存和 TLB 命中率（空间局部性）；
> - 减少 `mmap` 次数，提升加载效率。

2. When, if ever, does it matter in what order a linker allocates storage for routines? In our example, what difference would it make if the linker allocated newyork, mass, calif, main rather than main, calif, mass, newyork. (We’ll ask this question again later when we discuss overlays and dynamic linking, so you can disregard those considerations.)
> - 频繁调用的 caller/callee 如果相近可提高 cache hit rate，影响性能；
> - 嵌入式系统中如果从 Flash 中读取代码，其分块读取特性可能影响性能；
> - 对齐要求可能导致代码体积膨胀，重排可能优化代码体积；
> - 安全敏感场景中，分离敏感函数和不可信代码可减少攻击可能性。

3. In most cases a linker allocates similar sections sequentially, for example, the text of calif, mass, and newyork one after another. But it allocates all common sections with the same name on top of each other. Why?
> - 语义不同：common sections 实质就是未初始化的全局变量，语义上同名的符号指向同一对象，所以要重叠覆盖并取最大空间（兼容）；
> - 而不同的普通 sections 是良好定义的，合并即可。


4. Is it a good idea to permit common blocks declared in different input files with the same name but different sizes? Why or why not?
> 坏注意，现代 GCC/MSVC 上都默认启用 `-fno-common` 禁用 common section：
> - 不同 size 的同名 common section 违反 ODR(One Definition Rule)；
> - 语义不清晰，造成程序逻辑混乱；
> - 难以调试和排查问题。
> 但旧的 Unix linker 可能宽容这种行为。

## Chap6
1. What should a linker do if two modules in different libraries define the same symbol? Is it an error?
> - 如果多个符号都是强符号，则报错；
> - 如果是一个强符号和多个弱符号，则采用强符号；
> - 如果是多个弱符号，采用第一个。

2. Library symbol directories generally include only defined global symbols. Would it be useful to include undefined global symbols as well?
> 有用，现在库的符号表已经包含了未定义的符号，用于后续的依赖查找。

3. When sorting object files using `lorder` and `tsort`, it’s possible that `tsort` won’t be able to come up with a total order for the files. When will this happen, and is it a problem?
> - 当有循环依赖时，`tsort` 可能无法正确输出依赖拓扑；
> - 当依赖信息缺失、不完整时，`tsort` 可能输出一个偏序的拓扑（非唯一）。
> 循环依赖是设计缺陷，应该予以解决，使依赖关系构成 DAG；
> 偏序拓扑一般不是问题，仍可正常链接（常由弱符号导致）。

4. Some library formats put the directory at the front of the library while others put it at the end. What practical difference does it make?
> 将索引放在库的开头是更优的选择：
> - 链接器可以首先读取索引，快速获取符号信息；
> - 生成库时先输出索引再输出实际内容，有利于增量构建和并行构建（放在结尾必须等目标文件内容写入后才能写入索引）。

5. Describe some other situations where weak externals and weak definitions are useful.
> - 提供可选的默认实现：库可以提供一个弱符号的默认实现，而可以被用户自定义的强符号实现覆盖；
> - 作为条件编译的替代手段：提供未定义的默认弱符号，如果链接了某个提供强符号的模块则开启对应功能，否则默认关闭；
> - 跨平台库上提供默认的 fallback 实现：针对特定平台定义特定的强符号，在没有对应强符号的平台上 fallback 到弱符号使用；
> - **C++ 中内联函数和模板实例化：这两者往往生成弱符号，允许多个编译单元重复定义，链接时仅保留一份，是 ODR 的实现基础之一；**
> - 嵌入式中的中断向量表：启动的汇编代码中往往定义默认的弱符号中断处理函数，后续可由使用者覆写来更改默认行为（无需更改的部分使用默认实现，不必手动填充向量表）；
> - 单测中动态插桩：生产代码中使用弱符号，单测代码中提供测试行为的强符号，那么链接单测模块时即可使用模拟实现，不链接时使用生产实现。

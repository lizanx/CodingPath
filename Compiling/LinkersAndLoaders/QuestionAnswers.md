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

## Chap7
3. References to symbols that are pseudo-registers and thread local storage are resolved as offsets from the start of the segment, while normal symbol references are resolved as absolute addresses. Why?
> 伪寄存器和 TLS 存储的地址都是编译时未知、运行时确定的，所以必须使用偏移地址；
> 而普通全局变量的地址是全局唯一且编译时即可确定的，因此可用绝对地址。

## Chap8
1. Compile some small C routines with PIC and non-PIC code. How much slower is the PIC code than non-PIC? Is it enough slower to be worth having non-PIC versions of libraries for programmers in a hurry?
> 现代硬件上 `PIC` 带来的性能影响通常在 1%~5%，可以忽略，不值得为维护两个版本的库付出额外的精力。
> 除非在高实时性要求或极端高性能计算场景中，在评估确认 PIC 带来可观的影响后，可考虑提供静态非 PIC 版本。

3. In the overlay segment table, there’s no explicit marking of conflicting segments. When the overlay manager loads a segment and the segment’s path, how does the manager determine what segments to mark as not present?
> - 支持覆盖段的 linker 会在链接时分析路径调用，构建依赖关系；
> - 运行时加载某个段时，会检查其所需的地址空间是否被其他段使用，如果被使用则相应卸载或根据依赖执行其他操作。

## Chap9
1. If you look in a `/shlib` directory on a Unix system with shared libraries, you’ll usually see three or four versions of each library with names like `libc_s.2.0.1` and `libc_s.3.0.0`. Why not just have the most recent one?
> 该目录是旧式 Unix 用来保存静态共享库(static shared lib)的目录：
> 由于静态共享库中的符号地址都是固化到可执行程序中的，因此任何地址改动都导致与之前的程序不兼容，需要重新链接，故而保存多个版本以实现兼容性。

## Chap10
1. In ELF shared libraries, libraries are often linked so that calls from one routine to another within a single shared library go through the PLT and have their addresses bound at runtime. Is this useful? Why or why not?
> 动态库内部的函数调用也统一使用 PLT 而不是相对地址调用的原因：
> - 为了符号介入(Symbol Interposition)能力：
动态链接器允许在运行时使用一个外部同名符号替换掉共享库中的全局函数，如果使用直接相对跳转，那么无法实现这种行为，而使用 PLT 很容易做到；
> - 支持延迟绑定的一致性：
如果共享库内函数调用使用直接相对跳转，那么就需要在库加载时即对相对跳转的指令进行重定位，违反延迟绑定；
> - 统一的 PLT 实现让编译器、链接器可以简单直接地统一处理所有函数调用，而不用去分析调用是内部调用还是外部调用。

2. Imagine that a program calls a library routine `plugh()` that is found in a shared library, and the programmer builds a dynamically linked program that uses that library. Later, the system manager notices that `plugh` is a silly name for a routine and installs a new version of the library that calls the routine `xsazq` instead. What happens when the next time the programmer runs the program?
> 如果新的共享库中兼容地保留了 `plugh` 函数，那么程序还会继续调用该函数；
> 而如果新的共享库中破坏性地删除了该函数，那么程序会因为找不到对应的符号而启动失败。

3. If the runtime environment variable `LD_BIND_NOW` is set, the ELF dynamic loader binds all of the program’s PLT entries at load time. What would happen in the situtation in the previous problem if `LD_BIND_NOW` were set?
> 程序依然启动失败，但失败的时间点提前——从初次调用 `plugh` 时失败变为初始化时即失败，无法进入到 `main()` 函数；
> 因为 `LD_BIND_NOW` 告诉加载器在初始化加载时即解析所有符号，而不是延迟到初次使用时才绑定。

4. Microsoft implemented lazy procedure binding without operating system assistance by adding some extra cleverness in the linker and using the existing facilities in the operating system. How hard would it be to provide transparent access to shared data, avoiding the extra level of pointers that the current scheme uses?
> 非常困难，ASLR 的需求导致很难透明化，而且还要求 `.text` 段是只读的，此外数据段还需要是按需复制的；
> 当前 x64/Arm 等架构生态下不会对 ABI 进行大改而实现问题中的需求，要解决需要 hardware + compiler + linker 协作处理。

## Chap11
2. Look at the generated code from a compiler for C++ or another object oriented language. How much better could a link time optimizer make it? What info could the compiler put in the object module to make it easier for the linker to do interesting optimizations? How badly do shared libraries mess up this plan?
> 链接器可能的优化：
> - 跨模块内联
> - 过程间常量传播
> - 死代码消除
> - 全局指针分析
> - 虚函数去虚拟化
> - 代码布局优化
> 编译器可能提供的辅助信息：
> - 控制流程摘要
> - 函数属性标记
> - 内联候选提示
> - 类型继承关系
> - 指针逃逸分析结果
> - PGO
> 共享库可能造成的破坏：
> - 动态绑定的硬边界，必须使用 PLT/GOT
> - 地址空间随机化的代价
> - 符号截断问题（不同库对同一符号可能有不同实现，必须确保一致）


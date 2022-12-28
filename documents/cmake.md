# 一般编译

cmake指定最小版本：

**cmake_minimum_required(VERSION 3.5 FATAL_ERROR)**

FATAL_ERROR指严重错误



project指定语言用：

`project(XXX LANGUAGES CXX)`

CXX 指C++，CMAKE默认就是C++



生成构建器->生成文件

cmake直接执行 或者使用 `cmake -H -B`

`cmake ..` 和 `cmake -H..`是一样的

-H指在某个目录下搜索 -B指在某个目录下生成所有的文件



CMake是一个构建系统生成器。将描述构建系统(如：Unix Makefile、Ninja、Visual Studio等)应当如何操作才能编译代码。然后，CMake为所选的构建系统生成相应的指令。默认情况下，在GNU/Linux和macOS系统上，CMake使用Unix Makefile生成器。Windows上，Visual Studio是默认的生成器。



生成文件：

`cmake --build .`

`cmake --build . --target <target-name>`

指定构建目标，target-name可以换成help来查看所有可用的名字

一般功能如下：

+ **all**(或Visual Studio generator中的ALL_BUILD)是默认目标，将在项目中构建所有目标。
+ **clean**，删除所有生成的文件。
+ **rebuild_cache**，将调用CMake为源文件生成依赖(如果有的话)。
+ **edit_cache**，这个目标允许直接编辑缓存。



# 关于切换生成器

用以下命令，可在平台上找到生成器名单，以及已安装的CMake版本：

`cmake --help`

切换生成器需要使用 -G来进行切换

即在配置生成器的时候便使用-G

`cmake --build .`将`ninja`命令封装在一个跨平台的接口中



# 关于生成静态库和动态库

**`add_library(message STATIC Message.hpp Message.cpp)`**

生成必要的构建指令，将指定的源码编译到库中。`add_library`的第一个参数是目标名。整个`CMakeLists.txt`中，可使用相同的名称来引用库。生成的库的实际名称将由CMake通过在前面添加前缀`lib`和适当的扩展名作为后缀来形成。生成库是根据第二个参数(`STATIC`或`SHARED`)和操作系统确定的。



**`target_link_libraries(hello-world message)`**

将库链接到可执行文件。此命令还确保`hello-world`可执行文件可以正确地依赖于消息库。因此，在消息库链接到`hello-world`可执行文件之前，需要完成消息库的构建。

同target类的指令来确定目标



其他的add_library第二参数

CMake接受其他值作为`add_library`的第二个参数的有效值，我们来看下本书会用到的值：

+ **STATIC**：用于创建静态库，即编译文件的打包存档，以便在链接其他目标时使用，例如：可执行文件。
+ **SHARED**：用于创建动态库，即可以动态链接，并在运行时加载的库。可以在`CMakeLists.txt`中使用`add_library(message SHARED Message.hpp Message.cpp)`从静态库切换到动态共享对象(DSO)。
+ **OBJECT**：可将给定`add_library`的列表中的源码编译到目标文件，不将它们归档到静态库中，也不能将它们链接到共享对象中。如果需要一次性创建静态库和动态库，那么使用对象库尤其有用。我们将在本示例中演示。
+ **MODULE**：又为DSO组。与`SHARED`库不同，它们不链接到项目中的任何目标，不过可以进行动态加载。该参数可以用于构建运行时插件。



对于OBJECT第二参数的使用：

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(recipe-03 LANGUAGES CXX)
add_library(message-objs
    OBJECT
        Message.hpp
        Message.cpp
    )
# this is only needed for older compilers
# but doesn't hurt either to have it
set_target_properties(message-objs
    PROPERTIES
        POSITION_INDEPENDENT_CODE 1
    )
add_library(message-shared
    SHARED
        $<TARGET_OBJECTS:message-objs>
    )
add_library(message-static
    STATIC
        $<TARGET_OBJECTS:message-objs>
    )
add_executable(hello-world hello-world.cpp)
target_link_libraries(hello-world message-static)
```

1. 保证编译的目标文件与生成位置无关，可以使用set_target_properties命令来设置message-objs的相应属性来实现



2. 其次，引用对象库的生成器表达式语法：

$\<TARGET_OBJECTS:message-objs>

==生成器表达式==：是CMake在生成时(即配置之后)构造，用于生成特定于配置的构建输出



3. 输出时的名字可以由set_target_properties指定

    `set-target_properties(message-static PROPERTIES OUTPUT_NAME "messasge")`

    输出的就是**libmessage.a**而不是**libmessage-static.a**



# 关于if elseif endif

逻辑真假的表示

变量设置为：1 ON YES true Y 或者任意非0的数，则逻辑为真

变量设置为：0 OFF NO false N IGNORE NOTFOUND 空字符串 或者以-NOTFOUND 为后缀，则逻辑变量为false



#### BUILD_SHARED_LIBS全局变量的作用

**`BUILD_SHARED_LIBS`**是CMake的一个全局标志。

因为CMake内部要查询**`BUILD_SHARED_LIBS`**全局变量，

所以**`add_library`**命令可以在不传递**`STATIC/SHARED/OBJECT`**参数的情况下调用；

如果为**`false`**或未定义，将生成一个静态库。



==else() 和 endif() 后面接括号==



# 展示选项

在使用-D前需要先使用

`option(USE_LIBRARY "Compile sources into a library" OFF)`

命令行选项：**`-D`**

例如：cmake -D USE_LIBRARY=ON ..

option的可接收参数：

`option(<option_variable> "help string" [initial value])`

+ `<option_variable>`表示该选项的变量的名称。
+ `"help string"`记录选项的字符串，在CMake的终端或图形用户界面中可见。
+ `[initial value]`选项的默认值，可以是`ON`或`OFF`。



cmake_dependent_option()用预定义依赖于其他选项的选项

前提是include(CMkaeDependentOption)

CMake有适当的机制，通过包含模块来扩展其语法和功能，这些模块要么是CMake自带的，要么是定制的。本例中，包含了一个名为`CMakeDependentOption`的模块。如果没有`include`这个模块，`cmake_dependent_option()`命令将不可用。

基本形式：

```cmake
cmake_dependent_option(<option> "<help_text>" <value> <depends> <force>)
```

当depends均有效的时候 option被设置成默认值value，并且用户可见

当无效的时候，被设置成force，并且对用户不可见

depends的写法：用双引号括起来的一系列变量值，分号隔开

“USE_BAR;NOT USE_ZOT” 当USE_BAR == Y 并且 USE_ZOT == N，depends有效



list()用于指定一个变量为列表例如：

list(_source Message.hpp Message.cpp)

set()用于直接指定一个变量

option()用于指定一个用户可定义的变量



# 选择编译器

1. CMake把语言的编译器存储在

    `CMAKE_<LANG>_COMPILER`里面，\<LANG>可以是CXX C Fortran等等

    可以使用-D来设置：

    `$ cmake -D CMAKE_CXX_COMPILER=clang++ ..`

    可以通过导出环境变量CXX CC FC。

    `$ env CXX=clang++ cmake ..`

2. 如何找到可用的编译器和编译器标志？

    CMake提供的--system-information标志，它把关于系统的所有信息转存到屏幕或者文件中。

    例如：

    `cmake --system-information information.txt`

    

    CMake还提供了额外的变量：

    + `CMAKE_<LANG>_COMPILER_LOADED`:如果为项目启用了语言`<LANG>`，则将设置为`TRUE`。
    + `CMAKE_<LANG>_COMPILER_ID`:编译器标识字符串，编译器供应商所特有。例如，`GCC`用于GNU编译器集合，`AppleClang`用于macOS上的Clang, `MSVC`用于Microsoft Visual Studio编译器。注意，不能保证为所有编译器或语言定义此变量。
    + `CMAKE_COMPILER_IS_GNU<LANG>`:如果语言`<LANG>`是GNU编译器集合的一部分，则将此逻辑变量设置为`TRUE`。注意变量名的`<LANG>`部分遵循GNU约定：C语言为`CC`, C++语言为`CXX`, Fortran语言为`G77`。
    + `CMAKE_<LANG>_COMPILER_VERSION`:此变量包含一个字符串，该字符串给定语言的编译器版本。版本信息在`major[.minor[.patch[.tweak]]]`中给出。但是，对于`CMAKE_<LANG>_COMPILER_ID`，不能保证所有编译器或语言都定义了此变量。



message()，打印一条信息，可选参数：

![image-20221123130733567](C:\Users\DreamLAND\AppData\Roaming\Typora\typora-user-images\image-20221123130733567.png)

status最常用，为普通信息。



# 选择构建类型

CMake可以配置构建类型，例如：Debug、Release等。配置时，可以为Debug或Release构建设置相关的选项或属性，例如：编译器和链接器标志。控制生成构建系统使用的配置变量是`CMAKE_BUILD_TYPE`。该变量默认为空，CMake识别的值为:

1. **Debug**：用于在没有优化的情况下，使用带有调试符号构建库或可执行文件。
2. **Release**：用于构建的优化的库或可执行文件，不包含调试符号。
3. **RelWithDebInfo**：用于构建较少的优化库或可执行文件，包含调试符号。
4. **MinSizeRel**：用于不增加目标代码大小的优化方式，来构建库或可执行文件。

CMake支持符合生成器，可以使用Visual Studio和XCode，同时处理多个配置。使用

CMAKE_CONFIGURATION_TYPES变量可以进行配置：

`cmake .. -G"Visual Studio 12 2017 Win64" -D CMAKE_CONFIGURATION_TYPES="Release;Debug"`

生成一个构建树，之后通过--config标志选择构建二者的哪一个：

`cmake --build . --config Release`



# 设置编译器选项

CMake为调整或扩展编译器标志提供了很大的灵活性，您可以选择下面两种方法:

+ CMake将编译选项视为目标属性。因此，可以根据每个目标设置编译选项，而不需要覆盖CMake默认值。
+ 可以使用`-D`CLI标志直接修改`CMAKE_<LANG>_FLAGS_<CONFIG>`变量。这将影响项目中的所有目标，并覆盖或扩展CMake默认值。



### 方法一：

编译选项可见性的三个级别：PRIVATE INTERFACE PUBLIC

PRIVATE:仅会应用于给定的目标，不会传递给与目标相关的目标

INTERFACE:仅会应用于指定目标，并传递给与目标相关的目标

PUBLIC:应用于指定目标和使用它的目标



使用target_complie_options(<target> <flag> <options>)

options应该是字符串



查看用的编译标志

我们如何验证，这些标志是否按照我们的意图正确使用呢？或者换句话说，如何确定项目在CMake构建时，实际使用了哪些编译标志？一种方法是，使用CMake将额外的参数传递给本地构建工具。本例中会设置环境变量`VERBOSE=1`



### 方法二：

控制编译器标志的第二种方法，不用对`CMakeLists.txt`进行修改。如果想在这个项目中修改`geometry`和`compute-areas`目标的编译器选项，可以使用CMake参数进行配置：

`cmake -D CMAKE_CXX_FLAGS="-fno-exceptions -fno-rtti" ..`

当使用上述CMakeLists.txt运行时，会有叠加：

-- “这将使用`-fno-rtti - fpic - wall - Wextra - wpedantic`配置`geometry`目标，同时使用`-fno exception -fno-rtti - fpic`配置`compute-areas`。”



list(APPEND yy “XXX”)在变量列表yy后面追加一个“XXX”



# 设定语言标准

set_target_properties(XXX PROPERTIES CXX_STANDARD 14 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

* CXX_STANDARD 标准
* CXX_EXTENSIONS 告诉CMake，只启用`ISO C++`标准的编译器标志，而不使用特定编译器的扩展。
* CXX_STANDARD_REQUIRED 指定所选标准的版本。如果这个版本不可用，CMake将停止配置并出现错误。当这个属性被设置为`OFF`时，CMake将寻找下一个标准的最新版本，直到一个合适的标志。这意味着，首先查找`C++14`，然后是`C++11`，然后是`C++98`。（译者注：目前会从`C++20`或`C++17`开始查找）

**TIPS**:*如果语言标准是所有目标共享的全局属性，那么可以将`CMAKE_<LANG>_STANDARD`、`CMAKE_<LANG>_EXTENSIONS`和`CMAKE_<LANG>_STANDARD_REQUIRED`变量设置为相应的值。所有目标上的对应属性都将使用这些设置。*



```none
通过引入编译特性，CMake对语言标准提供了更精细的控制。这些是语言标准引入的特性，比如C++11中的可变参数模板和Lambda表达式，以及C++14中的自动返回类型推断。可以使用target_compile_features()命令要求为特定的目标提供特定的特性，CMake将自动为标准设置正确的编译器标志。也可以让CMake为可选编译器特性，生成兼容头文件。
```



# 控制流

CMake还提供了创建循环的语言工具：`foreach endforeach`和`while-endwhile`。两者都可以与`break`结合使用，以便尽早从循环中跳出。

+ `set_source_files_properties(file PROPERTIES property value)`，它将属性设置为给定文件的传递值。与目标非常相似，文件在CMake中也有属性，允许对构建系统进行非常细粒度的控制。
+ `get_source_file_property(VAR file property)`，检索给定文件所需属性的值，并将其存储在CMake`VAR`变量中。

**NOTE**:*CMake中，列表是用分号分隔的字符串组。列表可以由`list`或`set`命令创建。例如，`set(var a b c d e)`和`list(APPEND a b c d e)`都创建了列表`a;b;c;d;e`。*



`foreach()`的四种使用方式:

+ `foreach(loop_var arg1 arg2 ...)`: 其中提供循环变量和显式项列表。当为`sources_with_lower_optimization`中的项打印编译器标志集时，使用此表单。注意，如果项目列表位于变量中，则必须显式展开它；也就是说，`${sources_with_lower_optimization}`必须作为参数传递。
+ 通过指定一个范围，可以对整数进行循环，例如：`foreach(loop_var range total)`或`foreach(loop_var range start stop [step])`。
+ 对列表值变量的循环，例如：`foreach(loop_var IN LISTS [list1[...]])` 。参数解释为列表，其内容就会自动展开。
+ 对变量的循环，例如：`foreach(loop_var IN ITEMS [item1 [...]])`。参数的内容没有展开。



# 检测操作系统

CMAKE_SYSTEM_NAME就是CMake为目标操作系统定义的变量，字符串

# 平台相关代码

target_compile_definitions指定目标添加宏定义

`CMAKE_HOST_SYSTEM_PROCESSOR`变量是处理器名称

`CMAKE_SIZEOF_VOID_P`为void指针的大小。我们可以在CMake配置时进行查询，以便修改目标或目标编译定义。

除了`CMAKE_HOST_SYSTEM_PROCESSOR`, CMake还定义了`CMAKE_SYSTEM_PROCESSOR`变量。前者包含当前运行的CPU在CMake的名称，而后者将包含当前正在为其构建的CPU的名称。

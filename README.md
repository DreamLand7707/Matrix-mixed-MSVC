# 关于Matrix Doubled的使用注意

此项目目前开发状态为半弃坑

Matrix的元素为纯double

文件结构：

```powershell
├─.cache
│  └─clangd
│      └─index
├─.vscode
├─bin
│  ├─basbin
│  │  └─CMakeFiles
│  │      └─baspar.dir
│  ├─leetcode
│  │  └─CMakeFiles
│  │      └─leetcode.dir
│  ├─testbin
│  │  └─CMakeFiles
│  │      └─cppdebug.dir
│  └─testbinc
│      └─CMakeFiles
│          └─cdebug.dir
├─build
│  ├─.cmake
│  │  └─api
│  │      └─v1
│  │          ├─query
│  │          │  └─client-vscode
│  │          └─reply
│  └─CMakeFiles
│      ├─3.23.2
│      │  ├─CompilerIdC
│      │  │  └─tmp
│      │  └─CompilerIdCXX
│      │      └─tmp
│      └─CMakeTmp
├─Debug
├─include
├─leetcode
├─lib
├─mcfunctions
├─source
├─src
├─test
└─tests
```



矩阵库的功能归结如下：

1. 创建
2. 基本操作（赋值，删除，访问等）
3. 基本计算
4. 迭代器操作

## 创建

...

## 基本操作

...

## 基本计算

...

## 迭代器操作

...



# 如下为新增内容：2022/10/13日次更新

#### 1.

加入了一个matrix成员函数：printcsv

函数原型：

`virtual bool printcsv(const std::string &, int = -1);`

string的引用为输出的文件目录

int为保留小数精度

会以excel表格的结构输出文件，也就是csv格式

示例：

```c++
#include <basic_par.h>
int main(void)
{
    using namespace std;
    drl::matrix A(1.0, 9.0, 3, 3);
    A.printcsv(string("../source/1.csv"), 2);
    return 0;
}
```

会在source文件夹下出现1.csv文件

按照格式打印矩阵



### 2.

完善了trans成员函数（之前应该是落下了还忘记打了TODO）
























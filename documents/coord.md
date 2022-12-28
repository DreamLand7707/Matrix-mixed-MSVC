# 函数绘图

## 宏定义

当UNICODE被定义的时候

**`_TSTRING = std::wstring`**

**`_TOSTRINGSTREAM = std::wostringstream`**

当UNICODE没被定义的时候

**`_TSTRING = std::string`**

**`_TOSTRINGSTREAM = std::ostringstream`**

## C++标准库文件

```c++
#include <algorithm>
#include <cmath>
#include <conio.h>
#include <initializer_list>
#include <iostream>
#include <numeric>
#include <string>
#include <tchar.h>
#include <utility>
#include <vector>
```

## 命名空间

**`namespace drl`**

## 类

#### 一. `drl::plot2_messages::graphstyle_s`

该类的作用是进行绘画样式控制

* public成员：

    ```c++
    COLORREF linecolor;       // 线颜色
    ushort linewidth;         // 线宽度
    linestyle_ linestyle;     // 线形状
    COLORREF pointcolor;      // 点颜色
    ushort pointsize;         // 点大小
    pointstyle_ pointstyle;   // 点的样式
    
    linestyle_ scale_line_style_x;
    linestyle_ scale_line_style_y;
    
    unsigned int num_of_x;        // x轴信息的数量
    unsigned int num_of_y;        // y轴信息的数量
    unsigned int point_density;   // 点密度
    
    unsigned int xnum_density;           // x轴信息的x点坐标的密度
    unsigned int ynum_density;           // y轴信息的y点坐标的密度
    unsigned int x_scaleplace_density;   // x轴信息的x主坐标线的密度
    unsigned int y_scaleplace_density;   // y轴信息的y主坐标线的密度
    
    ushort frame_width;                 // 边框宽度
    ushort scaleplate_width;            // 坐标线的宽
    COLORREF frame_color;               // 边框颜色
    COLORREF scaleplate_color;          // 坐标线的颜色
    COLORREF bkcolor;                   // 背景颜色
    COLORREF colorxtext;                // x轴文字的颜色
    COLORREF colorytext;                // y轴文字的颜色
    COLORREF colortitle;                // title的颜色
    COLORREF colorxnum;                 // x轴坐标值的颜色
    COLORREF colorynum;                 // y轴坐标值的颜色
    COLORREF color_main_x_scaleplace;   // x轴主坐标线的颜色
    COLORREF color_main_y_scaleplace;   // y轴主坐标线的颜色
    _TSTRING lougfont;                  // 字体
    int point_line_width;               // 对于某种样式来说，线宽
    
    int width_window  = 1920;			// 实体窗口宽度
    int height_window = 1080;			// 实体窗口高度
    
    std::vector<double> line_ref_x;		// x轴参考线位置
    std::vector<double> line_ref_y;		// y轴参考线位置
    COLORREF color_line_ref_x;			// x轴参考线的颜色
    COLORREF color_line_ref_y;			// y轴参考线的颜色
    ushort line_ref_x_width;			// x轴参考线的宽度
    ushort line_ref_y_width;			// y轴参考线的宽度
    
    linestyle_ ref_line_style_x;		//x轴参考线的样式
    linestyle_ ref_line_style_y;		//y轴参考线的样式
    ```

    以下是枚举值

    ```c++
    enum class linestyle_
    {
        SOLID      = PS_SOLID,
        DASH       = PS_DASH,
        DOT        = PS_DOT,
        DASHDOT    = PS_DASHDOT,
        DASHDOTDOT = PS_DASHDOTDOT
    };
    enum class pointstyle_
    {
        SOLID       = 0,
        SQUARE      = 1,
        TRIA        = 2,
        CIRCLE      = 3,
        CROSS       = 4,
        CIRCLECROSS = 5,
        SQUARECROSS = 6,
        TRIACROSS   = 7,
        Star        = 8,
        Nazi        = 9,
    };
    ```

#### 二. `drl::plot2_messages::range_para`

该类的作用是进行绘画范围及范围显示精度控制

```c++
public:
    std::pair<double, double> x_minmax;			//绘图范围
    std::pair<double, double> y_minmax;
    bool xdefaulted = true;						//是否自动适配
    bool ydefaulted = true;
    double x_ratio;								//缩放倍数
    double y_ratio;
    int pres;   								//精度
    decltype(std::ios::floatfield) output;		//显示的模式，设置方式同cout
```

#### 三. `drl::plot2_messages::act_para`

该类的作用是对绘画进行启用设置

```c++
public:
    bool title;          //启用标题？
    bool axis;           //启用坐标轴？
    bool mess_x;         //启用x坐标轴文本？
    bool mess_y;         //启用y坐标轴文本？
    bool x_;             //启用x坐标轴线？
    bool y_;             //启用y坐标轴线？
    bool x_num;          //启用x坐标轴数？
    bool y_num;          //启用y坐标轴数？
    bool point_;         //启用描点？
    bool draw_line_;     //启用画线？
    bool clear_all;      //是否清除全部？
    bool x_main_scale;   //是否启用x主坐标线
    bool y_main_scale;   //是否启用y主坐标线
    bool clip;           //是否启用裁剪
    bool clip_detail;    //裁剪细节
    bool polar;          // TODO启用极坐标
    bool part_graph;     //部分绘图
    bool x_ref_line;	 //x参考线
    bool y_ref_line;	 //y参考线
```

#### 四. `drl::plot2_messages::image_message`

该类的作用设置显示信息

```c++
public:
    _TSTRING x_mess;		//x轴信息
    _TSTRING y_mess;		//y轴信息
    _TSTRING title;			//大标题信息
```

下面是一些预定义类

```c++
extern const plot2_messages::graphstyle_s default_graphstyle;
//默认绘图模式，theme light
extern const plot2_messages::range_para default_range_para;
//默认范围模式
extern const plot2_messages::act_para default_act_para;
//默认启用模式
extern const plot2_messages::image_message default_image_message;
//默认坐标轴标题信息
extern const plot2_messages::graphstyle_s darkmode_graphstyle;
//默认绘图模式，dark theme
extern const std::pair<int, int> basic_wh;
//图片信息，有效占比
```

## 函数

#### 一. `pict_curve_xy`

1. 作用

    根据x，y的对应的值描点连线。

2. 参数

    * 参数1：image的指针，表示要画入的image，可以是NULL，但必须保证窗口已经创建。

    * 参数2：一个pair，表示x的数值的区间。

        pair的创建方式可以使用标准库函数：std::make_pair(_arg1_,_arg2_);

        而参数需要的pair是一组指针/迭代器，表示x的范围。

    ```c++
    double a[10] = {1,2,3,4,5,6,7,8,9,10};
    auto _x_ = make_pair(a,a+10);//_x_就是一个pair
    ```

    * 参数3：一个pair，表示y的数值区间。

        同样可以使用make_pair创建。

        但是需要注意的是表示的区间的长度必须和x相同。

        ```c++
        double b[10] = {1,4,7,2,5,8,3,6,9};
        double b_[11] = {1,4,7,2,5,8,3,6,9,11};
        auto _y_ = make_pair(b,b+10);//这个是可以使用的，长度为10
        auto _y1_ = make_pair(b_,b_+11);//这个不可以使用，因为它的长度和_x_不同
        ```

    * 参数4-7：graph_style range_para image_message act_para 类型参数，决定绘图的方式，样式。

        他们都有自己的默认参数，也可以自定义自己的参数。

    * 参数8：bool ucover

        表示是否以非覆盖的方式进行画图。

        非覆盖相当于：

        clear_all = false;

        title = false;

        axis = false;

        mess_x = false;

        mess_y = false;

        x_ = false;

        y_ = false;

        x_num = false;

        y_num = false;

        x_main_scale = false;

        y_main_scale = false;

        x_ref_line = false;

        y_ref_line = false;

        其余参数保持不变。

3. 
























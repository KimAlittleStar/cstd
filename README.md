# cstd
使用C语言实现C++&lt;std>中的几种数据容器
使用过C++ <STD> 库的猿友们应该都觉得 C++中那些已经实现好了的数据类型封装使用让人很是舒服;

例如 vector 支持自动扩充数组，支持模板类，任何数据类型都可以 简单的管理，如果在C语言中，我们就

需要预先声明数组或者动态声明指针，最最重要的是，同样的事情我们有可能需要做很多遍，那么有没有什么

方式可以让C语言也可以实现类似C++中数据类型的功能呢？

答案当然是可以的，不仅可以实现自动管理数组，同时还支持代码膨胀，也就是支持自定义的数据类型

（无限嵌套哦）；

笔者我就想编写这么一个系列，一来是记录我自己“造轮子”的过程，二来是为了分享，让大家都可以使用，

免得大家重复造轮子；

 

<h3>编码风格（约定|声明）</h3> 

1.每一个数据类型模块文件命名都是以 c****.c/.h命名；例如vector模块 那么文件名为：cvector.c/.h

2.每一个模块都会有单独的文件前缀；例如 在cvector模块中，所有函数前缀统一为VCT（VeCTor）

3.每个模板函数都会在前标注其功能以及注意事项；

4.推荐使用VSCode进行编辑编码； 

5.由于其特性，请使用支持C99以上的编译器编译； 

 

<h3>实现原理</h3>

  <h4>宏定义实现代码膨胀；</h4>

    大家都知道宏定义的作用就是在使用宏的位置展开宏；并且不检查类型等直接使用；（Eg1）

    同时宏还可以使用##拼接符和#字符化符号来完成编译器基本的字符处理（等效于插入代码）；（Eg2）

    我们的代码膨胀功能的实现就是基于这个特性来完成的；

    typedef struct 实现数据结构的实现；

    这个应该是个入门知识，我就不过多赘述；

 

Eg.1

    1 #define PI 3.14

    double getCircleArea(double radius)
    4 {
    5     // return radius * radius * 3.14
    6     return radius*radius*PI;
    }   // （Eg1）<p></code>
 

   Eg.2
   
    1 // Eg .2
    2 #include<stdio.h>
    3 #define PRINTF_NUM(NUM) printf("%s = %d",#NUM,NUM)
    4 
    5 void main(void)
    6 {
    7     int number = 10;
    8 
    9     // printf("%s = %d","number",number);
    10     PRINTF_NUM(number);
    11 }
    
 ## 目录

### 1.[引言](https://www.cnblogs.com/kimalittlestar/p/11703214.html)

### 2.1 [C语言_实现简单基础的vector](https://www.cnblogs.com/kimalittlestar/p/11704083.html)

### 2.2 [C语言_实现数据容器vector(排序功能)](https://www.cnblogs.com/kimalittlestar/p/11716252.html)

### 3.1 [C语言_实现AVL平衡二叉树](https://www.cnblogs.com/kimalittlestar/p/11739050.html)

### 3.2 [C语言_实现数据容器set(基础版)]()

### 4 [C语言_实现简单基础的map]()
 

版权所有； 未经许可，不得转载； 如需转载，请联系 kim_alittlestar@qq.com；

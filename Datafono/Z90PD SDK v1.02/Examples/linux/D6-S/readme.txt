<1> libLinux.a是静态库，libLinux.so是动态库,dclinux.h是头文件，exam4442.c是测试的例子。

<2>静态库的编译方法：cc exam4442.c libLinux.a -o exam4442.o     就可以生成exam4442.o

<3>动态库的编译方法：首先要把库libLinux.so拷贝到一个系统目录，
       比如说/lib,然后执行ldconfig 
                     
       #cp libLinux.so /lib/libLinux.so
                     
       #ldconfig
                     
       这样命令执行后就共享了动态库，下面执行编译命令：
                     
       #cc -o exam4442 exam4442.c /lib/libLinux.so


<4>执行例子：./exam4442.o /dev/ttyS0                  对连接在串口一的读写器进行操作
123
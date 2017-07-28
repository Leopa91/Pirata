<1>libdcd6.a是静态库， libdcd6linux.so是动态库,dclinux.h是头文件，demo.c是测试的例子。
<2>静态库的编译方法：gcc demo.c librf.a -o demo -lrt    就可以生成demo
<3>动态库的编译方法：首先要把库libdcd6linux.so拷贝到一个系统目录，比如说/lib,然后执行ldconfig 
                     #cp libdcd6linux.so /lib/
                     #ldconfig
                     这样命令执行后就共享了动态库，下面执行编译命令：
                     #gcc -o demo demo.c -L. -ldcd6linux -lrt

<4>执行例子：./demo    

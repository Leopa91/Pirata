<1> libLinux.a�Ǿ�̬�⣬libLinux.so�Ƕ�̬��,dclinux.h��ͷ�ļ���exam4442.c�ǲ��Ե����ӡ�

<2>��̬��ı��뷽����cc exam4442.c libLinux.a -o exam4442.o     �Ϳ�������exam4442.o

<3>��̬��ı��뷽��������Ҫ�ѿ�libLinux.so������һ��ϵͳĿ¼��
       ����˵/lib,Ȼ��ִ��ldconfig 
                     
       #cp libLinux.so /lib/libLinux.so
                     
       #ldconfig
                     
       ��������ִ�к�͹����˶�̬�⣬����ִ�б������
                     
       #cc -o exam4442 exam4442.c /lib/libLinux.so


<4>ִ�����ӣ�./exam4442.o /dev/ttyS0                  �������ڴ���һ�Ķ�д�����в���
123
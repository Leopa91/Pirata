<1>libdcd6.a�Ǿ�̬�⣬ libdcd6linux.so�Ƕ�̬��,dclinux.h��ͷ�ļ���demo.c�ǲ��Ե����ӡ�
<2>��̬��ı��뷽����gcc demo.c librf.a -o demo -lrt    �Ϳ�������demo
<3>��̬��ı��뷽��������Ҫ�ѿ�libdcd6linux.so������һ��ϵͳĿ¼������˵/lib,Ȼ��ִ��ldconfig 
                     #cp libdcd6linux.so /lib/
                     #ldconfig
                     ��������ִ�к�͹����˶�̬�⣬����ִ�б������
                     #gcc -o demo demo.c -L. -ldcd6linux -lrt

<4>ִ�����ӣ�./demo    

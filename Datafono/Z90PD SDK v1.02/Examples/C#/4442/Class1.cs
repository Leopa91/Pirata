using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
namespace D6
{
    class Class1
    {

        //����APIλ��.
        [DllImport("dcic32.dll")]
        //��ʼ���˿�
        public static extern int IC_InitComm(int Port);

        [DllImport("dcic32.dll")]
        //�رն˿�
        public static extern short IC_ExitComm(int icdev);

        [DllImport("dcic32.dll")]
        //���µ�(Ҫ�������������ܼ�������)
        public static extern short IC_Down(int icdev);

        [DllImport("dcic32.dll")]
        //��ʼ������
        public static extern short IC_InitType(int icdev, int cardType);

        [DllImport("dcic32.dll")]
        //�ж������Ƿ�ɹ�,<0 ,���Ӳ��ɹ�.0���Զ�д,1���ӳɹ�,����û�忨.
        public static extern short IC_Status(int icdev);
        [DllImport("dcic32.dll")]
        //���ԭʼ����(С��0Ϊ����ȷ)
        public static extern short IC_CheckPass_4442hex(int icdev, string Password);
        [DllImport("dcic32.dll")]
        //��������(0Ϊ���ĳɹ�)
        public static extern short IC_ChangePass_4442hex(int icdev, string Password);
        [DllImport("dcic32.dll")]
        //�ڹ̶���λ��д��̶����ȵ�����
        public static extern short IC_Write(int icdev, int offset, int Length, string Databuffer);
        [DllImport("dcic32.dll")]
        //�ڹ̶���λ�ö����̶����ȵ�����
       // public static extern short IC_Read(int icdev, int offset, int l, byte[] Databuffer);
        public static extern short IC_Read(int icdev, int offset, int l,StringBuilder data1);

        [DllImport("dcic32.dll")]
        //��������
        public static extern short IC_DevBeep(int icdev, int intime);
    }
}

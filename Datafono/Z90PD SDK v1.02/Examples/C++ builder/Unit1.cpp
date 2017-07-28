//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define MAX_BUFFER 260
HANDLE g_hDLL;                                    //�����豸���
short g_status;                                   //����״̬

/* ��������ԭ�Ͳ��Ҷ��庯��ָ�룬���������ɲο�MSDN��
   Using Run-Time Dynamic Linking���� */
typedef HANDLE (__stdcall * FUNC1)(int);
FUNC1 IC_InitComm;
typedef short (__stdcall * FUNC2)(HANDLE);
FUNC2 IC_ExitComm;
typedef short (__stdcall * FUNC3)(HANDLE, int);
FUNC3 IC_InitType;
typedef short (__stdcall * FUNC4)(HANDLE);
FUNC4 IC_Status;
typedef short (__stdcall * FUNC5)(HANDLE);
FUNC5 IC_Down;
typedef short (__stdcall * FUNC6)(HANDLE, PUCHAR, PUCHAR);
FUNC6 IC_CpuReset;
typedef short (__stdcall * FUNC7)(HANDLE, UCHAR, PUCHAR, PUCHAR, PUCHAR);
FUNC7 IC_CpuApdu;
/* -- */

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    ListBox1->AddItem(
        "--------------------------------------------------------------------",
        NULL
        );

    g_hDLL = IC_InitComm(1);                      //��ʼ���˿ڣ�����Ϊ1��ʾCOM2
    if((short)g_hDLL < 0)
    {
        ListBox1->AddItem("IC_InitComm ʧ��", NULL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_InitComm �ɹ�", NULL);
    }

    g_status = IC_InitType(g_hDLL, 12);           //��ʼ����д����Ҫ�����Ŀ�Ƭ-
    if(g_status != 0)                             //���ͣ�12ΪCPU��������ɲ�-
    {                                             //���ֲᡣ
        ListBox1->AddItem("IC_InitType ʧ��", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_InitType �ɹ�", NULL);
    }

    g_status = IC_Status(g_hDLL);                 //��ö�д��״̬������������-
    if(g_status < 0)                              //��д�������Ƿ���������Ƭ��-
    {                                             //���Ѿ����롣
        ListBox1->AddItem("IC_Status ʧ��", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else if(g_status == 0)
    {
        ListBox1->AddItem("IC_Status �ɹ����п�", NULL);
    }
    else
    {
        ListBox1->AddItem("IC_Status �ɹ����޿�", NULL);
    }

    UCHAR rlen;                                   //���巵�س��ȣ��ֽڱ�ʾ
    UCHAR rdata[MAX_BUFFER] = {0};                //���巵�����ݻ���
    g_status = IC_CpuReset(g_hDLL, &rlen, rdata);
    if(g_status != 0)
    {
        ListBox1->AddItem("IC_CpuReset ʧ��", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_CpuReset �ɹ�", NULL);
    }

    UCHAR slen = 5;                               //���巢�ͳ��ȣ��ֽڱ�ʾ
    UCHAR sdata[MAX_BUFFER] = {0};                //���巢�����ݻ���
    sdata[0] = 0x00;
    sdata[1] = 0x84;
    sdata[2] = 0x00;
    sdata[3] = 0x00;
    sdata[4] = 0x08;
    g_status = IC_CpuApdu(g_hDLL, slen, sdata, &rlen, rdata);  //CPU�����ݽ���
    if(g_status != 0)
    {
        ListBox1->AddItem("IC_CpuApdu ʧ��", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_CpuApdu �ɹ�", NULL);
    }

    g_status = IC_Down(g_hDLL);                   //�Կ��µ�
    if(g_status != 0)
    {
        ListBox1->AddItem("IC_Down ʧ��", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_Down �ɹ�", NULL);
    }

    g_status = IC_ExitComm(g_hDLL);               //�رն˿�
    if(g_status < 0)
    {
        ListBox1->AddItem("IC_ExitComm ʧ��", NULL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_ExitComm �ɹ�", NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    /* �����д����̬�Ⲣ�һ�ú���ָ�� */
    g_hDLL = LoadLibrary("dcic32.dll");           //ȷ����̬���ڿɲ�ѯĿ¼
    IC_InitComm = (FUNC1)GetProcAddress(g_hDLL, "IC_InitComm");
    IC_ExitComm = (FUNC2)GetProcAddress(g_hDLL, "IC_ExitComm");
    IC_InitType = (FUNC3)GetProcAddress(g_hDLL, "IC_InitType");
    IC_Status = (FUNC4)GetProcAddress(g_hDLL, "IC_Status");
    IC_Down = (FUNC5)GetProcAddress(g_hDLL, "IC_Down");
    IC_CpuReset = (FUNC6)GetProcAddress(g_hDLL, "IC_CpuReset");
    IC_CpuApdu = (FUNC7)GetProcAddress(g_hDLL, "IC_CpuApdu");
    /* -- */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    FreeLibrary(g_hDLL);                          //�ͷŶ�̬��
}
//---------------------------------------------------------------------------

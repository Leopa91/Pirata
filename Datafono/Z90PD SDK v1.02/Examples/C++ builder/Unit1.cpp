//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#define MAX_BUFFER 260
HANDLE g_hDLL;                                    //定义设备句柄
short g_status;                                   //定义状态

/* 声明函数原型并且定义函数指针，声明方法可参考MSDN中
   Using Run-Time Dynamic Linking部分 */
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

    g_hDLL = IC_InitComm(1);                      //初始化端口，参数为1表示COM2
    if((short)g_hDLL < 0)
    {
        ListBox1->AddItem("IC_InitComm 失败", NULL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_InitComm 成功", NULL);
    }

    g_status = IC_InitType(g_hDLL, 12);           //初始化读写器将要操作的卡片-
    if(g_status != 0)                             //类型，12为CPU卡，具体可参-
    {                                             //照手册。
        ListBox1->AddItem("IC_InitType 失败", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_InitType 成功", NULL);
    }

    g_status = IC_Status(g_hDLL);                 //获得读写器状态，可用来测试-
    if(g_status < 0)                              //读写器连接是否正常，卡片是-
    {                                             //否已经插入。
        ListBox1->AddItem("IC_Status 失败", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else if(g_status == 0)
    {
        ListBox1->AddItem("IC_Status 成功，有卡", NULL);
    }
    else
    {
        ListBox1->AddItem("IC_Status 成功，无卡", NULL);
    }

    UCHAR rlen;                                   //定义返回长度，字节表示
    UCHAR rdata[MAX_BUFFER] = {0};                //定义返回数据缓冲
    g_status = IC_CpuReset(g_hDLL, &rlen, rdata);
    if(g_status != 0)
    {
        ListBox1->AddItem("IC_CpuReset 失败", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_CpuReset 成功", NULL);
    }

    UCHAR slen = 5;                               //定义发送长度，字节表示
    UCHAR sdata[MAX_BUFFER] = {0};                //定义发送数据缓冲
    sdata[0] = 0x00;
    sdata[1] = 0x84;
    sdata[2] = 0x00;
    sdata[3] = 0x00;
    sdata[4] = 0x08;
    g_status = IC_CpuApdu(g_hDLL, slen, sdata, &rlen, rdata);  //CPU卡数据交换
    if(g_status != 0)
    {
        ListBox1->AddItem("IC_CpuApdu 失败", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_CpuApdu 成功", NULL);
    }

    g_status = IC_Down(g_hDLL);                   //对卡下电
    if(g_status != 0)
    {
        ListBox1->AddItem("IC_Down 失败", NULL);
        IC_ExitComm(g_hDLL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_Down 成功", NULL);
    }

    g_status = IC_ExitComm(g_hDLL);               //关闭端口
    if(g_status < 0)
    {
        ListBox1->AddItem("IC_ExitComm 失败", NULL);
        return;
    }
    else
    {
        ListBox1->AddItem("IC_ExitComm 成功", NULL);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    /* 载入读写器动态库并且获得函数指针 */
    g_hDLL = LoadLibrary("dcic32.dll");           //确保动态库在可查询目录
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
    FreeLibrary(g_hDLL);                          //释放动态库
}
//---------------------------------------------------------------------------

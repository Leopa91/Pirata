using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace t6_cpu
{
    public partial class Form1 : Form
    {
        #region  T6接口函数
        [DllImport("dcic32.dll")]        //初始化端口
        public static extern int IC_InitComm(int Port);

        [DllImport("dcic32.dll")]        //关闭端口
        public static extern short IC_ExitComm(int icdev);

        [DllImport("dcic32.dll")]        //卡下电(要重新审核密码才能继续操作)
        public static extern short IC_Down(int icdev);

        [DllImport("dcic32.dll")]        //初始化卡型
        public static extern short IC_InitType(int icdev, int cardType);
        
        [DllImport("dcic32.dll")]        //判断连接是否成功,<0 ,连接不成功.0可以读写,1连接成功,但是没插卡.
        public static extern short IC_Status(int icdev);
        [DllImport("dcic32.dll")]        //检查原始密码(小于0为不正确)
        public static extern short IC_CheckPass_4442hex(int icdev, string Password);
        [DllImport("dcic32.dll")]        //更改密码(0为更改成功)
        public static extern short IC_ChangePass_4442hex(int icdev, string Password);
        [DllImport("dcic32.dll")]        //在固定的位置写入固定长度的数据
        public static extern short IC_Write(int icdev, int offset, int Length, string Databuffer);
        [DllImport("dcic32.dll")]        //在固定的位置读出固定长度的数据
        public static extern short IC_Read(int icdev, int offset, int l, byte[] Databuffer);
        [DllImport("dcic32.dll")]        //发出声音
        public static extern short IC_DevBeep(int icdev, int intime);
        //cpu卡函数
        ////[DllImport("./dcic32.dll")] //cpu卡上电复位
        ////public static extern short IC_CpuReset(int icdev, ref short rlen, StringBuilder rbuff);
        ////[DllImport("./dcic32.dll")] //cpu卡上电复位
        ////public static extern short IC_CpuReset_Hex(int icdev, ref short rlen, StringBuilder rbuff);

        ////[DllImport("./dcic32.dll")]
        ////public static extern short IC_CpuReset(int icdev, [Out] byte[] rlen, [Out] byte[] rbuff);
        ////[DllImport("./dcic32.dll")]
        ////public static extern short IC_CpuReset_Hex(int icdev, [Out] byte[] rlen, [Out] byte[] rbuff);
        [DllImport("dcic32.dll")]
        public static extern short IC_CpuReset(int icdev, ref byte rlen, ref char rbuff);
        [DllImport("dcic32.dll")]
        public static extern short IC_CpuReset_Hex(int icdev, ref byte rlen, StringBuilder rbuff);
        

        [DllImport("dcic32.dll")]//设置cpu参数
        public static extern short IC_SetCpuPara(int icdev,short  cputype,short  cpupro,short  cpuetu);
        [DllImport("dcic32.dll")] //cpu卡信息交换协议
        public static extern short IC_CpuApdu(int icdev, short  slen, string sbuff,ref short rlen,ref string rbuff);   
        [DllImport("dcic32.dll")] //cpu卡信息交换协议
        public static extern short IC_CpuApdu_Hex(int icdev, short slen, string sbuff, ref short rlen, StringBuilder rbuff);   
        
        #endregion

        public int icdev = -1;
        public short st = -1;
        public short  TypeCpu=0;

        public Form1()
        {
            InitializeComponent();          

        }

        private void button1_Click(object sender, EventArgs e)
        {
            icdev = IC_InitComm(100); //初始化usb  
            if (icdev < 0)
            {
                MessageBox.Show("打开端口失败！");
                return;
            }
            st = IC_DevBeep(icdev,10);
            MessageBox.Show("打开端口成功！");

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            TypeCpu = 12;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            TypeCpu = 13;
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            TypeCpu = 14;
        }

        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {
            TypeCpu = 15;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (textBox1.Text.Trim()==null||textBox1.Text.Trim ()==""|| textBox2 .Text .Trim()==null || textBox2 .Text .Trim()=="")
            {
              MessageBox.Show ("请输入cpu设置参数");
              this.textBox1.Focus();
              return;
            }
            string s1 = textBox1.Text;
            string s2 = textBox2.Text;
           
            st = IC_SetCpuPara(icdev, Convert.ToInt16(s1), TypeCpu, Convert.ToInt16(s2));
            if (st != 0)
            {
                MessageBox.Show("设置cpu参数失败！");
                return;
            }
            MessageBox.Show("设置cpu参数成功");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            byte rlen = 0;
            //string rbuff = "";
            StringBuilder rbuff = new StringBuilder(); 
            st = IC_InitType(icdev,TypeCpu );
            if (st != 0)
            {
                MessageBox.Show("设置卡座参数失败！");
                return;
            }
            //st = IC_CpuReset(icdev, ref rlen, rbuff);
            ////st = IC_CpuReset_Hex(icdev, ref rlen, rbuff);            
            ////byte[] offlen = new byte[64];
            ////byte[] offbuff = new byte[64];
            ////st = IC_CpuReset_Hex(icdev, offlen, offbuff);
            byte crlen = 1;
            //char[] recbuff = new char[32];
            StringBuilder rbuffer = new StringBuilder(1024);
            st = IC_CpuReset_Hex(icdev, ref rlen, rbuffer); 

            if (st != 0)
            {
                MessageBox.Show("卡片复位失败！");
                return;
            }
            textBox3.Text = rbuffer.ToString();

        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (textBox4.Text.Trim() == ""||textBox4 .Text.Trim ()==null)
            {
                MessageBox.Show("请输入命令参数！");
                this.textBox4.Focus ();
                return;
            }
            short rlen, slen;
            //string rbuffer = "";
            StringBuilder rbuffer = new StringBuilder(); 
            rlen = 0;
            string sdata = textBox4.Text;
            slen = (short )(sdata.Length/2);
            st = IC_CpuApdu_Hex(icdev,slen,sdata ,ref rlen,rbuffer);
            if (st != 0)
            {
                MessageBox.Show("发送命令失败！");
                return;
            }
            textBox5.Text = rbuffer.ToString ();

        }

        private void button6_Click(object sender, EventArgs e)
        {
            st = IC_Down(icdev);
            if (st != 0)
            {
                MessageBox.Show("卡下电失败！");
                return;
            }
            MessageBox.Show("卡下电成功！");
            return;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (icdev > 0)
            {
                st = IC_ExitComm(icdev );
            }
            this.Close();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

            radioButton1.Checked = true;
            TypeCpu = 12;
            this.textBox3.ReadOnly = true;
            this.textBox5.ReadOnly = true;

        }
    }
}
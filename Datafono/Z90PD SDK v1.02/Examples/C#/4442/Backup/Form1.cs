using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace D6
{
    public partial class Form1 : Form
    {

        int icdev = -1;
        short st = -1;

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            icdev = Class1.IC_InitComm(100);
            if (icdev < 0)
            {
                listBox1.Items.Add(" 打开端口失败");
                return;
            }
            //listBox1.Items.Add(" 打开端口成功");
            st = Class1.IC_DevBeep(icdev ,10);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            st = Class1.IC_InitType(icdev , 16);
            if (st != 0)
            {
                MessageBox.Show("IC_InitType Error");
                return;
            }

            st = Class1.IC_Status(icdev);
            if (st == 1)
            {
                MessageBox.Show("NO card");
                return;
            }
            if (st != 0)
            {
                MessageBox.Show("IC_Status Error");
                return;
            }
            StringBuilder databuff = new StringBuilder();
            st = Class1.IC_Read(icdev,0,16,databuff );
            if (st != 0)
            {
                listBox1.Items.Add("读卡失败");
                return;            
            }
            listBox1.Items.Add("读卡成功，数据：" +databuff );

            st = Class1.IC_CheckPass_4442hex(icdev ,"FFFFFF");
            if (st != 0)
            {
                listBox1.Items.Add("核对密码失败");
                return;
            }
            listBox1.Items.Add("核对密码成功" );
            st = Class1.IC_Write(icdev, 30, 10, "1234567890");
            if (st != 0)
            {
                MessageBox.Show("IC_Write Error");
                return;
            }

            StringBuilder data = new StringBuilder();
            st = Class1.IC_Read(icdev, 30, 10, data);
            if (st != 0)
            {
                MessageBox.Show("IC_Read Error");
                return;
            }
            listBox1.Items.Add("读卡成功，数据：" + data);

            st = Class1.IC_Write(icdev, 30, 10, "asdfg");
            if (st != 0)
            {
                MessageBox.Show("IC_Write Error");
                return;
            }

            StringBuilder data2 = new StringBuilder();
            st = Class1.IC_Read(icdev, 30, 10, data2);
            if (st != 0)
            {
                MessageBox.Show("IC_Read Error");
                return;
            }
            listBox1.Items.Add("读卡成功，数据：" + data2);

            st = Class1.IC_ChangePass_4442hex(icdev,"FFFFFF");
            if (st != 0)
            {
                MessageBox.Show(" 修改密码失败");
                return;
            }
            listBox1.Items.Add("修改密码成功");
              
        }

        private void button3_Click(object sender, EventArgs e)
        {
            st = Class1.IC_ExitComm(icdev );
            this.Close();

        }
    }
}
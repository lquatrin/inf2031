using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using System.Runtime.InteropServices;

namespace MyClassCS
{

  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }
      
    [DllImport("..\\..\\..\\Release\\MyClassCppDLL.dll", CallingConvention = CallingConvention.Cdecl)]
    public static extern double sumTwo(double a, double b);

    private void button1_Click(object sender, EventArgs e)
    {
      label1.Text = sumTwo(10,14).ToString();
    }

    private void label1_Click(object sender, EventArgs e)
    {

    }

  }
}

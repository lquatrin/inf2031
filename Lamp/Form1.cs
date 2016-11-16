using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using Emgu.CV;
using Emgu.Util;

namespace Lamp
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    private void Form1_Load(object sender, EventArgs e)
    {

    }

    private void DrawIt()
    {
      System.Drawing.Graphics graphics = this.CreateGraphics();
      System.Drawing.Rectangle rectangle = new System.Drawing.Rectangle(
          50, 100, 150, 150);
      graphics.DrawEllipse(System.Drawing.Pens.Black, rectangle);
      graphics.DrawRectangle(System.Drawing.Pens.Red, rectangle);

      /*
      Graphics g;
      // Sets g to a graphics object representing the drawing surface of the
      // control or form g is a member of.
      g = this.CreateGraphics(); 
      Bitmap myBitmap = new Bitmap(@"C:\Documents and 
        Settings\Joe\Pics\myPic.bmp");
      Graphics g = Graphics.FromImage(myBitmap);
      */
    }

    private void button1_Click_1(object sender, EventArgs e)
    {

      DrawIt();

      OpenFileDialog open = new OpenFileDialog();
      if (open.ShowDialog() == System.Windows.Forms.DialogResult.OK)
      {
        Image img = Image.FromFile(open.FileName);
        pictureBox1.Image = img;

      }
    }
  }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lamp
{
  static class Program
  {
    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main()
    {
      AlgLAMP.Test();

      double[,] d = new double[10, 3] { {1,2,3}, {3,2,1}, {4,5,6}, {2,3,4},
           {4,3,2}, {6,8,9}, {2,4,6}, {1,9,5}, {1,3,9}, {9,8,7} };

      int[] idx = new int[3] { 1, 5, 9 };

      double[,] arr_ys = new double[3, 2] { { 4, 9 }, { 1, 1 }, { 9, 6 } };

      Emgu.CV.Matrix<double> X = new Emgu.CV.Matrix<double>(d);

      //Application.EnableVisualStyles();
      //Application.SetCompatibleTextRenderingDefault(false);
      //Application.Run(new Form1());
    }
  }
}

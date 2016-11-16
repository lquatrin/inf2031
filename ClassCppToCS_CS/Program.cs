using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using ClassCppToCS_Wrapper;

namespace ClassCppToCS_CS
{
  static class Program
  {
    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    [STAThread]
    static void Main()
    {
      int noElements = 1000;
      int[] myArray = new int[noElements];

      for (int i = 0; i < noElements; i++)
      {
        myArray[i] = i * 10;
      }

      unsafe
      {
        fixed (int* pmyArray = &myArray[0])
        {
          ClassCppToCS_Wrapper.CppWrapperClass controlCpp = new ClassCppToCS_Wrapper.CppWrapperClass(pmyArray, noElements);
          controlCpp.GetSum();
          double sumOfArray = controlCpp.sum;
          Console.WriteLine(sumOfArray.ToString());
        }

      }

      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      Application.Run(new Form1());
    }
  }
}

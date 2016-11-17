using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using CppWrapper;

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
          CppWrapper.CppLAMPWrapper controlCpp = new CppWrapper.CppLAMPWrapper(pmyArray, noElements);
          controlCpp.GetSum();
          double sumOfArray = controlCpp.sum;
          Console.WriteLine(sumOfArray.ToString());
          controlCpp.testLamp();

          CppWrapper.CppMDSWrapper mds = new CppWrapper.CppMDSWrapper(pmyArray, noElements);
          mds.testMDS();

          CppWrapper.CppHistogramWrapper histo = new CppWrapper.CppHistogramWrapper();
          Console.WriteLine("histograma distancias");
          histo.testHistogram();
        }

      }

      Application.EnableVisualStyles();
      Application.SetCompatibleTextRenderingDefault(false);
      Application.Run(new Form1());
    }
  }
}

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using CppWrapper;
using System.Windows.Forms.DataVisualization.Charting;

namespace ClassCppToCS_CS
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    private void InitializeOpenFileDialog()
    {
      // Set the file dialog to filter for graphics files.
      this.openFileDialog1.Filter =
          "Images (*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|" +
          "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      this.openFileDialog1.Multiselect = true;
      this.openFileDialog1.Title = "My Image Browser";
    }


    private void MDS_Click(object sender, EventArgs e)
    {
      openFileDialog1.Filter =
      "Images (*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|" +
      "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      openFileDialog1.Multiselect = true;
      openFileDialog1.Title = "My Image Browser";
      DialogResult result = openFileDialog1.ShowDialog();
      List<string> paths = new List<string>();
      if (result == DialogResult.OK) // Test result.
      {

        CppWrapper.CppHistogramWrapper histo = new CppWrapper.CppHistogramWrapper();
   
        
        for (int k = 0; k < 3; k++)
        {
          histo.Clear();
          paths.Clear();
          int counter = 0;
          foreach (String file in openFileDialog1.FileNames)
          {
            string files = openFileDialog1.InitialDirectory + file;
            paths.Add(files);
            counter++;
          }


          histo.addPath(paths.ToArray(), k);
          double[,] array = histo.GetDistances();

          Console.Write("matriz de distancias\n");
          for (int i = 0; i < counter; i++)
          {
            for (int j = 0; j < counter; j++)
            {
              Console.Write(" " + array[i, j]);
            }
            Console.Write("\n");
          }

          CppWrapper.CppMDSWrapper mMDS = new CppWrapper.CppMDSWrapper(array, counter);
          double[,] arrayMDS = mMDS.GetMDS();

          //TO DO - refinar!
          Chart chart = new Chart();
          switch (k)
          {
            case 0:
              chart = chart1;
              chart.Series.RemoveAt(0);
              chart.Series.Add("MDS HUE");
              break;
            case 1:
              chart = chart2;
              chart.Series.RemoveAt(0);
              chart.Series.Add("MDS Saturation");
              break;
            case 2:
              chart = chart4;
              chart.Series.RemoveAt(0);
              chart.Series.Add("MDS Values");
              break;
          }
          //chart.ChartAreas[0].Area3DStyle.Enable3D = true;
          chart.ChartAreas[0].AxisX.Minimum = -1;
          chart.ChartAreas[0].AxisX.Maximum = 1;
          for (int i = 0; i < counter; i++)
          {
            string name = paths[i].Split('\\').Last();
            chart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series[0].Points.AddXY(Math.Round(arrayMDS[i, 0], 1), Math.Round(arrayMDS[i, 1], 3));
            chart.Series[0].Points[i].LegendToolTip = name;
            chart.Series[0].Points[i].ToolTip = name + "\n X= " + arrayMDS[i, 0] + " Y = " + arrayMDS[i, 1];

          }
        }
      }
    }
  }
}

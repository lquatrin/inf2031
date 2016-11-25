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
    public CppWrapper.CppInverseProjectionWrapper wrapper_inverse_projection;
    public int current_colorspace_input;

    public Form1()
    {
      InitializeComponent();

      comboBox1.Items.Add("HSV");
      comboBox1.Items.Add("RGB");

      current_colorspace_input = 0;
      comboBox1.SelectedIndex = current_colorspace_input;

      wrapper_inverse_projection = new CppWrapper.CppInverseProjectionWrapper();
      wrapper_inverse_projection.SetInputColorScapeType(0);
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

    private DialogResult OpenFileImageDialog ()
    {
      openFileDialog1.Filter =
      "Images (*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|" +
      "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      openFileDialog1.Multiselect = true;
      openFileDialog1.Title = "My Image Browser";
      return openFileDialog1.ShowDialog();
    }


    private void MDS_Click(object sender, EventArgs e)
    {
      DialogResult result = OpenFileImageDialog();
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

          Console.WriteLine("matriz de distancias\n");
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
            chart.Series[0].Points.AddXY(Math.Round(arrayMDS[i, 0], 3), Math.Round(arrayMDS[i, 1], 3));
            chart.Series[0].Points[i].LegendToolTip = name;
            chart.Series[0].Points[i].ToolTip = name + "\n X= " + arrayMDS[i, 0] + " Y = " + arrayMDS[i, 1];

          }
        }
      }
    }

    private void button1_Click(object sender, EventArgs e)
    {
      /*DialogResult result = OpenFileImageDialog();
      List<string> paths = new List<string>();
      if (result == DialogResult.OK) // Test result.
      {
        CppWrapper.CppHistogramWrapper histo = new CppWrapper.CppHistogramWrapper();
        for (int k = 0; k < 3; k++)
        {
          histo.Clear();
          paths.Clear();
          int counter = 0;
          textBox1.Clear();
          foreach (String file in openFileDialog1.FileNames)
          {
            textBox1.AppendText(file);
            textBox1.AppendText("\n");
            string files = openFileDialog1.InitialDirectory + file;
            paths.Add(files);
            counter++;
          }

          histo.addPath(paths.ToArray(), k);
          double[,] array = histo.GetDistances();

          Console.WriteLine("Distância entre histogramas:");
          for (int i = 0; i < counter; i++)
          {
            for (int j = 0; j < counter; j++)
            {
              Console.Write(" " + array[i, j]);
            }
            Console.Write("\n");
          }


          CppWrapper.CppLAMPWrapper mlamp = new CppWrapper.CppLAMPWrapper(array, counter);*/
          //double[,] arrayMDS = mlamp.GetMDS();

          /*
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
      Console.WriteLine("LAMP");
          */
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {

    }

    private void chart2_Click(object sender, EventArgs e)
    {

    }

    private void button2_Click(object sender, EventArgs e)
    {
      label1.Text = "Start Inverse Projection";
      label1.Update();

      Chart chart;
      int s = 0;
      int number_of_charts = 3;
      
      chart = chart1;
      int n_series = chart.Series.Count();
      int n_points_per_chart = chart.Series[0].Points.Count();
      double[,] arraypoints = new double[number_of_charts * n_points_per_chart, 2];

      List<string> paths = new List<string>();
      int counter = 0;
      foreach (String file in openFileDialog1.FileNames)
      {
        string files = openFileDialog1.InitialDirectory + file;
        paths.Add(files);
        counter++;
      }

      s = 0;
      for (int p = 0; p < n_points_per_chart; p++)
      {
        DataPoint pt = chart.Series[0].Points[p];
        if (!(pt.LegendToolTip == paths[p].Split('\\').Last()))
        {
          throw new System.InvalidOperationException();
        }
        arraypoints[s * n_points_per_chart + p, 0] = pt.XValue;
        arraypoints[s * n_points_per_chart + p, 1] = pt.YValues[0];
      }

      s++;
      chart = chart2;
      for (int p = 0; p < n_points_per_chart; p++)
      {
        DataPoint pt = chart.Series[0].Points[p];
        if (!(pt.LegendToolTip == paths[p].Split('\\').Last()))
        {
          throw new System.InvalidOperationException();
        }
        arraypoints[s * n_points_per_chart + p, 0] = pt.XValue;
        arraypoints[s * n_points_per_chart + p, 1] = pt.YValues[0];
      }


      s++;
      chart = chart4;
      for (int p = 0; p < n_points_per_chart; p++)
      {
        DataPoint pt = chart.Series[0].Points[p];
        if (!(pt.LegendToolTip == paths[p].Split('\\').Last()))
        {
          throw new System.InvalidOperationException();
        }
        arraypoints[s * n_points_per_chart + p, 0] = pt.XValue;
        arraypoints[s * n_points_per_chart + p, 1] = pt.YValues[0];
      }
      
      //Console.Write(number_of_charts);
      //Console.Write(" ");
      //Console.Write(n_points_per_chart);
      //for (int i = 0; i < number_of_charts; i++)
      //{
      //  for (int p = 0; p < n_points_per_chart; p++)
      //  {
      //    Console.WriteLine(arraypoints[i * n_points_per_chart + p, 0] + " " + arraypoints[i * n_points_per_chart + p, 1]);
      //  }
      //}

      double[,] input_point = new double[,] { { -0.17429880797863, 0.124405957758427 }, { 0, 0 }, { 0, 0 } };
     
      
      wrapper_inverse_projection.InverseProjection01(
          number_of_charts, 
          n_points_per_chart, 
          arraypoints, 
          input_point,
          paths.ToArray() 
          );

      label1.Text = "Finished Inverse Projection";
      //pictureBox1.Image = Image.FromFile("result.jpg");
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {

    }

    private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
    {
      if (wrapper_inverse_projection != null)
        wrapper_inverse_projection.SetInputColorScapeType(comboBox1.SelectedIndex);
    }

    private void button3_Click(object sender, EventArgs e)
    {

    }

    private void chart4_Click(object sender, EventArgs e)
    {

    }

    private void label1_Click(object sender, EventArgs e)
    {

    }

    private void Form1_Load(object sender, EventArgs e)
    {

    }
  }
}

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

    private string path_image;

    public Form1()
    {
      path_image = "";
      InitializeComponent();

      current_colorspace_input = 0;

      wrapper_inverse_projection = new CppWrapper.CppInverseProjectionWrapper();
      wrapper_inverse_projection.SetInputColorScapeType(0);

      Chart chart = new Chart();

      chart = chart1;

      chart.Series.Clear();

      chart.Series.Add("Loaded Points");
      chart.Series[0].Tag = "LoadedPoints";
      chart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;

      chart.Series.Add("Input Points");
      chart.Series[1].Tag = "InputPoints";
      chart.Series[1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;

      chart.Series.Add("Reference Points");
      chart.Series[2].Tag = "ReferencePoints";
      chart.Series[2].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
    }

    private void InitializeOpenFileDialog()
    {
      // Set the file dialog to filter for graphics files.
      this.openFileDialog1.Filter =
          "Images (*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|" +
          "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      this.openFileDialog1.Multiselect = true;
      this.openFileDialog1.Title = "My Image Browser";
    }

    private DialogResult OpenFileImageDialog()
    {
      openFileDialog1.Filter =
      "Images (*.BMP;*.JPG;*.GIF;*.PNG)|*.BMP;*.JPG;*.GIF;*.PNG|" +
      "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      openFileDialog1.Multiselect = true;
      openFileDialog1.Title = "My Image Browser";
      return openFileDialog1.ShowDialog();
    }


    private void MDS_Click(object sender, EventArgs e)
    {
      label1.Text = "Start MDS";
      label1.Update();

      DialogResult result = OpenFileImageDialog();
      List<string> paths = new List<string>();
      if (result == DialogResult.OK) // Test result.
      {

        //CppWrapper.CppHistogramWrapper histo = new CppWrapper.CppHistogramWrapper();
        CppWrapper.CppDistPixelWrapper dist = new CppWrapper.CppDistPixelWrapper();

        dist.Clear();
        paths.Clear();
        int counter = 0;
        foreach (String file in openFileDialog1.FileNames)
        {
          Console.WriteLine(file);
          string files = openFileDialog1.InitialDirectory + file;
          paths.Add(files);
          counter++;
        }

        dist.addPath(paths.ToArray(), 0);
        double[,] array = dist.GetDistances();

        CppWrapper.CppMDSWrapper mMDS = new CppWrapper.CppMDSWrapper(array, counter);
        double[,] arrayMDS = mMDS.GetMDS();

        Chart chart = new Chart();
        chart = chart1;
        chart.Series[0].Points.Clear();
        chart.Series[2].Points.Clear();

        for (int i = 0; i < counter; i++)
        {
          string name = paths[i].Split('\\').Last();
          chart.Series[0].Points.AddXY(Math.Round(arrayMDS[i, 0], 5), Math.Round(arrayMDS[i, 1], 5));
          chart.Series[0].Points[i].LegendToolTip = name;
          chart.Series[0].Points[i].Tag = paths[i];
          chart.Series[0].Points[i].ToolTip = name + "\n X= " + arrayMDS[i, 0] + " Y = " + arrayMDS[i, 1];

        }
      }
      label1.Text = "Finished MDS";
      label1.Update();
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


    private void button2_Click(object sender, EventArgs e)
    {
      label1.Text = "Start Inverse Projection";
      label1.Update();
   
      Chart chart = chart1;

      int n_reference_points = chart.Series[0].Points.Count();

      double[,] arraypoints = new double[n_reference_points, 2];

      List<string> paths = new List<string>();
      int counter = 0;
      for (int p = 0; p < n_reference_points; p++)
      {
        DataPoint pt = chart.Series[0].Points[p];
        paths.Add(pt.Tag.ToString());
        counter++;

        arraypoints[p, 0] = pt.XValue;
        arraypoints[p, 1] = pt.YValues[0];
      }

      double[,] input_point = new double[,] { {0,0} };
      
      Chart schart = chart1;
      if (schart.Series[1].Points.Count() > 0)
      {
        input_point[0, 0] = schart.Series[1].Points[0].XValue;
        input_point[0, 1] = schart.Series[1].Points[0].YValues[0];
      }

      wrapper_inverse_projection.InverseProjectionValBased(
          n_reference_points,
          arraypoints,
          input_point,
          paths.ToArray()
          );
      
      label1.Text = "Finished Inverse Projection";
      label1.Update();
    }

    private void pictureBox1_Click(object sender, EventArgs e)
    {

    }

    private void button3_Click(object sender, EventArgs e)
    {

    }


    private void label1_Click(object sender, EventArgs e)
    {

    }

    private void Form1_Load(object sender, EventArgs e)
    {

    }

    private void chart1_MouseClick(object sender, MouseEventArgs e)
    {
      if (e.Button == MouseButtons.Left)
      {
        var pos = e.Location;
        Point clickPosition = pos;
        var results = chart1.HitTest(pos.X, pos.Y, false,
                                     ChartElementType.PlottingArea);
        foreach (var result in results)
        {
          if (result.ChartElementType == ChartElementType.PlottingArea)
          {
            chart1.Series[1].Points.Clear();
            
            var xVal = result.ChartArea.AxisX.PixelPositionToValue(pos.X);
            var yVal = result.ChartArea.AxisY.PixelPositionToValue(pos.Y);

            chart1.Series[1].Points.AddXY(Math.Round(xVal, 5), Math.Round(yVal, 5));
            chart1.Series[1].Points[0].LegendToolTip = "userpoint";
            chart1.Series[1].Points[0].ToolTip = "userpoint" + "\n X= " + xVal + " Y = " + yVal;
          }
        }
      }
      if (e.Button == MouseButtons.Right)
      {
        Chart chart = chart1;
        Series scol = chart.Series[0];
        if (scol.Points.Count > 0)
        {
          var pos = e.Location;
          Point clickPosition = pos;
          var results = chart1.HitTest(pos.X, pos.Y, false, ChartElementType.PlottingArea);
 
          foreach (var result in results)
          {
            if (result.ChartElementType == ChartElementType.PlottingArea)
            {
              var xpos = result.ChartArea.AxisX.PixelPositionToValue(pos.X);
              var ypos = result.ChartArea.AxisY.PixelPositionToValue(pos.Y);

              int m_id = 0;
              double m_dist = Math.Sqrt(
                Math.Pow(scol.Points[0].XValue - xpos, 2.0)
                +
                Math.Pow(scol.Points[0].YValues[0] - ypos, 2.0)
              );
              
              int n_reference_points = scol.Points.Count();
              for (int p = 1; p < n_reference_points; p++)
              {
                DataPoint pt = scol.Points[p];

                double dist = Math.Sqrt(
                  Math.Pow(scol.Points[p].XValue - xpos, 2.0)
                  +
                  Math.Pow(scol.Points[p].YValues[0] - ypos, 2.0)
                );
                if (dist < m_dist)
                {
                  m_dist = dist;
                  m_id = p;
                }
              }
              
              chart.Series[2].Points.Add(chart.Series[0].Points[m_id]);
              chart.Series[0].Points.RemoveAt(m_id);
            }
          }
        }
      }
      if (e.Button == MouseButtons.Middle)
      {
        Chart chart = chart1;
        Series scol = chart.Series[2];
        if (scol.Points.Count > 0)
        {
          var pos = e.Location;
          Point clickPosition = pos;
          var results = chart1.HitTest(pos.X, pos.Y, false, ChartElementType.PlottingArea);

          foreach (var result in results)
          {
            if (result.ChartElementType == ChartElementType.PlottingArea)
            {
              var xpos = result.ChartArea.AxisX.PixelPositionToValue(pos.X);
              var ypos = result.ChartArea.AxisY.PixelPositionToValue(pos.Y);

              int m_id = 0;
              double m_dist = Math.Sqrt(
                Math.Pow(scol.Points[0].XValue - xpos, 2.0)
                +
                Math.Pow(scol.Points[0].YValues[0] - ypos, 2.0)
              );

              int n_reference_points = scol.Points.Count();
              for (int p = 1; p < n_reference_points; p++)
              {
                DataPoint pt = scol.Points[p];

                double dist = Math.Sqrt(
                  Math.Pow(scol.Points[p].XValue - xpos, 2.0)
                  +
                  Math.Pow(scol.Points[p].YValues[0] - ypos, 2.0)
                );
                if (dist < m_dist)
                {
                  m_dist = dist;
                  m_id = p;
                }
              }

              chart.Series[0].Points.Add(chart.Series[2].Points[m_id]);
              chart.Series[2].Points.RemoveAt(m_id);
            }
          }
        }
      }
    }

    private void chart2_MouseClick(object sender, MouseEventArgs e)
    {

    }

    private void chart4_MouseClick(object sender, MouseEventArgs e)
    {
     
    }
    
  }
}

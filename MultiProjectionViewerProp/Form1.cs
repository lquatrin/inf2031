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

    private bool model_loaded = false;
    private string model_name;
    private int[] model_size = new int[3];
    private string model_path;
    
    public Form1()
    {
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
      // Allow the user to select multiple images.
      this.openFileDialog1.Multiselect = true;
      this.openFileDialog1.Title = "File input selection";

      // Allow the user to select one CFG.
      this.openCFGDialog.Multiselect = false;
      this.openCFGDialog.Title = "CFG selection";
    }

    private DialogResult OpenCFGDialog()
    {
      openCFGDialog.Filter =
      "Input FIles (*.cfg)|*.cfg|" +
      "All files (*.*)|*.*";

      return openCFGDialog.ShowDialog();
    }

    private DialogResult OpenPropDialog()
    {
      openFileDialog1.Filter =
      "Input FIles (*.prop)|*.prop|" +
      "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      openFileDialog1.Multiselect = true;
      openFileDialog1.Title = "File input selection";
      return openFileDialog1.ShowDialog();
    }


    private void MDS_Click(object sender, EventArgs e)
    {
      label1.Text = "Start MDS";
      label1.Update();

      DialogResult result = OpenPropDialog();
      List<string> prop_files = new List<string>();
      List<string> filter_files = new List<string>();
      if (result == DialogResult.OK)
      {
        prop_files.Clear();
        filter_files.Clear();
      
        int counter = 0;
        foreach (String file in openFileDialog1.FileNames)
        {
          string idk = file.Split('\\').Last().Split('_').Last().Split('.').First();
          string prop = file.Split('\\').Last().Split('_').First();
          int splitted_paths = file.Split('\\').Last().Length;
          
          string path = file.Substring(0, file.Length - splitted_paths);
          path = path + prop.ToString() + '\\' + "k_" + idk.ToString() + ".filter";
          
          //Console.WriteLine(path);
          //Console.WriteLine(file);

          prop_files.Add(file);
          
          filter_files.Add(path);
          
          counter++;
        }

        /*
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
        */
      }

      label1.Text = "Finished MDS";
      label1.Update();
    }

    private void button1_Click(object sender, EventArgs e)
    {
      label1.Text = "Start LAMP";
      label1.Update();
/*
      Chart chart = new Chart();
      chart = chart1;

      if (checkBox1.Checked)
      {
        DialogResult result = OpenFileImageDialog();
        List<string> file_paths = new List<string>();
        if (result == DialogResult.OK)
        {
          file_paths.Clear();
          int counter = 0;
          foreach (String file in openFileDialog1.FileNames)
          {
            Console.WriteLine(file);
            string files = openFileDialog1.InitialDirectory + file;
            file_paths.Add(files);
            counter++;
          }
        }
      }

      int n_points = chart.Series[2].Points.Count();
      if (n_points > 0)
      {
        foreach (DataPoint pt in chart.Series[2].Points)
        {
          Console.WriteLine(pt.Tag);
        }
        //double[,] array = new double[4, 2];
        //CppWrapper.CppLAMPWrapper mlamp = new CppWrapper.CppLAMPWrapper();
      }*/

      label1.Text = "Finished LAMP";
      label1.Update();
    }

    private void textBox1_TextChanged(object sender, EventArgs e)
    {

    }


    private void button2_Click(object sender, EventArgs e)
    {
      label1.Text = "Start Inverse Projection";
      label1.Update();
   
      /*Chart chart = chart1;

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
      */
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

    private void checkBox1_CheckedChanged(object sender, EventArgs e)
    {

    }

    private void button3_Click_1(object sender, EventArgs e)
    {
      label1.Text = "Loading CFG";
      label1.Update();

      DialogResult result = OpenCFGDialog();
      if (result == DialogResult.OK) // Test result.
      {
        model_loaded = true;
        model_path = openCFGDialog.FileName;

        System.IO.StreamReader file = new System.IO.StreamReader(model_path);

        model_name = file.ReadLine().ToString();
        label2.Text = model_name;
        label2.Update();

        model_size[0] = Int32.Parse(file.ReadLine().ToString());
        model_size[1] = Int32.Parse(file.ReadLine().ToString());
        model_size[2] = Int32.Parse(file.ReadLine().ToString());

        label3.Text = model_size[0] + " " + model_size[1] + " " + model_size[2];
        label3.Update();
    
        file.Close();
        
      }
      
      label1.Text = "CFG Loaded";
      label1.Update();
    }

    private void label2_Click(object sender, EventArgs e)
    {

    }

    private void label3_Click(object sender, EventArgs e)
    {

    }
    
  }
}

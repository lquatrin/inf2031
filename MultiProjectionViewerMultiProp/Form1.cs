using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing.Drawing2D;

using CppWrapper;
using System.Windows.Forms.DataVisualization.Charting;

namespace ClassCppToCS_CS
{
  public partial class Form1 : Form
  {
    public CppWrapper.CppInverseProjectionWrapper wrapper_inverse_projection;
    public int current_colorspace_input;

    private string model_name;
    private int[] model_size = new int[3];
    
    private int global_mouse_id_click;

    private int input_prop_type;

    private string[] loaded_properties;
    private int number_of_properties;

    private string model_path;
    private double[,] min_max_property;

    private int global_n_of_cases;
    private double[,] original_xy_cases;

    public Form1()
    {
      InitializeComponent();

      this.pct_box_result_image.Image = null;
      this.pct_box_result_image.BorderStyle = BorderStyle.FixedSingle;

      global_mouse_id_click = -1;

      current_colorspace_input = 0;

      wrapper_inverse_projection = new CppWrapper.CppInverseProjectionWrapper();
      wrapper_inverse_projection.SetInputColorScapeType(0);
      Chart chart = new Chart();
      chart = chart1;
      chart.Series.Clear();

      chart.Series.Add("Loaded Points");
      chart.Series[0].Tag = "LoadedPoints";
      chart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      chart.Series[0].Color = Color.Blue;
      chart.Series[0].MarkerStyle = MarkerStyle.Square;

      chart.Series.Add("Input Points");
      chart.Series[1].Tag = "InputPoints";
      chart.Series[1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      chart.Series[1].Color = Color.Orange;
      chart.Series[1].MarkerStyle = MarkerStyle.Circle;

      chart.Series.Add("Control Points");
      chart.Series[2].Tag = "ControlPoints";
      chart.Series[2].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      chart.Series[2].Color = Color.Red;
      chart.Series[2].MarkerStyle = MarkerStyle.Square;

      input_prop_type = 0;
      loaded_properties = null;
      number_of_properties = 0;
      min_max_property = null;
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
      "Input FIles (*.multiprop)|*.multiprop|" +
      "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      openFileDialog1.Multiselect = false;
      openFileDialog1.Title = "File input selection";
      return openFileDialog1.ShowDialog();
    }

    private DialogResult OpenCFGMultiPropDialog()
    {
      openFileDialog1.Filter =
      "Input FIles (*.cfgmultiprop)|*.cfgmultiprop|" +
      "All files (*.*)|*.*";

      // Allow the user to select multiple images.
      openFileDialog1.Multiselect = false;
      openFileDialog1.Title = "File input selection";
      return openFileDialog1.ShowDialog();
    }

    private void InverseProjection ()
    {
      Chart chart = chart1;

      label1.Text = "Start Inverse Projection";
      label1.Update();

      int n_2d_control_points = 0;
      for (int i = 0; i < chart.Series[0].Points.Count(); i++)
      {
        if (chart.Series[0].Points[i].Color == Color.Red)
          n_2d_control_points++;
      }

      double[,] arraypoints = new double[n_2d_control_points, 2];


      List<string> ctl_paths = new List<string>(n_2d_control_points * number_of_properties);
      for (int i = 0; i < n_2d_control_points * number_of_properties; i++) ctl_paths.Add(null);

      int p2d = 0;
      for (int i = 0; i < chart.Series[0].Points.Count(); i++)
      {
        if (chart.Series[0].Points[i].Color == Color.Red)
        {
          DataPoint pt = chart.Series[0].Points[i];
          if (pt.Color == Color.Red)
          {
            arraypoints[p2d, 0] = pt.XValue;
            arraypoints[p2d, 1] = pt.YValues[0];

            for (int py = 0; py < number_of_properties; py++)
            {
              ctl_paths[p2d + py * n_2d_control_points] = (model_path + "\\" + loaded_properties[py] + "\\" + loaded_properties[py] + "_" + (pt.Tag) + ".prop");
            }
            p2d++;
          }
        }
      }

      double[,] input_point = new double[,] { { 0, 0 } };

      if (chart.Series[1].Points.Count() > 0)
      {
        input_point[0, 0] = chart.Series[1].Points[0].XValue;
        input_point[0, 1] = chart.Series[1].Points[0].YValues[0];
      }

      if (this.pct_box_result_image.Image != null)
      {
        this.pct_box_result_image.Image.Dispose();
        this.pct_box_result_image.Image = null;
      }

      wrapper_inverse_projection.SetModelSize(model_size[0], model_size[1], model_size[2]);

      wrapper_inverse_projection.InverseProjectionMultiPropBased(
        input_prop_type,
        input_point,
        n_2d_control_points,
        arraypoints,
        ctl_paths.ToArray(),
        number_of_properties,
        min_max_property
      );


      Bitmap b = new Bitmap(this.pct_box_result_image.Width, this.pct_box_result_image.Height);
      Graphics g = Graphics.FromImage((Image)b);

      Image f_image = Image.FromFile(loaded_properties[0] + ".propinverse.png");
      double pbw = this.pct_box_result_image.Width;
      double pbh = this.pct_box_result_image.Height;

      double orig_imw = f_image.Width;
      double imw = f_image.Width * loaded_properties.Length;
      double imh = f_image.Height;
      
      double sw = pbw / imw;
      double sh = pbh / imh;
      
      f_image.Dispose();

      double s;
      if (sw < sh)
        s = sw;
      else
        s = sh;

      int step_x = (int)(orig_imw * s);
      int step_y = (int)(imh * s);
      int mid_h = this.pct_box_result_image.Height / 2;
      for (int i = 0; i < loaded_properties.Length; i++)
      {
        Image res_image = Image.FromFile(loaded_properties[i] + ".propinverse.png");
        g.InterpolationMode = InterpolationMode.HighQualityBicubic;
        g.DrawImage(res_image, step_x * i, 0, step_x, step_y);
        res_image.Dispose();
      }
      g.Dispose();

      this.pct_box_result_image.Image = (Image)b.Clone();

      b.Dispose();

      label1.Text = "Finished Inverse Projection";
      label1.Update();
    }

    private void btn_inverseprojection_click(object sender, EventArgs e)
    {
      InverseProjection();
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

    private Chart GetChartByID (int c_id)
    {
      if (c_id == 1)
        return chart1;
      return chart1;
    }

    private void chart_MouseDown(object sender, MouseEventArgs e)
    {
      Chart chart = (Chart)sender;
      int chart_id = int.Parse(chart.Text);
      MouseDownChartCallback(chart_id, GetChartByID(chart_id), e);
    }

    private void chart_MouseMove(object sender, MouseEventArgs e)
    {
      Chart chart = (Chart)sender;
      int chart_id = int.Parse(chart.Text);
      MouseMoveChartCallback(chart_id, GetChartByID(chart_id), e);
    }

    private void chart_MouseUp(object sender, MouseEventArgs e)
    {
      Chart chart = (Chart)sender;
      int chart_id = int.Parse(chart.Text);
      MouseUpChartCallback(chart_id, GetChartByID(chart_id), e);
    }
      private void MouseDownChartCallback(int chart_id, Chart chart, MouseEventArgs e)
    {
      if (e.Button == MouseButtons.Right)
      {
        MouseDownRightButtonProcess(chart, e.Location, chart_id - 1);
      }
    }

    private void MouseMoveChartCallback(int chart_id, Chart chart, MouseEventArgs e)
    {
      if (global_mouse_id_click >= 0)
      {
        Point clickPosition = e.Location;
        var xpos = chart.ChartAreas[0].AxisX.PixelPositionToValue(clickPosition.X);
        var ypos = chart.ChartAreas[0].AxisY.PixelPositionToValue(clickPosition.Y);

        chart.Series[0].Points[global_mouse_id_click].XValue = xpos;
        chart.Series[0].Points[global_mouse_id_click].YValues[0] = ypos;
        chart.Series[0].Points[global_mouse_id_click].ToolTip = "Case " + (global_mouse_id_click + 1) + "\n X= " + xpos + " Y = " + ypos;
      }
    }
    private void MouseUpChartCallback(int chart_id, Chart chart, MouseEventArgs e)
    {
      if (e.Button == MouseButtons.Left)
      {
        MouseLeftButtonProcess(chart, e.Location);
      }
      if (e.Button == MouseButtons.Right)
      {
        global_mouse_id_click = -1;
      }
    }

    private void MouseLeftButtonProcess(Chart chart, Point clickPosition)
    {

      var results = chart.HitTest(clickPosition.X, clickPosition.Y, false,
                                   ChartElementType.PlottingArea);
      foreach (var result in results)
      {
        if (result.ChartElementType == ChartElementType.PlottingArea)
        {
          chart.Series[1].Points.Clear();

          var xVal = result.ChartArea.AxisX.PixelPositionToValue(clickPosition.X);
          var yVal = result.ChartArea.AxisY.PixelPositionToValue(clickPosition.Y);

          chart.Series[1].Points.AddXY(Math.Round(xVal, 5), Math.Round(yVal, 5));
          chart.Series[1].Points[0].LegendToolTip = "userpoint";
          chart.Series[1].Points[0].ToolTip = "userpoint" + "\n X= " + xVal + " Y = " + yVal;
          chart.Series[1].Color = Color.Orange;
        }
      }
    }

    private void MouseDownRightButtonProcess(Chart chart, Point clickPosition, int chart_id)
    {
      Series scol = chart.Series[0];
      if (scol.Points.Count > 0)
      {
        var results = chart.HitTest(clickPosition.X, clickPosition.Y, false, ChartElementType.PlottingArea);

        foreach (var result in results)
        {
          if (result.ChartElementType == ChartElementType.PlottingArea)
          {
            var xpos = result.ChartArea.AxisX.PixelPositionToValue(clickPosition.X);
            var ypos = result.ChartArea.AxisY.PixelPositionToValue(clickPosition.Y);

            int m_id = -1;
            double m_dist = 1.0;

            int n_reference_points = scol.Points.Count();
            for (int p = 0; p < n_reference_points; p++)
            {
              DataPoint pt = scol.Points[p];

              double dist = Math.Sqrt(
                Math.Pow(scol.Points[p].XValue - xpos, 2.0)
                +
                Math.Pow(scol.Points[p].YValues[0] - ypos, 2.0)
              );

              if (dist < m_dist && dist < 1)
              {
                m_dist = dist;
                m_id = p;
              }
            }

            if (m_id >= 0)
            {
              if (chart.Series[0].Points[m_id].Color == Color.Blue)
              {
                global_mouse_id_click = m_id;

                chart.Series[0].Points[m_id].Color = Color.Red;
              }
              else if (chart.Series[0].Points[m_id].Color == Color.Red)
              {
                global_mouse_id_click = -1;
                chart.Series[0].Points[m_id].XValue = original_xy_cases[m_id, 0];
                chart.Series[0].Points[m_id].YValues[0] = original_xy_cases[m_id, 1];
                chart.Series[0].Points[m_id].ToolTip = "Case " + (m_id + 1) + "\n X= " + original_xy_cases[m_id, 0] + " Y = " + original_xy_cases[m_id, 1];
                
                chart.Series[0].Points[m_id].Color = Color.Blue;
              }
            }
          }
        }
      }
    }

    private void CallMDSWithMultiPropAndCFG(object sender, EventArgs e)
    {
      Chart chart = chart1;

      label1.Text = "Start CFG MultiProp MDS";
      label1.Update();
      DialogResult result = OpenCFGMultiPropDialog();
      if (result == DialogResult.OK)
      {
        String file_path_name = openFileDialog1.FileName;

        // Get filename path
        int splitted_paths = file_path_name.Split('\\').Last().Length;
        string filename_path = file_path_name.Substring(0, file_path_name.Length - splitted_paths);
        
        // Get lines
        var lines = File.ReadAllLines(openFileDialog1.FileName);
        
        model_path = file_path_name;
        
        // Get "Model Name" and "Model Sizes"
        System.IO.StreamReader file = new System.IO.StreamReader(model_path);

        input_prop_type = int.Parse(lines[0]);
        
        model_name = lines[1];
        label2.Text = model_name;
        label2.Update();
        
        model_size[0] = int.Parse(lines[2]);
        model_size[1] = int.Parse(lines[3]);
        model_size[2] = int.Parse(lines[4]);
        
        label3.Text = model_size[0] + " " + model_size[1] + " " + model_size[2];
        label3.Update();
        
        file.Close();
        
        // Get number of properties
        number_of_properties = int.Parse(lines[5]);

        label4.Text = number_of_properties + " properties:";
        
        min_max_property = null;
        min_max_property = new double[number_of_properties, 2];

        loaded_properties = null;
        loaded_properties = new string[number_of_properties];

        // Get number of cases
        int number_of_cases = int.Parse(lines[6]);
        global_n_of_cases = number_of_cases;

        original_xy_cases = null;
        original_xy_cases = new double[global_n_of_cases, 2];

        // Get path properties
        string multiprop_path = lines[7];
        
        // Distance Prop Class
        CppWrapper.CppDistanceProp distance_prop_eval = new CppWrapper.CppDistanceProp();
        distance_prop_eval.SetEnvironmentType(1);
        distance_prop_eval.SetNumberOfPropertiesAndCases(number_of_properties, number_of_cases);
        distance_prop_eval.SetMapSize(model_size[0], model_size[1]);
        
        List<string> prop_files = new List<string>();
        for (int i = 0; i < number_of_properties; i++)
        {
          string prop = lines[8 + i * 3];
          double min = double.Parse(lines[8 + i * 3 + 1]);
          double max = double.Parse(lines[8 + i * 3 + 2]);

          Console.Out.WriteLine("Propriedade " + (i + 1) + ":\n - " + prop + " between [" + min + ", " + max + "]");
          label4.Text = label4.Text + " \"" + prop + "\"";
          loaded_properties[i] = prop;

          prop_files.Clear();
          for (int cases_files = 0; cases_files < number_of_cases; cases_files++)
          {
            prop_files.Add(filename_path + multiprop_path + "\\" + prop + "\\" + prop + "_" + (cases_files + 1) + ".prop");
          }
          
          // Return Property
          double[] ret_input = distance_prop_eval.SetMultiProjectionInputFilePaths(
              input_prop_type
            , i
            , prop_files.ToArray()
            , min
            , max
          );

          min_max_property[i,0] = ret_input[0];
          min_max_property[i,1] = ret_input[1];

          Console.Out.WriteLine(" - Min: " + min_max_property[i, 0] + ", Max: " + min_max_property[i, 1]);
        }

        model_path = filename_path + multiprop_path;

        double[,] array = distance_prop_eval.GetDistances();

        CppWrapper.CppMDSWrapper eval_MDS = new CppWrapper.CppMDSWrapper(array, number_of_cases);
        double[,] arrayMDS = eval_MDS.GetMDS();
        
        chart.Series[0].Points.Clear();
        
        double[] min_max_axis_limits = new Double[4];
        min_max_axis_limits[0] = Double.MaxValue;
        min_max_axis_limits[1] = Double.MinValue;
        min_max_axis_limits[2] = Double.MaxValue;
        min_max_axis_limits[3] = Double.MinValue;
        
        double expand_limtis = 1.2;
        
        for (int i = 0; i < number_of_cases; i++)
        {
          string name = prop_files[i].Split('\\').Last();
        
          double mm_x = arrayMDS[i, 0]; //Math.Round(arrayMDS[i, 0], 5);
          double mm_y = arrayMDS[i, 1]; //Math.Round(arrayMDS[i, 1], 5);
        
          chart.Series[0].Points.AddXY(mm_x, mm_y);
          original_xy_cases[i, 0] = mm_x;
          original_xy_cases[i, 1] = mm_y;


          chart.Series[0].Points[i].LegendToolTip = "loadedpoint";
          chart.Series[0].Points[i].Tag = (i + 1).ToString();
          chart.Series[0].Points[i].ToolTip = "Case " + (i+1) + "\n X= " + arrayMDS[i, 0] + " Y = " + arrayMDS[i, 1];
          if (this.controlpoints_state.Checked)
            chart.Series[0].Points[i].Color = Color.Red;
          else
            chart.Series[0].Points[i].Color = Color.Blue;
        
          min_max_axis_limits[0] = Math.Min(min_max_axis_limits[0], mm_x);
          min_max_axis_limits[1] = Math.Max(min_max_axis_limits[1], mm_x);
        
          min_max_axis_limits[2] = Math.Min(min_max_axis_limits[2], mm_y);
          min_max_axis_limits[3] = Math.Max(min_max_axis_limits[3], mm_y);
        }
        
        min_max_axis_limits[0] *= expand_limtis;
        min_max_axis_limits[1] *= expand_limtis;
        
        min_max_axis_limits[2] *= expand_limtis;
        min_max_axis_limits[3] *= expand_limtis;
        
        chart.ChartAreas[0].AxisX.Minimum = min_max_axis_limits[0];
        chart.ChartAreas[0].AxisX.Maximum = min_max_axis_limits[1];
        
        chart.ChartAreas[0].AxisY.Minimum = min_max_axis_limits[2];
        chart.ChartAreas[0].AxisY.Maximum = min_max_axis_limits[3];
      }

      label4.Update();

      label1.Text = "Finished CFG MultiProp MDS";
      label1.Update();
    }

    private void btn_lamp_click(object sender, EventArgs e)
    {
      Chart chart = chart1;

      label1.Text = "Start LAMP";
      label1.Update();

      int n_2d_control_points = 0;
      for (int i = 0; i < chart.Series[0].Points.Count(); i++)
      {
        if (chart.Series[0].Points[i].Color == Color.Red)
          n_2d_control_points++;
      }

      int[] indexPoints = new int[n_2d_control_points];
      double[,] pts_control = new double[n_2d_control_points, 2];

      double[,] pts_inputarray = new double[chart.Series[0].Points.Count(), 2];
      List<string> ctl_paths = new List<string>(chart.Series[0].Points.Count() * number_of_properties);
      for (int i = 0; i < chart.Series[0].Points.Count() * number_of_properties; i++) ctl_paths.Add("");

      for (int i = 0; i < n_2d_control_points * number_of_properties; i++) ctl_paths.Add(null);

      int p2d = 0;
      int n_ref_points = chart.Series[0].Points.Count();
      for (int i = 0; i < n_ref_points; i++)
      {
        DataPoint pt = chart.Series[0].Points[i];
        pts_inputarray[i, 0] = original_xy_cases[i, 0];
        pts_inputarray[i, 1] = original_xy_cases[i, 1];
        
        for (int py = 0; py < number_of_properties; py++)
        {
          string prop_path_ith = (model_path + "\\" + loaded_properties[py] + "\\" + loaded_properties[py] + "_" + (pt.Tag) + ".prop");
          ctl_paths[i + py * chart.Series[0].Points.Count()] = prop_path_ith;
        }
        
        if (pt.Color == Color.Red)
        {
          pts_control[p2d, 0] = Math.Round(pt.XValue,5);
          pts_control[p2d, 1] = Math.Round(pt.YValues[0],5);
          indexPoints[p2d] = i;
          p2d++;
        }
      }

      CppWrapper.CppLAMPWrapper lamp = new CppWrapper.CppLAMPWrapper();
      double[,] proj = lamp.GetLAMP(pts_inputarray, pts_control, indexPoints, n_2d_control_points, n_ref_points);

      double[] min_max_axis_limits = new Double[4];
      min_max_axis_limits[0] = Double.MaxValue;
      min_max_axis_limits[1] = Double.MinValue;
      min_max_axis_limits[2] = Double.MaxValue;
      min_max_axis_limits[3] = Double.MinValue;

      double expand_limtis = 1.2;
      for (int i = 0; i < n_ref_points; i++)
      {
        double mm_x = proj[i, 0]; //Math.Round(proj[i, 0], 5);
        double mm_y = proj[i, 1]; //Math.Round(proj[i, 1], 5);

        Console.Out.WriteLine(i + " - [" + mm_x + ", " + mm_y + "]");

        chart.Series[0].Points[i].XValue = mm_x;
        chart.Series[0].Points[i].YValues[0] = mm_y;
        //chart.Series[0].Points.AddXY(mm_x, mm_y);

        min_max_axis_limits[0] = Math.Min(min_max_axis_limits[0], mm_x);
        min_max_axis_limits[1] = Math.Max(min_max_axis_limits[1], mm_x);

        min_max_axis_limits[2] = Math.Min(min_max_axis_limits[2], mm_y);
        min_max_axis_limits[3] = Math.Max(min_max_axis_limits[3], mm_y);
      }

      min_max_axis_limits[0] *= expand_limtis;
      min_max_axis_limits[1] *= expand_limtis;
      
      min_max_axis_limits[2] *= expand_limtis;
      min_max_axis_limits[3] *= expand_limtis;
      
      chart.ChartAreas[0].AxisX.Minimum = min_max_axis_limits[0];
      chart.ChartAreas[0].AxisX.Maximum = min_max_axis_limits[1];
      
      chart.ChartAreas[0].AxisY.Minimum = min_max_axis_limits[2];
      chart.ChartAreas[0].AxisY.Maximum = min_max_axis_limits[3];    

      label1.Text = "Finished LAMP";
      label1.Update();
    }

    private void controlpoints_state_CheckedChanged(object sender, EventArgs e)
    {
      bool checked_box_state = this.controlpoints_state.Checked;
      Chart chart = chart1;

      for (int i = 0; i < chart.Series[0].Points.Count(); i++)
      {
        if (checked_box_state)
          chart.Series[0].Points[i].Color = Color.Red;
        else
          chart.Series[0].Points[i].Color = Color.Blue;
      }
    }

    private void chart1_Click(object sender, EventArgs e)
    {

    }

  };
}

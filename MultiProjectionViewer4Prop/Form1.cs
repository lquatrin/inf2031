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
        private int[] id_mouse_aux = new int[5];
        private string model_path;
        private double[,] input_property;
        private List<List<List<double>>> controls;
        private List<List<int>> controls_idx;
        private bool add;
        public Form1()
        {
            InitializeComponent();
            add = false;
            controls = new List<List<List<double>>>();
            controls_idx = new List<List<int>>();
            for (int i = 0; i < 4; i++)
            {
                List<List<double>> aux = new List<List<double>>();
                List<double> t = new List<double>();
                aux.Add(t);
                controls.Add(aux);
                controls_idx.Add(new List<int>());
            }

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
            chart.Series.Add("Control Points");
            chart.Series[2].Tag = "ControlPoints";
            chart.Series[2].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series[2].Color = Color.Red;

            chart = chart2;
            chart.Series.Clear();

            chart.Series.Add("Loaded Points");
            chart.Series[0].Tag = "LoadedPoints";
            chart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;

            chart.Series.Add("Input Points");
            chart.Series[1].Tag = "InputPoints";
            chart.Series[1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series.Add("Control Points");
            chart.Series[2].Tag = "ControlPoints";
            chart.Series[2].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series[2].Color = Color.Red;

            chart = chart3;
            chart.Series.Clear();

            chart.Series.Add("Loaded Points");
            chart.Series[0].Tag = "LoadedPoints";
            chart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;

            chart.Series.Add("Input Points");
            chart.Series[1].Tag = "InputPoints";
            chart.Series[1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series.Add("Control Points");
            chart.Series[2].Tag = "ControlPoints";
            chart.Series[2].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series[2].Color = Color.Red;

            chart = chart4;
            chart.Series.Clear();

            chart.Series.Add("Loaded Points");
            chart.Series[0].Tag = "LoadedPoints";
            chart.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;

            chart.Series.Add("Input Points");
            chart.Series[1].Tag = "InputPoints";
            chart.Series[1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;

            chart.Series.Add("Control Points");
            chart.Series[2].Tag = "ControlPoints";
            chart.Series[2].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
            chart.Series[2].Color = Color.Red;
            input_property = new double[4, 2];
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

        private void button1_Click(object sender, EventArgs e)
        {

            Console.Out.Write("niga");
            /*label1.Text = "Start LAMP";
            label1.Update();

            Chart chart = new Chart();
            chart = chart1;

            double[,] array_input = new double[chart.Series[2].Points.Count, 2];
            List<string> array_prop_files = new List<string>();
            List<string> array_other_files = new List<string>();
            int count = 0;
            foreach (DataPoint pt in chart.Series[2].Points)
            {
              array_input[count, 0] = pt.XValue;
              array_input[count, 1] = pt.YValues[0];

              array_prop_files.Add(pt.Tag as string);
              count++;
            }
      
            foreach (DataPoint pt in chart.Series[0].Points)
            {
              array_other_files.Add(pt.Tag as string);
            }

            CppWrapper.CppLAMPWrapper mlamp = new CppWrapper.CppLAMPWrapper();
            double[,] arrayLAMP = mlamp.GetLAMP();

            chart.Series[0].Points.Clear();
            chart.Series[2].Points.Clear();
      
            label1.Text = "Finished LAMP";
            label1.Update();*/
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }


        private void button2_Click(object sender, EventArgs e)
        {
            InverseProjection(chart1, 0);
        }

        private void InverseProjection(Chart chart, int index_chart)
        {
            label1.Text = "Start Inverse Projection";
            label1.Update();

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

            double[,] input_point = new double[,] { { 0, 0 } };

            if (chart.Series[1].Points.Count() > 0)
            {
                input_point[0, 0] = chart.Series[1].Points[0].XValue;
                input_point[0, 1] = chart.Series[1].Points[0].YValues[0];
            }

            double[] input_prop = new double[2];
            input_prop[0] = input_property[index_chart, 0];
            input_prop[1] = input_property[index_chart, 1];


            wrapper_inverse_projection.InverseProjectionPropBased(
                n_reference_points,
                arraypoints,
                input_point,
                paths.ToArray(),
                model_size[0],
                model_size[1],
                input_prop
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
                MouseLeftButtonProcess(chart1, e.Location);
            }
            /*if (e.Button == MouseButtons.Right)
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
            }*/
            /*if (e.Button == MouseButtons.Middle)
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
            }*/
        }

        private void chart2_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseLeftButtonProcess(chart2, e.Location);
            }
        }

        private void chart3_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseLeftButtonProcess(chart3, e.Location);
            }
        }

        private void chart4_MouseClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                MouseLeftButtonProcess(chart4, e.Location);
            }
        }

        private Chart GetChartByID(int c_id)
        {
            if (c_id == 1)
                return chart1;
            else if (c_id == 2)
                return chart2;
            else if (c_id == 3)
                return chart3;
            else if (c_id == 4)
                return chart4;
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
            if (e.Button == MouseButtons.Right)
            {
                MouseMoveRightButtonProcess(chart, e.Location, chart_id - 1);
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
                MouseUpRightButtonProcess(chart, e.Location, chart_id - 1);
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
                }
            }
        }

        private void MouseDownRightButtonProcess(Chart chart, Point clickPosition, int chart_id)
        {
            id_mouse_aux[chart_id] = -1;
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

                            if (dist < m_dist && dist < 0.01)
                            {
                                m_dist = dist;
                                m_id = p;
                            }
                        }

                        if (m_id >= 0)
                        {
                            //chart.Series[0].Points[m_id].XValue = xpos;
                            //chart.Series[0].Points[m_id].YValues[0] = ypos;
                            
                            id_mouse_aux[chart_id] = m_id;
                            if (!controls_idx[chart_id].Contains(m_id))
                            {
                                chart.Series[0].Points[m_id].Color = Color.Red;
                                controls_idx[chart_id].Add(m_id);
                                add = true;
                            }
                            else
                            {
                              chart.Series[0].Points[m_id].Color = Color.Blue;
                              controls_idx[chart_id].Remove(m_id);
                              add = true;
                            }
                        }
                    }
                }
            }
        }

        private void MouseMoveRightButtonProcess(Chart chart, Point clickPosition, int chart_id)
        {
            if (id_mouse_aux[chart_id] >= 0)
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
                            chart.Series[0].Points[id_mouse_aux[chart_id]].XValue = xpos;
                            chart.Series[0].Points[id_mouse_aux[chart_id]].YValues[0] = ypos;
                        }
                    }
                }
            }
        }

        private void MouseUpRightButtonProcess(Chart chart, Point clickPosition, int chart_id)
        {
            if (id_mouse_aux[chart_id] >= 0)
            {
                Series scol = chart.Series[0];
                if (scol.Points.Count > 0)
                {
                    var results = chart.HitTest(clickPosition.X, clickPosition.Y, false, ChartElementType.PlottingArea);

                    foreach (var result in results)
                    {
                        if (result.ChartElementType == ChartElementType.PlottingArea)
                        {
                            List<double> t = new List<double>();
                            t.Add(result.ChartArea.AxisX.PixelPositionToValue(clickPosition.X));
                            t.Add(result.ChartArea.AxisY.PixelPositionToValue(clickPosition.Y));
                            if (add)
                            {
                                controls[chart_id].Add(t);
                                add = false;
                            }
                            else
                            {
                                controls[chart_id].RemoveAt(controls[chart_id].Count - 1);
                                controls[chart_id].Add(t);
                            }
                        }
                    }
                }
            }
            id_mouse_aux[chart_id] = -1;
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

        private void chart2_Click(object sender, EventArgs e)
        {

        }

        private void chart4_Click(object sender, EventArgs e)
        {

        }

        private void chart3_Click(object sender, EventArgs e)
        {

        }

        private void MDS_CHART_1(object sender, EventArgs e)
        {
            controls[0].Clear();
            BuildMDSToChart(chart1, 0);
        }

        private void MDS_CHART_2(object sender, EventArgs e)
        {
            controls[1].Clear();
            BuildMDSToChart(chart2, 1);
        }

        private void MDS_CHART_3(object sender, EventArgs e)
        {
            controls[2].Clear();
            BuildMDSToChart(chart3, 2);
        }

        private void MDS_CHART_4(object sender, EventArgs e)
        {
            controls[3].Clear();
            BuildMDSToChart(chart4, 3);
        }

        private void BuildMDSToChart(Chart chart, int chart_index)
        {
            label1.Text = "Start MDS";
            label1.Update();

            DialogResult result = OpenPropDialog();
            List<string> prop_files = new List<string>();
            List<string> filter_files = new List<string>();
            List<int> k_values = new List<int>();
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

                    prop_files.Add(file);

                    filter_files.Add(path);
                    k_values.Add(Int32.Parse(idk));

                    counter++;
                }

                CppWrapper.CppDistanceProp distance_prop_eval = new CppWrapper.CppDistanceProp();
                distance_prop_eval.SetMapSize(model_size[0], model_size[1]);

                double[] ret_property = distance_prop_eval.SetInputFilePaths(prop_files.ToArray(), filter_files.ToArray(), k_values.ToArray());

                input_property[chart_index, 0] = ret_property[0];
                input_property[chart_index, 1] = ret_property[1];

                double[,] array = distance_prop_eval.GetDistances();

                CppWrapper.CppMDSWrapper eval_MDS = new CppWrapper.CppMDSWrapper(array, counter);
                double[,] arrayMDS = eval_MDS.GetMDS();

                chart.Series[0].Points.Clear();
                //chart.Series[2].Points.Clear();

                double[] min_max_axis_limits = new Double[4];
                min_max_axis_limits[0] = Double.MaxValue;
                min_max_axis_limits[1] = Double.MinValue;
                min_max_axis_limits[2] = Double.MaxValue;
                min_max_axis_limits[3] = Double.MinValue;

                double expand_limtis = 1.2;

                for (int i = 0; i < counter; i++)
                {
                    string name = prop_files[i].Split('\\').Last();

                    double mm_x = Math.Round(arrayMDS[i, 0], 5);
                    double mm_y = Math.Round(arrayMDS[i, 1], 5);

                    chart.Series[0].Points.AddXY(mm_x, mm_y);

                    chart.Series[0].Points[i].LegendToolTip = name;
                    chart.Series[0].Points[i].Tag = prop_files[i];
                    chart.Series[0].Points[i].ToolTip = name + "\n X= " + arrayMDS[i, 0] + " Y = " + arrayMDS[i, 1];
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

            label1.Text = "Finished MDS";
            label1.Update();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            InverseProjection(chart2, 1);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            InverseProjection(chart3, 2);
        }

        private void button8_Click(object sender, EventArgs e)
        {
            InverseProjection(chart4, 3);
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }


        private void CalcByLambdas(Chart chart, int index_chart)
        {
            label1.Text = "Start Inverse Projection";
            label1.Update();

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

            double[,] input_point = new double[,] { { 0, 0 } };

            if (chart.Series[1].Points.Count() > 0)
            {
                input_point[0, 0] = chart.Series[1].Points[0].XValue;
                input_point[0, 1] = chart.Series[1].Points[0].YValues[0];
            }

            double[] input_prop = new double[2];
            input_prop[0] = input_property[index_chart, 0];
            input_prop[1] = input_property[index_chart, 1];


            wrapper_inverse_projection.InverseProjectionByLambda(
                n_reference_points,
                arraypoints,
                input_point,
                paths.ToArray(),
                model_size[0],
                model_size[1],
                input_prop
                );

            label1.Text = "Finished Inverse Projection";
            label1.Update();
        }

        private void button1_MouseClick(object sender, MouseEventArgs e)
        {
            InverseProjection(chart1, 0);

            CalcByLambdas(chart2, 1);
            CalcByLambdas(chart3, 2);
            CalcByLambdas(chart4, 3);
            wrapper_inverse_projection.CalcNewPropGridByInverse();

        }

        private void generateLamp(Chart chart, int index_chart)
        {
            label1.Text = "Start Inverse Projection";
            label1.Update();

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

            int[] indexPoints = new int[controls_idx[index_chart].Count];
            int k = 0;

            foreach (int val in controls_idx[index_chart])
            {
                indexPoints[k] = val;
                k++;
            }
            List<List<double>> tcontrol = controls[index_chart];
            double[,] controlPoints = new double[controls[index_chart].Count, 2];
            k = 0;
            foreach (var a in tcontrol)
            {
                controlPoints[k, 0] = a[0];
                controlPoints[k, 1] = a[1];
                k++;
            }
            CppWrapper.CppLAMPWrapper lamp = new CppWrapper.CppLAMPWrapper();
            double[,] proj = lamp.GetLAMP(arraypoints, controlPoints, indexPoints, controls_idx[index_chart].Count, n_reference_points);


            List<string> prop_files = new List<string>();
            List<string> filter_files = new List<string>();
            List<int> k_values = new List<int>();

            prop_files.Clear();
            filter_files.Clear();

            int count = 0;
            foreach (String file in openFileDialog1.FileNames)
            {
                string idk = file.Split('\\').Last().Split('_').Last().Split('.').First();
                string prop = file.Split('\\').Last().Split('_').First();
                int splitted_paths = file.Split('\\').Last().Length;

                string path = file.Substring(0, file.Length - splitted_paths);
                path = path + prop.ToString() + '\\' + "k_" + idk.ToString() + ".filter";

                prop_files.Add(file);

                filter_files.Add(path);
                k_values.Add(Int32.Parse(idk));

                count++;
            }

            chart.Series[0].Points.Clear();
            //chart.Series[2].Points.Clear();

            double[] min_max_axis_limits = new Double[4];
            min_max_axis_limits[0] = Double.MaxValue;
            min_max_axis_limits[1] = Double.MinValue;
            min_max_axis_limits[2] = Double.MaxValue;
            min_max_axis_limits[3] = Double.MinValue;

            double expand_limtis = 1.2;

            for (int i = 0; i < counter; i++)
            {
                string name = prop_files[i].Split('\\').Last();

                double mm_x = Math.Round(proj[i, 0], 5);
                double mm_y = Math.Round(proj[i, 1], 5);

                chart.Series[0].Points.AddXY(mm_x, mm_y);

                chart.Series[0].Points[i].LegendToolTip = name;
                chart.Series[0].Points[i].Tag = prop_files[i];
                chart.Series[0].Points[i].ToolTip = name + "\n X= " + proj[i, 0] + " Y = " + proj[i, 1];

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
        private void button9_Click(object sender, EventArgs e)
        {
            generateLamp(chart1, 0);
            //generateLamp(chart2, 1);
            //generateLamp(chart3, 2);
            //generateLamp(chart4, 3);

        }

    }
}

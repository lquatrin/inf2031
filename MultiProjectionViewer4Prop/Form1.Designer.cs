namespace ClassCppToCS_CS
{
  partial class Form1
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
      }
      base.Dispose(disposing);
    }

    #region Windows Form Designer generated code

    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea4 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend4 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.MDS = new System.Windows.Forms.Button();
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.openCFGDialog = new System.Windows.Forms.OpenFileDialog();
      this.button2 = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.button3 = new System.Windows.Forms.Button();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.chart2 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.chart3 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.chart4 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.MDS_CHART2 = new System.Windows.Forms.Button();
      this.button4 = new System.Windows.Forms.Button();
      this.button5 = new System.Windows.Forms.Button();
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart2)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart3)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart4)).BeginInit();
      this.SuspendLayout();
      // 
      // chart1
      // 
      chartArea1.Name = "ChartArea1";
      this.chart1.ChartAreas.Add(chartArea1);
      legend1.Name = "Legend1";
      this.chart1.Legends.Add(legend1);
      this.chart1.Location = new System.Drawing.Point(12, 93);
      this.chart1.Name = "chart1";
      series1.ChartArea = "ChartArea1";
      series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series1.LabelToolTip = "#SERIESNAME";
      series1.Legend = "Legend1";
      series1.Name = "Series1";
      series1.ToolTip = "#SERIESNAME";
      this.chart1.Series.Add(series1);
      this.chart1.Size = new System.Drawing.Size(620, 356);
      this.chart1.TabIndex = 0;
      this.chart1.Text = "chart1";
      this.chart1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.chart1_MouseClick);
      // 
      // MDS
      // 
      this.MDS.Location = new System.Drawing.Point(12, 64);
      this.MDS.Name = "MDS";
      this.MDS.Size = new System.Drawing.Size(102, 23);
      this.MDS.TabIndex = 4;
      this.MDS.Text = "MDS [Chart 1]";
      this.MDS.UseVisualStyleBackColor = true;
      this.MDS.Click += new System.EventHandler(this.MDS_CHART_1);
      // 
      // openFileDialog1
      // 
      this.openFileDialog1.FileName = "openFileDialog1";
      // 
      // openCFGDialog
      // 
      this.openCFGDialog.FileName = "openCFGDialog";
      // 
      // button2
      // 
      this.button2.Location = new System.Drawing.Point(636, 64);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(165, 23);
      this.button2.TabIndex = 7;
      this.button2.Text = "Inverse Projection LU";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new System.EventHandler(this.button2_Click);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(15, 43);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(10, 13);
      this.label1.TabIndex = 10;
      this.label1.Text = " ";
      // 
      // button3
      // 
      this.button3.Location = new System.Drawing.Point(12, 12);
      this.button3.Name = "button3";
      this.button3.Size = new System.Drawing.Size(75, 23);
      this.button3.TabIndex = 13;
      this.button3.Text = "Load CFG";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Click += new System.EventHandler(this.button3_Click_1);
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(351, 12);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(39, 13);
      this.label2.TabIndex = 14;
      this.label2.Text = " Model";
      this.label2.Click += new System.EventHandler(this.label2_Click);
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(351, 41);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(30, 13);
      this.label3.TabIndex = 15;
      this.label3.Text = " Size";
      this.label3.Click += new System.EventHandler(this.label3_Click);
      // 
      // chart2
      // 
      chartArea2.Name = "ChartArea1";
      this.chart2.ChartAreas.Add(chartArea2);
      legend2.Name = "Legend1";
      this.chart2.Legends.Add(legend2);
      this.chart2.Location = new System.Drawing.Point(636, 93);
      this.chart2.Name = "chart2";
      series2.ChartArea = "ChartArea1";
      series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series2.LabelToolTip = "#SERIESNAME";
      series2.Legend = "Legend1";
      series2.Name = "Series1";
      series2.ToolTip = "#SERIESNAME";
      this.chart2.Series.Add(series2);
      this.chart2.Size = new System.Drawing.Size(620, 356);
      this.chart2.TabIndex = 16;
      this.chart2.Text = "chart2";
      this.chart2.Click += new System.EventHandler(this.chart2_Click);
      this.chart2.MouseClick += new System.Windows.Forms.MouseEventHandler(this.chart2_MouseClick);
      // 
      // chart3
      // 
      chartArea3.Name = "ChartArea1";
      this.chart3.ChartAreas.Add(chartArea3);
      legend3.Name = "Legend1";
      this.chart3.Legends.Add(legend3);
      this.chart3.Location = new System.Drawing.Point(12, 455);
      this.chart3.Name = "chart3";
      series3.ChartArea = "ChartArea1";
      series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series3.LabelToolTip = "#SERIESNAME";
      series3.Legend = "Legend1";
      series3.Name = "Series1";
      series3.ToolTip = "#SERIESNAME";
      this.chart3.Series.Add(series3);
      this.chart3.Size = new System.Drawing.Size(620, 356);
      this.chart3.TabIndex = 18;
      this.chart3.Text = "chart3";
      this.chart3.Click += new System.EventHandler(this.chart3_Click);
      this.chart3.MouseClick += new System.Windows.Forms.MouseEventHandler(this.chart3_MouseClick);
      // 
      // chart4
      // 
      chartArea4.Name = "ChartArea1";
      this.chart4.ChartAreas.Add(chartArea4);
      legend4.Name = "Legend1";
      this.chart4.Legends.Add(legend4);
      this.chart4.Location = new System.Drawing.Point(636, 455);
      this.chart4.Name = "chart4";
      series4.ChartArea = "ChartArea1";
      series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series4.LabelToolTip = "#SERIESNAME";
      series4.Legend = "Legend1";
      series4.Name = "Series1";
      series4.ToolTip = "#SERIESNAME";
      this.chart4.Series.Add(series4);
      this.chart4.Size = new System.Drawing.Size(620, 356);
      this.chart4.TabIndex = 17;
      this.chart4.Text = "chart4";
      this.chart4.Click += new System.EventHandler(this.chart4_Click);
      this.chart4.MouseClick += new System.Windows.Forms.MouseEventHandler(this.chart4_MouseClick);
      // 
      // MDS_CHART2
      // 
      this.MDS_CHART2.Cursor = System.Windows.Forms.Cursors.Default;
      this.MDS_CHART2.Location = new System.Drawing.Point(120, 64);
      this.MDS_CHART2.Name = "MDS_CHART2";
      this.MDS_CHART2.Size = new System.Drawing.Size(102, 23);
      this.MDS_CHART2.TabIndex = 19;
      this.MDS_CHART2.Text = "MDS [Chart 2]";
      this.MDS_CHART2.UseVisualStyleBackColor = true;
      this.MDS_CHART2.Click += new System.EventHandler(this.MDS_CHART_2);
      // 
      // button4
      // 
      this.button4.Location = new System.Drawing.Point(228, 64);
      this.button4.Name = "button4";
      this.button4.Size = new System.Drawing.Size(102, 23);
      this.button4.TabIndex = 20;
      this.button4.Text = "MDS [Chart 3]";
      this.button4.UseVisualStyleBackColor = true;
      this.button4.Click += new System.EventHandler(this.MDS_CHART_3);
      // 
      // button5
      // 
      this.button5.Location = new System.Drawing.Point(336, 64);
      this.button5.Name = "button5";
      this.button5.Size = new System.Drawing.Size(102, 23);
      this.button5.TabIndex = 21;
      this.button5.Text = "MDS [Chart 4]";
      this.button5.UseVisualStyleBackColor = true;
      this.button5.Click += new System.EventHandler(this.MDS_CHART_4);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1268, 821);
      this.Controls.Add(this.button5);
      this.Controls.Add(this.button4);
      this.Controls.Add(this.MDS_CHART2);
      this.Controls.Add(this.chart3);
      this.Controls.Add(this.chart4);
      this.Controls.Add(this.chart2);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.button3);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.button2);
      this.Controls.Add(this.MDS);
      this.Controls.Add(this.chart1);
      this.Name = "Form1";
      this.Text = "Property Projection Analysis";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart2)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart3)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart4)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
    private System.Windows.Forms.Button MDS;
    private System.Windows.Forms.OpenFileDialog openFileDialog1;
    private System.Windows.Forms.OpenFileDialog openCFGDialog;
    private System.Windows.Forms.Button button2;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button button3;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.DataVisualization.Charting.Chart chart2;
    private System.Windows.Forms.DataVisualization.Charting.Chart chart3;
    private System.Windows.Forms.DataVisualization.Charting.Chart chart4;
    private System.Windows.Forms.Button MDS_CHART2;
    private System.Windows.Forms.Button button4;
    private System.Windows.Forms.Button button5;
  }
}


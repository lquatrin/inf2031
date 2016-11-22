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
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea4 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend4 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea5 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend5 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series5 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea6 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend6 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series6 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.chart2 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.chart4 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.MDS = new System.Windows.Forms.Button();
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.button1 = new System.Windows.Forms.Button();
      this.textBox1 = new System.Windows.Forms.TextBox();
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart2)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart4)).BeginInit();
      this.SuspendLayout();
      // 
      // chart1
      // 
      chartArea4.Name = "ChartArea1";
      this.chart1.ChartAreas.Add(chartArea4);
      legend4.Name = "Legend1";
      this.chart1.Legends.Add(legend4);
      this.chart1.Location = new System.Drawing.Point(4, 3);
      this.chart1.Name = "chart1";
      series4.ChartArea = "ChartArea1";
      series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series4.LabelToolTip = "#SERIESNAME";
      series4.Legend = "Legend1";
      series4.Name = "Series1";
      series4.ToolTip = "#SERIESNAME";
      this.chart1.Series.Add(series4);
      this.chart1.Size = new System.Drawing.Size(523, 294);
      this.chart1.TabIndex = 0;
      this.chart1.Text = "chart1";
      // 
      // chart2
      // 
      chartArea5.Name = "ChartArea1";
      this.chart2.ChartAreas.Add(chartArea5);
      legend5.Name = "Legend1";
      this.chart2.Legends.Add(legend5);
      this.chart2.Location = new System.Drawing.Point(530, 3);
      this.chart2.Name = "chart2";
      series5.ChartArea = "ChartArea1";
      series5.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series5.Legend = "Legend1";
      series5.Name = "Series1";
      this.chart2.Series.Add(series5);
      this.chart2.Size = new System.Drawing.Size(524, 294);
      this.chart2.TabIndex = 1;
      this.chart2.Text = "chart2";
      // 
      // chart4
      // 
      chartArea6.Name = "ChartArea1";
      this.chart4.ChartAreas.Add(chartArea6);
      legend6.Name = "Legend1";
      this.chart4.Legends.Add(legend6);
      this.chart4.Location = new System.Drawing.Point(4, 300);
      this.chart4.Name = "chart4";
      series6.ChartArea = "ChartArea1";
      series6.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series6.Legend = "Legend1";
      series6.Name = "Series1";
      this.chart4.Series.Add(series6);
      this.chart4.Size = new System.Drawing.Size(523, 301);
      this.chart4.TabIndex = 3;
      this.chart4.Text = "chart3";
      // 
      // MDS
      // 
      this.MDS.Location = new System.Drawing.Point(1060, 5);
      this.MDS.Name = "MDS";
      this.MDS.Size = new System.Drawing.Size(102, 23);
      this.MDS.TabIndex = 4;
      this.MDS.Text = "calcMDS";
      this.MDS.UseVisualStyleBackColor = true;
      this.MDS.Click += new System.EventHandler(this.MDS_Click);
      // 
      // openFileDialog1
      // 
      this.openFileDialog1.FileName = "openFileDialog1";
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(1060, 34);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(102, 23);
      this.button1.TabIndex = 5;
      this.button1.Text = "LAMP";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // textBox1
      // 
      this.textBox1.Location = new System.Drawing.Point(1168, 3);
      this.textBox1.Multiline = true;
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new System.Drawing.Size(299, 598);
      this.textBox1.TabIndex = 6;
      this.textBox1.TextChanged += new System.EventHandler(this.textBox1_TextChanged);
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1471, 605);
      this.Controls.Add(this.textBox1);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.MDS);
      this.Controls.Add(this.chart4);
      this.Controls.Add(this.chart2);
      this.Controls.Add(this.chart1);
      this.Name = "Form1";
      this.Text = "Form1";
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart2)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart4)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
    private System.Windows.Forms.DataVisualization.Charting.Chart chart2;
    private System.Windows.Forms.DataVisualization.Charting.Chart chart4;
    private System.Windows.Forms.Button MDS;
    private System.Windows.Forms.OpenFileDialog openFileDialog1;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.TextBox textBox1;
  }
}


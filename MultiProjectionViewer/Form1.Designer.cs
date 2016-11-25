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
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea13 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend13 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series13 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea14 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend14 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series14 = new System.Windows.Forms.DataVisualization.Charting.Series();
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea15 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend15 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series15 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.chart2 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.chart4 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.MDS = new System.Windows.Forms.Button();
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.button1 = new System.Windows.Forms.Button();
      this.button2 = new System.Windows.Forms.Button();
      this.pictureBox1 = new System.Windows.Forms.PictureBox();
      this.comboBox1 = new System.Windows.Forms.ComboBox();
      this.label1 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart2)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart4)).BeginInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
      this.SuspendLayout();
      // 
      // chart1
      // 
      chartArea13.Name = "ChartArea1";
      this.chart1.ChartAreas.Add(chartArea13);
      legend13.Name = "Legend1";
      this.chart1.Legends.Add(legend13);
      this.chart1.Location = new System.Drawing.Point(12, 41);
      this.chart1.Name = "chart1";
      series13.ChartArea = "ChartArea1";
      series13.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series13.LabelToolTip = "#SERIESNAME";
      series13.Legend = "Legend1";
      series13.Name = "Series1";
      series13.ToolTip = "#SERIESNAME";
      this.chart1.Series.Add(series13);
      this.chart1.Size = new System.Drawing.Size(484, 287);
      this.chart1.TabIndex = 0;
      this.chart1.Text = "chart1";
      // 
      // chart2
      // 
      chartArea14.Name = "ChartArea1";
      this.chart2.ChartAreas.Add(chartArea14);
      legend14.Name = "Legend1";
      this.chart2.Legends.Add(legend14);
      this.chart2.Location = new System.Drawing.Point(502, 41);
      this.chart2.Name = "chart2";
      series14.ChartArea = "ChartArea1";
      series14.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series14.Legend = "Legend1";
      series14.Name = "Series1";
      this.chart2.Series.Add(series14);
      this.chart2.Size = new System.Drawing.Size(484, 287);
      this.chart2.TabIndex = 1;
      this.chart2.Text = "chart2";
      this.chart2.Click += new System.EventHandler(this.chart2_Click);
      // 
      // chart4
      // 
      chartArea15.Name = "ChartArea1";
      this.chart4.ChartAreas.Add(chartArea15);
      legend15.Name = "Legend1";
      this.chart4.Legends.Add(legend15);
      this.chart4.Location = new System.Drawing.Point(992, 41);
      this.chart4.Name = "chart4";
      series15.ChartArea = "ChartArea1";
      series15.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series15.Legend = "Legend1";
      series15.Name = "Series1";
      this.chart4.Series.Add(series15);
      this.chart4.Size = new System.Drawing.Size(484, 287);
      this.chart4.TabIndex = 3;
      this.chart4.Text = "chart3";
      this.chart4.Click += new System.EventHandler(this.chart4_Click);
      // 
      // MDS
      // 
      this.MDS.Location = new System.Drawing.Point(12, 12);
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
      this.button1.Location = new System.Drawing.Point(120, 12);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(102, 23);
      this.button1.TabIndex = 5;
      this.button1.Text = "LAMP";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // button2
      // 
      this.button2.Location = new System.Drawing.Point(502, 12);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(165, 23);
      this.button2.TabIndex = 7;
      this.button2.Text = "Inverse Projection LU";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new System.EventHandler(this.button2_Click);
      // 
      // pictureBox1
      // 
      this.pictureBox1.Location = new System.Drawing.Point(12, 334);
      this.pictureBox1.Name = "pictureBox1";
      this.pictureBox1.Size = new System.Drawing.Size(1464, 349);
      this.pictureBox1.TabIndex = 8;
      this.pictureBox1.TabStop = false;
      this.pictureBox1.Click += new System.EventHandler(this.pictureBox1_Click);
      // 
      // comboBox1
      // 
      this.comboBox1.FormattingEnabled = true;
      this.comboBox1.Location = new System.Drawing.Point(865, 12);
      this.comboBox1.Name = "comboBox1";
      this.comboBox1.Size = new System.Drawing.Size(121, 21);
      this.comboBox1.TabIndex = 9;
      this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(992, 17);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(10, 13);
      this.label1.TabIndex = 10;
      this.label1.Text = " ";
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1493, 695);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.comboBox1);
      this.Controls.Add(this.pictureBox1);
      this.Controls.Add(this.button2);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.MDS);
      this.Controls.Add(this.chart4);
      this.Controls.Add(this.chart2);
      this.Controls.Add(this.chart1);
      this.Name = "Form1";
      this.Text = "Form1";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart2)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.chart4)).EndInit();
      ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
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
    private System.Windows.Forms.Button button2;
    private System.Windows.Forms.PictureBox pictureBox1;
    private System.Windows.Forms.ComboBox comboBox1;
    private System.Windows.Forms.Label label1;
  }
}


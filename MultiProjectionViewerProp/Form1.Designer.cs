﻿namespace ClassCppToCS_CS
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
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea3 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend3 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.MDS = new System.Windows.Forms.Button();
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.openCFGDialog = new System.Windows.Forms.OpenFileDialog();
      this.button2 = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.button3 = new System.Windows.Forms.Button();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
      this.SuspendLayout();
      // 
      // chart1
      // 
      chartArea3.Name = "ChartArea1";
      this.chart1.ChartAreas.Add(chartArea3);
      legend3.Name = "Legend1";
      this.chart1.Legends.Add(legend3);
      this.chart1.Location = new System.Drawing.Point(12, 93);
      this.chart1.Name = "chart1";
      series3.ChartArea = "ChartArea1";
      series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series3.LabelToolTip = "#SERIESNAME";
      series3.Legend = "Legend1";
      series3.Name = "Series1";
      series3.ToolTip = "#SERIESNAME";
      this.chart1.Series.Add(series3);
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
      this.MDS.Text = "MDS";
      this.MDS.UseVisualStyleBackColor = true;
      this.MDS.Click += new System.EventHandler(this.MDS_Click);
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
      this.button2.Location = new System.Drawing.Point(467, 64);
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
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(644, 460);
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
  }
}


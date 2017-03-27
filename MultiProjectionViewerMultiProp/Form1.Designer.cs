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
      System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
      System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
      System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
      this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
      this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
      this.openCFGDialog = new System.Windows.Forms.OpenFileDialog();
      this.button2 = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.button9 = new System.Windows.Forms.Button();
      this.button1 = new System.Windows.Forms.Button();
      this.controlpoints_state = new System.Windows.Forms.CheckBox();
      this.label4 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
      this.SuspendLayout();
      // 
      // chart1
      // 
      chartArea1.Name = "ChartArea1";
      this.chart1.ChartAreas.Add(chartArea1);
      legend1.Name = "Legend1";
      this.chart1.Legends.Add(legend1);
      this.chart1.Location = new System.Drawing.Point(12, 78);
      this.chart1.Name = "chart1";
      series1.ChartArea = "ChartArea1";
      series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
      series1.LabelToolTip = "#SERIESNAME";
      series1.Legend = "Legend1";
      series1.Name = "Series1";
      series1.ToolTip = "#SERIESNAME";
      this.chart1.Series.Add(series1);
      this.chart1.Size = new System.Drawing.Size(620, 371);
      this.chart1.TabIndex = 0;
      this.chart1.Text = "1";
      this.chart1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.chart_MouseDown);
      this.chart1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.chart_MouseMove);
      this.chart1.MouseUp += new System.Windows.Forms.MouseEventHandler(this.chart_MouseUp);
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
      this.button2.Location = new System.Drawing.Point(176, 12);
      this.button2.Name = "button2";
      this.button2.Size = new System.Drawing.Size(115, 23);
      this.button2.TabIndex = 7;
      this.button2.Text = "Inverse Projection";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Click += new System.EventHandler(this.btn_inverseprojection_click);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(423, 38);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(28, 13);
      this.label1.TabIndex = 10;
      this.label1.Text = " Log";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Location = new System.Drawing.Point(12, 38);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(39, 13);
      this.label2.TabIndex = 14;
      this.label2.Text = " Model";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Location = new System.Drawing.Point(12, 60);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(30, 13);
      this.label3.TabIndex = 15;
      this.label3.Text = " Size";
      // 
      // button9
      // 
      this.button9.Location = new System.Drawing.Point(297, 12);
      this.button9.Name = "button9";
      this.button9.Size = new System.Drawing.Size(123, 23);
      this.button9.TabIndex = 28;
      this.button9.Text = "LAMP";
      this.button9.UseVisualStyleBackColor = true;
      this.button9.Click += new System.EventHandler(this.btn_lamp_click);
      // 
      // button1
      // 
      this.button1.Location = new System.Drawing.Point(12, 12);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(158, 23);
      this.button1.TabIndex = 29;
      this.button1.Text = "Call MDS multiprop with CFG";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new System.EventHandler(this.CallMDSWithMultiPropAndCFG);
      // 
      // controlpoints_state
      // 
      this.controlpoints_state.AutoSize = true;
      this.controlpoints_state.Location = new System.Drawing.Point(426, 18);
      this.controlpoints_state.Name = "controlpoints_state";
      this.controlpoints_state.Size = new System.Drawing.Size(190, 17);
      this.controlpoints_state.TabIndex = 30;
      this.controlpoints_state.Text = "All Loaded Points as Control Points";
      this.controlpoints_state.UseVisualStyleBackColor = true;
      this.controlpoints_state.CheckedChanged += new System.EventHandler(this.controlpoints_state_CheckedChanged);
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Location = new System.Drawing.Point(116, 60);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(33, 13);
      this.label4.TabIndex = 31;
      this.label4.Text = "props";
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(638, 459);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.controlpoints_state);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.button9);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.button2);
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
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.Button button9;
    private System.Windows.Forms.Button button1;
    private System.Windows.Forms.CheckBox controlpoints_state;
    private System.Windows.Forms.Label label4;
  }
}


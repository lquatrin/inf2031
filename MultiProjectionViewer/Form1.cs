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

namespace ClassCppToCS_CS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
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


        private void MDS_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter =
            "Images (*.BMP;*.JPG;*.GIF)|*.BMP;*.JPG;*.GIF|" +
            "All files (*.*)|*.*";

            // Allow the user to select multiple images.
            openFileDialog1.Multiselect = true;
            openFileDialog1.Title = "My Image Browser";
            DialogResult result = openFileDialog1.ShowDialog();
            List<string> paths = new List<string>();
            if (result == DialogResult.OK) // Test result.
            {
                CppWrapper.CppHistogramWrapper histo = new CppWrapper.CppHistogramWrapper();
                int counter = 0;
                foreach (String file in openFileDialog1.FileNames)
                {
                    string files = openFileDialog1.InitialDirectory + file;
                    paths.Add(files);
                    counter++;
                }
                histo.addPath(paths.ToArray());
                double[,] array = histo.GetDistances();
                // printa array
                for (int i = 0; i < counter; i++)
                {
                    for (int j = 0; j < counter; j++)
                    {
                        
                        Console.Write(array[i, j]);
                        Console.Write(" | ");
                    }
                    Console.Write("\n");
                }
                CppWrapper.CppMDSWrapper mMDS = new CppWrapper.CppMDSWrapper(array, counter);
                double[,] arrayMDS = mMDS.GetMDS();

                //TO DO - refinar!
                for (int i = 0; i < counter; i++)
                {
        
                        chart1.Series["Series1"].Points.AddXY(arrayMDS[i, 0], arrayMDS[i, 1]);
                    
                }
            }
        }
    }
}

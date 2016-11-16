using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

using Emgu.CV;
using Emgu.Util;
using Emgu.CV.UI;


namespace Lamp
{
  public class AlgLAMP
  {
    public AlgLAMP()
    {
      
    }

    public static void Test ()
    {
      //Matrix<float> md = new Matrix<float>(10, 3);
      //md[0,0] = 1;

      double[,] d = new double[10, 3] { {1,2,3}, {3,2,1}, {4,5,6}, {2,3,4},
           {4,3,2}, {6,8,9}, {2,4,6}, {1,9,5}, {1,3,9}, {9,8,7} };
      
      int[] idx = new int[3] { 1, 5, 9 };
      
      double[,] arr_ys = new double[3, 2] { { 4, 9 }, { 1, 1 }, { 9, 6 } };
      
      Emgu.CV.Matrix<double> X = new Emgu.CV.Matrix<double>(d);
      Emgu.CV.Matrix<double> Ys = new Emgu.CV.Matrix<double>(arr_ys);

      Console.WriteLine("TESTANDO");
      
      Emgu.CV.Matrix<double> Y = AlgLAMP.LAMP(X, idx, Ys);
    }

    public static Emgu.CV.Matrix<double> LAMP(Emgu.CV.Matrix<double> X, int[] idx, Emgu.CV.Matrix<double> Ys) 
    {

      //if (!s_CheckInputErrorsLAMP(X, cp_index, Ys)) {
      //  fprintf(stderr, "ERROR: lamp - Invalid input.\n");
      //  return Mat::zeros(1, 1, CV_8UC1);
      //}
      
      double tol = 1E-003;
      
      // Building an array with the indices of the points to be projected.
      //std::vector<int> proj_idx(X.rows);
      //for (int i = 0; i < X.rows; ++i)
      //  proj_idx[i] = i;
      //for (int i = 0; i < cp_index.size(); ++i)
      //  proj_idx[cp_index[i]] = -1;
      //
      
      // Building the control points and projected points matrices.
      Emgu.CV.Matrix<double> Xs = new Emgu.CV.Matrix<double>(idx.Length, X.Cols);
      Xs.SetZero();
      
      Emgu.CV.Matrix<double> Y = new Emgu.CV.Matrix<double>(X.Rows, Ys.Cols);
      Y.SetZero();

      //for (int i = 0; i < Xs.rows; ++i) {
      //  X.row(cp_index[i]).copyTo(Xs.row(i));
      //  Ys.row(i).copyTo(Y.row(cp_index[i]));
      //}
      //
      //Mat alpha = Mat::zeros(1, cp_index.size(), CV_32FC1);
      //for (int i = 0; i < X.rows; ++i) {
      //  if (proj_idx[i] == -1)
      //    continue;
      //
      //  // Building the weights of each control point over the current point.
      //  for (int j = 0; j < cp_index.size(); ++j)
      //    alpha.at<float>(0, j) = 1 / cv::max(cv::norm(Xs.row(j), X.row(proj_idx[i])), tol);
      //
      //  float sum_alpha = cv::sum(alpha)[0];
      //
      //  Mat T = Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
      //  for (int k = 0; k < Xs.cols; ++k)
      //    T.col(k) = Xs.col(k).mul(alpha.t());
      //
      //  // Building the x-tilde and y-tilde variables (Eq. 3).
      //  Mat Xtil;
      //  cv::reduce(T, Xtil, 0, CV_REDUCE_SUM);
      //  Xtil = Xtil * (1 / sum_alpha);
      //
      //  T = Mat::zeros(Ys.rows, Ys.cols, Ys.depth());
      //  for (int k = 0; k < Ys.cols; ++k)
      //    T.col(k) = Ys.col(k).mul(alpha.t());
      //
      //  Mat Ytil;
      //  cv::reduce(T, Ytil, 0, CV_REDUCE_SUM);
      //  Ytil = Ytil * (1 / sum_alpha);
      //
      //  // Building the x-hat and y-hat variables (Eq. 4).
      //  Mat Xhat = Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
      //  for (int k = 0; k < Xs.rows; ++k)
      //    Xhat.row(k) = Xs.row(k) - Xtil;
      //
      //  Mat Yhat = Mat::zeros(Ys.rows, Ys.cols, Ys.depth());
      //  for (int k = 0; k < Ys.rows; ++k)
      //    Yhat.row(k) = Ys.row(k) - Ytil;
      //
      //  // Building the A and B matrices (Eq. 6) and calculating the SVD of t(A) * B.
      //  Mat sqrt_alpha;
      //  cv::sqrt(alpha, sqrt_alpha);
      //  sqrt_alpha = sqrt_alpha.t();
      //
      //  Mat A;
      //  Xhat.copyTo(A);
      //  for (int k = 0; k < A.cols; ++k)
      //    A.col(k) = A.col(k).mul(sqrt_alpha);
      //
      //  Mat B;
      //  Yhat.copyTo(B);
      //  for (int k = 0; k < B.cols; k++)
      //    B.col(k) = B.col(k).mul(sqrt_alpha);
      //
      //  cv::SVD udv(A.t() * B);
      //
      //  // Calculating the affine transform matrix (Eq. 7).
      //  Mat M = udv.u * udv.vt;
      //
      //  // Projecting X[i] using the matrix M (Eq 8)
      //  Y.row(proj_idx[i]) = (X.row(proj_idx[i]) - Xtil) * M + Ytil;
      //}
      return Y;
    }
  }
}

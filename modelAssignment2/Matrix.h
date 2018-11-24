class Matrix
{
public:
  Matrix();
  void static initilzeMatrix(double **m,int numOfRows,int numOfColumns);
  void static transposeMatrix(double **m, int numOfRows, int numOfColumns,double **r);
  void static MatrixMultiplication(double **A,int order,double **B,double **result);
  void static MatrixInversion(double **A, int order, double **Y);
  int static GetMinor(double **src, double **dest, int row, int col, int order);
  double static CalcDeterminant( double **mat, int order);

};
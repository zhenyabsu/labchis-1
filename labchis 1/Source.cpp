#include<iostream>
using std::cout;
const int n = 3;
void print(double a[][3], double b[], int n) {
	cout << "\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << a[i][j] << "  ";
		}
		cout << "|  " << b[i] << "\n";
	}
}
void find_main(double matrix[][3], int indexes[], int SE)
{
	//find max
	int index_i = 0;
	int index_j = 0;
	double buf;
	double main_element = matrix[SE][SE];
	for (int i = SE; i < n; i++)
	{
		for (int j = SE; j < n; j++)
		{
			if (matrix[i][j] > main_element)
			{
				main_element = matrix[i][j];
				index_i = i;
				index_j = j;
			}
		}
	}
	//permutation lines
	if (index_i != SE)
	{
		for (int j = SE; j < n; j++)
		{
			buf = 0;
			buf = matrix[SE][j];
			matrix[SE][j] = matrix[index_i][j];
			matrix[index_i][j] = buf;
		}
	}
	//permutation row
	if (index_j != SE)
	{
		for (int i = SE; i < n; i++)
		{
			buf = 0;
			buf = matrix[i][SE];
			matrix[i][SE] = matrix[i][index_j];
			matrix[i][index_j] = buf;
			buf = indexes[SE];
			indexes[SE] = indexes[index_j];
			indexes[index_j] = buf;
		}
	}
}
int main()
{
	int SE;
	double buf;
	int indexes[n] = { 0,1,2 };
	double matrix_A[n][n] =
	{ 2.30, 5.70, -0.80, 3.50, -2.70, 5.30, 1.70, 2.30, -1.80 };
	double matrix_b[n] = { -6.49, 19.20, -5.09 };
	//
	print(matrix_A, matrix_b, n);
	//1		
	SE = 0;
	find_main(matrix_A, indexes, SE);
	cout << "\nFind main element for first step\n";
	print(matrix_A, matrix_b, n);
	if (matrix_A[0][0] != 1) {
		double c = matrix_A[0][0];
		matrix_b[0] /= c;

		for (int j = 0; j < n; j++) {
			matrix_A[0][j] /= c;
		}
	}
	//
	cout << "\n";
	print(matrix_A, matrix_b, n);
	//2
	for (int i = 1; i < n; i++) {
		if (matrix_A[i][0] != 0) {
			double c = matrix_A[i][0];
			matrix_b[i] -= c * matrix_b[0];
			for (int j = 0; j < n; j++) {
				matrix_A[i][j] -= c * matrix_A[0][j];
			}
		}
	}
	//
	print(matrix_A, matrix_b, n);
	//3
	SE = 1;
	find_main(matrix_A, indexes, SE);
	cout << "\nFind main element for second step\n";
	print(matrix_A, matrix_b, n);
	if (matrix_A[1][1] != 1) {
		double c = matrix_A[1][1];
		matrix_b[1] /= c;
		for (int j = 0; j < n; j++) {
			matrix_A[1][j] /= c;
		}
	}
	//4
	if (matrix_A[n - 1][1] != 0) {
		double c = matrix_A[2][1];
		matrix_b[2] -= c * matrix_b[1];
		for (int j = 1; j < n; j++) {
			matrix_A[2][j] -= c * matrix_A[1][j];
		}
	}
	//
	print(matrix_A, matrix_b, n);
	SE = 3;
	find_main(matrix_A, indexes, SE);
	cout << "\nFind main element for first step\n";
	print(matrix_A, matrix_b, n);
	//5
	if (matrix_A[2][2] != 1) {
		double c = matrix_A[2][2];
		matrix_b[2] /= c;
		matrix_A[2][2] /= c;
	}
	//
	print(matrix_A, matrix_b, n);
	////обратный метод
	double an[n];
	/*for (int i = 0; i < 3; i++)
	{
		if(indexe)
	}*/
	an[indexes[2]] = matrix_b[2];
	an[indexes[1]] = matrix_b[1] - an[indexes[2]] * matrix_A[1][2];
	an[indexes[0]] = matrix_b[0] - an[indexes[1]] * matrix_A[0][1] - an[indexes[2]] * matrix_A[0][2];
	cout << "\n" << "x1 = " << an[indexes[0]] << ", x2  = " << an[indexes[1]] << ", x3 = " << an[indexes[2]] << "\n";
	//
	double matrix_A_2[n][n] =
	{ 2.30, 5.70, -0.80, 3.50, -2.70, 5.30, 1.70, 2.30, -1.80 };

	//
	double matrix_F[n];
	//calculating F = Ax-b
	double matrix_Ax[n];
	double matrix_b_2[n] = { -6.49, 19.20, -5.09 };
	for (int I = 0; I < n; I++)
	{
		buf = 0;
		for (int J = 0; J < n; J++)
		{
			buf += matrix_A_2[I][J] * an[J];
		}
		matrix_Ax[I] = buf;
		buf -= matrix_b_2[I];
		matrix_F[I] = buf;
	}
	cout << "\nVector Of Discrepancy F:\n";
	for (int i = 0; i < n; i++)
	{
		cout << matrix_F[i] << "\n";
	}
	//Find norm
	int maxIndex = 0;
	for (int i = 0; i < n; ++i)
	{
		if (fabs(matrix_F[i]) > fabs(matrix_F[maxIndex]))
		{
			maxIndex = i;
		}
	}
	cout << "\nNorm of Vector Of Discrepancy:\n d = " << matrix_F[maxIndex];
	cout << "\nError:\n";
	double error;
	/// Calculating xn~~ Ax=Ax~

	if (matrix_A_2[0][0] != 1) {
		double c = matrix_A_2[0][0];
		matrix_Ax[0] /= c;

		for (int j = 0; j < n; j++) {
			matrix_A_2[0][j] /= c;
		}
	}
	//2
	for (int i = 1; i < n; i++) {
		if (matrix_A_2[i][0] != 0) {
			double c = matrix_A_2[i][0];
			matrix_Ax[i] -= c * matrix_Ax[0];
			for (int j = 0; j < n; j++) {
				matrix_A_2[i][j] -= c * matrix_A_2[0][j];
			}
		}
	}
	//3
	if (matrix_A_2[1][1] != 1) {
		double c = matrix_A_2[1][1];
		matrix_Ax[1] /= c;
		for (int j = 0; j < n; j++) {
			matrix_A_2[1][j] /= c;
		}
	}
	//4
	if (matrix_A_2[n - 1][1] != 0) {
		double c = matrix_A_2[2][1];
		matrix_Ax[2] -= c * matrix_Ax[1];
		for (int j = 1; j < n; j++) {
			matrix_A_2[2][j] -= c * matrix_A_2[1][j];
		}
	}
	//5
	if (matrix_A_2[2][2] != 1) {
		double c = matrix_A_2[2][2];
		matrix_Ax[2] /= c;
		matrix_A_2[2][2] /= c;
	}
	////обратный метод
	double xx[n];
	xx[2] = matrix_Ax[2];
	xx[1] = matrix_Ax[1] - xx[2] * matrix_A_2[1][2];
	xx[0] = matrix_Ax[0] - xx[1] * matrix_A_2[0][1] - xx[2] * matrix_A_2[0][2];
	/// x~~-x~
	for (int i = 0; i < n; i++)
	{
		xx[i] -= an[i];
	}
	//Find norm
	maxIndex = 0;
	for (int i = 0; i < n; ++i)
	{
		if (fabs(xx[i]) > fabs(xx[maxIndex]))
		{
			maxIndex = i;
		}
	}
	double errorU = xx[maxIndex];
	maxIndex = 0;
	for (int i = 0; i < n; ++i)
	{
		if (fabs(an[i]) > fabs(an[maxIndex]))
		{
			maxIndex = i;
		}
	}
	double errorD = an[maxIndex];
	error = abs(errorU / errorD);
	cout << "b = " << error;
	return 0;
}
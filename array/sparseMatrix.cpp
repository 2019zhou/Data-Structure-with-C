#include "sparsematrices.h"

int main()
{
	//读入数据, 初始化在乘，加中需要用到的三元组表
	//请在input文件中使用tab键分割相邻的两个元素
	sparsematrices matrix_l("input.txt");
	sparsematrices matrix_r("input2.txt");

	//test
	//cout << matrix_l.getrow() << ends << matrix_l.getcol() << endl;
	//cout << matrix_r.getrow() << ends << matrix_r.getcol() << endl;
	//cout << matrix_l.getlen() << endl;

	matrix_l.displaytable();
	matrix_r.displaytable();

	matrix_l.display();
	matrix_r.display();

	//矩阵的转置
	/*matrix_l.transposematrix();
	matrix_l.displaytable();*/

	//矩阵相加
	//matrix_l.addmatrix(matrix_r);
	//matrix_l.displaytable();

	//矩阵相减
	//matrix_l.submatrix(matrix_r);
	//matrix_l.displaytable();

	//矩阵相乘
	sparsematrices matrixnew;
	matrix_l.mulmatrix(matrix_r, matrixnew);
	matrixnew.displaytable();
	matrixnew.display();
	return 0;
}
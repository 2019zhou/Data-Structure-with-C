#pragma once
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <istream>
#include <string>
using namespace std;
const int maxsize = 100;	//此处定义的是三元组表的三元组对象的数目
constexpr auto roww = 50;

//一个三元组
struct elements
{
	int row;	//这里约定数组的下表从0开始
	int col;
	int e;
};

//三元组表
class sparsematrices
{
private:
	int row;	//行总数
	int col;	//列总数
	int len;	//非零元个数
public:
	//构造函数
	sparsematrices(const char* file); //包括初始化，导入数据的部分
	sparsematrices() { row = 0; col = 0; len = 0; e = new elements[maxsize]; }
	//有关操作
	elements * e;
	int getrow() { return row; };
	int getcol() { return col; };
	int getlen() { return len; };
	void displaytable();
	void display();
	void transposematrix();	//矩阵的转置
	void addmatrix(sparsematrices matrix2);
	void submatrix(sparsematrices matrix2);
	void mulmatrix(sparsematrices matrix1, sparsematrices& matrixnew);
	static bool cmpcol(elements a, elements b) {
		return a.col < b.col;
	}
};



sparsematrices::sparsematrices(const char* file)
{
	//获取行数
	row = 0;
	ifstream f1;
	f1.open(file, ios::in);
	string temp;
	while (getline(f1, temp, '\n'))
	{
		if (temp.size() > 0)
			row++;
	}
	f1.close();
	//获取列数
	col = 0;
	ifstream f2;
	f2.open(file, ios::_Nocreate);
	while (f2.peek() != '\n') {
		f2.get();
		col++;
	}
	col = (col + 1) / 2;
	f2.close();
	//初始化有关数据
	e = new elements[maxsize];
	len = 0;
	ifstream f3;
	int count = 0;
	f3.open(file, ios::in);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col;) {			//开始这里的j的循环条件设置错误
			if (f3.peek() == '0') {
				f3.get();
				j++;
			}
			else if (f3.peek() == '\n') {
				f3.get();
			}
			else if (f3.peek() == '\t') {
				f3.get();
			}
			else {
				e[len].row = i;
				e[len].col = j;
				f3 >> e[len].e;
				len++;
				j++;
			}
		}
	}
}



void sparsematrices::displaytable()
{
	cout << "ROW\t" << "COLUMN\t" << "DATA" << endl;
	for (int i = 0; i < len; i++)
		cout << e[i].row << "\t" << e[i].col << "\t" << e[i].e << endl;
	cout << "--------------------" << endl;
}



void sparsematrices::transposematrix()
{
	for (int i = 0; i < len; i++)
		swap(e[i].col, e[i].row);
	sort(e, e + len, cmpcol);
}



void sparsematrices::display()
{
	int num = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (num < len && i == e[num].row && j == e[num].col) {
				cout << e[num].e << "\t";
				num++;
			}
			else cout << "0\t";
		}
		cout << endl;
	}
}


void sparsematrices::addmatrix(sparsematrices matrix2)	//由于是按照顺序存储，故加法效率可以提升
{
	if (row != matrix2.row || col != matrix2.col) {
		cout << "矩阵的行，列不合法" << endl;
		exit(0);
	}
	else {
		int len2 = matrix2.getlen();
		for (int i = 0; i < len; i++)
			for (int j = 0; j < len2; j++)
			{
				//cout << e[i].row << ends << matrix2.e[j].row << 
				if (e[i].row == matrix2.e[j].row && e[i].col == matrix2.e[j].col)
					e[i].e += matrix2.e[j].e;
				if (e[i].row < matrix2.e[j].row) break;
			}
	}
}


void sparsematrices::submatrix(sparsematrices matrix2)
{
	if (row != matrix2.row || col != matrix2.col) {
		cout << "矩阵的行，列不合法" << endl;
		exit(0);
	}
	else {
		int len2 = matrix2.getlen();
		for (int i = 0; i < len; i++)
			for (int j = 0; j < len2; j++)
			{
				if (e[i].row == matrix2.e[j].row && e[i].col == matrix2.e[j].col)
					e[i].e -= matrix2.e[j].e;
				if (e[i].row < matrix2.e[j].row) break;
			}
	}
}

void sparsematrices::mulmatrix(sparsematrices matrix1, sparsematrices& matrixnew)
{
	if (row != matrix1.col || col != matrix1.row)
	{
		cout << "矩阵的行列不合法" << endl;
		exit(0);
	}
	matrixnew.row = row;
	matrixnew.col = matrix1.col;
	matrixnew.len = 0;

	int reference[50] = { -1 };
	int count = 0;
	if (len >= 1) {
		reference[0] = 0;
		count = 1;
	}
	for (int i = 1; i < len; i++) {
		if (e[i].row != e[i - 1].row) {
			reference[count++] = i;
		}
	}

	cout << endl;
	//具体计算稀疏矩阵
	int num = 0;
	int m = 0;
	int ctemp[roww] = { 0 };
	if (len * matrix1.len != 0) {
		for (int i = 0; i < row; i++){	//处理this matrix中的每一行数据
			memset(ctemp, 0, sizeof(ctemp));	//数组清零
			m = reference[i];  //m存row开始的位置
			if (m == -1)  continue;//如果发现第一个矩阵第i行没有非0元素，下一循环
			//计算matrixnew中i行的积并存入ctemp[]中
			do {
				for (int k = 0; k < matrix1.getlen(); k++) {
					if (matrix1.e[k].row == e[m].col){
						ctemp[matrix1.e[k].col] += matrix1.e[k].e * e[m].e;
					}
				 }
				m++;
			} while (e[m].row == e[m - 1].row);
			//将ctemp[]中的非零元压缩存储
			for (int j = 0; j < row; j++){
				if (ctemp[j]){
					matrixnew.e[num].e = ctemp[j];
					matrixnew.e[num].row = i;
					matrixnew.e[num].col = j;
					matrixnew.len++;
					num++;
					//matrixnew.displaytable();
				}
			}
		}

	}
}
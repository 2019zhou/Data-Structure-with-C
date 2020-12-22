// 数组 管理系统
//输入10个职工的信息，每个职工含有成员名为“职工号、姓名、基本工资、生活补贴、水电费、房租、实发工资、工资排名”，分别编写六个函数求：
//(1)输入一个职工的职工号，查询该职工的信息并输出，若不存在显示没找到。
//(2)输入一个新职工的信息，按职工号顺序将该职工的信息插入后输出。
//(3)输入一个已存在职工的姓名信息，删除该职工的信息后输出。
//(4)求每个职工的实发工资（实发工资 = 基本工资 + 生活补贴 - 水电费 - 房租）；
//(5)求所有职工基本工资、生活补贴、水电费、房租、实发工资的总和并输出；
//(6)对所有职工的信息按实发工资升序排序，并填写工资排名后输出；
//要求：
//10个职工的数据用文件存储，每个工人的结构体用数组和单链表。当程序执行后先显示“菜单”，输入为1时，执行第（1）个函数；输入为2时，执行第（2）个函数；输入为3时，执行第（3）个函数；输入为4时，执行第（4）个函数；输入为5时，执行第（5）个函数；输入为6时，执行第（6）个函数；当输入为7时，退出系统，当输入其他数字时，提示输入有错误。

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

int number = 10;
const int row = 8;
void menu();
void search();	//查找员工基本信息
void add();		//添加员工信息
void deleting();//删除员工信息
void InforTable();//职工的实发工资信息表(被其他调用的)
void InforTablePLUS();// 一个功能部件:实发工资信息表
void Statistic();//员工的各项工资总和
void SortTable();//员工的职工工资排序表
void display(int i); //用于方便展示单条信息
void GOSERACH();//询问是否需要继续查询
void Import();//载入所有员工信息

class staff { //职工号、姓名、基本工资、生活补贴、水电费、房租、实发工资、工资排名
public:
	int number;
	string name;
	double WageBasic;	//基本工资
	double Welfare;		//生活补贴
	double Utilities;	//水电费
	double Rent;		//房租
	double WageReal;	//实发工资
	int WageRank;		//工资排名
	staff() {
		number = 0;
		name = "LI";
		WageBasic = 0;
		Welfare = 0;
		Utilities = 0;
		Rent = 0;
		WageReal = 0;
		WageRank = 0;
	}
};

staff IMSTAFF[20];
int main()
{
	Import();
	menu();
	return 0;
}

void Import() {
	// import 10位员工的信息
	fstream f2;
	f2.open("SampleData.txt");
	if (f2) {
		for (int i = 0; i < number; ++i) {
			f2 >> IMSTAFF[i].number >> IMSTAFF[i].name >> IMSTAFF[i].WageBasic >> IMSTAFF[i].Welfare >> IMSTAFF[i].Utilities >> IMSTAFF[i].Rent;
		}

		//计算每位员工的实发工资，计算工资的排名，即属性,WageReal,WageRank  实发工资 = 基本工资 + 生活补贴 - 水电费 - 房租
		double RW[20] = { 0 };
		for (int i = 0; i < number; i++) {
			RW[i] = IMSTAFF[i].WageBasic + IMSTAFF[i].Welfare - IMSTAFF[i].Utilities - IMSTAFF[i].Rent;
			IMSTAFF[i].WageReal = RW[i];
		}
		int l = 0;
		sort(RW, RW + number);
		for (int k = 0; k < number && l < 10; k++) {
			for (int m = 0; m < number; m++)
				if (IMSTAFF[k].WageReal == RW[m]) {
					IMSTAFF[k].WageRank = m + 1;
					//cout << m + 1 << endl;  测试代码
					++l;
				}
		}

	//测试代码
	/*for (int i = 0; i < number; i++) {
		cout << IMSTAFF[i].number << ends << IMSTAFF[i].name << ends << IMSTAFF[i].WageBasic << ends << IMSTAFF[i].Utilities << ends << IMSTAFF[i].Welfare << ends;
		cout << IMSTAFF[i].Rent << ends << IMSTAFF[i].WageReal << ends << IMSTAFF[i].WageRank << endl;
	}*/
	}
	else {
		cerr << "打开文件失败！" << endl;
		exit(1);
	}
	f2.close();
}

void menu(){ //菜单栏的显示
	int choice;
	printf("*********************************************");
	printf("\n\t\t职工信息管理系统\n");
	cout << "\t(1)查询职工信息" << endl;
	cout << "\t(2)添加新职工信息" << endl;
	cout << "\t(3)删除已有职工" << endl;
	cout << "\t(4)职工的实发工资信息表" << endl;
	cout << "\t(5)职工各项工资统计" << endl;
	cout << "\t(6)职工工资排序表（按照实发工资）" << endl;
	cout << "\t\t请输入使用功能前的编号" << endl;
	printf("*********************************************\n");
	cin >> choice;
	switch (choice) {
	case 1:search(); break;	//查询职工信息
	case 2:add(); break;		//添加新职工信息
	case 3:deleting(); break;	//删除已有职工
	case 4:InforTablePLUS(); break;//职工的实发工资信息表
	case 5:Statistic(); break;	//职工各项工资统计
	case 6:SortTable(); break; //职工工资排序表（按照实发工资）
	default:cout << "输入有误，请重新输入" << endl;
	}
}

void search() {
	int n;
	cout << "请输入想要查询的员工编号" << endl;
	cin >> n;
	printf("┌──────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│编  号│姓    名│基本工资│生活补贴│水 电 费│房    租│实发工资│工资排名│\n");
	if (n <= number) {
		n = n--;
		display(n);
		printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	}
	else cout << "没有查询到有关员工信息" << endl;
	GOSERACH();
}

void add() {
	cout << "请输入该员工的基本信息：" << ends;
	cout << "包括如下六项，职工号、姓名、基本工资、生活补贴、水电费、房租" << endl;
	int n;
	cin >> n;
	if (n <= number) {
		cout << "员工编号重复" << endl;
		cout << "请重新输入员工信息" << endl;
		add();
	}
	number++;
	string name;
	double WageBasic = 0, Welfare = 0, Utility = 0, Rent = 0;
	cin >> name >> WageBasic >> Welfare >> Utility >> Rent;
	//将员工信息写入文件
	fstream f1;
	f1.open("SampleData.txt", ios::out | ios::app);//app表明是向文档末尾写信息
	if (f1) {
		f1 << endl << n << '\t' << name << '\t' << WageBasic << '\t' << Welfare << '\t' << Utility << '\t' << Rent << endl;
	}
	else {
		cerr << "打开文件失败！" << endl;
		exit(1);
	}
	f1.close();
	Import();
	InforTable();
	GOSERACH();
}

void deleting() {
	string name;
	cout << "请输入需要删除的姓名" << endl;
	cin >> name;
	for (int j = 0; j < number; j++) {
		if (name == IMSTAFF[j].name)
			//在文件中删除这个员工的信息,本质上是将后面的信息一行一行复制上来
		{
			fstream f3;
			f3.open("SampleData.txt");
			if (f3) {
			for (int k = j; k < number - 1; k++) {
				IMSTAFF[k] = IMSTAFF[k + 1]; //使用了类的复制
				//display(k);
			}
			for (int k = 0; k < number - 1; k++) {  //感觉输出文件仅仅是
				f3 << IMSTAFF[k].number << "\t" << IMSTAFF[k].name << "\t" << IMSTAFF[k].WageBasic << "\t";
				f3 << IMSTAFF[k].Welfare << "\t" << IMSTAFF[k].Utilities << "\t" << IMSTAFF[k].Rent << endl;
				//cout << "*" << endl;
				//display(k);
			}
			f3 << "\t\t\t\t\t\t\t\t" << endl;
			}
			else {
				cerr << "打开文件失败！" << endl;
				exit(1);
			}
			f3.close();
			number--;
			Import();
			InforTable();
			break;
		}
	}
	GOSERACH();
}
void InforTable() {	//职工号、姓名、基本工资、生活补贴、水电费、房租、实发工资、工资排名  8个值
	printf("┌──────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│编  号│姓    名│基本工资│生活补贴│水 电 费│房    租│实发工资│工资排名│\n");
	for (int i = 0; i < number; i++) {
		printf("├──────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
		printf("│%6d│", IMSTAFF[i].number);
		cout << setw(8) << IMSTAFF[i].name;
		printf("│%-8.2lf│%8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%8d│\n", IMSTAFF[i].WageBasic, IMSTAFF[i].Welfare, IMSTAFF[i].Utilities, IMSTAFF[i].Rent, IMSTAFF[i].WageReal,IMSTAFF[i].WageRank);	
	}
	printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
}

void InforTablePLUS() {
	InforTable();
	GOSERACH();
}

void SortTable() {
	printf("┌──────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│编  号│姓    名│基本工资│生活补贴│水 电 费│房    租│实发工资│工资排名│\n");
	for (int i = 0; i < number; i++) {
		for (int j = 0; j < number; j++)
			if (IMSTAFF[j].WageRank == i+1)
				display(j);
	}
	printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	GOSERACH();
}

void Statistic() { //基本工资、生活补贴、水电费、房租、实发工资的总和并输出
	InforTable();
	double Wage_sum = 0, Utility_sum = 0, Walfare_sum = 0, Rent_sum = 0, WageReal_sum = 0;
	for (int j = 0; j < number; j++) {
		Wage_sum += IMSTAFF[j].WageBasic;
		Utility_sum += IMSTAFF[j].Utilities;
		Rent_sum += IMSTAFF[j].Rent;
		Walfare_sum += IMSTAFF[j].Welfare;
		WageReal_sum += IMSTAFF[j].WageReal;  
	}
	printf("│  总和│\t│%-8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│        │\n", Wage_sum, Walfare_sum, Utility_sum, Rent_sum, WageReal_sum);
	printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	GOSERACH();
}

void display(int i) { // 用于展示单条信息
	printf("├──────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
	printf("│%6d│", IMSTAFF[i].number);
	cout << setw(8) << IMSTAFF[i].name;
	printf("│%-8.2lf│%8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%8d│\n", IMSTAFF[i].WageBasic, IMSTAFF[i].Welfare, IMSTAFF[i].Utilities, IMSTAFF[i].Rent, IMSTAFF[i].WageReal, IMSTAFF[i].WageRank);
}

void GOSERACH() {
	char c;
	cout << "是否需要继续查询" << endl;
	cin >> c;
	if (c == 'y') {
		system("cls");
		menu();
	}
	else return;
}
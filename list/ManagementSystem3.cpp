// 双链表 管理系统
// 输入10个职工的信息，每个职工含有成员名为“职工号、姓名、基本工资、生活补贴、水电费、房租、实发工资、工资排名”，分别编写六个函数求：
//(1)输入一个职工的职工号，查询该职工的信息并输出，若不存在显示没找到。
//(2)输入一个新职工的信息，按职工号顺序将该职工的信息插入后输出。
//(3)输入一个已存在职工的姓名信息，删除该职工的信息后输出。
//(4)求每个职工的实发工资（实发工资 = 基本工资 + 生活补贴 - 水电费 - 房租）；
//(5)求所有职工基本工资、生活补贴、水电费、房租、实发工资的总和并输出；
//(6)对所有职工的信息按实发工资升序排序，并填写工资排名后输出；
//要求：
//10个职工的数据用文件存储，每个工人的结构体用数组和链表。当程序执行后先显示“菜单”，输入为1时，执行第（1）个函数；输入为2时，执行第（2）个函数；输入为3时，执行第（3）个函数；输入为4时，执行第（4）个函数；输入为5时，执行第（5）个函数；输入为6时，执行第（6）个函数；当输入为7时，退出系统，当输入其他数字时，提示输入有错误。
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

void menu();
void search();	//查找员工基本信息
void add();		//添加员工信息
void deleting();//删除员工信息
void InforTable();//职工的实发工资信息表(被其他调用的)
void InforTablePLUS();// 一个功能部件:实发工资信息表
void Statistic();//员工的各项工资总和
void SortTable();//员工的职工工资排序表
void GOSEARCH();//询问是否需要继续查询
int number = 10;


bool cmp(double a, double b) {
	return a > b;
}

struct staff //职工号、姓名、基本工资、生活补贴、水电费、房租、实发工资、工资排名
{
	string name;
	double WageBasic;	//基本工资
	double Welfare;		//生活补贴
	double Utilities;	//水电费
	double Rent;		//房租
	double WageReal;	//实发工资
	int WageRank = 0;		//工资排名
};

struct Node	//建立所需的链表
{
	staff sta;
	int number;
	Node* pre;
	Node* next;
};

void display(Node*); //用于方便展示单条信息
Node* head = NULL;
Node* cur = head;

int main()
{
	ifstream fin("SampleData.txt");
	while (!fin.eof()) {
		Node* data = new Node;
		//读入数据
		fin >> data->number;
		fin >> data->sta.name >> data->sta.WageBasic >> data->sta.Welfare >> data->sta.Utilities >> data->sta.Rent;
		//添加至链表
		if (cur != NULL) {
			cur->next = data;
			data->pre = cur;
			data->next = NULL;
			cur = data;
		}
		else {
			data->next = NULL;
			data->pre = NULL;
			cur = data;
			head = cur;
		}
	}
	fin.close();

	//实发工资 = 基本工资 + 生活补贴 - 水电费 - 房租）
	double RW[20] = { 0 };
	int temp = 0;
	for (Node* p = head; p != NULL && temp <= 20; p = p->next) {
		p->sta.WageReal = p->sta.WageBasic + p->sta.Welfare - p->sta.Utilities - p->sta.Rent;
		RW[temp] = p->sta.WageReal;
		temp++;
	}

	//排序
	sort(RW, RW + number, cmp);
	int l = 0;
	for (Node* p = head; p != NULL && l <= 10; p = p->next) {
		for (int m = 0; m < number; m++)
			if (p->sta.WageReal == RW[m]) {
				p->sta.WageRank = m + 1;
				//cout << m + 1 << endl;  //测试代码
				++l;
			}
	}

	//测试代码
	/*int n = 0;
	for (Node* p = head->next; p != NULL && n <= 10; p = p->next) {
		cout << p->number << ends << p->sta.name << ends << p->sta.WageBasic << ends << p->sta.Utilities << ends << p->sta.Welfare << ends;
		cout << p->sta.Rent << ends << p->sta.WageReal << ends << p->sta.WageRank << endl;
		n++;
	}*/
	menu();
	return 0;
}

void menu() { //菜单栏的显示
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
	int cnt = 0;
	Node* p = head;
	for (; p != NULL; p = p->next) {
		if (p->number == n)
			break;
		cnt++;
	}
	if (cnt > number) {
		cout << "查询的员工编号不存在" << endl;
	}
	else {
		printf("┌──────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
		printf("│编  号│姓    名│基本工资│生活补贴│水 电 费│房    租│实发工资│工资排名│\n");
		printf("├──────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
		printf("│%6d│", p->number);
		cout << setw(8) << p->sta.name;
		printf("│%-8.2lf│%8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%8d│\n", p->sta.WageBasic, p->sta.Welfare, p->sta.Utilities, p->sta.Rent, p->sta.WageReal, p->sta.WageRank);
		printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	}
	GOSEARCH();
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
	// 插入链表
	Node* data = new Node;
	data->number = n;
	data->sta.name = name;
	data->sta.WageBasic = WageBasic;
	data->sta.Welfare = Welfare;
	data->sta.Utilities = Utility;
	data->sta.Rent = Rent;
	//添加至链表
	if (cur != NULL) {
		cur->next = data;
		data->pre = cur;
		data->next = NULL;
		cur = data;
	}
	else {
		data->next = NULL;
		data->pre = NULL;
		cur = data;
		head = cur;
	}
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
	number++;
	InforTable();
	GOSEARCH();
}

void deleting() {
	string name;
	cout << "请输入需要删除的姓名" << endl;
	cin >> name;
	int cnt = 0;
	Node* p = head;
	while (p != NULL) {
		if (p->next->sta.name == name)
			break;
		p = p->next;
		cnt++;
	}
	if (cnt >= number) {
		cout << "没有找到需要删除的姓名" << endl;
	}
	else {
		Node* q = p;
		q = p->next;
		p->next = q->next;
		number--;

		//删除文件中的数据
		fstream f3;
		f3.open("SampleData.txt");
		if (f3) {
			for (Node* f = head; f != NULL; f = f->next) {
				f3 << f->number << "\t" << f->sta.name << "\t" << f->sta.WageBasic << "\t";
				f3 << f->sta.Welfare << "\t" << f->sta.Utilities << "\t" << f->sta.Rent << endl;
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
		InforTable();
	}
	GOSEARCH();
}

void InforTable() {	//职工号、姓名、基本工资、生活补贴、水电费、房租、实发工资、工资排名  8个值
	printf("┌──────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│编  号│姓    名│基本工资│生活补贴│水 电 费│房    租│实发工资│工资排名│\n");
	for (Node* p = head; p != NULL; p = p->next) {
		printf("├──────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
		printf("│%6d│", p->number);
		cout << setw(8) << p->sta.name;
		printf("│%-8.2lf│%8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%8d│\n", p->sta.WageBasic, p->sta.Welfare, p->sta.Utilities, p->sta.Rent, p->sta.WageReal, p->sta.WageRank);
	}
	printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
}

void InforTablePLUS() {
	InforTable();
	GOSEARCH();
}

void SortTable() {
	printf("┌──────┬────────┬────────┬────────┬────────┬────────┬────────┬────────┐\n");
	printf("│编  号│姓    名│基本工资│生活补贴│水 电 费│房    租│实发工资│工资排名│\n");
	for (int i = 1; i <= number; i++) {
		for (Node* p = head; p != NULL; p = p->next)
			if (p->sta.WageRank == i)
				display(p);
	}
	printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	GOSEARCH();
}

void Statistic() { //基本工资、生活补贴、水电费、房租、实发工资的总和并输出
	InforTable();
	double Wage_sum = 0, Utility_sum = 0, Walfare_sum = 0, Rent_sum = 0, WageReal_sum = 0;
	for (Node* p = head; p != NULL; p = p->next) {
		Wage_sum += p->sta.WageBasic;
		Utility_sum += p->sta.Utilities;
		Rent_sum += p->sta.Rent;
		Walfare_sum += p->sta.Welfare;
		WageReal_sum += p->sta.WageReal;
	}
	printf("│  总和│\t│%-8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│        │\n", Wage_sum, Walfare_sum, Utility_sum, Rent_sum, WageReal_sum);
	printf("└──────┴────────┴────────┴────────┴────────┴────────┴────────┴────────┘\n");
	GOSEARCH();
}

void display(Node* f) { // 用于展示单条信息
	printf("├──────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤\n");
	printf("│%6d│", f->number);
	cout << setw(8) << f->sta.name;
	printf("│%-8.2lf│%8.2lf│%-8.2lf│%-8.2lf│%-8.2lf│%8d│\n", f->sta.WageBasic, f->sta.Welfare, f->sta.Utilities, f->sta.Rent, f->sta.WageReal, f->sta.WageRank);
}

void GOSEARCH() { //go search函数最好在末尾使用
	char c;
	cout << "是否需要继续查询" << endl;
	cin >> c;
	if (c == 'y') {
		system("cls");
		menu();
	}
	else return;
}
// 简单计算器
// 支持整数的加减乘除
#include <stdio.h>
#include <string.h>
const int MaxSize = 1005;
char OperatorStack[MaxSize];
double DataStack[MaxSize];
char inputExpr[1005];
char postExpr[1005];

//----------------------------------------------
//------------------操作数栈---------------------
class Numstack{
private:
	int cur;
public:
	Numstack() {
		cur = 0;
		for (int i = 0; i < MaxSize; i++) {
			DataStack[i] = 0;
		}
	}
	double top() {
		return DataStack[cur - 1];
	}
	void push(double x) {
		DataStack[cur] = x;
		cur++;
	}
	void pop() {
		if (cur <= 0)
			return;
		else {
			cur--;
		}
	}
	int size() {
		return cur;
	}
	bool empty() {
		return cur == 0;
	}
};
//----------------------------------------------
//----------------------------------------------
//------------------操作符栈---------------------
class Opstack {
private:
	int cur;
public:
	Opstack() {
		cur = 0;
		for (int i = 0; i < MaxSize; i++) {
			OperatorStack[i] = 0;
		}
	}
	char top() {
		return OperatorStack[cur - 1];
	}
	void push(char x) {
		OperatorStack[cur] = x;
		cur++;
	}
	void pop() {
		if (cur <= 0)
			return;
		else {
			cur--;
		}
	}
	int size() {
		return cur;
	}
	bool empty() {
		return cur == 0;
	}
};
//----------------------------------------------
// 转为后缀表达式
void trans() {
	Opstack op;
	int j = 0;
	for (int i = 0; inputExpr[i] != '\0'; i++) {
		switch (inputExpr[i]) {
		case '(': {
			op.push('(');
			break;
		}
		case ')': {
			while (op.top() != '(') {
				postExpr[j++] = op.top();
				op.pop();
			}
			op.pop();
			break;
		}
		case '+':
		case '-': {
			while (!op.empty()) {
				if (op.top() != '(') {
					postExpr[j++] = op.top();
					op.pop();
				}
				else {
					break;
				}
			}
			op.push(inputExpr[i]);
			break;
		}
		case '*':
		case '/': {
			while (!op.empty()) {
				if (op.top() == '*' || op.top() == '/') {
					postExpr[j++] = op.top();
					op.pop();
				}
				else {
					break;
				}
			}
			op.push(inputExpr[i]);
			break;
		}
		default:
			while (inputExpr[i] >= '0' && inputExpr[i] <= '9') {
				postExpr[j++] = inputExpr[i];
				if (inputExpr[i + 1] >= '0' && inputExpr[i + 1] <= '9')
					i++;
				else {
					postExpr[j++] = '#';
					break;
				}
					
			}
		}
		//printf("%s\n", postExpr);
	}
	while (!op.empty()) {
		postExpr[j++] = op.top();
		op.pop();
	}
	postExpr[j] = '\0';
}

//----------------------------------------------
// 计算后缀表达式的值
double calc() {
	Numstack ns;
	double num1, num2, num3, numtemp;
	for (int i = 0; postExpr[i] != '\0'; i++) {
		//如果是数字
		numtemp = 0;
		if (postExpr[i] >= '0' && postExpr[i] <= '9') {
			while (postExpr[i] >= '0' && postExpr[i] <= '9') {
				numtemp = numtemp * 10 + postExpr[i] - '0';
				i++;
			}
			ns.push(numtemp);
			//printf("%f\n", numtemp);
		}
		else {
			num2 = ns.top();
			ns.pop();
			num1 = ns.top();
			ns.pop();
			//printf("%f %f %c\n", num1, num2, postExpr[i]);
			switch (postExpr[i]) {
				case '+':
					num3 = num1 + num2;
					break;
				case '-':
					num3 = num1 - num2;
					break;
				case '*':
					num3 = num1 * num2;
					break;
				case  '/': {
					if (num2 == 0) {
						printf("\t cannot divide zero ERROR!\n");
						return -1;
					}
					else {
						num3 = num1 / num2;
					}
					break;
				}
			}
			ns.push(num3);
		}
	}
	return ns.top();
}



int main() {
	scanf("%s", &inputExpr);
	trans();
	printf("%s\n", inputExpr);
	printf("%s\n", postExpr);
	printf("%f\n", calc());

	return 0;
}

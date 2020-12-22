// 实现四种不同的排序算法
// 1. 插入排序
// 2. 选择排序
// 3. 冒泡排序
// 4. 快速排序
// 5. 归并排序

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

//为方便理解，这里的hi, mi, lo都是前闭后开区间

int a[20] = { 4, 2, 5, 1, 3 };

void merge(int lo, int mi, int hi);
void mergesorting(int lo, int hi)
{
	if (hi - lo < 2)return;
	int mi = (hi + lo) / 2;
	mergesorting(lo, mi);
	mergesorting(mi, hi);
	merge(lo, mi, hi);
}

void merge(int lo, int mi, int hi)
{
	int* A = a + lo;
	int lb = mi - lo;
	int lc = hi - mi;
	int* B = new int[lb];
	for (int i = 0; i < lb; i++) B[i] = A[i];
	int* C = a + mi;
	for (int i = 0, j = 0, k = 0; (j < lb) || (k < lc); ) {
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] <  B[j]))) A[i++] = C[k++];
	}
	delete[] B;
}

int partition(int lo, int hi);
void quicksorting(int lo, int hi)
{
	if (hi - lo < 2)return;
	int pivot = partition(lo, hi - 1);
	quicksorting(lo, pivot);
	quicksorting(pivot, hi);
}

int partition(int lo, int hi)
{
	swap(a[lo], a[lo + rand() % (hi - lo + 1)]);
	int pivot = a[lo];
	while (lo < hi)
	{
		while ((lo < hi) && pivot <= a[hi])hi--;
		a[lo] = a[hi];
		while ((lo < hi) && a[lo] <= pivot)lo++;
		a[hi] = a[lo];
	}
	a[lo] = pivot;
	return lo;
}


void insertsorting(int lo, int n){
	for (int i = 1; i < n; i++){
		int j = i - 1;
		int val = a[i];
		for (; j >= 0; j--){
			if (val < a[j]){
				a[j + 1] = a[j];
			}
			else
				break;
		}
		a[j+1] = val;
	}
}


void bubblesorting(int lo, int n)
{
	if (n < 2)
		return;
	for (int end = n - 1; n > 0; n--){
		for (int i = 0; i < end; i++){
			if (a[i] > a[i + 1]){
				swap(a[i], a[i+1]);
			}
		}
	}
}


void selectsorting(int lo, int n)
{
	if (n < 2)
		return;
	for (int i = 0; i < n; i++){
		int min = i;
		for (int j = i + 1; j < n; j++)
			min = a[min] < a[j] ? min : j;
		swap(a[i], a[min]);
	}
}


int main() {
	printf("未排序前序列");
	for (int i = 0; i < 5; i++)
		cout << a[i] << ends;
	cout << endl;
	printf("sorting methods: \n");
	string sort;
	cin >> sort;
	if(sort =="mergesort"){
		mergesorting(0, 5); 
		cout << "mergesort result:" << endl;
	}else if(sort =="quicksort"){
		quicksorting(0, 5); 
		cout << "quicksort result" << endl;
	}else if(sort == "bubblesort"){
		bubblesorting(0, 5);
		cout << "bubble sort result" << endl;
	}else if(sort == "insertsort"){
		insertsorting(0, 5);
		cout << "insert sort result" << endl;
	}else if(sort == "selectsort"){
		selectsorting(0, 5);
		cout << "select sort result" << endl;
	}
	for (int i = 0; i < 5; i++)
		cout << a[i] << ends;
	cout << endl;
	return 0;
}
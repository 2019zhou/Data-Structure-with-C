// 实现两种查找算法
// 1. 折半查找
// 2. 顺序查找
#include <iostream>
#include <string>
#include <cstdio>
using namespace std;


int a[20] ={1, 5, 9, 10, 10, 19};


int Search(int n, int key){
	for(int i = 0;i < n;i++){
		if(a[i] == key)
			return i;
	}
	return -1;
}

int BinarySearch(int n,int key){
    int low, high, mid;
    low=0;
    high=n-1;
    while(low <= high){
        mid = (low+high)/2;   
        if(a[mid]==key)     
            return mid;
        else if(a[mid]>key)        
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;      //查找失败返回-1
}


int main(){
	string method;
	
	for(int i  = 0;i < 6;i++){ 
		cout << a[i] <<" ";
	}
	cout << endl;
	cin >> method;
	printf("现在正在查找9\n");
	if(method == "search"){
		cout << "position" << Search(6, 9);
	}else if(method == "binarysearch"){
		cout << "position" << BinarySearch(6,9);
	}


	return 0;
}
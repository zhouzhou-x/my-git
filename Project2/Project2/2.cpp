#include <stdio.h>
#include <stdlib.h>
void shellSort(int* array, int m){
	int gap = m;
	while (gap > 1){
		gap = gap / 3 + 1;
		for (int i = 0; i < m - gap; i++){
			int end = i;
			int key = array[end + gap];
			while (end >= 0 && array[end] > key){
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}
}
void insretSort(int* array, int n){
	for (int i = 0; i < n - 1; i++){
		int end = i;
		int key = array[end + 1];
		while (end >= 0 && array[end] > key){
			array[end + 1] = array[end];
			--end;
		}
		array[end + 1] = key;
	}
}
void Myprintf(int* a, int num){
	for (int i = 0; i < num; i++){
		printf("%d ", a[i]);
	}
	printf("\n");
}
int main(){
	int arr[] = { 1, 5, 8, 3, 2, 4 };
	int arr1[] = { 2,5,8,1,4,6,8,3 };
	int num = sizeof(arr) / sizeof arr[0];
	int num1 = sizeof(arr1) / sizeof arr1[0];
	Myprintf(arr, num);
	insretSort(arr, num);
	Myprintf(arr, num);
	Myprintf(arr1, num1);
	shellSort(arr1, num1);
	Myprintf(arr1, num1);
	system("pause");
	return 0;
}
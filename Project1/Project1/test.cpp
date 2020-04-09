#include <stdio.h>
#include <stdlib.h>
void insretSort(int* array, int n){
	for (int i = 0; i < n - 1; i++){
		int end = i;
		int key = array[end + 1];
		while(end >= 0 && array[end] > key){
			array[end+1] = array[end];
			--end;
		}
		array[end+1] = key;
	}
}
void Myprintf(int* a,int num){
	for (int i = 0; i < num; i++){
		printf("%d ",a[i]);
	}
	printf("\n");
}
int main(){
	int arr[] = {1,5,8,3,2,4};
	int num = sizeof(arr) / sizeof arr[0];
	Myprintf(arr, num);
	insretSort(arr, num);
	Myprintf(arr, num);
	system("pause");
	return 0;
}
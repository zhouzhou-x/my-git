#include <stdio.h>
#include <windows.h>
void myprintf(int* array,int n){
	for (int i = 0; i < n; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}
void swap(int* array, int i, int j){
	int tpm = array[i];
	array[i] = array[j];
	array[j] = tpm;
}
void selectSort(int* array,int n){
	for (int i = n ; i > 0; i--){
		int start = n - i;
		int min = start;
		for (int j = n - i+1; j < n;j++){
			if (array[j] < array[min]){
				min = j;
			}
		}
		swap(array,start,min);
	}
}
void selectSort2(int* array, int n){//¸ü¸ßÐ§
	int start = 0;
	int end = n - 1;
	int max, min;
	while (start < end){
		max = min = start;
		for (int i = start + 1; i <= end;i++){
			if (array[i] >= array[max])
				max = i;
			if (array[i] < array[min])
				min = i;
		}
		swap(array,start,min);
		if (max == start)
			max = min;
		swap(array,end,max);
		--end;
		++start;
	}
}

int main(){
	int a[] = {1,5,3,4,8,7,3};
	int b[] = { 1, 5, 3, 4, 8, 7, 3, 2, -1 };
	myprintf(a, 7);
	selectSort(a,7);
	myprintf(a, 7);
	myprintf(b, 9);
	selectSort2(b, 9);
	myprintf(b, 9);
	system("pause");
	return 0;
}
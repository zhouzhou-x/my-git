#pragma warning(disable:4996)
#include<stdio.h>
#include<math.h>
int test(int n){
	if (n <= 2 || n >= 10000)
		return 0;
	for (int m=2; m < n; m++){
		if (m % 10 == 1){
			int flag = 1;
			for (int z = 2; z < m / 2 &&flag ==1; z++)
				if (m%z == 0){
					flag = 0;
			}
			if (flag != 0)
				printf("%d ", m);
		}
	}
	return -1;
}
int main(){
	int n;
	scanf("%d", &n);
	test(n);
	return 0;
}
#pragma warning(disable:4996)
#include <iostream>
#include <string>
using namespace std;
char* cur(char *str){
	int a = strlen(str);
	char* u = str;
	char b[10] = { 0 };
	char c[10] = { 0 };
	char d[10] = { 0 };
	int q = 0;
	int h = 0;
	int i = 0;
	for (i = 0; i < a / 2; i++){
		b[i] = *str++;
	}
	for (int j = a/2; j < a; j++){
		c[q] = *str++;
		q++;
	}
	while (i > 0){
		u[h] = c[i-1];
		i--;
		h++;
		u[h] = b[q-1];
		h++;
		q--;
	}
	strrev(u);
	return u;
}
void test(char* str){
	int a = *str;
	a -= 48;
	str++;
	while (a--){
		int b = *str;
		b -= 48;
		str++;
		int c = *str;
		c -= 48;
		str++;
		char w[100] = {0};
		for (int i = 0; i < 2 * b; i++){
			w[i] = *str++;
		}
		while (c--){
			cur(w);
		}
		for (int z = 0; z <2*b; z++){
			cout << w[z] <<"";
		}
		cout << endl;
	}
}
int main(){
	char n[10];
	cin >> n;
	test(n);
	system("pause");
	return 0;
}
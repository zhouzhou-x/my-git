//vector ����������ݵ�˳���--->��ģ��
//��������8��
//�ַ�Ϊ�ɶ���д �� �ɶ�
#include <vector>
#include <iostream>
using namespace std;
void test(){
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> v(arr, arr + 10);
	v.end();
}
int main(){
	test();
	system("pause");
	return 0;
}

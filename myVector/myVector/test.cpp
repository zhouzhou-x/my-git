//vector ����������ݵ�˳���--->��ģ��
//��������8��
//�ַ�Ϊ�ɶ���д �� �ɶ�
//�������
#include <vector>
#include <iostream>
using namespace std;
template <class T>
class Vector{
	Vector()
	:_start(nullptr)
	,_finish(nullptr)
	, _endofStorage(nullptr)
	{
	
	}
	size
private:
	T* _start;
	T* _finish;
	T* _endofStorage;



};
void test(){
	int arr[10] = { 0,1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> v(arr, arr + 10);
	cout << *(v.end()-1) <<endl;
}
int main(){
	test();
	system("pause");
	return 0;
}

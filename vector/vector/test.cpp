//vector 管理各种数据的顺序表--->类模板
//迭代器有8个
//粗分为可读的写 和 可读
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

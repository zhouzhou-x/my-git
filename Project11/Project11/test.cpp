#pragma warning(disable:4996)
#include <string>
#include <iostream>

class String{
public:
	//String��������ԭ��ָ��
	typedef char* iterator; 
	typedef const char* const_iterator;
	/*
	//�޲ι���
	String() 
		:_str(new char[1])
	{
		*_str = '\0';
	}
	//���ι���
	String(const char* str)
		:_str(new char[strlen(str)+1])//
	{
		strcpy(_str,str);
	}*/
	//ȫȱʡ
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _size(strlen(str))
		, _capacity(_size)	//��ε���strlen Ч�ʲ��зſ�������
	{
		strcpy(_str, str);
	}
	//��������
	String(const String& str)
		:_str(new char[strlen(str._str) + 1])//_str(str._capacity)
		, _size(str._size)
		, _capacity(str._capacity)
	{
		strcpy(_str, str._str);
	}
	//�ִ�д�� 
	String& operator=(const String& str)
	{
		if (this != &str){
			delete[] _str;
			_str = new char[strlen(str._str) + 1];//_str(str._capacity)
			strcpy(_str, str._str);
			_size = str._size;
			_capacity = str._capacity;
		}
		return *this;
	}
	char* c_str(){
		return _str;
	}
	~String(){
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
			_size = 0;
			_capacity = 0;
		}
	}
	//������opeartor[] + size    ������    ��Χfor
	//opertor[]
	char& operator[](size_t pos){//�ɶ���д����ȫ
		if (pos < _size){
			return _str[pos];
		}
	}
	size_t size(){
		return _size;
	}
	//������
	//������ָ���һ��ʹ��
	//�ɶ���д
	iterator begin()
	{
		return _str;
	}
	iterator end(){
		return _str + _size;
	}
	//ֻ��������
	const_iterator begin() const
	{
		return _str;
	}
	const_iterator end() const
	{
		return _str + _size;
	}
	//β���ַ�
	void pushback(const char ch){
		if (_size == _capacity){
			size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
			//����
			reserve(newC);
		}
		_str[_size++] = ch;
		_str[_size] = '\0';
	}
	void reserve(size_t n){
		if (n > _capacity){
			char* tmp = new char[n + 1];
			strcpy(tmp, _str);
			delete[]_str;
			_str = tmp;
			_capacity = n;
		}
	}
	//β���ַ���
	void pushBack(const char* str){
		int len = strlen(str);
		if (_size+len > _capacity){
			//����
			reserve(_size + len);
		}
		strcpy(_str + _size, str);
		_size += len;
	}
	String& operator+=(const char& ch){
		pushback(ch);
		return *this;
	}
	String& operator+=(const char* str){
		pushBack(str);
		return *this;
	}
	String& operator+=(const String& str)
	{
		pushBack(str._str);
		return *this;
	}
	//ָ��λ�ò���
	void insert(int pos,const char& ch)
	{
		if (pos <= _size){
			if (_size == _capacity){
				size_t newC = _capacity == 0 ? 15 : 2 * _capacity;
				reserve(newC);
			}
			size_t end = _size + 1;
			while (end > pos){
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			++_size;
		}
	}
	void insert(size_t pos, const char* str){
		int len = strlen(str);
		if (pos <= _size){
			if (_size + len > _capacity){
				reserve(_size+len);
			}
			size_t end = _size + len;
			while (end > pos+len-1){
				_str[end] = _str[end - len];
				--end;
			}
			for (int i = 0; i < len; i++){
				_str[pos + i] = str[i];
			}
			_size += len;
		}
	}
	//ɾ���ӿ�
	void erase(size_t pos, size_t len){
		if (pos + len >= _size){
			_size = pos;
			_str[_size] = '\0';
		}
		else {
			for (int i = pos + len; i <= _size; i++){
				_str[pos++] = _str[i];
			}
		}
		_size -= len;
	}
	//n<size �޸�size
	//size<n<capacity �޸� size + ��ֵ
	//n>capacity ����  �޸�size �Ӹ�ֵ
	void resize(size_t n,const char& ch){
		if(n > _capacity){
			reserve(n);
			}
		if (n > _size){
			memset(_str + _size, ch, n -_size);//�������
		}
		_size = n;
		_str[_size] = '\0';
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};
//��Χforfor(const auto& ch : str)
//�ײ���ǵ�����

void test(){
	//�����ʵ��ᴴ�����ַ���
	String str1 = "123445";
	String str2 = "123445";
	char* ptr = str1.c_str();
	char* ptr2 = str2.c_str();
	std::cout << ptr << std::endl;//�ַ���ָ�������ʱ�������ַ �������
	std::cout << ptr2 << std::endl;

}
void test1(){
	String str = "add";
	String str1(str);
	str1 = "132";
	char* ptr = str.c_str();
	char* ptr2 = str1.c_str();
	std::cout << ptr << std::endl;//�ַ���ָ�������ʱ�������ַ �������
	std::cout << ptr2 << std::endl;
}
void test2(){
	String str("123456");
	for (int i = 0; i < str.size(); i++){
		std::cout << str[i] << "";
	}
	std::cout << std::endl;
}
void test4(){
	String str("123456789");
	String::iterator it = str.begin();
	while (it != str.end()){
		std::cout << *it << "";
		++it;
	}
	std::cout << std::endl;
}
void test5(){
	String str("123456");
	str.pushback('a');
	std::cout << str.c_str() << std::endl;
	str.pushBack("asdf");
	std::cout << str.c_str() << std::endl;

}
void test6(){
	String str("123456");
	str += '1';
	std::cout << str.c_str() << "\n";
	str += "123456";
	std::cout << str.c_str() << "\n";
	str += String("adf");
	std::cout << str.c_str() << "\n";
	std::cout << "" << std::endl;
}
void test7(){
	String s;
	s.insert(0,"asd");
	std::cout << s.c_str() << '\n';
	s.insert(0, "asd");
	std::cout << s.c_str() << '\n';
	s.insert(1, "asd");
	std::cout << s.c_str() << '\n';
	s.insert(0, "asd");
	std::cout << s.c_str() << '\n';
	std::cout << "" << std::endl;
}
void test8(){
	String s("132456789");
	s.erase(0, 1);
	std::cout << s.c_str() << std::endl;
}
void test9(){
	String s("s222");
	s.resize(10,'a');
	std::cout << s.c_str() << std::endl;
}
int main(){
	test7();
	system("pause");
	return 0;
}

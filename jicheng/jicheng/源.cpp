#include <iostream>
#include <string>
using namespace std;
class Person
{
public:
	Person(int age = 18)
		:_age(age)
	{
		cout << "Person" << endl;
	}
	void Print()
	{
		cout << "name:" << _name << endl;
		cout << "age:" << _age << endl;
	}
private:
	int _age ; // ÄêÁä
};
class Student : public Person
{
public:
private:
	int _id = 2; // Ñ§ºÅ
};
int main()
{
	Student s;
	s.Print();
	return 0;
}
#include <string>
#include <iostream>
void test(){
	std::string s = "123456";
	std::cout << s.size() << std::endl;
	std::cout << s.length() << std::endl;
	std::cout << s.capacity() << std::endl;
	s.push_back('2');
	std::cout << s << std::endl;
	s.resize(30, 'b');
	std::cout << s << std::endl;
	std::cout << s.capacity() << std::endl;
	std::cout << s.size() << std::endl;
	s.resize(15, 'h');
	std::cout << s << std::endl;
	std::cout << s.capacity() << std::endl;
	std::cout << s.size() << std::endl;
}
void test1(){
	std::string str = "123";
	std::cout << str.size() << std::endl;
	std::cout << str.capacity() << std::endl;
	str.reserve(100);
	std::cout << str.size() << std::endl;
	std::cout << str.capacity() << std::endl;

}
void test2(){//±éÀú
	std::string ss = "321";
	for (int i = 0; i < ss.size(); i++){
		std::cout << ss[i] << " ";
	}
	std::cout << std::endl;
	for (int j = 0; j < ss.size(); j++){
		ss[j] = '8';
		std::cout << ss[j] << " ";
	}
	std::cout << std::endl;
	std::string sss = "465798";
	std::string::iterator it = sss.begin();
	while (it != sss.end()){
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	std::string ssss = "465798";
	std::string::iterator it1 = ssss.begin();
	while (it1 != ssss.end()){
		*it1 = '1';
		std::cout << *it1 << " ";
		++it1;
	}
	std::cout << std::endl;
	for (char c : ssss){
		std::cout << c << " ";
	}
	std::cout << std::endl;
}
void test3(){
	std::string s2 = "12345ss";
	std::string s3;
	std::string s4;
	std::string s5;
	std::string s6;
	std::string s7;
	s2.append("asdasd");
	for (int i = 0; i < s2.size(); i++){
		std::cout << s2[i] << " ";
	}
	std::cout << std::endl;
	s3.append(s2);
	for (int i = 0; i < s2.size(); i++){
		std::cout << s2[i] << " ";
	}
	std::cout << std::endl;
	s4.append(s2,3,1);
	for (int i = 0; i < s4.size(); i++){
		std::cout << s4[i] << " ";
	}
	std::cout << std::endl;
	s5.append("asdasd",2);
	for (int i = 0; i < s5.size(); i++){
		std::cout << s5[i] << " ";
	}
	std::cout << std::endl;
	s6.append(5,'a');
	for (int i = 0; i < s6.size(); i++){
		std::cout << s6[i] << " ";
	}
	std::cout << std::endl;
	s7.append(s2.begin()+1,s2.end());
	for (int i = 0; i < s7.size(); i++){
		std::cout << s7[i] << " ";
	}
	std::cout << std::endl;
}
void test4(){
	std::string s2 = "12345ss";
	std::string s3 = "12345ss";
	s2 += '2';
	for (int i = 0; i < s2.size(); i++){
		std::cout << s2[i] << " ";
	}
	std::cout << std::endl;
	s2 += "123";
	for (int i = 0; i < s2.size(); i++){
		std::cout << s2[i] << " ";
	}
	std::cout << std::endl;
	s2 += s3;
	for (int i = 0; i < s2.size(); i++){
		std::cout << s2[i] << " ";
	}
	std::cout << std::endl;
}
int main(){
	//test();
	//test1();
	//test2();
	//test3();
	test4();
	system("pause");
	return 0;
}
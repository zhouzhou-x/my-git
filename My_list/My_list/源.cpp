#include<iostream>
using namespace std;
template<class T>
struct ListNode
{
	T _value;
	ListNode<T>* _prev;
	ListNode<T>* _next;		

	ListNode(const T& val = T())
		:_value(val)
		, _prev = nullptr
		, _next(nullptr)
	{
	}
};
template<class T>
struct Listiterator{
	typedef ListNode<T> Node;
	typedef Listiterator<T> Self;
	Node* _node;
	Listiterator(Node* node)
		:_node(node)
	{
	}
	T& operator*(){
		return _node->_value;
	}
	Self& operator++(){
		_node = _node->_next;
		return *this;
	}
	Self& operator--(){
		_node = _node->_prev;
		return *this;
	}
	bool operator!=(const Self& it){
		return _node != it._node;
	}
	T* operator->(){
		return &_node->_value;
	}
};
//list：双向循环列表
template<class T>
class List
{
public:
	typedef ListNode<T> Node;
	typedef Listiterator<T> iterator;
	//无参构造
	List()
		:_header(new Node)
	{
		_header->_prev = _header->_next = _header;
	}
	//尾插
	void pushBack(const T& val)
	{
		Node* prev = _header->_prev;
		Node* newNode = new Node(val);
		//开始重新链接
		prev->_next = newNode;
		newNode->_prev = prev;
		
		newNode->_next = _header;
		_header->_prev = newNode;
	}
	iterator begin(){
		return iterator(_header->_next);
	}
	iterator end(){
		return iterator(_header);
	}
	void popback(){
		erase(--end());
	}
	void popfront(){
		erase(begin());
	
	}
	void insert(iterator pos,const T& val){
		Node* prev = pos._node->_prev;
		Node* newNode = new Node(val);

		prev->_next = newNode;
		newNode->_prev = prev;

		newNode->_next = pos._node;
		pos._node->_prev = newNode;
	}

	iterator erase(iterator pos){
		if (pos != end()){
			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;
			delete cur;
			prev->_next = next;
			next->_prev = prev;
			return iterator(next);
		}
		return pos;
	}
	void clear(){
		Node* start = _header->_next;
		while (start != _header){
			Node* next = start->_next;
			delete start;
			start = next;
		}
	}
	~List(){
		clear();
		delete _header;
		_header = nullptr;
	}
private:
	Node* _header;
};
template<class T>
void listprintf(List<T>& lst){
	List<T>::iterator it = lst.begin();
	while (it != lst.end()){
		cout << *it << "";
		++it;
	}
	cout << endl;
}
void test(){
	List<int> lst;
	lst.pushBack(1);
	lst.pushBack(2);
	lst.pushBack(3);
	lst.pushBack(4);
	listprintf(lst);//1234
	lst.insert(lst.begin(), 88);
	listprintf(lst);//881234
	lst.erase(lst.begin());
	listprintf(lst);//1234
	lst.popback();
	listprintf(lst);//123
	lst.popfront();
	listprintf(lst);//23

}
int main(){
	test();
	system("pause");
	return 0;
}
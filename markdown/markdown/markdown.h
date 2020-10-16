#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

enum Token {
	nul = 0,
	paragraph = 1,
	href = 2,
	ul = 3,
	ol = 4,
	li = 5,
	em = 6,
	strong = 7,
	hr = 8,
	image = 9,
	quote = 10,
	h1 = 11,
	h2 = 12,
	h3 = 13,
	h4 = 14,
	h5 = 15,
	h6 = 16,
	blockcode = 17,
	code = 18,
};
// HTML前置标签
const std::string frontTag[] = {
	"", "<p>", "", "<ul>", "<ol>", "<li>", "<em>", "<strong>", "<hr color=#CCCCCC size=1/ >",
	"", "<blockquote>", "<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>",
	"<pre><code>", "<code>" };
// HTML 后置标签
const std::string backTag[] = {
	"", "</p>", "", "</ul>", "</ol>", "</li>", "</em>",
	"</strong>", "", "", "</blockquote>", "</h1>", "</h2>",
	"</h3>", "</h4>", "</h5>", "</h6>", "</code></pre>", "</code>" };
struct Node
{
	int _type;

	vector<Node*> _child;

	string elem[2];

	Node(int type)
		:_type(type){
	
	
	}

};
class markdown{
public:
	markdown(const string& filename)
		:_root(new Node(nul))
		, _filename(filename)
	{
	
	
	}
	void transform(){
		//打开文件
		ifstream fin(_filename);
		if (!fin.is_open()){
			cout << "file:" << _filename << "open failed" << endl;
			return;
		}
		//读取内容
		//判断是否为代码块
		bool inblock = false;

		string rowStr;
		while (!fin.eof()){

			getline(fin, rowStr);

			const char* start = processStr(rowStr.c_str());
			
			//预处理
			if (!inblock && start == nullptr)
				continue;

			//判断为是否为水平分割线
			if (!inblock && isCutLine(start)){
				_root->_child.push_back(new Node(hr));
				continue;
			}
			//语法解析
			pair<int, const char*> typeRet = paresType(start);



		//创建语法节点
			if (typeRet.first == blockcode){
				//判断代码块的其实或者结束
				if (!inblock){
					//代码块的起始创建代码块
					_root->_child.push_back(new Node(blockcode));
				}
				inblock = !inblock;
				continue;
			}
			//判断是不是代码块的代码
			if (inblock){
				_root->_child.back()->elem[0] += rowStr;
				_root->_child.back()->elem[0] += '\n';
				continue;

			}
			//段落节点
			if (typeRet.first = paragraph){
				_root->_child.push_back(new Node(paragraph));
				//逐字符插入
				insret(_root->_child.back(), typeRet.second);
				continue;
			}
			if (typeRet.first >= h1 && typeRet.first <= h6){
				//创建结点标题
				_root->_child.push_back(new Node(typeRet.first));
				//插入内容
				_root->_child.back()->elem[0] = typeRet.second;
				continue;
			}
			if (typeRet.first == ul){
				//判断是不是第一项
				//文档开始 /语法树最后一个节点不是无序列表
				if (_root->_child.empty() || _root->_child.back()->_type != ul)
					_root->_child.push_back(new Node(ul));
				Node* uNode = _root->_child.back();
				uNode->_child.push_back(new Node(li));
				insret(uNode->_child.back(),typeRet.second);
			}
			if (typeRet.first == quote){

				//引用结点的创建
				_root->_child.push_back(new Node(quote));
				insret(_root->_child.back(), typeRet.second);
			}
		}

		
		//展开语法树，生成html文档
		//树的深度优先遍历
		dfs(_root);
	}
	// 树的深度优先遍历
	void dfs(Node* root){
		//插入前置标签
		_content += frontTag[root->_type];

		//插入结点内容

		//特殊的标签 网址和链接
		//网址
		if (root->_type == href){
			_content += "<a href=\"";
			_content += root->elem[0];
			_content += "\">";
			_content += root->elem[1];
			_content += "</a>";
		}
		//图片
		else if (root->_type == image){
			_content += "<img alt=\"";
			_content += root->elem[0];
			_content += "\" src=\">";
			_content += root->elem[1];
			_content += "<\" />";
		}
		//普通的
		_content += root->elem[0];


		//处理孩子结点
		for (Node* ch : root->_child)
			dfs(ch);

		//插入后置标签
		_content += backTag[root->_type];
	
	
	}

	//逐字符插入
	void insret(Node* curNode, const char* str){
		//是不是行内代码
		bool incode = false;
		bool instrong = false;
		bool inem = false;
		//解析的纯文本
		//创建纯文本结点
		curNode->_child.push_back(new Node(nul));
		int len = strlen(str);
		for (int i = 0; i < len; i++){
			//行内代码 `
			if (str[i] == '`'){
				if (incode){
					curNode->_child.push_back(new Node(nul));
				}
				else{
					curNode->_child.push_back(new Node(code));
				}
				incode = !incode;
				continue;
			}


			//粗体 **

			if (str[i] == '*' && i+1<len && str[i+1]=='*' && !incode){
				if(instrong){
					curNode->_child.push_back(new Node(nul));
				}
				else{
					curNode->_child.push_back(new Node(strong));
				}
				instrong = !instrong;
				++i;
				continue;
			}
			//斜体 _
			if (str[i] == '_' && !incode){
				if (inem)
					curNode->_child.push_back(new Node(nul));
				else
					curNode->_child.push_back(new Node(em));
				inem = !inem;
				continue;

			}
			//图片 ![]()
			if (str[i] == '!' && i + 1 < len && str[i + 1] == '['){
				curNode->_child.push_back(new Node(image));
				Node* iNode = curNode->_child.back();
				i+=2;
				//存放图片变量名称
				for (; i < len && str[i] != ']'; ++i){
					iNode->elem[0] += str[i];
				}
				i += 2;
				//粗放地址
				for (; i < len && str[i] != ')'; ++i){
					iNode->elem[i] += str[i];
				}
				//处理后边内容
				curNode->_child.push_back(new Node(nul));
				continue;
			}


			//链接 []()
			if (str[i] == '[' && !incode){
				curNode->_child.push_back(new Node(href));
				Node* hNode = curNode->_child.back();
				++i;
				//存放链接名称
				for (; i < len && i != ']'; ++i){
					hNode->elem[0] += str[i];
				}
				i += 2;
				//存放链接
				for (; i < len && i != ']'; ++i){
					hNode->elem[1] += str[i];
				}
				curNode->_child.push_back(new Node(nul));
				continue;
			}



			//普通文本
			curNode->_child.back()->elem[0] += str[i];
		}
	}


	//行首语法解析
	//返回值是 语法类型 + 有效内容的起始位置
	pair<int, const char* > paresType(const char* str){
		const char* ptr = str;
		int cnt = 0;

		while (*ptr && *ptr == '#'){
			ptr++;
			cnt++;
		}
		if (*ptr == ' ' && (cnt > 0 && cnt <= 6)){

			return make_pair(h1 + cnt - 1, ptr + 1);
		}
		ptr = str;

		//判断是不是代码解析块
		if (strncmp(ptr, "```", 3) == 0){
			return make_pair(blockcode, ptr + 3);
		}

		//判断是不是无序列表
		if (strncmp(ptr, "- ", 2) == 0){
			return make_pair(ul, ptr + 2);
		}

		//判断是不是有序列表
		if (*ptr >= 0 && *ptr <= 9){
			while (*ptr && (*ptr >= 0 && *ptr <= 9))
				++ptr;
			if (*ptr && *ptr == '.') {
				++ptr;
				if (*ptr && *ptr == ' ')
					return make_pair(ol, ptr + 1);
			}
		}
		ptr = str;

		//判断是不是引用
		if (strncmp(ptr, "> ", 2) == 0){
			return make_pair(quote, ptr + 2);
		}


		//其他语法
		return make_pair(paragraph,str);
	}

	//判断为是否为水平分割线
	bool isCutLine(const char* str){
		int cnt = 0;
		if (*str && *str == '-'){
			++str;
			++cnt;
		}
		return cnt >= 3;
	}


	//去除行首空格
	const char* processStr(const char* str){
		while (*str){
			if (*str == ' ' || *str == '\t')
				++str;
			else
				break;
		}
		if (*str == '\0')
			return nullptr;
		return str;
	}

	string getContent() const{
		return _content;
	}

	void generatHtml(){
		std::string head =
			"<!DOCTYPE html><html><head>\
			<meta charset=\"utf-8\">\
			<title>Markdown</title>\
			<link rel=\"stylesheet\" href=\"github-markdown.css\">\
			</head><body><article class=\"markdown-body\">";
		std::string end = "</article></body></html>";
		ofstream fout("out/markdown.html");

		fout << head << _content << end;
		
	}


private:
	Node* _root;
	//文件名
	string _filename;
	//生成的内容
	string _content;
};


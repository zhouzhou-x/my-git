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
// HTMLǰ�ñ�ǩ
const std::string frontTag[] = {
	"", "<p>", "", "<ul>", "<ol>", "<li>", "<em>", "<strong>", "<hr color=#CCCCCC size=1/ >",
	"", "<blockquote>", "<h1>", "<h2>", "<h3>", "<h4>", "<h5>", "<h6>",
	"<pre><code>", "<code>" };
// HTML ���ñ�ǩ
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
		//���ļ�
		ifstream fin(_filename);
		if (!fin.is_open()){
			cout << "file:" << _filename << "open failed" << endl;
			return;
		}
		//��ȡ����
		//�ж��Ƿ�Ϊ�����
		bool inblock = false;

		string rowStr;
		while (!fin.eof()){

			getline(fin, rowStr);

			const char* start = processStr(rowStr.c_str());
			
			//Ԥ����
			if (!inblock && start == nullptr)
				continue;

			//�ж�Ϊ�Ƿ�Ϊˮƽ�ָ���
			if (!inblock && isCutLine(start)){
				_root->_child.push_back(new Node(hr));
				continue;
			}
			//�﷨����
			pair<int, const char*> typeRet = paresType(start);



		//�����﷨�ڵ�
			if (typeRet.first == blockcode){
				//�жϴ�������ʵ���߽���
				if (!inblock){
					//��������ʼ���������
					_root->_child.push_back(new Node(blockcode));
				}
				inblock = !inblock;
				continue;
			}
			//�ж��ǲ��Ǵ����Ĵ���
			if (inblock){
				_root->_child.back()->elem[0] += rowStr;
				_root->_child.back()->elem[0] += '\n';
				continue;

			}
			//����ڵ�
			if (typeRet.first = paragraph){
				_root->_child.push_back(new Node(paragraph));
				//���ַ�����
				insret(_root->_child.back(), typeRet.second);
				continue;
			}
			if (typeRet.first >= h1 && typeRet.first <= h6){
				//����������
				_root->_child.push_back(new Node(typeRet.first));
				//��������
				_root->_child.back()->elem[0] = typeRet.second;
				continue;
			}
			if (typeRet.first == ul){
				//�ж��ǲ��ǵ�һ��
				//�ĵ���ʼ /�﷨�����һ���ڵ㲻�������б�
				if (_root->_child.empty() || _root->_child.back()->_type != ul)
					_root->_child.push_back(new Node(ul));
				Node* uNode = _root->_child.back();
				uNode->_child.push_back(new Node(li));
				insret(uNode->_child.back(),typeRet.second);
			}
			if (typeRet.first == quote){

				//���ý��Ĵ���
				_root->_child.push_back(new Node(quote));
				insret(_root->_child.back(), typeRet.second);
			}
		}

		
		//չ���﷨��������html�ĵ�
		//����������ȱ���
		dfs(_root);
	}
	// ����������ȱ���
	void dfs(Node* root){
		//����ǰ�ñ�ǩ
		_content += frontTag[root->_type];

		//����������

		//����ı�ǩ ��ַ������
		//��ַ
		if (root->_type == href){
			_content += "<a href=\"";
			_content += root->elem[0];
			_content += "\">";
			_content += root->elem[1];
			_content += "</a>";
		}
		//ͼƬ
		else if (root->_type == image){
			_content += "<img alt=\"";
			_content += root->elem[0];
			_content += "\" src=\">";
			_content += root->elem[1];
			_content += "<\" />";
		}
		//��ͨ��
		_content += root->elem[0];


		//�����ӽ��
		for (Node* ch : root->_child)
			dfs(ch);

		//������ñ�ǩ
		_content += backTag[root->_type];
	
	
	}

	//���ַ�����
	void insret(Node* curNode, const char* str){
		//�ǲ������ڴ���
		bool incode = false;
		bool instrong = false;
		bool inem = false;
		//�����Ĵ��ı�
		//�������ı����
		curNode->_child.push_back(new Node(nul));
		int len = strlen(str);
		for (int i = 0; i < len; i++){
			//���ڴ��� `
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


			//���� **

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
			//б�� _
			if (str[i] == '_' && !incode){
				if (inem)
					curNode->_child.push_back(new Node(nul));
				else
					curNode->_child.push_back(new Node(em));
				inem = !inem;
				continue;

			}
			//ͼƬ ![]()
			if (str[i] == '!' && i + 1 < len && str[i + 1] == '['){
				curNode->_child.push_back(new Node(image));
				Node* iNode = curNode->_child.back();
				i+=2;
				//���ͼƬ��������
				for (; i < len && str[i] != ']'; ++i){
					iNode->elem[0] += str[i];
				}
				i += 2;
				//�ַŵ�ַ
				for (; i < len && str[i] != ')'; ++i){
					iNode->elem[i] += str[i];
				}
				//����������
				curNode->_child.push_back(new Node(nul));
				continue;
			}


			//���� []()
			if (str[i] == '[' && !incode){
				curNode->_child.push_back(new Node(href));
				Node* hNode = curNode->_child.back();
				++i;
				//�����������
				for (; i < len && i != ']'; ++i){
					hNode->elem[0] += str[i];
				}
				i += 2;
				//�������
				for (; i < len && i != ']'; ++i){
					hNode->elem[1] += str[i];
				}
				curNode->_child.push_back(new Node(nul));
				continue;
			}



			//��ͨ�ı�
			curNode->_child.back()->elem[0] += str[i];
		}
	}


	//�����﷨����
	//����ֵ�� �﷨���� + ��Ч���ݵ���ʼλ��
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

		//�ж��ǲ��Ǵ��������
		if (strncmp(ptr, "```", 3) == 0){
			return make_pair(blockcode, ptr + 3);
		}

		//�ж��ǲ��������б�
		if (strncmp(ptr, "- ", 2) == 0){
			return make_pair(ul, ptr + 2);
		}

		//�ж��ǲ��������б�
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

		//�ж��ǲ�������
		if (strncmp(ptr, "> ", 2) == 0){
			return make_pair(quote, ptr + 2);
		}


		//�����﷨
		return make_pair(paragraph,str);
	}

	//�ж�Ϊ�Ƿ�Ϊˮƽ�ָ���
	bool isCutLine(const char* str){
		int cnt = 0;
		if (*str && *str == '-'){
			++str;
			++cnt;
		}
		return cnt >= 3;
	}


	//ȥ�����׿ո�
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
	//�ļ���
	string _filename;
	//���ɵ�����
	string _content;
};


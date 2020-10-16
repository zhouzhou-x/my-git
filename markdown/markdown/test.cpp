#include "markdown.h"
void test(){
	markdown mp("test.md");
	mp.transform();
	mp.generatHtml();
}
int main(){
	test();
	return 0;
}
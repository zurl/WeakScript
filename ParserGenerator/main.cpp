#include<iostream>
#include<string>
#include<map>
#include<set>
#include<vector>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::map;
using std::set;
using std::endl;

string head = "";
string declr = "";
string body = "";
string tail = ""; 
string getBackStr(string str) {
	string ret = "";
	for (int i = 1; i <= str.length() - 1; i++)
		ret += str[i];
	return ret;
}
void app(string &x, string y, int tabs) {
	for (int i = 1; i <= tabs; i++)x += "    ";
	x += y + "\n";
}
void dealrule() {
	string rulename;
	cin >> rulename;
		

}

void work() {
	string tmpStr;
	while (cin >> tmpStr) {
		if (tmpStr == ":RULE")dealrule();
	}
}
int main() {
	char c;
	freopen("header.code", "r", stdin);
	while ((c = getchar()) != EOF)head += c;
	fclose(stdin);
	freopen("tail.code", "r", stdin);
	while ((c = getchar()) != EOF)tail += c;
	fclose(stdin);
	//This is the bloddy fucking shit
	work();
	freopen("result.code", "w", stdout);
	cout << head << endl;
	cout << declr << endl;
	cout << body << endl;
	cout << tail << endl;
	return 0;
}
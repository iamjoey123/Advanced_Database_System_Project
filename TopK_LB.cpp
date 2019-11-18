#include<stdc++.h>
#include <string>
using namespace std;
struct Struct {
	string sub;
	int pos;
};
class qGram {
private:
	int size;
	Struct *qgram;
public:
	qGram(string s);
	void print();
};
qGram::qGram(string s) {
	size = 0;
	qgram = new Struct[s.length() - 1];
	for (int i = 0; i < s.length() - 2; i++) {
		qgram[i].sub = s.substr(i, 3);
		qgram[i].pos = i;
		size++;
	}
}
void qGram::print() {
	for (int i = 0; i < size; i++) {
		cout << qgram[i].sub << " " << qgram[i].pos << "\n";
	}
}
int main() {
	qGram test = qGram("Why are we still here");
	test.print();
}
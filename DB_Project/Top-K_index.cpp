#include <string>
#include <vector>
#include <iterator>
#include <list>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <map>
#include <iostream>
#include <queue>
using namespace std;

multimap<int, string> maps;
int gPrime = 2; // 7/3=2
struct Struct {
	string sub;
	int pos;

	Struct(string s, int p)
	{
		sub = s;
		pos = p;
	}

	string getString()
	{
		return sub;
	}

	int getPos()
	{
		return pos;
	}
};

class qGram {
private:
	int capac;
	int size;
	std::vector<Struct> qgram;
public:
	qGram();
	qGram(string s);
	qGram(int max);
	void print();
	std::vector<Struct> getQgram();
	int getSize();
	int getCapac();
	void insert(string s, int p);
	void setSize(int s);
	void setCapacity(int c);
	void setVec(std::vector<Struct> v);
};

qGram::qGram()
{
	size = 0;
	capac = 0;
}

qGram::qGram(string s) {
	//cout << s.length() << endl;
	size = 0;
	qgram.reserve(s.length() - 1);
	for (int i = 0; i < s.length() - 2; i++) {
		string temp = s.substr(i, 3);
		Struct t(temp, i + 1);
		qgram.push_back(t);
		size++;
	}
}

qGram::qGram(int max) {
	size = 0;
	capac = max;
	qgram.reserve(max);
}


std::vector<Struct> qGram::getQgram() {
	return qgram;
}


void qGram::setSize(int s) { size = s; }

void qGram::setCapacity(int c) { capac = c; }

void qGram::setVec(std::vector<Struct> v) { qgram = v; }

int qGram::getSize()
{
	return size;
}

int qGram::getCapac()
{
	return capac;
}

void qGram::print() {
	for (int i = 0; i < size; i++) {
		cout << qgram[i].sub << " " << qgram[i].pos << "\n";
	}
}

void qGram::insert(string insertion, int pos)
{
	Struct temp(insertion, pos);
	qgram.push_back(temp);
	size++;
}


int EditDist(string src, string dest, int len1, int len2)
{
	int i, j;
	int edit[len1 + 1][len2 + 1];
	//edit[i][j]=minimum number of edit operations required to transform src[0....(i-1)] to dest[0...(j-1)]

	//initializing
	for (i = 0; i <= len1; i++)
		edit[i][0] = i;    //min operations required to transform src[0...i-1] to empty dest string

	for (j = 0; j <= len2; j++)
		edit[0][j] = j;   //min operations required to transform empty src to dest[0...j-1]

	//now, start filling the matrix row wise
	for (i = 1; i <= len1; i++)
	{
		for (j = 1; j <= len2; j++)
		{
			//if current character of both strings match
			if (src[i - 1] == dest[j - 1])
			{
				edit[i][j] = edit[i - 1][j - 1];
			}

			//mismatch
			else
			{
				//try applying all operations and choose the one which costs minimum
				int x = 1 + edit[i - 1][j];    //delete 
				int y = 1 + edit[i][j - 1];    //insert
				int z = 1 + edit[i - 1][j - 1];  //replace

				edit[i][j] = min(x, min(y, z));

			}
		}
	}

	//now, return the final value 
	return edit[len1][len2];

}

int subString(string str, string query, int n, int k)
{
        int max = 2147483647;
        string temp = "";

        // Pick starting point 
        for (int len = 1; len <= n; len++)
        {
                // Pick ending point 
                for (int i = 0; i <= n - len; i++)
                {
                        //  Print characters from current 
                        // starting point to current ending 
                        // point.   
                        int j = i + len - 1;
                        for (int m = i; m <= j; m++)
                                temp += str[m];

                        int min = EditDist(temp, query, temp.length(), query.length());
                        if(min < max)
                        {
                                max = min;
                        }
                        temp = "";
                }
        }

        return max;
}


bool compareByPos(const Struct& a, const Struct& b)
{
	return a.pos < b.pos;
}

qGram* qGramsComparison(qGram* qGramQuery, qGram* qGramString)
{
	qGram qgq(qGramQuery->getSize());
	qGram qgs(qGramString->getSize());

	std::vector<Struct> q = qGramQuery->getQgram();
	std::vector<Struct> s = qGramString->getQgram();

	std::vector<Struct> temp(std::begin(s), std::end(s));

	for (auto itr = q.begin(); itr != q.end(); itr++)
	{
		for (auto itr2 = temp.begin(); itr2 != temp.end(); itr2++)
		{
			if ((*itr).getString().compare((*itr2).getString()) == 0)
			{
				qgq.insert((*itr).getString(), (*itr).getPos());
				qgs.insert((*itr2).getString(), (*itr2).getPos());
				temp.erase(itr2);
				break;
			}
		}
	}

	auto st1 = qgq.getQgram();
	auto st2 = qgs.getQgram();
	std::sort(st1.begin(), st1.end(), compareByPos);
	std::sort(st2.begin(), st2.end(), compareByPos);

	qGram* combination = new qGram[2];
	combination[0].setSize(qgq.getSize());
	combination[0].setCapacity(qgq.getCapac());
	combination[0].setVec(st1);

	combination[1].setSize(qgs.getSize());
	combination[1].setCapacity(qgs.getCapac());
	combination[1].setVec(st2);

	return combination;
}

int lower_boundthree(int** m, std::vector<Struct> query, std::vector<Struct> st, int qlength, std::map<int, int>locations)
{
	int ql = qlength;
	int fr = ceil((qlength - 3 + 1) / 3.0);
	int mini = 2147483647;

	int t;
	auto index = locations.begin();
	for (int i = 0; i < query.size(); i++)
	{
		int u, v;
		u = (*index).first;
		v = (*index).second;;

		if (m[u][v] != -1)
		{
			t = m[u][v] + ceil((qlength - query[i].getPos() - 3 + 1) / 3.0);
			if (t < mini)
				mini = t;
		}
		index++;
	}

	return min(fr, mini);
}

int lower_boundtwo(list<std::vector<Struct>> vQgram, int i, int j, std::vector<Struct> query, std::vector<Struct> st, int** m)
{
	int u, v;
	int temp = 2147483647;
	bool foundmin;

	for (auto k = vQgram.begin(); k != vQgram.end(); k++)
	{
		if (((*k)[0].getPos() < query[i].getPos()) && ((*k)[1].getPos() < st[j].getPos()))
		{
			foundmin = true;
			int index1 = 0, index2 = 0;
			for (auto p = query.begin(); p != query.end(); p++) {
				if ((*p).getPos() == (*k)[0].getPos() && (*p).getString().compare((*k)[0].getString()) == 0)
				{
					u = index1;
					break;
				}

				index1++;
			}

			for (auto p = st.begin(); p != st.end(); p++) {
				if ((*p).getPos() == (*k)[1].getPos() && (*p).getString().compare((*k)[1].getString()) == 0)
				{
					v = index2;
					break;
				}

				index2++;
			}

			int m1 = m[u][v];
			int m2 = ceil((query[i].getPos() - query[u].getPos() - 1) / 3.0);
			int m3 = abs((query[i].getPos() - query[u].getPos()) - (st[j].getPos() - st[v].getPos()));
			int m4 = m1 + max(m2, m3);

			if (m4 < temp)
				temp = m4;
		}
	}

	return temp;
}
int lower_bound(qGram* newcombo, int qlength)
{
	std::vector<Struct> query;
	std::vector<Struct> sinitial;
	std::vector<Struct> sfinal;

	std::vector<Struct> q = newcombo[0].getQgram();
	std::vector<Struct> s = newcombo[1].getQgram();

	std::map<int, int> locations;
	int ql = newcombo[0].getSize();
	int sl = newcombo[1].getSize();

	int sti = -1;

	for (int i = 0; i < ql; i++)
		query.push_back(q[i]);

	for (int i = 0; i < sl; i++)
	{
		sinitial.push_back(s[i]);
		sfinal.push_back(s[i]);
	}

	list<std::vector<Struct>> vQgram;

	int** m = new int* [ql];
	for (int i = 0; i < ql; i++)
		m[i] = new int[sl];

	int j, u = -1, v = -1, sp, fp;

	for (int i = 0; i < query.size(); i++)
	{
		j = -1;
		for (auto k = sinitial.begin(); k != sinitial.end(); k++)
		{
			if (sinitial.size() > 0)
			{
				if ((*k).getString().compare(query[i].getString()) == 0)
				{

					int index1 = 0, index2 = 0;
					for (auto p = sfinal.begin(); p != sfinal.end(); p++) {
						if ((*p).getPos() == (*k).getPos() && (*p).getString().compare((*k).getString()) == 0)
						{
							j = index1;
							break;
						}

						index1++;
					}

					for (auto p = sinitial.begin(); p != sinitial.end(); p++) {
						if ((*p).getPos() == (*k).getPos() && (*p).getString().compare((*k).getString()) == 0)
						{
							sti = index2;
							break;
						}

						index2++;
					}

					break;
				}
			}

		}

		if (j != -1)
		{
			locations.insert(pair<int, int>(i, j));
			if (vQgram.empty())
			{
				m[i][j] = ceil((query[i].getPos() - 1) / 3.0);
			}
			else
			{
				fp = ceil((query[i].getPos() - 1) / 3.0);
				sp = lower_boundtwo(vQgram, i, j, query, sfinal, m);
				m[i][j] = min(fp, sp);
			}
			std::vector<Struct> tstruct;
			tstruct.push_back(query[i]);
			tstruct.push_back(sfinal[j]);

			vQgram.push_back(tstruct);
			sinitial.erase(sinitial.begin() + sti);
		}
	}

	return lower_boundthree(m, query, sfinal, qlength, locations);
	//return 0;
}

int DYN_LB(string query, string s)
{
	qGram* qGramQuery = new qGram(query);
	qGram* qGramString = new qGram(s);

	qGram* qGramcombo = qGramsComparison(qGramQuery, qGramString);

	int st = lower_bound(qGramcombo, query.length());
	delete qGramQuery;
	delete qGramString;
	return st;
}


int main() {
	int num_checked = 0;
	priority_queue <int, vector<int>, greater<int> > pq;
	cout << "Choose between 1. dblp.txt and 2. wiki.txt and 3. dict.txt (input 1 or 2 or 3):";
	int choice;
	string filename;
	string pointername;
	cin >> choice;
	string q; int k = 2;
	if (choice == 1) {
		cout << "Reading DBLP set--" << endl;
		q = "support";
		cout << "The query string is: " << q << ",K is 2." << endl;
		filename = "dblp.txt";
		pointername = "dblpPointers.txt";
	}
	else if (choice == 2){
		cout << "Reading Wikipedia set--" << endl;
		q = "similar";
		cout << "The query string is: " << q << ",K is 2." << endl;
		filename = "wiki.txt";
		pointername = "wikiPointers.txt";	
	}
	else {
		cout << "Reading Collins Dictionary set--" << endl;
		q = "support";
		cout << "The query string is: " << q << ",K is 2." << endl;
		filename = "dict.txt";
		pointername = "dictPointer.txt";
		
	}
	ifstream tempfile(pointername);
	ifstream file(filename);
	string str1;
	while (getline(tempfile, str1)) {
		pq.push(stoi(str1));
	}		
	clock_t begin = clock();
	string str;
	int iter = 0;
	bool cond = false;
	while (getline(file, str)) {
		if(iter % 100000==0){cout<<"Number of strings processed:"<<iter<<endl;}
        if(str.length()<3){iter++;continue;}
		if (cond == true) {
			if(pq.top() == iter){
				pq.pop();
			}
			else {
				iter++;
				continue;
			}
		}
		if (maps.size() < k)
		{
			num_checked++;
			int dist = subString(str, q, str.length(), k);
			maps.insert(pair<int, string>(dist, str));
		}
		else if (cond == false)
		{
			int d = DYN_LB(q, str);

			auto itr = --maps.end();
			if (itr->first > d)
			{
				int dist = subString(str, q, str.length(), k);
				num_checked++;
				if (itr->first > dist)
				{
					maps.erase(itr);
					maps.insert(pair<int, string>(dist, str));
				}
			}
			itr = --maps.end();
			if (itr->first <= gPrime) {
				while (pq.top() < iter & cond == false) { pq.pop(); }
				cond = true; }
		}
		else {
			if (str.find("upp") == 0 & str.find("ort") == 0 != std::string::npos) {
				int d = DYN_LB(q, str);	
				auto itr = --maps.end();
				if (itr->first > d)
				{
					num_checked++;
					int dist = subString(str, q, str.length(), k);
					if (itr->first > dist)
					{
						maps.erase(itr);
						maps.insert(pair<int, string>(dist, str));
					}
				}
			}
		}
		iter++;
	}
	cout << "TopK_index result:" << endl;
	cout << "Top " << k << " Strings:" << endl;
	for (auto itr = maps.begin(); itr != maps.end(); itr++)
		cout << itr->second << endl;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Total number of words: " << iter << " words" << endl;
	cout << "Number of words filtered: " << iter - num_checked << " words" << endl;
	cout << "Number of words checked: " << num_checked << " words" << endl;
	cout << "Time elapsed: " << elapsed_secs << " s" << endl;
	cout << cond;
	return 0;
}

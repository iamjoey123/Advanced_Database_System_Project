#include <stdc++.h>
#include <string>
#include <vector>
#include <iterator>
#include <list>
#include <math.h>
#include <algorithm>
#include <cmath>
#include <ctime>
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

/*int EditDist(string str1, string str2, int m, int n)
{
/*        int i,j;

	int temp[m + 1][n + 1];
	for(i = 0; i <= m; i++)
		temp[i][0] = i;

	for(j = 0; j <= n; j++)
		temp[0][j] = j;

	for(i = 1; i <= m; i++)
	{
		for(j = 1; j <= n; j++)
		{
			if(str1[i - 1] == str2[j - 1])
				temp[i][j] = temp[i - 1][j - 1];
			else
			{
				int a = 1 + temp[i-1][j];
				int b = 1 + temp[i][j - 1];
				int c = 1 + temp[i-1][j-1];
				temp[i][j] = min(min(a, b),c);
			}
		}
	}

	return temp[m][n];

	int temp[m + 1];

	for(int i = 1; i <= m; i++)
	{
		temp[0] = i;
		int t = i - 1;
		for(int j = 1; j <= n; j++)
		{
			int tj = min(1 + min(temp[j], temp[j - 1]), str1[i - 1] == str2[j-1] ? t : t + 1);
			t = temp[j];
			temp[j] = tj;
		}
	}

	std::sort(temp, temp + (m + 1));

	return temp[0];
}*/


int EditDist(string src, string dest, int len1, int len2)
{
	int i, j;
	//create a matrix of order (len1+1)*(len2+1) to memoize values
	//int edit[len1 + 1][len2 + 1];
	int** edit = new int* [len1+1];
	for (int i = 0; i < len1+1; ++i)
		edit[i] = new int[len2+1];
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
	ifstream file1;
	file1.open("pointers.txt");
	priority_queue <int, vector<int>, greater<int> > pq;
	string str1;
	while (getline(file1, str1)) {
		pq.push(stoi(str1));
	}
	
	int num_checked = 0;
	ifstream file("output.txt");
	int k;
	cout << "Enter value for K: ";
	cin >> k;
	cout << "K: " << k << endl;
	string q = "support";
	cout << "The query string is: " << q << endl;
	clock_t begin = clock();
	string str;
	int iter = 0;
	bool cond = false;
	while (getline(file, str)) {
		if (str.length() < 3) { continue; }
		if (maps.size() < k)
		{
			num_checked++;
			int dist = EditDist(str, q, str.length(), q.length());
			maps.insert(pair<int, string>(dist, str));
		}
		else if(cond == false)
		{
			int d = DYN_LB(q, str);

			auto itr = --maps.end();
			if (itr->first > d)
			{
				int dist = EditDist(str, q, str.length(), q.length());
				num_checked++;
				if (itr->first > dist)
				{
					maps.erase(itr);
					maps.insert(pair<int, string>(dist, str));
				}
			}
			itr = --maps.end();
			if (itr->first <= gPrime) { cond = true; }
		}
		else {
			if (str.find("upp") == 0 & str.find("ppo")==0 != std::string::npos) {
				int d = DYN_LB(q, str);	
				auto itr = --maps.end();
				if (itr->first > d)
				{
					num_checked++;
					int dist = EditDist(str, q, str.length(), q.length());
					num_checked++;
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
	cout << "TopK_Split result:" << endl;
	cout << "Top " << k << " Strings:" << endl;
	for (auto itr = maps.begin(); itr != maps.end(); itr++)
		cout <<"The string is:"<< itr->second <<",and the distance is:"<<itr->first << endl;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Total number of words: " << iter << " words" << endl;
	cout << "Number of words filtered: " << iter - num_checked << " words" << endl;
	cout << "Number of words checked: " << num_checked << " words" << endl;
	cout << "Time elapsed: " << elapsed_secs << " s" << endl;
	cout << cond;
	return 0;
}

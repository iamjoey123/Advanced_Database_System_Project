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

int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

multimap<int, string> maps;

int EditDist(string src, string dest, int len1, int len2)
{
	int i, j;

	//create a matrix of order (len1+1)*(len2+1) to memoize values
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
int main(int argc, char *argv[])
{
	int k = 2; string q;
	cout << "Choose between 1. dblp.txt and 2. wiki.txt 3. dict.txt(input 1 or 2 or 3):";
	int choice;
	cin >> choice;
	string filename;
	if (choice == 1) {
		cout << "Reading DBLP set--" << endl;
		filename = "dblp.txt";
		q = "support";
		cout << "Query string is:" << q << ",K is 2" << endl;
	}
	else if (choice == 2) {
		cout << "Reading Wikipedia set--" << endl;
		filename = "wiki.txt";
		q = "similar";
		cout << "Query string is:" << q << ",K is 2" << endl;
	}
	else {
		cout << "Reading Collins Dictionary set--" << endl;
		filename = "dict.txt";
		q = "support";
		cout << "Query string is:" << q << ",K is 2" << endl;
	}
	ifstream file(filename);
	clock_t begin = clock();
	string str;
	int iter = 0;
	while (getline(file, str)) {
		if(iter % 10000==0){cout<<"Number of strings processed:"<<iter<<endl;}
                int dist = subString(str, q,str.length(), k);
                if(maps.size() < k)
                         maps.insert(pair<int, string>(dist,str));
                else
                {
                        auto itr = --maps.end();
                        if (itr->first > dist)
                        {
                                maps.erase(itr);
                                maps.insert(pair<int, string>(dist, str));
                        }
                }

		iter++;
	}
	cout << "The Top " << k << " Strings: " << endl;
	for (auto itr = maps.begin(); itr != maps.end(); itr++)
		cout << itr->second << endl;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Total Number of words: " << iter << " words" << endl;
	cout << "Number of words checked: " << iter << " words" << endl;
	cout << "Number of words filtered: " << 0 << " words" << endl;
	cout << "Number of words checked: " << iter << " words" << endl;
	cout << "Time elapsed: " << elapsed_secs << " s" << endl;
	return 0;
}

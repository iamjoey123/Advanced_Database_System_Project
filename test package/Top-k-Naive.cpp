#include <bits/stdc++.h>
#include <string>
#include <map>
#include <ctime>
using namespace std;

int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

multimap<int, string> maps;


/*int editDist(string str1, string str2, int m, int n)
{
	// If first string is empty, the only option is to 
	// insert all characters of second string into first 
	if (m == 0) return n;

	// If second string is empty, the only option is to 
	// remove all characters of first string 
	if (n == 0) return m;

	// If last characters of two strings are same, nothing 
	// much to do. Ignore last characters and get count for 
	// remaining strings. 
	if (str1[m - 1] == str2[n - 1])
		return editDist(str1, str2, m - 1, n - 1);

	// If last characters are not same, consider all three 
	// operations on last character of first string, recursively 
	// compute minimum cost for all three operations and take 
	// minimum of three values. 
	return 1 + min(editDist(str1, str2, m, n - 1),    // Insert 
		editDist(str1, str2, m - 1, n),   // Remove 
		editDist(str1, str2, m - 1, n - 1) // Replace 
	);
}*/


int EditDist(string src, string dest, int len1, int len2)
{
    int i, j;
 
    //create a matrix of order (len1+1)*(len2+1) to memoize values
    int edit[len1+1][len2+1];
 
    //edit[i][j]=minimum number of edit operations required to transform src[0....(i-1)] to dest[0...(j-1)]
 
    //initializing
    for(i=0;i<=len1;i++)
        edit[i][0]=i;    //min operations required to transform src[0...i-1] to empty dest string
 
    for(j=0;j<=len2;j++)
        edit[0][j]=j;   //min operations required to transform empty src to dest[0...j-1]
 
    //now, start filling the matrix row wise
    for(i=1;i<=len1;i++)
    {
        for(j=1;j<=len2;j++)
        {
            //if current character of both strings match
            if(src[i-1]==dest[j-1])
            {
                edit[i][j]=edit[i-1][j-1];
            }
 
            //mismatch
            else
            {
                //try applying all operations and choose the one which costs minimum
                int x=1+edit[i-1][j];    //delete 
                int y=1+edit[i][j-1];    //insert
                int z=1+edit[i-1][j-1];  //replace
 
                edit[i][j]=min(x,min(y,z));
 
            }
        }
    }
 
    //now, return the final value 
    return edit[len1][len2];
 
}

void subString(string str, string query, int n, int k)
{
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

			if (maps.size() < k)
				maps.insert(pair<int, string>(EditDist(temp, query, temp.length(), query.length()), temp));
			else
			{
				int dist = EditDist(temp, query, temp.length(), query.length());
				auto itr = --maps.end();
				if (itr->first > dist)
				{
					maps.erase(itr);
					maps.insert(pair<int, string>(dist, str));
				}
			}
			temp = "";
		}
	}
}
int main()
{
	//string dataString[7] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"};
	clock_t begin = clock();
	int k;
	string query;
	cout << "Enter value for K: ";
	cin >> k;
	cout << "K: " << k << endl;
	cout << "Enter query string: ";
	cin >> query;
	cout << "The query string is: " << query << endl;
	ifstream file("dict.txt");
	string str;
	int iter = 0;
	while (getline(file, str)) {
		subString(str, query,str.length(), k);
		iter++;
	}
	/*for (int i = 0; i < 7; i++) {
		subString(dataString[i], query, dataString[i].length(), k);
	}
	*/
	cout << "The Top " << k << " Strings: " << endl;
	for(auto itr = maps.begin(); itr != maps.end(); itr++)
		cout << itr->second << endl;
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Total Number of words: " << iter << " words" << endl;
	cout << "Number of words checked: " << iter << " words" << endl;
	cout << "Number of words filtered: " << 0 << " words" << endl;
	cout << "Number of words checked: " << iter << " words << endl;
	cout <<"Time elapsed: "<< elapsed_secs << " s" << endl;
	return 0;
}

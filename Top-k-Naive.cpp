 
#include<bits/stdc++.h>
#include <string>
#include <map>

using namespace std;

int min(int x, int y, int z)
{
	return min(min(x, y), z);
}

int editDist(string str1, string str2, int m, int n)
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
}

multimap<int,string> subString(string str, string query, int n, int k)  
{ 
    multimap <int, string> tempmap;
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
            for (int k = i; k <= j; k++)  
                temp += str[k]; 
	    if(tempmap.size() < k)
		tempmap.insert(pair<int, string>(editDist(temp, query, temp.length(), query.length()), temp));
	    else
	    {
		int dist = editDist(temp, query, temp.length(), query.length());
		auto itr = --tempmap.end();
		if(itr->first > dist)
		{
			tempmap.erase(itr);
			tempmap.insert(pair<int, string>(dist, temp));
		}
	    }	
	    temp = "";
        } 
    } 

    return tempmap;
} 

int main()
{
	// your code goes here 
	string str1 = "saturdab";
	string str2 = "saturday";
	int k = 3;
	multimap<int, string> substrings = subString(str1, str2, str1.length(), k);
	for(auto i = substrings.begin(); i != substrings.end(); i++)
		cout << i->second << ": " << i->first << endl;

	//cout << editDist(str1, str2, str1.length(), str2.length());

	return 0;
}

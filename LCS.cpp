#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int n;
string str1;
list<string> LCS;
vector< vector<int> > candidate;

void find_LCS(int i, int j, int length, string str);

int main()
{
    int m, length;
    string str2;
    cout<<"Please input two sequences:"<<endl;
    cin>>str1>>str2;
    str1 = "0" + str1;
    str2 = "0" + str2;
    m = str1.length();
    n = str2.length();
    candidate.assign(min(m, n), vector<int>());
    vector< vector<int> > table(m, vector<int>(n, 0));

    for(int i=1; i<m; i++)
    {
        for(int j=1; j<n; j++)
        {
            if(str1[i] == str2[j])
            {
                table[i][j] = table[i-1][j-1]+1;
                candidate[table[i][j]].push_back(i*n+j);
            }
            else if(table[i-1][j] > table[i][j-1])
            {
                table[i][j] = table[i-1][j];
            }
            else
            {
                table[i][j] = table[i][j-1];
            }
        }
    }

    length = table[m-1][n-1];
    cout<<"The length of LCS: "<<length<<endl;
    cout<<"All possible LCS:"<<endl;
    find_LCS(m, n, length, string(length, '0'));
    LCS.sort();
    LCS.unique();
    list<string>::iterator it;
    for(it=LCS.begin(); it!=LCS.end(); it++) cout<<*it<<endl;
    return 0;
}

void find_LCS(int i, int j, int length, string str)
{
    int next_i, next_j;
    if(length==0)
    {
        LCS.push_back(str);
        return;
    }
    for(int arrow=0; arrow<candidate[length].size(); arrow++)
    {
        next_i = candidate[length][arrow]/n;
        next_j = candidate[length][arrow]%n;
        if(next_i<i && next_j<j)
        {
            length--;
            str[length] = str1[next_i];
            find_LCS(next_i, next_j, length, str);
            length++;
        }
    }
}

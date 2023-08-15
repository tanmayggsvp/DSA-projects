#include<bits/stdc++.h>
using namespace std;
void helper(vector<vector<char>> &a, vector<map<int,int>> &row, vector<map<int,int>> &column, int r, int c,map<pair<int,int>,map<int,int>> &mp)
{
    if(r == 9)
    {
        for(int i =0;i<9;i++)
        {
            for(int j=0;j<9;j++)
            {
                cout<<a[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return;
    }
    if(c == 9)
    {
        helper(a,row,column,r+1,0,mp);
        return;
    }
    if(a[r][c]!='.')
    {
        helper(a,row,column,r,c+1,mp);
        return;
    }
    else
    {
        for(int i = 1;i<=9;i++)
        {
            int rw = r/3;
            int col = c/3;
            if(!mp[{rw,col}][i] and !row[r][i] and !column[c][i])
            {
                mp[{rw,col}][i] = 1;
                a[r][c] = i+'0';
                row[r][i] = 1;
                column[c][i] = 1;
                helper(a,row,column,r,c+1,mp);
                mp[{rw,col}][i] = 0;
                a[r][c] = '.';
                row[r][i] = 0;
                column[c][i] = 0;
            }
        }
    }


}
void solveSudoku(vector<vector<char>>&a)
{
    map<pair<int,int>,map<int,int>>mp;
    vector<map<int,int>>row(9);
    vector<map<int,int>>column(9);
    for(int i=0;i<9;i++)
    {
        for(int j =0;j<9;j++)
        {
            if(a[i][j]!='.')
            {
                mp[{i/3,j/3}][a[i][j]-'0']=1;
                row[i][a[i][j]-'0'] = 1;
                column[j][a[i][j]-'0'] = 1;
            }
        }
    }
    helper(a,row,column,0,0,mp);
}
int main()
{
    vector<vector<char>> soduku = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    solveSudoku(soduku);
    return 0;
}
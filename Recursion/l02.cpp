#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> dirA{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
vector<string> dirN{"u", "d", "r", "l"};

int multi_move(int sr, int sc, int er, int ec, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }
    int cnt = 0;
    for (int i = 0; i < dirA.size(); i++)
    {

        for (int jump = 1; jump <= max(er, ec); jump++)
        {
            int x = sr + jump * dirA[i][0];
            int y = sc + jump * dirA[i][1];

            if (x <= er && y <= ec)
                cnt += multi_move(x, y, er, ec, ans + dirN[i]);
        }
    }
    return cnt;
}
vector<string> multi_move02(int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
    {
        vector<string> baseRes;
        baseRes.push_back("");
        return baseRes;
    }
    vector<string> myAns;
    for (int i = 0; i < dirA.size(); i++)
    {
        for (int jump = 1; jump <= max(er, ec); jump++)
        {
            int x = sr + jump * dirA[i][0];
            int y = sc + jump * dirA[i][1];

            if (x <= er && y <= ec)
            {
                vector<string> recAns = multi_move02(x, y, er, ec);
                for (string str : recAns)
                {
                    myAns.push_back(str + dirN[i]);
                }
            }
        }
    }
    return myAns;
}

int flood_fill(int sr, int sc, int er, int ec, vector<vector<int>> &board, string ans)
{
    if (sr == er && sc == ec)
    {
        cout << ans << endl;
        return 1;
    }
    int cnt = 0;
    board[sr][sc] = 1;
    for (int i = 0; i < dirA.size(); i++)
    {

        int x = sr + dirA[i][0];
        int y = sc + dirA[i][1];

        if (x >= 0 && y >= 0 && x <= er && y <= ec && board[x][y] == 0)
            cnt += flood_fill(x, y, er, ec, board, ans + dirN[i]);
    }
    board[sr][sc] = 0;
    return cnt;
}
class helper
{
public:
    int len;
    string path = "";
    helper(int l, string p)
    {
        len = l;
        path = p;
    }
};
helper longestPath(int sr, int sc, int er, int ec, vector<vector<int>> &board)
{
    if (sr == er && sc == ec)
    {
        helper baseRes(0, "");
        return baseRes;
    }
    helper myAns(0, "");
    board[sr][sc] = 1;
    for (int i = 0; i < dirA.size(); i++)
    {

        int x = sr + dirA[i][0];
        int y = sc + dirA[i][1];

        if (x >= 0 && y >= 0 && x <= er && y <= ec && board[x][y] == 0)
        {
            helper recAns = longestPath(x, y, er, ec, board);
            if (recAns.len + 1 > myAns.len)
            {
                myAns.len = recAns.len + 1;
                myAns.path = recAns.path + dirN[i];
            }
        }
    }
    board[sr][sc] = 0;
    return myAns;
}
helper shortestPath(int sr, int sc, int er, int ec, vector<vector<int>> &board)
{
    if (sr == er && sc == ec)
    {
        helper baseRes(0, "");
        return baseRes;
    }
    helper myAns(9, "");
    board[sr][sc] = 1;
    for (int i = 0; i < dirA.size(); i++)
    {

        int x = sr + dirA[i][0];
        int y = sc + dirA[i][1];

        if (x >= 0 && y >= 0 && x <= er && y <= ec && board[x][y] == 0)
        {
            helper recAns = shortestPath(x, y, er, ec, board);
            if (recAns.len <= myAns.len)
            {
                myAns.len = recAns.len + 1;
                myAns.path = recAns.path + dirN[i];
            }
        }
    }
    board[sr][sc] = 0;
    return myAns;
}
bool isSafe(vector<vector<char>> &board, int r, int c, int num)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[r][i] - '0' == num)
            return false;
    }
    for (int j = 0; j < board.size(); j++)
    {
        if (board[j][c] - '0' == num)
            return false;
    }
    r = (r / 3) * 3;
    c = (c / 3) * 3;
    for (int i = r; i < 3; i++)
    {
        for (int j = c; j < 3; j++)
        {
            if (board[r + i][c + j] - '0' == num)
                return false;
        }
    }
    return true;
}
bool sudoku(vector<vector<char>> &board, int idx, vector<int> &calls)
{
    if (idx == calls.size())
    {
        return true;
    }
    int r = calls[idx] / 9;
    int c = calls[idx] % 9;
    bool res = false;
    for (int i = 1; i <= 9; i++)
    {
        if (isSafe(board, r, c, i))
        {
            board[r][c] = (char)(i + '0');
            res = res || sudoku(board, idx + 1, calls);
            if (res == false)
            {
                board[r][c] = '.';
            }
        }
    }
    return res;
}
void sudokuSolve(vector<vector<char>> &board)
{
    vector<int> calls;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == '.')
                calls.push_back((i * 9) + j);
        }
        bool ans = sudoku(board, 0, calls);
    }
}
//=====================Crypto==========================

string str1 = "send";
string str2 = "more";
string str3 = "money";
int boolArray = 0;
vector<int> hashmap(26, 0);
int strToNum(string str)
{
    int ans = 0;
    for (int i = 0; i < str.length(); i++)
    {
        
        ans =ans * 10 + hashmap[str[i] - 'a'];
    }
    return ans;
}
int cryptoSolve(string &compressed, int idx)
{
    if (idx == compressed.length())
    {
        int one = strToNum(str1);
        int two = strToNum(str2);
        int three = strToNum(str3);
        if (one + two == three)
        {
            for (int i = 0; i < hashmap.size(); i++)
            {
                if (hashmap[i] > 0)
                {
                    char ch = i + 'a';
                    cout << ch << ":" << hashmap[i] << " ";
                }
            }
            cout << endl;
            return 1;
        }
        return 0;
    }
    int cnt = 0;
    for (int i = 0; i <= 9; i++)
    {
        int mask = 1 << i;
        if ((boolArray & mask) == 0)
        {
            boolArray ^= mask;
            hashmap[compressed[idx] - 'a'] = i;
            cnt += cryptoSolve(compressed, idx + 1);
            hashmap[compressed[idx] - 'a'] = 0;
            boolArray ^= mask;
        }
    }
    return cnt;
}
void crypto()
{
    string str = str1 + str2 + str3;
    vector<int> compress(26, 0);
    for (int i = 0; i < str.length(); i++)
    {
        compress[str[i] - 'a']++;
    }
    string compressed = "";
    for (int i = 0;i< compress.size(); i++)
    {
        if (compress[i] > 0)
            compressed += (char)(i + 'a');
    }
    // cout<<compressed;
    cout << cryptoSolve(compressed, 0);
}
class Solution {
public:
    vector<int> row;
    vector<int> col;
    vector<vector<int>> mat;
    bool solve(vector<vector<char>>& board,vector<int>&calls,int idx){
        if(idx==calls.size())return true;
        bool res=false;
        int r=calls[idx]/9;
        int c=calls[idx]%9;
        for(int i=1;i<=9;i++){
            int mask=1<<i;
            if((row[r]&mask)==0&&(col[c]&mask)==0&&(mat[r/3][c/3]&mask)==0){
                board[r][c]=(char)(i+'0');
                row[r]^=mask;
                col[c]^=mask;
                mat[r/3][c/3]^=mask;
                res=res||solve(board,calls,idx+1);
                if(res==true)return res;
                board[r][c]='.';
                row[r]^=mask;
                col[c]^=mask;
                mat[r/3][c/3]^=mask;
            }
        }
        return res;
    }
    void solveSudoku(vector<vector<char>>& board) {
        row.assign(9,0);
        col.assign(9,0);
        mat.assign(3,vector<int>(3,0));
        vector<int> calls;
        for(int i=0;i<board.size();i++){
            for(int j=0;j<board.size();j++){
                if(board[i][j]=='.')calls.push_back((i*9)+j);
                else{
                    int num=board[i][j]-'0';
                    int mask=1<<num;
                    row[i]^=mask;
                    col[j]^=mask;
                    mat[i/3][j/3]^=mask;
                }
            }
        }
        solve(board,calls,0);
    }
};


void solve()
{
    // cout << multi_move(0, 0, 3, 2, "");
    // vector<string> ans = multi_move02(0, 0, 3, 2);
    // for (string str : ans)
    //     cout << str << endl;
    // vector<vector<int>> board(3, vector<int>(3, 0));
    // // cout << flood_fill(0, 0, 1, 1, board, "");
    // helper ans=shortestPath(0, 0, 2, 2, board);
    // cout<<ans.len<<endl<<ans.path;
    crypto(); //util function
}

int main()
{

    solve();
}
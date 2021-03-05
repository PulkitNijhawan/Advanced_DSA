#include <iostream>
#include <vector>
using namespace std;
#define mod 1000000007
typedef long long int lli;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
int type1(vi &arr)
{ //Leetcode: 121
    int Ti0 = 0;
    int Ti1 = -1e9;
    for (int ele : arr)
    {
        Ti0 = max(Ti0, Ti1 + ele);
        Ti1 = max(Ti1, -ele);
    }
    return Ti0;
}
int type2(vi &arr)
{ //Leetcode: 122
    int Ti0 = 0;
    int Ti1 = -1e9;
    for (int ele : arr)
    {
        Ti0 = max(Ti0, Ti1 + ele);
        Ti1 = max(Ti1, Ti0 - ele);
    }
    return Ti0;
}
int type3(vi &arr)
{ //Atmax 2 trans : 123
    int Ti20 = 0;
    int Ti21 = -1e9;
    int Ti10 = 0;
    int Ti11 = -1e9;
    for (int ele : arr)
    {
        Ti20 = max(Ti20, Ti21 + ele);
        Ti21 = max(Ti21, Ti10 - ele);
        Ti10 = max(Ti10, Ti11 + ele);
        Ti11 = max(Ti11, -ele);
    }
    return Ti20;
}
int type4(vi &arr)
{
    //Leetcode: 309
    int Ti0 = 0;
    int Ti1 = -1e9;
    int Ti2 = 0;
    for (int ele : arr)
    {
        int prevBuyingPt = Ti0;    //i-1
        Ti0 = max(Ti0, Ti1 + ele); //i  update
        Ti1 = max(Ti1, Ti2 - ele); // for this i => Ti2 : i-2
        Ti2 = prevBuyingPt;        // updating after process
    }
    return Ti0;
}
void solve()
{
    vi arr{1, 2, 3, 4, 5};
    cout << type1(arr) << "\n";
    cout << type3(arr) << "\n";
}
int main()
{
    solve();
    return 0;
}
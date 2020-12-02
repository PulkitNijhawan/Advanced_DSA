#include <iostream>
#include <vector>
using namespace std;
vector<string> words = {
    ":;/",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wx",
    "yz",
    "&*%",
    "#@$",
};
vector<string> nokia_keypad02(string ques)
{
    if (ques.length() == 0)
    {
        vector<string> baseRes;
        baseRes.push_back("");
        return baseRes;
    }
    vector<string> myAns;
    char ch = ques[0];
    string word = words[ch - '0'];
    vector<string> recAns = nokia_keypad02(ques.substr(1));
    for (int i = 0; i < word.length(); i++)
    {
        for (string str : recAns)
        {
            myAns.push_back(word[i] + str);
        }
    }
    return myAns;
}
int nokia_keypad(string ques, string ans)
{
    if (ques.length() == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int cnt = 0;
    char ch = ques[0];
    string word = words[ch - '0'];
    for (int i = 0; i < word.length(); i++)
    {
        cnt += nokia_keypad(ques.substr(1), word[i] + ans);
    }
    return cnt;
}
int enco_nokia(string ques, string ans)
{
    if (ques.length() == 0)
    {
        cout << ans << endl;
        return 1;
    }
    int cnt = 0;
    char ch = ques[0];
    string word = words[ch - '0'];
    for (int i = 0; i < word.length(); i++)
    {
        cnt += enco_nokia(ques.substr(1), word[i] + ans);
    }
    if (ques.length() >= 2)
    {
        int num = (ques[0] - '0') * 10 + (ques[1] - '0');
        if (num == 11 || num == 10)
        {
            string word2 = words[num];
            for (int i = 0; i < word.length(); i++)
            {
                cnt += enco_nokia(ques.substr(2), word2[i] + ans);
            }
        }
    }
    return cnt;
}
void quesSet()
{
    // cout<<nokia_keypad("456","");
    // vector<string> ans=nokia_keypad02("456");
    // for(string str:ans)cout<<str<<endl;
    cout << enco_nokia("1012", "");
}
void solve()
{
    quesSet();
}
int main()
{
    solve();
}
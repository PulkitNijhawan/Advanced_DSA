#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define reduce (int)(1e9 + 7)
unordered_mp<ll, ll> mp;
vector<ll> fact(500005);

ll m = reduce;
ll recursive(ll n, ll p)
{
    ll answer = 1;
    while (p!=0)
    {
        if ((p %2)>0)
            answer *=  n;
            answer%=m;
        n = (n * n) % m;
        p >>= 1;
    }

    return answer % m;
}
ll combinations(ll n, ll r)
{
    if (r == 0)
        return 1;
    return (((fact[n] * recursive(fact[n - r], m - 2)) % m) * (recursive(fact[r], m - 2) % m)) % m;
}
void solve(vector<ll> &arr, vector<ll> &quest, vector<ll> &remainder, int n)
{
    for (auto itr : mp)
    {
        ll sum = 1;
        for (int j = 1; j <= itr.second; j++)
        {
            sum = (sum + combinations(itr.second, j)) % reduce;
            quest[j] = (ll)(((quest[j] % reduce) * (sum % reduce)) % reduce);
        }
        remainder[itr.second + 1] = (ll)((remainder[itr.second + 1] * sum) % reduce);
    }
    ll multiply = 1;
    for (int i = 1; i <= n; i++)
    {
        multiply = (multiply * remainder[i]) % reduce;
        quest[i] = (ll)(((quest[i] % reduce) * (multiply % reduce)) % reduce);
    }
    for (int i = 1; i <= n; i++)
    {
        ll sum = 1;
        ll answer = 0;
        ll res = 0;

        for (int j = 1; j <= mp[i]; j++)
        {
            ll temp;
            answer = combinations(mp[i], j);
            temp = answer;
            sum = (sum + answer) % reduce;
            quest[j] = (ll)((quest[j] * recursive(sum, m - 2)) % reduce);
            answer = ((answer % reduce) * (quest[j] % reduce)) % reduce;
            quest[j] = (ll)((quest[j] * (sum - temp + reduce) % reduce) % reduce);
            res = (res + answer) % reduce;
        }

        cout << res % reduce << " ";
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < 500005; i++)
    {
        ll q = (ll)((i * fact[i - 1]) % reduce);
        fact[i] = q;
    }
    while (t--)
    {
        ll n;
        cin >> n;
        vector<ll> arr(n + 1);
        mp.clear();
        for (int i = 0; i < n; i++)
        {
            int j;
            cin >> j;
            arr[i] = j;
            mp[j]++;
        }
        vector<ll> quest(n + 3, 1);
        vector<ll> remainder(n + 1, 1);
        solve(arr, quest, remainder, n);
        cout << endl;
    }
    return 0;
}

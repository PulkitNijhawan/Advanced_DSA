#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
ll fastModExp(ll a, ll b)
{

    ll res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}
int main()
{
    return 0;
}
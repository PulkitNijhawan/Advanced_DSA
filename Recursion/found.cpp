#include <iostream>
#include <vector>
#define fo(i, n) for (int i = 0; i < n; i++)
typedef vector<int> vi;
int find_last(vi &arr)
{
    int rv = arr.size();
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        if (a[i] == d)
        {
            rv = i;
            break;
        }
    }
    return rv;
}
int find_first(vi &arr)
{
    int rv = -1;
    for (int i = 0; i < arr.size(); i++)
    {
        if (a[i] == d)
        {
            rv = i;
            break;
        }
    }
    return rv;
}
int main()
{
}
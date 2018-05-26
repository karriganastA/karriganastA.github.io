#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e6+10;
ll n ,p;
ll inv[maxn];
int main(int argc, char *argv[])
{
	ios::sync_with_stdio(false);
	cin >> n >> p;
	inv[1] = 1;
	for (int i = 2; i <= n; i++)
	inv[i] = (p - p/i) * inv[p % i] % p;
	for (int i = 1; i <= n; i++)
	cout << inv[i] << "\n"; 
	return 0;
}

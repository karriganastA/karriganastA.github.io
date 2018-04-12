#include<bits/stdc++.h>
using namespace std;
const int maxn = 500010;
int n,m,a[maxn],C[maxn];
#define lowbit(x) (x&-x)
int sum(int x)
{
	int ret = 0;
	while(x)
	{
		ret += C[x];
		x -= lowbit(x);
	}
	return ret;
}
void add(int x,int d)
{
	while(x <= n)
	{
		C[x] += d;
		x += lowbit(x);
	}
}
int query(int l,int r){return (sum(r)-sum(l-1));}
int main(int argc, char *argv[])
{
	memset(C,0,sizeof(C));
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d",&x);
		a[i] = x;
		add(i,x);
	}
	while(m--)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		printf("%d\n",query(x,y));
	}
	return 0;
}

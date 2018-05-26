#include<bits/stdc++.h>
using namespace std;
struct Edges{
	int u,v,cost;
	bool operator < (const Edges &b) const {
		return cost < b.cost;
	}
}edges[200010];
int fa[5010],son[5010];
int getf(int x)
{
	if (x == fa[x]) return x;
	fa[x] = getf(fa[x]);
	return fa[x];
}
bool union_(int x,int y)
{
	int r1 = getf(x);
	int r2 = getf(y);
	if (r1 == r2) return false;
	if (fa[r1] >= fa[r2])
	{
		fa[r2] = fa[r1];
		son[r1] += son[r2];
	}
	else
	{
		fa[r1] = fa[r2];
		son[r2] += son[r1];
	}
	return true;
}
int main(int argc, char *argv[])
{
	int n,m;
	scanf("%d %d",&n,&m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].cost);
	sort(edges+1,edges+1+m);
	for (int i = 1; i <= n; i++)
	fa[i] = i,son[i] = 1;
	int ltotal = 0,flag = 0,ans = 0;
	for (int i = 1; i <= m; i++)
	{
		if (union_(edges[i].u,edges[i].v))
		{
			ltotal++;
			ans += edges[i].cost;
		}
		if (ltotal == n-1) 
		{
			flag = 1;
			break;
		}
	}
	if (flag) printf("%d",ans);
	else printf("orz");
	return 0;
}

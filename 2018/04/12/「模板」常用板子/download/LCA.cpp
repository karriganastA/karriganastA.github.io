#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
int n,m,x,y,tot;
int fa[N],head[N],depth[N],sz[N],top[N];
vector<int>lt[N];
void add(int u,int v){lt[u].push_back(v);lt[v].push_back(u);}

inline int read(void)
{
	int x = 0,f = 1; char ch = getchar();
	while(!isdigit(ch)){f = ch == '-' ? -1 : 1; ch = getchar();}
	while(isdigit(ch)){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * f;
}

void dfs1(int u) 
{
	depth[u]=depth[fa[u]]+1;
	for (int i=0,v; i<lt[u].size(); i++)
		if ((v=lt[u][i])!=fa[u]) 
		{
			fa[v]=u;
			dfs1(v);
			sz[u]+=sz[v];
		}
	if (!sz[u]) ++sz[u];
}

void dfs2(int u) 
{
	if (!top[u]) top[u]=u;
	int t=0;
	for (int i=0,v; i<lt[u].size(); i++)
		if ((v=lt[u][i])!=fa[u]&&sz[v]>sz[t]) t=v;
	if (!t) return;
	top[t]=top[u];
	dfs2(t);
	for (int i=0,v; i<lt[u].size(); i++)
		if ((v=lt[u][i])!=fa[u]&&v!=t) dfs2(v);
}

int lca(int u,int v) 
{
	for (; top[u]!=top[v]; u=fa[top[u]]) 
		if (depth[top[u]]<depth[top[v]]) swap(u,v);
	return depth[u]<depth[v]?u:v;
}
int main(int argc, char *argv[]) 
{
	n = read(),m = read();
	for (int i=1; i<n; ++i) 
	{
		x = read(), y = read();
		add(x,y);
	}
	dfs1(1);dfs2(1);
	for (int i=1; i<=m; i++) 
	{
		x = read(), y = read();
		printf("%d\n",lca(x,y));
	}
	return 0;
}

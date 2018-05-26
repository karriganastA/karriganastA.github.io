#include<bits/stdc++.h>
#include<queue>
using namespace std;
const int maxn = 2510;

vector<int>lt[maxn];
vector<int>lw[maxn];
queue<int>q;
int n ,c, s, t ,dist[maxn];
bool isq[maxn];

void addedge(int u, int v,int w)
{
	lt[u].push_back(v);
	lt[v].push_back(u);
	lw[u].push_back(w);
	lw[v].push_back(w);
}

inline int read(void)
{
	int x = 0,f = 1; char ch = getchar();
	while(!isdigit(ch)){f = ch == '-' ? -1 : 1; ch = getchar();}
	while(isdigit(ch)){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * f; 
}


int main(int argc, char *argv[])
{
	memset(dist,0x7f,sizeof(dist));
	memset(isq,0,sizeof(isq));
	n = read(), c = read(), s = read(), t = read();
	for (int i = 1; i <= c; i++)
	{
		int u = read() , v = read() , w = read();
		addedge(u,v,w);
	}
	dist[s] = 0,isq[s] = 1,q.push(s);
	while(!q.empty())
	{
		int u = q.front(); q.pop();
		for (int i = 0; i < lt[u].size(); i++)
		{
			int to = lt[u][i],cost = lw[u][i];
			if (cost + dist[u] < dist[to])
			{
				dist[to] = cost + dist[u];
				if (!isq[to])
				{
					isq[to] = 1;
					q.push(to);
				}
			}
		}
		isq[u] = 0;
	}
	printf("%d\n",dist[t]);
	return 0;
}

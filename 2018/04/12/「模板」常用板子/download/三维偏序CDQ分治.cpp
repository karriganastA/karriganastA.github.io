#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int maxm = 6*1e5+10;
int num[maxn],t[maxm];
inline void read(int &a)
{
	int negativ = 1;
	a = 0;
	char c = getchar();
	while(!isdigit(c)){if(c == '-') negativ = -1; c = getchar();} 
	while(isdigit(c)) {a = a*10+c-'0';c = getchar();}
	a *= negativ;
}
int n,k;
struct Node{
	int a,b,c;
	int cnt,ans;
}nod[maxn];
int lowbit(int x){return (x&-x);}
void add(int x,int u){for(;x<=k;x+=lowbit(x)) t[x]+=u;}
int query(int x){int ret = 0; for(;x;x-=lowbit(x)) ret+=t[x]; return ret;}
bool cmpa(Node x,Node y)
{
	if (x.a != y.a) return x.a < y.a;
	if (x.b != y.b) return x.b < y.b;
	return x.c < y.c;
}
bool cmpb(Node x,Node y)
{
	return x.b==y.b?x.c<y.c:x.b<y.b;
}
void CDQ(int l,int r)
{
	if(l == r)
	{
		nod[l].ans+=nod[l].cnt-1;
		return;
	}
	int mid = (l+r) >> 1;
	CDQ(l,mid);
	CDQ(mid+1,r);
	sort(nod+l,nod+mid+1,cmpb);
	sort(nod+mid+1,nod+r+1,cmpb);
	int i,j=l;
	for (i=mid+1; i<=r; i++)
	{
		for(;nod[j].b <= nod[i].b && j<=mid; j++)
		add(nod[j].c,nod[j].cnt);
		nod[i].ans += query(nod[i].c);
	}
	for (int i=l;i<j;i++) add(nod[i].c,-nod[i].cnt);
}
int main(int argc, char *argv[])
{
	read(n); read(k);
	for (int i = 1; i <= n; i++){read(nod[i].a); read(nod[i].b); read(nod[i].c);nod[i].ans=nod[i].cnt=1;}
	sort(nod+1,nod+n+1,cmpa);
 	int tot = 0;
 	for (int i = 1; i <= n; i++)
 	{
 		if (i!=1 && nod[i].a == nod[i-1].a && nod[i].b == nod[i-1].b && nod[i].c == nod[i-1].c)
 			nod[tot].cnt++;
 		else nod[++tot] = nod[i];
	}
	CDQ(1,tot);
	for (int i = 1; i <= tot; i++) num[nod[i].ans]+=nod[i].cnt;
	for (int i = 1; i <= n; i++) printf("%d\n",num[i]);
	return 0;
}

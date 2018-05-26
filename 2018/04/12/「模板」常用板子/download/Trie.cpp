#pragma GCC optmize("0fuck")
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e6+10;
char s[11];
struct Trie{
	int tot,trie[maxn][26],sum[maxn];
	void settledown(void){tot=0;memset(sum,0,sizeof(sum));}
	void insert(char *s,int rt)
	{
		int l = strlen(s);
		for (int i = 0; i < l; i++)
		{
			int x = s[i]-'a';
			if (trie[rt][x] == 0)
				trie[rt][x] = ++tot;
			
			rt = trie[rt][x];
			sum[rt]++; 		
		}	
	} 
	int find(char *s,int rt)
	{
		int l = strlen(s);
		for (int i = 0; i < l; i++)
		{
			int x = s[i]-'a';
			if (!trie[rt][x]) return 0;
			rt = trie[rt][x];
		}
		return sum[rt];
	}
}Tr;

int main(int argc,char *argv[])
{
	char ch;
	while(gets(s))
	{
		if (s[0]==NULL)
			break;
		Tr.insert(s,0);
	}
	while(gets(s))
		printf("%d\n",Tr.find(s,0));
	return 0;
}

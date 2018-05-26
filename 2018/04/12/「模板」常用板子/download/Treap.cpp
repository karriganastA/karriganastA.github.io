// m     操作有m个
// 1 x   插入元素x
// 2 x   删除元素x。如果成功，输入1，否则输出0
// 3 k   输出值x的“名次”，即比x小的结点个数加1
// 4 x   第k小元素。k=1为最小元素
// 5 x   prefix of x
// 6 x   suffix of x
// ... to be continued ...
#include<bits/stdc++.h>
using namespace std;
struct Node {
	Node *ch[2]; // 左右子树
	int r; // 随机优先级
	int v; // 值
	int s; // 结点总数
	Node(int v = 0):v(v) {
		ch[0] = ch[1] = NULL;
		r = rand();
		s = 1;
	}
	int cmp(int x) const {
		if (x == v) return -1;
		return x < v ? 0 : 1;
	}
	void maintain() {
		s = 1;
		if(ch[0] != NULL) s += ch[0]->s;
		if(ch[1] != NULL) s += ch[1]->s;
	}
};
void rotate(Node* &o, int d) {
	Node* k = o->ch[d^1];
	o->ch[d^1] = k->ch[d];
	k->ch[d] = o;
	o->maintain();
	k->maintain();
	o = k;
}
void insert(Node* &o, int x) {
	if(o == NULL) o = new Node(x);
	else {
		int d = (x < o->v ? 0 : 1);
		insert(o->ch[d], x);
		if(o->ch[d]->r > o->r) rotate(o, d^1);
	}
	o->maintain();
}
Node* find(Node* o, int x) {
	if(o == NULL) return NULL;
	if(x == o->v) return o;
	return x < o->v ? find(o->ch[0], x) : find(o->ch[1], x);
}
void remove(Node* &o, int x) {
	int d = o->cmp(x);
	if(d == -1) {
		Node* u = o;
		if(o->ch[0] != NULL && o->ch[1] != NULL) {
			int d2 = (o->ch[0]->r > o->ch[1]->r ? 1 : 0);
			rotate(o, d2);
			remove(o->ch[d2], x);
		} else {
			if(o->ch[0] == NULL) o = o->ch[1];
			else o = o->ch[0];
			delete u;
		}
	} else
		remove(o->ch[d], x);
	if(o != NULL) o->maintain();
}
int kth(Node* o, int k) {
	if(o == NULL || k <= 0 || k > o->s) return 0;
	int s = (o->ch[0] == NULL ? 0 : o->ch[0]->s);
	if(k == s+1) return o->v;
	else if(k <= s) return kth(o->ch[0], k);
	else return kth(o->ch[1], k-s-1);
}
int rank(Node* o, int x) {
	if(o == NULL) return 1;
	if(x <= o->v) return rank(o->ch[0], x);
	return rank(o->ch[1], x) + (o->ch[0] == NULL ? 0 : o->ch[0]->s) + 1;
}
int prefix(Node *o, int k,int c) {
	if (o == NULL) return c;
	if (k > o->v) return prefix(o->ch[1],k,o->v);
	else return prefix(o->ch[0],k,c);
}
int suffix(Node *o, int k,int c) {
	if (o == NULL) return c;
	if (k < o->v) return suffix(o->ch[0],k,o->v);
	else return suffix(o->ch[1],k,c);
}
const int INF = INT_MAX >> 1;
/*
void dfs(Node *o)
{
	if (o == NULL) return ;
	printf("%d\n",o->v);
	 printf("LC of %d:\n",o->v);dfs(o->ch[0]);
	 printf("RC of %d:\n",o->v); dfs(o->ch[1]);
	printf("EO %d!\n\n",o->v); 
}
*/
int main(int argc, char *argv[]) {
	srand(int(time(NULL)));
	int m, c, v;
	Node* root = new Node(INF);
	scanf("%d", &m);
	while(m--) 
	{
		scanf("%d%d", &c, &v);
		if(c == 1) insert(root, v);
		else if(c == 2) {
			Node* o = find(root, v);
			if(o != NULL) remove(root, v);
		} else if(c == 3) printf("%d\n", rank(root, v));
		else if(c == 4) printf("%d\n", kth(root,v));
		else if(c == 5) printf("%d\n",prefix(root,v,0));
		else printf("%d\n",suffix(root,v,0));
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10; 
struct Node {
	Node* ch[2];
	int v,s,flip;
	int cmp(int k) {
		int d=k-ch[0]->s;
		if(d==1) return -1;
		return d<=0? 0:1;
	}
	void maintain() {
		s=ch[0]->s+ch[1]->s+1;
	}
	void pushdown() {
		if(flip) {
			flip=0;
			swap(ch[0],ch[1]);
			ch[0]->flip^=1;
			ch[1]->flip^=1;
		}
	}
};
Node* null=new Node();
void rotate(Node* &o,int d) {
	Node* k=o->ch[d^1];
	o->ch[d^1]=k->ch[d];
	k->ch[d]=o;
	o->maintain(),k->maintain();
	o=k;
}
void splay(Node* &o,int k) {
	o->pushdown();
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->s+1;
	if(d!=-1) {
		Node* p=o->ch[d];
		p->pushdown();
		int d2=p->cmp(k);
		int k2=d2==0? k:k-p->ch[0]->s-1;
		if(d2!=-1) {
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);
			else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}
Node* merge(Node* left,Node* right) {
	splay(left,left->s);
	left->ch[1]=right,left->maintain();
	return left;
}
void split(Node* o,int k,Node* &left,Node* &right) {
	splay(o,k);
	left=o,right=left->ch[1],left->ch[1]=null;
	left->maintain();
}
struct SplaySequence {
	int n;
	Node seq[maxn];
	Node* root;

	Node* build(int sz) {
		if(!sz) return null;
		Node* l=build(sz/2);
		Node* o=&seq[++n];
		o->v=n;
		o->ch[0]=l;
		o->ch[1]=build(sz-sz/2-1);
		o->flip=o->s=0;
		o->maintain();
		return o;
	}
	void init(int sz) {
		n=null->s=0;
		root=build(sz);
	}
} spaly;
vector<int> ans;
void print(Node* o) {
	if(o!=null) {
		o->pushdown();
		print(o->ch[0]);
		ans.push_back(o->v);
		print(o->ch[1]);
	}
}

int read() {
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	int x=0;
	while(isdigit(c)) {
		x=x*10+c-'0';
		c=getchar();
	}
	return x;
}
int n,m;
int main(int argc, char *argv[]) 
{
	n=read(),m=read();
	spaly.init(n+1);   
	int l,r;
	Node *left,*right,*mid;
	while(m--) {
		l=read(),r=read();
		split(spaly.root,l,left,right);
		split(right,r-l+1,mid,right);
		mid->flip^=1;
		spaly.root = merge(merge(left,mid),right);
	}
	print(spaly.root);
	for(int i=1; i<ans.size(); i++) printf("%d ",ans[i]-1);
	return 0;
}

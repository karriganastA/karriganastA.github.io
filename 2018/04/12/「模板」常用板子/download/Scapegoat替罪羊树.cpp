#include<bits/stdc++.h>
#include<vector>
using namespace std;
const double alpha=0.7;

struct scapegoat{
    scapegoat *l,*r;
    int val,size,cnt;
    bool deleted;
    bool is_bad(){return (l->cnt > alpha*cnt+5 || r->cnt > alpha*cnt+5);}
    void maintain(){size=!deleted+l->size+r->size; cnt=1+r->cnt+l->cnt;}
};
scapegoat *null;

void dfs(scapegoat *o,vector<scapegoat*> &v)
{
    if(o == null) return;
    dfs(o->l,v);
    if(!o->deleted) v.push_back(o);
    dfs(o->r,v);
    if(o->deleted) delete o;
}
scapegoat *build(vector<scapegoat*> &v,int l,int r)
{
    if(l >= r) return null;
    int mid = (l+r) >> 1;
    scapegoat *o = v[mid];
    o->l = build(v,l,mid);
    o->r = build(v,mid+1,r);
    o->maintain();
    return o;
}
void rebuild(scapegoat* &o)
{
    vector<scapegoat*> v;
    dfs(o,v);
    o = build(v,0,v.size());
}
void insert(int x,scapegoat* &o)
{
    if(o==null)
    {
        o=new scapegoat;
        o->l=o->r=null;
        o->deleted=false;
        o->size=o->cnt=1;
        o->val=x;
        return;
    }
    else
    {
        ++o->size;
        ++o->cnt;
        if(x>=o->val)
            insert(x,o->r);
            else
            insert(x,o->l);
        if(o->is_bad())rebuild(o);
    }
}
int rank(scapegoat *now,int x)
    {
        int ans=1;
        while(now!=null)
        {
            if(now->val>=x)now=now->l;
            else
            {
                ans+=now->l->size+!now->deleted;
                now=now->r;
            }
        }
        return ans;
    }
int kth(scapegoat *now,int x)
{
    while(now!=null)
    {
        if(!now->deleted && now->l->size+1==x)
            return now->val;
        if(now->l->size>=x)now=now->l;
            else
            {
                x-=now->l->size+!now->deleted;
                now=now->r;
            }
    }
}
void erase(scapegoat *o,int rk)
{
    if(!o->deleted && rk==o->l->size+1)
    {
        o->deleted=1;
        --o->size;
        return;
    }
    --o->size;
    if(rk<=o->l->size+!o->deleted)
        erase(o->l,rk);
    else
        erase(o->r,rk-o->l->size-!o->deleted);
}
inline void read(int &a)
{
    int negativ = 1;
    a = 0;
    char c = getchar();
    while(!isdigit(c)){if(c == '-') negativ = -1; c = getchar();} 
    while(isdigit(c)) {a = a*10+c-'0';c = getchar();}
    a *= negativ;
}

scapegoat *root;
int main(int argc, char *argv[])
{
    null = new scapegoat;
    root = null;
    int n;
    read(n);
    while(n--)
    {
        int op,x;
        read(op); read(x);
        if(op==1)insert(x,root);
        if(op==2)erase(root,rank(root,x));
        if(op==3)printf("%d\n",rank(root,x));
        if(op==4)printf("%d\n",kth(root,x));
        if(op==5)printf("%d\n",kth(root,rank(root,x)-1));
        if(op==6)printf("%d\n",kth(root,rank(root,x+1)));
    }
    return 0; 
}

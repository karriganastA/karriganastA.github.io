#include<bits/stdc++.h>
#include<queue>
using namespace std;
const int maxn = 1e6 + 5;
int cnt,N;
struct node{
    node *next[26];
    node *fail;
    int sum;
};
char key[maxn];
node *newnode,*root;
char pattern[maxn];
void Insert(char *s)
{
    node *p = root;
    for(int i = 0; s[i]; i++)
    {
        int x = s[i] - 'a';
        if(p->next[x] == NULL)
        {
            //newnode=(struct node *)malloc(sizeof(struct node)); 
            newnode = new(node);
            for(int j=0;j<26;j++) newnode->next[j] = 0;
            newnode->sum = 0;newnode->fail = 0;
            p->next[x]=newnode;
        }
        p = p->next[x];
    }
    p->sum++;
}
void build_fail_pointer()
{
    queue<node*>q;
    q.push(root);
    node *p;
    node *temp;
    while(!q.empty())
    {
        temp = q.front();
        q.pop();
        for(int i = 0; i <= 25; i++)
        {
            if(temp->next[i])
            {
                if(temp == root)
                    temp->next[i]->fail = root;
                else
                {
                    p = temp->fail;
                    while(p)
                    {
                        if(p->next[i])
                        {
                            temp->next[i]->fail = p->next[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if(p == NULL) temp->next[i]->fail = root;
                }
                q.push(temp->next[i]);
            }
        }
    }
}
void ac_automation(char *ch)
{
    node *p = root;
    int len = strlen(ch);
    for(int i = 0; i < len; i++)
    {
        int x = ch[i] - 'a';
        while(!p->next[x] && p != root) p = p->fail;
        p = p->next[x];
        if(!p) p = root;
        node *temp = p;
        while(temp != root)
        {
           if(temp->sum >= 0)
           {
               cnt += temp->sum;
               temp->sum = -1;
           }
           else break;
           temp = temp->fail;
        }
    }
}
int main(int argc, char *argv[])
{
	//root=(struct node *)malloc(sizeof(struct node));
    root = new(node); //ºÃÏñ new(node)¸ü¿ì!? 
    for(int j=0;j<26;j++) root->next[j] = 0;
    root->fail=0;
    root->sum=0;
    scanf("%d",&N);
    getchar();//get char of newline 
    for(int i = 1; i <= N; i++)
    {
        scanf("%s",key);
        Insert(key);
    }
    scanf("%s",pattern);
    cnt = 0;
    build_fail_pointer();
    ac_automation(pattern);
    printf("%d\n",cnt);
    return 0;
}

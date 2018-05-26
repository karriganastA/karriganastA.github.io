#include<bits/stdc++.h>
#define il inline
#define RG register
#define N 10010
using namespace std;
 
char s[N][55],ss[N*100];
int n,times[N];//times记录单词在文本串中出现的次数
 
struct Trie{
   int son[N][26],fail[N],root,L,num[N];
   int last[N];//只是一个优化，有没有都没关系
    
   void init(){
      L=1; root=0;
      memset(son,0,sizeof(son));
      memset(num,0,sizeof(num));
      memset(last,0,sizeof(last));
      memset(fail,0,sizeof(fail));
   }
    
   il int idx(char c){ return c-'a'; }
    
   void insert( char s[],int v ){
      int len=strlen(s), cur=root;
      for(int i=0;i<len;i++){
            int id=idx(s[i]);
         if(!son[cur][id])
            son[cur][id]=L++;
         cur=son[cur][id];
      }
      num[cur]=v;   //记录单词编号
   }
    
   void build(){
        int que[N],hd=0,tl=0;
        for(int i=0;i<26;i++)
            if(son[root][i]){
                que[tl++]=son[root][i];
                fail[son[root][i]]=root;
            }
            else son[root][i]=root;
       
        while(hd<tl){
            int cur=que[hd++];
            for(int i=0;i<26;i++){
                int Son=son[cur][i];
                if(Son){
                    int f=fail[cur];
                    while(f && !son[f][i]) f=fail[f];
                    fail[Son]=son[f][i];
                                        num[Son]=num[fail[Son]];//不用last优化时要加上这一句
                                        que[tl++]=Son;
                }
                else son[cur][i]=son[fail[cur]][i];
            }
                        //if( num[fail[cur]] )last[cur]=fail[cur];
                        //else last[cur]=last[fail[cur]];
        }
    }
    
   void query( char s[] ){
        int len=strlen(s),cur=root;
        for(int i=0;i<len;i++){
            int id=idx(s[i]);
            while(cur && !son[cur][id]) cur=fail[cur];
            if(son[cur][id]){
                cur=son[cur][id];
                int k=cur;
                        while(k) times[ num[k] ]++,k=fail[k];
                /*while(k){
                            if(num[k]) times[num[k]]++;
                            k=last[k];
                            }*/
            }
             
        }
    }
    
}AC;
 
int main(){
   scanf("%d",&n); AC.init();
   for(RG int i = 1;i<=n;i++){
      scanf("%s",s[i]);
      AC.insert(s[i],i);
   }
   AC.build();
   scanf("%s",ss); AC.query(ss);
   for( RG int i=1;i<=n;i++ )    printf("%s %d\n",s[i],times[i]);
   return 0;
}

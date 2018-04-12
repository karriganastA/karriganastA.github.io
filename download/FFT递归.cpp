//递归爆栈 热 
#include<bits/stdc++.h>
#define complex COMPLEX
using namespace std;
const int MAXN=2*1e6+10;
inline int read()
{
    char c=getchar();int x=0,f=1;
    while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
    while(isdigit(c)){x=x*10+c-'0';c=getchar();}
    return x*f;
}
const double Pi=acos(-1.0);
struct complex
{
    double x,y;
    complex (double xx=0,double yy=0){x=xx,y=yy;}
}a[MAXN],b[MAXN];
complex operator + (const complex &a,const complex &b){ return complex(a.x+b.x , a.y+b.y);}
complex operator - (const complex &a,const complex &b){ return complex(a.x-b.x , a.y-b.y);}
complex operator * (const complex &a,const complex &b){ return complex(a.x*b.x-a.y*b.y , a.x*b.y+a.y*b.x);}//不懂的看复数的运算那部分 
void FFT(int limit,complex *a,int type)
{
    if(limit==1) return ;//只有一个常数项
    complex a1[limit>>1],a2[limit>>1];
    for(int i=0;i<=limit;i+=2)//根据下标的奇偶性分类
        a1[i>>1]=a[i],a2[i>>1]=a[i+1];
    FFT(limit>>1,a1,type);
    FFT(limit>>1,a2,type);
    complex Wn=complex(cos(2.0*Pi/limit) , type*sin(2.0*Pi/limit)),w=complex(1,0);
    for(int i=0;i<(limit>>1);i++,w=w*Wn)//这里的w相当于公式中的k 
        a[i]=a1[i]+w*a2[i],
        a[i+(limit>>1)]=a1[i]-w*a2[i];//利用单位根的性质，O(1)得到另一部分 
}
int main(int argc, char *argv[])
{
    int N=read(),M=read();
    for(int i=0;i<=N;i++) a[i].x=read();
    for(int i=0;i<=M;i++) b[i].x=read();
    int limit=1;while(limit<=N+M) limit<<=1;
    FFT(limit,a,1);
    FFT(limit,b,1);
    for(int i=0;i<=limit;i++)
        a[i]=a[i]*b[i];
    FFT(limit,a,-1);
    for(int i=0;i<=N+M;i++) printf("%d ",(int)(a[i].x/limit+0.5));
	return 0;
}

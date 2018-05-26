#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL a[400010],b[400010],c[400010];
int p=1004535809,g=3,n,m,bin[400010]; 
LL pow(LL a,int b,int mod)
{
    LL ans=1;
    while(b)
    {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;b>>=1;
    }
    return ans;
}
void ntt(LL *a,int n,int op)
{
    for(int i=0;i<n;i++) if(i<bin[i]) swap(a[i],a[bin[i]]);
    for(int i=1;i<n;i<<=1)
    {
        LL wn=pow((LL)g,op==1?(p-1)/(2*i):p-1-(p-1)/(2*i),p),t,w;
        for(int j=0;j<n;j+=i<<1)
        {
            w=1;
            for(int k=0;k<i;k++)
            {
                t=w*a[i+j+k]%p;w=w*wn%p;
                a[i+j+k]=(a[j+k]-t+p)%p;a[j+k]=(a[j+k]+t)%p;
            }
        }
    }
    if(op==-1)
    {
        LL inv=pow(n,p-2,p);
        for(int i=0;i<n;i++) a[i]=a[i]*inv%p;
    }
}
int main(int argc, char *argv[])
{
    scanf("%d %d",&n,&m);
    for(int i=0;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=0;i<=m;i++) scanf("%lld",&b[i]);
    m+=n;n=1;while(n<=m) n<<=1;
    for(int i=0;i<n;i++) bin[i]=(bin[i>>1]>>1)|((i&1)*(n>>1));
    ntt(a,n,1);ntt(b,n,1);
    for(int i=0;i<n;i++) c[i]=a[i]*b[i];ntt(c,n,-1);
    for(int i=0;i<=m;i++) printf("%lld ",c[i]);
    return 0;
}

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

inline char nc(){
  static char buf[100000],*p1=buf,*p2=buf;
  return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;
}
inline void read(int &x){
  char c=nc(),b=1;
  for (;!(c>='0' && c<='9');c=nc()) if (c=='-') b=-1;
  for (x=0;c>='0' && c<='9';x=x*10+c-'0',c=nc()); x*=b;
}

int P=23333333;
const int M[]={998244353,1004535809,469762049};
const int G[]={3,3,3};
const ll _M=(ll)M[0]*M[1];

inline ll Pow(ll a,int b,int p){
  ll ret=1;
  for (;b;b>>=1,a=a*a%p)
    if (b&1)
      ret=ret*a%p;
  return ret;
}
inline ll mul(ll a,ll b,ll p){
  a%=p; b%=p;
  return ((a*b-(ll)((ll)((long double)a/p*b+1e-3)*p))%p+p)%p;
}

const int m1=M[0],m2=M[1],m3=M[2];
const int inv1=Pow(m1%m2,m2-2,m2),inv2=Pow(m2%m1,m1-2,m1),inv12=Pow(_M%m3,m3-2,m3);
inline int CRT(int a1,int a2,int a3){
  ll A=(mul((ll)a1*m2%_M,inv2,_M)+mul((ll)a2*m1%_M,inv1,_M))%_M;
  ll k=((ll)a3+m3-A%m3)*inv12%m3;
  return (k*(_M%P)+A)%P;
}

const int N=264000;

struct NTT{
  int P,G;
  int num,w[2][N];
  int R[N];
  void Pre(int _P,int _G,int m){
    num=m; P=_P; G=_G;
    int g=Pow(G,(P-1)/num,P);
    w[1][0]=1; for (int i=1;i<num;i++) w[1][i]=(ll)w[1][i-1]*g%P;
    w[0][0]=1; for (int i=1;i<num;i++) w[0][i]=w[1][num-i];
    int L=0; while (m>>=1) L++;
    for (int i=1;i<=num;i++) R[i]=(R[i>>1]>>1)|((i&1)<<(L-1));
  }
  void FFT(int *a,int n,int r){
    for (int i=0;i<n;i++) if (i<R[i]) swap(a[i],a[R[i]]);
    for (int i=1;i<n;i<<=1)
      for (int j=0;j<n;j+=(i<<1))
    for (int k=0;k<i;k++){
      int x=a[j+k],y=(ll)a[j+i+k]*w[r][num/(i<<1)*k]%P;
      a[j+k]=(x+y)%P; a[j+i+k]=(x+P-y)%P;
    }
    if (!r) for (int i=0,inv=Pow(n,P-2,P);i<n;i++) a[i]=(ll)a[i]*inv%P;
  }
}ntt[3];

int n,m,n1,n2;
int a[3][N];
int A[N],B[N],C[N],D[N];

int main(int argc, char *argv[]){
  scanf("%d%d%d",&n1,&n2,&P);
  for (int i=0;i<=n1;i++) scanf("%d",&A[i]);
  for (int i=0;i<=n2;i++) scanf("%d",&B[i]);
  for (m=1;m<=(n1+n2);m<<=1);
  for (int i=0;i<3;i++) ntt[i].Pre(M[i],G[i],m);
  for (int i=0;i<3;i++){
    memcpy(C,A,sizeof(int)*(m+5)); memcpy(D,B,sizeof(int)*(m+5));
    ntt[i].FFT(C,m,1); ntt[i].FFT(D,m,1);
    for (int j=0;j<m;j++) C[j]=(ll)C[j]*D[j]%ntt[i].P;
    ntt[i].FFT(C,m,0);
    for (int j=0;j<m;j++) a[i][j]=C[j];
  }
  for (int i=0;i<=n1+n2;i++) printf("%d ",CRT(a[0][i],a[1][i],a[2][i]));
  return 0;
}

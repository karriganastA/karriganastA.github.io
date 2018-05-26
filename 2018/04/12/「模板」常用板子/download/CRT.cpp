inline ll mul(int m,int n,int k){ll b=1;while(n){if(n&1)b=b*m%k;n=n>>1;m=m*m%k;}return b;}
inline int CRT(int a1,int a2,int a3)
{
  ll A=(mul((ll)a1*m2%_M,inv2,_M)+mul((ll)a2*m1%_M,inv1,_M))%_M;
  ll k=((ll)a3+m3-A%m3)*inv12%m3;
  return (k*(_M%P)+A)%P;
}

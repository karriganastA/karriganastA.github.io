inline ll mul(int m,int n,int k){ll b=1;while(n){if(n&1)b=b*m%k;n=n>>1;m=m*m%k;}return b;}

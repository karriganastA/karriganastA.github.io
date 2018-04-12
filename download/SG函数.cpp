int f[N],SG[N];
bool S[M];
void getSG(int n)
{
    memset(SG,0,sizeof(SG));
    for(int i=1;i<=n;i++)
    {
        memset(S,false,sizeof(S));
        for(int j=1;f[j]<=i&&j<M;j++)
        {
             S[SG[i-f[j]]]=true;
        }
        for(int j=0;;j++)
        if(!S[j])
        {
            SG[i]=j;
            break;
        }
    }
}

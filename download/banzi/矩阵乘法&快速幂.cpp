JZ cheng(JZ a,JZ b)
{
    JZ c;memset(c.m,0,sizeof c.m);
    c.x=a.x;c.y=b.y;
    for(int i=1;i<=a.x;i++)
        for(int j=1;j<=b.y;j++)
            for(int k=1;k<=a.y;k++)
                c.m[i][j]=(c.m[i][j]+(a.m[i][k]%MOD)*(b.m[k][j]%MOD))%MOD;
    return c;
}

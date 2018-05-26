inline void init(void)
{
	//phi[i]为欧拉函数,u[i]为莫比乌斯函数,f[i]为约数个数函数,g[i]为最高质因数的次方数 
	phi[1] = u[1] = f[1] = 1;
	for (int i = 2; i < maxn; i++)
	{
		if(!vis[i])
		{
			prime[++cnt] = i;
			u[i] = -1;
			f[i] = 2;
			g[i] = 1;
			phi[i] = i-1;
		}
		for(int j = 1;j <= cnt&& i*prime[j] <=maxn; j++)
		{
            vis[i*prime[j]]=true;
            if(i%prime[j]== 0)
			{
                u[i*prime[j]]=0;
                g[i*prime[j]]=g[i]+1;
                f[i*prime[j]]=f[i]/(g[i]+1)*(g[i]+2);
                phi[i*prime[j]] = phi[i] * prime[j];
                break;
            }
            u[i*prime[j]]=-u[i];
            g[i*prime[j]]=1;
            f[i*prime[j]]=f[i]*2;
            phi[i*prime[j]] = phi[i] * (prime[j]-1);
        }
	}
}

int kmp(char *a, char *b) //find b in a
{
	static int fail[MAXN];
	int na = strlen(a+1),nb = strlen(b+1);
	fail[1] = 0;
	for (int i = 2; i <= nb; i++)
	{
		int j = fail[i-1];
		while(j != 0 && b[j+1] != b[i]) j = fail[j];
		if (b[j+1] == b[i]) fail[i] = j+1;
		else fail[i] = 0;	
	}	
	int res = 0; 
	for (int i = 1,j = 0; i <= na; i++)
	{
		while(j != 0 && b[j+1] != a[i]) j = fail[j];
		if (a[i] == b[j+1]) j++;
		if (j == nb)
		{
			res ++;
			j = fail[j];
           // j = 0;
           //如果每个字符只能使用一次,这里的j应该为0
		} 
	}
	return res;
}

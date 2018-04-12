inline int read(void)
{
	int x = 0,f = 1; char ch = getchar();
	while(!isdigit(ch)){f = ch == '-' ? -1 : 1; ch = getchar();}
	while(isdigit(ch)){x = (x << 3) + (x << 1) + ch - '0'; ch = getchar();}
	return x * f;
}

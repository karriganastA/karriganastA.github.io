void ex_gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b){d = a;x = 1;y = 0;} 
	//如果b = 0，那么就是ax = d，令x = 1,y = 0即可
	else {ex_gcd(b,a%b,d,y,x) y-=x*(a/b);} 
}

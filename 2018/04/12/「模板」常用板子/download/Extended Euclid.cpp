void ex_gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b){d = a;x = 1;y = 0;} 
	//���b = 0����ô����ax = d����x = 1,y = 0����
	else {ex_gcd(b,a%b,d,y,x) y-=x*(a/b);} 
}

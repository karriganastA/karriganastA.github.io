#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
double l,r;
int N;
double xs[14];

double calc(double x)
{
	double ret = 0.0;
	for (int i = N; i >= 0; i--)
	ret += xs[i] * pow(x,double(i));
	return ret;
}
int main(int argc, char *argv[])
{
	scanf("%d%lf%lf",&N,&l,&r);
	for (int i = N; i >= 0; i--)
	scanf("%lf",&xs[i]);
	while(r - l > eps)
	{
		double m1 = l + (r - l) / 3;
		double m2 = r - (r - l) / 3;
		if (calc(m1) < calc(m2))  l = m1;
		else r = m2;
	}
	printf("%.5lf",l);
	return 0;
}

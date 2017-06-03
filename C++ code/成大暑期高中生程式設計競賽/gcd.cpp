#include<bits/stdc++.h>
using namespace std;
int Gcd(int a,int b)
{
	if(!b)return a;
	while((a%=b)&&(b%=a));
	return max(a,b);
}
int main()
{
	int a,b;
	while(scanf("%d%d",&a,&b)==2)
	{
		printf("%d\n",Gcd(a,b));
	}
}

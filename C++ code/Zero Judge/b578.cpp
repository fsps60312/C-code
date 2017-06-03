#include<bits/stdc++.h>
using namespace std;
int T;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		static unsigned long long a,b,c;
		scanf("%llu%llu%llu",&a,&b,&c);
		a*=a,b*=b,c*=c;
		if(a+b==c||a+c==b||b+c==a)puts("right triangle");
		else if(a+b>c&&a+c>b&&b+c>a)puts("acute triangle");
		else puts("obtuse triangle");
	}
	return 0;
}

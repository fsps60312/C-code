#include<bits/stdc++.h>
using namespace std;
int main()
{
	int N;
	scanf("%d",&N);
	int a=0,b=0,c=0;
	for(int i=0,v;i<N;i++)
	{
		scanf("%d",&v);
		if(v>=a)c=b,b=a,a=v;
		else if(v>=b)c=b,b=v;
		else if(v>=c)c=v;
	}
	printf("%d\n",a+b+c);
	return 0;
}

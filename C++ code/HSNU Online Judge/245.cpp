#include<cstdio>
int N;
int main()
{
	scanf("%d",&N);
	int a,b;scanf("%d%d",&a,&b);
	int mx=b,mn=a,premx=b,premn=a;
	a=b;
	bool ans=true;
	for(int i=2;i<N;i++)
	{
		scanf("%d",&b);
		if(!ans)continue;
		mx=a*2-premn,mn=a*2-premx;
		if(mx>b)mx=b;
		if(mx<mn)ans=false;
		a=b,premn=mn,premx=mx;
	}
	if(!ans)puts("0");
	else printf("%d\n",mx-mn+1);
	return 0;
}

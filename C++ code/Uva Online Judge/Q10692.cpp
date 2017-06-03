#include<cstdio>
#include<cstdlib>
int m,n,S[10];
int mod(int a,int b)//Sa^Sa+1^Sa+2^...^Sa+n % b
{
	if(a==n-1) return S[a]%b;
	int cycle[b];
	int order[b+2];
	int i;
	for(i=0;i<b;i++) cycle[i]=-1;
	int now,mm;
	for(i=1,now=S[a]%b;;i++)
	{
		if(cycle[now]!=-1)
		{
			if(cycle[now]!=1) printf("%d %d %derror",cycle[now],S[a],b);
			i--;
			order[0]=order[i];
			break;
		}
		cycle[now]=i;
		order[i]=now;
		now=now*S[a]%b;
	}
	//printf(" %d",i);
	return order[mod(a+1,i)];
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&m)==1)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",&S[i]);
		printf("Case #%d: %d\n",kase++,mod(0,m));
	}
	return 0;
}

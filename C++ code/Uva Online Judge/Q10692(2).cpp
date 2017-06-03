#include<cstdio>
#include<cstdlib>
int m,n,S[10];
int moo(int a,int b,int c)
{
	if(a<b) return a;
	return b+(a-b)%c;
}
int mod(int a,int c,int b)//Sa^Sa+1^Sa+2^...^Sa+n % b
{
	if(a==n-1) return moo(S[a],c,b);
	int cycle[c+b];
	int order[c+b];
	int i;
	for(i=0;i<c+b;i++) cycle[i]=-1;
	int now,mm;
	for(i=1,now=moo(S[a],c,b);;i++)
	{
		if(cycle[now]!=-1)
		{
			//if(cycle[now]!=1) printf("%d %d %d %d %derror",i,now,cycle[now],S[a],b);
			//i--;
			mm=i-cycle[now];
			//order[0]=order[i];
			break;
		}
		cycle[now]=i;
		order[i]=now;
		now=moo(now*S[a],c,b);
	}
	//printf(" %d",i);
	return order[mod(a+1,cycle[now],mm)];
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&m)==1)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%d",&S[i]);
		printf("Case #%d: %d\n",kase++,mod(0,0,m));
	}
	return 0;
}

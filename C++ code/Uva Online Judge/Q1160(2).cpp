#include<cstdio>
#include<cstdlib>
int leader[100001];
int fin(int a)
{
	if(leader[a]==a) return a;
	return leader[a]=fin(leader[a]);
}
int main()
{
	//freopen("in.txt","r",stdin);
	for(int i=0;i<=100000;i++)
	{
		leader[i]=i;
	}
	int a,b,ans=0;
	while(scanf("%d",&a)==1)
	{
		if(a==-1)
		{
			printf("%d\n",ans);
			ans=0;
			for(int i=0;i<=100000;i++)
			{
				leader[i]=i;
			}
			continue;
		}
		ans++;
		scanf("%d",&b);
		if(fin(a)==fin(b))continue;
		leader[fin(a)]=fin(b);
		//printf("%d %d, %d %d\n",a,b,leader[a],leader[b]);
		ans--;
	}
	return 0;
}

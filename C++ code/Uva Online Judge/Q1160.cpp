#include<cstdio>
#include<cstdlib>
int n1,n2,a,b;
bool vis[100001];
int main()
{
	for(int i=0;i<=100000;i++)vis[i]=false;
	int c;
	n2=1,n1=0;
	while(scanf("%d",&a)==1&&a!=-1)
	{
		scanf("%d",&b);
		c=0;
		if(!vis[a])c++;
		if(!vis[b])c++;
		if(n1+c==n2) continue;
		vis[a]=vis[b]=true;
		n1+=c;
		n2++;
		for(int i=0;i<=100000;i++)
		{
			if(vis[i])printf(" %d",i);
		}printf("\n");
	}
	printf("%d\n",n2);
	return 0;
}

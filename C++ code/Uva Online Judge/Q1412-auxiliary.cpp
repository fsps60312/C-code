#include<cstdio>
int dfs(int dep,int sum)
{
	if(sum>8)return 0;
	if(dep==8)return 1;
	int ans=0;
	for(int i=0;i<=8;i++)
	{
		ans+=dfs(dep+1,sum+i);
	}
	return ans;
}
int main()
{
	printf("%d\n",dfs(0,0));
}

#include<cstdio>
#include<cassert>
using namespace std;
int cost[105];
inline int Cost(int a,int b,int c,int d)
{
	assert(53<=a&&a<b&&b<c&&c<d&&d<=104);
	int s[4]={a,b,c,d};
	int ans=0;
	for(int i=0;i<4;)
	{
		int j=i+1;
		while(j<4&&s[j-1]+1==s[j])++j;
		int ta=cost[s[i]-1]-cost[s[i]-1-52];
		for(int k=0;k<i;k++)if(s[i]-1-52<=s[k]&&s[k]<=s[i]-1)--ta;
		ans+=ta*(j-i);
		i=j;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<105;i++)cost[i]=1;
	cost[0]=0;
	for(int i=0,v;i<4;i++)scanf("%d",&v),cost[v]=0;
	for(int i=1;i<105;i++)cost[i]+=cost[i-1];
	int ansa=53,ansb=54,ansc=55,ansd=56,ans=Cost(53,54,55,56);
	for(int a=53;a<=104;a++)
	{
		for(int b=a+1;b<=104;b++)
		{
			for(int c=b+1;c<=104;c++)
			{
				for(int d=c+1;d<=104;d++)
				{
					int ta=Cost(a,b,c,d);
					if(ta<ans)ans=ta,ansa=a,ansb=b,ansc=c,ansd=d;
				}
			}
		}
	}
	printf("%d %d %d %d\n",ansa-52,ansb-52,ansc-52,ansd-52);
	return 0;
}

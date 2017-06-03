#include<cstdio>
#include<cassert>
#include<string>
using namespace std;
int N;
bool BetterOrEqual(const pair<string,int>&a,const pair<string,int>&b)
{
	if(a.first.size()!=b.first.size())return a.first.size()>b.first.size();
	for(int i=0;i<(int)a.first.size();i++)if(a.first[i]!=b.first[i])return a.first[i]>b.first[i];
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		pair<string,int>ans1=make_pair("0",-1),ans2=make_pair("0",-1);
		for(int i=0;i<N;i++)
		{
			static char c_str[30001];
			scanf("%s",c_str);
			int cur=0;
			while(c_str[cur]=='0')++cur;
			if(c_str[cur]=='\0')continue;
			string str=c_str+cur;
			int remain=0;
			for(int j=0;j<(int)str.size();j++)remain=remain*10+(str[j]-'0'),remain%=396;
			if(remain)continue;
			if(BetterOrEqual(make_pair(str,i),ans1))ans2=ans1,ans1=make_pair(str,i);
		}
		if(ans1.first==ans2.first)
		{
			if(ans2.second==-1)printf("%d\n",ans1.second+1);
			else printf("%d\n",ans2.second+1);
		}
		else
		{
			printf("%d\n",ans1.second+1);
		}
	}
	return 0;
}

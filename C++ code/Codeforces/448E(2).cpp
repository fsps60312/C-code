#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
typedef long long LL;
const LL bound=100000LL;
map<pair<LL,LL>,vector<LL> >DP;
void GetAnswer(const LL &h,const LL &x,LL &remain,vector<LL>&ans)
{
	if(remain==0LL)return;
	if(x==1LL||h==0LL){ans.push_back(x),remain--;return;}
	if(true)
	{
		auto it=DP.find(make_pair(h,x));
		if(it!=DP.end())
		{
			for(int i=0;i<(it->second).size()&&remain>0LL;i++)ans.push_back((it->second)[i]),remain--;
			return;
		}
	}
	vector<LL>stk,&dp=DP[make_pair(h,x)];
	for(LL i=1LL;i*i<=x;i++)if(x%i==0LL)
	{
		GetAnswer(h-1LL,i,remain,dp);
		if(i*i!=x)stk.push_back(x/i);
	}
	for(int i=(int)stk.size()-1;i>=0;i--)GetAnswer(h-1LL,stk[i],remain,dp);
	for(const LL &v:dp)ans.push_back(v);
}
LL X,K;
int main()
{
	while(scanf("%I64d%I64d",&X,&K)==2)
	{
		if(K>=100000)
		{
			putchar('1');
			if(X!=1LL)for(int i=1;i<100000;i++)printf(" 1");
			puts("");
		}
		else
		{
			LL remain=100000LL;
			vector<LL>ans;
			GetAnswer(K,X,remain,ans);
			for(int i=0;i<(int)ans.size();i++)
			{
				if(i)putchar(' ');
				printf("%I64d",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}

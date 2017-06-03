#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<map>
using namespace std;
typedef long long LL;
const LL bound=100000LL;
map<LL,vector<LL> >F;
void GetAnswer(const LL &h,const LL &x,LL &remain,vector<LL>&ans)
{
	if(remain==0LL)return;
	assert(remain>0LL);
	if(x==1LL||h==0LL){ans.push_back(x),remain--;return;}
	vector<LL>&f=F[x];
	if(f.empty())
	{
		vector<LL>stk;
		for(LL i=1LL;i*i<=x;i++)if(x%i==0LL)
		{
			f.push_back(i);
			if(i*i!=x)stk.push_back(x/i);
		}
		for(int i=(int)stk.size()-1;i>=0;i--)f.push_back(stk[i]);
	}
	for(const LL &v:f)GetAnswer(h-1LL,v,remain,ans);
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

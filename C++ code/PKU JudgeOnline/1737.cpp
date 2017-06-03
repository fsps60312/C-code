#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
int CountCase(const int remain,const int max_val)
{
	if(remain==0)return 1;
	int ans=0;
	for(int i=min(remain,max_val);i>=1;i--)ans+=CountCase(remain-i,i);
	return ans;
}
void CountCase()
{
	int ans=0;
	for(int i=1;i<=50;i++)ans+=CountCase(50,i);
	printf("ans=%d\n",ans);
	exit(0);
}
int N;
map<vector<int>,LL>DP[51];
void InitializeDP2()
{
	DP[2].clear();
	vector<int>s;
	s.push_back(1),s.push_back(1);
	DP[2][s]=1;
	s.clear(),s.push_back(2);
	DP[2][s]=1;
}
LL ANS[51];
int main()
{
//	CountCase();
	ANS[1]=ANS[2]=1LL;
	InitializeDP2();
	for(int n=3;n<=50;n++)
	{
		DP[n].clear();
		for(const auto &it:DP[n-1])
		{
			vector<int>s=it.first;
			if(true){int tmp=0;for(const auto v:s)tmp+=v;assert(tmp==n-1);}
			vector<int>vals=s;unique(vals.begin(),vals.end());
			for(const int v:vals)
			{
				auto ir=upper_bound(s.begin(),s.end(),v),il=lower_bound(s.begin(),s.end(),v);
				ir--;
				(*ir)++;
				printf("s=");for(int i=0;i<(int)s.size();i++)printf(" %d",s[i]);puts("");
				DP[n][s]+=it.second*(ir-il+1);
				(*ir)--;
			}
			s.push_back(1);
			for(int i=1;i<(int)s.size();i++)s[i]=s[i-1];
			s[0]=1;
			DP[n][s]+=it.second;
		}
		vector<int>s;s.push_back(n);
		printf("n=%d,sum=%lld\n",n,DP[n][s]);
	}
	while(scanf("%d",&N)==1&&N)
	{
		
	}
	return 0;
}

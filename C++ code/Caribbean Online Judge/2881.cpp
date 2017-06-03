#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
int N,TO[300001];
int To(const int a){return TO[a]==a?a:(TO[a]=To(TO[a]));}
int main()
{
//	assert(0);
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&TO[i]);
			if(!TO[i])TO[i]=i;
		}
		TO[0]=0;
		vector<pair<int,int> >query;
		int querycount;scanf("%d",&querycount);
		for(int i=0,type,x;i<querycount;i++)
		{
			scanf("%d%d",&type,&x);
			if(type==1)query.push_back(make_pair(-1,x));
			else if(type==2)query.push_back(make_pair(x,TO[x])),TO[x]=x;
			else assert(0);
		}
		for(int i=1;i<=N;i++)if(TO[i]!=i)query.push_back(make_pair(i,TO[i])),TO[i]=i;
		vector<int>ans;
		for(int i=(int)query.size()-1;i>=0;i--)
		{
			const auto &p=query[i];
			if(p.first==-1)
			{
				assert(i<querycount);
				ans.push_back(To(p.second));
			}
			else
			{
				assert(p.first!=p.second&&TO[p.first]==p.first);
				if(To(p.second)==p.first)TO[p.first]=0;
				else TO[p.first]=p.second;
			}
		}
		for(int i=(int)ans.size()-1;i>=0;i--)
		{
			if(ans[i]==0)puts("CIKLUS");
			else printf("%d\n",ans[i]);
		}
		break;
	}
	return 0;
}

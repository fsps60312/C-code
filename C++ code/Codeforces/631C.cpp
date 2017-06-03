#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M,S[200000];
pair<int,int>STK[200002];
int LAST;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		STK[0]=make_pair(1,INF);
		LAST=0;
		for(int i=0,t,r;i<M;i++)
		{
			scanf("%d%d",&t,&r);
			while(STK[LAST].second<r)LAST--;
			STK[++LAST]=make_pair(t,r);
		}
		sort(S,S+STK[1].second);
		STK[++LAST].second=0;
		vector<int>ans;
		for(int i=N-1;i>=STK[1].second;i--)ans.push_back(S[i]);
		for(int l=0,r=STK[1].second-1,i=1;i<LAST;i++)
		{
			for(int j=0;j<STK[i].second-STK[i+1].second;j++)
			{
				if(STK[i].first==1)ans.push_back(S[r--]);
				else if(STK[i].first==2)ans.push_back(S[l++]);
				else assert(0);
			}
		}
		for(int i=N-1;i>=0;i--)
		{
			if(i<N-1)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}

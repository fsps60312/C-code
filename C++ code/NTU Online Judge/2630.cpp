#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
LL B;
int K,CD,CP;
pair<LL,int>D[50000],P[50000];
vector<pair<LL,int> >S;
vector<LL>SUM;
LL GetValue(const int l)
{
	const int r=l+K-1;
	assert(r>=CD-1&&l<=CD);
	return (B+(SUM[CD-1+1]-SUM[l-1+1]))*(100+(SUM[r+1]-SUM[CD-1+1]));
}
int main()
{
//	freopen("")
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%d%d%d",&B,&K,&CD,&CP)==4)
	{
		for(int i=0,v;i<CD;i++)scanf("%d",&v),D[i]=make_pair((LL)v,i+1);
		for(int i=0,v;i<CP;i++)scanf("%d",&v),P[i]=make_pair((LL)v,i+1);
//		static int kase=0;
//		if(kase++)puts("");
		if(CD+CP<=K)
		{
			printf("%d %d\n",CD,CP);
			for(int i=1;i<=CD;i++)
			{
				if(i>1)putchar(' ');
				printf("%d",i);
			}
			puts("");
			for(int i=1;i<=CP;i++)
			{
				if(i>1)putchar(' ');
				printf("%d",i);
			}
			puts("");
		}
		else
		{
			sort(D,D+CD),sort(P,P+CP);
			S.clear();
			for(int i=0;i<CD;i++)S.push_back(D[i]);
			for(int i=CP-1;i>=0;i--)S.push_back(P[i]);
			SUM.clear(),SUM.push_back(0);
			for(int i=0;i<CD+CP;i++)SUM.push_back(SUM[i]+S[i].first);
			int ans=0;
			while(ans+K<CD)ans++;
			for(int i=ans;i<=CD&&i+K<=CD+CP;i++)if(GetValue(i)>GetValue(ans))ans=i;
			printf("%d %d\n",CD-ans,ans+K-CD);
			for(int i=ans;i<CD;i++)
			{
				if(i>ans)putchar(' ');
				printf("%d",S[i].second);
			}
			puts("");
			for(int i=CD;i<ans+K;i++)
			{
				if(i>CD)putchar(' ');
				printf("%d",S[i].second);
			}
			puts("");
		}
	}
	return 0;
}

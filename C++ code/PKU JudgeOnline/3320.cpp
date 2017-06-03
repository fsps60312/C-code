#include<cstdio>
//#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void assert(const bool valid){if(valid)return;for(int a=0,b=0;;)a/=b;}
const int INF=2147483647;
int N,M,S[1000000];
void Discretize()
{
	vector<int>v;
	for(int i=0;i<N;i++)v.push_back(S[i]);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	M=v.size();
	for(int i=0;i<N;i++)S[i]=lower_bound(v.begin(),v.end(),S[i])-v.begin();
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		Discretize();
		static int cnt[1000000];
		for(int i=0;i<M;i++)cnt[i]=0;
		int uncovered=M,ans=INF;
		for(int l=0,r=-1;l<N;l++)
		{
			while(r+1<N&&uncovered)if(!cnt[S[++r]]++)uncovered--;
			if(uncovered)break;
			if(r-l+1<ans)ans=r-l+1;
			if(!--cnt[S[l]])uncovered++;
		}
		assert(ans!=INF);
		printf("%d\n",ans);
	}
	return 0;
}

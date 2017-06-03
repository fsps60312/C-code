#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
int PARENT[1000000];
vector<int>ET[1000000];
int ANS[1000000];
LL M;
int PATH[1000000];
bool VIS[1000000];
void GetAnswers(const int u,const vector<int>&cyc,const int loc,const int depth)
{
	VIS[u]=true;
	PATH[depth]=u;
	if(depth>=M)ANS[u]=PATH[depth-M];
	else ANS[u]=cyc[loc];
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		int nxtloc=loc-1;
		if(nxtloc<0)nxtloc+=(int)cyc.size();
		GetAnswers(nxt,cyc,nxtloc,depth+1);
	}
}
void Solve(const vector<int>&cyc)
{
	const int n=(int)cyc.size();
	for(int i=0;i<n;i++)
	{
		ANS[cyc[i]]=cyc[(i+M)%(LL)n];
		VIS[cyc[i]]=true;
		for(int j=0;j<(int)ET[cyc[i]].size();j++)
		{
			const int nxt=ET[cyc[i]][j];
			PATH[0]=cyc[i];
			if(nxt!=cyc[(i+1)%n])GetAnswers(nxt,cyc,(int)((i+M-1LL)%(LL)n),1);
		}
	}
}
int N,K;
LL S[1000000];
void BuildParents()
{
	for(int i=0;i<N;i++)ET[i].clear();
	int l=0,r=K;
	for(int i=0;i<N;i++)
	{
		while(l+1<=i&&r+1<N&&max(S[r+1]-S[i],S[i]-S[l+1])<max(S[r]-S[i],S[i]-S[l]))++l,++r;
		assert(l<=i&&i<=r);
		PARENT[i]=(S[r]-S[i]>S[i]-S[l]?r:l);
		ET[PARENT[i]].push_back(i);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld",&N,&K,&M)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		BuildParents();
//		for(int i=0;i<N;i++)printf("%d->%d\n",i+1,PARENT[i]+1);
		for(int i=0;i<N;i++)VIS[i]=false;
		for(int i=0;i<N;i++)if(!VIS[i])
		{
			int cur=i;
			for(;!VIS[cur];cur=PARENT[cur])VIS[cur]=true;
			vector<int>cyc;
			for(;VIS[cur];cur=PARENT[cur])cyc.push_back(cur),VIS[cur]=false;
			Solve(cyc);
		}
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]+1);
		}
		puts("");
	}
	return 0;
}

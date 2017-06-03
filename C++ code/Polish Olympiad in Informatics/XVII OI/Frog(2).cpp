#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long LL;
int PARENT[1000000];
int HEAD[1000000],NEXT[1000000],VAL[1000000],NSZ;
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
	for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])
	{
		const int nxt=VAL[cur];
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
		for(int cur=HEAD[cyc[i]];cur!=-1;cur=NEXT[cur])
		{
			const int nxt=VAL[cur];
			PATH[0]=cyc[i];
			if(nxt!=cyc[(i+1)%n])GetAnswers(nxt,cyc,(int)((i+M-1LL)%(LL)n),1);
		}
	}
}
int N,K;
LL S[1000000];
void BuildParents()
{
	int l=0,r=K;
	for(int i=0;i<N;i++)
	{
		while(l+1<=i&&r+1<N&&max(S[r+1]-S[i],S[i]-S[l+1])<max(S[r]-S[i],S[i]-S[l]))++l,++r;
		assert(l<=i&&i<=r);
		PARENT[i]=(S[r]-S[i]>S[i]-S[l]?r:l);
	}
	for(int i=0;i<N;i++)HEAD[i]=-1;
	NSZ=0;
	for(int i=0;i<N;i++)
	{
		NEXT[NSZ]=HEAD[PARENT[i]];
		VAL[NSZ]=i;
		HEAD[PARENT[i]]=NSZ++;
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
			vector<int>().swap(cyc);
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

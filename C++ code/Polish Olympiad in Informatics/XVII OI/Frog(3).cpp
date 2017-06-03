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
vector<int>CYC;
int DEPTH,LOC;
void GetAnswers(const int u)
{
	if(--LOC<0)LOC=(int)CYC.size()-1;
	++DEPTH;
	VIS[u]=true;
	PATH[DEPTH]=u;
	if(DEPTH>=M)ANS[u]=PATH[DEPTH-M];
	else ANS[u]=CYC[LOC];
	for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])
	{
		static int nxt;nxt=VAL[cur];
		GetAnswers(nxt);
	}
	--DEPTH;
	if(++LOC==(int)CYC.size())LOC=0;
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
			DEPTH=0;
			LOC=(int)((i+M)%(LL)n);
			if(nxt!=cyc[(i+1)%n])GetAnswers(nxt);
			assert(DEPTH==0&&LOC==(int)((i+M)%(LL)n));
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
			CYC.clear();
			for(;VIS[cur];cur=PARENT[cur])CYC.push_back(cur),VIS[cur]=false;
			Solve(CYC);
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

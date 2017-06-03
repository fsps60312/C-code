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
int DEPTH,LOC,U;
bool GO_TO_CH;
void GetAnswers()
{
	if(--LOC<0)LOC=(int)CYC.size()-1;
	++DEPTH;
	VIS[U]=true;
	PATH[DEPTH]=U;
	if(DEPTH>=M)ANS[U]=PATH[DEPTH-M];
	else ANS[U]=CYC[LOC];
	GO_TO_CH=false;
	for(int cur=HEAD[U];cur!=-1;cur=NEXT[cur])
	{
		GO_TO_CH=true;
		U=VAL[cur];
		GetAnswers();
	}
	if(GO_TO_CH)U=PARENT[U];
	--DEPTH;
	if(++LOC==(int)CYC.size())LOC=0;
}
void Solve()
{
	const int n=(int)CYC.size();
	for(int i=0;i<n;i++)
	{
		ANS[CYC[i]]=CYC[(i+M)%(LL)n];
		VIS[CYC[i]]=true;
		for(int cur=HEAD[CYC[i]];cur!=-1;cur=NEXT[cur])
		{
			U=VAL[cur];
			PATH[0]=CYC[i];
			DEPTH=0;
			LOC=(int)((i+M)%(LL)n);
			if(U!=CYC[(i+1)%n])GetAnswers();
			assert(DEPTH==0&&LOC==(int)((i+M)%(LL)n));
		}
	}
}
int N,K;
LL *S;
void BuildParents()
{
	S=new LL[N];
	for(int i=0;i<N;i++)scanf("%lld",&S[i]);
	int l=0,r=K;
	for(int i=0;i<N;i++)
	{
		while(l+1<=i&&r+1<N&&max(S[r+1]-S[i],S[i]-S[l+1])<max(S[r]-S[i],S[i]-S[l]))++l,++r;
		assert(l<=i&&i<=r);
		PARENT[i]=(S[r]-S[i]>S[i]-S[l]?r:l);
	}
	delete[]S;
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
		BuildParents();
//		for(int i=0;i<N;i++)printf("%d->%d\n",i+1,PARENT[i]+1);
		for(int i=0;i<N;i++)VIS[i]=false;
		for(int i=0;i<N;i++)if(!VIS[i])
		{
			int cur=i;
			for(;!VIS[cur];cur=PARENT[cur])VIS[cur]=true;
			CYC.clear();
			for(;VIS[cur];cur=PARENT[cur])CYC.push_back(cur),VIS[cur]=false;
			Solve();
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

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
void GetAnswers(const int _u,const vector<int>&cyc,const int _loc)
{
	static int locs[1000000],sts[1000000],top;
	top=1,PATH[top]=_u,locs[top]=_loc,sts[top]=-2;
	for(;top>0;--top)
	{
		const int u=PATH[top],loc=locs[top],cur=sts[top];
//		printf("top=%d,u=%d\n",top,u);
		if(cur==-2)
		{
			VIS[u]=true;
			if(top>=M)ANS[u]=PATH[top-M];
			else ANS[u]=cyc[loc];
			PATH[top]=u,locs[top]=loc,sts[top]=HEAD[u],++top;
		}
		else if(cur!=-1)
		{
			const int nxt=VAL[cur];
			int nxtloc=loc-1;
			if(nxtloc<0)nxtloc+=(int)cyc.size();
			PATH[top]=u,locs[top]=loc,sts[top]=NEXT[cur],++top;
			PATH[top]=nxt,locs[top]=nxtloc,sts[top]=-2,++top;
		}
	}
}
void Solve(const vector<int>&cyc)
{
	const int n=(int)cyc.size();
//	for(int i=0;i<n;i++)printf(" %d",cyc[i]+1);puts("");
	for(int i=0;i<n;i++)
	{
		ANS[cyc[i]]=cyc[(i+M)%(LL)n];
		VIS[cyc[i]]=true;
//		int cnt=0;
//		for(int cur=HEAD[cyc[i]];cur!=-1;cur=NEXT[cur])
//		{
//			const int nxt=VAL[cur];
//			printf("%d->%d\n",cyc[i]+1,nxt+1);
//			if(nxt==cyc[(i+1)%n])++cnt;
//		}
//		printf("cnt=%d\n",cnt);
//		assert(cnt==1);
		for(int cur=HEAD[cyc[i]];cur!=-1;cur=NEXT[cur])
		{
			const int nxt=VAL[cur];
			PATH[0]=cyc[i];
//			puts("a");
			if(nxt!=cyc[(i+n-1)%n])GetAnswers(nxt,cyc,(int)((i+M-1LL)%(LL)n));
//			puts("b");
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
//	freopen("zab2a.in","r",stdin);
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
			static vector<int>cyc;cyc.clear();
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

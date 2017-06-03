#include<cstdio>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
typedef long long LL;
int T,N;
LL MOD;
int SZ[500000],OUT[500000],PARENT[500000],CNT[500000];
bool ISP[500000]; 
vector<int>CH[500000];
vector<int>P;
LL Pow(LL a,int b)
{
	LL ans=1LL;
	while(b)
	{
		if(b&1)(ans*=a)%=MOD;
		(a*=a)%=MOD;
		b>>=1;
	}
	return ans;
}
int main()
{
	for(int i=0;i<500000;i++)ISP[i]=false;
	ISP[2]=ISP[3]=true;
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]>=500000)break;
		ISP[P[i]]=true;
	}
//	freopen("in.txt","r",stdin);
//	T=1;
	scanf("%d",&T);
	while(T--)
	{
//		N=500000,MOD=1000000000;
		scanf("%d%lld",&N,&MOD);
		for(int i=0;i<N;i++)CH[i].clear(),OUT[i]=0,CNT[i]=0;
		for(int i=1;i<N;i++)
		{
			int &p=PARENT[i];
//			p=i;
			scanf("%d",&p);
			CH[--p].push_back(i),OUT[p]++;
		}
		queue<int>q;
		for(int i=0;i<N;i++)if(!OUT[i])q.push(i);
		for(int i=2;i<=N-1;i++)CNT[i]++;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			int &sz=SZ[u]=1;
			for(const int nxt:CH[u])sz+=SZ[nxt];
			if(u)
			{
				CNT[sz]--;
				if(!--OUT[PARENT[u]])q.push(PARENT[u]);
			}
		}
		for(int i=2;i<N;i++)if(!ISP[i]&&CNT[i])
		{
			int n=i;
			for(int j=0;P[j]*P[j]<=n;j++)while(n%P[j]==0)n/=P[j],CNT[P[j]]+=CNT[i];
			CNT[n]+=CNT[i];
			CNT[i]=0;
		}
		LL ans=1LL;
		for(int i=2;i<=N-1;i++)assert(CNT[i]>=0),(ans*=Pow(i,CNT[i]))%=MOD;
		printf("%lld\n",ans);
	}
	return 0;
}

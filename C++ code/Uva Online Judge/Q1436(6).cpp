#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
int T,N;
LL MOD;
int SZ[500000],OUT[500000],PARENT[500000],CNT[500000];
int ISP[500000]; 
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
	for(int i=0;i<500000;i++)ISP[i]=-1;
	ISP[2]=0,ISP[3]=1;
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
		ISP[P[i]]=i;
	}
//	freopen("in.txt","r",stdin);
//	T=1;
	scanf("%d",&T);
	while(T--)
	{
		N=500000,MOD=1000000000;
//		scanf("%d%lld",&N,&MOD);
		for(int i=0;i<N;i++)CH[i].clear(),OUT[i]=0,CNT[i]=0;
		for(int i=1;i<N;i++)
		{
			int &p=PARENT[i];
			p=i;
//			scanf("%d",&p);
			CH[--p].push_back(i),OUT[p]++;
		}
		queue<int>q;
		for(int i=0;i<N;i++)if(!OUT[i])q.push(i);
		for(int i=0;P[i]<=N-1;i++)
		{
			int &cnt=CNT[i]=0,t=N-1;
			while(t/=P[i])cnt+=t;
		}
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			int &sz=SZ[u]=1;
			for(const int nxt:CH[u])sz+=SZ[nxt];
			if(u)
			{
				if(ISP[sz]!=-1)CNT[ISP[sz]]--;
				else for(int i=0,n=sz;P[i]<=n;i++)while(n%P[i]==0)n/=P[i],CNT[i]--;
				if(!--OUT[PARENT[u]])q.push(PARENT[u]);
			}
		}
		LL ans=1LL;
		for(int i=0;i<N;i++)(ans*=Pow(P[i],CNT[i]))%=MOD;
		printf("%lld\n",ans);
	}
	return 0;
}

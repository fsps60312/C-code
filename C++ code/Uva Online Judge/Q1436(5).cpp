#include<cstdio>
#include<vector>
#include<map>
#include<queue>
using namespace std;
typedef long long LL;
int T,N;
LL MOD,ANS[500000];
int SZ[500000],OUT[500000],PARENT[500000];
vector<int>CH[500000];
vector<int>P;
void Mul(map<int,int>&s,const int n,const int sign)
{
	for(int i=0;P[i]<=n;i++)
	{
		int cnt=0,t=n;
		while(t/=P[i])cnt+=t;
		s[P[i]]+=cnt*sign;
	}
}
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
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0);
		if(P[i]>500000)break;
	}
//	freopen("in.txt","r",stdin);
//	T=1;
	scanf("%d",&T);
	while(T--)
	{
//		N=500000,MOD=1000000000;
		scanf("%d%lld",&N,&MOD);
		for(int i=0;i<N;i++)CH[i].clear(),OUT[i]=0;
		for(int i=1;i<N;i++)
		{
			int &p=PARENT[i];
//			p=i;
			scanf("%d",&p);
			CH[--p].push_back(i),OUT[p]++;
		}
		queue<int>q;
		for(int i=0;i<N;i++)if(!OUT[i])q.push(i);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
//			printf("u=%d\n",u);
			int &sz=SZ[u]=1;
			LL &ans=ANS[u]=1LL;
			map<int,int>s;
			for(const int nxt:CH[u])
			{
				sz+=SZ[nxt],(ans*=ANS[nxt])%=MOD;
				Mul(s,SZ[nxt],-1);
			}
			Mul(s,sz-1,1);
			for(const auto &it:s)(ans*=Pow(it.first,it.second))%=MOD;
			if(u&&!--OUT[PARENT[u]])q.push(PARENT[u]);
		}
		printf("%lld\n",ANS[0]);
	}
	return 0;
}

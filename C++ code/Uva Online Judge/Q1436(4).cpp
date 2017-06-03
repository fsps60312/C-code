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
vector<int>FV[500000];
vector<int>FC[500000];
void GetF(int n)
{
	vector<int>&fv=FV[n],&fc=FC[n];
	for(int i=0;P[i]*P[i]<=n;i++)
	{
		int cnt=0;
		while(n%P[i]==0)n/=P[i],cnt++;
		if(cnt>0)fv.push_back(P[i]),fc.push_back(cnt);
	}
	if(n>1)fv.push_back(n),fc.push_back(1);
}
void Mul(map<int,int>&s,const int n,const int sign)
{
	vector<int>&fv=FV[n],&fc=FC[n];
	for(int i=0;i<fv.size();i++)s[fv[i]]+=fc[i]*sign;
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
		if(P[i]*P[i]>500000)break;
	}
	for(int i=2;i<500000;i++)GetF(i);
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%lld",&N,&MOD);
		for(int i=0;i<N;i++)CH[i].clear(),OUT[i]=0;
		for(int i=1;i<N;i++)
		{
			int &p=PARENT[i];
			scanf("%d",&p),CH[--p].push_back(i),OUT[p]++;
		}
		queue<int>q;
		for(int i=0;i<N;i++)if(!OUT[i])q.push(i);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			int &sz=SZ[u]=1;
			LL &ans=ANS[u]=1LL;
			map<int,int>s;
			for(const int nxt:CH[u])
			{
				sz+=SZ[nxt],(ans*=ANS[nxt])%=MOD;
				for(int i=2;i<=SZ[nxt];i++)Mul(s,i,-1);
			}
			for(int i=2;i<sz;i++)Mul(s,i,1);
			for(const auto &it:s)(ans*=Pow(it.first,it.second))%=MOD;
			if(u&&!--OUT[PARENT[u]])q.push(PARENT[u]);
		}
		printf("%lld\n",ANS[0]);
	}
	return 0;
}

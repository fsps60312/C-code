#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
LL Solve(LL ans,vector<LL>&s)
{
	const int n=s.size();
	for(int b=60,row=0;b>=0&&row<n;b--)
	{
		for(int i=row;i<n;i++)if(s[i]&(1LL<<b)){swap(s[row],s[i]);break;}
		if(!(s[row]&(1LL<<b)))continue;
		for(int i=row+1;i<n;i++)if(s[i]&(1LL<<b))s[i]^=s[row];
		row++;
	}
	for(const LL v:s)ans=max(ans,ans^v);
	return ans;
}
struct DisjointSets
{
	int PARENT[50000];
	LL XO[50000];
	void Clear(const int n){for(int i=0;i<n;i++)PARENT[i]=i,XO[i]=0LL;}
	int Find(const int a)
	{
		if(PARENT[a]==a){assert(XO[a]==0LL);return a;}
		const int parent=PARENT[a];
		PARENT[a]=Find(PARENT[a]);
		XO[a]^=XO[parent];
		return PARENT[a];
	}
	bool Merge(int _a,int _b,const LL xo)
	{
		int a,b;
		if((a=Find(_a))==(b=Find(_b)))return false;
		PARENT[a]=b;
		assert(XO[a]==0LL&&XO[b]==0LL);
		XO[a]=xo^XO[_a];
		return true;
	}
	LL QueryXO(const int a){Find(a);return XO[a];}
}DJ;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		DJ.Clear(N);
		vector<LL>cycles;
		for(int i=0,a,b;i<M;i++)
		{
			static LL c;
			scanf("%d%d%lld",&a,&b,&c),a--,b--;
			if(!DJ.Merge(a,b,c))cycles.push_back(DJ.QueryXO(a)^DJ.QueryXO(b)^c);
		}
		printf("%lld\n",Solve(DJ.QueryXO(0)^DJ.QueryXO(N-1),cycles));
	}
	return 0;
}

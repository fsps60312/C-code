#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
struct Bit
{
	int DATA[100001],N;
	void Clear(const int _N){N=_N;for(int i=1;i<=N;i++)DATA[i]=0;}
	void Add(int i,const int v){while(i)DATA[i]+=v,i-=(i&(-i));}
	int Query(int i){int ans=0;while(i<=N)ans+=DATA[i],i+=(i&(-i));return ans;}
}BIT;
int N,M,T[100000],J[100000],I[100000];
bool Solve(const int tick)
{
	static int mn[100001],mx[100001];
	for(int i=1;i<=N;i++)mn[i]=INF,mx[i]=-INF;
	for(int i=0;i<tick;i++)getmin(mn[J[i]],T[i]),getmax(mx[J[i]],T[i]);
	BIT.Clear(M);
	for(int i=1;i<=N;i++)if(mn[i]!=INF)BIT.Add(mx[i],1),BIT.Add(mn[i]-1,-1);
	vector<pair<int,int> >counts;
	for(int i=0;i<tick;i++)counts.push_back(make_pair(T[i],I[i]+1));
	counts.push_back(make_pair(0,0)),counts.push_back(make_pair(M+1,0));
	sort(counts.begin(),counts.end());
	int dif=0;
	for(int i=1;i<(int)counts.size();i++)
	{
		if(counts[i].first==counts[i-1].first&&counts[i].second!=counts[i-1].second)return false;
		dif+=abs(counts[i].second-counts[i-1].second);
	}
	if(dif>N*2)return false;
	for(int i=0;i<tick;i++)if(BIT.Query(T[i])>I[i]+1)return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<M;i++)scanf("%d%d%d",&T[i],&J[i],&I[i]);
		int l=0,r=M;
		while(l<r)
		{
			const int mid=(l+r+1)/2;
			if(Solve(mid))l=mid;
			else r=mid-1;
		}
		printf("%d\n",r);
	}
	return 0;
}

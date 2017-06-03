#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int T,N;
vector<int>S;
int CNT[10001];
int Solve(const int a,const int b)
{
	if(b-a+1>10000)return 0;
	int mn=S[a],mx=S[a];
	CNT[mn]=0;
	for(int i=a;i<=b;i++)
	{
		const int v=S[i];
		while(mn>v)CNT[--mn]=0;
		while(mx<v)CNT[++mx]=0;
		if(++CNT[v]>=2)return 0;
	}
	int pre=-1,ans=INF;
	for(int i=mn;i<=mx;i++)
	{
		if(CNT[i]==0)continue;
		if(pre!=-1&&i-pre<ans)ans=i-pre;
		pre=i; 
	}
	assert(ans!=INF);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		S.clear();
		for(int i=0,v;i<N;i++)scanf("%d",&v),S.push_back(v);
		int q;
		scanf("%d",&q);
		for(int a,b;q--;)scanf("%d%d",&a,&b),printf("%d\n",Solve(--a,--b));
	}
	return 0;
}

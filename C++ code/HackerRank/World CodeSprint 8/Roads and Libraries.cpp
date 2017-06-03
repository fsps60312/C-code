#include<cstdio>
#include<cassert>
using namespace std;
struct DisjointSets
{
	int S[100000];
	void Clear(const int n){for(int i=0;i<n;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b)
	{
		if((a=Find(a))==(b=Find(b)))return false;
		return S[a]=b,true;
	}
}DJ;
int N,M,CL,CR;
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;scanf("%d",&querycount);
	while(querycount--)
	{
		scanf("%d%d%d%d",&N,&M,&CL,&CR);
		DJ.Clear(N);
		int region=N;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			if(DJ.Merge(a,b))--region;
		}
		printf("%lld\n",CL<CR?(long long)CL*N:(long long)CL*region+(long long)CR*(N-region));
	}
	return 0;
}

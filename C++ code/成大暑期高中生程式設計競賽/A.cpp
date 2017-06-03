#include<cstdio>
#include<cassert>
//#include<algorithm>
using namespace std;
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
struct DisjointSets
{
	int S[100];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b)
	{
		if((a=Find(a))==(b=Find(b)))return false;
		S[a]=b;
		return true;
	}
}DJ;
int N,M;
bool Solve()
{
	for(int i=1;i<N;i++)if(DJ.Find(i)!=DJ.Find(0))return false;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		DJ.Clear(N);
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			DJ.Merge(a,b);
		}
		printf("%d\n",Solve()?N-1:-1);
	}
	return 0;
}

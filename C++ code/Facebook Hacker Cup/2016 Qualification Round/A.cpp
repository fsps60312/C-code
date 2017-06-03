#include<stdio.h>
#include<map>
#include<cassert>
using namespace std;
int N;
int X[2000],Y[2000];
int Sq(const int x){return x*x;}
int main()
{
	freopen("Ain.txt","r",stdin);
	freopen("out.txt","w",stdout);
	static int testcase;assert(scanf("%d",&testcase)==1);
	while(testcase--)
	{
		assert(scanf("%d",&N)==1);
		for(int i=0;i<N;i++)assert(scanf("%d%d",&X[i],&Y[i])==2);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			map<int,int>dist;
			for(int j=0;j<N;j++)if(i!=j)dist[Sq(X[i]-X[j])+Sq(Y[i]-Y[j])]++;
			for(const auto &it:dist)ans+=it.second*(it.second-1)/2;
		}
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	assert(scanf("%d",&testcase)!=1);
	return 0;
}

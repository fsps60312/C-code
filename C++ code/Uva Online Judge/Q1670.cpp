#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
int DEG[100000];
int main()
{
	while(scanf("%d",&N)==1)
	{
		assert(N>=2&&N<=100000);
		for(int i=0;i<N;i++)DEG[i]=0;
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			assert(a>=1&&a<=N&&b>=1&&b<=N&&a!=b);
			DEG[--a]++,DEG[--b]++;
		}
		vector<int>leaf;
		for(int i=0;i<N;i++)if(DEG[i]==1)leaf.push_back(i);
		const int ans=(leaf.size()+1)/2;
		printf("%d\n",ans);
		for(int i=1;i<leaf.size();i+=2)printf("%d %d\n",leaf[i-1]+1,leaf[i]+1);
		if(leaf.size()&1)printf("%d %d\n",leaf[leaf.size()-2]+1,leaf[leaf.size()-1]+1);
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N,M;
int Solve(const vector<int>&a,const vector<int>&b)
{
	if(a.size()!=b.size())return 0;
	puts("a");
	for(int i=0;i<(int)a.size();i++)if(a[i]!=b[i])return 0;
	puts("b");
	return 1;
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		vector<int>a,b;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			if(a.empty()||a.back()!=v)a.push_back(v);
		}
		for(int i=0,v;i<M;i++)
		{
			scanf("%d",&v);
			if(b.empty()||b.back()!=v)b.push_back(v);
		}
		for(int i=0;i<(int)a.size();i++)printf(" %d",a[i]);puts("");
		for(int i=0;i<(int)b.size();i++)printf(" %d",b[i]);puts("");
		printf("%d\n",Solve(a,b));
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<cassert>
using namespace std; 
int N,M;
int RF[100001];
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=1;i<=N;i++)RF[i]=0;
		for(int i=1,f;i<=N;i++)
		{
			scanf("%d",&f);
			if(RF[f]==0)RF[f]=i;
			else RF[f]=-1;
		}
		vector<int>ans;
		bool ambiguity=false,impossible=false;
		for(int i=0,b;i<M;i++)
		{
			scanf("%d",&b);
			if(RF[b]==0)impossible=true;
			else if(RF[b]==-1)ambiguity=true;
			else ans.push_back(RF[b]);
		}
		if(impossible)puts("Impossible");
		else if(ambiguity)puts("Ambiguity");
		else
		{
			puts("Possible");
			assert(ans.size()==M);
			for(int i=0;i<M;i++)
			{
				if(i)putchar(' ');
				printf("%d",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}

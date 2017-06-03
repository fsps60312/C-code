#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N,M;
vector<int>ET[200];
int main()
{
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&N,&M)==2);
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			assert(scanf("%d%d",&a,&b));
			a--,b--;
			ET[b].push_back(a);
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			if(ET[i].empty())ans++;
			else ans+=(int)ET[i].size()-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}

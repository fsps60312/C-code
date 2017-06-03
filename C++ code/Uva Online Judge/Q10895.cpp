#include<cstdio>
#include<vector>
#include<map>
#include<set>
using namespace std;
map<int,map<int,int> >S;
int N,M; 
int main()
{
	while(scanf("%d%d",&N,&M)==2)
	{
		S.clear();
		for(int r=1;r<=N;r++)
		{
			vector<int>idx;
			int cnt,v;
			scanf("%d",&cnt);
			for(int i=0;i<cnt;i++)scanf("%d",&v),idx.push_back(v);
			for(int i=0;i<cnt;i++)scanf("%d",&v),S[idx[i]][r]=v;
		}
		printf("%d %d\n",M,N);
		int c=1;
		for(auto &it:S)
		{
			for(;c<it.first;c++)puts("0"),puts("");
			printf("%d",it.second.size());
			for(auto &e:it.second)printf(" %d",e.first);puts("");
			bool printed=false;
			for(auto &e:it.second)
			{
				if(printed)putchar(' ');
				printf("%d",e.second);
				printed|=true;
			}
			puts("");
			c++;
		}
		for(;c<=M;c++)puts("0"),puts("");
	}
	return 0;
}

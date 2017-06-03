#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
int N,K;
vector<int>LOCS[1000000],X,Y;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<K;i++)LOCS[i].clear();
		for(int i=0,c;i<N;i++)
		{
			scanf("%d",&c),--c;
			LOCS[c].push_back(i);
		}
		if(true)
		{
			int m,l;scanf("%d%d",&m,&l);
			X.resize(m),Y.resize(l);
			for(int i=0;i<m;i++)scanf("%d",&X[i]),--X[i];
			for(int i=0;i<l;i++)scanf("%d",&Y[i]),--Y[i];
		}
		int l=0;
		for(int i=0;i<(int)X.size();i++)
		{
			vector<int>::const_iterator it=upper_bound(LOCS[X[i]].begin(),LOCS[X[i]].end(),l);
			if(it!=LOCS[X[i]].end())l=*it;
			else{l=N;break;}
		}
		int r=N-1;
		for(int i=0;i<(int)Y.size();i++)
		{
			vector<int>::const_iterator it=lower_bound(LOCS[Y[i]].begin(),LOCS[Y[i]].end(),r);
			if(it!=LOCS[Y[i]].begin())r=*--it;
			else{r=-1;break;} 
		}
		if(l<=r)
		{
			const vector<int>&locs=LOCS[X.back()];
			l=(int)(lower_bound(locs.begin(),locs.end(),l)-locs.begin());
			r=(int)(lower_bound(locs.begin(),locs.end(),r)-locs.begin());
			printf("%d\n",r-l+1);
			for(int i=l;i<=r;i++)
			{
				if(i>l)putchar(' ');
				printf("%d",locs[i]+1);
			}
			puts("");
		}
		else puts("0\n");
	}
	return 0;
}

#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int V,C,DICT[500][26],CHAL[500][26];
vector<int>ET[1000];
int MATCH[1000];
bool VIS[1000];
bool Expand(const int &u)
{
	for(int a:ET[u])
	{
		if(VIS[a])continue;
		VIS[a]=true;
		if(MATCH[a]==-1||Expand(MATCH[a]))
		{
			MATCH[a]=u;
			MATCH[u]=a;
			return true;
		}
	}
	return false;
}
int Solve()
{
	for(int i=0;i<V+C;i++)MATCH[i]=-1;
	int ans=0;
	for(int l=0;l<V;l++)
	{
		if(MATCH[l]!=-1)continue;
		for(int r:ET[l])if(MATCH[r]==-1){MATCH[r]=l,MATCH[l]=r,ans++;break;}
	}
	for(int l=0;l<V;l++)
	{
		if(MATCH[l]!=-1)continue;
		for(int i=V;i<V+C;i++)VIS[i]=false;
		if(Expand(l))ans++;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&V,&C)==2)
	{
		for(int i=0;i<V;i++)
		{
			for(int j=0;j<26;j++)DICT[i][j]=0;
			static char tmp[31];
			scanf("%s",tmp);
			for(int j=0;tmp[j];j++)assert(j<30),DICT[i][tmp[j]-'a']++;
		}
		for(int i=0;i<C;i++)
		{
			for(int j=0;j<26;j++)CHAL[i][j]=0;
			static char tmp[31];
			scanf("%s",tmp);
			for(int j=0;tmp[j];j++)assert(j<30),CHAL[i][tmp[j]-'a']++;
		}
		for(int i=0;i<V+C;i++)ET[i].clear();
		for(int i=0;i<V;i++)
		{
			for(int j=0;j<C;j++)
			{
				bool ok=true;
				for(int k=0;k<26;k++)if(DICT[i][k]<CHAL[j][k]){ok=false;break;}
				if(!ok)continue;
				ET[i].push_back(V+j);
				ET[V+j].push_back(i);
//				printf("(%d,%d)\n",i,j);
			}
		}
		printf("%d\n",Solve());
	}
	return 0;
}

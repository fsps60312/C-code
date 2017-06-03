#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<queue>
#define max(x,y) (x)>(y)?(x):(y)
#include<set>
using namespace std;
int K,IN[120],DEP[120];
map<string,int> IDX;
map<int,string> NAME;
vector<int> PREQ[120];
//bool cmp(int a,int b){return NAME[a]<NAME[b];}
int main()
{
	int t;scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&K);
		IDX.clear(),NAME.clear();
		char tname[21];
		for(int i=0;i<K;i++)
		{
			PREQ[i].clear();
			IN[i]=DEP[i]=0;
			scanf("%s",tname);
			IDX[tname]=i;
			NAME[i]=tname;
		}
		int j;scanf("%d",&j);
		while(j--)
		{
			scanf("%s",tname);int i=IDX[tname];
			int k;scanf("%d",&k);
			while(k--)
			{
				scanf("%s",tname);int tp=IDX[tname];
				PREQ[i].push_back(tp);
				/*for(int ti=PREQ[i].size()-1;ti>0&&cmp(PREQ[i][ti],PREQ[i][ti-1]);i--)
				{
					int tint=PREQ[i][ti];
					PREQ[i][ti]=PREQ[i][ti-1],PREQ[i][ti-1]=tint;
				}*/
				IN[tp]++;
			}
		}
		queue<int> q;
		for(int i=0;i<K;i++)
			if(!IN[i])q.push(i);
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<PREQ[u].size();i++)
			{
				int tu=PREQ[u][i];
				IN[tu]--;
				if(!IN[tu])q.push(tu);
				DEP[tu]=max(DEP[tu],DEP[u]+1);
			}
		}
		for(map<string,int>::iterator i=IDX.begin();i!=IDX.end();i++)
		{
			if(!PREQ[i->second].size())continue;
			printf("%s ",i->first.c_str());
			set<string> ts;
			for(int ti=0;ti<PREQ[i->second].size();ti++)
			{
				int tj=PREQ[i->second][ti];
				if(DEP[tj]==DEP[i->second]+1)ts.insert(NAME[tj]);
			}
			printf("%d",ts.size());
			for(set<string>::iterator it=ts.begin();it!=ts.end();it++)printf(" %s",it->c_str());
			printf("\n");
			//system("pause");
		}
	}
	return 0;
}

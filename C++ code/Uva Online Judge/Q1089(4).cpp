#include<cstdio>
#include<string>
#include<map>
#include<vector>
#include<set>
#include<cassert>
using namespace std;
const int INF=1<<29;
int S,T,NR,L,DIST[202][202],PRE[202][202];
map<string,int>IDX[21];
set<string>RULE;
vector<string>RI[21];
int AddIdx(string str)
{
	for(int i=0;i<str.size();i++)
	{
		string s=str.substr(i);
		int len=s.size();
//		printf("len=%d,sz=%d\n",len,str.size());
		if(IDX[len].find(s)==IDX[len].end())
		{
			static int sz;sz=IDX[len].size();
//			printf("%s\n",s.c_str());
			RI[len].push_back(s);
			assert(sz<202);
			IDX[len][s]=sz;
		}
	}
	assert(IDX[str.size()].find(str)!=IDX[str.size()].end());
	return IDX[str.size()][str];
}
int AddIdx()
{
	static char tmp[21];
	scanf("%s",tmp);
	return AddIdx(tmp);
}
int Solve()
{
//	printf("L=%d\n",L);
	for(int l=1;l<=L;l++)
	{
//		printf("l=%d\n",l);
//		for(map<string,int>::iterator it=IDX[l].begin();it!=IDX[l].end();it++)printf("\t%s\n",it->first.c_str());
		int sz=IDX[l].size();
		for(int i=0;i<sz;i++)
		{
			for(int j=0;j<sz;j++)
			{
				if(i==j){DIST[i][j]=0;continue;}
				string si=RI[l][i],sj=RI[l][j];
				if(RULE.find(si+"."+sj)!=RULE.end())DIST[i][j]=1;
				else if(l>1&&si[0]==sj[0])
				{
					string ti=si.substr(1),tj=sj.substr(1);
					assert(IDX[l-1].find(ti)!=IDX[l-1].end()&&IDX[l-1].find(tj)!=IDX[l-1].end());
					DIST[i][j]=PRE[IDX[l-1][ti]][IDX[l-1][tj]];
				}
				else DIST[i][j]=INF;
			}
		}
		for(int m=0;m<sz;m++)for(int i=0;i<sz;i++)for(int j=0;j<sz;j++)
		if(DIST[i][j]>DIST[i][m]+DIST[m][j])DIST[i][j]=DIST[i][m]+DIST[m][j];
		for(int i=0;i<sz;i++)for(int j=0;j<sz;j++)PRE[i][j]=DIST[i][j];
	}
	return DIST[S][T];
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tstr[21];
	while(scanf("%s",tstr)==1&&!(tstr[0]=='.'&&!tstr[1]))
	{
		RULE.clear();
		for(int i=1;i<=20;i++)IDX[i].clear(),RI[i].clear();
		for(int i=0;;i++)if(!tstr[i]){L=i;break;}
		S=AddIdx(tstr),T=AddIdx();
		scanf("%d",&NR);
		for(int i=0;i<NR;i++)
		{
			static char a[21],b[21];
			scanf("%s%s",a,b);
			AddIdx(a),AddIdx(b);
			string s=a;s+=".";s+=b;
			RULE.insert(s);
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		int ans=Solve();
		if(ans==INF)puts("No solution");
		else printf("%d\n",ans);
	}
	return 0;
}

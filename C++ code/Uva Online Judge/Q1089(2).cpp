#include<cstdio>
#include<string>
#include<map>
#include<vector>
using namespace std;
const int INF=2147483647;
int S,T,NR,L,DIST[102][102];
map<string,int>IDX[21],AI;
vector<string>RI[21],RA,RB;
int AddIdx(char *str)
{
	int ans;
	for(int i=0;str[i];i++)
	{
		string s=str+i;
		int len=s.length;
		if(IDX[len].find(s)==IDX[len].end())
		{
			static int sz;sz=IDX[len].size();
			RI[len].push_back(s);
			return IDX[len][s]=sz;
		}
		if(!i)ans=IDX[len][s];
	}
	return ans;
}
int AddIdx()
{
	static char tmp[21];
	scanf("%s",tmp);
	return AddIdx(tmp);
}
int Solve()
{
	for(int l=1;l<=L;l++)
	{
		int sz=IDX[l].size();
		for(int i=0;i<sz;i++)
		{
			for(int j=0;j<sz;j++)
			{
				if(i==j){DIST[i][j]=0;return;}
				string &si=RI[l][i];
				if(AI.find(si)!=AI.end())
				{
					if(RB[AI[si]])
				}
			}
		}
	}
	return DIST[S][T];
}
int main()
{
//	freopen("in.txt","r",stdin);
	static char tstr[21];
	while(scanf("%s",tstr)==1&&!(tstr[0]=='.'&&!tstr[1]))
	{
		RA.clear(),RB.clear(),AI.clear();
		for(int i=1;i<=20;i++)IDX[i].clear(),RI[i].clear();
		for(int i=0;;i++)if(!tstr[i]){L=i;break;}
		S=AddIdx(tstr),T=AddIdx();
		scanf("%d",&NR);
		for(int i=0;i<NR;i++)
		{
			static char a[21],b[21];
			scanf("%s%s",a,b);
			AI[a]=i;
			RA.push_back(a),RB.push_back(b);
			AddIdx(a),AddIdx(b);
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		int ans=Solve();
		if(ans==-1)puts("No solution");
		else printf("%d\n",ans);
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
const int INF=2147483647;
int N,M;
vector<int>ET[400][26],EF[400][26];
int DIST[400][400];
pair<int,int>PRE[400][400];
int PCHAR[400][400],VIS[400][26][400],KASE=0;
vector<char>Solve(const int source,const int target)
{
	++KASE;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=INF;
	queue<pair<int,int> >q;q.push(make_pair(source,target));DIST[source][target]=0;
	vector<int>ansl,ansr;
	pair<int,int>end=make_pair(-1,-1);
	while(!q.empty())
	{
		const pair<int,int>p=q.front();q.pop();
		const int d=DIST[p.first][p.second];
		assert(p.first!=p.second);
		if(end.first!=-1&&d+1>DIST[end.first][end.second])goto answer_found;
		for(int c=0;c<26;c++)
		{
			for(int i=0;i<(int)ET[p.first][c].size();i++)
			{
				const int a=ET[p.first][c][i];
				if(VIS[p.second][c][a]==KASE)continue;
				VIS[p.second][c][a]=KASE;
				if(a==p.second)
				{
					ansl.push_back(c);
					end=p;
					goto answer_found;
				}
				for(int j=0;j<(int)EF[p.second][c].size();j++)
				{
					const int b=EF[p.second][c][j];
					if(d+1<DIST[a][b])
					{
						DIST[a][b]=d+1;
						PRE[a][b]=p;
						PCHAR[a][b]=c;
						if(a==b)end=make_pair(a,b);
						else q.push(make_pair(a,b));
					}
				}
			}
		}
	}
	if(end.first!=-1)goto answer_found;
	return vector<char>();
	answer_found:;
	while(DIST[end.first][end.second]>0)
	{
		const int c=PCHAR[end.first][end.second];
		ansl.push_back(c),ansr.push_back(c);
		end=PRE[end.first][end.second];
	}
	vector<char>ans;
	for(int i=(int)ansl.size()-1;i>=0;i--)ans.push_back((char)('a'+ansl[i]));
	for(int i=0;i<(int)ansr.size();i++)ans.push_back((char)('a'+ansr[i]));
	return ans;
}
int main()
{
	for(int i=0;i<400;i++)for(int j=0;j<26;j++)for(int k=0;k<400;k++)VIS[i][j][k]=0;
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int c=0;c<26;c++)ET[i][c].clear(),EF[i][c].clear();
		for(int i=0,a,b;i<M;i++)
		{
			static char c[2];
			scanf("%d%d%s",&a,&b,c),--a,--b;
			ET[a][c[0]-'a'].push_back(b),EF[b][c[0]-'a'].push_back(a);
		}
		static int d,s[100];
		scanf("%d",&d);
		for(int i=0;i<d;i++)scanf("%d",&s[i]),--s[i];
		for(int i=1;i<d;i++)
		{
			vector<char>ans=Solve(s[i-1],s[i]);
			if(ans.empty())puts("-1");
			else
			{
				printf("%d ",(int)ans.size());
				ans.push_back('\0');
				printf("%s\n",&ans[0]);
			}
		}
	}
	return 0;
}

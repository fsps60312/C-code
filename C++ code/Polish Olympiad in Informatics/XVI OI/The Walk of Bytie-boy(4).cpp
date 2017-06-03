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
int PCHAR[400][400];
bool VIS[400][26][400];
void PreProcess()
{
	for(int i=0;i<N;i++)for(int j=0;j<26;j++)for(int k=0;k<N;k++)VIS[i][j][k]=0;
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)DIST[i][j]=INF;
	queue<pair<int,int> >q;
	for(int i=0;i<N;i++)q.push(make_pair(i,i)),DIST[i][i]=0;
	for(int i=0;i<N;i++)for(int c=0;c<26;c++)for(int j=0;j<(int)ET[i][c].size();j++)
	{
		const int nxt=ET[i][c][j];
		q.push(make_pair(i,nxt));
		DIST[i][nxt]=1;
		PCHAR[i][nxt]=c;
	}
	while(!q.empty())
	{
		const pair<int,int>p=q.front();q.pop();
		const int d=DIST[p.first][p.second];
		for(int c=0;c<26;c++)
		{
			for(int i=0;i<(int)EF[p.first][c].size();i++)
			{
				const int a=EF[p.first][c][i];
				if(VIS[p.second][c][a])continue;
				VIS[p.second][c][a]=true;
				for(int j=0;j<(int)ET[p.second][c].size();j++)
				{
					const int b=ET[p.second][c][j];
					if(d+2<DIST[a][b])
					{
						DIST[a][b]=d+2;
						PRE[a][b]=p;
						PCHAR[a][b]=c;
						q.push(make_pair(a,b));
					}
				}
			}
		}
	}
}
vector<char>Solve(const int source,const int target)
{
	if(DIST[source][target]==INF)return vector<char>();
	pair<int,int>p=make_pair(source,target);
	vector<int>tans;
	while(true)
	{
		if(DIST[p.first][p.second]==0)
		{
			for(int i=(int)tans.size()-1,v;i>=0;i--)tans.push_back(v=tans[i]);
			break;
		}
		tans.push_back(PCHAR[p.first][p.second]);
		if(DIST[p.first][p.second]==1)
		{
			for(int i=(int)tans.size()-2,v;i>=0;i--)tans.push_back(v=tans[i]);
			break;
		}
		p=PRE[p.first][p.second];
	}
	vector<char>ans;
	for(int i=0;i<(int)tans.size();i++)ans.push_back((char)('a'+tans[i]));
	return ans;
}
int main()
{
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
		PreProcess();
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

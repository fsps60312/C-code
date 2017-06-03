#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
int G[1002][1002];
bool WANT[1002][1002];
struct DisjointSets
{
	pair<int,int>S[1002][1002];
	void Clear(const int N,const int M)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)S[i][j]=make_pair(i,j);
	}
	pair<int,int>Find(const pair<int,int>&a){return S[a.first][a.second]==a?a:(S[a.first][a.second]=Find(S[a.first][a.second]));}
	void Merge(pair<int,int>a,pair<int,int>b)
	{
		a=Find(a),b=Find(b);
		if(!WANT[b.first][b.second]||(WANT[a.first][a.second]&&G[a.first][a.second]<G[b.first][b.second]))swap(a,b);
		S[a.first][a.second]=b;
	}
}DJ;
int N,M;
vector<pair<int,int> >H[1001];
bool VIS[1002][1002];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<=1000;i++)H[i].clear();
		for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)
		{
			scanf("%d",&G[i][j]);
			WANT[i][j]=(G[i][j]>=1);
			if(G[i][j]<0)G[i][j]*=-1;
			H[G[i][j]].push_back(make_pair(i,j));
		}
		for(int i=0;i<=N+1;i++)for(int j=0;j<=M+1;j++)VIS[i][j]=false;
		DJ.Clear(N,M);
		int ans=0;
		for(int h=0;h<=1000;h++)
		{
			for(int i=0;i<(int)H[h].size();i++)
			{
				const pair<int,int>&p=H[h][i];
				static int d[4][2]={{-1,0},{0,-1},{0,1},{1,0}};
				int same_h=0,cnt=0;
				for(int j=0;j<4;j++)
				{
					const pair<int,int>&nxtp=make_pair(p.first+d[j][0],p.second+d[j][1]);
					if(VIS[nxtp.first][nxtp.second])
					{
						const pair<int,int>&f=DJ.Find(nxtp);
						if(WANT[f.first][f.second])
						{
							if(G[f.first][f.second]==h)++same_h;
							else ++cnt;
						}
						DJ.Merge(p,nxtp);
					}
				}
				VIS[p.first][p.second]=true;
				const pair<int,int>&fp=DJ.Find(p);
				if(WANT[p.first][p.second]&&(fp==p||!WANT[fp.first][fp.second]))++ans;
				if(cnt)ans-=same_h;
				else if(same_h>=2)ans-=same_h-1;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

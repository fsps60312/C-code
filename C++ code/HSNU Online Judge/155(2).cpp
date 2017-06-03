#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm> 
using namespace std;
struct Hungary
{
	int MATCH[250];
	vector<int>ET[250];
	int N,M,VA[250],VB[250];
	void clear(const int _n,const int _m)
	{
		N=_n,M=_m;
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0;i<M;i++)MATCH[i]=-1;
	}
	bool Match(const int u)
	{
		for(const int nxt:ET[u])if(!VB[nxt])
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				return true;
			}
		}
		return false;
	}
	int Solve()
	{
		int ans=0;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)VB[j]=false;
			if(Match(i))ans++;
		}
		return N+M-ans;
	}
}HUNGARY;
struct Line
{
	int a,b1,b2;
	Line(){}
	Line(const int _a,const int _b1,const int _b2):a(_a),b1(min(_b1,_b2)),b2(max(_b1,_b2)){}
	bool operator<(const Line &l)const{return a!=l.a?a<l.a:b1<l.b1;}
};
vector<Line>LINE[2];
bool AtRange(const int o,const int l,const int r){return l<=o&&o<=r;}
bool Intersect(const Line &now,const Line &nxt){return AtRange(now.a,nxt.b1,nxt.b2)&&AtRange(nxt.a,now.b1,now.b2);}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d",&N)==1);
	for(int d=0;d<2;d++)LINE[d].clear();
	for(int i=0,x1,y1,x2,y2;i<N;i++)
	{
		assert(scanf("%d%d%d%d",&x1,&y1,&x2,&y2)==4);
		assert((x1==x2)!=(y1==y2));
		if(x1==x2)LINE[0].push_back(Line(x1,y1,y2));
		else LINE[1].push_back(Line(y1,x1,x2));
	}
	const int n=LINE[0].size(),m=LINE[1].size();
	HUNGARY.clear(n,m);
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(Intersect(LINE[0][i],LINE[1][j]))HUNGARY.ET[i].push_back(j);
	printf("%d\n",HUNGARY.Solve());
	return 0;
}

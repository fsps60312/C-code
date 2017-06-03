#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<cmath>
#include<cassert>
#include<queue>
using namespace std;
const double EPS=1e-9;
void getmax(double &a,double b){if(b>a)a=b;}
void massert(bool valid){if(valid)return;while(1)printf("E");}
struct Point
{
	double x,y;
	Point(){}
	Point(double x,double y):x(x),y(y){} 
};
double Hypot(double a,double b){return sqrt(a*a+b*b);}
double Dis(Point a,Point b){return Hypot(a.x-b.x,a.y-b.y);}
vector<string>NAME;
map<string,int>IDX;
struct Edge
{
	int to;
	double dt;
	Edge(){}
	Edge(int to,int dt):to(to),dt(dt){}
	bool operator<(const Edge &e)const{return dt<e.dt;}
};
double F[100][100];
vector<int>AD[100];
int GetIdx(string s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		NAME.push_back(s);
		AD[sz].clear();
		for(int i=0;i<=sz;i++)F[i][sz]=F[sz][i]=-1e100;
		return IDX[s]=sz;
	}
	return IDX[s];
}
bool Floyd()
{
	for(int m=0;m<IDX.size();m++)
	{
		for(int i=0;i<IDX.size();i++)
		{
			for(int j=0;j<IDX.size();j++)
			{
				if(F[i][m]+F[m][j]>F[i][j])F[i][j]=F[i][m]+F[m][j];
			}
		}
	}
	for(int m=0;m<IDX.size();m++)
	{
		for(int i=0;i<IDX.size();i++)
		{
			for(int j=0;j<IDX.size();j++)
			{
				if(F[i][m]+F[m][j]>F[i][j])return false;
			}
		}
	}
	return true;
}
int PRI[100],ANS[100];
void Bfs(int root)
{
	queue<int>q;
	q.push(root);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=0;i<AD[u].size();i++)
		{
			int &j=AD[u][i];
			if(PRI[j]<=PRI[u])PRI[j]=PRI[u]+1;
			q.push(j);
		}
	}
}
bool VIS[100];
void Dfs(int u)
{
	if(VIS[u])assert(0);
	VIS[u]=true;
	for(int i=0;i<AD[u].size();i++)Dfs(AD[u][i]);
	VIS[u]=false;
}
int Solve()
{
	if(!IDX.size())return -2;//unknown
	if(!Floyd())return -1;//find positive loops
	static int deg_in[100];
	for(int i=0;i<IDX.size();i++)deg_in[i]=0,PRI[i]=0,ANS[i]=-1,VIS[i]=false;
	for(int i=0;i<IDX.size();i++)
	{
		for(int j=0;j<IDX.size();j++)
		{
			if(F[i][j]<=EPS)continue;
			AD[i].push_back(j);
			deg_in[j]++;
		}
	}
	int cnt=0;
	for(int i=0;i<IDX.size();i++)
	{
		if(deg_in[i]==0)
		{
			cnt++;
			Dfs(i);
			Bfs(i);
		}
	}
	massert(cnt>0);
	for(int i=0;i<IDX.size();i++)
	{
		if(ANS[PRI[i]]!=-1)return -2;//multiple solutions
		ANS[PRI[i]]=i;
	}
	return 0;
}
int T,N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			map<string,int>idx;
			vector<string>name;
			vector<Point>loc;
			scanf("%d%d",&N,&M);
			for(int i=0;i<N;i++)
			{
				static char s[21];
				static double x,y;
				scanf("%s%lf%lf",s,&x,&y);
				idx[s]=i;
				name.push_back(s);
				loc.push_back(Point(x,y));
			}
			NAME.clear(),IDX.clear();
			for(int i=0;i<M;i++)
			{
				static char n1[21],n2[21],n3[21],tmp[7];
				massert(scanf("%s%s%s%s%s%s",n1,tmp,n2,tmp,tmp,n3)==6);
				massert(tmp==string("before"));
				massert(idx.find(n1)!=idx.end()&&idx.find(n2)!=idx.end()&&idx.find(n3)!=idx.end());
				static int o,a,b,i1,i2;
				o=idx[n1],a=idx[n2],b=idx[n3];
				static double d1,d2;
				d1=Dis(loc[o],loc[a]),d2=Dis(loc[o],loc[b]);//n2 advance n3 at least Dis(o,a)-Dis(o,b)
				i1=GetIdx(n2),i2=GetIdx(n3);
				getmax(F[i1][i2],d1-d2);
			}
			int result=Solve();
			if(result==-1)puts("IMPOSSIBLE");
			else if(result==-2)puts("UNKNOWN");
			else if(result==0)
			{
				printf("%s",NAME[ANS[0]].c_str());
				for(int i=1;i<IDX.size();i++)printf(" %s",NAME[ANS[i]].c_str());
				puts("");
			}
			else massert(0);
		}
	} 
	return 0;
}

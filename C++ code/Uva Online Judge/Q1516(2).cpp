#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<cmath>
//#include<cassert>
#include<queue>
using namespace std;
const double EPS=1e-9;
void getmax(double &a,double b){if(b>a)a=b;}
void assert(bool valid){if(valid)return;while(1)printf("E");}
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
				if(F[i][m]+F[m][j]-F[i][j]>EPS)F[i][j]=F[i][m]+F[m][j];
			}
		}
	}
	for(int m=0;m<IDX.size();m++)
	{
		for(int i=0;i<IDX.size();i++)
		{
			for(int j=0;j<IDX.size();j++)
			{
				if(F[i][m]+F[m][j]-F[i][j]>EPS)return false;
			}
		}
	}
	return true;
}
bool VIS[100];
int PRI[100],ANS[100];
void Bfs(int root)
{
	queue<int>q;
	q.push(root);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		assert(!VIS[u]);
		VIS[u]=true;
		for(int i=0;i<AD[u].size();i++)
		{
			int &j=AD[u][i];
			if(PRI[j]<=PRI[u])PRI[j]=PRI[u]+1;
			q.push(j);
		}
	}
}
int Solve()
{
	if(!IDX.size())return -2;//unknown
//	puts("before floyd");
//	for(int i=0;i<IDX.size();i++)
//	{
//		for(int j=0;j<IDX.size();j++)printf(" %.2e",F[i][j]);
//		puts("");
//	}
	if(!Floyd())return -1;//find positive loops
//	puts("after floyd");
//	for(int i=0;i<IDX.size();i++)
//	{
//		for(int j=0;j<IDX.size();j++)printf(" %.2e",F[i][j]);
//		puts("");
//	}
	static int deg_in[100];
	for(int i=0;i<IDX.size();i++)deg_in[i]=0,VIS[i]=false,PRI[i]=0,ANS[i]=-1;
	for(int i=0;i<IDX.size();i++)
	{
		for(int j=0;j<IDX.size();j++)
		{
			if(F[i][j]<=0.0)continue;
			AD[i].push_back(j);
			deg_in[j]++;
//			printf("build edge(%d,%d)\n",i,j);
		}
	}
	int cnt=0;
	for(int i=0;i<IDX.size();i++)
	{
		if(deg_in[i]==0)
		{
//			printf("root=%d\n",i);
			cnt++;
			Bfs(i);
		}
	}
//	printf("cnt=%d\n",cnt);
	assert(cnt>0);
	for(int i=0;i<IDX.size();i++)
	{
//		printf("PRI[%d]=%d\n",i,PRI[i]);
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
				assert(scanf("%s%s%s%s%s%s",n1,tmp,n2,tmp,tmp,n3)==6);
				assert(tmp==string("before"));
				assert(idx.find(n1)!=idx.end()&&idx.find(n2)!=idx.end()&&idx.find(n3)!=idx.end());
				static int o,a,b,i1,i2;
				o=idx[n1],a=idx[n2],b=idx[n3];
				static double d1,d2;
				d1=Dis(loc[o],loc[a]),d2=Dis(loc[o],loc[b]);
				//n2 advance n3 at least Dis(o,a)-Dis(o,b)
				i1=GetIdx(n2),i2=GetIdx(n3);
				getmax(F[i1][i2],d1-d2);
//				printf("F[%d][%d]=%.3lf(%.3lf,%.3lf)\n",i1,i2,F[i1][i2]);
			}
			int result=Solve();
//			printf("result=%d\n",result);
			if(result==-1)puts("IMPOSSIBLE");
			else if(result==-2)puts("UNKNOWN");
			else if(result==0)
			{
				printf("%s",NAME[ANS[0]].c_str());
				for(int i=1;i<IDX.size();i++)printf(" %s",NAME[ANS[i]].c_str());
				puts("");
			}
			else assert(0);
		}
	} 
	return 0;
}

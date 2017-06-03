#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<cmath>
#include<cassert>
using namespace std;
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
vector<int>AD[100];
int DEGIN[100];
bool VIS[100];
int ORDER[100];
int GetIdx(string s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		NAME.push_back(s);
		AD[sz].clear();
		DEGIN[sz]=0;
		VIS[sz]=false;
		ORDER[sz]=0;
		return IDX[s]=sz;
	}
	return IDX[s];
}
#include<queue>
bool Bfs(int root)
{
	queue<int>q;
	q.push(root);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(VIS[u])return false;//find loop
		VIS[u]=true;
		for(int i=0;i<AD[u].size();i++)
		{
			int &j=AD[u][i];
			if(ORDER[j]<=ORDER[u])ORDER[j]=ORDER[u]+1; 
			q.push(j);
		}
	}
	return true;
}
int ANS[100];
int Solve()
{
	if(!IDX.size())return -2;//unknown
	int cnt=0;
	for(int i=0;i<IDX.size();i++)
	{
		if(!DEGIN[i])
		{
			if(!Bfs(i))return -1;//have loops
			cnt++;
		}
	}
	for(int i=0;i<IDX.size();i++)
	{
		ANS[i]=-1;
		if(!VIS[i])return -1;//have loops
	}
	for(int i=0;i<IDX.size();i++)
	{
//		printf("%d: %d\n",ORDER[i],i);
		if(ANS[ORDER[i]]!=-1)return -2;//multiple solutions
		ANS[ORDER[i]]=i;
	}
	return 0;
}
int T,N,M;
int main()
{
	freopen("in.txt","r",stdin);
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
				if(d1<d2)continue;
				//n2 advance n3 at least Dis(o,a)-Dis(o,b)
				i1=GetIdx(n2),i2=GetIdx(n3);
				DEGIN[i2]++;
				AD[i1].push_back(i2);
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

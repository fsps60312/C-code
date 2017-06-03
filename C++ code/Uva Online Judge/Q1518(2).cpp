#include<cstdio>
#include<map>
#include<string>
#include<vector>
using namespace std;
const double INF=1e100;
void getmin(double &a,double b){if(b<a)a=b;}
struct Train
{
	int from,depart,time,odd,delay;
	Train(){}
	Train(int from,int depart,int time,int odd,int delay):from(from),depart(depart),time(time),odd(odd),delay(delay){}
};
vector<Train>TRAIN[2000];
map<string,int>IDX;
int VIS[2000];
int GetIdx(string s)
{
	if(IDX.find(s)==IDX.end())
	{
		static int sz;sz=IDX.size();
		TRAIN[sz].clear();
		VIS[sz]=false; 
		return IDX[s]=sz;
	}
	return IDX[s];
}
int GetIdx()
{
	static char s[21];
	scanf("%s",s);
	return GetIdx(s);
}
int ORI,DES;
bool Reachable(int u)
{
	if(VIS[u])return false;
	VIS[u]=true;
	if(u==DES)return true;
	for(int i=0;i<TRAIN[u].size();i++)
	{
		Train &t=TRAIN[u][i];
		int &j=t.to;
		if(Reachable(j))return true;
	}
	return false;
}
double DP[2000][60],ODD[2000][60];
struct Pq
{
	int u,m;
	double cost;
}
double Solve()
{
	if(!Reachable(ORI))return INF;
	for(int i=0;i<IDX.size();i++)for(int j=0;j<60;j++)DP[i][j]=INF,ODD[i][j]=0.0;
	#include<queue>
	queue<int>q;
	for(int i=0;i<60;i++)DP[DES][i]=0.0,ODD[DES][i]=1.0;
	q.push(DES);
	while(!q.empty())
	{
		
	}
	double ans=INF;
	for(int i=0;i<60;i++)getmin(ans,DP[ORI][i]);
	return ans;
}
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			IDX.clear();
			ORI=GetIdx(),DES=GetIdx();
			scanf("%d",&N);
			for(int i=0;i<N;i++)
			{
				static int ori,des,m,t,p,d;
				ori=GetIdx(),des=GetIdx();
				scanf("%d%d%d%d",&m,&t,&p,&d);
				TRAIN[des].push_back(Train(ori,m,t,p,d));
			}
			double ans=Solve();
			if(ans==INF)puts("IMPOSSIBLE");
			else printf("%.10f\n",ans);
		}
	}
	return 0;
}

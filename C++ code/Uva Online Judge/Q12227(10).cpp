#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;while(1)printf("E");}
const int INF=2147483647;
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y,z;
	Point(){}
	Point(int x,int y,int z):x(x),y(y),z(z){}
	void Scanf(){scanf("%d%d%d",&x,&y,&z);}
}BEGIN,END;
int T,N;
struct Warmhole
{
	Point entry,exit;
	int creation,shift;
	void Scanf()
	{
		entry.Scanf(),exit.Scanf();
		scanf("%d%d",&creation,&shift);
	}
};
vector<Warmhole>WARMHOLE;
int Hypot(int a,int b,int c){return (int)(ceil(sqrt(a*a+b*b+c*c))+0.5);}
int Dis(Point &a,Point &b){return Hypot(a.x-b.x,a.y-b.y,a.z-b.z);}
struct Edge
{
	int to,creation,shift,cost;
	Edge(int to=0,int creation=0,int shift=0,int cost=0):to(to),creation(creation),shift(shift),cost(cost){}
};
vector<Edge>AD[50];
int TIME[50],UPRE[50],CPRE[50],CNT[50],LPRE[50];
bool INQ[50];
int Solve()
{
	static int vis_cnt,vis[50];
	vis_cnt=0;
	queue<int>q;
	for(int i=0;i<N;i++)
	{
		q.push(i);
		Warmhole &w=WARMHOLE[i];
		TIME[i]=min(Dis(BEGIN,w.exit),max(w.creation,Dis(BEGIN,w.entry))+w.shift);
		UPRE[i]=-1;
		INQ[i]=true;
		CNT[i]=0;
		vis[i]=0;
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();
		INQ[u]=false,CNT[u]++;
		if(CNT[u]>N)
		{
			vis_cnt++;
			vis[u]=vis_cnt;
			for(int i=UPRE[u];;i=UPRE[i])
			{
				assert(i!=-1);
				if(vis[i]==vis_cnt){u=i;break;}
				vis[i]=vis_cnt;
			}
			vector<int>loop;
			loop.push_back(u);
			for(int i=UPRE[u];i!=u;i=UPRE[i])loop.push_back(i);
			for(int i=0;i<loop.size();i++)CNT[loop[i]]=0;
			int mn=INF,idx=-1;
			for(int i=0;i<loop.size();i++)
			{
				int &j=UPRE[loop[i]];
				if(CPRE[j]==-INF)continue;
				else if(TIME[j]-(LPRE[j]+CPRE[j])<mn)mn=TIME[j]-(LPRE[j]+CPRE[j]),idx=j;
			}
			if(mn>0)
			{
				assert(idx!=-1);
				TIME[idx]-=mn;
//				printf("LPRE=%d,CPRE=%d,TIME[%d]=%d\n",LPRE[idx],CPRE[idx],idx,TIME[idx]);
				u=idx;
			}
		}
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=AD[u][i];
			int time=max(TIME[u]+e.cost,e.creation)+e.shift;
			if(time>=TIME[e.to])continue;
			TIME[e.to]=time;
			UPRE[e.to]=u;
			CPRE[e.to]=e.creation;
			LPRE[e.to]=e.shift;
			if(!INQ[e.to])INQ[e.to]=true,q.push(e.to);
		}
	}
	int ans=Dis(BEGIN,END);
	for(int i=0;i<N;i++)
	{
		Warmhole &w=WARMHOLE[i];
		if(TIME[i]+Dis(w.exit,END)<ans)ans=TIME[i]+Dis(w.exit,END);
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			BEGIN.Scanf(),END.Scanf();
			scanf("%d",&N);
			assert(N>=0&&N<=50);
			WARMHOLE.clear();
			for(int i=0;i<N;i++)
			{
				static Warmhole w;
				w.Scanf();
				WARMHOLE.push_back(w);
			}
			for(int i=0;i<N;i++)AD[i].clear();
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)
				{
					Warmhole &w1=WARMHOLE[i],&w2=WARMHOLE[j];
					AD[i].push_back(Edge(j,-INF,0,Dis(w1.exit,w2.exit)));
					AD[i].push_back(Edge(j,w2.creation,w2.shift,Dis(w1.exit,w2.entry)));
				}
			}
			printf("%d\n",Solve());
		}
	}
	return 0;
}

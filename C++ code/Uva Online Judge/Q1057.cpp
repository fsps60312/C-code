#include<cstdio>
#include<vector>
#include<set>
#include<queue>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,M,VIS[100],PRE[100];
vector<int>AD[100],RA[100];
set<int> S[100][100];
bool INQ[100][100];
struct Pq
{
	int a,b;
	Pq(){}
	Pq(int a,int b):a(a),b(b){}
};
void Push(queue<Pq>&q,Pq p)
{
	if(INQ[p.a][p.b])return;
	INQ[p.a][p.b]=true;
	q.push(p);
}
Pq &Pop(queue<Pq>&q)
{
	static Pq p;p=q.front();q.pop();
	INQ[p.a][p.b]=false;
	return p;
}
struct Pre
{
	int u,cost,pre;
	Pre(){}
	Pre(int u,int cost,int pre):u(u),cost(cost),pre(pre){}
	bool operator<(const Pre &p)const{return cost>p.cost;}
};
bool Update(Pq &f,Pq &t)
{
	static int kase=0;
	kase++;
	set<int>&s=S[f.a][f.b];
	int goal=S[t.a][t.b].size();
	assert((f.a==t.a)^(f.b==t.b));
	int ori,des;
	if(f.a==t.a)ori=t.b,des=f.b;
	else ori=f.a,des=t.a;
	priority_queue<Pre>q;
	q.push(Pre(ori,s.find(ori)==s.end()?s.size()+1:s.size(),-1));
	int ans=-1;
	while(!q.empty())
	{
		Pre u=q.top();q.pop();
		if(VIS[u.u]==kase)continue;
		VIS[u.u]=kase;
		PRE[u.u]=u.pre;
		if(u.u==des)
		{
			if(!goal||u.cost<goal)ans=u.cost;
			break;
		}
		for(int i=0;i<AD[u.u].size();i++)
		{
			int &j=AD[u.u][i];
			q.push(Pre(j,s.find(j)==s.end()?u.cost+1:u.cost,u.u));
		}
	}
	if(ans==-1)return false;
	S[t.a][t.b]=S[f.a][f.b];
	for(;des!=-1;des=PRE[des])
	{
		if(s.find(des)!=s.end())continue;
		ans--;
		S[t.a][t.b].insert(des);
	}
	assert(ans==s.size());
	return true;
}
void Solve()
{
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		S[i][j].clear();
		INQ[i][j]=false;
	}
	S[0][0].insert(0);
	queue<Pq>q;
	Push(q,Pq(0,0));
	while(!q.empty())
	{
		Pq p=Pop(q);
		Pq t=p;
		for(int i=0;i<AD[p.a].size();i++)
		{
			t.a=AD[p.a][i];
			if(Update(p,t))Push(q,t);
		}
		t=p;
		for(int i=0;i<AD[p.b].size();i++)
		{
			t.b=AD[p.b][i];
			if(Update(p,t))Push(q,t);
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<100;i++)VIS[i]=0;
	while(scanf("%d%d",&N,&M)==2&&(N||M))
	{
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			RA[i].clear();
		}
		for(int i=0;i<M;i++)
		{
			static int a,b;scanf("%d%d",&a,&b);
			a--,b--;
			AD[a].push_back(b);
			RA[b].push_back(a); 
		}
		Solve();
		static int kase=1;
		printf("Network %d\n",kase++);
		if(S[1][1].size())printf("Minimum number of nodes = %d\n",S[1][1].size());
		else puts("IMPOSSIBLE");
	}
	return 0;
}

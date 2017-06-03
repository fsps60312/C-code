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
		set<int>&s=S[p.a][p.b];
//		printf("(%d,%d)\n",p.a,p.b);
		for(int i=0;i<RA[p.b].size();i++)
		{
			int &j=RA[p.b][i],cost=s.find(j)==s.end()?s.size()+1:s.size();
			set<int>&ts=S[p.a][j];
			if(ts.size()&&cost>=ts.size())continue;
			ts=s;
			ts.insert(j);
			Push(q,Pq(p.a,j));
		}
		for(int i=0;i<AD[p.a].size();i++)
		{
			int &j=AD[p.a][i],cost=s.find(j)==s.end()?s.size()+1:s.size();
			set<int>&ts=S[j][p.b];
			if(ts.size()&&cost>=ts.size())continue;
			ts=s;
			ts.insert(j);
			Push(q,Pq(j,p.b));
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
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
		if(S[1][1].size())printf("Minimum number of nodes = %d\n\n",S[1][1].size());
		else puts("IMPOSSIBLE\n");
	}
	return 0;
}

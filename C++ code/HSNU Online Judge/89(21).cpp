#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<queue> 
using namespace std;
const int INF=2147483647;
int N,X,Y,K;
int VIS[10][901][910];
struct Edge
{
	int d,u,c;
	Edge(){}
	Edge(const int _d,const int _u,const int _c):d(_d),u(_u),c(_c){}
//	bool operator<(const Edge &e)const{if((u+d*K)%10!=(e.u+e.d*K)%10)return (u+d*K)%10<(e.u+e.d*K)%10;return d<e.d;}
	bool operator<(const Edge &e)const{if(d!=e.d)return d<e.d;return u<e.u;}
};
vector<Edge>ET[10];
struct Pq
{
	vector<int>ans,ks;
	int u,dsum,ksum;
	Pq(){}
	Pq(const vector<int>_a,const int _u,const int _d,const int _k,vector<int>_ks):ans(_a),u(_u),dsum(_d),ksum(_k),ks(_ks){}
	bool operator<(const Pq &p)const
	{
		for(int i=0;i<ans.size()&&i<p.ans.size();i++)if(ans[i]!=p.ans[i])return p.ans[i]<ans[i];
		return p.ans.size()<ans.size();
	}
};
bool Solve()
{
	priority_queue<Pq>pq;
	for(int i=0;i<=9;i++)
	{
		vector<int>ans;
		vector<int>ks;
		ks.push_back(i);
		for(int j=0;j<ET[i].size();j++)
		{
			const Edge &e=ET[i][j];
			if(e.d==0)continue;
			ans.push_back(e.d);
			ks.push_back((e.u+e.d*K)%10);
			pq.push(Pq(ans,e.u,e.d,i+(e.u+e.d*K)%10,ks));
			ks.pop_back();
			ans.pop_back();
		}
	}
	while(!pq.empty())
	{
		Pq p=pq.top();pq.pop();
		int n=N-p.ans.size();
		if(n<=VIS[p.u][p.dsum][p.ksum])continue;
		VIS[p.u][p.dsum][p.ksum]=n;
//	printf("u=%d,dsum=%d,ksum=%d,ANS=",p.u,p.dsum,p.ksum);for(int i=0;i<p.ans.size();i++)printf("%d",p.ans[i]);printf(" KS=");for(int i=0;i<p.ks.size();i++)printf("%d",p.ks[i]);puts("");
		if(p.dsum+n*9<X||p.dsum>X)continue;
		if(p.dsum==X&&p.ksum==Y&&p.u==0)
		{
			vector<int>seq=p.ans;
			while(seq.size()<N)seq.push_back(0);
			for(int i=0;i<N;i++)printf("%d",seq[i]);puts(""); 
			return true;
		}
		if(p.ans.size()==N)continue;
		for(int i=0;i<ET[p.u].size();i++)
		{
			const Edge &e=ET[p.u][i];
			p.ans.push_back(e.d);
			p.ks.push_back((e.u+e.d*K)%10);
			pq.push(Pq(p.ans,e.u,p.dsum+e.d,p.ksum+(e.u+e.d*K)%10,p.ks));
			p.ks.pop_back();
			p.ans.pop_back();
		}
	}
	return false;
}
int main()
{
	N=2,X=9,Y=9,K=5;
//	freopen("out.txt","w",stdout);
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)for(int j=N*9;j>=0;j--)for(int k=(N+1)*9;k>=0;k--)VIS[i][j][k]=-1;
	for(int i=0;i<10;i++)ET[i].clear();
	for(int i=0;i<10;i++)//initial number
	{
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			ET[v/10].push_back(Edge(n,i,c));
		}
	}
	for(int i=0;i<10;i++)sort(ET[i].begin(),ET[i].end());
	if(!Solve())puts("-1");
	return 0;
}

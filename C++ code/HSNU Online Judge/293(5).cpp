#include<cstdio>
#include<vector>
#include<cassert>
#include<queue>
#include<algorithm>
using namespace std;
int N,M;
struct Edge
{
	int a,b,type;
	Edge(){}
	Edge(const int _a,const int _b,const int _t):a(_a),b(_b),type(_t){}
	bool operator<(const Edge &e)const
	{
		if(type!=e.type)return type<e.type;
		return a!=e.a?a<e.a:b<e.b;
	}
};
struct Link
{
	vector<int>s;
	int type;
	Link(){}
	Link(const vector<int>&_s,const int _type):s(_s),type(_type){}
	int size()const{return s.size();}
	bool operator<(const Link &l)const{return size()!=l.size()?size()>l.size():type<l.type;}
	int operator[](const int idx)const{return s[idx];}
};
queue<Edge>ANS;
vector<int>ET[100000];
bool VIS[100000];
vector<Link>LINK;
void Dfs(const int u,vector<int>&link)
{
	assert(!VIS[u]);
	VIS[u]=true;
	link.push_back(u);
	int cnt=0;
	for(const int nxt:ET[u])if(!VIS[nxt])Dfs(nxt,link),cnt++;
	assert(cnt<=1);
}
void AddEdge(const int a,const int b,const int type){ANS.push(Edge(a,b,type));}
bool Solve()
{
	if(N<=2)return M==0;
	for(int i=0;i<N;i++)VIS[i]=false;
	LINK.clear();
	for(int i=0;i<N;i++)if((int)ET[i].size()==1&&!VIS[i])
	{
		vector<int>s;Dfs(i,s);
		LINK.push_back(Link(s,0));
	}
	for(int i=0;i<N;i++)if(!VIS[i])
	{
		vector<int>s;Dfs(i,s);
		LINK.push_back(Link(s,1));
	}
	sort(LINK.begin(),LINK.end());
	while(!ANS.empty())ANS.pop();
	const int l0sz=LINK[0].size();
	if(l0sz==1)
	{
		assert((int)LINK.size()>=2);
		AddEdge(LINK[0][0],LINK[1][0],1);
		for(int i=0;i<2;i++)LINK.erase(LINK.begin());
	}
	else if(l0sz==2||l0sz==3)
	{
		const Link &s=LINK[0];
		if(l0sz==3&&s.type==0)AddEdge(s[0],s[1],0),AddEdge(s[1],s[2],0),AddEdge(s[0],s[2],1);
		else for(int i=0;i<l0sz;i++)AddEdge(s[i],s[(i+1)%l0sz],0);
		LINK.erase(LINK.begin());
	}
	else if(l0sz==4)
	{
		const Link &s=LINK[0];
		AddEdge(s[1],s[2],0);
		AddEdge(s[0],s[3],s.type^1);
		AddEdge(s[0],s[2],1),AddEdge(s[1],s[3],1);
		LINK.erase(LINK.begin());
	}
	else if(l0sz>=5)
	{
		const int n=LINK[0].size();
		vector<int>tmp;
		int cur=0;
		while(cur<n)tmp.push_back(cur),cur+=2;
		if(cur==n)
		{
			tmp.push_back(1),cur=n-1;
			while(cur>1)tmp.push_back(cur),cur-=2;
		}
		else
		{
			cur=1;
			while(cur<n)tmp.push_back(cur),cur+=2;
		}
		assert((int)tmp.size()==n);
		for(int i=0;i<n;i++)AddEdge(LINK[0][tmp[i]],LINK[0][tmp[(i+1)%n]],1);
		tmp.clear(),vector<int>().swap(tmp);
		LINK.erase(LINK.begin());
	}
	else assert(0);
	for(const auto &s:LINK)
	{
		for(int i=0;i<(int)s.size();i++)
		{
			ANS.push(Edge(ANS.front().a,s[i],1));
			ANS.push(Edge(s[i],ANS.front().b,1));
			ANS.pop();
		}
	}
	while(!ANS.empty()&&(ANS.front().type==0||(int)ANS.size()>M))ANS.pop();
	return (int)ANS.size()==M;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(Solve())while(!ANS.empty())printf("%d %d\n",ANS.front().a+1,ANS.front().b+1),ANS.pop();
		else puts("-1");
		break;
	}
	return 0;
}
/*
4 3
1 2
2 3
3 4
*/

#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<deque>
using namespace std;
const int INF=0x7fffffff;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
template<class T>inline bool getmin(T&a,const T&b){return b<a?(a=b,true):false;}
void Update(deque<pair<int,int> >&q,const pair<int,int> h)
{
	if(q.empty()||h.first>q.front().first)q.push_front(h);
	while(q.size()>3)q.pop_back();
}
int N;
vector<int>ET[200000];
deque<pair<int,int> >H[200000];
void Dfs1(const int u,const int pa)
{
	H[u].clear();
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		Dfs1(nxt,u);
		if(H[nxt].empty())Update(H[u],make_pair(1,nxt));
		else
		{
			for(const auto h:H[nxt])Update(H[u],make_pair(h.first+1,nxt));
		}
	}
}
int ANS;
void Dfs2(const int u,const int pa,const deque<pair<int,int> >hp)
{
	assert(hp.size()<2);//or it's no need to continue to dfs
	{
		deque<pair<int,int> >cpy;
		for(const auto p:H[u])Update(cpy,make_pair(p.first,-1));
		for(const auto h:hp)Update(cpy,make_pair(h.first,pa));
		if(cpy.size()<=1)
		{
			const int ta=(cpy.empty()?0:cpy[0].first);
			getmin(ANS,ta);
			printf("u=%d, len=%d\n",u+1,ta);
		}
	}
	int problem=-1;
	for(const int nxt:ET[u])if(nxt!=pa)
	{
		deque<pair<int,int> >nxtq;
		for(const auto h:hp)Update(nxtq,make_pair(h.first+1,-1));
		int killed=0;
		for(const auto p:H[u])
		{
			if(p.second==nxt)killed++;
			else Update(nxtq,make_pair(p.first+1,-1));
		}
		if(killed>=2)
		{
			assert(problem==-1);
			problem=nxt;
		}
		else
		{
			if(nxtq.size()<2)Dfs2(nxt,u,nxtq);
		}
	}
	if(problem!=-1)
	{
		deque<pair<int,int> >newq;
		for(const auto p:hp)Update(newq,make_pair(p.first+1,-1));
		for(const int nxt:ET[u])if(nxt!=pa&&nxt!=problem)
		{
			for(const auto p:H[nxt])Update(newq,make_pair(p.first+2,-1));
		}
		if(newq.size()<2)Dfs2(problem,u,newq);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(b);
			ET[b].push_back(a);
		}
		Dfs1(0,-1);
		ANS=INF;
		Dfs2(0,-1,deque<pair<int,int> >());
		printf("%d\n",ANS==INF?-1:ANS);
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<map>
#include<set>
#include<queue>
#include<algorithm>
using namespace std;
int N,M,PARENT[52];
char IDER[52];
map<char,int>ET[52];
set<char>SUBTREE[52];
set<int>TRACK[52];
bool STATE[52];
void Build()
{
	for(int i=0;i<=N;i++)ET[i].clear(),SUBTREE[i].clear(),TRACK[i].clear();
	static int deg[52];
	for(int i=0;i<=N;i++)deg[i]=0;
	for(int i=1;i<=N;i++)++deg[PARENT[i]];
	queue<int>q;
	for(int i=0;i<=N;i++)if(!deg[i])q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		if(u==0)break;
//		printf("u=%d,parent=%d\n",u,PARENT[u]);
		if(IDER[u]!='\0')SUBTREE[u].insert(IDER[u]);
		for(const char i:SUBTREE[u])ET[PARENT[u]][i]=u,SUBTREE[PARENT[u]].insert(i);
		TRACK[PARENT[u]].insert(u);
		if(!--deg[PARENT[u]])q.push(PARENT[u]);
	}
	assert((int)TRACK[0].size()==1);
	for(int i=1;i<=N;i++)assert((int)TRACK[i].size()==2||(int)TRACK[i].size()==0);
}
vector<pair<int,pair<int,bool> > >COMMAND;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			static char type[2],ider[2];
			ider[0]='\0';
			scanf("%s",type);
			scanf("%d",&PARENT[i]);
			if(type[0]=='s'){}
			else if(type[0]=='p')scanf("%s",ider);
			else assert(0);
			IDER[i]=ider[0];
		}
//		puts("a");
		Build();
//		puts("b");
		for(int i=0;i<=N;i++)STATE[i]=true;
		scanf("%d",&M);
		COMMAND.clear();
		for(int i=0,t;i<M;i++)
		{
			static char ider[2];
			scanf("%d%s",&t,ider);
			int cur=0;
//			puts("c");
			while(IDER[cur]!=ider[0])
			{
				const auto &it=ET[cur].find(ider[0]);
				assert(it!=ET[cur].end());
				assert(it->second==(*TRACK[cur].begin())||it->second==(*TRACK[cur].rbegin()));
				COMMAND.push_back(make_pair(t,make_pair(cur,it->second==(*TRACK[cur].begin()))));
				cur=it->second;
				t++;
			}
//			puts("d");
		}
		{
			auto &s=COMMAND;
			sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
		}
		vector<pair<int,int> >ans;
		for(const auto &p:COMMAND)if(STATE[p.second.first]!=p.second.second)
		{
			STATE[p.second.first]^=true;
			ans.push_back(make_pair(p.second.first,p.first));
		}
		printf("%d\n",(int)ans.size());
		for(const auto &p:ans)printf("%d %d\n",p.first,p.second);
	}
	return 0;
}

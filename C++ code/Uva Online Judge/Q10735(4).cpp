#include<cstdio>
//#include<cassert>
#include<vector>
#include<set>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Hungary
{
	int N,M;
	bool VA[500],VB[500];
	int MATCH[500],RM[500];
	vector<int>ET[500];
	bool Match(const int u)
	{
		if(VA[u])return false;
		VA[u]=true;
		for(const int nxt:ET[u])
		{
			VB[nxt]=true;
			if(MATCH[nxt]==-1||Match(MATCH[nxt]))
			{
				MATCH[nxt]=u;
				RM[u]=nxt;
				return true;
			}
		}
		return false;
	}
	bool Solve()
	{
		for(int i=0;i<M;i++)MATCH[i]=-1;
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)VA[j]=false;
			for(int j=0;j<M;j++)VB[j]=false;
			if(!Match(i))return false;
		}
		return true;
	}
}HUNGARY;
int V,E;
struct Edge
{
	int a,b,type;
	bool vis;
	Edge(){}
	Edge(const int _a,const int _b,const int _t):a(_a),b(_b),type(_t),vis(false){}
};
vector<Edge>EDGE;
vector<int>ET[100];
vector<int>ANS;
struct Pair
{
	int a,b;
	Pair(){}
	Pair(const int _a,const int _b):a(_a),b(_b){}
	bool operator<(const Pair &p)const{return a!=p.a?a<p.a:b<p.b;}
};
multiset<Pair>UNDIR,DIREC;
void Delete(const int a,const int b)
{
	auto it=DIREC.find(Pair(a,b));
	if(it!=DIREC.end()){DIREC.erase(it);return;}
	it=UNDIR.find(Pair(min(a,b),max(a,b)));
	assert(it!=UNDIR.end());
	UNDIR.erase(it);
}
void Dfs(const int u)
{
	for(const int ei:ET[u])
	{
		const Edge &e=EDGE[ei];
		if(e.vis)continue;
		EDGE[ei].vis=true;
		Dfs(e.b);
	}
	ANS.push_back(u);
}
bool Solve()
{
	vector<int>idx;
	do
	{
		HUNGARY.N=E;
		int &sz=HUNGARY.M=0;
		for(int i=0;i<E;i++)HUNGARY.ET[i].clear();
		for(int i=0;i<V;i++)
		{
			if(ET[i].size()&1)return false;
			const int cnt=ET[i].size()/2;
			for(int j=0;j<cnt;j++)
			{
				for(const auto ei:ET[i])
				{
					const Edge &e=EDGE[ei];
					if(e.type==0||e.b!=i)HUNGARY.ET[ei].push_back(sz);
				}
				idx.push_back(i);
				sz++;
			}
		}
		assert(HUNGARY.M==HUNGARY.N);
	}while(0);
	if(!HUNGARY.Solve())return false;
	for(int i=0;i<E;i++)
	{
		const Edge &e=EDGE[i];
		const int u=idx[HUNGARY.RM[i]];
		if(e.type==1)assert(e.a==u&&"type=1");
		else
		{
			if(e.b==u)swap(EDGE[i].a,EDGE[i].b);
			assert(e.a==u&&"type=0");
		}
	}
	static int din[100],dout[100];
	for(int i=0;i<V;i++)ET[i].clear(),din[i]=dout[i]=0;
	for(int i=0;i<E;i++)ET[EDGE[i].a].push_back(i),dout[EDGE[i].a]++,din[EDGE[i].b]++;
	for(int i=0;i<V;i++)assert(din[i]==dout[i]);
	ANS.clear();
	Dfs(0);
	for(int i=0,j=(int)ANS.size()-1;i<j;i++,j--)swap(ANS[i],ANS[j]);
	for(int i=1;i<(int)ANS.size();i++)dout[ANS[i-1]]--,din[ANS[i]]--,Delete(ANS[i-1],ANS[i]);
	assert(DIREC.empty()&&UNDIR.empty());
	for(int i=0;i<V;i++)assert(din[i]==0);
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	static int casecount;assert(scanf("%d",&casecount)==1);
	while(casecount--)
	{
		assert(scanf("%d%d",&V,&E)==2);
		for(int i=0;i<V;i++)ET[i].clear();
		EDGE.clear();
		DIREC.clear(),UNDIR.clear();
		for(int i=0,a,b,type;i<E;i++)
		{
			static char tmp[2];
			assert(scanf("%d%d%s",&a,&b,tmp)==3);
			a--,b--;
			assert(a>=0&&a<V&&b>=0&&b<V);
			if(tmp[0]=='U')type=0,UNDIR.insert(Pair(min(a,b),max(a,b)));
			else assert(tmp[0]=='D'),type=1,DIREC.insert(Pair(a,b));
			EDGE.push_back(Edge(a,b,type));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		static int kase=0;
		if(kase++)puts("");
		if(!Solve())puts("No euler circuit exist");
		else
		{
			assert((int)ANS.size()==E+1);
			for(int i=0;i<(int)ANS.size();i++)
			{
				if(i)putchar(' ');
				printf("%d",ANS[i]+1);
			}
			puts("");
		}
	}
	assert(scanf("%d",&casecount)!=1);
	return 0;
}
/* 
1

1 1
1 1 D
*/

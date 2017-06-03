#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
//void assert(bool valid){if(valid)return;for(;;)putchar('E');}
struct Djset
{
	int s[6];
	void clear(){for(int i=0;i<6;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
}DJ;
struct State
{
	vector<int>member;
	vector<int>candidate;
};
struct Pair
{
	int a,b;
	Pair(){}
	Pair(const int _a,const int _b):a(min(_a,_b)),b(max(_a,_b)){}
};
int N;
map<int,State>GSET;
vector<Pair>ANS;
vector<State>G;
vector<Pair>END,FOUR;
void Solve()
{
	ANS.clear();
	assert(!G.empty());
	if(G.size()==1)
	{
		vector<int>&s=G[0].candidate;
		if(s.size()>=4)for(int i=0;i+2<(int)s.size();i+=2)ANS.push_back(Pair(s[i],s[i+1]));
		return;
	}
	END.clear();
	FOUR.clear();
	for(int i=0;i<(int)G.size();i++)
	{
		vector<int>&s=G[i].candidate;
		const vector<int>&mem=G[i].member;
		if(s.empty())
		{
			END.push_back(Pair(mem[0],mem[0]));
			FOUR.push_back(Pair(mem[0],mem[0]));
		}
		else if(s.size()==2)END.push_back(Pair(s[0],s[1])),FOUR.push_back(Pair(mem[0],mem[0]));
		else
		{
			assert(s.size()==4);
			END.push_back(Pair(s[0],s[1]));
			FOUR.push_back(Pair(s[2],s[3]));
		}
	}
	int minus=-1,end1=-1,end2=-1;
	for(int i=0;i<(int)G.size();i++)for(int j=i+1;j<(int)G.size();j++)
	{
		if(END[i].b+END[j].b>minus)minus=END[i].b+END[j].b,end1=i,end2=j;
	}
	for(int i=0;i<(int)G.size();i++)
	{
		if(END[i].a+END[i].b-(FOUR[i].a+FOUR[i].b)>minus)minus=END[i].a+END[i].b-(FOUR[i].a+FOUR[i].b),end1=end2=i;
	}
	assert(minus>-1);
	if(end1==end2)
	{
		vector<Pair>node;
		node.push_back(FOUR[end1]);
		for(int i=0;i<(int)G.size();i++)if(i!=end1)node.push_back(END[i]);
		node.push_back(FOUR[end1]);
		for(int i=1;i<(int)node.size();i++)ANS.push_back(Pair(node[i-1].a,node[i].b));
	}
	else
	{
		vector<Pair>node;
		node.push_back(Pair(END[end1].a,END[end1].a));
		for(int i=0;i<(int)G.size();i++)if(i!=end1&&i!=end2)node.push_back(END[i]);
		node.push_back(Pair(END[end2].a,END[end2].a));
		for(int i=1;i<(int)node.size();i++)ANS.push_back(Pair(node[i-1].a,node[i].b));
	}
}
int DEG[6];
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<6;i++)DEG[i]=0;
		DJ.clear();
		vector<Pair>tmp;
		for(int i=0,a,b;i<N;i++)
		{
			assert(scanf("%d%d",&a,&b)==2);
			tmp.push_back(Pair(a,b));
			a--,b--;
			assert(a>=0&&a<6&&b>=0&&b<6);
			DEG[a]++,DEG[b]++;
			DJ.Merge(a,b);
		}
		GSET.clear();
		for(int i=0;i<6;i++)if(DEG[i])
		{
			State &g=GSET[DJ.Find(i)];
			g.member.push_back(i+1);
			if(DEG[i]&1)g.candidate.push_back(i+1);
		}
		G.clear();
		for(auto &it:GSET)
		{
			State &g=it.second;
			assert(g.candidate.size()%2==0);
			sort(g.member.begin(),g.member.end());
			sort(g.candidate.begin(),g.candidate.end());
			G.push_back(g);
		}
		Solve();
		int sum=0;
		for(const auto &p:ANS)sum+=p.a+p.b;
//		static int kase=1;
//		printf("Case %d:\n",kase++);
		printf("%d\n%d\n",sum,(int)ANS.size());
		for(const auto &p:ANS)printf("%d %d\n",p.a,p.b),tmp.push_back(p);
		for(int i=0;i<6;i++)DEG[i]=0;
		DJ.clear();
		for(const auto &p:tmp)DJ.Merge(p.a-1,p.b-1),DEG[p.a-1]++,DEG[p.b-1]++;
		int cnt=0,head=-1;
		for(int i=0;i<6;i++)if(DEG[i])
		{
			if(DEG[i]&1)cnt++;
			int v=DJ.Find(i);
			if(head==-1)head=v;
			assert(head==v);
		}
		assert(cnt==0||cnt==2);//this line got error
	}
	return 0;
}
/*
4
6 5
2 6
3 3
4 6
*/

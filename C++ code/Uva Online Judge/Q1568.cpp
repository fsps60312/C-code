#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
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
vector<Pair>END;
void Solve()
{
	ANS.clear();
	if(G.size()==0)return;
	for(int i=0;i<(int)G.size();i++)
	{
		vector<int>&s=G[i].candidate;
		if(s.size()>=4)
		{
			for(int i=0;;i++)
			{
				if(i+2==(int)s.size())
				{
					int a=s[i],b=s[i+1];
					s.clear();
					s.push_back(a),s.push_back(b);
					break;
				}
				ANS.push_back(Pair(s[i],s[i+1]));
			}
		}
	}
	if(G.size()==1)return;
	END.clear();
	int sum=0;
	for(int i=0;i<(int)G.size();i++)
	{
		vector<int>&s=G[i].candidate;
		if(s.empty())
		{
			vector<int>&mem=G[i].member;
			sum+=mem[0]*2;
			END.push_back(Pair(mem[0],mem[0]));
		}
		else
		{
			sum+=s[0]+s[1];
			END.push_back(Pair(s[0],s[1]));
		}
	}
	int minus=-1,end1=-1,end2=-1;
	for(int i=0;i<(int)G.size();i++)for(int j=i+1;j<(int)G.size();j++)
	{
		if(END[i].b+END[j].b>minus)minus=END[i].b+END[j].b,end1=i,end2=j;
	}
	for(int i=0;i<(int)G.size();i++)
	{
		const int mn=G[i].member[0];
		if(END[i].a+END[i].b-2*mn>minus)minus=END[i].a+END[i].b-2*mn,end1=end2=i;
	}
	assert(minus>-1);
	if(end1==end2)
	{
		vector<Pair>node;
		const Pair &p=Pair(G[end1].member[0],G[end1].member[0]);
		node.push_back(p);
		for(int i=0;i<(int)G.size();i++)if(i!=end1)node.push_back(END[i]);
		node.push_back(p);
		for(int i=1;i<(int)node.size();i++)ANS.push_back(Pair(node[i-1].b,node[i].a));
	}
	else
	{
		vector<Pair>node;
		node.push_back(Pair(-1,END[end1].a));
		for(int i=0;i<(int)G.size();i++)if(i!=end1&&i!=end2)node.push_back(END[i]);
		node.push_back(Pair(END[end2].a,-1));
		for(int i=1;i<(int)node.size();i++)ANS.push_back(Pair(node[i-1].b,node[i].a));
	}
}
int DEG[6];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<6;i++)DEG[i]=0;
		DJ.clear();
		for(int i=0,a,b;i<N;i++)
		{
			assert(scanf("%d%d",&a,&b)==2);
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
		printf("%d\n%d\n",sum,(int)ANS.size());
		for(const auto &p:ANS)printf("%d %d\n",p.a,p.b);
	}
	return 0;
}

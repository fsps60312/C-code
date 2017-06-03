#include<cstdio>
#include<vector>
#include<cassert>
#include<map>
using namespace std;
int N,R,Q;
int AREA[200000],BOSS[200000];
vector<int>ET[200000]; 
struct Bst
{
	map<int,map<int,int> >ROOT;
	map<int,int>IDX;
	int LIGHT,N;
	void Build(const vector<int>&seq)
	{
		assert(!seq.empty());
		ROOT.clear(),IDX.clear();
		LIGHT=seq[0],N=seq.size();
		for(int i=0;i<(int)seq.size();i++)IDX[seq[i]]=i;
	}
	void Add(const int node,const int area)
	{
		const auto it=IDX.find(node);
		assert(it!=IDX.end());
		ROOT[area][it->second]++;
	}
};
int SZ[200000];
int BuildSZ(const int u){int &sz=SZ[u]=1;for(const auto &nxt:ET[u])sz+=BuildSZ(nxt);return sz;}
vector<Bst>BST;
int main()
{
	freopen("in.txt","r",stdin);
	assert(scanf("%d%d%d",&N,&R,&Q)==3);
	BOSS[0]=-1;assert(scanf("%d",&AREA[0])==1),AREA[0]--;
	for(int i=1;i<N;i++)assert(scanf("%d%d",&BOSS[i],&AREA[i])==2),AREA[i]--,ET[--BOSS[i]].push_back(i);
	BuildSZ(0);
	BST.clear(),BuildBST(0);
	return 0;
}

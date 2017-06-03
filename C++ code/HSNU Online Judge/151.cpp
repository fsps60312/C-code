#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
struct SegTree
{
	vector<int>TAG;
	map<int,int>LOC;
	int N,LIGHT;
	void Build(const int id,const int l,const int r)
	{
		while((int)TAG.size()<=id)TAG.push_back(0);
		TAG[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	SegTree(){}
	SegTree(const vector<int>&link)
	{
		assert(!link.empty());
		N=link.size(),LIGHT=link[0];
		LOC.clear();
		for(int i=0;i<N;i++)LOC[link[i]]=i;
		Build(1,0,N-1);
	}
	void PutDown(const int id){TAG[id*2]+=TAG[id],TAG[id*2+1]+=TAG[id],TAG[id]=0;}
	void Add(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){TAG[id]+=val;return;}
		PutDown(id);
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br,val),Add(id*2+1,mid+1,r,bl,br,val);
	}
	int GetLoc(const int a){const auto it=LOC.find(a);assert(it!=LOC.end());return it->second;}
	void Add(const int _a,const int _b)
	{
		const int a=GetLoc(_a),b=GetLoc(_b);
		assert(a<=b);
		if(a<b)Add(1,0,N-1,a+1,b,1);
	}
	void Add(const int _a){const int a=GetLoc(_a);Add(1,0,N-1,0,a,1);}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r){assert(loc==r);return TAG[id];}
		PutDown(id);
		const int mid=(l+r)/2;
		if(loc<=mid)return Query(id*2,l,mid,loc);
		else return Query(id*2+1,mid+1,r,loc);
	}
	int Query(const int node){return Query(1,0,N-1,GetLoc(node));}
};
int N,Q;
vector<int>ET[100000];
vector<SegTree>LINK;
int FA[100000],TREE_ID[100000],DEP[100000];
void BuildLink(const int u,const int fa,const int *sz,vector<int>&rec,const int dep)
{
//	printf("u=%d\n",u);
	FA[u]=fa;
	DEP[u]=dep;
	rec.push_back(u);
	bool hasch=false;
	multimap<int,int,greater<int> >sot;
	for(const int nxt:ET[u])if(nxt!=fa)sot.insert(make_pair(sz[nxt],nxt));
	for(const auto it:sot)hasch=true,BuildLink(it.second,u,sz,rec,dep+1);
	if(!hasch)
	{
		for(const int node:rec)TREE_ID[node]=LINK.size();
		LINK.push_back(SegTree(rec));
		rec.clear();
	}
}
int GetSz(const int u,const int fa,int *sz){int &ans=sz[u]=1;for(const int nxt:ET[u])if(nxt!=fa)ans+=GetSz(nxt,u,sz);return ans;}
void PaintTree(int a,int b)
{
	assert(a!=-1&&b!=-1);
	if(DEP[a]>DEP[b])swap(a,b);
	const int ida=TREE_ID[a],idb=TREE_ID[b];
	if(ida==idb)LINK[ida].Add(a,b);
	else
	{
		if(DEP[LINK[ida].LIGHT]>DEP[LINK[idb].LIGHT])LINK[ida].Add(a),PaintTree(FA[LINK[ida].LIGHT],b);
		else LINK[idb].Add(b),PaintTree(a,FA[LINK[idb].LIGHT]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d%d",&N,&Q)==2);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<N-1;i++)assert(scanf("%d%d",&a,&b)==2),a--,b--,ET[a].push_back(b),ET[b].push_back(a);
	LINK.clear();
	if(1)
	{
		vector<int>tmp;
		static int sz[100000];
		GetSz(0,-1,sz);
		BuildLink(0,-1,sz,tmp,0);
		assert(tmp.empty());
	}
	while(Q--)
	{
		static char type[2];
		static int a,b;
		assert(scanf("%s%d%d",type,&a,&b)==3);
		a--,b--;
		if(type[0]=='P')PaintTree(a,b);
		else if(type[0]=='Q')
		{
			if(DEP[a]>DEP[b])swap(a,b);
			assert(FA[b]==a);
			printf("%d\n",LINK[TREE_ID[b]].Query(b));
		}
		else assert(0);
	}
	return 0;
}

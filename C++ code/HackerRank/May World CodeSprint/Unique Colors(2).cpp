#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
const int INF=2147483647;
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
template<class T>struct MyArray
{
	T S[100000],DEFAULT;
	bool CHANGED[100000];
	vector<int>CHANGES;
	MyArray<T>(const T &v){DEFAULT=v;for(int i=0;i<100000;i++)S[i]=v,CHANGED[i]=DEFAULT;CHANGES.clear();}
	T Get(const int i)const{assert(CHANGED[i]);return S[i];}
	void Set(const int i,const T &v)
	{
		S[i]=v;
		if(!CHANGED[i])CHANGED[i]=true,CHANGES.push_back(i);
	}
	void Add(const int i,const T &v)
	{
		S[i]+=v;
		if(!CHANGED[i])CHANGED[i]=true,CHANGES.push_back(i);
	}
	void Clear()
	{
		for(const int i:CHANGES)S[i]=DEFAULT,CHANGED[i]=false;
		CHANGES.clear();
//		for(int i=0;i<100000;i++)assert(!CHANGED[i]&&S[i]==DEFAULT);
	}
};
int N,C[100000],SZ[100000];
vector<int>ET[100000];
bool VIS[100000];
MyArray<int>SIZE=MyArray<int>(0);
int GetSize(const int u,const int parent)
{
	assert(!VIS[u]);
	int ans=1;
	for(const int nxt:ET[u])if(!VIS[nxt]&&nxt!=parent)ans+=GetSize(nxt,u);
	SIZE.Set(u,ans);
	return ans;
}
int GetWeightPoint(const int root)
{
	assert(!VIS[root]);
	SIZE.Clear();
	const int sz=GetSize(root,-1);
	int ans=-1,min_size=INF;
	for(const int u:SIZE.CHANGES)
	{
		int tsz=sz-SIZE.Get(u);
		for(const int nxt:ET[u])if(!VIS[nxt])
		{
			const int chsz=SIZE.Get(nxt);
			if(chsz<SIZE.Get(u))getmax(tsz,chsz);
		}
		if(tsz<min_size)min_size=tsz,ans=u;
	}
	SIZE.Clear();
	GetSize(ans,-1);
	return ans;
}
int VCOLOR[100000];
void StatisticColors(const int u,const int parent,MyArray<int>&cnt)
{
	assert(!VIS[u]);
	if(!VCOLOR[C[u]]++)cnt.Add(C[u],SIZE.Get(u));
	for(const int nxt:ET[u])if(!VIS[nxt]&&nxt!=parent)StatisticColors(nxt,u,cnt);
	--VCOLOR[C[u]];
}
LL ANS[100000];
void UpdateAnswers(const int u,const int parent,const MyArray<int>&cnt,LL &now,const int remain_size)
{
	assert(!VIS[u]);
	if(!VCOLOR[C[u]]++)now-=cnt.Get(C[u]),now+=remain_size;
	ANS[u]+=now;
	printf("Add %lld to %d\n",now,u+1);
	for(const int nxt:ET[u])if(!VIS[nxt]&&nxt!=parent)UpdateAnswers(nxt,u,cnt,now,remain_size);
	if(!--VCOLOR[C[u]])now-=remain_size,now+=cnt.Get(C[u]);
}
MyArray<int>TOTAL_CNT=MyArray<int>(0);
MyArray<int>CURRENT_CNT=MyArray<int>(0);
void Solve(const int one_vertex)
{
	const int root=GetWeightPoint(one_vertex);
	assert(!VIS[one_vertex]&&!VIS[root]);
	TOTAL_CNT.Clear();
	int sz=1;
	for(const int nxt:ET[root])if(!VIS[nxt])
	{
		StatisticColors(nxt,root,TOTAL_CNT);
		sz+=SIZE.Get(nxt);
	}
	LL colorcovered=0LL;
	printf("root=%d\n",root+1);
	for(const int i:TOTAL_CNT.CHANGES)colorcovered+=TOTAL_CNT.Get(i),printf("color=%d,covered=%d\n",i+1,TOTAL_CNT.Get(i));
	ANS[root]+=colorcovered;
	for(const int nxt:ET[root])if(!VIS[nxt])
	{
		CURRENT_CNT.Clear();
		StatisticColors(nxt,root,CURRENT_CNT);
		printf("nxt=%d\n",nxt+1);
		for(const int i:CURRENT_CNT.CHANGES)TOTAL_CNT.Add(i,-CURRENT_CNT.Get(i)),colorcovered-=CURRENT_CNT.Get(i),printf("color=%d,covered=%d\n",i+1,CURRENT_CNT.Get(i));
		UpdateAnswers(nxt,root,TOTAL_CNT,colorcovered,sz-SIZE.Get(nxt));
		for(const int i:CURRENT_CNT.CHANGES)TOTAL_CNT.Add(i,CURRENT_CNT.Get(i)),colorcovered+=CURRENT_CNT.Get(i);
	}
	VIS[root]=true;
	for(const int nxt:ET[root])if(!VIS[nxt])Solve(nxt);
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<100000;i++)VCOLOR[i]=0;
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&C[i]),--C[i],ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)scanf("%d%d",&a,&b),--a,--b,ET[a].push_back(b),ET[b].push_back(a);
		for(int i=0;i<N;i++)ANS[i]=0LL,VIS[i]=false;
		Solve(0);
		for(int i=0;i<N;i++)printf("%lld\n",ANS[i]);
		for(int i=0;i<100000;i++)assert(VCOLOR[i]==0);
	}
	return 0;
}

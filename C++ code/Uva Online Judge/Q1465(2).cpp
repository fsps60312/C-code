#include<cstdio>
#include<set>
#include<map>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
multiset<int>MN;
struct GapManager
{
	set<int>LOC;
	multiset<int>GAP;
	int N;
	void clear(const int _n)
	{
		N=_n;LOC.clear(),GAP.clear();
		LOC.insert(-INF/2),LOC.insert(INF/2);
		GAP.insert(INF/2+INF/2);
	}
	void insert(const int loc)
	{
		auto it=LOC.lower_bound(loc);
		const int r=(*it),l=(*--it);
		GAP.erase(GAP.find(r-l));
		LOC.insert(loc);
		GAP.insert(r-loc),GAP.insert(loc-l);
		assert(GAP.size()+1==LOC.size());
	}
	void erase(const int loc)
	{
		MN.erase(MN.find(GetValue()));
		auto it=LOC.find(loc);
		const int r=(*++it),l=(*----it);
		GAP.erase(GAP.find(r-loc)),GAP.erase(GAP.find(loc-l));
		LOC.erase(loc);
		GAP.insert(r-l);
		MN.insert(GetValue());
		assert(GAP.size()+1==LOC.size());
	}
	int GetValue()const
	{
		if((int)GAP.size()==1)return INF-2;
		int lmx,rmx;
		if(true)
		{
			auto it=LOC.begin();
			lmx=((*++it)+1)*2-1;
			it=LOC.end();it--;
			rmx=(N-(*--it))*2-1;
		}
		auto it=GAP.end();it--,it--;
		return max(max(lmx,rmx),it==GAP.begin()?0:(*--it));
	}
}HG[100],VG[10000];
int N,M,GRID[100][10000];
multimap<int,int>LEVEL;
int Solve()
{
	for(int level=1;!LEVEL.empty();level++)
	{
		while(!LEVEL.empty()&&(LEVEL.begin()->first)<level)
		{
			const int u=LEVEL.begin()->second;
			LEVEL.erase(LEVEL.begin());
			HG[u/M].erase(u%M);
			VG[u%M].erase(u/M);
		}
		assert((int)MN.size()==N+M);
//		puts("pass");
//		for(int i=0;i<N;i++)
//		{
//			printf("H[%d]:",i);
//			for(auto it:HG[i].LOC)printf(" %d",it);puts("");
//			printf("G[%d]:",i);
//			for(auto it:HG[i].GAP)printf(" %d",it);puts("");
//		}
//		for(int i=0;i<M;i++)
//		{
//			printf("V[%d]:",i);
//			for(auto it:VG[i].LOC)printf(" %d",it);puts("");
//			printf("G[%d]:",i);
//			for(auto it:VG[i].GAP)printf(" %d",it);puts("");
//		}
//		printf("MN:");for(auto it:MN)printf(" %d",it);puts("");
		auto it=MN.end();it--;
//		printf("mx=%d\n",*it);
		if(((*it)+2)/2<=level)return level;
	}
	return -1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		if(N==0&&M==0)break;
		for(int i=0;i<N;i++)HG[i].clear(M);
		for(int i=0;i<M;i++)VG[i].clear(N);
		LEVEL.clear();
		for(int i=0;i<N;i++)for(int j=0;j<M;j++)
		{
			int &v=GRID[i][j];scanf("%d",&v);
			if(v)LEVEL.insert(make_pair(v,i*M+j)),HG[i].insert(j),VG[j].insert(i);
		}
		MN.clear();
		for(int i=0;i<N;i++)MN.insert(HG[i].GetValue());
		for(int i=0;i<M;i++)MN.insert(VG[i].GetValue());
		const int ans=Solve();
		if(ans!=-1)printf("%d\n",ans);
		else puts("NO ANSWER!");
	}
	return 0;
}

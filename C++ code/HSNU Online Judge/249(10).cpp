#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int F,K;
LL MOD;
inline int Plus(const int a,const int b){return (((LL)a+(LL)b)%MOD+MOD)%MOD;}
inline int Mul(const int a,const int b){return (LL)a*(LL)b%MOD;}
struct Seg
{
	int s[2000000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=1;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int loc,const int v)
	{
		if(l==r){s[id]=Plus(s[id],v);return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Add(id*2,l,mid,loc,v);
		else Add(id*2+1,mid+1,r,loc,v);
		s[id]=Mul(s[id*2],s[id*2+1]);
	}
	void Set(const int id,const int l,const int r,const int loc,const int v)
	{
		if(l==r){s[id]=v%MOD;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Set(id*2,l,mid,loc,v);
		else Set(id*2+1,mid+1,r,loc,v);
		s[id]=Mul(s[id*2],s[id*2+1]);
	}
	void Query(const int id,const int l,const int r,const int bl,const int br,int &ans)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){ans=Mul(ans,s[id]);return;}
		const int mid=(l+r)/2;
		Query(id*2,l,mid,bl,br,ans);
		Query(id*2+1,mid+1,r,bl,br,ans);
	}
	int Query(const int l,const int r)
	{
		int ans=1;
		Query(1,0,K-1,l,r,ans);
		return ans;
	}
	int QueryExcept(const int rank){return Mul(Query(0,rank-1),Query(rank+1,K-1));}
}SEG,ALL;
struct Fish
{
	int len,jewel;
	Fish(){}
	Fish(const int _l,const int _j):len(_l),jewel(_j){}
	bool operator<(const Fish &f)const{return len<f.len;}
};
vector<Fish>FISH;
int COLOR[500000],RANK[500000],CNT[500000],MX[500000];
vector<int>LENS[500000];
int Mxlen(const int color){return LENS[color][LENS[color].size()-1];}
bool CmpColor(int a,int b){return Mxlen(a)<Mxlen(b);}
void AddFish(const Fish &f,const int v)
{
	SEG.Add(1,0,K-1,RANK[f.jewel],v);
	CNT[RANK[f.jewel]]+=v;
}
int MaxMate(const int len)
{
	int l=0,r=K-1;
	while(l<r)
	{
		int mid=(l+r+1)/2;
		if(Mxlen(COLOR[mid])>=len*2)r=mid-1;
		else l=mid;
	}
	if(Mxlen(COLOR[l])>=len*2)return -1;
	return l;
}
int main()
{
	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d%lld",&F,&K,&MOD)==3)
	{
		MOD=2147483647LL;
		for(int i=0;i<K;i++)LENS[i].clear();
		FISH.clear();
		for(int i=0,l,j;i<F;i++)
		{
			scanf("%d%d",&l,&j);
			j--;
			FISH.push_back(Fish(l,j));
			LENS[j].push_back(l);
		}
		sort(FISH.begin(),FISH.end());
		for(int i=0;i<K;i++)COLOR[i]=i,sort(LENS[i].begin(),LENS[i].end());
		sort(COLOR,COLOR+K,CmpColor);
		for(int i=0;i<K;i++)RANK[COLOR[i]]=i,CNT[i]=0;
		SEG.Build(1,0,K-1),ALL.Build(1,0,K-1);
		int l=0;
		while(FISH[l].len*2<=Mxlen(COLOR[K-1]))AddFish(FISH[l],1),ALL.Add(1,0,K-1,RANK[FISH[l].jewel],1),l++;
		l--;
		for(int i=0;i<K;i++)MX[i]=CNT[i];
		int ans=0;
		for(int rank=K-1;rank>=0;rank--)
		{
			const int c=COLOR[rank];
			while(l>=0&&FISH[l].len*2>Mxlen(c))AddFish(FISH[l--],-1);
			int cnt=CNT[rank]-1;
			int prev=SEG.Query(rank,rank);
			printf("color=%d,prev=%d\n",c,prev);
			SEG.Set(1,0,K-1,rank,1);
			for(int i=LENS[c].size()-1;cnt>=0;cnt--)
			{
				while(LENS[c][i]>=LENS[c][cnt-1]*2)i--;
				int r=MaxMate(LENS[c][i]);
				printf("len=%d,rank=%d,color=%d\n",LENS[c][i],r,COLOR[r]);
				int ta=ans;
				ans=Plus(ans,SEG.Query(0,r));
				printf("*****cost %d\n",ans-ta);
			}
			int r=MaxMate(LENS[c][0]);
			printf("len=%d,rank=%d,color=%d\n",LENS[c][0],r,COLOR[r]);
			int ta=ans;
			ans=Plus(ans,SEG.Query(0,r));
			printf("*****cost %d\n",ans-ta);
			SEG.Set(1,0,K-1,rank,prev);
			puts("");
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
5
3
7
2 2
5 1
8 3
4 1
2 3

10 1 2147483647
1 1
2 1
4 1
8 1
16 1
32 1
64 1
128 1
256 1
512 1

10 1 2147483647
1 1
2 1
4 1
8 1
16 1
32 1
64 1
128 1
256 1
511 1

10 2 2147483647
1 1
1 2
2 1
2 2
4 1
4 2
8 1
8 2
16 1
16 2
*/ 

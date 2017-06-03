#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Deq
{
	int *S,L,R;
	Deq(){}
	Deq(const int n):S(new int[n]),L(0),R(-1){}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Back()const{return S[R];}
	int Front()const{return S[L];}
	int Size()const{return R-L+1;}
	bool Empty()const{return R<L;}
};
void getmin(int &a,const int b){if(b<a)a=b;}
int DP[1000000];
struct SegTree
{
	Deq S[4000000];
	SegTree()
	{
		for(int i=0;i<4000000;i++)S[i]=Deq(0);
	}
	void Build(const int id,const int l,const int r,const int *sum)
	{
		delete[]S[id].S;
		S[id]=Deq(sum[l]-sum[r+1]);
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid,sum),Build(id*2+1,mid+1,r,sum);
		}
	}
	void Insert(const int id,const int l,const int r,const int loc,const int val)
	{
		while(!S[id].Empty()&&DP[S[id].Back()]>=DP[val])S[id].PopBack();
		S[id].PushBack(val);
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Insert(id*2,l,mid,loc,val);
			else Insert(id*2+1,mid+1,r,loc,val);
		}
	}
	void Remove(const int id,const int l,const int r,const int loc,const int val)
	{
		if(!S[id].Empty()&&S[id].Front()==val)S[id].PopFront();
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Remove(id*2,l,mid,loc,val);
			else Remove(id*2+1,mid+1,r,loc,val);
		}
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return INF;
		if(bl<=l&&r<=br)return S[id].Empty()?INF:DP[S[id].Front()];
		const int mid=(l+r)/2;
		return min(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
}SEG;
int N,M,K,H[1000000];
void Discretize()
{
	vector<int>v;
	for(int i=0;i<N;i++)v.push_back(H[i]);
	sort(v.begin(),v.end()),v.resize(M=(int)(unique(v.begin(),v.end())-v.begin()));
	for(int i=0;i<N;i++)H[i]=(int)(lower_bound(v.begin(),v.end(),H[i])-v.begin());
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		Discretize();
		static int sum[1000001];
		for(int i=0;i<=M;i++)sum[i]=0;
		for(int i=0;i<N;i++)++sum[H[i]];
		for(int i=N-1;i>=0;i--)sum[i]+=sum[i+1];
		int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			scanf("%d",&K);
			DP[N-1]=0;
			SEG.Build(1,0,M-1,sum);
			SEG.Insert(1,0,M-1,H[N-1],N-1);
			for(int i=N-2;i>=0;i--)
			{
				DP[i]=INF;
				const int ansl=SEG.Query(1,0,M-1,0,H[i]-1);
				if(ansl!=INF)getmin(DP[i],ansl);
				const int ansr=SEG.Query(1,0,M-1,H[i],M-1);
				if(ansr!=INF)getmin(DP[i],ansr+1);
				SEG.Insert(1,0,M-1,H[i],i);
				if(i+K<N)SEG.Remove(1,0,M-1,H[i+K],i+K);
			}
//			for(int i=0;i<N;i++)printf(" %d",dp[i]);puts("");
			printf("%d\n",DP[0]);
		}
	}
	return 0;
}

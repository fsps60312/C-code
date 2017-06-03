#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
struct SegTree
{
	int S[1600000],N;
	void Build(const int id,const int l,const int r)
	{
		S[id]=INF;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N){N=_N,Build(1,0,N);}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		getmin(S[id],val);
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Modify(id*2,l,mid,loc,val);
			else Modify(id*2+1,mid+1,r,loc,val);
		}
	}
	void Modify(const int loc,const int val){Modify(1,0,N,loc,val);}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return INF;
		if(bl<=l&&r<=br)return S[id];
		const int mid=(l+r)/2;
		return min(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	}
	int Query(const int bl,const int br){return Query(1,0,N,bl,br);}
}SEG;
int N,Z[400000];
char S[400000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		N=-1;while(S[++N]);
		S[N*2-1]='\0';
		for(int i=N-1;i>=0;i--)
		{
			S[i*2]=S[i];
			if(i)S[i*2-1]='.';
		}
//		printf("S=%s\n",S);
		Z[0]=1;
		for(int i=1,mx=0;i<N*2-1;i++)
		{
			if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-i,Z[mx*2-i]);
			else Z[i]=1;
			while(i-Z[i]>=0&&i+Z[i]<N*2-1&&S[i-Z[i]]==S[i+Z[i]])++Z[i];
		}
		SEG.Build(N*2-1);
		SEG.Modify(0,0);
		for(int i=1;i<=N*2-1;i++)
		{
			const int val=SEG.Query((i-1)-Z[i-1]+1,i-1);
//			printf("i=%d: %d\n",i,val);
			SEG.Modify(i,val+1);
			if(i%2&&i<N*2-1)SEG.Modify(i+1,val+1);
//			printf("dp[%d]=%d\n",i,val+1);
		}
		printf("%d\n",SEG.Query(N*2-1,N*2-1));
	}
	return 0;
}

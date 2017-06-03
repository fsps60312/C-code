#include<cstdio>
#include<cassert>
#include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL MOD=1e9+7;
struct SegTree
{
	int N;
	LL TAG[400000];
	void Build(const int id,const int l,const int r)
	{
		TAG[id]=0LL;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int n){N=n;Build(1,1,N);}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const LL val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){(TAG[id]+=val)%=MOD;return;}
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	}
	void Modify(const int bl,const int br,const LL val){Modify(1,1,N,bl,br,val);}
	LL Query(const int id,const int l,const int r,const int loc)const
	{
		LL ans=TAG[id];
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)ans+=Query(id*2,l,mid,loc);
			else ans+=Query(id*2+1,mid+1,r,loc);
		}
		return ans%=MOD;
	}
	LL operator[](const int id)const{return Query(1,1,N,id);}
}CNT[2];
int N,S[1000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		sort(S,S+N);
		CNT[0].Build(S[0]);
		CNT[0].Modify(S[0],S[0],1LL);
		int d=0;
		for(int i=1;i<N;i++,d^=1)
		{
			CNT[d^1].Build(S[0]);
			for(int j=1;j<=S[0];j++)
			{
				const LL val=CNT[d][j];
				if(val)
				{
					CNT[d^1].Modify(j,j,val*(S[i]-j+1));
					CNT[d^1].Modify(1,j-1,val*2LL);
				}
			}
		}
		LL ans=0LL;
		for(int i=1;i<=S[0];i++)
		{
			const LL val=CNT[d][i];
			(ans+=val*(1+i/2)%MOD*(i/2))%=MOD;
			if(i%2==0)(ans-=val*(i/2))%=MOD;
		}
		printf("%lld\n",(ans%MOD+MOD)%MOD);
	}
	return 0;
}

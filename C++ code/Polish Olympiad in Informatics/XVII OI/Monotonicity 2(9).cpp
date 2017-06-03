#include<cstdio>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct SegTree
{
	int MX[4000000],N;
	void Build(const int id,const int l,const int r)
	{
		MX[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Build(const int _N){N=_N;Build(1,1,N);}
	void Update(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){getmax(MX[id],val);return;}
		const int mid=(l+r)/2;
		Update(id*2,l,mid,bl,br,val),Update(id*2+1,mid+1,r,bl,br,val);
	}
	void Update(const int bl,const int br,const int val){Update(1,1,N,bl,br,val);}
	int Query(const int id,const int l,const int r,const int loc)const
	{
		int ans=MX[id];
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)getmax(ans,Query(id*2,l,mid,loc));
			else getmax(ans,Query(id*2+1,mid+1,r,loc));
		}
		return ans;
	}
	int Query(const int loc)const{return Query(1,1,N,loc);}
}SEG;
int N,K,A[500000];
char S[500000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<K;i++)
		{
			char tmp[2];scanf("%s",tmp);
			S[i]=tmp[0];
		}
		for(int i=K;i<N;i++)S[i]=S[i%K];
		SEG.Build(1000000);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			const int j=SEG.Query(A[i]);
//			printf("i=%d,j=%d\n",i,j);
			getmax(ans,j);
			switch(S[j])
			{
				case'<':SEG.Update(A[i]+1,1000000,j+1);break;
				case'=':SEG.Update(A[i],A[i],j+1);break;
				case'>':SEG.Update(1,A[i]-1,j+1);break;
				default:assert(0);break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

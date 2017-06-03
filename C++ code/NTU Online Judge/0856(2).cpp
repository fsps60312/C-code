#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
//const int INF=2147483647/2;
inline void getmax(int &a,const int b){if(a<b)a=b;}
inline void getmin(int &a,const int b){if(b<a)a=b;}
struct SegTree
{
	int MN[800000],ADD[800000],LOW[800000],N;
	void Maintain(const int id){MN[id]=min(MN[id*2],MN[id*2+1]);getmin(LOW[id],MN[id]);}
	void Add(const int id,const int val)
	{
		MN[id]+=val,ADD[id]+=val,LOW[id]+=val;
	}
	void SetLow(const int id,const int val)
	{
		getmax(MN[id],val),getmax(LOW[id],val);
	}
	inline void PutDown(const int id)
	{
		{
			const int v=ADD[id];ADD[id]=0;
			Add(id*2,v),Add(id*2+1,v);
		}
		{
			SetLow(id*2,LOW[id]),SetLow(id*2+1,LOW[id]);
		}
	}
	void Build(const int id,const int l,const int r,const int val)
	{
		MN[id]=val,ADD[id]=0,LOW[id]=val;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid,val),Build(id*2+1,mid+1,r,val);
		}
	}
	void Build(const int _N,const int val){N=_N;Build(1,0,N-1,val);}
	void Add(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){Add(id,val);return;}
		const int mid=(l+r)/2;
		PutDown(id);
		Add(id*2,l,mid,bl,br,val),Add(id*2+1,mid+1,r,bl,br,val);
		Maintain(id);
	}
	void Add(const int bl,const int br,const int val){Add(1,0,N-1,bl,br,val);}
	void SetLow(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){SetLow(id,val);return;}
		const int mid=(l+r)/2;
		PutDown(id);
		SetLow(id*2,l,mid,bl,br,val),SetLow(id*2+1,mid+1,r,bl,br,val);
		Maintain(id);
	}
	void SetLow(const int bl,const int br,const int val){SetLow(1,0,N-1,bl,br,val);}
	int FindNegative(const int id,const int l,const int r)
	{
		assert(MN[id]<=0);
		if(l==r){SetLow(r,r,1e9);return r;}
		const int mid=(l+r)/2;
		int a0=MN[id],a1=ADD[id],a2=LOW[id],b0=MN[id*2],b1=ADD[id*2],b2=LOW[id*2],c0=MN[id*2+1],c1=ADD[id*2+1],c2=LOW[id*2+1];
		PutDown(id);
//		assert(MN[id]==min(MN[id*2],MN[id*2+1]));
		if(MN[id*2]<=0)return FindNegative(id*2,l,mid);
		if(MN[id*2+1]<=0)return FindNegative(id*2+1,mid+1,r);
		printf("id=%d,(%d,%d,%d)(%d,%d,%d)(%d,%d,%d)\n",id,a0,a1,a2,b0,b1,b2,c0,c1,c2);
		assert(0);return -1;
	}
	int FindNegative(){return FindNegative(1,0,N-1);}
}SEG;
int N,M,L;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&L)==3)
	{
		if(N==0&&M==0&&L==0)break;
		SEG.Build(N,L);
		set<int>broken;
		int ans=0;
		for(int i=0,type,s,t,x;i<M;i++)
		{
//			printf("i=%d\n",i);
			scanf("%d%d%d%d",&type,&s,&t,&x),--s,--t;
			assert(s<=t&&x>0);
			switch(type)
			{
				case 1:
				{
					if(broken.lower_bound(s)!=broken.upper_bound(t))continue;
					SEG.Add(s,t,-x);
					while(SEG.MN[1]<=0)broken.insert(SEG.FindNegative());
					++ans;
				}break;
				case 2:
				{
					SEG.Add(s,t,x);
				}break;
				case 3:
				{
					SEG.SetLow(s,t,x);
				}break;
				default:assert(0);break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

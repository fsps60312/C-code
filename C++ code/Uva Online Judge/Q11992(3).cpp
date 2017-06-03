#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int R,C,M;
struct Seg
{
	vector<int>add,mn,mx,sum,set;
	void clear(){add.resize(C*4),mn.resize(C*4),mx.resize(C*4),sum.resize(C*4),set.resize(C*4);Set(1,1,C,1,C,0);}
	inline void PushAdd(const int &id,const int &l,const int &r,const int &mid)
	{
		if(add[id]>0)
		{
			const int &v=add[id];
			add[id*2]+=v,add[id*2+1]+=v;
			mx[id*2]+=v,mn[id*2]+=v,mx[id*2+1]+=v,mn[id*2+1]+=v;
			sum[id*2]+=v*(mid-l+1),sum[id*2+1]+=v*(r-mid);
			add[id]=0;
		}
	}
	inline void PushSet(const int &id,const int &l,const int &r,const int &mid)
	{
		if(set[id]!=-1)
		{
			if(l<r)
			{
				const int &v=set[id];
				mx[id*2]=mx[id*2+1]=mn[id*2]=mn[id*2+1]=v;
				sum[id*2]=v*(mid-l+1),sum[id*2+1]=v*(r-mid);
				set[id*2]=set[id*2+1]=v;
				add[id*2]=add[id*2+1]=0;
				assert(add[id]==0);
			}
			set[id]=-1;
		}
	}
	inline void Pull(const int &id)
	{
		mn[id]=min(mn[id*2],mn[id*2+1]);
		mx[id]=max(mx[id*2],mx[id*2+1]);
		sum[id]=sum[id*2]+sum[id*2+1];
	}
	void Set(const int &id,const int &l,const int &r,const int &L,const int &R,const int &v)
	{
		if(l>R||r<L)return;
		int mid=(l+r)/2;
		PushSet(id,l,r,mid);
		PushAdd(id,l,r,mid);
		if(L<=l&&r<=R)
		{
			sum[id]=v*(r-l+1);
			mn[id]=mx[id]=v;
			set[id]=v;
			add[id]=0;
			return;
		}
		Set(id*2,l,mid,L,R,v);
		Set(id*2+1,mid+1,r,L,R,v);
		Pull(id);
	}
	void Add(const int &id,const int &l,const int &r,const int &L,const int &R,const int &v)
	{
		if(l>R||r<L)return;
		int mid=(l+r)/2;
		PushSet(id,l,r,mid);
		PushAdd(id,l,r,mid);
		if(L<=l&&r<=R)
		{
			sum[id]+=v*(r-l+1);
			mn[id]+=v,mx[id]+=v;
			add[id]+=v;
			return;
		}
		Add(id*2,l,mid,L,R,v);
		Add(id*2+1,mid+1,r,L,R,v);
		Pull(id);
	}
	void Query(const int &id,const int &l,const int &r,const int &L,const int &R,int &a,int &b,int &c)
	{
		if(l>R||r<L)return;
		int mid=(l+r)/2;
		PushSet(id,l,r,mid);
		PushAdd(id,l,r,mid);
		if(L<=l&&r<=R)
		{
//			printf("(%d,%d)(%d,%d,%d)\n",l,r,sum[id],mn[id],mx[id]);
			a+=sum[id];
			b=min(b,mn[id]);
			c=max(c,mx[id]);
			return;
		}
		Query(id*2,l,mid,L,R,a,b,c);
		Query(id*2+1,mid+1,r,L,R,a,b,c);
	}
}SEG[20];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&R,&C,&M)==3)
	{
		for(int i=0;i<R;i++)SEG[i].clear();
		for(int i=0;i<M;i++)
		{
//			printf("i=%d\n",i);
			static int type;scanf("%d",&type);
			switch(type)
			{
				case 1:
				case 2:
				{
					static int x1,y1,x2,y2,v;
					scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&v);
					x1--,x2--;
					for(int r=x1;r<=x2;r++)
					{
						if(type==1)SEG[r].Add(1,1,C,y1,y2,v);
						else SEG[r].Set(1,1,C,y1,y2,v);
					}
				}break;
				case 3:
				{
					static int x1,y1,x2,y2;
					scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
					x1--,x2--;
					int sum=0,mn=INF,mx=-INF;
					for(int r=x1;r<=x2;r++)
					{
						SEG[r].Query(1,1,C,y1,y2,sum,mn,mx);
					}
					printf("%d %d %d\n",sum,mn,mx);
				}break;
				default:assert(0);
			}
		}
	}
}

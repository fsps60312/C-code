#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Seg
{
	int sum,l,r;
	Seg(){}
	Seg(const int _sum,const int _l,const int _r):sum(_sum),l(_l),r(_r){}
	Seg operator+(const Seg &a)const{assert(r+1==a.l);return Seg(sum+a.sum,l,a.r);}
	bool operator<(const Seg &a)const{return sum<a.sum;}
};
struct Node
{
	Seg sum,lmx,mmx,rmx,lmn,mmn,rmn;
	bool flipped;
	Node(){}
	Node(const int val,const int loc):flipped(false)
	{
		sum=lmx=mmx=rmx=lmn=mmn=rmn=Seg(val,loc,loc);
	}
	void Flip()
	{
		flipped^=true;
		sum.sum*=-1;
		lmx.sum*=-1,lmn.sum*=-1;
		mmx.sum*=-1,mmn.sum*=-1;
		rmx.sum*=-1,rmn.sum*=-1;
		swap(lmx,lmn),swap(mmx,mmn),swap(rmx,rmn);
	}
}S[400000];
Node Merge(const Node &a,const Node &b)
{
	Node s;
	s.flipped=false;
	s.sum=a.sum+b.sum;
	s.lmx=max(a.lmx,a.sum+b.lmx);
	s.mmx=max(max(a.mmx,b.mmx),a.rmx+b.lmx);
	s.rmx=max(a.rmx+b.sum,b.rmx);
	s.lmn=min(a.lmn,a.sum+b.lmn);
	s.mmn=min(min(a.mmn,b.mmn),a.rmn+b.lmn);
	s.rmn=min(a.rmn+b.sum,b.rmn);
	return s;
}
void PutDown(const int id)
{
	if(!S[id].flipped)return;
	S[id*2].Flip(),S[id*2+1].Flip();
	S[id].flipped=false;
}
int A[100000];
void Build(const int id,const int l,const int r)
{
	if(l==r){S[id]=Node(A[r],r);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	S[id]=Merge(S[id*2],S[id*2+1]);
}
void Modify(const int id,const int l,const int r,const int loc,const int val)
{
	if(l==r){assert(loc==r);S[id]=Node(A[r]=val,r);return;}
	const int mid=(l+r)/2;
	PutDown(id);
	if(loc<=mid)Modify(id*2,l,mid,loc,val);
	else Modify(id*2+1,mid+1,r,loc,val);
	S[id]=Merge(S[id*2],S[id*2+1]);
}
Node Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br)return S[id];
	const int mid=(l+r)/2;
	PutDown(id);
	if(br<mid+1)return Query(id*2,l,mid,bl,br);
	if(mid<bl)return Query(id*2+1,mid+1,r,bl,br);
	return Merge(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
}
void Flip(const int id,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br){S[id].Flip();return;}
	if(r<bl||br<l)return;
	const int mid=(l+r)/2;
	PutDown(id);
	Flip(id*2,l,mid,bl,br);
	Flip(id*2+1,mid+1,r,bl,br);
	S[id]=Merge(S[id*2],S[id*2+1]);
}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		Build(1,0,N-1);
		scanf("%d",&M);
		while(M--)
		{
			int type;scanf("%d",&type);
			if(type==0)
			{
				int i,v;scanf("%d%d",&i,&v);i--;
				Modify(1,0,N-1,i,v);
			}
			else if(type==1)
			{
				int l,r,k;scanf("%d%d%d",&l,&r,&k);l--,r--;
				vector<Node>history;
				int ans=0;
				while(k--)
				{
					const Node &s=Query(1,0,N-1,l,r);
					if(s.mmx.sum<=0)break;
					ans+=s.mmx.sum;
					history.push_back(s);
					Flip(1,0,N-1,s.mmx.l,s.mmx.r);
				}
				printf("%d\n",ans);
				for(const Node &s:history)Flip(1,0,N-1,s.mmx.l,s.mmx.r);
			}
			else assert(0);
		}
	}
	return 0;
}

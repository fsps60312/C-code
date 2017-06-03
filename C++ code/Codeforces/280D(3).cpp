#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,A[100000];
struct State
{
	int mmx[21],lmx[21],rmx[21],amx[21];
	int sum;
	void Clear(const int val)
	{
		sum=val;
		for(int i=0;i<=20;i++)lmx[i]=rmx[i]=amx[i]=val;
		mmx[0]=0;
		for(int i=1;i<=20;i++)mmx[i]=max(0,val);
	}
}S[400000];
void Merge(int *s,const int *ls,const int *rs)
{
	for(int i=0;i<=20;i++)s[i]=0;
	for(int i=0;i<=20;i++)for(int j=0;i+j<=20;j++)getmax(s[i+j],ls[i]+rs[j]);
}
void Merge(State &s,const State &a,const State &b)
{
	s.sum=a.sum+b.sum;
	Merge(s.mmx,a.mmx,b.mmx);
	Merge(s.lmx,a.lmx,b.mmx);
	Merge(s.rmx,a.mmx,b.rmx);
	Merge(s.amx,a.lmx,b.rmx);
	for(int i=0;i<=20;i++)
	{
		getmax(s.lmx[i],a.sum+b.lmx[i]);
		getmax(s.rmx[i],a.rmx[i]+b.sum);
		getmax(s.amx[i],a.sum+b.amx[i]);
		getmax(s.amx[i],a.amx[i]+b.sum);
	}
	for(int i=0;i<=20;i++)for(int j=0;i+j+1<=20;j++)
	{
		getmax(s.mmx[i+j+1],a.rmx[i]+b.lmx[j]);
		getmax(s.lmx[i+j+1],a.amx[i]+b.lmx[j]);
		getmax(s.rmx[i+j+1],a.rmx[i]+b.amx[j]);
		getmax(s.amx[i+j+1],a.amx[i]+b.amx[j]);
	}
}
void Maintain(const int id)
{
	Merge(S[id],S[id*2],S[id*2+1]);
}
void Build(const int id,const int l,const int r)
{
	if(l==r){S[id].Clear(A[r]);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	Maintain(id);
}
void Modify(const int id,const int l,const int r,const int loc,const int val)
{
	if(l==r){assert(loc==r);A[r]=val;S[id].Clear(val);return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Modify(id*2,l,mid,loc,val);
	else Modify(id*2+1,mid+1,r,loc,val);
	Maintain(id);
}
State Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br)return S[id];
	if(r<bl||br<l)
	{
		State ans;
		ans.Clear(0);
		return ans;
	}
	const int mid=(l+r)/2;
	State ans;
	Merge(ans,Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		Build(1,0,N-1);
		int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			int type;scanf("%d",&type);
			if(type==0)
			{
				int i,val;scanf("%d%d",&i,&val),i--;
				Modify(1,0,N-1,i,val);
			}
			else if(type==1)
			{
				int l,r,k;scanf("%d%d%d",&l,&r,&k),l--,r--;
//				for(int i=0;i<=20;i++)printf("%d ",Query(1,0,N-1,l,r).mmx[i]);puts("");
				printf("%d\n",Query(1,0,N-1,l,r).mmx[k]);
			}
			else assert(0);
		}
	}
	return 0;
}

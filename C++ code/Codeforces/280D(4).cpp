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
	int sum,n;
	void Clear(const int val)
	{
		n=1;
		sum=val;
		lmx[0]=rmx[0]=amx[0]=lmx[1]=rmx[1]=amx[1]=val;
		mmx[0]=0;
		mmx[1]=max(0,val);
	}
}S[400000];
void Merge(State &s,const State &a,const State &b)
{
	s.n=min(20,a.n+b.n);
	s.sum=a.sum+b.sum;
	for(int i=0;i<=s.n;i++)s.mmx[i]=s.lmx[i]=s.rmx[i]=s.amx[i]=0;
	for(int i=0;i<=a.n;i++)for(int j=0;j<=b.n&&i+j<=s.n;j++)
	{
		getmax(s.mmx[i+j],a.mmx[i]+b.mmx[j]);
		getmax(s.lmx[i+j],a.lmx[i]+b.mmx[j]);
		getmax(s.rmx[i+j],a.mmx[i]+b.rmx[j]);
		getmax(s.amx[i+j],a.lmx[i]+b.rmx[j]);
	}
	for(int i=0;i<=a.n;i++)
	{
		getmax(s.rmx[i],a.rmx[i]+b.sum);
		getmax(s.amx[i],a.amx[i]+b.sum);
	}
	for(int i=0;i<=b.n;i++)
	{
		getmax(s.lmx[i],a.sum+b.lmx[i]);
		getmax(s.amx[i],a.sum+b.amx[i]);
	}
	for(int i=0;i<=a.n;i++)for(int j=0;j<=b.n&&i+j+1<=s.n;j++)
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
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
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
				const State &ans=Query(1,0,N-1,l,r);
				printf("%d\n",ans.mmx[min(k,ans.n)]);
			}
			else assert(0);
		}
	}
	return 0;
}

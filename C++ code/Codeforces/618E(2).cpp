#include<cstdio>
#include<cassert>
#include<cmath>
using namespace std;
const long double PI=acos(-1.0);
struct SegTree
{
	int N;
	long double A[1200000],B[1200000],L[1200000];
	void Maintain(const int id)
	{
		const long double y=L[id*2]*sin(A[id*2])+L[id*2+1]*sin(B[id*2]+A[id*2+1]);
		const long double x=L[id*2]*cos(A[id*2])+L[id*2+1]*cos(B[id*2]+A[id*2+1]);
		A[id]=atan2(y,x),L[id]=sqrt(x*x+y*y),B[id]=B[id*2]+B[id*2+1];
	}
	void Build(const int id,const int l,const int r)
	{
		if(l==r){A[id]=B[id]=0.0,L[id]=1.0;return;}
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		Maintain(id);
	}
	void Build(const int _N){N=_N;Build(1,1,N);}
	void ModifyA(const int id,const int l,const int r,const int loc,const long double v)
	{
		if(l==r){A[id]+=v,B[id]+=v;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)ModifyA(id*2,l,mid,loc,v);
		else ModifyA(id*2+1,mid+1,r,loc,v);
		Maintain(id);
	}
	void ModifyA(const int loc,const long double v){ModifyA(1,1,N,loc,v);}
	void ModifyL(const int id,const int l,const int r,const int loc,const long double v)
	{
		if(l==r){L[id]+=v;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)ModifyL(id*2,l,mid,loc,v);
		else ModifyL(id*2+1,mid+1,r,loc,v);
		Maintain(id);
	}
	void ModifyL(const int loc,const long double v){ModifyL(1,1,N,loc,v);}
}SEG;
int N,M;
int main()
{
//	printf("%.10f\n",atan2(-1.0,0.0)/PI*180.0);
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		SEG.Build(N);
		for(int i=0,x,y,z;i<M;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			if(x==1)
			{
				SEG.ModifyL(y,z);
			}
			else if(x==2)
			{
				SEG.ModifyA(y,-z/180.0*PI);
			}
			else assert(0);
			const long double a=SEG.A[1],l=SEG.L[1];
//			printf("(%.10f,%.10f)\n",a/PI*180.0,l);
			printf("%.10f %.10f\n",(double)(l*cos(a)),(double)(l*sin(a)));
		}
	}
	return 0;
}

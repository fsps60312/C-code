#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
LL N,M,SUM[400000],MIN[400000],MAX[400000],TAG[400000];
struct Bst
{
	void Build(LL id,LL l,LL r)
	{
		SUM[id]=MIN[id]=MAX[id]=TAG[id]=0LL;
		if(l==r)return;
		LL mid=(l+r)>>1,i1=id<<1,i2=i1+1LL;
		Build(i1,l,mid);
		Build(i2,mid+1LL,r);
	}
	LL QuerySum(){return SUM[1];}
	void PutDown(LL id,LL l,LL r,LL mid,LL i1,LL i2)
	{
		if(!TAG[id])return;
		TAG[i1]=TAG[i2]=1LL,TAG[id]=0LL;
		LL &v=MIN[id];
		MIN[i1]=MIN[i2]=MAX[i1]=MAX[i2]=v;
		SUM[i1]=v*(mid-l+1LL);
		SUM[i2]=v*(r-mid);
	}
	void Modify(LL id,LL l,LL r,LL L,LL R,LL v)
	{
		if(L<=l&&r<=R)
		{
			if(MIN[id]>=v)return;
			if(MAX[id]<=v)
			{
				SUM[id]=v*(r-l+1LL);
				MIN[id]=MAX[id]=v;
				TAG[id]=1LL;
				return;
			}
		}
		if(l>R||r<L)return;
		LL mid=(l+r)>>1,i1=id<<1,i2=i1+1LL;
		PutDown(id,l,r,mid,i1,i2);
		Modify(i1,l,mid,L,R,v);
		Modify(i2,mid+1LL,r,L,R,v);
		SUM[id]=SUM[i1]+SUM[i2];
		MIN[id]=min(MIN[i1],MIN[i2]);
		MAX[id]=max(MAX[i1],MAX[i2]);
	}
}BST;
struct Point
{
	LL x,y,z;
	Point(){}
	Point(LL x,LL y,LL z):x(x),y(y),z(z){}
};
vector<Point> P;
bool cmpz(Point a,Point b){return a.z>b.z;}
int main()
{
	while(scanf("%lld%lld",&N,&M)==2&&(N||M))
	{
		P.clear();
		for(LL i=0LL,a,b,c;i<N;i++)
		{
			scanf("%lld%lld%lld",&a,&b,&c);
			P.push_back(Point(a,b,c));
		}
		sort(P.begin(),P.end(),cmpz);
		BST.Build(1LL,1LL,M);
		LL ans=0LL;
		for(LL zpre=M,znow=M,i=0LL;;)
		{
			znow=P[i].z;
			ans+=(zpre-znow)*BST.QuerySum();
			while(i<N&&P[i].z==znow)
			{
				BST.Modify(1LL,1LL,M,1LL,P[i].y,P[i].x);
				i++;
			}
//			printf("%lld:%lld\n",znow,BST.QuerySum());
			zpre=znow;
			if(i==N){ans+=znow*BST.QuerySum();break;}
		}
		printf("%lld\n",M*M*M-ans);
	}
	return 0;
}

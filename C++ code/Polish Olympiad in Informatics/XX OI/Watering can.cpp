#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,K,*D;
int MX[1200000],ANS[1200000],TAG[1200000];
void Maintain(const int id)
{
	MX[id]=max(MX[id*2],MX[id*2+1]);
	ANS[id]=ANS[id*2]+ANS[id*2+1];
}
void Build(const int id,const int l,const int r)
{
	TAG[id]=0;
	if(l==r)
	{
		if(D[r]>=K)MX[id]=-INF,ANS[id]=1;
		else MX[id]=D[r],ANS[id]=0;
		return;
	}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	Maintain(id);
}
void inicjuj(int _N,int _K,int *_D)
{
	N=_N,K=_K,D=_D;
	Build(1,0,N-1);
}
void PutDown(const int id)
{
	if(!TAG[id])return;
	MX[id*2]+=TAG[id],MX[id*2+1]+=TAG[id];
	TAG[id*2]+=TAG[id],TAG[id*2+1]+=TAG[id];
	TAG[id]=0;
}
void TransToAns(const int id,const int l,const int r)
{
	if(MX[id]<K)return;
	if(l==r){MX[id]=-INF,ANS[id]=1;return;}
	const int mid=(l+r)/2;
	PutDown(id);
	TransToAns(id*2,l,mid),TransToAns(id*2+1,mid+1,r);
	Maintain(id);
}
void Modify(const int id,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br)
	{
		MX[id]++,TAG[id]++;
		TransToAns(id,l,r);
		return;
	}
	if(r<bl||br<l)return;
	const int mid=(l+r)/2;
	PutDown(id);
	Modify(id*2,l,mid,bl,br),Modify(id*2+1,mid+1,r,bl,br);
	Maintain(id);
}
void podlej(const int l,const int r)
{
	Modify(1,0,N-1,l,r);
}
int Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(bl<=l&&r<=br)return ANS[id];
	if(r<bl||br<l)return 0;
	const int mid=(l+r)/2;
	PutDown(id);
	return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
}
int dojrzale(const int l,const int r)
{
	return Query(1,0,N-1,l,r);
}
//int main(){}

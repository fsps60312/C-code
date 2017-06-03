#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
LL S[100000],SUM[400000],TAG[400000];
void Maintain(const int id){SUM[id]=SUM[id*2]+SUM[id*2+1];} 
void Build(const int id,const int l,const int r,const LL *s)
{
	SUM[id]=TAG[id]=0LL;
	if(l==r){SUM[id]=s[r];return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid,s),Build(id*2+1,mid+1,r,s);
	Maintain(id);
}
void PutDown(const int id,const int l,const int mid,const int r)
{
	if(!TAG[id])return;
	const LL &v=TAG[id];
	TAG[id*2]+=v,TAG[id*2+1]+=v;
	SUM[id*2]+=(LL)(mid-l+1)*v,SUM[id*2+1]+=(LL)(r-mid)*v;
	TAG[id]=0LL;
}
void Modify(const int id,const int l,const int r,const int bl,const int br,const LL &v)
{
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br){TAG[id]+=v,SUM[id]+=(LL)(r-l+1)*v;return;}
	const int mid=(l+r)/2;
	PutDown(id,l,mid,r);
	Modify(id*2,l,mid,bl,br,v),Modify(id*2+1,mid+1,r,bl,br,v);
	Maintain(id);
}
LL Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return 0LL;
	if(bl<=l&&r<=br)return SUM[id];
	const int mid=(l+r)/2;
	PutDown(id,l,mid,r);
	return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;
		scanf("%d%d",&N,&querycount);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		Build(1,0,N-1,S);
		for(int l,r;querycount--;)
		{
			static char type[6];
			scanf("%s%d%d",type,&l,&r),l--,r--;
			if(type[0]=='a')
			{
				static LL v;scanf("%lld",&v);
				Modify(1,0,N-1,l,r,v);
			}
			else if(type[0]=='q')
			{
				printf("%lld\n",Query(1,0,N-1,l,r));
			}
		}
	}
	return 0;
}

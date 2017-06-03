#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<cmath>
#define int long long
using namespace std;
const double EPS=1e-8;
struct Deq
{
	vector<int>data;
	int l;
	void clear(){data.clear(),l=0;}
	int size()const{return (int)data.size()-l;}
	void pop_front(const int cnt)
	{
		l+=cnt;
		if(size()<=0)clear();
	}
	void push_back(const int v){data.push_back(v);}
	int &operator[](const int i){return data[l+i];}
};
Deq SUM[400000];
int SQ[400000];
int GetSUM(const int id,const int i,const int l,const int r){return i<SUM[id].size()?SUM[id][i]:r-l+1;}
void PutDown(const int id)
{
	if(!SQ[id])return;
	SUM[id*2].pop_front(SQ[id]),SUM[id*2+1].pop_front(SQ[id]);
	SQ[id*2]+=SQ[id],SQ[id*2+1]+=SQ[id];
	SQ[id]=0;
}
void Maintain(const int id,const int l,const int mid,const int r)
{
	SUM[id].clear();
	for(int i=0;i<max(SUM[id*2].size(),SUM[id*2+1].size());i++)SUM[id].push_back(GetSUM(id*2,i,l,mid)+GetSUM(id*2+1,i,mid+1,r));
}
void SetSUM(const int id,int v)
{
	SUM[id].clear();
	while(v>1)SUM[id].push_back(v),v=(int)(sqrt(v)+EPS);
}
void Build(const int id,const int l,const int r,const int *s)
{
//	printf("id=%lld(%lld,%lld)\n",id,l,r);
	SQ[id]=0;
	if(l==r){SetSUM(id,s[r]);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid,s),Build(id*2+1,mid+1,r,s);
	Maintain(id,l,mid,r);
}
void Modify(const int id,const int l,const int r,const int loc,const int v)
{
	if(l==r){assert(r==loc);SetSUM(id,v);return;}
	const int mid=(l+r)/2;
	PutDown(id);
	if(loc<=mid)Modify(id*2,l,mid,loc,v);
	else Modify(id*2+1,mid+1,r,loc,v);
	Maintain(id,l,mid,r);
}
void Sqrt(const int id,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br){SUM[id].pop_front(1),SQ[id]++;return;}
	const int mid=(l+r)/2;
	PutDown(id);
	Sqrt(id*2,l,mid,bl,br),Sqrt(id*2+1,mid+1,r,bl,br);
	Maintain(id,l,mid,r);
}
int Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return 0;
	if(bl<=l&&r<=br)return GetSUM(id,0,l,r);
	const int mid=(l+r)/2;
	PutDown(id);
	return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
}
int N,S[100000];
main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%lld",&testcount);
	for(int querycount;testcount--;)
	{
		scanf("%lld%lld",&N,&querycount);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		Build(1,0,N-1,S);
		for(int p,e,c;querycount--;)
		{
			scanf("%lld%lld%lld",&p,&e,&c);
			if(p==0)
			{
				e--,c--;
				Sqrt(1,0,N-1,e,c);
			}
			else if(p==1)
			{
				e--;
				Modify(1,0,N-1,e,c);
			}
			else if(p==2)
			{
				e--,c--;
				printf("%lld\n",Query(1,0,N-1,e,c));
			}
			else assert(0);
		}
	}
	return 0;
}

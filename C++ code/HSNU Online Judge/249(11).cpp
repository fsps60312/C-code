#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int MOD;
int MUL[2000000];
void Build(const int id,const int l,const int r)
{
	MUL[id]=1;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Set(const int id,const int l,const int r,const int loc,const int v)
{
	if(l==r){assert(loc==l),MUL[id]=v%MOD;return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Set(id*2,l,mid,loc,v);
	else Set(id*2+1,mid+1,r,loc,v);
	MUL[id]=(LL)MUL[id*2]*MUL[id*2+1]%MOD;
}
int Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(r<bl||l>br)return 1;
	if(bl<=l&&r<=br)return MUL[id];
	const int mid=(l+r)/2;
	return (LL)Query(id*2,l,mid,bl,br)*Query(id*2+1,mid+1,r,bl,br)%MOD;
}
int F,K;
struct Fish
{
	int len,type;
	Fish(){}
	Fish(const int _l,const int _t):len(_l),type(_t){}
	bool operator<(const Fish &f)const{return len<f.len;} 
};
vector<Fish>FISH;
vector<int>LEN[500000];
int Mxlen(const int i){return LEN[i][LEN[i].size()-1];}
bool CmpMaxLen(const int a,const int b){return Mxlen(a)<Mxlen(b);}
int TYPE[500000],RANK[500000];
int LastCanEat(const int type,const int len)
{
	if(LEN[type][0]*2>len)return -1;
	int l=0,r=LEN[type].size()-1;
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(LEN[type][mid]*2<=len)l=mid;
		else r=mid-1;
	}
	return l;
}
int LastEatSameAmount(const int type)
{
	const int last_can_eat=LastCanEat(type,Mxlen(type));
	int l=RANK[type],r=K-1;
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(LastCanEat(type,Mxlen(TYPE[mid]))>last_can_eat)r=mid-1;
		else l=mid;
	}
	return l;
}
int CNT[500000];
int main()
{
	while(scanf("%d%d%d",&F,&K,&MOD)==3)
	{
		for(int i=0;i<K;i++)LEN[i].clear(),TYPE[i]=i,CNT[i]=0;
		FISH.clear();
		for(int i=0,l,t;i<F;i++)
		{
			scanf("%d%d",&l,&t);
			FISH.push_back(Fish(l,--t));
			LEN[t].push_back(l);
		}
		sort(FISH.begin(),FISH.end());
		for(int i=0;i<K;i++)sort(LEN[i].begin(),LEN[i].end());
		sort(TYPE,TYPE+K,CmpMaxLen);
		for(int i=0;i<K;i++)RANK[TYPE[i]]=i;
		Build(1,0,K-1);
		int ans=0;
		for(int rank=0,i=0;rank<K;rank++)
		{
			const int &type=TYPE[rank];
			while(i<F&&FISH[i].len*2<=Mxlen(type))
			{
				const int rk=RANK[FISH[i].type];
				CNT[rk]++;
				Set(1,0,K-1,rk,CNT[rk]+1);
				i++;
			}
			int biggerfish=LastEatSameAmount(type);
			LL tmp=Query(1,0,K-1,rank+1,biggerfish);
			(tmp+=CNT[rank])%=MOD;
			(tmp*=Query(1,0,K-1,0,rank-1))%=MOD;
			(ans+=tmp)%=MOD;
		}
		printf("%d\n",ans);
	}
	return 0;
}

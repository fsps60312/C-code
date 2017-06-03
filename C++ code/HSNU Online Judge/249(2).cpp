#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
int F,K;
LL MOD;
struct Fish
{
	int len,jewel;
	int cnt;LL add;
	Fish(){}
	Fish(const int l,const int j):len(l),jewel(j),cnt(-1){}
	bool operator<(const Fish &f)const{return len<f.len;}
};
vector<Fish>FISH;
LL MUL[2000000];
int CNT[500001];
void Build(const int id,const int l,const int r)
{
	MUL[id]=1LL;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Add(const int id,const int l,const int r,const int loc)
{
	if(l==r){assert(loc==l),MUL[id]++,MUL[id]%=MOD;return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Add(id*2,l,mid,loc);
	else Add(id*2+1,mid+1,r,loc);
	MUL[id]=MUL[id*2]*MUL[id*2+1]%MOD;
}
void Query(const int id,const int l,const int r,const int bl,const int br,LL &ans)
{
	if(l>br||r<bl)return;
	if(bl<=l&&r<=br){ans*=MUL[id],ans%=MOD;return;}
	const int mid=(l+r)/2;
	Query(id*2,l,mid,bl,br,ans);
	Query(id*2+1,mid+1,r,bl,br,ans);
}
LL Query(const int l,const int r)
{
	LL ans=1LL;
	Query(1,1,K,l,r,ans);
	return ans;
}
void AssignCntAdd(Fish &f)
{
	f.cnt=CNT[f.jewel]+1;
	f.add=Query(1,f.jewel-1)*Query(f.jewel+1,K)%MOD;
}
bool VIS[500001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld",&F,&K,&MOD)==3)
	{
		FISH.clear();
		for(int i=0,l,j;i<F;i++)
		{
			scanf("%d%d",&l,&j);
			FISH.push_back(Fish(l,j));
		}
		sort(FISH.begin(),FISH.end());
		Build(1,1,K);
		for(int i=1;i<=K;i++)CNT[i]=0;
		for(int l=0,r=0;;l++)
		{
			const Fish &f=FISH[l];
			while(r<F&&FISH[r].len<f.len*2)AssignCntAdd(FISH[r]),r++;
			if(r==F)break;
			Add(1,1,K,f.jewel);
			CNT[f.jewel]++;
		}
//		for(int i=1;i<=K;i++)printf(" %d",CNT[i]);puts("");
//		for(int i=1;i<=K;i++)printf(" %lld",Query(i,i));puts("");
		for(int i=1;i<=K;i++)VIS[i]=false;
		LL ans=Query(1,K);
		for(int i=F-1;i>=0;i--)
		{
			const Fish &f=FISH[i];
//			printf("rank=%d,len=%d,jewel=%d,cnt=%d,add=%lld\n",i,f.len,f.jewel,f.cnt,f.add);
			assert(f.cnt!=-1);
			if(f.cnt<=CNT[f.jewel]||VIS[f.jewel])continue;
			assert(f.cnt==CNT[f.jewel]+1);
			VIS[f.jewel]=true;
			ans+=f.add,ans%=MOD;
		}
		ans--;
		if(ans<0LL)ans+=MOD;
		printf("%lld\n",ans);
//		break;
	}
	return 0;
}

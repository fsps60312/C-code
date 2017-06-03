#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int F,K;
LL MOD;
LL MUL[2000000];
void Build(const int id,const int l,const int r)
{
	MUL[id]=1LL;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Add(const int id,const int l,const int r,const int loc)
{
	if(l==r){MUL[id]++,MUL[id]%=MOD;return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Add(id*2,l,mid,loc);
	else Add(id*2+1,mid+1,r,loc);
	MUL[id]=MUL[id*2]*MUL[id*2+1]%MOD;
}
void Set(const int id,const int l,const int r,const int loc,const LL v)
{
	if(l==r){MUL[id]=v%MOD;return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Set(id*2,l,mid,loc,v);
	else Set(id*2+1,mid+1,r,loc,v);
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
	Query(1,0,K-1,l,r,ans);
	return ans;
}
LL QueryExcept(const int jewel){return Query(0,jewel-1)*Query(jewel+1,K-1)%MOD;}
struct Fish
{
	int len,jewel;
	Fish(){}
	Fish(const int _l,const int _j):len(_l),jewel(_j){}
	bool operator<(const Fish &f)const{return len<f.len;}
};
vector<Fish>FISH;
int MXLEN[500000],COLOR[500000],RANK[500000];
bool CmpColor(int a,int b){return MXLEN[a]<MXLEN[b];}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d%lld",&F,&K,&MOD);
	MOD=2147483647LL;
	for(int i=0;i<K;i++)MXLEN[i]=-1;
	for(int i=0,l,j;i<F;i++)
	{
		scanf("%d%d",&l,&j);
		j--;
		FISH.push_back(Fish(l,j));
		getmax(MXLEN[j],l);
	}
	sort(FISH.begin(),FISH.end());
	for(int i=0;i<K;i++)COLOR[i]=i;
	sort(COLOR,COLOR+K,CmpColor);
	for(int i=0;i<K;i++)RANK[COLOR[i]]=i;
	LL ans=0LL;
	Build(1,0,K-1);
	for(int i=0,l=0;i<K;i++)
	{
		const int c=COLOR[i];
		const int mxlen=MXLEN[c];
		printf("mxlen=%d,color=%d\n",mxlen,c);
		ans++,ans%=MOD;
		for(;l<K&&FISH[l].len*2<=mxlen;l++)
		{
			const Fish &f=FISH[l];
			ans+=QueryExcept(f.jewel),ans%=MOD;
			printf("ans=%lld\n",ans);
			Add(1,0,K-1,RANK[f.jewel]);
		}
		for(int j=0;j<K;j++)if(j!=RANK[c])Set(1,0,K-1,j,1LL);
	}
	printf("%lld\n",ans);
	return 0;
}

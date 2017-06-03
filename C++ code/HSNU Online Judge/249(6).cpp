#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
int F,K;
LL MOD;
struct Seg
{
	LL s[2000000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=1LL;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int loc)
	{
		if(l==r){s[id]++,s[id]%=MOD;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Add(id*2,l,mid,loc);
		else Add(id*2+1,mid+1,r,loc);
		s[id]=s[id*2]*s[id*2+1]%MOD;
	}
	void Set(const int id,const int l,const int r,const int loc,const LL v)
	{
		if(l==r){s[id]=v%MOD;return;}
		const int mid=(l+r)/2;
		if(loc<=mid)Set(id*2,l,mid,loc,v);
		else Set(id*2+1,mid+1,r,loc,v);
		s[id]=s[id*2]*s[id*2+1]%MOD;
	}
	void Query(const int id,const int l,const int r,const int bl,const int br,LL &ans)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){ans*=s[id],ans%=MOD;return;}
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
}S1,S2;
struct Fish
{
	int len,jewel;
	Fish(){}
	Fish(const int _l,const int _j):len(_l),jewel(_j){}
	bool operator<(const Fish &f)const{return len<f.len;}
};
vector<Fish>FISH;
int MXLEN[500000],COLOR[500000],RANK[500000];
bool VIS[500000];
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
	for(int i=0;i<K;i++)RANK[COLOR[i]]=i,VIS[i]=false;
	LL ans=0LL;
	S1.Build(1,0,K-1),S2.Build(1,0,K-1);
	for(int i=0,l=0;i<K;i++)
	{
		const int c=COLOR[i];
		const int mxlen=MXLEN[c];
		printf("mxlen=%d,color=%d\n",mxlen,c);
//		ans++,ans%=MOD;
		for(;l<K&&FISH[l].len*2<=mxlen;l++)
		{
			const Fish &f=FISH[l];
			ans+=S1.QueryExcept(RANK[f.jewel]),ans%=MOD;
//			printf("ans=%lld\n",ans);
			S1.Add(1,0,K-1,RANK[f.jewel]);
			if(VIS[RANK[f.jewel]]){VIS[RANK[f.jewel]]=false;continue;}
			S2.Add(1,0,K-1,RANK[f.jewel]);
		}
		ans+=S2.Query(0,K-1);//all pre cnt is 0
		S2.Set(1,0,K-1,i,1LL);
		VIS[i]=true;
		//color:edcba
		//e:(a:0~4,b:0~5,c:0~3,d:0,e:0~1)
		//if(e>2)return 0;
		//else if(e>=1)return 5*6*4*1
		//else if(e==0)
		//if(
		//color a,color b
		//a: a*3,b*5,c*4 => 4*6*5 (a:1~4,b:0~5,c:0~4)
		//b: a*5,b*7,c*5 => (a:0~5,b:1~7,c:0~5)
		//new: (a:0 5,b:1~7,c:0~5)(a:1~4,b:6~7,c:0~5)(a:1~4,b:1~5,c:5)
		//become:(a:0 5,b:1~7,c:0~5)(a:1~4,b:0~7,c:0~4)(a:1~4,b:6~7,c:5)(a:1~4,b:1~5,c:5)
		//     = (a:0 5,b:1~7,c:0~5)(a:1~4,b:0~7,c:0~4)(a:1~4,b:1~7,c:5)
		//     = (a:0 5,b:1~7,c:0~5)(a:1~4,b:0~7,c:0~5)-(a:1~4,b:0,c:5)
//		for(int j=0;j<K;j++)if(j!=RANK[c])S1.Set(1,0,K-1,j,1LL);
	}
	printf("%lld\n",ans);
	return 0;
}

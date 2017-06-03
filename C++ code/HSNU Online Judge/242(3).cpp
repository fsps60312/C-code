#include<cstdio>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;
bool EMPTY[400000];
void Build(const int id,const int l,const int r)
{
	EMPTY[id]=false;
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void SetEmpty(const int id,const int l,const int r,const int bl,const int br)
{
	if(l>br||r<bl)return;
	if(bl<=l&&r<=br){EMPTY[id]=true;return;}
	const int mid=(l+r)/2;
	SetEmpty(id*2,l,mid,bl,br),SetEmpty(id*2+1,mid+1,r,bl,br);
}
bool IsEmpty(const int id,const int l,const int r,const int loc)
{
	if(EMPTY[id])return true;
	if(l==r)return false;
	const int mid=(l+r)/2;
	if(loc<=mid)return IsEmpty(id*2,l,mid,loc);
	else return IsEmpty(id*2+1,mid+1,r,loc);
}
struct Observe
{
	int a,b;
	Observe(){}
	Observe(int _a,int _b):a(_a),b(_b){}
};
bool cmpa(const Observe &a,const Observe &b){return a.a<b.a;}
bool cmpb(const Observe &a,const Observe &b){return a.b<b.b;}
vector<Observe>OBSERVE;
vector<int>ANS;
int N,K,M;
bool ISEMPTY[100001];
void Solve()
{
	ANS.clear();
	int cnt=0;
	for(int i=1;i<=N;i++)ISEMPTY[i]=IsEmpty(1,1,N,i);
	for(int i=1;i<=N;i++)if(!ISEMPTY[i])cnt++,ANS.push_back(i);
//	printf("a:cnt=%d\n",cnt);
	assert(cnt>=K);
	if(cnt==K)return;
	else ANS.clear();
	if(OBSERVE.empty())return;
	for(int i=0;i<OBSERVE.size();i++)
	{
		Observe &o=OBSERVE[i];
		while(ISEMPTY[o.a])o.a++;
		while(ISEMPTY[o.b])o.b--;
		assert(o.a<=o.b);
	}
	static bool isans1[100001],isans2[100001];
	for(int i=1;i<=N;i++)isans1[i]=isans2[i]=false;
	//////////////////////////////////////////////
	int now,cnt1,cnt2;
	sort(OBSERVE.begin(),OBSERVE.end(),cmpa);
	cnt1=0,now=OBSERVE[0].b;
	for(int i=1;i<OBSERVE.size();i++)
	{
		const Observe &o=OBSERVE[i];
		if(o.a>now)isans1[now]=true,cnt1++,now=o.b;
		else if(o.b<now)now=o.b;
	}
	isans1[now]=true,cnt1++;
	//////////////////////////////////////////////
	sort(OBSERVE.begin(),OBSERVE.end(),cmpb);
	cnt2=0,now=OBSERVE[OBSERVE.size()-1].a;
	for(int i=(int)OBSERVE.size()-2;i>=0;i--)
	{
		const Observe &o=OBSERVE[i];
		if(o.b<now)isans2[now]=true,cnt2++,now=o.a;
		else if(o.a>now)now=o.a;
	}
	isans2[now]=true,cnt2++;
	//////////////////////////////////////////////
	assert(cnt1==cnt2&&cnt1<=K);
	ANS.clear();
	if(cnt1==K){for(int i=1;i<=N;i++)if(isans1[i]&&isans2[i])ANS.push_back(i);return;}
	else
	{
		for(int i=0;i<OBSERVE.size();i++)
		{
			const Observe &o=OBSERVE[i];
			if(o.a==o.b)ANS.push_back(o.a);
		}
		ANS.resize(unique(ANS.begin(),ANS.end())-ANS.begin());
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&K,&M)==3)
	{
		Build(1,1,N);
		OBSERVE.clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			if(c==1)OBSERVE.push_back(Observe(a,b));
			else SetEmpty(1,1,N,a,b);
		}
		ANS.clear();
		Solve();
		if(ANS.empty())puts("-1");
		else for(int i=0;i<ANS.size();i++)printf("%d\n",ANS[i]);
		break;
	}
	return 0;
}

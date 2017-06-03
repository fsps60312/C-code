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
	bool operator<(const Observe &o)const{return a<o.a;}
};
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
	sort(OBSERVE.begin(),OBSERVE.end());
	cnt=0;
	int now=OBSERVE[0].b;
	for(int i=1;i<OBSERVE.size();i++)
	{
		const Observe &o=OBSERVE[i];
		if(o.a>now)
		{
			if(OBSERVE[i-1].a==now)ANS.push_back(now);
			cnt++;
			now=o.b;
		}
		else if(o.b<now)now=o.b;
	}
	if(OBSERVE[OBSERVE.size()-1].a==now)ANS.push_back(now);
	cnt++;
//	printf("b:cnt=%d\n",cnt);
	assert(cnt<=K);
	if(cnt==K)return;
	ANS.clear();
	for(int i=1;i<OBSERVE.size();i++)
	{
		const Observe &o=OBSERVE[i];
		if(o.a==o.b)ANS.push_back(o.a);
	}
	ANS.resize(unique(ANS.begin(),ANS.end())-ANS.begin());
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

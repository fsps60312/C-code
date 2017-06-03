#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
#include<cassert>
using namespace std;
typedef long long LL;
struct Sail
{
	int h,cnt;
	Sail(){}
	Sail(const int _h,const int _c):h(_h),cnt(_c){}
	bool operator<(const Sail &s)const{return h<s.h;} 
};
int N;
vector<Sail>SAIL;
struct Seg
{
	int s[400000];
	void Build(const int id,const int l,const int r)
	{
		s[id]=0;
		if(l==r)return;
		const int mid=(l+r)/2;
		Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	}
	void Add(const int id,const int l,const int r,const int bl,const int br)
	{
		if(l>br||r<bl)return;
		if(bl<=l&&r<=br){s[id]++;return;}
		const int mid=(l+r)/2;
		Add(id*2,l,mid,bl,br),Add(id*2+1,mid+1,r,bl,br);
	}
	void Output(const int id,const int l,const int r,LL *result)
	{
		if(l==r){result[l]=s[id];return;}
		s[id*2]+=s[id],s[id*2+1]+=s[id],s[id]=0;
		const int mid=(l+r)/2;
		Output(id*2,l,mid,result),Output(id*2+1,mid+1,r,result);
	}
}SEG;
LL ANS[100000];
void Erase(set<int>&s,int v){assert(s.find(v)!=s.end()),s.erase(v);}
void Insert(set<int>&s,int v){assert(s.find(v)==s.end()),s.insert(v);}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0,h,c;i<N;i++)
	{
		scanf("%d%d",&h,&c);
		SAIL.push_back(Sail(h,c));
	}
	sort(SAIL.begin(),SAIL.end());
	set<int>joint;
	SEG.Build(1,0,99999);
	for(const Sail &sail:SAIL)
	{
		auto upbound=joint.upper_bound(sail.h-sail.cnt),lowbound=joint.lower_bound(sail.h-sail.cnt);
		int l,r;
		r=(lowbound==joint.end()?sail.h:*lowbound);
		l=(upbound==joint.begin()?0:*(--upbound));
		int unstable=sail.cnt-(sail.h-r);
		assert(l+unstable<=r);
		printf("(%d,%d),(%d,%d)\n",l,l+unstable,r,sail.h);
		for(auto v:joint)printf(" %d",v);puts("");
		SEG.Add(1,0,99999,r,sail.h-1);
		SEG.Add(1,0,99999,l,l+unstable-1);
		if(l==r)Erase(joint,l);
		else
		{
			if(l!=0)Erase(joint,l);
			if(l+unstable!=0)Insert(joint,l+unstable);
			if(r!=sail.h)Erase(joint,r);
		}
	}
	SEG.Output(1,0,99999,ANS);
	LL ans=0LL;
	for(int i=0;i<=99999;i++)ans+=ANS[i]*(ANS[i]-1LL)/2LL;
	printf("%lld\n",ans);
	return 0;
}

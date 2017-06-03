#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Node
{
	Node *ch[2];
	int tag;
	LL sum;
	Node(const int _tag,const LL &l,const LL &r):ch{NULL,NULL},tag(_tag),sum((LL)tag*(r-l+1LL)){}
	void PutDown(const LL &l,const LL &mid,const LL &r)
	{
		if(tag==-1)return;
		assert(!ch[0]&&!ch[1]);
		ch[0]=new Node(tag,l,mid),ch[1]=new Node(tag,mid+1LL,r);
		tag=-1;
	}
	void Maintain()
	{
		assert(tag==-1&&ch[0]&&ch[1]);
		sum=(ch[0]->sum)+(ch[1]->sum);
	}
}*ROOT=NULL;
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;o=NULL;
}
void Modify(Node* &o,const LL &l,const LL &r,const LL &bl,const LL &br,const int v)
{
	assert(o);
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br){Delete(o);o=new Node(v,l,r);return;}
	if((o->tag)==v)return;
	const LL mid=(l+r)/2LL;
	o->PutDown(l,mid,r);
	Modify(o->ch[0],l,mid,bl,br,v),Modify(o->ch[1],mid+1LL,r,bl,br,v);
	o->Maintain();
}
LL Query(Node* &o,const LL &l,const LL &r,const LL &bl,const LL &br)
{
	assert(o);
	if(r<bl||br<l)return 0LL;
	if(bl<=l&&r<=br)return o->sum;
	if((o->tag)!=-1)return (LL)(o->tag)*(min(r,br)-max(l,bl)+1LL);
	const LL mid=(l+r)/2LL;
	return Query(o->ch[0],l,mid,bl,br)+Query(o->ch[1],mid+1LL,r,bl,br);
}
LL GetAnswer(Node* &o,const LL &l,const LL &r)
{
	assert(o);
	if(l==r)return r;
	const LL mid=(l+r)/2LL;
	assert((o->tag)==-1);
	if(o->ch[0]->sum)return GetAnswer(o->ch[0],l,mid);
	else if(o->ch[1]->sum)return GetAnswer(o->ch[1],mid+1LL,r);
	else assert(0);
}
int H;
LL L,R;
vector<pair<LL,LL> >SEG;
LL Solve()
{
	if((ROOT->sum)==0LL)return -2LL;
	else if((ROOT->sum)>1LL)return -1LL;
	for(const auto &p:SEG)if(Query(ROOT,L,R,p.first,p.second)==0LL)return -2LL;
	assert((ROOT->sum)==1LL);
	return GetAnswer(ROOT,L,R);
}
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;
	while(scanf("%d%d",&H,&querycount)==2)
	{
		Delete(ROOT);
		if(true)
		{
			int h=1;
			L=R=1LL;
			for(;h<H;h++,L=L*2LL,R=R*2LL+1LL);
			ROOT=new Node(1,L,R);
		}
		SEG.clear();
		for(int h,a;querycount--;)
		{
			static LL l,r;
			scanf("%d%I64d%I64d%d",&h,&l,&r,&a);
			for(;h<H;h++,l=l*2LL,r=r*2LL+1LL);
			if(a==0)
			{
				Modify(ROOT,L,R,l,r,0);
			}
			else if(a==1)
			{
				Modify(ROOT,L,R,L,l-1LL,0);
				Modify(ROOT,L,R,r+1LL,R,0);
				SEG.push_back(make_pair(l,r));
			}
			else assert(0);
		}
		const LL ans=Solve();
		if(ans==-1LL)puts("Data not sufficient!");
		else if(ans==-2LL)puts("Game cheated!");
		else printf("%I64d\n",ans);
	}
	return 0;
}

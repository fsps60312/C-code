#include<cstdio>
#include<cassert>
#include<algorithm>
#include<utility>
#include<vector>
#include<set>
using namespace std;
const int INF=2147483647,MAX_COORDINATE=1000000000;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Node
{
	Node *ch[2];
	int mn;
	Node(const int _mn):ch{NULL,NULL},mn(_mn){}
}*ROOT;
void PutDown(Node *o)
{
	for(int d=0;d<2;d++)
	{
		if(!o->ch[d])o->ch[d]=new Node(o->mn);
		getmin(o->ch[d]->mn,o->mn);
	}
}
void Modify(Node *o,const int l,const int r,const int bl,const int br,const int val)
{
	assert(o);
	if(r<bl||br<l||o->mn<=val)return;
	if(bl<=l&&r<=br){o->mn=val;return;}
	const int mid=(l+r)/2;
	PutDown(o);
	Modify(o->ch[0],l,mid,bl,br,val),Modify(o->ch[1],mid+1,r,bl,br,val);
}
void Query(Node *o,const int l,const int r,const int loc,int &ans)
{
	if(!o)return;
	getmin(ans,o->mn);
	assert(l<=loc&&loc<=r);
	const int mid=(l+r)/2;
	if(loc<=mid)Query(o->ch[0],l,mid,loc,ans);
	else Query(o->ch[1],mid+1,r,loc,ans);
}
struct Frog
{
	int id,x,tongue,eaten;
	Frog(){}
	Frog(const int _id,const int _x,const int _tongue):id(_id),x(_x),tongue(_tongue),eaten(0){}
};
void Modify(const Frog &f,int val){Modify(ROOT,0,MAX_COORDINATE,f.x,f.x+f.tongue,val);}
int Query(const int loc){int ans=INF;Query(ROOT,0,MAX_COORDINATE,loc,ans);return ans;}
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		vector<Frog>frogs;
		for(int i=0,x,t;i<N;i++)scanf("%d%d",&x,&t),frogs.push_back(Frog(i,x,t));
		sort(frogs.begin(),frogs.end(),[](const Frog &a,const Frog &b)->bool{return a.x<b.x;});
		ROOT=new Node(INF);
		for(int i=0;i<N;i++)Modify(frogs[i],i);
//		for(int i=0;i<=MAX_COORDINATE;i++)printf("%d ",Query(i));puts("");
		multiset<pair<int,int> >alive;
		for(int i=0,p,b;i<M;i++)
		{
			scanf("%d%d",&p,&b);
			int result=Query(p);
			if(result==INF)alive.insert(make_pair(p,b));
			else
			{
				Frog &f=frogs[result];
				f.tongue+=b;
				f.eaten++;
				for(auto it=alive.lower_bound(make_pair(f.x,-INF));it!=alive.end();it=alive.lower_bound(make_pair(f.x,-INF)))
				{
					if((it->first)>f.x+f.tongue)break;
					f.tongue+=it->second;
					f.eaten++;
					alive.erase(it);
				}
				Modify(f,result);
			}
		}
		sort(frogs.begin(),frogs.end(),[](const Frog &a,const Frog &b)->bool{return a.id<b.id;});
		for(int i=0;i<N;i++)printf("%d %d\n",frogs[i].eaten,frogs[i].tongue);
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
#include<set>
using namespace std;
unsigned int Rand()
{
	static unsigned int seed=20160318;
	seed*=0xdefaced,seed+=83739;
	return seed+=seed>>20;
}
struct Node
{
	Node *ch[2],*parent;
	bool flipped;
	int sz;
	unsigned int pri;
	Node():ch{NULL,NULL},parent(NULL),flipped(false),sz(1),pri(Rand()){}
	void Flip()
	{
		flipped^=true;
		swap(ch[0],ch[1]);
	}
	void PutDown()
	{
		if(!flipped)return;
		for(int d=0;d<2;d++)if(ch[d])ch[d]->Flip();
		flipped=false;
	}
	void Maintain()
	{
		sz=1;
		for(int d=0;d<2;d++)if(ch[d])sz+=ch[d]->sz,ch[d]->parent=this;
	}
};
void Discretize(int *s,const int n)
{
	vector<int>v;
	for(int i=0;i<n;i++)v.push_back(s[i]);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	for(int i=0;i<n;i++)s[i]=lower_bound(v.begin(),v.end(),s[i])-v.begin();
}
Node *Root(Node *o)
{
	while(o->parent)o=o->parent;
	return o;
}
Node *Leaf(Node *o,const int d)
{
	while(o->ch[d])o->PutDown(),o=o->ch[d];
	return o;
}
Node *Merge(Node *a,Node *b)
{
	if(a)a->parent=NULL;
	if(b)b->parent=NULL;
	if(!a||!b)return a?a:b;
	if(a->pri>b->pri)
	{
		a->PutDown();
		a->ch[1]=Merge(a->ch[1],b);
		a->Maintain();
		return a;
	}
	else
	{
		b->PutDown();
		b->ch[0]=Merge(a,b->ch[0]);
		b->Maintain();
		return b;
	}
}
int Sz(Node *o){return o?o->sz:0;}
void Split(Node *o,Node* &a,Node* &b,const int loc)
{
	if(!o){a=b=NULL;return;}
	o->parent=NULL;
	o->PutDown();
	if(loc<=Sz(o->ch[0]))
	{
		b=o;
		Split(o->ch[0],a,b->ch[0],loc);
		b->Maintain();
	}
	else
	{
		a=o;
		Split(o->ch[1],a->ch[1],b,loc-Sz(o->ch[0])-1);
		a->Maintain();
	}
}
void Connect(Node *a,Node *b)
{
	Node *ra=Root(a),*rb=Root(b);
	assert(ra!=rb);
	if(Leaf(ra,1)!=a)ra->Flip();
	if(Leaf(rb,0)!=b)rb->Flip();
	assert(Leaf(ra,1)==a&&Leaf(rb,0)==b);
	Merge(ra,rb);
}
int PutDownParents(Node *o)
{
	if(!o->parent)return 0;
	const int ans=PutDownParents(o->parent);
	o->parent->PutDown();
	if(o->parent->ch[0]==o)return ans;
	else return ans+Sz(o->parent->ch[0])+1;
}
int GetLoc(Node *o){return PutDownParents(o)+Sz(o->ch[0]);}
void Cut(Node *o,Node* &a,Node* &b)
{
	const int loc=GetLoc(o);
	Split(Root(o),a,b,loc+1);
	assert(Leaf(Root(a),1)==o);
}
int N,S[200000];
vector<pair<int,int> >OPES;
Node NODES[200000];
void Print(Node *o)
{
	if(!o)return;
	o->PutDown();
	Print(o->ch[0]);
	printf("%d ",o-NODES);
	Print(o->ch[1]);
}
Node *Root(const int o){return Root(&NODES[o]);}
void Connect(const int a,const int b){Connect(&NODES[a],&NODES[b]);}
void Cut(const int o,Node* &a,Node* &b){Cut(&NODES[o],a,b);}
int BuildCycles()
{
	for(int i=0;i<N;i++)NODES[i]=Node();
	for(int i=0;i<N;i++)if(Root(i)!=Root(S[i]))Connect(i,S[i]);
	set<Node*>roots;
	for(int i=0;i<N;i++)roots.insert(Root(i));
	return roots.size();
}
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		static int backup[200000];
		for(int i=0;i<N;i++)backup[i]=S[i];
		Discretize(S,N);
		int opecount;scanf("%d",&opecount);
		OPES.clear();
		for(int a,b;opecount--;)scanf("%d%d",&a,&b),OPES.push_back(make_pair(a,b));
		vector<pair<int,int> >ans;
		opecount=0;
		for(int chance=0,cyclecount=BuildCycles();;opecount++,chance++)
		{
			printf("opecount=%d\n",opecount);
			printf("S:");for(int i=0;i<N;i++)printf(" %d",S[i]);puts("");
			printf("cycle count=%d\n",cyclecount);
			for(int i=0;i<N;i++){Print(Root(i));puts("");}
			if(chance>=N-cyclecount)
			{
				int *trans=new int[N];
				for(int i=0;i<N;i++)trans[i]=i;
				for(int i=opecount-1;i>=0;i--)swap(trans[OPES[i].first],trans[OPES[i].second]);
				int *loc=new int[N];
				for(int i=0;i<N;i++)loc[S[i]]=i;
				int j=0;
				for(int i=0;i<N;i++)if(S[i]!=i)
				{
//					printf("(%d,%d)\n",OPES[j].first,OPES[j].second);
					swap(backup[OPES[j].first],backup[OPES[j].second]);
					swap(trans[OPES[j].first],trans[OPES[j].second]);
					j++;
//					printf("(%d,%d)\n",trans[i],trans[loc[i]]);
					swap(backup[trans[i]],backup[trans[loc[i]]]);
					ans.push_back(make_pair(trans[i],trans[loc[i]]));
					const int want=loc[i];
					swap(loc[S[i]],loc[i]);
					swap(S[i],S[want]);
				}
				if(j<opecount)swap(backup[OPES[j].first],backup[OPES[j].second]),ans.push_back(make_pair(0,0));
				for(int i=0;i<N;i++)printf("%d ",backup[i]);puts("");
				assert(is_sorted(S,S+N));
				assert(is_sorted(backup,backup+N));
				delete[]trans;
				delete[]loc;
				assert((int)ans.size()==chance);
//				if((int)ans.size()==chance-1)ans.push_back(make_pair(0,0));
				break;
			}
			assert(opecount<(int)OPES.size());
			const auto &p=OPES[opecount];
			if(p.first!=p.second)
			{
				if(Root(p.first)!=Root(p.second))
				{
					Node *a,*b,*c,*d;
					Cut(p.first,a,b);
					Merge(b,a);
					Cut(p.second,c,d);
					Merge(d,c);
					swap(S[p.first],S[p.second]);
					Connect(p.first,S[p.first]);
					cyclecount--;
				}
				else
				{
					int first=p.first,second=p.second;
					if(GetLoc(&NODES[first])>GetLoc(&NODES[second]))swap(first,second);
					Node *a,*b,*c;
					Cut(first,a,b);Cut(second,b,c);
					Merge(a,c);
					swap(S[first],S[second]);
					assert(Root(first)!=Root(second));
					cyclecount++;
				}
			}
		}
		printf("%d\n",(int)ans.size());
		for(const auto &p:ans)printf("%d %d\n",p.first,p.second);
	}
	return 0;
}

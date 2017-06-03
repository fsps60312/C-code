#include<cstdio>
#include<vector>
using namespace std;
int N,M;
struct Node
{
	Node *ch[2];
	int sz,v;
	bool empty;
	Node(const int &_v):v(_v),sz(1),empty(_v==0){ch[0]=ch[1]=NULL;}
}*ROOT=NULL;
inline int Sz(Node* &o){return o?o->sz:0;}
inline bool Empty(Node* &o){return o?o->empty:false;}
inline void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->empty=((o->v==0)||Empty(o->ch[0])||Empty(o->ch[1]));
}
inline void Rotate(Node* &o,const int &cu)
{
	static Node *u;u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
inline void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>2)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>2)Rotate(o,1);
}
void Remove(Node* &o)
{
	if(o->ch[0]&&o->ch[1])
	{
		static int cu;cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
		Rotate(o,cu);
		Remove(o->ch[cu^1]);
		Maintain(o),Rotate(o);
	}
	else
	{
		static Node *u;u=o;
		o=(o->ch[0]?o->ch[0]:o->ch[1]);
		delete u;
	}
}
bool RemoveEmpty(Node* &o)
{
	if(!Empty(o))return false;
	if(!RemoveEmpty(o->ch[0]))
	{
		if(o->v==0){Remove(o);return true;}
		RemoveEmpty(o->ch[1]);
	}
	Maintain(o);
	return true;
}
void BuildTree(Node* &o,const int &l,const int &r)
{
	o=new Node(0);
	if(l==r)return;
	int mid=(l+r)/2;
	if(l<mid)BuildTree(o->ch[0],l,mid-1);
	if(mid<r)BuildTree(o->ch[1],mid+1,r);
	Maintain(o),Rotate(o);
}
bool Insert(Node* &o,const int &loc,const int &v)
{
	if(!o){o=new Node(v);return false;}
	if(loc<=Sz(o->ch[0]))
	{
		static bool result;result=Insert(o->ch[0],loc,v);
		Maintain(o);
		if(!result)
		{
			if(o->v==0){Remove(o);result=true;}
			else result=RemoveEmpty(o->ch[1]);
		}
		Maintain(o),Rotate(o);
		return result;
	}
	else
	{
		static bool result;result=Insert(o->ch[1],loc-Sz(o->ch[0])-1,v);
		Maintain(o),Rotate(o);
		return result;
	}
}
vector<int>ANS;
void DfsTree(Node* &o)
{
	if(!o)return;
	DfsTree(o->ch[0]);
	ANS.push_back(o->v);
	DfsTree(o->ch[1]);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		ROOT=NULL;
		BuildTree(ROOT,1,M-1);
		for(int i=1,loc;i<=N;i++)
		{
			scanf("%d",&loc);
			loc--;
			Insert(ROOT,loc,i);
		}
		ANS.clear();ANS.reserve(Sz(ROOT));
		DfsTree(ROOT);
		int ans=0;
		for(int i=0;i<ANS.size();i++)if(ANS[i])ans=i+1;
		printf("%d\n",ans);
		for(int i=0;i<ans;i++)
		{
			if(i)printf(" ");
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}

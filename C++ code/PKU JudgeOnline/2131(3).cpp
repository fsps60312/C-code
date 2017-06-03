#include<cstdio>
//#include<cassert>
#include<vector>
using namespace std;
void assert(const bool &valid){if(valid)return;int i=0,j=0;i/=j;}
int N,M;
struct Node
{
	Node *ch[2];
	int sz,v;
	bool empty;
	Node(const int &_v):v(_v),sz(1),empty(_v==0){ch[0]=ch[1]=NULL;}
}*ROOT=NULL;
int Sz(Node* &o){return o?o->sz:0;}
bool Empty(Node* &o){return o?o->empty:false;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->empty=((o->v==0)||Empty(o->ch[0])||Empty(o->ch[1]));
}
void Rotate(Node* &o,const int &cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
}
void Remove(Node* &o)
{
	if(o->ch[0]&&o->ch[1])
	{
		int cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
		Rotate(o,cu);
		Remove(o->ch[cu^1]);
		Maintain(o),Rotate(o);
	}
	else
	{
		Node *u=o;
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
		assert(RemoveEmpty(o->ch[1]));
	}
	Maintain(o),Rotate(o);
	return true;
}
void BuildTree(Node* &o,int l,int r)
{
	o=new Node(0);
	if(l==r)return;
	int mid=(l+r)/2;
	if(l<mid)BuildTree(o->ch[0],l,mid-1);
	if(mid<r)BuildTree(o->ch[1],mid+1,r);
	Maintain(o);
}
bool Insert(Node* &o,const int &loc,const int &v)
{
	if(!o){o=new Node(v);return false;}
	if(loc<=Sz(o->ch[0]))
	{
		bool result=Insert(o->ch[0],loc,v);
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
		bool result=Insert(o->ch[1],loc-Sz(o->ch[0])-1,v);
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
//void Print(Node* &o)
//{
//	if(!o)return;
//	Print(o->ch[0]);
//	printf(" %d",o->v);
//	Print(o->ch[1]);
//}
int main()
{
//	assert(0);
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%d",&N,&M)==2)
	{
		ROOT=NULL;
		BuildTree(ROOT,1,N+M);
		for(int i=1,loc;i<=N;i++)
		{
			scanf("%d",&loc);
			loc--;
//			Print(ROOT);puts("");
			assert(Insert(ROOT,loc,i));
		}
		ANS.clear();
		DfsTree(ROOT);
		int ans=0;
		for(int i=0;i<ANS.size();i++)if(ANS[i])ans=i+1;
		assert(ans>0);
		printf("%d\n",ans);
		for(int i=0;i<ans;i++)
		{
			if(i)printf(" ");
			printf("%d",ANS[i]);
		}
		puts("");
		break;
	}
	return 0;
}

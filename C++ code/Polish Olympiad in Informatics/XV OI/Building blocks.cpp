#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
struct Node
{
	Node *ch[2];
	int val,sz;
	Node(const int _val):val(_val),sz(1){ch[0]=ch[1]=NULL;}
};
inline int Sz(Node* &o){return o?o->sz:0;}
inline void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
}
inline void Rotate(Node* &o,const int cu)
{
	Node *u=o;
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
void Insert(Node* &o,const int val)
{
	if(!o){o=new Node(val);return;}
	Insert(o->ch[val<o->val?0:1],val);
	Maintain(o);
	Rotate(o);
}
void Delete(Node* &o)
{
	assert(o);
	if(o->ch[0]&&o->ch[1])
	{
		const int cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
		Rotate(o,cu);
		Delete(o->ch[cu^1]);
		Maintain(o);
	}
	else o=o->ch[o->ch[0]?0:1];
}
void Erase(Node* &o,const int val)
{
	assert(o);
	if(o->val==val){Delete(o);return;}
	Erase(o->ch[val<o->val?0:1],val);
	Maintain(o);
	Rotate(o);
}
int Query(Node* &o,const int loc)
{
	assert(o);
	if(loc<Sz(o->ch[0]))return Query(o->ch[0],loc);
	else if(loc==Sz(o->ch[0]))return o->val;
	else return Query(o->ch[1],loc-Sz(o->ch[0])-1);
}
struct QueryType
{
	int id,v;
	QueryType(){}
	QueryType(const int _id,const int _v):id(_id),v(_v){}
};
bool operator<(const QueryType &a,const QueryType &b){return a.v<b.v;}
int N,K,H[100000];
vector<QueryType>QUERY;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		QUERY.clear();
		if(true)
		{
			Node *root=NULL;
			for(int i=0;i<N;i++)
			{
				Insert(root,H[i]);
				if(i-K>=0)Erase(root,H[i-K]);
				if(i>=K-1)QUERY.push_back(QueryType(i,Query(root,Sz(root)/2)));
			}
		}
		sort(QUERY.begin(),QUERY.end());
		multimap<int,int>sot;
		for(int i=0;i<N;i++)
	}
	return 0;
}

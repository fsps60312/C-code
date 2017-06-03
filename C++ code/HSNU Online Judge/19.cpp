#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
struct Node
{
	Node *ch[2];
	int sz,v;
	Node(){}
	Node(int v):v(v),sz(1),ch{NULL,NULL}{}
}*LOC[1000001];
int M,N,K,S[1000000];
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,int cu)
{
	Node* u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	int a=Sz(o->ch[0]),b=Sz(o->ch[1]);
	if(a>b)Rotate(o,0);
	else if(a<b)Rotate(o,1);
}
void Insert(Node* &o,const int &v)
{
	if(!o){o=new Node(v);return;}
	Insert(o->ch[v<o->v?0:1],v);
	Maintain(o);
	Rotate(o);
}
void Query(Node* &o,const int &mn,int &ans)
{
	if(!o)return;
	if(mn<=o->v)
	{
		ans=min(ans,o->v);
		Query(o->ch[0],mn,ans);
	}
	else Query(o->ch[1],mn,ans);
}
int main()
{
	while(scanf("%d",&M)==1)
	{
		set<int>all;
		for(int i=0;i<M;i++)
		{
			scanf("%d",&S[i]);
			all.insert(S[i]);
			LOC[S[i]]=NULL;
		}
		for(int i=0;i<M;i++)Insert(LOC[S[i]],i);
		scanf("%d",&N);
		while(N--)
		{
			scanf("%d",&K);
			int idx=0;
			bool found=true;
			while(K--)
			{
				static int v,ans;
				scanf("%d",&v);
				if(all.find(v)==all.end())found=false;
				if(found)Query(LOC[v],idx,ans=INF);
				if(ans==INF)found=false;
				else idx=ans+1;
			}
			puts(found?"TAK":"NIE");
		}
	}
	return 0;
}

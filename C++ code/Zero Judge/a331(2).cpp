#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
struct Node
{
	Node *ch[2];
	int sz,v;
	Node(const int _v):v(_v),sz(1),ch{NULL,NULL}{}
};
int Sz(Node* &o){return o?o->sz:0;}
void Maintain(Node* &o){o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);}
void Rotate(Node* &o,const int cu)
{
	Node *u=o;
	o=o->ch[cu];
	u->ch[cu]=o->ch[cu^1];
	o->ch[cu^1]=u;
	Maintain(u),Maintain(o);
}
void Rotate(Node* &o)
{
	if(Sz(o->ch[0])-Sz(o->ch[1])>1)Rotate(o,0);
	else if(Sz(o->ch[1])-Sz(o->ch[0])>1)Rotate(o,1);
}
void Insert(Node* &o,const int v)
{
	if(!o){o=new Node(v);return;}
	Insert(o->ch[v<o->v?0:1],v);
	Maintain(o);
	Rotate(o);
}
void QueryRank(Node* &o,const int v,int &ans)
{
	if(!o)return;
	if(v<=o->v)QueryRank(o->ch[0],v,ans);
	else ans+=Sz(o->ch[0])+1,QueryRank(o->ch[1],v,ans);
}
Node *ST[400000];
int S[100000];
//void Check(Node* &o)
//{
//	if(!o)return;
//	assert(o->sz==Sz(o->ch[0])+1+Sz(o->ch[1]));
//	Check(o->ch[0]),Check(o->ch[1]);
//}
void Build(const int id,const int l,const int r)
{
	ST[id]=NULL;
	for(int i=l;i<=r;i++)Insert(ST[id],S[i]);
//	Check(ST[id]);
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void QueryRank(const int id,const int l,const int r,const int bl,const int br,const int v,int &ans)
{
//	printf("id=%d\n",id);
	if(r<bl||br<l)return;
	if(bl<=l&&r<=br){QueryRank(ST[id],v,ans);return;}
	const int mid=(l+r)/2;
	QueryRank(id*2,l,mid,bl,br,v,ans),QueryRank(id*2+1,mid+1,r,bl,br,v,ans);
}
int N,M;
vector<int>VALUE;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		VALUE.clear();
		for(int i=0;i<N;i++)scanf("%d",&S[i]),VALUE.push_back(S[i]);
		sort(VALUE.begin(),VALUE.end());
		VALUE.resize(unique(VALUE.begin(),VALUE.end())-VALUE.begin());
		Build(1,0,N-1);
		while(M--)
		{
			static int i,j,k;scanf("%d%d%d",&i,&j,&k);
			i--,j--;
			int l=0,r=(int)VALUE.size();
			while(l<r)
			{
				const int mid=(l+r)/2;
//				printf("VALUD[%d]=%d\n",mid,VALUE[mid]);
				int rank=1;
				QueryRank(1,0,N-1,i,j,VALUE[mid],rank);
//				printf("%d in (%d,%d) rank %d\n",VALUE[mid],i,j,rank);
				if(rank<=k)l=mid+1;
				else r=mid;
			}
			printf("%d\n",VALUE[r-1]);
		}
	}
	return 0;
}

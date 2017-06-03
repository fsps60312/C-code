#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct QueryType{int type,l,r,v;};
struct Node
{
	Node *ch[2];
	int v,cnt,sz,sum;
	Node(const int _v):ch{NULL,NULL},v(_v),cnt(1),sz(1),sum(1){}
};
void Delete(Node* &o)
{
	if(!o)return;
	Delete(o->ch[0]),Delete(o->ch[1]);
	delete o;o=NULL;
}
int Sz(Node* &o){return o?o->sz:0;}
int Sum(Node* &o){return o?o->sum:0;}
void Maintain(Node* &o)
{
	o->sz=Sz(o->ch[0])+1+Sz(o->ch[1]);
	o->sum=Sum(o->ch[0])+(o->cnt)+Sum(o->ch[1]);
}
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
	if(Sz(o->ch[0])>Sz(o->ch[1]))Rotate(o,0);
	else if(Sz(o->ch[1])>Sz(o->ch[0]))Rotate(o,1);
}
void Insert(Node* &o,const int v)
{
	if(!o){o=new Node(v);return;}
	if((o->v)==v){o->cnt++;return;}
	Insert(o->ch[v<(o->v)?0:1],v);
	Maintain(o),Rotate(o);
}
void Erase(Node* &o)
{
	if(!o->ch[0]||!o->ch[1])
	{
		Node *u=o;
		o=o->ch[o->ch[0]?0:1];
		delete u;return;
	}
	const int cu=(Sz(o->ch[0])>Sz(o->ch[1])?0:1);
	Rotate(o,cu);
	Erase(o->ch[cu^1]);
	Maintain(o);
}
void Erase(Node* &o,const int v)
{
	assert(o);
	if((o->v)==v)
	{
		if(!--(o->cnt))Erase(o);
		if(o)Maintain(o);
		return;
	}
	Erase(o->ch[v<(o->v)?0:1],v);
	Maintain(o);
}
int N,S[50000];
Node *ST[200000];
void Build(const int id,const int l,const int r)
{
	Delete(ST[id]);
	for(int i=l;i<=r;i++)Insert(ST[id],S[i]);
	assert(Sum(ST[id])==r-l+1);
	if(l==r)return;
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
}
void Modify(const int id,const int l,const int r,const int loc,const int v)
{
	Erase(ST[id],S[loc]),Insert(ST[id],v);
	assert(Sum(ST[id])==r-l+1);
	if(l==r)return;
	const int mid=(l+r)/2;
	if(loc<=mid)Modify(id*2,l,mid,loc,v);
	else Modify(id*2+1,mid+1,r,loc,v);
}
int QueryRank(Node* &o,const int v)
{
	if(!o)return 0;
	if((o->v)<=v)return Sum(o->ch[0])+(o->cnt)+QueryRank(o->ch[1],v);
	else return QueryRank(o->ch[0],v);
}
int QueryRank(const int id,const int l,const int r,const int bl,const int br,const int v)
{
	if(r<bl||br<l)return 0;
	if(bl<=l&&r<=br)
	{
//		printf("(%d,%d,%d,%d,%d)=%d(sz=%d,cnt=%d,sum=%d)\n",l,r,bl,br,v,QueryRank(ST[id],v),Sz(ST[id]),ST[id]->cnt,ST[id]->sum);
		return QueryRank(ST[id],v);
	}
	const int mid=(l+r)/2;
	return QueryRank(id*2,l,mid,bl,br,v)+QueryRank(id*2+1,mid+1,r,bl,br,v);
}
vector<QueryType>QUERY;
//void Print(Node* &o)
//{
//	if(!o)return;
//	Print(o->ch[0]);
//	printf("{%d,%d}",o->v,o->cnt);
//	Print(o->ch[1]);
//}
//void Print(const int id,const int l,const int r)
//{
//	printf("(%d,%d):",l,r);Print(ST[id]);puts("");
//	if(l==r)return;
//	const int mid=(l+r)/2;
//	Print(id*2,l,mid),Print(id*2+1,mid+1,r);
//}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<200000;i++)ST[i]=NULL;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int querycount;
		scanf("%d%d",&N,&querycount);
		vector<int>vals;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),vals.push_back(S[i]);
		Build(1,0,N-1);
		QUERY.clear();
		for(QueryType q;querycount--;)
		{
			scanf("%d",&q.type);
			switch(q.type)
			{
				case 1:scanf("%d%d%d",&q.l,&q.r,&q.v),q.l--,q.r--;break;
				case 2:scanf("%d%d",&q.l,&q.v),q.l--;vals.push_back(q.v);break;
				case 3:scanf("%d%d",&q.l,&q.v),q.l--;break;
				default:assert(0);break;
			}
			QUERY.push_back(q);
		}
		sort(vals.begin(),vals.end()),vals.resize(unique(vals.begin(),vals.end())-vals.begin());
		for(const QueryType &q:QUERY)
		{
//			printf("%d %d %d %d\n",q.type,q.l,q.r,q.v);
			switch(q.type)
			{
				case 1:
				{
					int l=0,r=vals.size();
					while(l<r)
					{
						const int mid=(l+r)/2;
						const int result=QueryRank(1,0,N-1,q.l,q.r,vals[mid]);
//						printf("(%d,%.d,%d):val=%d,rank=%d\n",q.l,q.r,q.v,vals[mid],result);
						if(result>=q.v)r=mid;
						else l=mid+1;
					}
					assert(r<(int)vals.size());
					printf("%d\n",vals[r]);
				}break;
				case 2:Modify(1,0,N-1,q.l,q.v);/*printf("Modify(%d,%d)\n",q.l,q.v),*/S[q.l]=q.v;break;
				case 3:puts("7122");break;
				default:assert(0);break;
			}
//			Print(1,0,N-1);
		}
	}
	return 0;
}

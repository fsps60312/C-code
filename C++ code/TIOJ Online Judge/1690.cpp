#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(min(_a,_b)),b(max(_a,_b)){}
	bool operator<(const Edge &e)const{return a!=e.a?a<e.a:b<e.b;}
};
vector<Edge>EDGE;
struct Node
{
	Node *left,*right,*up,*down;
	const int r,c;
	Node(const int _r,const int _c):left(this),right(this),up(this),down(this),r(_r),c(_c){}
}*COL[1000],*ROW[10000],*ORIGIN=new Node(-1,-1);
void InsertH(Node *l,Node *o,Node *r){l->right=o,o->right=r,r->left=o,o->left=l;}
void InsertV(Node *u,Node *o,Node *d){u->down=o,o->down=d,d->up=o,o->up=u;}
int CNT[1000];
void AddNode(const int r,const int c)
{
	Node *o=new Node(r,c);
	InsertH(ROW[r]->left,o,ROW[r]),InsertV(COL[c]->up,o,COL[c]);
	CNT[c]++;
}
int N,M;
bool ConnectV(Node *o)
{
	bool connect_up=(o->up->down==o),connect_down=(o->down->up==o);
	assert(connect_up==connect_down);
	return connect_up;
}
void RemoveRow(const int r)
{
	Node *row=ROW[r];
	assert(ConnectV(row));
	row->up->down=row->down,row->down->up=row->up;
	for(Node *cur=row->right;cur!=row;cur=cur->right)assert(ConnectV(cur)),cur->up->down=cur->down,cur->down->up=cur->up;
}
void SelectRow(const int r)
{
	Node *row=ROW[r];
	assert(ConnectV(row));
	for(Node *cur1=row->right;cur1!=row;cur1=cur1->right)
	{
		assert(ConnectV(cur1));
		for(Node *cur2=cur1->down;cur2!=cur1;cur2=cur2->down)if(cur2->r!=-1)RemoveRow(cur2->r);
		assert(cur1->down==cur1);
		cur1->right->left=cur1->left,cur1->left->right=cur1->right;
	}
	assert(row->right==row);
	assert(0);
//	row->up->down=row->down,row->down->up=row->up;
}
void RestoreRow(const int r)
{
	Node *row=ROW[r];
	if(ConnectV(row))return;
	row->up->down=row->down->up=row;
	for(Node *cur=row->right;cur!=row;cur=cur->right)assert(!ConnectV(cur)),cur->up->down=cur->down->up=cur;
}
void UnselectRow(const int r)
{
	Node *row=ROW[r];
	assert(!ConnectV(row));
	RestoreRow(r);
	for(Node *cur1=row->left;cur1!=row;cur1=cur1->left)
	{
		assert(ConnectV(cur1));
		for(Node *cur2=cur1->up;cur2!=cur1;cur2=cur2->up)if(cur2->r!=-1)RestoreRow(cur2->r);
	}
}
bool Dance(vector<int>&ans)
{
	if(ORIGIN->down==ORIGIN||ORIGIN->right==ORIGIN)return true;
	Node *col=ORIGIN;
	for(Node *cur=ORIGIN->right;cur!=ORIGIN;cur=cur->right)
	{
		if(CNT[cur->c]==0)return false;
		if(col==ORIGIN||CNT[cur->c]<CNT[col->c])col=cur;
	}
	assert(col!=ORIGIN);
	for(Node *row=col->down;row!=col;row=row->down)
	{
		ans.push_back(row->r);
		SelectRow(row->r);
		if(Dance(ans))return true;
		UnselectRow(row->r);
		ans.pop_back();
	}
	assert(0);
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<1000;i++)COL[i]=NULL;
	for(int i=0;i<10000;i++)ROW[i]=NULL;
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)if(COL[i])delete COL[i];
		for(int i=0;i<M;i++)if(ROW[i])delete ROW[i];
		delete ORIGIN;ORIGIN=new Node(-1,-1);
		for(int i=0;i<N;i++)COL[i]=new Node(-1,i),InsertH(ORIGIN->left,COL[i],ORIGIN),CNT[i]=0;
		for(int i=0;i<M;i++)ROW[i]=new Node(i,-1),InsertV(ORIGIN->up,ROW[i],ORIGIN);
		EDGE.clear();
		for(int i=0,a,b;i<M;i++)scanf("%d%d",&a,&b),EDGE.push_back(Edge(--a,--b));
		sort(EDGE.begin(),EDGE.end());
		for(int i=0;i<M;i++)
		{
			const Edge &e=EDGE[i];
			AddNode(i,e.a),AddNode(i,e.b);
		}
		vector<int>ans;
		if(Dance(ans))
		{
			puts("YES");
			sort(ans.begin(),ans.end());
			for(const int ei:ans)printf("%d %d\n",EDGE[ei].a,EDGE[ei].b);
		}
		else puts("NO");
	}
	return 0;
}

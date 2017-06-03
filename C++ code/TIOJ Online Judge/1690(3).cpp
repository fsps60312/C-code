#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#define debug(x,...) //printf(x,##__VA_ARGS__)
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
bool IsConnectedV(Node *o)
{
	assert((o->up->down==o)==(o->down->up==o));
	return (o->up->down==o);
}
void DisconnectV(Node *o){debug("unlinkV(%d,%d)\n",o->r,o->c);assert(IsConnectedV(o));o->up->down=o->down,o->down->up=o->up;CNT[o->c]--;assert(!IsConnectedV(o));}
void ConnectV(Node *o){debug("  linkV(%d,%d)\n",o->r,o->c);assert(!IsConnectedV(o));o->up->down=o->down->up=o;CNT[o->c]++;assert(IsConnectedV(o));}
void RemoveRow(const int r)
{
	debug("remove  row%d\n",r);
	Node *row=ROW[r],*cur=row;
	do{DisconnectV(cur),cur=cur->right;}while(cur!=row);
}
void RestoreRow(const int r)
{
	debug("restore row%d\n",r);
	Node *row=ROW[r],*cur=row;
	do{ConnectV(cur),cur=cur->right;}while(cur!=row);
}
bool IsConnectedH(Node *o)
{
	assert((o->left->right==o)==(o->right->left==o));
	return (o->left->right==o);
}
void DisconnectH(Node *o){debug("unlinkH(%d,%d)\n",o->r,o->c);assert(IsConnectedH(o));o->left->right=o->right,o->right->left=o->left;assert(!IsConnectedH(o));}
void ConnectH(Node *o){debug("  linkH(%d,%d)\n",o->r,o->c);assert(!IsConnectedH(o));o->left->right=o->right->left=o;assert(IsConnectedH(o));}
void RemoveCol(const int c){debug("remove  col%d\n",c);DisconnectH(COL[c]);}//為避免資訊遺失，只移除表頭 
void RestoreCol(const int c){debug("restore col%d\n",c);ConnectH(COL[c]);}//為避免資訊遺失，只移除表頭
void SelectRow(const int r)
{
	debug("  select %d\n",r);
	Node *row=ROW[r];
	assert(IsConnectedV(row));
	for(Node *cur1=row->right;cur1!=row;cur1=cur1->right)
	{
		assert(IsConnectedV(cur1));
		for(Node *cur2=cur1->down;cur2!=cur1;cur2=cur2->down)if(cur2->r!=-1)RemoveRow(cur2->r),ConnectV(cur2);//為避免資訊遺失，cur2要接回來 
	}
	for(Node *cur1=row->right;cur1!=row;cur1=cur1->right)RemoveCol(cur1->c);
	RemoveRow(r);
}
void UnselectRow(const int r)
{
	debug("unselect %d\n",r);
	RestoreRow(r);
	Node *row=ROW[r];
	assert(IsConnectedV(row));
	for(Node *cur1=row->left;cur1!=row;cur1=cur1->left)RestoreCol(cur1->c);
	for(Node *cur1=row->left;cur1!=row;cur1=cur1->left)//刪除時往右，反操作要往左 
	{
		assert(IsConnectedV(cur1));
		for(Node *cur2=cur1->up;cur2!=cur1;cur2=cur2->up)if(cur2->r!=-1)DisconnectV(cur2),RestoreRow(cur2->r);//反向操作，刪除時往下，反操作要往上  
	}
}
int Dance(vector<int>&now,vector<int>&ans)
{
	if(ORIGIN->right==ORIGIN)
	{
		if(ORIGIN->down==ORIGIN){ans=now;return 1;}
		else{return 2;}
	}
	Node *col=ORIGIN;
	for(Node *cur=ORIGIN->right;cur!=ORIGIN;cur=cur->right)
	{
		if(CNT[cur->c]==0)return 0;
		if(col==ORIGIN||CNT[cur->c]<CNT[col->c])col=cur;
	}
	assert(col!=ORIGIN);
	int solution_count=0;
	for(Node *row=col->down;row!=col&&solution_count<=1;row=row->down)
	{
		now.push_back(row->r);
		SelectRow(row->r);
		solution_count+=Dance(now,ans);
		UnselectRow(row->r);
		now.pop_back();
	}
	return solution_count;
}
int main()
{
//	freopen("in.txt","r",stdin);
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
		vector<int>now,ans;
		const int result=Dance(now,ans);//全部主要計算都在這一行 
		//確認一下舞蹈鏈有沒有受損 
		for(int i=0;i<N;i++)assert(IsConnectedH(COL[i]));
		for(int i=0;i<M;i++)
		{
			assert(IsConnectedV(ROW[i]));
			int j=1;
			for(Node *cur=ROW[i]->right;cur!=ROW[i];cur=cur->right,j++)
			{
				assert(IsConnectedV(cur));
				if(j==1)assert(cur->c==EDGE[i].a);
				else if(j==2)assert(cur->c==EDGE[i].b);
				else assert(0);
			}
		}
		//損害確認通過 
		if(result==1)
		{
			puts("YES");
			sort(ans.begin(),ans.end());
			for(const int ei:ans)printf("%d %d\n",EDGE[ei].a+1,EDGE[ei].b+1);
		}
		else puts("NO");
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<algorithm>
#define At(a,i,j) a[(i)*C+(j)]
using namespace std;
const int INF=2147483647;
bool getmin(int &a,const int b){if(b<a){a=b;return true;}return false;}
int R,C,H[5000][199],V[4999][200];
struct Node
{
	Node *ch[2];
	int *mn;
	Node(int *_mn):ch{NULL,NULL},mn(_mn){}
}*ROOT=NULL;
int *Merge(const int *a,const int *b)
{
	int *ans=new int[C*C];
	static int lpre[200],rpre[200];
	for(int i=0;i<C;i++)
	{
		int &v=At(ans,i,i)=INF;
		for(int j=0;j<C;j++)if(getmin(v,At(a,i,j)+At(b,j,i)))lpre[i]=rpre[i]=j;
	}
	for(int gap=1;gap<C;gap++)
	{
		for(int i=0;i+gap<C;i++)
		{
			int &v=At(ans,i+gap,i)=INF;
			for(int j=lpre[i];j<=lpre[i+1];j++)if(getmin(v,At(a,i+gap,j)+At(a,j,i)))lpre[i]=j;
		}
		for(int i=0;i+gap<C;i++)
		{
			int &v=At(ans,i,i+gap)=INF;
			for(int j=rpre[i];j<=rpre[i+1];j++)if(getmin(v,At(a,i,j)+At(b,j,i+gap)))rpre[i]=j;
		}
	}
	return ans;
}
int SUM[2][201];
inline int GetSum(const int d,const int a,const int b){return SUM[d][max(a,b)+1]-SUM[d][min(a,b)];}
int *Generate(const int r)
{
	for(int c=0;c<C;c++)SUM[0][c+1]=SUM[0][c]+H[r][c],SUM[1][c+1]=SUM[r+1][c]+H[r+1][c];
	int *ans=new int[C*C];
	static int lpre[200],rpre[200];
	for(int i=0;i<C;i++)
	{
		int &v=At(ans,i,i)=INF;
		for(int j=0;j<C;j++)if(getmin(v,GetSum(0,i,j)+V[r][j]+GetSum(1,j,i)))lpre[i]=rpre[i]=j;
	}
	for(int gap=1;gap<C;gap++)
	{
		for(int i=0;i+gap<C;i++)
		{
			int &v=At(ans,i+gap,i)=INF;
			for(int j=lpre[i];j<=lpre[i+1];j++)if(getmin(v,GetSum(0,i+gap,j)+V[r][j]+GetSum(1,j,i)))lpre[i]=j;
		}
		for(int i=0;i+gap<C;i++)
		{
			int &v=At(ans,i,i+gap)=INF;
			for(int j=rpre[i];j<=rpre[i+1];j++)if(getmin(v,GetSum(0,i,j)+V[r][j]+GetSum(1,j,i+gap)))rpre[i]=j;
		}
	}
	return ans;
}
int *Generate(const int r1,const int r2)
{
	assert(r1<r2);
	int *ans=Generate(r1);
	for(int r=r1+1;r<r2;r++)
	{
		int *nxt=Generate(r);
		int *ta=Merge(ans,nxt);
		delete ans;delete nxt;
		ans=ta;
	}
	return ans;
}
void Maintain(Node* &o){delete o->mn;o->mn=Merge(o->ch[0]->mn,o->ch[1]->mn);}
Node *Build(const int l,const int r)
{
	if(l==r)return new Node(Generate(l,r+1));
	const int mid=(l+r)/2;
	Node *ans=new Node(new int[0]);
	ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	Maintain(ans);
}
void Modify(Node* &o,const int l,const int r,const int loc)
{
	if(l==r){delete o->mn;o->mn=Generate(l,r+1);return;}
	const int mid=(l+r)/2;
	if(loc<=mid)Modify(o->ch[0],l,mid,loc);
	else Modify(o->ch[1],mid+1,r,loc);
	Maintain(o);
}
int *Query(Node* &o,const int l,const int r,const int bl,const int br)
{
	
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&R,&C);
	for(int i=0;i<R;i++)for(int j=0;j<C-1;j++)scanf("%d",&H[i][j]);
	for(int i=0;i<R-1;i++)for(int j=0;j<C;j++)scanf("%d",&V[i][j]);
	ROOT=Build(0,R-2);
	int eventcount;scanf("%d",&eventcount);
	while(eventcount--)
	{
		scanf("%d",&type);
		if(type==1)
		{
			int p,q,w;scanf("%d%d%d",&p,&q,&w);
			H[p][q]=w;
			if(p)Modify(ROOT,0,R-2,p-1);
			if(p+1<N)Modify(ROOT,0,R-2,p);
		}
		else if(type==2)
		{
			int p,q,w;scanf("%d%d%d",&p,&q,&w);
			V[p][q]=w;
			Modify(ROOT,0,R-2,p);
		}
		else if(type==3)
		{
			int v1,v2;scanf("%d%d",&v1,&v2);
		}
		else assert(0);
	}
	return 0;
}

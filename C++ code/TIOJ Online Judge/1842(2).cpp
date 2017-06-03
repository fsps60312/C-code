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
int *Merge(const int r,const int *a,const int *b)
{
	int *ans=new int[C*C];
	static int lpre[200],rpre[200];
	for(int i=0;i<C;i++)
	{
		int &v=At(ans,i,i)=INF;
		for(int j=0;j<C;j++)if(getmin(v,At(a,i,j)+V[r][j]+At(b,j,i)))lpre[i]=rpre[i]=j;
	}
	for(int gap=1;gap<C;gap++)
	{
		for(int i=0;i+gap<C;i++)
		{
			int &v=At(ans,i+gap,i)=INF;
			for(int j=lpre[i];j<=lpre[i+1];j++)if(getmin(v,At(a,i+gap,j)+V[r][j]+At(b,j,i)))lpre[i]=j;
		}
		for(int i=0;i+gap<C;i++)
		{
			int &v=At(ans,i,i+gap)=INF;
			for(int j=rpre[i];j<=rpre[i+1];j++)if(getmin(v,At(a,i,j)+V[r][j]+At(b,j,i+gap)))rpre[i]=j;
		}
	}
	return ans;
}
int *Generate(const int r)
{
	static int sum[200];
	for(int i=1;i<C;i++)sum[i]=sum[i-1]+H[r][i-1];
	int *ans=new int[C*C];
	for(int i=0;i<C;i++)
	{
		for(int j=0;j<=i;j++)At(ans,i,j)=sum[i]-sum[j];
		for(int j=i+1;j<C;j++)At(ans,i,j)=sum[j]-sum[i];
	}
	return ans;
}
int *Generate(const int r1,const int r2)
{
	assert(r1<=r2);
	int *ans=Generate(r1);
	for(int r=r1+1;r<=r2;r++)
	{
		int *nxt=Generate(r);
		int *ta=Merge(r-1,ans,nxt);
		delete ans;delete nxt;
		ans=ta;
	}
	return ans;
}
void Maintain(const int r,Node* &o){delete o->mn;o->mn=Merge(r,o->ch[0]->mn,o->ch[1]->mn);}
Node *Build(const int l,const int r)
{
	if(r-l<=10)return new Node(Generate(l,r));
	const int mid=(l+r)/2;
	Node *ans=new Node(new int[0]);
	ans->ch[0]=Build(l,mid),ans->ch[1]=Build(mid+1,r);
	Maintain(mid,ans);
	return ans;
}
void Modify(Node* &o,const int l,const int r,const int bl,const int br)
{
	if(r-l<=10){delete o->mn;o->mn=Generate(l,r);return;}
	const int mid=(l+r)/2;
	if(mid>=bl)Modify(o->ch[0],l,mid,bl,br);
	if(mid+1<=br)Modify(o->ch[1],mid+1,r,bl,br);
	Maintain(mid,o);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d",&R,&C);
	for(int i=0;i<R;i++)for(int j=0;j<C-1;j++)scanf("%d",&H[i][j]);
	for(int i=0;i<R-1;i++)for(int j=0;j<C;j++)scanf("%d",&V[i][j]);
	ROOT=Build(0,R-1);
	int eventcount;scanf("%d",&eventcount);
	for(int type;eventcount--;)
	{
		scanf("%d",&type);
		if(type==1)
		{
			int p,q,w;scanf("%d%d%d",&p,&q,&w);
			H[p][q]=w;
			Modify(ROOT,0,R-1,p,p);
		}
		else if(type==2)
		{
			int p,q,w;scanf("%d%d%d",&p,&q,&w);
			V[p][q]=w;
			Modify(ROOT,0,R-1,p,p+1);
		}
		else if(type==3)
		{
			int v1,v2;scanf("%d%d",&v1,&v2);
			printf("%d\n",At(ROOT->mn,v1,v2));
		}
		else assert(0);
	}
	return 0;
}

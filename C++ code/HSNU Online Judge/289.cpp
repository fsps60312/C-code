#include<cstdio>
#include<cstdlib>
int R,C,H_SUM[5000][100],H[5000][100],V_SUM[5000][100],V[5000][100];
void getmin(int &a,int b){if(b<a)a=b;}
int abs(int a){return a>=0?a:-a;}
int get_dis_H(int r,int c1,int c2)
{
	return abs(H_SUM[r][c1]-H_SUM[r][c2]);
}
int get_dis_V(int c,int r1,int r2)
{
	return abs(V_SUM[r1][c]-V_SUM[r2][c]);
}
void get_rowdis(int r,int ans[100][100])
{
	for(int c1=0;c1<C;c1++)
	{
		for(int c2=0;c2<C;c2++)
		{
			int &a=ans[c1][c2]=2147483647;
			for(int cm=0;cm<C;cm++)
			{
				int v=get_dis_H(r-1,c1,cm)+get_dis_V(cm,r-1,r)+get_dis_H(r,cm,c2);
//				printf("(%d,%d)=%d\n",c1,c2,v);
				getmin(a,v);
			}
		}
	}
//	printf("get_rowdis(%d)\n",r);
//	for(int i=0;i<C;i++)
//	{
//		for(int j=0;j<C;j++)
//		{
//			printf(" %d",ans[i][j]);
//		}printf("\n");
//	}
}
void merge_r1r2(int up[100][100],int down[100][100],int ans[100][100])
{
	for(int c1=0;c1<C;c1++)
	{
		for(int c2=0;c2<C;c2++)
		{
			int &a=ans[c1][c2]=2147483647;
			for(int cm=0;cm<C;cm++)
			{
				getmin(a,up[c1][cm]+down[cm][c2]);
			}
		}
	}
}
void copy_array(int from[100][100],int to[100][100])
{
	for(int c1=0;c1<C;c1++)
	{
		for(int c2=0;c2<C;c2++)
		{
			to[c1][c2]=from[c1][c2];
		}
	}
}
struct Node
{
	Node *r,*l;
	int v[100][100];
	Node():r(NULL),l(NULL){}
	Node(int r1,int r2):Node()
	{
		int down[100][100],ans[100][100];
		for(int c1=0;c1<C;c1++)
		{
			for(int c2=c1;c2<C;c2++)
			{
				v[c1][c2]=v[c2][c1]=get_dis_H(r1,c1,c2);
			}
		}
		for(int r=r1+1;r<=r2;r++)
		{
			get_rowdis(r,down);
			merge_r1r2(v,down,ans);
			copy_array(ans,v);
		}
	}
	void show()
	{
		for(int i=0;i<C;i++)
		{
			for(int j=0;j<C;j++)
			{
				printf(" %d",v[i][j]);
			}printf("\n");
		}
	}
};
Node *ROOT;
void build_tree(Node* &n,int l,int r,int dep)
{
	if(dep==12||l+1>=r)
	{
		n=new Node(l,r);
//		printf("new dep=%d %d~%d\n",dep,l,r);
//		n->show();
		return;
	}
	n=new Node();
	int mid=(l+r)/2;
	build_tree(n->l,l,mid,dep+1);
	build_tree(n->r,mid,r,dep+1);
	merge_r1r2(n->l->v,n->r->v,n->v);
//	printf("%d~%d\n",l,r);
//	n->show();
}
void modify_tree(Node* &n,int l,int r,int dep,int ql,int qr)
{
	if(ql>r||qr<l)return;
	if(dep==12||l+1>=r)
	{
		n=new Node(l,r);
		return;
	}
	int mid=(l+r)/2;
	modify_tree(n->l,l,mid,dep+1,ql,qr);
	modify_tree(n->r,mid,r,dep+1,ql,qr);
	merge_r1r2(n->l->v,n->r->v,n->v);
}
int main()
{
	//freopen("IN.txt","r",stdin); 
	while(scanf("%d%d",&R,&C)==2)
	{
		for(int r=0;r<R;r++)
		{
			H_SUM[r][0]=0;
			for(int c=1;c<C;c++)
			{
				scanf("%d",&H[r][c]);
				H_SUM[r][c]=H_SUM[r][c-1]+H[r][c];
			}
		}
		for(int c=0;c<C;c++)V_SUM[0][c]=0;
		for(int r=1;r<R;r++)
		{
			for(int c=0;c<C;c++)
			{
				scanf("%d",&V[r][c]);
				V_SUM[r][c]=V_SUM[r-1][c]+V[r][c];
			}
		}
		build_tree(ROOT,0,R-1,1);
		int E;scanf("%d",&E);
		while(E--)
		{
			int type;scanf("%d",&type);
			if(type==1)
			{
				int r,c,w;scanf("%d%d%d",&r,&c,&w);
				H[r][c+1]=w;
				for(int i=c+1;i<C;i++)
				{
					H_SUM[r][i]=H_SUM[r][i-1]+H[r][i];
				}
				modify_tree(ROOT,0,R-1,1,r,r);
			}
			else if(type==2)
			{
				int r,c,w;scanf("%d%d%d",&r,&c,&w);
				V[r+1][c]=w;
				for(int i=r+1;i<R;i++)
				{
					V_SUM[i][c]=V_SUM[i-1][c]+V[i][c];
				}
				modify_tree(ROOT,0,R-1,1,r,r+1);
			}
			else
			{
				int c1,c2;scanf("%d%d",&c1,&c2);
				printf("%d\n",ROOT->v[c1][c2]);
			}
		}
	}
	return 0;
}

#include<cstdio>
#include<cstdlib>
int H_SUM[5000][100],V_SUM[5000][100],TMP_ARRAY2[100][100],TMP_ARRAY3[100][100];
short R,C,H[5000][100],V[5000][100],TMP_ARRAY[100][100];
inline int abs(int a){return a>=0?a:-a;}
inline int get_dis_H(short r,short c1,short c2)
{
    return abs(H_SUM[r][c1]-H_SUM[r][c2]);
}
inline int get_dis_V(short c,short r1,short r2)
{
    return abs(V_SUM[r1][c]-V_SUM[r2][c]);
}
inline void get_rowdis(short r,int ans[100][100])
{
    for(short i=0;i<C;i++)
    {
        int &a=ans[i][i]=2147483647;
        for(short j=0;j<C;j++)
        {
            int v=get_dis_H(r-1,i,j)+get_dis_V(j,r-1,r)+get_dis_H(r,j,i);
            if(v<a)
            {
                a=v;
                TMP_ARRAY[i][i]=j;
            }
        }
    }
    for(short gap=1;gap<C;gap++)
    {
        for(short i=gap;i<C;i++)
        {
            int &a=ans[i][i-gap]=2147483647;
            for(short j=TMP_ARRAY[i-1][i-gap];j<=TMP_ARRAY[i][i-gap+1];j++)
            {
                int v=get_dis_H(r-1,i,j)+get_dis_V(j,r-1,r)+get_dis_H(r,j,i-gap);
                if(v<a)
                {
                    a=v;
                    TMP_ARRAY[i][i-gap]=j;
                }
            }
        }
        for(short i=0;i+gap<C;i++)
        {
            int &a=ans[i][i+gap]=2147483647;
            for(short j=TMP_ARRAY[i][i+gap-1];j<=TMP_ARRAY[i+1][i+gap];j++)
            {
                int v=get_dis_H(r-1,i,j)+get_dis_V(j,r-1,r)+get_dis_H(r,j,i+gap);
                if(v<a)
                {
                    a=v;
                    TMP_ARRAY[i][i+gap]=j;
                }
            }
        }
    }
}
inline void merge_r1r2(int up[100][100],int down[100][100],int ans[100][100])
{
    for(short i=0;i<C;i++)
    {
        int &a=ans[i][i]=2147483647;
        for(short j=0;j<C;j++)
        {
            int v=up[i][j]+down[j][i];
            if(v<a)
            {
                a=v;
                TMP_ARRAY[i][i]=j;
            }
        }
    }
    for(short gap=1;gap<C;gap++)
    {
        for(short i=gap;i<C;i++)
        {
            int &a=ans[i][i-gap]=2147483647;
            for(short j=TMP_ARRAY[i-1][i-gap];j<=TMP_ARRAY[i][i-gap+1];j++)
            {
                int v=up[i][j]+down[j][i-gap];
                if(v<a)
                {
                    a=v;
                    TMP_ARRAY[i][i-gap]=j;
                }
            }
        }
        for(short i=0;i+gap<C;i++)
        {
            int &a=ans[i][i+gap]=2147483647;
            for(short j=TMP_ARRAY[i][i+gap-1];j<=TMP_ARRAY[i+1][i+gap];j++)
            {
                int v=up[i][j]+down[j][i+gap];
                if(v<a)
                {
                    a=v;
                    TMP_ARRAY[i][i+gap]=j;
                }
            }
        }
    }
}
inline void copy_array(int from[100][100],int to[100][100])
{
    for(short c1=0;c1<C;c1++)
    {
        for(short c2=0;c2<C;c2++)
        {
            to[c1][c2]=from[c1][c2];
        }
    }
}
struct Node
{
    Node *r,*l;
    int v[100][100];
    inline Node():r(NULL),l(NULL){}
    inline Node(short r1,short r2):Node()
    {
        for(short c1=0;c1<C;c1++)
        {
            for(short c2=c1;c2<C;c2++)
            {
                v[c1][c2]=v[c2][c1]=get_dis_H(r1,c1,c2);
            }
        }
        for(short r=r1+1;r<=r2;r++)
        {
            get_rowdis(r,TMP_ARRAY2);
            merge_r1r2(v,TMP_ARRAY2,TMP_ARRAY3);
            copy_array(TMP_ARRAY3,v);
        }
    }
};
Node *ROOT;
void build_tree(Node* &n,short l,short r,short dep)
{
    if(dep==12||l+1>=r)
    {
        n=new Node(l,r);
        return;
    }
    n=new Node();
    short mid=(l+r)/2;
    build_tree(n->l,l,mid,dep+1);
    build_tree(n->r,mid,r,dep+1);
    merge_r1r2(n->l->v,n->r->v,n->v);
}
void modify_tree(Node* &n,short l,short r,short dep,short ql,short qr)
{
    if(ql>r||qr<l)return;
    if(dep==12||l+1>=r)
    {
        n=new Node(l,r);
        return;
    }
    short mid=(l+r)/2;
    modify_tree(n->l,l,mid,dep+1,ql,qr);
    modify_tree(n->r,mid,r,dep+1,ql,qr);
    merge_r1r2(n->l->v,n->r->v,n->v);
}
int main()
{
    //freopen("IN.txt","r",stdin); 
    while(scanf("%d%d",&R,&C)==2)
    {
        for(short r=0;r<R;r++)
        {
            H_SUM[r][0]=0;
            for(short c=1;c<C;c++)
            {
                scanf("%d",&H[r][c]);
                H_SUM[r][c]=H_SUM[r][c-1]+H[r][c];
            }
        }
        for(short c=0;c<C;c++)V_SUM[0][c]=0;
        for(short r=1;r<R;r++)
        {
            for(short c=0;c<C;c++)
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
            //printf("%d\n",type);continue;
            switch(type)
            {
            	case 1:
            	{
	                short r,c,w;scanf("%d%d%d",&r,&c,&w);
	                H[r][c+1]=w;
	                for(short i=c+1;i<C;i++)
	                {
	                    H_SUM[r][i]=H_SUM[r][i-1]+H[r][i];
	                }
	                modify_tree(ROOT,0,R-1,1,r,r);
				}break;
            	case 2:
            	{
	                int r,c,w;scanf("%d%d%d",&r,&c,&w);
	                V[r+1][c]=w;
	                for(int i=r+1;i<R;i++)
	                {
	                    V_SUM[i][c]=V_SUM[i-1][c]+V[i][c];
	                }
	                modify_tree(ROOT,0,R-1,1,r,r+1);
				}break;
            	default:
            	{
	                int c1,c2;scanf("%d%d",&c1,&c2);
	                printf("%d\n",ROOT->v[c1][c2]);
				}break;
			}
        }
    }
    return 0;
}


#include<cstdio>
#include<cstdlib>
int R,C,H_SUM[5000][200],V_SUM[5000][200],TMP_ARRAY[200][200],TMP_ARRAY2[200][200],TMP_ARRAY3[200][200];
inline void getmin(int &a,int b){if(b<a)a=b;}
inline int abs(int a){return a>=0?a:-a;}
inline int get_dis_H(int r,int c1,int c2)
{
    return abs(H_SUM[r][c1]-H_SUM[r][c2]);
}
inline int get_dis_V(int c,int r1,int r2)
{
    return abs(V_SUM[r1][c]-V_SUM[r2][c]);
}
inline void get_rowdis(int r,int ans[200][200])
{
    for(int i=0;i<C;i++)
    {
        int &a=ans[i][i]=2147483647;
        for(int j=(i>=1?TMP_ARRAY[i-1][i-1]:0);j<C;j++)
        {
            int v=get_dis_H(r-1,i,j)+get_dis_V(j,r-1,r)+get_dis_H(r,j,i);
            if(v<a)
            {
                a=v;
                TMP_ARRAY[i][i]=j;
            }
        }
    }
    for(int gap=1;gap<C;gap++)
    {
        for(int i=gap;i<C;i++)
        {
            int &a=ans[i][i-gap]=2147483647;
            for(int j=TMP_ARRAY[i-1][i-gap];j<=TMP_ARRAY[i][i-gap+1];j++)
            {
                int v=get_dis_H(r-1,i,j)+get_dis_V(j,r-1,r)+get_dis_H(r,j,i-gap);
                if(v<a)
                {
                    a=v;
                    TMP_ARRAY[i][i-gap]=j;
                }
            }
        }
        for(int i=0;i+gap<C;i++)
        {
            int &a=ans[i][i+gap]=2147483647;
            for(int j=TMP_ARRAY[i][i+gap-1];j<=TMP_ARRAY[i+1][i+gap];j++)
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
inline void merge_r1r2(int up[200][200],int down[200][200],int ans[200][200])
{
    for(int i=0;i<C;i++)
    {
        int &a=ans[i][i]=2147483647;
        for(int j=(i>=1?TMP_ARRAY[i-1][i-1]:0);j<C;j++)
        {
            int v=up[i][j]+down[j][i];
            if(v<a)
            {
                a=v;
                TMP_ARRAY[i][i]=j;
            }
        }
    }
    for(int gap=1;gap<C;gap++)
    {
        for(int i=gap;i<C;i++)
        {
            int &a=ans[i][i-gap]=2147483647;
            for(int j=TMP_ARRAY[i-1][i-gap];j<=TMP_ARRAY[i][i-gap+1];j++)
            {
                int v=up[i][j]+down[j][i-gap];
                if(v<a)
                {
                    a=v;
                    TMP_ARRAY[i][i-gap]=j;
                }
            }
        }
        for(int i=0;i+gap<C;i++)
        {
            int &a=ans[i][i+gap]=2147483647;
            for(int j=TMP_ARRAY[i][i+gap-1];j<=TMP_ARRAY[i+1][i+gap];j++)
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
inline void copy_array(int from[200][200],int to[200][200])
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
    int v[200][200];
    inline Node():r(NULL),l(NULL){}
    inline Node(int r1,int r2):Node()
    {
        for(int c1=0;c1<C;c1++)
        {
            for(int c2=c1;c2<C;c2++)
            {
                v[c1][c2]=v[c2][c1]=get_dis_H(r1,c1,c2);
            }
        }
        for(int r=r1+1;r<=r2;r++)
        {
            get_rowdis(r,TMP_ARRAY2);
            merge_r1r2(v,TMP_ARRAY2,TMP_ARRAY3);
            copy_array(TMP_ARRAY3,v);
        }
    }
};
Node *ROOT;
void build_tree(Node* &n,int l,int r,int dep)
{
    if(r-l<=19||l+1>=r)
    {
        n=new Node(l,r);
        return;
    }
    n=new Node();
    int mid=(l+r)/2;
    build_tree(n->l,l,mid,dep+1);
    build_tree(n->r,mid,r,dep+1);
    merge_r1r2(n->l->v,n->r->v,n->v);
}
void modify_tree(Node* &n,int l,int r,int dep,int ql,int qr)
{
    if(ql>r||qr<l)return;
    if(r-l<=19||l+1>=r)
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
                scanf("%d",&H_SUM[r][c]);
                H_SUM[r][c]+=H_SUM[r][c-1];
            }
        }
        for(int c=0;c<C;c++)V_SUM[0][c]=0;
        for(int r=1;r<R;r++)
        {
            for(int c=0;c<C;c++)
            {
                scanf("%d",&V_SUM[r][c]);
                V_SUM[r][c]+=V_SUM[r-1][c];
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
                w-=H_SUM[r][c+1]-H_SUM[r][c];
                for(int i=c+1;i<C;i++)
                {
                    H_SUM[r][i]+=w;
                }
                modify_tree(ROOT,0,R-1,1,r,r);
            }
            else if(type==2)
            {
                int r,c,w;scanf("%d%d%d",&r,&c,&w);
                w-=V_SUM[r+1][c]-V_SUM[r][c];
                for(int i=r+1;i<R;i++)
                {
                    V_SUM[i][c]+=w;
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


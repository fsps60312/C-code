#include<cstdio>
#include<cstdlib>
int T,N,Q,YS,YL;
struct Ctype
{
    int head;
    int sum;
    int yl;
    int ys;
}C[100000];
struct STtype
{
    bool tag;
    int num;
    int sum;
    int addn,adds;
}ST[4000000];
void buildtree(int id,int l,int r)
{
    STtype &s=ST[id];
    s.tag=false;
    s.num=s.sum=0;
    if(l==r)return;
    int mid=(l+r)>>1;
    id<<=1;
    buildtree(id,l,mid);
    buildtree(++id,++mid,r);
}
void maintain(STtype &st,int addn,int adds)
{
    st.num+=addn,st.sum+=adds;
    if(st.tag)
    {
        st.addn+=addn;
        st.adds+=adds;
    }
    else
    {
        st.addn=addn;
        st.adds=adds;
        st.tag=true;
    }
}
void putdown(int id)
{
    STtype &s=ST[id];
    if(!s.tag)return;
    int id1=(id<<=1),id2=(++id);
    s.tag=false;
    int addn=s.addn,adds=s.adds;
    maintain(ST[id1],addn,adds);
    maintain(ST[id2],addn,adds);
}
STtype query(int id,int l,int r,int i)
{
    if(l==r)return ST[id];
    putdown(id);
    int mid=(l+r)>>1;
    id<<=1;
    if(i<=mid)return query(id,l,mid,i);
    return query(++id,++mid,r,i);
}
int findhead(int a)
{
    if(C[a].head==a)return a;
    return C[a].head=findhead(C[a].head);
}
void addv(int id,int l,int r,int L,int R,int addn,int adds)
{
    if(r<L||l>R)return;
    if(l>=L&&r<=R)
    {
        maintain(ST[id],addn,adds);
        return;
    }
    putdown(id);
    int mid=(l+r)>>1;
    id<<=1;
    addv(id,l,mid,L,R,addn,adds);
    addv(++id,++mid,r,L,R,addn,adds);
}
void update(int i1,int i2)
{
    if(i1==i2)return;
    Ctype &c1=C[i1],&c2=C[i2];
    //clear data of C[i1]
    if(c1.ys<c1.yl)addv(1,YS,YL,c1.ys,c1.yl-1,-1,-c1.sum);
    //clear data of C[i2]
    if(c2.ys<c2.yl)addv(1,YS,YL,c2.ys,c2.yl-1,-1,-c2.sum);
    //insert data to C[i1]
    c2.head=i1;
    if(c2.yl>c1.yl)c1.yl=c2.yl;
    if(c2.ys<c1.ys)c1.ys=c2.ys;
    c1.sum+=c2.sum;
    if(c1.ys<c1.yl)addv(1,YS,YL,c1.ys,c1.yl-1,1,c1.sum);
}
int main()
{
    //freopen("in.txt","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        YS=1000000,YL=0;
        for(int i=0,ti1,ti2;i<N;i++)
        {
            scanf("%d%d",&ti1,&ti2);
            if(ti2>YL)YL=ti2;
            if(ti2<YS)YS=ti2;
            Ctype &c=C[i];
            c.ys=c.yl=ti2;
            c.sum=1;
            c.head=i;
        }
        YL--;
        if(YS<=YL)buildtree(1,YS,YL);
        scanf("%d",&Q);
        char tstr[5];
        while(Q--)
        {
            scanf("%s",tstr);
            if(tstr[0]=='r')
            {
                int a,b;scanf("%d%d",&a,&b);
                if(YS<=YL)update(findhead(a),findhead(b));
            }
            else
            {
                double ty;scanf("%lf",&ty);
                int y=(int)ty;
                if(YS<=YL&&y>=YS&&y<=YL)
                {
                    STtype ts=query(1,YS,YL,y);
                    printf("%d %d\n",ts.num,ts.sum);
                }
                else printf("0 0\n");
            }
        }
    }
    return 0;
}

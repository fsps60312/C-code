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
    bool notinit;
    bool tag;
    int num;
    int sum;
    int addn,adds;
}ST[4000000];
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
    if(ST[id].notinit)
    {
        ST[id].notinit=false;
        int id1=id*2,id2=id*2+1;
        ST[id1].notinit=ST[id2].notinit=true;
        ST[id1].tag=ST[id2].tag=false;
        ST[id1].num=ST[id2].num=ST[id1].sum=ST[id2].sum=0;
    }
    if(!ST[id].tag)return;
    int id1=id*2,id2=id*2+1;
    ST[id].tag=false;
    int addn=ST[id].addn,adds=ST[id].adds;
    maintain(ST[id1],addn,adds);
    maintain(ST[id2],addn,adds);
}
STtype query(int id,int l,int r,int i)
{
    if(l==r)return ST[id];
    putdown(id);
    int mid=(l+r)/2;
    if(i<=mid)return query(id*2,l,mid,i);
    return query(id*2+1,mid+1,r,i);
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
    int mid=(l+r)/2;
    addv(id*2,l,mid,L,R,addn,adds);
    addv(id*2+1,mid+1,r,L,R,addn,adds);
}
void update(int i1,int i2)
{
    if(i1==i2)return;
    //clear data of C[i1]
    if(C[i1].ys<C[i1].yl)addv(1,YS,YL,C[i1].ys,C[i1].yl-1,-1,-C[i1].sum);
    //clear data of C[i2]
    if(C[i2].ys<C[i2].yl)addv(1,YS,YL,C[i2].ys,C[i2].yl-1,-1,-C[i2].sum);
    //insert data to C[i1]
    C[i2].head=i1;
    if(C[i2].yl>C[i1].yl)C[i1].yl=C[i2].yl;
    if(C[i2].ys<C[i1].ys)C[i1].ys=C[i2].ys;
    C[i1].sum+=C[i2].sum;
    if(C[i1].ys<C[i1].yl)addv(1,YS,YL,C[i1].ys,C[i1].yl-1,1,C[i1].sum);
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
            C[i].ys=C[i].yl=ti2;
            C[i].sum=1;
            C[i].head=i;
        }
        YL--;
        ST[1].notinit=true;
        ST[1].tag=false;
        ST[1].num=ST[1].sum=0;
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

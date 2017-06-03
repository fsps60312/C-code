#include<cstdio>
#include<cstdlib>
int S[100001],st[400000];
int N,Q;
void buildtree(int id,int l,int r)
{
    if(l==r)
    {
        st[id]=S[l];
        return;
    }
    int mid=(l+r)/2;
    buildtree(id*2,l,mid);
    buildtree(id*2+1,mid+1,r);
    st[id]=st[id*2]<st[id*2+1]?st[id*2]:st[id*2+1];
}
int query(int id,int l,int r,int L,int R)
{
    if(l>=L&&r<=R)return st[id];
    if(l>R||r<L)return 2147483647;
    int mid=(l+r)/2;
    int ql=query(id*2,l,mid,L,R);
    int qr=query(id*2+1,mid+1,r,L,R);
    return ql<qr?ql:qr;
}
int query(int id,int l,int r,int i)
{
    if(l==r)return st[id];
    int mid=(l+r)/2;
    if(i<=mid)return query(id*2,l,mid,i);
    else return query(id*2+1,mid+1,r,i);
}
void change(int id,int l,int r,int i,int v)
{
    if(l==r)
    {
        st[id]=v;
        return;
    }
    int mid=(l+r)/2;
    if(i<=mid)change(id*2,l,mid,i,v);
    else change(id*2+1,mid+1,r,i,v);
    st[id]=st[id*2]<st[id*2+1]?st[id*2]:st[id*2+1];
}
bool isnum(char a){return a>='0'&&a<='9';}
int main()
{
	//freopen("in.txt","r",stdin);
    scanf("%d%d",&N,&Q);
    for(int i=1;i<=N;i++)scanf("%d",&S[i]);
    buildtree(1,1,N);
    char tstr[31];
    while(Q--)
    {
		scanf("%s",tstr);
        if(tstr[0]=='q')
        {
            int L=0,R=0;
            int i=0;
            while(!isnum(tstr[i]))i++;
            while(isnum(tstr[i]))L*=10,L+=tstr[i]-'0',i++;
            while(!isnum(tstr[i]))i++;
            while(isnum(tstr[i]))R*=10,R+=tstr[i]-'0',i++;
            printf("%d\n",query(1,1,N,L,R));
        }
        else
        {
            int tf,tn1=0,tn2=0;
            int i;
            while(!isnum(tstr[i]))i++;
            while(isnum(tstr[i]))tn1*=10,tn1+=tstr[i]-'0',i++;
            tf=query(1,1,N,tn1);
            while(!isnum(tstr[i])&&tstr[i]!=')')i++;
            while(tstr[i]!=')')
            {
                while(isnum(tstr[i]))tn2*=10,tn2+=tstr[i]-'0',i++;
                while(!isnum(tstr[i])&&tstr[i]!=')')i++;
                change(1,1,N,tn1,query(1,1,N,tn2));
                tn1=tn2;
                tn2=0;
            }
            if(tn2==0)continue;
            change(1,1,N,tn1,tf);
        }
    }
    return 0;
}

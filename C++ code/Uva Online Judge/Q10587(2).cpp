#include<cstdio>
#include<cstdlib>
int T,N,t1[10000001];
struct pairtype{int tag,v;}w[10000001*4];
void putdown(int id,int l,int r,int mid)
{
	if(w[id].tag==-1)return;
	int v=w[id].tag;
	w[id].tag=-1;
	w[id*2].tag=w[id*2+1].tag=v;
	w[id*2].v=v*(mid-l+1);
	w[id*2+1].v=v*(r-mid);
}
void setvalue(int id,int l,int r,int v,int L,int R)
{
	if(l>=L&&r<=R)
	{
		w[id].tag=v;
		w[id].v=v*(r-l+1);
		return;
	}
	if(l>R||r<L)return;
	int mid=(l+r)/2;
	putdown(id,l,r,mid);
	setvalue(id*2,l,mid,v,L,R);
	setvalue(id*2+1,mid+1,r,v,L,R);
	w[id].v=w[id*2].v+w[id*2+1].v;
}
int countnum(int id)
{
	int ans=0;
	if(w[id].tag!=-1)
	{
		if(!t1[w[id].tag])ans++;
		t1[w[id].tag]++;
		return ans;
	}
	ans+=countnum(id*2);
	ans+=countnum(id*2+1);
	return ans;
}
int in[10000][2];
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		int Max=0;
		for(int i=1;i<=N;i++)
		{
			scanf("%d%d",&in[i][0],&in[i][1]);
			if(in[i][1]>Max)Max=in[i][1];
		}
		setvalue(1,1,Max,0,1,Max);
		for(int i=0;i<N;i++)
		{
			setvalue(1,1,Max,i+1,in[i][0],in[i][1]);
		}
		t1[0]=1;
		for(int i=1;i<=N;i++)t1[i]=0;
		printf("%d\n",countnum(1));
		//for(int i=1;i<=Max;i++)printf(" %d",t1[i]);printf("\n");
	}
	return 0;
}

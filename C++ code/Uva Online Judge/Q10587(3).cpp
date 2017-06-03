#include<cstdio>
#include<cstdlib>
int T,N,t1[10000001],w[10000001*4];
void putdown(int id,int l,int r,int mid)
{
	if(w[id]==-1)return;
	int v=w[id];
	w[id]=-1;
	w[id*2]=w[id*2+1]=v;
}
void setvalue(int id,int l,int r,int v,int L,int R)
{
	if(l>=L&&r<=R)
	{
		w[id]=v;
		return;
	}
	if(l>R||r<L)return;
	int mid=(l+r)/2;
	putdown(id,l,r,mid);
	setvalue(id*2,l,mid,v,L,R);
	setvalue(id*2+1,mid+1,r,v,L,R);
}
int countnum(int id)
{
	int ans=0;
	if(w[id]!=-1)
	{
		if(!t1[w[id]])ans++;
		t1[w[id]]++;
		return ans;
	}
	ans+=countnum(id*2);
	ans+=countnum(id*2+1);
	return ans;
}
int in[10001][2];
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
		for(int i=1;i<=N;i++)
		{
			setvalue(1,1,Max,i,in[i][0],in[i][1]);
		//for(int i=1;i<=20;i++)printf(" %d",w[i]);printf("\n");
		}
		t1[0]=1;
		for(int i=1;i<=N;i++)t1[i]=0;
		//for(int i=1;i<=20;i++)printf(" %d",w[i]);printf("\n");
		printf("%d\n",countnum(1));
		//for(int i=1;i<=Max;i++)printf(" %d",t1[i]);printf("\n");
	}
	return 0;
}

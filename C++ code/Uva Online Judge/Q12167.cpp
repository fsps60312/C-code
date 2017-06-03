#include<cstdio>
#include<cstdlib>
#define min(x,y) (x)<(y)?(x):(y)
#define max(x,y) (x)>(y)?(x):(y)
int T,N,M,HEAD[20001],NEXT[50000],TO[50000],NSZ,BCC_CNT,PRE_CNT,PRE[20001],LOW[20001],BCC[20001],IN[20001],OUT[20001];
void addprove(int a,int b)
{
	NEXT[NSZ]=HEAD[a];
	HEAD[a]=NSZ;
	TO[NSZ]=b;
	NSZ++;
}
struct Stack
{
	int sz,s[50000];
	void clear(){sz=0;}
	void push(int x){s[sz]=x;sz++;}
	void pop(){sz--;}
	int front(){return s[sz-1];}
}SIDE;
void dfs(int u)
{
	//printf("a:%d\n",u);
	LOW[u]=PRE[u]=++PRE_CNT;
	int first=0;
	SIDE.push(u);
	for(int ti=HEAD[u];ti!=-1;ti=NEXT[ti])
	{
		int i=TO[ti];
		if(BCC[i])continue;
		if(!PRE[i])
		{
			if(!first)first=i;
			dfs(i);
		}
		else
		{
			LOW[u]=min(LOW[u],PRE[i]);
		}
	}
	//printf("b:%d\n",u);
	if(PRE[u]==LOW[u])
	{
		BCC_CNT++;
		for(;;)
		{
			int v=SIDE.front();SIDE.pop();
			if(!BCC[v])BCC[v]=BCC_CNT;
			if(v==u)break;
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	SIDE.clear();
	scanf("%d",&T);
	while(T--)
	{
		NSZ=BCC_CNT=PRE_CNT=0;
		scanf("%d%d",&N,&M);
		for(int i=1;i<=N;i++){PRE[i]=IN[i]=OUT[i]=BCC[i]=0;HEAD[i]=-1;}
		while(M--)
		{
			int a,b;scanf("%d%d",&a,&b);
			addprove(a,b);
		}
		for(int i=1;i<=N;i++)
		{
			if(!PRE[i])dfs(i);
		}
		//for(int i=1;i<=N;i++)if(BCC[i])printf("BCC[%d] is %d\n",i,BCC[i]);
		for(int i=1;i<=N;i++)
		{
			for(int tj=HEAD[i];tj!=-1;tj=NEXT[tj])
			{
				int j=TO[tj];
				if(BCC[i]!=BCC[j])OUT[BCC[i]]++,IN[BCC[j]]++;
			}
		}
		int in=0,out=0;
		for(int i=1;i<=BCC_CNT;i++)
		{
			if(!OUT[i])out++;
			if(!IN[i])in++;
		}
		printf("%d\n",BCC_CNT==1?0:max(in,out));
	}
	return 0;
}

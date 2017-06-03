#include<cstdio>
#include<cstdlib>
#define LL long long
#define min(x,y) (x)<(y)?(x):(y)
int N,L,HEAD[50002],HSZ,NEXT[100001],TO[100001],NSZ,PRE[50002],PRE_CNT,LOW[50002],BCC_CNT,BCC[50002],ISCUT[50002],SUM;
LL ANS;
struct Stack
{
	int s[100000][2],sz;
	void clear(){sz=0;}
	void push(int x,int y){s[sz][0]=x,s[sz][1]=y,sz++;}
	void pop(){sz--;}
	int *front(){return s[sz-1];}
}SIDE;
LL cnt(int u,int bccn)
{
	BCC[u]=0;
	LL ans=1;
	for(int ti=HEAD[u];ti!=-1;ti=NEXT[ti])
	{
		int i=TO[ti];
		if(BCC[i]!=bccn)continue;
		ans+=cnt(i,bccn);
	}
	return ans;
}
void dfs(int u,int fa)
{
	LOW[u]=PRE[u]=++PRE_CNT;
	for(int ti=HEAD[u];ti!=-1;ti=NEXT[ti])
	{
		int i=TO[ti];
		if(!PRE[i])
		{
			SIDE.push(u,i);
			dfs(i,u);
			if(LOW[i]>=PRE[u])
			{
				ISCUT[u]=true;
				BCC_CNT++;
				int cutn=0,cnt=0;
				while(1)
				{
					int *v=SIDE.front();SIDE.pop();
					if(BCC[v[0]]!=BCC_CNT)
					{
						if(ISCUT[v[0]])
						{
							cutn++;
							if(cutn==2)break;
						}
						else cnt++;
						BCC[v[0]]=BCC_CNT;
					}
					if(BCC[v[1]]!=BCC_CNT)
					{
						if(ISCUT[v[1]])
						{
							cutn++;
							if(cutn==2)break;
						}
						else cnt++;
						BCC[v[1]]=BCC_CNT;
					}
					if(v[0]==u&&v[1]==i)break;
				}
				//printf("cutn=%d\tcnt=%d\n",cutn,cnt);
				if(cutn==1)ANS*=cnt,SUM++;
			}
			else LOW[u]=min(LOW[u],LOW[i]);
		}
		else if(PRE[i]<PRE[u]&&i!=fa)
		{
			LOW[u]=min(LOW[u],PRE[i]);
		}
	}
}
void addhead(int a){while(HSZ<=a)PRE[HSZ]=BCC[HSZ]=ISCUT[HSZ]=0,HEAD[HSZ++]=-1;}
void addtunnel(int from,int to)
{
	NEXT[NSZ]=HEAD[from];
	HEAD[from]=NSZ;
	TO[NSZ]=to;
	NSZ++;
}
int main()
{
	//freopen("in.txt","r",stdin);
	SIDE.clear();
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		HSZ=NSZ=PRE_CNT=BCC_CNT=SUM=0;
		ANS=1LL;
		while(N--)
		{
			int a,b;scanf("%d%d",&a,&b);
			addhead(a),addhead(b);
			addtunnel(a,b),addtunnel(b,a);
		}
		//for(int i=0;i<HSZ;i++)printf("HEAD[%d]=%d\n",i,HEAD[i]);
		//for(int i=0;i<NSZ;i++)printf("NEXT[%d]=%d\t%d\n",i,NEXT[i],TO[i]);
		dfs(1,-1);
		if(!BCC_CNT)SUM=2,ANS=(HSZ-1)*(HSZ-2)/2;
		printf("Case %d: %d %lld\n",kase++,SUM,ANS);
	}
	return 0;
}

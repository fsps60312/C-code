#include<cstdio>
#define debug(x,...) {}//printf(x,##__VA_ARGS__)
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
char LINE[1000001];
int N,SA[1000001],HT[1000001],RANK[1000001],SUF[21][1000001];
void show(char *msg,int *bse,int n){printf("%s:",msg);for(int i=0;i<n;i++)printf(" %d",bse[i]);puts("");}
void buildSA()
{
	int *c=RANK,*x=SUF[0],*y=SUF[1];
	int kind=256;
	for(int i=0;i<kind;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=LINE[i]]++;
	for(int i=1;i<kind;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;//SA[x]=y -> rank x is loc y
	for(int dis=1;dis<N;dis<<=1)
	{
		int p=0;
		for(int i=N-dis;i<N;i++)y[p++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=dis)y[p++]=SA[i]-dis;
		for(int i=0;i<kind;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<kind;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		p=0;
		y[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(x[SA[i]]!=x[SA[i-1]])y[SA[i]]=p++;
			else if(SA[i]+dis>=N&&SA[i-1]+dis>=N)y[SA[i]]=p-1;
			else if(SA[i]+dis>=N||SA[i-1]+dis>=N)y[SA[i]]=p++;
			else y[SA[i]]=x[SA[i]+dis]==x[SA[i-1]+dis]?p-1:p++; 
		}
		kind=p;
		if(kind>=N)break;
		int *tmp=x;x=y,y=tmp;
	}
}
void buildHT()//HT[x]=y -> height of rank x is y
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	int ans=0;HT[0]=0;
	for(int loc=0,i;loc<N;loc++)
	{
		if(ans)ans--;
		i=RANK[loc];
		if(!i)continue;
		while(LINE[SA[i]+ans]==LINE[SA[i-1]+ans])ans++;
		HT[i]=ans;
	}
}
int min(int a,int b){return a<b?a:b;}
void buildSUF()
{
	debug("0:");
	for(int i=0;i<N;i++)
	{
		SUF[0][i]=HT[i];
		debug(" %d",SUF[0][i]);
	}debug("\n");
	for(int h=1,dis=2;dis<=N;h++,dis<<=1)
	{
		debug("%d:",h);
		for(int i=0;i+dis<=N;i++)
		{
			SUF[h][i]=min(SUF[h-1][i],SUF[h-1][i+dis/2]);
			debug(" %d",SUF[h][i]);
		}debug("\n");
	}
}
int SufLen(int i1,int i2)
{
	if(i1==i2)return N-i1;
	i1=RANK[i1],i2=RANK[i2];
	if(i1>i2){int tmp=i1;i1=i2,i2=tmp;}
	i1++;
	int h=0;
	while((1<<(h+1))<=i2-i1+1)h++;
	return min(SUF[h][i1],SUF[h][i2-(1<<h)+1]);
}
int solve()
{
	for(int p=1;p<=N;p++)
	{
		if(N%p)continue;
		bool found=true;
		for(int i=p;i<N;i+=p)if(SufLen(0,p)<p){found=false;break;}
		if(found)return N/p;
	}
}
int main()
{
//	printf("test=%d\n",1<<(-1));
//	printf("%d\n",';');
	while(scanf("%s",LINE)==1)
	{
		N=-1;while(LINE[++N])if(LINE[N]>=256||LINE[N]<0)termin("not in range\n");
		if(N==1&&LINE[0]=='.')break;
		buildSA();
		buildHT();
		buildSUF();
//		show("HT",HT,N);
		printf("%d\n",solve());
	}
	return 0;
}

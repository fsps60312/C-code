#include<cstdio>
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);}
int T,L,*X,TMP[3][100000],SA[100000];
char STR[100001];
void show(char *msg,int *s,int n)
{
	printf("%s:",msg);
	for(int i=0;i<n;i++)printf(" %d",s[i]);puts("");
}
void buildSA()
{
	int *c=TMP[0],*x=TMP[1],*y=TMP[2];
	int kind=26;
	for(int i=0;i<kind;i++)c[i]=0;
	for(int i=0;i<L;i++)c[x[i]=STR[i]-'a']++;
	for(int i=1;i<kind;i++)c[i]+=c[i-1];
	for(int i=L-1;i>=0;i--)SA[--c[x[i]]]=i;//SA[x]=y -> rank x is loc y
	show("x",x,L),show("y",y,L);
	for(int dis=1;dis<L;dis<<=1)
	{
		for(int i=0;i<L;i++)y[(SA[i]+L-dis)%L]=i;
		for(int i=0;i<kind;i++)c[i]=0;
		for(int i=0;i<L;i++)c[x[i]]++;
		for(int i=0;i<kind;i++)c[i]+=c[i-1];
		for(int i=L-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
		show("x",x,L),show("y",y,L);
		int p=0;
		y[SA[0]]=p++;
		for(int i=1;i<L;i++)
		{
			y[SA[i]]=(x[SA[i]]==x[SA[i-1]]&&x[(SA[i]+dis)%L]==x[(SA[i-1]+dis)%L])?p-1:p++;
		}
		X=y;
		if(p>=L)break;
		int *tmp=x;x=y,y=tmp;
		kind=p;
	}
}
int solve(int *x)
{
	for(int i=0;i<L;i++)printf(" %d",x[i]);puts("");
	for(int i=0;i<L;i++)if(x[i]==0)return i;
	return -1;
	termin("0 isn't existed\n");
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%s",&L,STR);
		buildSA();
		printf("%d\n",solve(X));
	}
	return 0;
}

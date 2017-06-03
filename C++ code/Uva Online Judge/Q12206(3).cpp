#include<cstdio>
#include<cstdlib>
int N,M,TARRY[4][40000],SA[40000];
char STR[40000];
void build_SA()
{
	int *x=TARRY[0],*y=TARRY[1],*c=TARRY[2];
	int m=26;
	for(int i=0;i<m;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=STR[i]-'a']++;
	for(int i=1;i<m;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;//SA[i] is the idx at rank i
	for(int k=1;k<N;k<<=1)
	{
		int p=0;
		for(int i=N-k;i<N;i++)y[p++]=i;//x[i] is the value of i
		for(int i=0;i<N;i++)if(SA[i]>=k)y[p++]=SA[i]-k;//y[i] is the idx of rank i
		for(int i=0;i<m;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<m;i++)c[i]+=c[i-1];
		//for(int i=0;i<N;i++)printf(" %d",SA[i]);printf("\n");
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];//SA[i] is the idx at rank i
		int *t=x;
		x=y,y=t;
		p=1,x[SA[0]]=0;//cal x from y
		for(int i=1;i<N;i++)//i is rank, SA[i] is idx at rank i
		{
			x[SA[i]]=((y[SA[i]]==y[SA[i-1]]&&y[SA[i]+k]==y[SA[i-1]+k])?p-1:p++);
		}
		if(p>m)m=p;
		//if(m==N)return;
	}
}
int HEIGHT[40000],RANK[40000];
void build_HEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	int h=1;
	for(int i=0;i<N;i++)//i is idx
	{
		h--;
		int j=SA[RANK[i]-1];
		while(STR[i+h]==STR[j+h])h++;
		HEIGHT[RANK[i]]=h;
	}
}
int main()
{
	sscanf("aabaaaab\0","%s",STR);
	printf("%s\n",STR);
	N=-1;while(STR[++N]);
	build_SA();
	for(int i=0;i<N;i++)printf(" %d",SA[i]);printf("\n");
	build_HEIGHT();
	for(int i=0;i<N;i++)printf(" %d",HEIGHT[i]);printf("\n");
	return 0;
	while(scanf("%d",&M)==1)
	{
		scanf("%s",STR);
		N=-1;while(STR[++N]);
		build_SA();
	}
	return 0;
}

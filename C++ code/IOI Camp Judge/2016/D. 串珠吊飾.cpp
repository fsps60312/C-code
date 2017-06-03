#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][400000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int p=128;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=str[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int tmp=0;
		for(int i=n-move;i<n;i++)y[tmp++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[tmp++]=sa[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0;x[sa[0]]=p++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]])x[sa[i]]=p++;
			else if((sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=p++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?p-1:p++);
		}
		if(p==n)break;
	}
}
void BuildHeight(const char *str,const int n,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)ans--;
		if(rank[i]==0)height[rank[i]]=0;
		else
		{
			int j=sa[rank[i]-1];
			while(str[i+ans]==str[j+ans])ans++;
			height[rank[i]]=ans;
		}
	}
}
int SPARSE[20][400000];
void BuildSparse(const int *height,const int n)
{
	for(int i=0;i<n;i++)SPARSE[0][i]=height[i];
	for(int d=1;(1<<d)<=n;d++)for(int i=0;i+(1<<d)<=n;i++)SPARSE[d][i]=min(SPARSE[d-1][i],SPARSE[d-1][i+(1<<(d-1))]);
}
int QuerySparse(const int a,const int b)
{
	if(a>b)return QuerySparse(b,a);
	int d=0;
	while((1<<(d+1))<b-a)d++;
	return min(SPARSE[d][a+1],SPARSE[d][b-(1<<d)+1]);
}
int N,SA[400000],RANK[400000],HEIGHT[400000];
char S[400001];
int main()
{
//	BuildSa("aabaaaab",8,SA);
//	for(int i=0;i<8;i++)printf("%d ",SA[i]);puts("");
//	BuildHeight("aabaaaab",8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);puts("");
//	return 0;
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		N=-1;while(S[++N]);
		for(int i=N;i<N*2;i++)S[i]=S[i-N];
		for(int i=0;i<N*2;i++)S[N*4-1-i]=S[i];
		S[N*4]='\0';
		BuildSa(S,N*4,SA),BuildHeight(S,N*4,SA,RANK,HEIGHT);
		BuildSparse(HEIGHT,N*4);
		int ans=0;
		for(int i=0;i<N/2;i++)getmax(ans,QuerySparse(RANK[i],RANK[i+N/2]));
		for(int i=0;i<N;i++)getmax(ans,QuerySparse(RANK[i],RANK[N*3-i]));
		printf("%d\n",min(ans,N/2));
	}
	return 0;
}

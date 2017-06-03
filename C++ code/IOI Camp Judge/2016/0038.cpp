#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
void getmax(int &a,const int b){if(b>a)a=b;}
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][200001];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2],p=128;
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
		p=0,x[sa[0]]=p++;
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
		if(rank[i]==0)height[0]=0;
		else
		{
			const int j=sa[rank[i]-1];
			while(str[i+ans]==str[j+ans])ans++;
			height[rank[i]]=ans;
		}
	}
}
int SA[200001],RANK[200001],HEIGHT[200001];
int N,MID,M,COST[26];
char A[100001],B[100001];
int SUM[200002];
int main()
{
//	freopen("in.txt","r",stdin);
//	BuildSa("aabaaaab",8,SA);
//	for(int i=0;i<8;i++)printf("%d ",SA[i]);puts("");
//	BuildHeight("aabaaaab",8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);puts("");
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&M);
		for(int i=0;i<M;i++)scanf("%d",&COST[i]);
		scanf("%s%s",A,B);
		if(true)
		{
			int i;
			static char str[200002];
			SUM[0]=0;
			for(i=0;A[i];i++)str[i]=A[i],SUM[i+1]=SUM[i]+COST[A[i]-'a'];
			str[i]=1;
			MID=++i;
			for(;B[i-MID];i++)str[i]=B[i-MID],SUM[i+1]=SUM[i]+COST[B[i-MID]-'a'];
			str[N=i]='\0';
			BuildSa(str,N,SA),BuildHeight(str,N,SA,RANK,HEIGHT);
			MID--;
//			puts(str);
		}
		//mid does not contain special charactor, need min(...,...)
//		for(int i=0;i<=N;i++)printf("%d ",SUM[i]);puts("");
		int ans=0;
		for(int i=1;i<N;i++)
		{
			if(SA[i-1]==MID||SA[i]==MID)continue;
			if((SA[i-1]<MID)!=(SA[i]<MID))
			{
				int a=i-1,b=i;
				if(SA[a]>=MID)swap(a,b);
				assert(SA[a]<MID);
//				printf("h=%d\n",HEIGHT[i]);
				const int len=min(MID-SA[a],HEIGHT[i]);
				getmax(ans,SUM[SA[a]+len]-SUM[SA[a]]);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

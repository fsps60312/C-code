#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
void BuildSa(const char *str,const int n,int *sa) 
{
	int tmp[3][90001];
	int k=256,*x=tmp[0],*y=tmp[1],*c=tmp[2];
	for(int i=0;i<k;i++)c[i]=0;
	for(int i=0;i<n;i++)c[x[i]=str[i]]++;
	for(int i=1;i<k;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int p=0;
		for(int i=n-move;i<n;i++)y[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[p++]=sa[i]-move;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<n;i++)c[x[i]]++;
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		k=0,x[sa[0]]=k++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]])x[sa[i]]=k++;
			else if((sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=k++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?k-1:k++);
		}
		if(k==n)break;
	}
}
void BuildHeight(const char *str,const int n,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)ans--;
		if(rank[i]==0){height[0]=0;continue;}
		const int j=sa[rank[i]-1];
		while(str[i+ans]==str[j+ans])ans++;
		height[rank[i]]=ans;
	}
}
int N,SA[90000],RANK[90000],HEIGHT[90000];
char S[90001];
typedef long long LL;
LL SUM[90000];
int main()
{
//	BuildSa("aabaaaab",8,SA);
//	BuildHeight("aabaaaab",8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",SA[i]);puts("");
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);puts("");return 0;
//	freopen("in.txt","r",stdin);
	scanf("%s",&S);
	N=-1;while(S[++N]);
	BuildSa(S,N,SA);
	BuildHeight(S,N,SA,RANK,HEIGHT);
	SUM[0]=N-SA[0];
	for(int i=1;i<N;i++)
	{
		SUM[i]=SUM[i-1];
		SUM[i]+=(N-SA[i]-HEIGHT[i]);
	}
	int querycount;scanf("%d",&querycount);
	for(LL k;querycount--;)
	{
		scanf("%lld",&k);
		const int loc=lower_bound(SUM,SUM+N,k)-SUM;
		assert(0<=loc&&loc<N);
		const int cut=SUM[loc]-k;
		for(int i=SA[loc];i<N-cut;i++)putchar(S[i]);puts("");
	}
}

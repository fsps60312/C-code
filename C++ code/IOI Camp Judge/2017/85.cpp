#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int MAX_N=100000;
void BuildSA(const int n,const char *s,int *sa)
{
	static int tmp[3][MAX_N],*x=tmp[0],*y=tmp[1],*c=tmp[2];
	int w=256;
	for(int i=0;i<w;i++)c[i]=0;
	for(int i=0;i<n;i++)++c[x[i]=s[i]];
	for(int i=1;i<w;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int p=0;
		for(int i=n-move;i<n;i++)y[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[p++]=sa[i]-move;
		assert(p==n);
		for(int i=0;i<w;i++)c[i]=0;
		for(int i=0;i<n;i++)++c[x[i]];
		for(int i=1;i<w;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		w=0;
		x[sa[0]]=w++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]]||(sa[i]+move<n)!=(sa[i-1]+move<n)||y[sa[i]+move]!=y[sa[i-1]+move])x[sa[i]]=w++;
			else x[sa[i]]=w-1;
		}
//		printf("move=%d,w=%d\n",move,w);
		if(w==n)return;
	}
	assert(0);
}
void BuildHeight(const int n,const char *s,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)--ans;
		if(rank[i]==0)height[0]=0;
		else
		{
			const int j=sa[rank[i]-1];
			while(s[i+ans]==s[j+ans])++ans;
			height[rank[i]]=ans;
		}
	}
}
char S[MAX_N+1];
int N,SA[MAX_N],RANK[MAX_N],HEIGHT[MAX_N];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		N=-1;while(S[++N]);
		BuildSA(N,S,SA);
//		for(int i=0;i<N;i++)printf("%d ",SA[i]);puts("");
//		assert(0&&"finished");
		BuildHeight(N,S,SA,RANK,HEIGHT);
		long long ans=N;
		for(int i=1;i<N;i++)
		{
			ans+=i-HEIGHT[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}

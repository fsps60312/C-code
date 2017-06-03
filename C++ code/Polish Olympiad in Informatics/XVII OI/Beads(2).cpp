#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
using namespace std;
int *SPARSE[20],BIT[400000];
void BuildSparse(const int n,int *s)
{
	SPARSE[0]=s;
	for(int d=1;(1<<d)<n;d++)
	{
		SPARSE[d]=new int[n-(1<<d)+1];
		for(int i=1;i+(1<<d)<=n;i++)SPARSE[d][i]=min(SPARSE[d-1][i],SPARSE[d-1][i+(1<<(d-1))]);
	}
	for(int i=0,d=0;i<n;i++)
	{
		while((1<<(d+1))<=i+1)++d;
		BIT[i]=d;
	}
}
int QuerySparse(const int a,const int b)
{
	assert(a<=b);
	const int bit=BIT[b-a];
	return min(SPARSE[bit][a],SPARSE[bit][b-(1<<bit)+1]);
}
void BuildSa(const int n,const int *str,int *sa)
{
	static int tmp[3][400000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int p=n;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<n;i++)++c[x[i]=str[i]];
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int t=0;
		for(int i=n-move;i<n;i++)y[t++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[t++]=sa[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<n;i++)++c[x[i]];
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		p=0,x[sa[0]]=p++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i-1]]!=y[sa[i]]||(sa[i-1]+move<n)!=(sa[i]+move<n)||y[sa[i-1]+move]!=y[sa[i]+move])x[sa[i]]=p++;
			else x[sa[i]]=p-1;
		}
		if(p==n)break;
	}
}
void BuildHeight(const int n,const int *str,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)--ans;
		if(rank[i]==0)continue;
		const int j=sa[rank[i]-1];
		while(i+ans<n&&j+ans<n&&str[i+ans]==str[j+ans])++ans;
		height[rank[i]]=ans;
	}
}
int N,S[400000],SA[400000],RANK[400000],HEIGHT[400000];
void GetRanks(vector<int>*ranks)
{
	static vector<int>sot[400000];
	for(int gap=1;gap<=N;gap++)
	{
		for(int i=0;i*gap+gap<=N;i++)sot[min(RANK[i*gap],RANK[N*2-i*gap-gap])].push_back(gap);
	}
	for(int i=0;i<N*2;i++)
	{
		for(int j=0;j<(int)sot[i].size();j++)ranks[sot[i][j]].push_back(i);
		vector<int>().swap(sot[i]);
	}
}
int Solve(const int gap,const vector<int>&ranks)
{
	int ans=1;
	for(int i=1;i<(int)ranks.size();i++)
	{
		assert(ranks[i-1]<ranks[i]);
		if(QuerySparse(ranks[i-1]+1,ranks[i])<gap)++ans;
	}
	return ans;
}
int main()
{
	for(int i=0;i<20;i++)SPARSE[i]=NULL;
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]),--S[i];
		for(int i=N,j=N-1;i<N*2;i++,j--)S[i]=S[j];
		BuildSa(N*2,S,SA);
//		for(int i=0;i<N*2;i++)printf(" %d",SA[i]);puts("");
		BuildHeight(N*2,S,SA,RANK,HEIGHT);
		static vector<int>ranks[200001];
		GetRanks(ranks);
		BuildSparse(N*2,HEIGHT);
		int ansn=0;
		vector<int>ansk;
		for(int gap=1;gap<=N;gap++)
		{
			const int ta=Solve(gap,ranks[gap]);
//			printf("gap=%d,ta=%d\n",gap,ta);
			if(ta>ansn)ansk.clear(),ansn=ta;
			if(ta==ansn)ansk.push_back(gap);
			vector<int>().swap(ranks[gap]);
		}
		for(int i=1;(1<<i)<N*2;i++)delete[]SPARSE[i];
		printf("%d %d\n",ansn,(int)ansk.size());
		for(int i=0;i<(int)ansk.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ansk[i]);
		}
		puts("");
	}
	return 0;
}

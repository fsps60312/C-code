#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct SuffixArray
{
	int SA[500000],N;
	void BuildSuffixArray(const char *str)
	{
		static int tmp[3][500000];
		int *x=tmp[0],*y=tmp[1],*c=tmp[2];
		int k=256;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]=str[i]]++;
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
		for(int move=1;move<N;move<<=1)
		{
			int cur=0;
			for(int i=N-move;i<N;i++)y[cur++]=i;
			for(int i=0;i<N;i++)if(SA[i]>=move)y[cur++]=SA[i]-move;
			for(int i=0;i<k;i++)c[i]=0;
			for(int i=0;i<N;i++)c[x[i]]++;
			for(int i=1;i<k;i++)c[i]+=c[i-1];
			for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
			swap(x,y);
			k=0,x[SA[0]]=k++;
			for(int i=1;i<N;i++)
			{
				if(y[SA[i]]!=y[SA[i-1]]||(SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=k++;
				else x[SA[i]]=(y[SA[i]+move]==y[SA[i-1]+move]?k-1:k++);
			}
			if(k==N)break;
		}
	}
	int RANK[500000],HEIGHT[500000];
	void BuildHeight(const char *str)
	{
		for(int i=0;i<N;i++)RANK[SA[i]]=i;
		for(int i=0,ans=0;i<N;i++)
		{
			if(ans)ans--;
			if(RANK[i]==0){HEIGHT[0]=0;continue;}
			else
			{
				const int j=SA[RANK[i]-1];
				while(str[i+ans]==str[j+ans])ans++;
				HEIGHT[RANK[i]]=ans;
			}
		}
	}
	int SPARSE[20][500000];
	void BuildSparseTable()
	{
		for(int i=1;i<N;i++)SPARSE[0][i]=HEIGHT[i];
		for(int b=1;(1<<b)<N;b++)
		{
			for(int i=1;i+(1<<b)<N;i++)
			{
				SPARSE[b][i]=min(SPARSE[b-1][i],SPARSE[b-1][i+(1<<(b-1))]);
			}
		}
	}
	void Build(const char *str)
	{
		BuildSuffixArray(str);
		BuildHeight(str);
		BuildSparseTable();
	}
	int QuerySparse(const int a,const int b)
	{
		assert(a<=b);
		for(int bit=0;;bit++)if((1<<(bit+1))>(a-b+1))
		{
			return min(SPARSE[bit][a],SPARSE[bit][b-(1<<bit)+1]);
		}
	}
	int QueryLCS(const int _a,const int _b)
	{
		int a=RANK[_a],b=RANK[_b];
		if(a>b)swap(a,b);
		return QuerySparse(a+1,b);
	}
}SA;
int N;
char S[500001];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%s",&N,S);
	SA.Build(S);
	int querycount;scanf("%d",&querycount);
	for(int a,b;querycount--;)
	{
		scanf("%d%d",&a,&b),a--,b--;
		
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<algorithm>
#include<numeric>
using namespace std;
const int MAX_N=100000;
bool not_equ(int *ra,int a,int b,int k,int n)
{
	return ra[a]!=ra[b]||a+k>=n||b+k>=n||ra[a+k]!=ra[b+k];
}
void radix(int *box,int *key,int *it,int *ot,int m,int n)
{
	std::fill_n(box,m,0);
	for(int i(0);i<n;++i)box[key[i]]++;
	std::partial_sum(box,box+m,box);
	for(int i(n-1);i>=0;--i)ot[--box[key[it[i]]]]=it[i];
}
void BuildSA(int n,const char *s,int *sa,int *ra)
{
	static int box[MAX_N],tp[MAX_N];
	std::copy_n(s,n,ra);
	int k(1),m(256);
	do{
		std::iota(tp,tp+k,n-k);
		std::iota(sa+k,sa+n,0);
		radix(box,ra+k,sa+k,tp+k,m,n-k);
		radix(box,ra+0,tp+0,sa+0,m,n-0);
		tp[sa[0]]=0,m=1;
		for(int i(1);i<n;++i){
			m+=not_equ(ra,sa[i],sa[i-1],k,n);
			tp[sa[i]]=m-1;
		}
		std::copy_n(tp,n,ra);
		k*=2;
	}while(k<n&&m!=n);
}
void BuildHeight(const int n,const char *s,const int *sa,const int *rank,int *height)
{
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
int N,SA[MAX_N],RANK[MAX_N],HEIGHT[MAX_N];
char S[MAX_N+1];
typedef long long LL;
LL C(const LL l,const LL r)
{
	return (l+r)*(r-l+1)/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		N=-1;while(S[++N]);
		BuildSA(N,S,SA,RANK);
		BuildHeight(N,S,SA,RANK,HEIGHT);
//		for(int i=0;i<N;i++)printf("%d ",HEIGHT[i]);puts("");
		long long ans=C(1,N-SA[0]);
		for(int i=1;i<N;i++)
		{
			ans+=C(HEIGHT[i]+1,N-SA[i]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}

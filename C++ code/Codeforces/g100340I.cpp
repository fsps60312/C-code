#include<bits/stdc++.h>
using namespace std;
struct SuffixArray
{
	static const int maxn=6000+10;
	char s[maxn];
	int sa[maxn],rank[maxn],pri[maxn],c[maxn],n;
	void build_sa(int m)
	{
		n=(int)strlen(s);s[n++]=0;
		memset(c,0,sizeof(c));
		for(int i=0;i<n;i++) c[rank[i]=s[i]]++;
		for(int i=1;i<m;i++) c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--) sa[--c[rank[i]]]=i;

		for(int k=1;k<=n;k<<=1)
		{
			int p=0;
			for(int i=n-k;i<n;i++) pri[p++]=i;
			for(int i=0;i<n;i++) if(sa[i]>=k) pri[p++]=sa[i]-k;

			memset(c,0,sizeof(c));
			for(int i=0;i<n;i++) c[rank[pri[i]]]++;
			for(int i=1;i<m;i++) c[i]+=c[i-1];
			for(int i=n-1;i>=0;i--) sa[--c[rank[pri[i]]]]=pri[i];

			swap(pri,rank);
			p=1;rank[sa[0]]=0;
			for(int i=1;i<n;i++)
				rank[sa[i]] = pri[sa[i-1]]==pri[sa[i]] && pri[sa[i-1]+k]==pri[sa[i]+k]?p-1:p++;
			if(p>=n) break;
			m=p;
		}
	}
	int m;
	int cmp_suffix(char* pattern,int p)
	{
		return strncmp(pattern,s+sa[p],m);
	}
	int find(char* p)
	{
		m=(int)strlen(p);
		if(cmp_suffix(p,0)<0) return -1;
		if(cmp_suffix(p,n-1)>0) return -1;
		int l=0,r=n-1;
		while(r>=l)
		{
			int mid=l+(r-l)/2;
			int res=cmp_suffix(p,mid);
			if(!res) return mid;
			if(res<0) r=mid-1;
			else l=mid+1;
		}
		return -1;
	}
	int height[maxn];
	void getheight()
	{
		int k=0;
		for(int i=1;i<n;i++) rank[sa[i]]=i;
		for(int i=0;i<n-1;i++)
		{
			if(k) k--;
			int j=sa[rank[i]-1];
			while(s[i+k]==s[j+k]) k++;
			height[rank[i]]=k;
		}
	}
	int sparse[13][maxn];
	void buildsparse()
	{
		for(int i=0;i<n;i++)sparse[0][i]=height[i];
		for(int b=1;(1<<b)<=n;b++)
		{
			for(int i=0;i+(1<<b)<=n;i++)sparse[b][i]=min(sparse[b-1][i],sparse[b-1][i+(1<<(b-1))]);
		}
	}
	int querysparse(int l,int r)
	{
		if(l>r)return querysparse(r,l);
		++l;
		assert(l<=r);
		int b=0;
		while((1<<(b+1))<=r-l+1)++b;
		return min(sparse[b][l],sparse[b][r-(1<<b)+1]);
	}
	void Build()
	{
		build_sa(256);
		getheight();
		buildsparse();
	}
	int Query(const int i,const int j)
	{
		assert(i!=j);
		return querysparse(rank[i],rank[j]);
	}
}SA1,SA2;
char A[3001],B[3001];
int N,M;
struct Dp
{
	int i,j,l;
	Dp(){}
	Dp(int _i,int _j,int _l):i(_i),j(_j),l(_l){}
}DP1[3001][3001],DP2[3001][3001];
bool operator<(Dp a,Dp b){return a.l<b.l;}
Dp max(Dp a,Dp b,Dp c){return max(max(a,b),c);}
void getmax(Dp &a,Dp b){if(a<b)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("subpair.in","r",stdin);
	freopen("subpair.out","w",stdout);
	while(scanf("%s%s",A,B)==2)
	{
		N=M=-1;
		while(A[++N]);while(B[++M]);
		for(int i=0;i<N;i++)SA1.s[i]=A[i];
		SA1.s[N]=' ';
		for(int i=0;i<M;i++)SA1.s[N+1+i]=B[i];
		SA1.s[N+M+1]='\0';
		for(int i=0;i<N+M+1;i++)SA2.s[i]=SA1.s[i];
		reverse(SA2.s,SA2.s+N+M+1);
		SA2.s[N+M+1]='\0';
//		printf("%s\n%s\n",SA1.s,SA2.s);
		SA1.Build(),SA2.Build();
		Dp ans1=Dp(0,0,0),ans2=Dp(0,0,0);
		for(int i=N-1;i>=0;i--)for(int j=M-1;j>=0;j--)
		{
			DP1[i][j]=max(Dp(i,j,SA1.Query(i,N+1+j)),i==N-1?Dp(0,0,-1):DP1[i+1][j],j==M-1?Dp(0,0,-1):DP1[i][j+1]);
			DP2[i][j]=max(Dp(i,j,SA2.Query(j,M+1+i)),i==N-1?Dp(0,0,-1):DP2[i+1][j],j==M-1?Dp(0,0,-1):DP2[i][j+1]);
			getmax(ans1,DP2[i][j]);
		}
		for(int i=0;i+1<N;i++)for(int j=0;j+1<M;j++)
		{
//			printf("(%d,%d)(%d,%d)\n",i+1,j+1,N-1-i,M-1-j);
			Dp a=DP2[N-1-i][M-1-j],b=DP1[i+1][j+1];
			if(a.l+b.l>ans1.l+ans2.l)
			{
				ans1=a,ans2=b;
			}
		}
//		printf("%d\n",ans1.l+ans2.l);
//		printf("%d %d\n",ans1.l,ans2.l);
		for(int i=ans1.l-1;i>=0;i--)putchar(A[N-1-(ans1.i+i)]);puts("");
		for(int i=0;i<ans2.l;i++)putchar(A[ans2.i+i]);puts("");
	}
	return 0;
}

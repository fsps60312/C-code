#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
const int MAX_N=200002;
struct Sparse
{
	int N,S[19][MAX_N*2+2],B[MAX_N*2+3];
	void Build(const int n,const int *s)
	{
		for(int i=0;i<n;i++)S[0][i]=s[i];
		for(int b=1;b<=18;b++)for(int i=0;i+(1<<b)<=n;i++)S[b][i]=max(S[b-1][i],S[b-1][i+(1<<(b-1))]);
		for(int i=1;i<=n;i++)
		{
			int &b=B[i]=0;
			while((1<<(b+1))<=i)++b;
		}
		N=n;
	}
	int Get(const int l,const int r)const
	{
		if(l>r)return Get(r,l);
		assert(0<=l&&l<=r&&r<N);
		const int b=B[r-l+1];
		return max(S[b][l],S[b][r-(1<<b)+1]);
	}
}SZ;
void BuildSA(const int n,const char *s,int *sa)
{
	int tmp[3][MAX_N],*x=tmp[0],*y=tmp[1],*c=tmp[2];
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
		if(w==n)break;
	}
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
void BuildZ(const int n,const char *_s,int *z)
{
	static char s[MAX_N*2+2];
	s[0]='_';
	for(int i=0;i<n;i++)s[i*2+1]=_s[i],s[i*2+2]='_';
	s[n*2+1]='\0';
	z[0]=1;
	for(int i=1,mx=0;i<n*2+2;i++)
	{
		if(mx+z[mx]>i)z[i]=min(mx+z[mx]-i,z[mx*2-i]);
		else z[i]=1;
		while(z[i]<=i&&s[i-z[i]]==s[i+z[i]])++z[i];
		if(i+z[i]>=mx+z[mx])mx=i;
	}
}
int N,M,SA[MAX_N],RANK[MAX_N],HEIGHT[MAX_N],Z[MAX_N*2+2];
char S[MAX_N];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		N=-1;while(S[++N]);
		S[N]=' ';
		scanf("%s",S+N+1);
		M=-1;while(S[++M+N+1]);
//		puts(S);
		BuildSA(N+M+1,S,SA);
//		for(int i=0;i<N+M+1;i++)printf("%d ",SA[i]);puts("");
		BuildHeight(N+M+1,S,SA,RANK,HEIGHT);
//		for(int i=0;i<N+M+1;i++)printf("%d ",HEIGHT[i]);puts("");
		BuildZ(N+M+1,S,Z);
//		SH.Build(N,HEIGHT);
		SZ.Build((N+M+1)*2+2,Z);
		int ans=0;
		for(int i=1;i<N+M+1;i++)
		{
			if(HEIGHT[i]>=1&&((SA[i-1]<N&&SA[i]>N)||(SA[i]<N&&SA[i-1]>N)))
			{
				const int bl=SA[i]*2+1-1,br=(SA[i]+HEIGHT[i]-1)*2+1+1;
				int l=0,r=(br-bl)/2;
				auto f=[&](const int v)->int{return min(v,SZ.Get(bl+v,br-v)-1);};
				while(r-l>=3)
				{
					const int ml=(l+l+r)/3,mr=(l+r+r)/3;
					if(f(ml)<f(mr))l=ml;
					else r=mr;
				}
				for(int j=l;j<=r;j++)getmax(ans,f(j));
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}

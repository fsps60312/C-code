#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
void BuildSa(const char *str,const int n,int *sa)
{
	static int tmp[3][300003];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int k=128;
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
		k=0;x[sa[0]]=k++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]])x[sa[i]]=k++;
			else if((sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=k++;
			else x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?k-1:k++);
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
		if(rank[i]==0)height[rank[i]]=0;
		else
		{
			int j=sa[rank[i]-1];
			while(str[i+ans]==str[j+ans])ans++;
			height[rank[i]]=ans;
		}
	}
}
const LL MOD=1000000007LL;
char A[300001],B[300001],C[300001];
char S[300003];
int SA[300003],RANK[300003],HEIGHT[300003];
int N;
int DJ[300003],SZ[300003][3];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
LL NOW;
void Merge(int a,int b)
{
	if((a=Find(a))==(b=Find(b)))return;
	NOW-=(LL)SZ[a][0]*SZ[a][1]*SZ[a][2];
	NOW-=(LL)SZ[b][0]*SZ[b][1]*SZ[b][2];
	for(int i=0;i<3;i++)SZ[b][i]+=SZ[a][i],SZ[a][i]=0;
	NOW+=(LL)SZ[b][0]*SZ[b][1]*SZ[b][2];
	DJ[a]=b;
	NOW=(NOW%MOD+MOD)%MOD;
}
int main()
{
//	char tmp[]="aabaaaab";
//	BuildSa(tmp,8,SA),BuildHeight(tmp,8,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf("%d ",HEIGHT[i]);return 0;
//	freopen("in.txt","r",stdin);
	while(scanf("%s%s%s",A,B,C)==3)
	{
		N=0;
		int aloc,bloc;
		for(int i=0;A[i];i++)S[N++]=A[i];S[N++]=0,aloc=N;
		for(int i=0;B[i];i++)S[N++]=B[i];S[N++]=1,bloc=N;
		for(int i=0;C[i];i++)S[N++]=C[i];S[N++]=2;
		BuildSa(S,N,SA),BuildHeight(S,N,SA,RANK,HEIGHT);
		for(int i=0;i<N;i++)
		{
			DJ[i]=i;
			for(int j=0;j<3;j++)SZ[i][j]=0;
			if(SA[i]<aloc)SZ[i][0]++;
			else if(SA[i]<bloc)SZ[i][1]++;
			else SZ[i][2]++;
		}
		NOW=0LL;
		multimap<int,int,greater<int> >sot;
		for(int i=1;i<N;i++)sot.insert(make_pair(HEIGHT[i],i));//,printf("%d ",HEIGHT[i]);puts("");
		N=0;while(A[N]&&B[N]&&C[N])N++;
		static LL ans[300001];
		if(true)
		{
			auto it=sot.begin();
			for(int i=N;i>0;i--)
			{
				for(;it!=sot.end()&&(it->first)>=i;it++)Merge(it->second,(it->second)-1);
				ans[i]=NOW;
			}
		}
		for(int i=1;i<=N;i++)
		{
			if(i>1)putchar(' ');
			printf("%I64d",ans[i]);
		}
		puts("");
	}
	return 0;
}

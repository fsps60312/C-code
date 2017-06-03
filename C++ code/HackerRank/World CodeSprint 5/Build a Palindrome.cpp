#include<cstdio>
#include<cassert>
#include<string>
#include<algorithm>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
void BuildSA(const int n,const char *str,int *sa)
{
	static int tmp[3][400002];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int k=256;
	for(int i=0;i<k;i++)c[i]=0;
	for(int i=0;i<n;i++)++c[x[i]=str[i]];
	for(int i=1;i<k;i++)c[i]+=c[i-1];
	for(int i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
	for(int move=1;move<n;move<<=1)
	{
		int p=0;
		for(int i=n-move;i<n;i++)y[p++]=i;
		for(int i=0;i<n;i++)if(sa[i]>=move)y[p++]=sa[i]-move;
		for(int i=0;i<k;i++)c[i]=0;
		for(int i=0;i<n;i++)++c[x[i]];
		for(int i=1;i<k;i++)c[i]+=c[i-1];
		for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
		swap(x,y);
		k=0,x[sa[0]]=k++;
		for(int i=1;i<n;i++)
		{
			if(y[sa[i]]!=y[sa[i-1]]||(sa[i]+move<n)!=(sa[i-1]+move<n))x[sa[i]]=k++;
			else assert(sa[i]+move<n&&sa[i-1]+move<n),x[sa[i]]=(y[sa[i]+move]==y[sa[i-1]+move]?k-1:k++);
		}
		if(k==n)break;
	}
}
void BuildHeight(const int n,const char *str,const int *sa,int *rank,int *height)
{
	for(int i=0;i<n;i++)rank[sa[i]]=i;
	for(int i=0,ans=0;i<n;i++)
	{
		if(ans)--ans;
		if(rank[i]==0){height[0]=0;continue;}
		else
		{
			const int j=sa[rank[i]-1];
			while(str[i+ans]==str[j+ans])++ans;
			height[rank[i]]=ans;
		}
	}
}
int N,SA[400002],RANK[400002],HEIGHT[400002];
char S[400002];
char A[200001],B[200001];
int main()
{
//	char ttt[]="aabaaaab";
//	BuildSA(8,ttt,SA);
//	BuildHeight(8,ttt,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf(" %d",SA[i]);puts("");
//	for(int i=0;i<8;i++)printf(" %d",HEIGHT[i]);puts("");
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s%s",A,B);
		int an=-1;while(A[++an]);
		int bn=-1;while(B[++bn]);
		for(int i=0;i<an;i++)S[i]=A[i];
		S[an]=0;
		for(int i=0;i<bn;i++)S[an+1+i]=B[bn-1-i];
		S[an+1+bn]=1;
		N=an+1+bn;
		BuildSA(N,S,SA);
		BuildHeight(N,S,SA,RANK,HEIGHT);
		pair<int,pair<int,int> >ans=make_pair(-1,make_pair(0,0));
		int i1,h1,i2,h2;
		for(int i=1;i<N;i++)if(SA[i-1]!=an&&SA[i]!=an&&(SA[i-1]<an)!=(SA[i]<an)&&HEIGHT[i]>=1)
		{
			const int h=HEIGHT[i];
			const int ia=min(SA[i-1],SA[i]),ib=max(SA[i-1],SA[i]);
			if(ia+h<an&&getmax(ans,make_pair(h*2+1,make_pair(N-i,'z'-S[ia+h]))))i1=ia,h1=h+1,i2=ib,h2=h;
			if(ib+h<N&&getmax(ans,make_pair(h*2+1,make_pair(N-i,'z'-S[ib+h]))))i1=ia,h1=h,i2=ib,h2=h+1; 
			if(getmax(ans,make_pair(h*2,make_pair(i,0))))i1=ia,h1=h,i2=ib,h2=h;
		}
		if(ans.first==-1)puts("-1");
		else
		{
			for(int i=0;i<h1;i++)putchar(S[i1+i]);
			for(int i=0;i<h2;i++)putchar(S[i2+h2-1-i]);
			puts("");
		}
	}
	return 0;
}

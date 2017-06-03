#include<cstdio>
#include<cassert>
#include<string>
#include<algorithm>
#include<utility>
using namespace std;
template<class T>inline bool getmax(T&a,const T&b){return a<b?(a=b,true):false;}
void BuildSA(const int n,const char *str,int *sa)
{
	static int tmp[3][200004];
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
int MX[400008];
void BuildZ(const int n,const char *_s)
{
	static char s[400008];
	static int z[400008];
	for(int i=0;i<n;i++)s[i*2]=_s[i],s[i*2+1]=5; 
	for(int i=0;i<n*2-1;i++)MX[i]=i;
	for(int i=1,mx=0;i<n*2-1;i++)
	{
		if(mx+z[mx]-1>=i)z[i]=min(mx+z[mx]-i,z[mx-(i-mx)]);
		else z[i]=0;
		while(i+z[i]<n*2-1&&i-z[i]>=0&&s[i-z[i]]==s[i+z[i]])++z[i];
		if(i+z[i]>=mx+z[mx])mx=i;
		assert(z[i]>=1);
//		if(z[i]>1)printf("z[%d]=%d\n",i,z[i]);
		getmax(MX[i-z[i]+1],i);
	}
	for(int i=1;i<n*2-1;i++)getmax(MX[i],MX[i-1]);
}
int N,SA[200004],RANK[200004],HEIGHT[200004];
int Len(const int i)
{
	if(i*2-1>=N*2-1)return 0;
	const int len=2*(MX[i*2-1]-(i*2-1));
	return len/2;
}
char S[200005];
char A[100001],B[100001];
int main()
{
//	char ttt[]="aabaaaab";
//	BuildSA(8,ttt,SA);
//	BuildHeight(8,ttt,SA,RANK,HEIGHT);
//	for(int i=0;i<8;i++)printf(" %d",SA[i]);puts("");
//	for(int i=0;i<8;i++)printf(" %d",HEIGHT[i]);puts("");
//	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s%s",A,B);
		int an=-1;while(A[++an]);
		int bn=-1;while(B[++bn]);
		for(int i=0;i<an;i++)S[i]=A[i];
		S[an]=0,S[an+1]=1;
		for(int i=0;i<bn;i++)S[an+2+i]=B[bn-1-i];
		S[an+2+bn]=2,S[an+2+bn+1]=3;
		N=an+4+bn;
		BuildZ(N,S);
		BuildSA(N,S,SA);
		BuildHeight(N,S,SA,RANK,HEIGHT);
		pair<int,int>ans=make_pair(-1,0);
		int i1,h1,i2,h2;
		for(int i=1;i<N;i++)if((SA[i-1]<an)!=(SA[i]<an)&&HEIGHT[i]>=1)
		{
			const int h=HEIGHT[i];
			for(int j=i;j<N&&HEIGHT[j]>=HEIGHT[i]&&(SA[i]<an)==(SA[j]<an);j++)
			{
				const int ia=min(SA[i-1],SA[j]),ib=max(SA[i-1],SA[j]);
				if(S[ia+h]>5&&getmax(ans,make_pair(h*2+Len(ia+h),N-(SA[i-1]<SA[j]?i-1:j))))i1=ia,h1=h+Len(ia+h),i2=ib,h2=h;
				if(S[ib+h]>5&&getmax(ans,make_pair(h*2+Len(ib+h),N-(SA[i-1]>SA[j]?i-1:j))))i1=ia,h1=h,i2=ib,h2=h+Len(ib+h); 
				if(getmax(ans,make_pair(h*2,i-1)))i1=ia,h1=h,i2=ib,h2=h;
			}
			for(int j=i-1;j>=0&&HEIGHT[j+1]>=HEIGHT[i]&&(SA[i-1]<an)==(SA[j]<an);j--)
			{
				const int ia=min(SA[j],SA[i]),ib=max(SA[j],SA[i]);
				if(S[ia+h]>5&&getmax(ans,make_pair(h*2+Len(ia+h),N-(SA[j]<SA[i]?j:i))))i1=ia,h1=h+Len(ia+h),i2=ib,h2=h;
				if(S[ib+h]>5&&getmax(ans,make_pair(h*2+Len(ib+h),N-(SA[j]>SA[i]?j:i))))i1=ia,h1=h,i2=ib,h2=h+Len(ib+h);
				if(getmax(ans,make_pair(h*2,j)))i1=ia,h1=h,i2=ib,h2=h;
			}
		}
//		printf("%d, %s\n",Len(an+2+bn-1),&S[an+2+bn-1]);
		if(ans.first==-1)puts("-1");
		else
		{
			assert(h1+h2==ans.first&&h1>=1&&h2>=1);
			for(int i=0;i<h1;i++)putchar(S[i1+i]);//puts("");
			for(int i=0;i<h2;i++)putchar(S[i2+h2-1-i]);
			puts("");
		}
	}
	return 0;
}

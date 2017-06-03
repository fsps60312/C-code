#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N;
char A[200002],B[200002];
int Cmp(const char *a,const char *b,const int len)
{
	for(int i=0;i<len;i++)if(a[i]!=b[i])return a[i]<b[i]?-1:1;
	return 0;
}
void Sort(char *s,const int l,const int r)
{
	if((r-l+1)&1)return;
	const int mid=(l+r)/2;
	Sort(s,l,mid),Sort(s,mid+1,r);
	if(Cmp(s+l,s+mid+1,mid-l+1)>0)
	{
		for(int i=0;i<=mid-l;i++)swap(s[l+i],s[mid+1+i]);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(gets(A)&&gets(B))
	{
		for(N=0;;N++)if(A[N]=='\n'||!A[N]){A[N]=B[N]='\0';break;}
		Sort(A,0,N-1),Sort(B,0,N-1);
		puts(Cmp(A,B,N)==0?"YES":"NO");
	}
	return 0;
}

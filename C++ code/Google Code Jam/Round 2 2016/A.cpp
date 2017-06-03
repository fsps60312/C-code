#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,R,S,P;
int TMP[1<<12];
char TYPE[3]={'R','S','P'};
bool IsSmaller(const int *a,const int *b,const int n)
{
	for(int i=0;i<n;i++)if(a[i]!=b[i])return TYPE[a[i]]<TYPE[b[i]];
	return false;
}
void Build(const int l,const int r,const int val)
{
	if(l==r){TMP[l]=val;return;}
	const int mid=(l+r)/2;
	Build(l,mid,val);
	Build(mid+1,r,(val+1)%3);
	if(!IsSmaller(TMP+l,TMP+mid+1,r-mid))
	{
		for(int i=l,j=mid+1;i<=mid;i++,j++)swap(TMP[i],TMP[j]);
	}
}
bool Solve()
{
	for(int i=0;i<3;i++)
	{
		Build(0,N-1,i);
		int cnt[3]={0,0,0};
		for(int j=0;j<N;j++)cnt[TMP[j]]++;
		assert(cnt[0]+cnt[1]+cnt[2]==N);
		if(cnt[0]==R&&cnt[1]==S&&cnt[2]==P)return true;
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d%d",&N,&R,&P,&S);
		N=1<<N;
		static int kase=0;
		printf("Case #%d: ",++kase);
		if(!Solve())puts("IMPOSSIBLE");
		else
		{
			for(int i=0;i<N;i++)putchar(TYPE[TMP[i]]);
			puts("");
		}
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
using namespace std;
int N;
struct Dot
{
	int x,y;
}DOT[100000];
bool Cmpx(const Dot &a,const Dot &b){return a.x<b.x;}
int DP[100000],ANS[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0,t,s;i<N;i++)
	{
		scanf("%d%d",&s,&t);
		DOT[i].x=t+s;
		DOT[i].y=t-s;
	}
	sort(DOT,DOT+N,Cmpx);
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int l=0,r=ans,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(DOT[i].y<DP[mid])l=mid+1;
			else r=mid;
		}
		DP[l]=DOT[i].y;
		if(l==ans)ans++;
		ANS[i]=l+1;
	}
	printf("%d\n",ans);
//	for(int i=0;i<N;i++)printf("dot:%d %d %d\n",DOT[i].x,DOT[i].y,ANS[i]);
	for(int i=0;i<N;i++)printf("%d %d %d\n",(DOT[i].x-DOT[i].y)/2,(DOT[i].x+DOT[i].y)/2,ANS[i]);
	return 0;
}

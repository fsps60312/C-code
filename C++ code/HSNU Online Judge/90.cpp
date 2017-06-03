#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int N,K,GRID[2001][2001];
LL SUM[2001][2001];
int H[2001][2002],L[2001],R[2001];
LL Sum(const int y1,const int y2,const int x1,const int x2){return SUM[y2][x2]-SUM[y1-1][x2]-SUM[y2][x1-1]+SUM[y1-1][x1-1];}
struct Deq
{
	int s[2001],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int back(){return s[r];}
	int front(){return s[l];}
	bool empty(){return r<l;}
}DEQ;
bool Solve(int &y1,int &y2,int &x1,int &x2)
{
//	for(int i=1;i<=N;i++)
//	{
//		for(int j=1;j<=N;j++)printf(" %d",H[i][j]);
//		puts("");
//	}
	for(int i=1;i<=N;i++)
	{
//		printf("i=%d,K=%lld\n",i,K);
		int *h=H[i];
//		printf("H[%d]:",i);for(int j=1;j<=N;j++)printf(" %d",h[j]);puts("");
		h[0]=-1;
		DEQ.clear();DEQ.push_back(0);
		for(int j=1;j<=N;j++)
		{
			while(!DEQ.empty()&&h[DEQ.back()]>=h[j])DEQ.pop_back();
			L[j]=DEQ.back()+1;
			DEQ.push_back(j);
		}
		h[N+1]=-1;
		DEQ.clear();DEQ.push_back(N+1);
		for(int j=N;j>=1;j--)
		{
			while(!DEQ.empty()&&h[DEQ.back()]>=h[j])DEQ.pop_back();
			R[j]=DEQ.back()-1;
			DEQ.push_back(j);
		}
//		printf("L[%d]:",i);for(int j=1;j<=N;j++)printf(" %d",L[j]);puts("");
//		printf("R[%d]:",i);for(int j=1;j<=N;j++)printf(" %d",R[j]);puts("");
		for(int j=1;j<=N;j++)
		{
			if(h[j]==0)continue;
			y1=i-h[j]+1,y2=i,x1=L[j],x2=R[j];
			LL sum=Sum(y1,y2,x1,x2);
//			printf("K=%lld,Sum(%d,%d,%d,%d)=%lld\n",K,y1,y2,x1,x2,Sum(y1,y2,x1,x2));
			if(sum>=K)
			{
//				puts("pass");
				int mid;
				while(y1<y2&&Sum(y1,y2,x1,x2)>K*2LL)
				{
					mid=(y1+y2)/2;
					if(Sum(y1,mid,x1,x2)>=K)y2=mid;
					else y1=mid+1;
//					printf("K=%lld,Sum(%d,%d,%d,%d)=%lld\n",K,y1,y2,x1,x2,Sum(y1,y2,x1,x2));
				}
				while(x1<x2&&Sum(y1,y2,x1,x2)>K*2LL)
				{
					mid=(x1+x2)/2;
					if(Sum(y1,y2,x1,mid)>=K)x2=mid;
					else x1=mid+1;
//					printf("K=%lld,Sum(%d,%d,%d,%d)=%lld\n",K,y1,y2,x1,x2,Sum(y1,y2,x1,x2));
				}
				assert(Sum(y1,y2,x1,x2)>=K&&Sum(y1,y2,x1,x2)<=K*2LL);
				return true;
			}
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&K,&N)==2)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)scanf("%d",&GRID[i][j]);
		for(int i=0;i<=N;i++)SUM[i][0]=SUM[0][i]=0LL;
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)SUM[i][j]=GRID[i][j]+SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1];
		for(int i=1;i<=N;i++)
		{
			H[0][i]=0;
			for(int j=1;j<=N;j++)H[j][i]=(GRID[j][i]>K*2?0:H[j-1][i]+1);
		}
		int y1,y2,x1,x2;
		if(Solve(y1,y2,x1,x2))printf("%d %d %d %d\n",x1,y1,x2,y2);
		else puts("NIE");
	}
	return 0;
}

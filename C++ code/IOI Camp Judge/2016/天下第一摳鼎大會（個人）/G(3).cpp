#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
struct Deq
{
	int s[10000],l,r;
	void clear(){l=0,r=-1;}
	int size(){return r-l+1;}
	int back(const int i){return s[r-i];}
	int front(const int i){return s[l+i];}
	void pop_front(){l++;}
	void pop_back(){r--;}
	void push_back(const int v){s[++r]=v;}
}DEQ;
int N,K;
LL S[10000],SUM0[10001],SUM1[10001],*B;
LL GetA(const int j){return j;}
LL GetB(const int j){return B[j-1]+SUM1[j];}
double GetX(const int j0,const int j1){return (double)(GetB(j1)-GetB(j0))/(double)(GetA(j0)-GetA(j1));}
LL GetF(const int j,const LL x){return GetA(j)*x+GetB(j);}
//ax+b=Ax+B
//(a-A)x=B-b
//x=(B-b)/(a-A)
//a=j,b=B[j-1]+SUM1[j]
//A[i]=max(a*SUM0[i+1]+b)-SUM1[i+1]-i*SUM0[i+1]-SUM0[i+1]
LL Score(const int l,const int r)
{
	return SUM1[l]-SUM1[r+1]-(LL)(r-l+1LL)*SUM0[r+1];
}
void Solve(LL *A,LL *_B,const int start)
{
	B=_B;
	DEQ.clear();DEQ.push_back(start+1);
	for(int i=start+1;i<N;i++)
	{
		while(DEQ.size()>=2&&GetX(DEQ.front(0),DEQ.front(1))<=SUM0[i+1])DEQ.pop_front();
		A[i]=GetF(DEQ.front(0),SUM0[i+1])-SUM1[i+1]-(LL)i*SUM0[i+1]-SUM0[i+1];
		assert(A[i]==B[DEQ.front(0)-1]+Score(DEQ.front(0),i));
		while(DEQ.size()>=2&&GetX(DEQ.back(0),i+1)<=GetX(DEQ.back(1),DEQ.back(0)))DEQ.pop_back();
		DEQ.push_back(i+1);
	}
}
LL DP[101][10000];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&K);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		SUM0[N]=SUM1[N]=0LL;
		for(int i=N-1;i>=0;i--)SUM0[i]=S[i]+SUM0[i+1],SUM1[i]=SUM0[i]+SUM1[i+1];
		for(int i=0;i<N;i++)DP[1][i]=Score(0,i);
		for(int i=2;i<=K;i++)
		{
			//DP[i][j]=max(DP[i-1][k-1]+Score(k,j))
			//A[i]=max(B[j-1]+Score(j,i))
			//A[i]=max(B[j-1]+SUM1[j]-SUM1[i+1]-(i-j+1)*SUM0[i+1])
			//A[i]=max(B[j-1]+SUM1[j]+j*SUM0[i+1])-SUM1[i+1]-i*SUM0[i+1]-SUM0[i+1]
			//a=j,b=B[j-1]+SUM1[j]
			//A[i]=max(a*SUM0[i+1]+b)-SUM1[i+1]-i*SUM0[i+1]-SUM0[i+1]
			for(int j=0;j<N;j++)DP[i][j]=0LL;
			Solve(DP[i],DP[i-1],i-2);
		}
		for(int i=1;i<=K;i++)
		{
			if(i>1)putchar(' ');
			printf("%lld",DP[i][N-1]);
		}
		puts("");
	}
	return 0;
}

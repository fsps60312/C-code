#include<cstdio>
#include<cassert>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Deque
{
	int s[3001],l,r;
	void clear(){l=0,r=-1;}
	bool empty(){return r<l;}
	void push(const int v){s[++r]=v;}
	int pop(){return s[r--];}
	int top(){return s[r];}
}DEQ;
int Solve(const int N,const int *H)
{
	int ans=0;
	static int left[3001];
	DEQ.clear(),DEQ.push(0);
	for(int i=1;i<=N;i++)
	{
		while(H[DEQ.top()]>=H[i])DEQ.pop();
		left[i]=DEQ.top();
		DEQ.push(i);
	}
	DEQ.clear(),DEQ.push(N+1);
	for(int i=N;i>=1;i--)
	{
		while(H[DEQ.top()]>=H[i])DEQ.pop();
		const int right=DEQ.top();
		DEQ.push(i);
		getmax(ans,H[i]*(right-left[i]-1));
	}
	return ans;
}
int R,C,H[3000][3002];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(2,"%d%d",&R,&C);
	for(int i=0;i<R;i++)for(int j=1;j<=C;j++)scanf(1,"%d",&H[i][j]);
	for(int i=1;i<R;i++)for(int j=1;j<=C;j++)if(H[i][j])H[i][j]+=H[i-1][j];
	int ans=0;
	for(int i=0;i<R;i++)H[i][0]=H[i][C+1]=-1,getmax(ans,Solve(C,H[i]));
	printf("%d\n",ans);
	return 0;
}

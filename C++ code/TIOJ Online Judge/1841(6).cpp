#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Stack
{
	vector<int>data;
	int last;
	void clear(){data.clear(),last=-1;}
	void push(const int v){data.push_back(v),last++;}
	void pop(){data.pop_back(),last--;}
	int top()const{return data[last];}
	int lower_bound(const int v)
	{
		int l=0,r=last+1;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(data[mid]>=v)l=mid+1;
			else r=mid;
		}
		assert(r<=last);
		return data[r];
	}
}STK;
int N;
LL SUM[1000002];
int RIGHT[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%lld",&SUM[i]),SUM[i]+=SUM[i-1];
		STK.clear();
		SUM[N+1]=-INF,STK.push(N+1);
		for(int i=N;i>=0;i--)
		{
			while(SUM[i]<=SUM[STK.top()])STK.pop();
			RIGHT[i]=STK.top();
			STK.push(i);
		}
		int ans=0;
		STK.clear();
		SUM[N+1]=INF,STK.push(N+1);
		for(int i=N;i>=0;i--)
		{
			while(SUM[i]>SUM[STK.top()])STK.pop();
			STK.push(i);
			getmax(ans,STK.lower_bound(RIGHT[i])-i);
		}
		printf("%d\n",ans);
	}
	return 0;
}

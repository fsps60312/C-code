#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
void getmax(int &a,const int b){if(b>a)a=b;}
LL SUM[1000001];
int N,K,S[1000001];
int Solve()
{
	SUM[0]=0LL;
	for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+(S[i]-K);
	int ans=0;
	static vector<int>deq;deq.clear();
	deq.push_back(0);
	for(int i=1,back=0;i<=N;i++)
	{
		if(SUM[i]<SUM[back])deq.push_back(back=i);
		else
		{
			int l=0,r=(int)deq.size()-1;
			while(l<r)
			{
				const int mid=(l+r)/2;
				if(SUM[deq[mid]]<=SUM[i])r=mid;
				else l=mid+1;
			}
			assert(SUM[deq[r]]<=SUM[i]);
			getmax(ans,i-deq[r]);
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int querycount;
	scanf(2,"%d%d",&N,&querycount);
	for(int i=1;i<=N;i++)scanf(1,"%d",&S[i]);
	for(int qcnt=0;qcnt<querycount;qcnt++)
	{
		if(qcnt)putchar(' ');
		scanf(1,"%d",&K);
		printf("%d",Solve());
	}
	puts("");
	return 0;
}

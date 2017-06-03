#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Stk
{
	int s[100000],r;
	void clear(){r=-1;}
	void push(const int v){s[++r]=v;}
	void pop(){r--;}
	int top()const{return s[r];}
	bool empty()const{return r==-1;}
	int operator[](const int i)const{return s[i];}
}STK;
int N,S[100000],H[99999];
LL SUM[99999];
int main()
{
//	freopen("in.txt","r",stdin);
	for(int querycount;scanf("%d%d",&N,&querycount)==2;)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=0;i+1<N;i++)H[i]=abs(S[i]-S[i+1]);
		for(int l,r;querycount--;)
		{
			scanf("%d%d",&l,&r),l--,r-=2;
			STK.clear(),STK.push(l);
			LL ans=SUM[l]=H[l];
			for(int i=l+1;i<=r;i++)
			{
				while(!STK.empty()&&H[i]>=H[STK.top()])STK.pop();
				if(STK.empty())SUM[i]=(i-l+1LL)*H[i];
				else SUM[i]=SUM[STK.top()]+(LL)(i-STK.top())*H[i];
				STK.push(i);
				ans+=SUM[i];
			}
			printf("%I64d\n",ans);
		}
	}
	return 0;
}

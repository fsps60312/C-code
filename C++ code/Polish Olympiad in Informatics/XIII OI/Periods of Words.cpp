#include<cstdio>
#include<cassert>
#include<algorithm>
#include<stack>
using namespace std;
int N,Z[1000000];
char S[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%s",&N,S);
	Z[0]=0;
	stack<int>stk;
	long long ans=0;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-1-i+1,Z[i-mx]);
		else Z[i]=0;
		while(S[i+Z[i]]==S[Z[i]])Z[i]++;
		if(i+Z[i]>=mx+Z[mx])mx=i;
		while(!stk.empty()&&stk.top()+Z[stk.top()]-1<=i+Z[i]-1)stk.pop();
		stk.push(i);
		while(!stk.empty()&&stk.top()+Z[stk.top()]-1<i)stk.pop();
		if(!stk.empty()&&i<(stk.top()+1)*2)ans+=stk.top();//,printf("len=%d,ans=%d\n",i+1,stk.top());
	}
	printf("%lld\n",ans);
	return 0;
}

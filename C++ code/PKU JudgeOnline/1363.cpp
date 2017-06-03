#include<cstdio>
#include<cassert>
#include<stack>
#include<queue>
using namespace std;
int N,A[1000];
queue<int>S;
stack<int>STK;
bool GetA()
{
	scanf("%d",&A[0]);
	if(A[0]==0)return false;
	for(int i=1;i<N;i++)scanf("%d",&A[i]);
	while(!S.empty())S.pop();
	for(int i=1;i<=N;i++)S.push(i);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		while(GetA())
		{
			while(!STK.empty())STK.pop();
			int cur=0;
			while(!S.empty())
			{
				STK.push(S.front()),S.pop();
				while(!STK.empty()&&STK.top()==A[cur])STK.pop(),cur++;
			}
			puts(cur==N?"Yes":"No");
		}
		puts("");
	}
	return 0;
}

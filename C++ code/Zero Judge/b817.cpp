#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,K1,K2;
int main()
{
	scanf("%d",&N);
	queue<int>A,B;
	scanf("%d",&K1);
	for(int i=0,v;i<K1;i++)scanf("%d",&v),A.push(v);
	scanf("%d",&K2);
	for(int i=0,v;i<K2;i++)scanf("%d",&v),B.push(v);
	int ans=0;
	while(!A.empty()&&!B.empty())
	{
		int a=A.front();
		A.pop();
		int b=B.front();
		B.pop();
		if(a>b)
		{
			A.push(b);
			A.push(a);
		}
		else
		{
			B.push(a);
			B.push(b);
		}
		ans++;
	}
	printf("%d ",ans);
	if(B.empty())printf("1\n");
	else printf("2\n");
	return 0;
}

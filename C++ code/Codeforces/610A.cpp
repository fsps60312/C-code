#include<cstdio>
#include<cassert>
using namespace std;
int Solve(int n)
{
	if(n%2==1)return 0;
	n/=2;
	if(n%2==0)return n/2-1;
	else return n/2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int n;scanf("%d",&n)==1;)
	{
		printf("%d\n",Solve(n));
	}
	return 0;
}

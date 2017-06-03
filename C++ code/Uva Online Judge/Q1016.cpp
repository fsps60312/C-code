#include<cstdio>
#include<vector>
using namespace std;
#define min(x,y) (x<y?x:y)
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int N;
vector<int> V;
int solve(int &sum,int &mn1,int &mn2,int &p)
{
	if(p>0)return (N-2)*mn1+sum;
	return min((N-2)*mn2+sum,mn1+mn2+(N-2)*mn1+sum);
}
int main()
{
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
//		if(N>100)termin();
		int sum=0,mn1=1000,mp=-1,mn2=1000;
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			sum+=v;
			if(v<mn1)mp=i,mn2=mn1,mn1=v;
			else if(v<mn2)mn2=v;
		}
		printf("Case %d: %d\n\n",kase++,solve(sum,mn1,mn2,mp));
	}
	return 0;
}

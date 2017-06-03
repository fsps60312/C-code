#include<cstdio>
#include<cmath>
#include<cassert>
#include<vector>
using namespace std;
int N,X,Y;
const double LogTwo=log(2.0);
vector<double>LEVEL;
double Level(const int i)
{
	if(i<(int)LEVEL.size())return LEVEL[i];
	LEVEL.push_back(Level(i-1)+log(i));
//	printf("level %d=%.9f\n",i,exp(LEVEL[i]));
	return LEVEL[i];
}
double F(const int a,const int b)
{
	const double ans=exp(Level(a)-Level(b)-Level(a-b)-a*LogTwo);
//	printf("F(%d,%d)=%.9f\n",a,b,ans);
	return ans;
}
double Solve()
{
	//1,6,15,28
	int v=sqrt(N*2);
	if(v*(v+1)/2>N)v--;
	assert(v*(v+1)/2<=N&&(v+1)*(v+2)/2>N);
	if(v%2==0)v--;
	const int remain=N-v*(v+1)/2;
//	printf("v=%d\n",v);
	if(v-1>=X+Y)return 1.0;
	else if(v+1<X+Y)return 0.0;
//	puts("pass");
	if(Y==v+1)return false;
	double ans=1.0;
	for(int i=0;i<=Y&&i<=remain;i++)if(remain-i<=v+1||i+(v+1)-(remain-i)<=Y)ans-=F(remain,i);
	return ans;
}
int main()
{
	LEVEL.push_back(0.0);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d%d%d",&N,&X,&Y);
		if(X<0)X=-X;
		if((X+Y)%2==1)
		{
			if(Y==0)X--;
			else Y--;
		}
		printf("%.9f\n",Solve());
	}
	return 0;
}
/*
5 1 2
*/

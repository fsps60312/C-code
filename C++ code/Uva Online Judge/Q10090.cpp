#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long LL;
void ExGcd(const LL a,const LL b,LL &g,LL &x,LL &y)
{
	if(b==0){g=a,x=1,y=0;return;}
	ExGcd(b,a%b,g,y,x);
	y-=a/b*x;
}
LL N,C1,N1,C2,N2;
bool Solve(LL &m1,LL &m2)
{
	LL g,x,y;
	ExGcd(N1,N2,g,x,y);
	if(N%g)return false;
	m1=x*N/g,m2=y*N/g;
	LL v1=N1/g,v2=N2/g;
	//N1*x+N2*y=N;
	LL move=(m2>=0?-m2/v1:(-m2-1)/v1+1);
	m2+=move*v1,m1-=move*v2;
	assert(m2>=0&&m2-v1<0&&N1*m1+N2*m2==N);
	return m1>=0;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1&&N)
	{
		scanf("%lld%lld%lld%lld",&C1,&N1,&C2,&N2);
		bool swaped=false;
		if(C1*N2>C2*N1)swap(C1,C2),swap(N1,N2),swaped=true;
		LL m1,m2;
		if(Solve(m1,m2))printf("%lld %lld\n",swaped?m2:m1,swaped?m1:m2);
		else puts("failed");
	}
	return 0;
}

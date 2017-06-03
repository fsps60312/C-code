//a*c-2*b*d=x
//a*d+b*c=y
//dx-cy=b*c*c-2*b*d*d
//(2*b)*d*d+(x)*d-(c*y+b*c*c)=0
//d=(-x+sqrt(x*x+8*b*b*c*c+8*b*c*y))/(4*b)
//(x,y) is divisible by (a,b)
//(x,y)/(a,b)=(c,d)
//(a)c-(2*b)d=x
//(b)c+(a)d=y
//(ab)c-(2bb)d=x
//(ab)c-(aa)d=y
//(aa)c-(2ab)d=x
//(2bb)c+(2ab)d=y
//(aa-2bb)d=x-y
//(aa+2bb)c=x+y

//Example(3,4)
//(aa-2bb)d=-1
//(aa+2bb)c=7
#include<cstdio>
#include<vector>
#include<cassert>
#include<cmath>
using namespace std;
int T,A,B;
vector<int>FA,FB;
void GetFactor(const int n,vector<int>&f)
{
	assert(n>0);
	f.clear();
	for(int i=1;i*i<=n;i++)if(n%i==0)f.push_back(i),f.push_back(n/i),f.push_back(-i),f.push_back(-n/i);
}
bool IsSq(const int v)
{
	int l=0,r=46340;//sqrt(2147483647)
	while(l<r)
	{
		const int mid=(l+r)/2;
		if(mid*mid<v)l=mid+1;
		else r=mid;
	}
	return l*l==v; 
}
//(aa-2bb)d=x-y
//(aa+2bb)c=x+y
bool Solve()
{
	if(A==0)return B>1||B<-1;
	if(B==0)
	{
		for(int i=2;i*i<=A;i++)if(A%i==0)return true;
		return false;
	}
	if(A-B==0||A+B==0)return A>1||A<-1;
	GetFactor(abs(A-B),FA),GetFactor(abs(A+B),FB);
	for(int i=0;i<FA.size();i++)for(int j=0;j<FB.size();j++)
	{
		const int va=FA[i]+FB[j],vb=FB[j]-FA[i];
		if(va<=0||va%2!=0||vb<=0||vb%4!=0)continue;
		if(IsSq(va/2)&&IsSq(vb/4))
		{
//			printf("(%d,%d)*(%d,%d),FA=%d,FB=%d\n",(int)(sqrt(va/2)+0.5),(int)(sqrt(vb/4)+0.5),(A-B)/FA[i],(A+B)/FB[j],FA[i],FB[j]);
			return true;
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&A,&B);
//		printf("A=%d,B=%d\n",A,B);
		puts(!Solve()?"Yes":"No");
	}
	return 0;
}

#include<cstdio>
#include<cassert>
using namespace std;
int C(int a,int b)
{
	if(b>a)return 0;
	int ans=1;
	for(int i=b+1;i<=a;i++)ans*=i,ans/=i-b;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int ans=0;
	for(int i=0;i<=10;i++)ans+=C(12,i);
	printf("%d\n",ans);
	return 0;
}

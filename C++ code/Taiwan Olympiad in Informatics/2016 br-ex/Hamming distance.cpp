#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef UI unsigned int;
int N,S[80];
void getmax(int &a,const int b){if(b>a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int ans=0;
		for(int i1=0;i1<31;i1++)for(int i2=i1+1;i2<31;i2++)for(int i3=i2+1;i3<31;i3++)for(int i4=i3+1;i4<31;i4++)
		{
			map<int,int>cnt;
			const int v=(1<<i1)|(1<<i2)|(1<<i3)|(1<<i4);
			for(int i=0;i<N;i++)getmax(ans,++cnt[S[i]&(~v)]);
		}
		printf("%d\n",ans);
	}
	return 0;
}

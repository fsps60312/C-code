#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef unsigned int UI;
const int BITCNT=32;
const UI ONE=1;
int N;
UI S[80];
void getmax(int &a,const int b){if(b>a)a=b;}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%u",&S[i]);
		int ans=0;
		for(int i1=0;i1<BITCNT;i1++)for(int i2=i1+1;i2<BITCNT;i2++)for(int i3=i2+1;i3<BITCNT;i3++)for(int i4=i3+1;i4<BITCNT;i4++)
		{
			map<UI,int>cnt;
			const UI v=(ONE<<i1)|(ONE<<i2)|(ONE<<i3)|(ONE<<i4);
			for(int i=0;i<N;i++)++cnt[S[i]&(~v)];
			getmax(ans,(int)cnt.size());
		}
		printf("%d\n",ans);
	}
	return 0;
}

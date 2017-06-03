#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,CONFIDENCE[100000],HOST[100000],PROTOCOL[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&CONFIDENCE[i]);
		for(int i=1;i<N;i++)scanf("%d%d",&HOST[i],&PROTOCOL[i]);
		int cnt=0;
		for(int i=N-1;i>=1;i--)
		{
			const int v=CONFIDENCE[i];
			switch(PROTOCOL[i])
			{
				case 0:cnt+=v,CONFIDENCE[HOST[i]]=max(0,CONFIDENCE[HOST[i]]-v);break;
				case 1:CONFIDENCE[HOST[i]]+=v;break;
				case 2:getmax(CONFIDENCE[HOST[i]],v);break;
				default:assert(0);break;
			}
		}
		printf("%d\n",cnt+CONFIDENCE[0]);
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,S[2001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=1;i<=N;i++)scanf("%d",&S[i]);
	int place_1,place_N;
	for(int i=1;i<=N;i++)
	{
		if(S[i]==1)place_1=i;
		if(S[i]==N)place_N=i;
	}
	printf("%d\n",max(max(place_1-1,N-place_1),max(place_N-1,N-place_N)));
	return 0;
}

#include<cstdio>
#include<cassert>
using namespace std;
char S[501];
int CNT[27],N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		for(int i=0;i<27;i++)CNT[i]=0;
		for(N=0;S[N];N++)++CNT[S[N]-'a'];
		int sum=0;
		for(int i=0;;i++)
		{
			if(CNT[i]==0)
			{
				puts(sum==N?"YES":"NO");
				break;
			}
			sum+=CNT[i];
		}
	}
	return 0;
}

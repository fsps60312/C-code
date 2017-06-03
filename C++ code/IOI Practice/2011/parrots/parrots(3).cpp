#include "grader.h"
#include<map>
using namespace std;

void decode(int N, int L, int X[])
{
	map<int,int>s;
	for(int i=0;i<L;i++)++s[X[i]];
	int cur=0,now=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<8;j+=2,cur++)
		{
			now^=s[cur]<<j;
		}
		output(now);
	}
}
void encode(int N, int M[])
{
	int cur=0,now=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<8;j+=2,cur++)
		{
			int cnt=((now^M[i])>>j)&3;
			for(int k=0;k<cnt;k++)send(cur);
			now^=cnt<<j;
		}
	}
}

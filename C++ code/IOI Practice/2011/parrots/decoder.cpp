#include "decoder.h"
#include "decoderlib.h"
#include<set>
using namespace std;
void decode(int N, int L, int X[])
{
	set<int>s;
	for(int i=0;i<L;i++)s.insert(X[i]);
	int cur=0,now=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<8;j++,cur++)
		{
			if(s.find(cur)!=s.end())now^=(1<<j);
		}
		output(now);
	}
}

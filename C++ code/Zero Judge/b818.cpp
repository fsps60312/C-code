#include<cstdio>
#include<cassert>
#include<deque>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	deque<int>S;
	for(int i=0,v;i<N;i++)scanf("%d",&v),S.push_back(v);
	int OO=0,XX=0;
	for(int i=0;!S.empty();i++)
	{
		int v;
		if(S.front()>=S.back())v=S.front(),S.pop_front();
		else v=S.back(),S.pop_back();
		(i&1?XX:OO)+=v;
	}
	puts(OO==XX?"D":(OO>XX?"O":"X"));
	printf("%d %d\n",OO,XX);
	return 0;
}

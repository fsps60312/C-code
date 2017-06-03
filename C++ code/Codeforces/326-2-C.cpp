#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int N,S[1000000];
struct Node
{
	int v,cnt;
	Node(){}
	Node(const int &v,const int &c):v(v),cnt(c){}
};
vector<Node>NODE;
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	sort(S,S+N);
	Node now=Node(S[0],1);
	for(int i=1;i<N;i++)
	{
		if(S[i]==S[i-1])now.cnt++;
		else
		{
			NODE.push_back(now);
			now=Node(S[i],1);
		}
	}
	NODE.push_back(now);
	return 0;
}

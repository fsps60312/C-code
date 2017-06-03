#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
const int INF=2147483647;
int N,S[1000],RIGHT_LOWER[1000];
vector<int>ET[1000];
int COLOR[1000];
bool Color(const int u,const int color)
{
	if(COLOR[u]!=-1)return COLOR[u]==color;
	COLOR[u]=color;
	for(const int nxt:ET[u])if(!Color(nxt,color^1))return false;
	return true;
}
vector<char>ANS;
stack<int>A,B;
bool Solve()
{
	//i<j<k,S[k]<S[i]<S[j]
	for(int i=0;i<N;i++)
	{
		for(int j=N-1;;j--)if(S[j]<=S[i]){RIGHT_LOWER[i]=j;break;}
	}
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(S[i]<S[j])
	{
		if(RIGHT_LOWER[i]>j)ET[i].push_back(j),ET[j].push_back(i);
	}
	for(int i=0;i<N;i++)COLOR[i]=-1;
	ANS.clear();
	while(!A.empty())A.pop();
	while(!B.empty())B.pop();
	int cur=1;
	for(int i=0;i<N;i++)
	{
		if(COLOR[i]==-1)if(!Color(i,0))return false;
		if(COLOR[i]==0)A.push(S[i]),ANS.push_back('a');
		else if(COLOR[i]==1)
		{
			while(!B.empty()&&B.top()==cur)B.pop(),cur++,ANS.push_back('d');
			B.push(S[i]),ANS.push_back('c');
		}
		else assert(0);
		while(!A.empty()&&A.top()==cur)A.pop(),cur++,ANS.push_back('b');
	}
	while(!A.empty()||!B.empty())
	{
		if(!A.empty()&&A.top()==cur)A.pop(),cur++,ANS.push_back('b');
		if(!B.empty()&&B.top()==cur)B.pop(),cur++,ANS.push_back('d');
	}
	assert(cur==N+1);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		if(!Solve())puts("0");
		else
		{
			for(int i=0;i<(int)ANS.size();i++)
			{
				if(i)putchar(' ');
				putchar(ANS[i]);
			}
			puts("");
		}
	}
	return 0;
}

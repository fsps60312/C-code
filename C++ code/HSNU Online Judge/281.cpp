#include<cstdio>
#include<cassert>
#include<deque>
using namespace std;
int N;
char S[200001];
deque<char>TUBE;
void PutLeft(const char c)
{
	putchar('L');
	if(!TUBE.empty()&&TUBE.front()==c)TUBE.pop_front();
	else TUBE.push_front(c);
}
void PutRight(const char c)
{
	putchar('R');
	if(!TUBE.empty()&&TUBE.back()==c)TUBE.pop_back();
	else TUBE.push_back(c);
}
int main()
{
	scanf("%d%s",&N,S);
	for(int i=0;i<N;i++)
	{
		if(TUBE.empty())PutLeft(S[i]);
		else if(TUBE.front()==S[i])PutLeft(S[i]);
		else if(TUBE.back()==S[i])PutRight(S[i]);
		else if(i==N-1||(int)TUBE.size()==1)PutLeft(S[i]);
		else if(S[i]==S[i+1])PutLeft(S[i]),PutLeft(S[++i]);
		else if(S[i+1]==TUBE.front())PutRight(S[i]),PutLeft(S[++i]);
		else if(S[i+1]==TUBE.back())PutLeft(S[i]),PutRight(S[++i]);
		else assert(0);
	}
	puts("");
	return 0;
}

#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
int N,A[250000],B[250000];
bool ANS[250000];
struct CmpB{bool operator()(const int a,const int b)const{return B[a]<B[b];};};
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&A[i]);
	for(int i=0;i<N;i++)scanf("%d",&B[i]);
	for(int i=0;i<N;i++)ANS[i]=false;
	priority_queue<int,vector<int>,CmpB>accepted;
	long long now=0;
	for(int i=0;i<N;i++)
	{
		now+=A[i];
		if(now>=B[i])now-=B[i],accepted.push(i),ANS[i]=true;
		else if(!accepted.empty()&&B[accepted.top()]>B[i])
		{
			const int j=accepted.top();accepted.pop();
			now+=B[j],now-=B[i];
			ANS[j]=false,ANS[i]=true;
			accepted.push(i);
		}
	}
	printf("%d\n",(int)accepted.size());
	for(int i=0,printed=0;i<N;i++)if(ANS[i])
	{
		if(printed++)putchar(' ');
		printf("%d",i+1);
	}
	puts("");
	return 0;
}

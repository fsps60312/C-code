#include<cstdio>
#include<cassert>
#include<utility>
using namespace std;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
int N;
char S[1000001];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S);
		int ans=0;
		pair<int,int>low=make_pair(0,-1);
		for(int i=0,h=0;i<N;i++)
		{
			h+=(S[i]=='p'?1:-1);
			if(h>=low.first)getmax(ans,i-low.second);
			else low=make_pair(h,i);
		}
		low=make_pair(0,N);
		for(int i=N-1,h=0;i>=0;i--)
		{
			h+=(S[i]=='p'?1:-1);
			if(h>=low.first)getmax(ans,low.second-i);
			else low=make_pair(h,i);
		}
		printf("%d\n",ans);
	}
	return 0;
}

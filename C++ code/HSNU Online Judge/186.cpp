#include<cstdio>
#include<utility>
#include<vector>
using namespace std;
int N;
vector<pair<int,int> >S;
int main()
{
	scanf("%d",&N);
	if(true)
	{
		int sz=0;
		for(int i=0,pre=-1,color;i<N;i++)
		{
			scanf("%d",&color);
			if(color==pre)S[sz-1].second++;
			else if(pre==0&&sz>=2&&S[sz-2].first==color)S[sz-2].second+=S[sz-1].second,S.pop_back(),sz--,S[sz-1].second++;
			else S.push_back(make_pair(pre=color,1)),sz++;
		}
		N=sz;
	}
	if(N>1&&S[N-1].first==S[0].first)S[0].second+=S[N-1].second,S.pop_back(),N--;
	if(N>=3&&S[N-1].first==0&&S[N-2].first==S[0].first)S[0].second+=S[N-1].second+S[N-2].second,S.pop_back(),S.pop_back(),N-=2;
	if(N>=3&&S[0].first==0&&S[1].first==S[N-1].first)
	{
		S[1].second+=S[0].second+S[N-1].second;
		S.pop_back(),N--;
		for(int i=1;i<N;i++)S[i-1]=S[i];
		S.pop_back(),N--;
	}
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int len=S[i].second;
		if(S[(i+N-1)%N].first==0)len+=S[(i+N-1)%N].second;
		if(S[(i+1)%N].first==0)len+=S[(i+1)%N].second;
		if(len>ans)ans=len;
	}
	printf("%d\n",ans);
	return 0;
}

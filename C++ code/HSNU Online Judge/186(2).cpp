#include<cstdio>
#include<utility>
#include<vector>
using namespace std;
int N;
vector<pair<int,int> >S;
int main()
{
	scanf("%d",&N);
	const int beadlen=N;
	if(true)
	{
		int *tmp=new int[N];
		for(int i=0;i<N;i++)scanf("%d",&tmp[i]);
		int sz=0;
		for(int i=0,pre=-1;i<N*2;i++)
		{
			const int color=tmp[i%N];
			if(color==pre)S[sz-1].second++;
			else if(pre==0&&sz>=2&&S[sz-2].first==color)S[sz-2].second+=S[sz-1].second,S.pop_back(),sz--,S[sz-1].second++,pre=color;
			else S.push_back(make_pair(pre=color,1)),sz++;
		}
		delete[]tmp;
		N=sz;
	}
//	for(int i=0;i<N;i++)printf("(%d,%d)\n",S[i].first,S[i].second);
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int len=S[i].second;
		if(i&&S[i-1].first==0)len+=S[i-1].second;
		if(i+1<N&&S[i+1].first==0)len+=S[i+1].second;
		if(len>ans)ans=len;
	}
	printf("%d\n",ans>beadlen?beadlen:ans);
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
int N,K,ZERO,S[10000];
vector<int>LEFT,RIGT;
int Solve()
{
	if(K==N)
	{
		int ans=0;
		for(int i=0;i<N;i++)ans+=S[i];
		return ans;
	}
	assert(K<N);
	int ri=0,li=0;
	int zero_taken=0;
	for(int i=0;i<K;i++)
	{
		if(ri<(int)RIGT.size()&&(li==(int)LEFT.size()||RIGT[ri]>=LEFT[li]))++ri;
		else if(li<(int)LEFT.size())++li;
		else ++zero_taken;
	}
//	printf("li=%d,ri=%d,zero_taken=%d\n",li,ri,zero_taken);
	if(zero_taken==0&&li%2==1)
	{
		if(li==(int)LEFT.size()&&ri==(int)RIGT.size())
		{
			assert(ZERO>0);
			zero_taken=-1;
		}
		else if(li>0&&ri<(int)RIGT.size()
			&&(li==(int)LEFT.size()||ri==0||/*RIGT[ri]/LEFT[li-1]>=LEFT[li]/RIGT[ri-1]*/RIGT[ri]*RIGT[ri-1]>=LEFT[li]*LEFT[li-1]))++ri,--li;
		else if(ri>0&&li<(int)LEFT.size()
			&&(ri==(int)RIGT.size()||li==0||/*LEFT[li]/RIGT[ri-1]>=RIGT[ri]/LEFT[li-1]*/LEFT[li]*LEFT[li-1]>=RIGT[ri]*RIGT[ri-1]))--ri,++li;
		else assert(RIGT.empty());
	}
	if(zero_taken!=0)
	{
		int ans=0;
		for(int i=0;i<K;i++)ans+=S[i];
		return ans;
	}
	assert(li%2==0||RIGT.empty());
	assert(li+ri==K);
	int ans=0;
	for(int i=0;i<li;i++)ans-=LEFT[i];
	for(int i=0;i<ri;i++)ans+=RIGT[i];
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(true)
	{
		assert(scanf("%d%d",&N,&K)==2);
		if(N==0&&K==0)break;
		LEFT.clear(),RIGT.clear();
		ZERO=0;
		for(int i=0;i<N;i++)
		{
			int &v=S[i];
			scanf("%d",&v);
			if(v)(v<0?LEFT:RIGT).push_back(abs(v));
			else ++ZERO;
		}
		sort(S,S+N,greater<int>());
		sort(LEFT.begin(),LEFT.end(),greater<int>());
		sort(RIGT.begin(),RIGT.end(),greater<int>());
		printf("%d\n",Solve());
	}
	return 0;
}

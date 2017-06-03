#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int N;
vector<pair<int,char> >ANS;
struct DataSet
{
	int S[2000],LOC[2000],CUR;
	void Initialize()
	{
		CUR=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),LOC[--S[i]]=i;
	}
	int &At(const int i){return S[(CUR+i)%N];}
	void DoA(bool tagging)
	{
		if(tagging){CUR--;if(CUR<0)CUR+=N;}
		else
		{
			for(int i=N-1;i>=1;i--)swap(At(i),At(i-1)),swap(LOC[At(i)],LOC[At(i-1)]);
		}
		ANS.push_back(make_pair(1,'a'));
	}
	void DoB()
	{
		assert(N>=3);
		swap(At(2),At(1)),swap(LOC[At(2)],LOC[At(1)]);
		swap(At(1),At(0)),swap(LOC[At(1)],LOC[At(0)]);
		ANS.push_back(make_pair(1,'b'));
	}
	void MoveCUR(const int loc)
	{
		int cnt=CUR-loc;
		if(cnt<0)cnt+=N;
		CUR=loc;
		if(cnt)ANS.push_back(make_pair(cnt,'a'));
	}
	void MoveRight(const int loc,const int bound){MoveCUR(min(loc,bound-2));DoB();}
	bool Sorted(){for(int i=0;i<N;i++)if(At(i)!=i)return false;return true;}
}S;
int InversePairs()
{
	int ans=0;
	for(int i=0;i<N;i++)for(int j=i+1;j<N;j++)if(S.At(i)>S.At(j))ans++;
	return ans;
}
bool Solve()
{
	ANS.clear();
	if(N==1)return true;
	if(N==2)
	{
		if(!S.Sorted())S.DoA(false);
	}
	else
	{
		if(InversePairs()&1)
		{
			if(N&1)return false;
			S.DoA(false);
		}
		assert(!(InversePairs()&1));
		for(int i=N-1;i>=2;i--)
		{
			while(S.LOC[i]!=i)S.MoveRight(S.LOC[i],i);
		}
	}
	S.MoveCUR(0);
	assert(S.Sorted());
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("prz5ocen.in","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		S.Initialize();
		if(!Solve())puts("NIE DA SIE");
		else
		{
			vector<pair<int,char> >ans;
			for(int i=0;i<(int)ANS.size();i++)
			{
				if(ans.empty()||ans.back().second!=ANS[i].second)ans.push_back(ANS[i]);
				else ans.back().first+=ANS[i].first;
			}
			printf("%d\n",(int)ans.size());
			if(!ans.empty())
			{
				for(int i=0;i<(int)ans.size();i++)
				{
					if(i)putchar(' ');
					printf("%d%c",ans[i].first,ans[i].second);
				}
				puts("");
			}
		}
	}
	return 0;
}

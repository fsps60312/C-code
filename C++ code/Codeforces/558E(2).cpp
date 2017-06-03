#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
using namespace std;
int N,CNT[100001][26],TYPE[100001];
char A[100001];
set<int>LOCS;
void Split(const int loc)
{
	int l,sum;
	if(true)
	{
		auto it=LOCS.lower_bound(loc);
		if((*it)==loc)return;
		sum=*it;
		l=*--it;
		sum-=l;
	}
	TYPE[loc]=TYPE[l];
//	printf("l=%d,loc=%d,sum=%d\n",l,loc,sum);
	for(int i=(TYPE[l]==1?25:0);;i+=(TYPE[l]==1?-1:1))
	{
		assert(0<=i&&i<=26);
//		printf("i=%d,sum=%d,cnt=%d\n",i,sum,CNT[l][i]);
		if(sum-CNT[l][i]>loc-l)CNT[loc][i]+=CNT[l][i],sum-=CNT[l][i],CNT[l][i]=0;
		else
		{
			const int v=sum-(loc-l);
			CNT[loc][i]+=v,CNT[l][i]-=v;
			break;
		}
	}
	LOCS.insert(loc);
}
void Merge(const int l,const int r,const int type)
{
	TYPE[l]=type;
	auto it=LOCS.find(l),end=LOCS.find(r);
	assert(it!=LOCS.end()&&end!=LOCS.end());
	vector<set<int>::iterator>to_erase;
	for(it++;it!=end;it++)
	{
		for(int i=0;i<26;i++)CNT[l][i]+=CNT[*it][i],CNT[*it][i]=0;
		to_erase.push_back(it);
	}
	for(const auto &v:to_erase)LOCS.erase(v);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int querycount;
	while(scanf("%d%d",&N,&querycount)==2)
	{
		scanf("%s",A);
		LOCS.clear();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<26;j++)CNT[i][j]=0;
			CNT[i][A[i]-'a']++;
			LOCS.insert(i);
			TYPE[i]=1;
		}
		for(int i=0;i<26;i++)CNT[N][i]=0;TYPE[N]=1;LOCS.insert(N);
		for(int l,r,k;querycount--;)
		{
			scanf("%d%d%d",&l,&r,&k),l--,r--;
			Split(l),Split(r+1);
			Merge(l,r+1,k);
		}
		for(const auto it:LOCS)
		{
			for(int i=(TYPE[it]==1?0:25);0<=i&&i<=25;i+=(TYPE[it]==1?1:-1))
			{
				for(int j=0;j<CNT[it][i];j++)putchar('a'+i);
			}
		}
		puts("");
	}
	return 0;
}

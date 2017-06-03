#include<cstdio>
#include<vector>
#include<cassert>
#include<utility>
#include<set>
using namespace std;
int N,M;
vector<int>ET[100000],EA[100000];
vector<pair<int,int> >ANS;
set<int>AVAIL;
int Move(const int u)
{
	vector<set<int>::iterator>to_erase;
	int ans=-1;
	for(auto it=AVAIL.begin();;it++)
	{
		assert(it!=AVAIL.end());
		if((int)EA[*it].size()==2)to_erase.push_back(it);
		else if(*it!=u)
		{
			bool found=false;
			for(const int v:ET[u])found|=(v==*it);
			for(const int v:EA[u])found|=(v==*it);
			if(!found){ans=*it;break;}
		}
	}
	for(const auto &it:to_erase)AVAIL.erase(it);
	return ans;
}
bool HasEdge(const int a,const int b)
{
	for(const int v:ET[a])if(v==b)return true;
	return false;
}
bool Solve()
{
	printf("N=%d\n",N);
	if(N==1)return true;
	else if(N==2)return M==0;
	else if(N==3)
	{
		puts("pass");
		if(M>=2)return false;
		if(M==0)return true;
		ANS.push_back(make_pair(0,3-ET[0][0]));
		return true;
	}
	else if(N==4)
	{
		for(int i=0;i<N&&(int)ANS.size()<M;i++)for(int j=0;j<N&&(int)ANS.size()<M;j++)if(i!=j&&!HasEdge(i,j))ANS.push_back(make_pair(i,j));
		return (int)ANS.size()==M;
	}
	AVAIL.clear();
	for(int i=0;i<N;i++)AVAIL.insert(i);
	for(int i=0;AVAIL.size()>=3&&(int)ANS.size()<M;i++)if((int)EA[i].size()!=2)
	{
		assert(EA[i].empty());
		int cur=i;
		do
		{
			const int nxt=Move(cur);
			ANS.push_back(make_pair(cur,nxt)),printf("(%d,%d)\n",cur,nxt);
			EA[cur].push_back(nxt),EA[nxt].push_back(cur);
			cur=nxt;
		}while(cur!=i);
	}
	if((int)ANS.size()!=M)
	{
		assert((int)AVAIL.size()==1);
		const int lose=*AVAIL.begin();
		for(auto &v:ANS)if(!HasEdge(lose,v.first)&&!HasEdge(lose,v.second))
		{
			const auto tmp=v;
			v=make_pair(lose,tmp.first);
			ANS.push_back(make_pair(lose,tmp.second));
			break;
		}
	}
	assert((int)ANS.size()==M||N==5);
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear(),EA[i].clear();
		ANS.clear();
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		if(Solve())
		{
			for(const auto &p:ANS)printf("%d %d\n",p.first+1,p.second+1);
		}
		else puts("-1");
		break;
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
int SG[21][21];
int GetSG(const int row,const int col)
{
	int &ans=SG[row][col];
	if(ans!=-1)return ans;
	vector<int>s;
	for(int i=0;i<row;i++)for(int j=0;j<col;j++)
	{
		if(i&&j)s.push_back(GetSG(i,j)^GetSG(i,col)^GetSG(row,j));
		else if(i)
	}
	sort(s.begin(),s.end()),s.resize(unique(s.begin(),s.end())-s.begin());
	for(ans=0;ans<(int)s.size()&&s[ans]==ans;ans++);
	return ans;
}
int N,M;
multiset<int>ANS;
bool Solve(int K)
{
	ANS.clear();
	map<int,int>s;
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)s[GetSG(i,j)]++;
	if(s.begin()->first==0)
	{
		int &v=s.begin()->second;
		if(v<K)
		{
			for(int i=0;i<v;i++)ANS.insert(0);
			K-=v;
			s.erase(s.begin());
		}
		else if(s.size()==1)return false;
		else
		{
			for(int i=0;i<K-1;i++)ANS.insert(0);
			auto it=s.begin();it++;
			ANS.insert(it->first);
			return true;
		}
	}
	vector<int>to_erase;
	for(auto &it:s)
	{
		const int v=min(it.second/2*2,K/2*2);
		if(v<K)
		{
			K-=v,it.second-=v;
			for(int i=0;i<v;i++)ANS.insert(it.first);
		}
		if(it.second==0)to_erase.push_back(it.first);
	}
	for(const int v:to_erase)s.erase(v);
	assert(!s.empty());
	if(K==1)
	{
		ANS.insert(s.begin()->first);
		return true;
	}
	else if(K==2)
	{
		if(s.size()>=2)
		{
			auto it=s.begin();
			ANS.insert(it->first);
			it++;
			ANS.insert(it->first);
			return true;
		}
		else return false;
	}
	else
	{
		vector<int>remain;
		for(const auto &it:s)assert(it.second==1),remain.push_back(it.first);
		assert((int)remain.size()>=K);
		int ans=0;
		for(int i=0;i<K;i++)ans^=remain[i];
		if(ans!=0)
		{
			for(int i=0;i<K;i++)ANS.insert(remain[i]);
			return true;
		}
		else
		{
			if(s.size()==1||(int)remain.size()==K)return false;
			const int a=remain[0],b=remain[(int)remain.size()-1];
			assert(a!=b);
			for(int i=1;i<K;i++)ANS.insert(remain[i]);
			ANS.insert(b);
			return true;
		}
	}
}
int K;
int main()
{
	freopen("in.txt","r",stdin);
	for(int i=0;i<=20;i++)for(int j=0;j<=20;j++)SG[i][j]=1;
	for(int i=1;i<=20;i++)for(int j=1;j<=20;j++)SG[i][j]=-1;
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=20;j++)printf("%d ",GetSG(i,j));
		puts("");
	}
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d",&N,&M,&K);
		if(Solve(K))
		{
			puts("^v^;;");
			assert((int)ANS.size()==K);
			int check=0;
			for(int i=1;i<=N;i++)
			{
				for(int j=1;j<=M;j++)
				{
					const auto it=ANS.find(GetSG(i,j));
					if(it!=ANS.end()){ANS.erase(it);putchar('C');check^=GetSG(i,j);}
					else putchar('A');
				}
				puts("");
			}
			assert(ANS.empty());
			assert(check!=0);
		}
		else puts("ko_ko_ko");
	}
	return 0;
}

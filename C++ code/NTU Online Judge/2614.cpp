#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
class Sam
{
	private: vector<int*>CH;
	private: vector<int>GREEN,MAX_LEN;
	public:  vector<int>LOC;
	private: int LAST;
	public:  int Size()const{return LAST+1;}
	public:  void Clear()
	{
		for(int* &v:CH)delete[]v;
		CH.clear();
		GREEN.clear(),MAX_LEN.clear();
		LOC.clear();
		Expand(0,-1);
		GREEN[0]=-1;
		LAST=0;
	}
	private: void Expand(const int max_len,const int loc)
	{
		CH.push_back(new int[26]{-1});
		GREEN.push_back(-2),MAX_LEN.push_back(max_len);
		LOC.push_back(loc);
		++LAST;
	}
	public:  void Extend(const char _w,const int _i)
	{
		const int w=_w-'a';
		int cur=LAST;
		Expand(MAX_LEN[cur]+1,_i);
		const int last=LAST;
		for(;cur!=-1&&CH[cur][w]==-1;cur=GREEN[cur])CH[cur][w]=last;
		if(cur==-1)GREEN[last]=0;
		else
		{
			const int potential_green=CH[cur][w];
			if(MAX_LEN[cur]+1==MAX_LEN[potential_green])GREEN[last]=potential_green;
			else
			{
				Expand(MAX_LEN[cur]+1,-1);
				const int green=LAST;
				for(;cur!=-1&&CH[cur][w]==potential_green;cur=GREEN[cur])CH[cur][w]=green;
				for(int i=0;i<26;i++)CH[green][i]=CH[potential_green][i];
				GREEN[green]=GREEN[potential_green];
				GREEN[potential_green]=green;
				GREEN[last]=green;
			}
		}
	}
	public: void BuildET(vector<int>*et)
	{
		for(int i=0;i<Size();i++)et[i].clear();
		for(int i=1;i<Size();i++)et[GREEN[i]].push_back(i);
	}
}SAM;
int N;
char S[200001];
vector<int>ET[400001];
int SZ[400001];
int BuildSZ(const int u)
{
	int &sz=SZ[u]=1;
	for(const int nxt:ET[u])sz+=BuildSZ(nxt);
	return sz;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,S)==2)
	{
		SAM.Clear();
		for(int i=0;i<N;i++)SAM.Extend(S[i],i);
		SAM.BuildET(ET);
		BuildSZ(0);
		for(int i=0;i<SAM.Size();i++)DP[i]=-1;
		
	}
	return 0;
}

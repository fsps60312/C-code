#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
struct Trie
{
	int SZ;
	vector<int>CH[2],DEPTH,PARENT;
	vector<bool>REAL_END,FAKE_END;
	void Clear()
	{
		CH[0].clear(),CH[1].clear();
		DEPTH.clear(),PARENT.clear();
		REAL_END.clear(),FAKE_END.clear();
		SZ=0;
		Expand();
	}
	void Expand()
	{
		CH[0].push_back(0),CH[1].push_back(0);
		DEPTH.push_back(0),PARENT.push_back(-1);
		REAL_END.push_back(false);
		FAKE_END.push_back(false);
		++SZ;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();
		DEPTH[SZ-1]=DEPTH[u]+1;
		PARENT[SZ-1]=u;
		return CH[c][u]=SZ-1;
	}
	vector<int>WORDS;
	void Initialize()
	{
		Clear();
		WORDS.clear();
		vector<int>us;us.push_back(0);
		int n;scanf("%d",&n);
		for(int i=0;i<n;i++)
		{
			const char c=(char)getchar();
			switch(c)
			{
				case'0':us.push_back(GetNxt(us.back(),0));break;
				case'1':us.push_back(GetNxt(us.back(),1));break;
				case'B':us.pop_back();break;
				case'X':REAL_END[us.back()]=FAKE_END[us.back()]=true,WORDS.push_back(us.back());break;
				default:i--;break;
			}
		}
	}
	vector<int>FAIL;
	vector<bool>LONG_MUST_END,LONG_CANT_END;
	void BuildFail()
	{
		FAIL.clear(),FAIL.resize(SZ,0);
		queue<int>q;
		for(int i=0;i<2;i++)if(CH[i][0])q.push(CH[i][0]);
		vector<int>order;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			order.push_back(u);
			for(int c=0;c<2;c++)if(CH[c][u])
			{
				int &f=FAIL[CH[c][u]]=FAIL[u];
				while(f&&!CH[c][f])f=FAIL[f];
				f=CH[c][f];
				q.push(CH[c][u]);
				if(FAKE_END[FAIL[u]])FAKE_END[u]=true;
			}
		}
		LONG_MUST_END.clear(),LONG_MUST_END.resize(SZ,false);
		LONG_CANT_END.clear(),LONG_CANT_END.resize(SZ,false);
		for(int i=(int)order.size()-1;i>=0;i--)
		{
			const int u=order[i];
			if(REAL_END[u])LONG_MUST_END[u]=true;
			else LONG_CANT_END[u]=true;
//			printf("u=%d, fail=%d, depth=%d, parent=%d, must/cant=(%d,%d)\n",u,FAIL[u],DEPTH[u],PARENT[u],(int)LONG_MUST_END[u],(int)LONG_CANT_END[u]);
			if(LONG_MUST_END[u])LONG_MUST_END[FAIL[u]]=true;
			if(LONG_CANT_END[u])LONG_CANT_END[FAIL[u]]=true;
		}
	}
	vector<bool>MUST_BE_END,MUST_BE_END_VIS,CANT_BE_END,CANT_BE_END_VIS;
	int GrandParent(const int u,const int dis)
	{
		int ans=u;
		for(int i=0;i<dis;i++)ans=PARENT[ans];
		return ans;
	}
	bool MustBeEnd(const int u)
	{
		if(MUST_BE_END_VIS[u])return MUST_BE_END[u];
		MUST_BE_END_VIS[u]=true;
		if(LONG_MUST_END[u])goto return_true;
		for(int o=u;o;o=FAIL[o])if(REAL_END[o])
		{
			assert(DEPTH[o]<DEPTH[u]);
			if(MustBeEnd(GrandParent(u,DEPTH[o])))goto return_true;
		}
		goto return_false;
		return_true:;
		return MUST_BE_END[u]=true;
		return_false:;
		return MUST_BE_END[u]=false;
	}
	bool CantBeEnd(const int u)
	{
		if(CANT_BE_END_VIS[u])return CANT_BE_END[u];
		CANT_BE_END_VIS[u]=true;
		if(LONG_CANT_END[u])goto return_true;
		for(int o=u;o;o=FAIL[o])if(!REAL_END[o])
		{
			assert(DEPTH[o]<DEPTH[u]);
			if(MustBeEnd(GrandParent(u,DEPTH[o])))goto return_true;
		}
		goto return_false;
		return_true:;
		return CANT_BE_END[u]=true;
		return_false:;
		return CANT_BE_END[u]=false;
	}
	vector<int>Solve()
	{
		MUST_BE_END_VIS.clear(),MUST_BE_END_VIS.resize(SZ,false);
		CANT_BE_END_VIS.clear(),CANT_BE_END_VIS.resize(SZ,false);
		MUST_BE_END.resize(SZ),CANT_BE_END.resize(SZ);
		vector<int>ans;
		for(int i=0;i<(int)WORDS.size();i++)
		{
			if(!CantBeEnd(WORDS[i]))ans.push_back(i);
		}
		return ans;
	}
}TRIE;
int main()
{
	freopen("in.txt","r",stdin);
	TRIE.Initialize();
	TRIE.BuildFail();
	const vector<int>&ans=TRIE.Solve();
	printf("%d\n",(int)ans.size());
	for(int i=0;i<(int)ans.size();i++)printf("%d\n",ans[i]+1);
	return 0;
}

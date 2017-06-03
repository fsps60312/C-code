#include<cstdio>
#include<string>
#include<vector>
#include<map>
using namespace std;
char PF1[12],PF2[12],TMP[2],NAME[21];
map<string,int>IDX;
vector<string>STR;
struct Trie
{
	struct Node
	{
		int bse[10],v,vis;
		int &operator[](int i){return bse[i];}
		Node():v(-1),vis(0){for(int i=0;i<10;i++)bse[i]=0;}
	};
	vector<Node>bse;
	int sz;
	void clear(){bse.clear(),bse.push_back(Node());sz=0;}
	int getnxt(int u,int c){int &v=bse[u][c];if(v)return v;bse.push_back(Node());return bse[u][c]=++sz;}
	bool allisafter(char *s,int idx,char c)
	{
		for(int i=idx;s[i];i++)if(s[i]!=c)return false;
		return true;
	}
	bool changevalue(int u,int v)
	{
		if(bse[u].vis)return false;
		bse[u].vis=1;
		bse[u].v=v;return true;
	}
	void insert(char *s1,char *s2,int idx,int u,int _state,int v)
	{
		idx++;
		if(bse[u].v!=-1)return;
		if(!s1[idx])
		{
			if(changevalue(u,v))return;
			s1[idx]='0',s2[idx]='9',s1[idx+1]=s2[idx+1]=0;
		}
		else
		{
			if((_state&1)&&allisafter(s1,idx,'0'))
			{
				if(!(_state&2)||allisafter(s2,idx,'9'))
					if(changevalue(u,v))return;
			}
			else if((_state&2)&&allisafter(s2,idx,'9'))
			{
				if(!(_state&1)||allisafter(s1,idx,'0'))
					if(changevalue(u,v))return;
			}
			else if(!(_state&1)&&!(_state&2))
			{
				if(changevalue(u,v))return;
			}
		}
		int l=(_state&1)?s1[idx]-'0':0;
		int r=(_state&2)?s2[idx]-'0':9;
		bse[u].vis=1;
		for(int i=l;i<=r;i++)
		{
			int state=_state;
			if(i>l)state&=~1;
			if(i<r)state&=~2;
			insert(s1,s2,idx,getnxt(u,i),state,v);
		}
	}
	void insert(char *s1,char *s2,int v)
	{
		int l=s1[0]-'0',r=s2[0]-'0';
		for(int i=l;i<=r;i++)
		{
			int state=3;
			if(i>l)state&=~1;
			if(i<r)state&=~2;
			insert(s1,s2,0,getnxt(0,i),state,v);
		}
	}
	void exprt(int u,vector<int>&now,map<string,string>&m)
	{
		if(bse[u].v!=-1)
		{
			if(bse[u].v)
			{
				for(int i=0;i<now.size();i++)PF1[i]='0'+now[i];
				PF1[now.size()]=0;
				m[PF1]=STR[bse[u].v];
			}
			return;
		}
		for(int i=0;i<=9;i++)
		{
			int &v=bse[u][i];
			if(!v)continue;
			now.push_back(i);
			exprt(v,now,m);
			now.pop_back();
		}
	}
}TEL;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int kase=0;
	while(scanf("%d",&N)==1)
	{
		if(kase++)puts("");
		TEL.clear();STR.clear();IDX.clear();STR.push_back("invalid");IDX["invalid"]=0;
		for(int i=0;i<N;i++)
		{
			scanf("%s%s%s%s",PF1,TMP,PF2,NAME);
			int n1=-1,n2=-1;while(PF1[++n1]);while(PF2[++n2]);
			PF2[n1]=0;
			for(int i=n2-1;i>=0;i--)PF2[i+n1-n2]=PF2[i];
			for(int i=n1-n2-1;i>=0;i--)PF2[i]=PF1[i];
			if(IDX.find(NAME)==IDX.end()){int sz=IDX.size();IDX[NAME]=sz;STR.push_back(NAME);}
			TEL.insert(PF1,PF2,IDX[NAME]);
		}
		map<string,string>ans;
		vector<int>now;
		TEL.exprt(0,now,ans);
		printf("%d\n",ans.size());
		for(map<string,string>::iterator it=ans.begin();it!=ans.end();it++)
		{
			printf("%s %s\n",it->first.c_str(),it->second.c_str());
		}
	}
	return 0;
}

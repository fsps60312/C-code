#include<cstdio>
#include<cassert>
#include<string>
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
struct Sparse
{
	vector<int>LOCS;
	vector<vector<int> >S;
	int N;
	Sparse(const vector<pair<int,int> >&_S)
	{
		N=(int)_S.size();
		S.push_back(vector<int>(N));
		for(int i=0;i<N;i++)
		{
			const pair<int,int>p=_S[i];
			LOCS.push_back(p.first);
			S[0][i]=p.second;
		}
		for(int bit=1;(1<<bit)<=N;bit++)
		{
			S.push_back(vector<int>(N));
			for(int i=0;i+(1<<bit)<=N;i++)S[bit][i]=max(S[bit-1][i],S[bit-1][i+(1<<(bit-1))]);
		}
	}
	int Query(const int _l,const int _r)
	{
		const int l=(int)(upper_bound(LOCS.begin(),LOCS.end(),_l)-LOCS.begin())-1;
		const int r=(int)(upper_bound(LOCS.begin(),LOCS.end(),_r)-LOCS.begin())-1;
		assert(l<=r);
		int bit=0;
		while((1<<(bit+1))<=r-l+1)++bit;
		return max(S[bit][l],S[bit][r-(1<<bit)+1]);
	}
};
map<string,int>ID;
vector<vector<pair<int,int> > >CNT;//time, cnt
int GetId(const string s)
{
	map<string,int>::iterator it=ID.find(s);
	if(it!=ID.end())return it->second;
	const int sz=(int)ID.size();
	CNT.push_back(vector<pair<int,int> >());
	return ID[s]=sz;
}
int N,L,M;
string TRAIN_STRING[1000];
vector<pair<int,int> >TRAIN[1000];//time, id
void ChangeCnt(const int id,const int time,const int dif)
{
	if(CNT[id].empty())CNT[id].push_back(make_pair(time,dif));
	pair<int,int>p=CNT[id].back();
	if(p.first<time)CNT[id].push_back(make_pair(time,p.second+dif));
	else
	{
		assert(p.first==time);
		CNT[id].pop_back();
		p.second+=dif;
		if(CNT[id].empty()||p.second!=CNT[id].back().second)CNT[id].push_back(p);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&L,&M)==3)
	{
		for(int i=0;i<N;i++)TRAIN[i].clear();
		ID.clear(),CNT.clear();
		for(int i=0;i<N;i++)
		{
			static char train[101];
			scanf("%s",train);
			const int id=GetId(TRAIN_STRING[i]=train);
			TRAIN[i].push_back(make_pair(0,id));
		}
		for(int i=0;i<(int)ID.size();i++)CNT[i].push_back(make_pair(0,0));
		for(int i=0;i<N;i++)++CNT[TRAIN[i][0].second][0].second;
		for(int time=1,p1,w1,p2,w2;time<=M;time++)
		{
			scanf("%d%d%d%d",&p1,&w1,&p2,&w2),--p1,--w1,--p2,--w2;
			if(TRAIN_STRING[p1][w1]==TRAIN_STRING[p2][w2])continue;
			const int pre_id1=GetId(TRAIN_STRING[p1]),pre_id2=GetId(TRAIN_STRING[p2]);
			swap(TRAIN_STRING[p1][w1],TRAIN_STRING[p2][w2]);
			const int nxt_id1=GetId(TRAIN_STRING[p1]),nxt_id2=GetId(TRAIN_STRING[p2]);
			if(p1!=p2)TRAIN[p1].push_back(make_pair(time,nxt_id1));
			TRAIN[p2].push_back(make_pair(time,nxt_id2));
			ChangeCnt(pre_id1,time,-1);
			ChangeCnt(pre_id2,time,-1);
			ChangeCnt(nxt_id1,time,1);
			ChangeCnt(nxt_id2,time,1);
		}
		vector<Sparse>sparse;
		for(int i=0;i<(int)ID.size();i++)sparse.push_back(Sparse(CNT[i]));
		for(int i=0;i<N;i++)
		{
			TRAIN[i].push_back(make_pair(M+1,-1));
			int ans=0;
//			for(int j=0;j<(int)TRAIN[i].size();j++)printf("(%d,%d)",TRAIN[i][j].first,TRAIN[i][j].second);puts("");
			for(int j=0;j+1<(int)TRAIN[i].size();j++)
			{
				const int l=TRAIN[i][j].first,r=TRAIN[i][j+1].first-1;
				getmax(ans,sparse[TRAIN[i][j].second].Query(l,r));
			}
			assert(ans>0);
			printf("%d\n",ans-1);
		}
	}
	return 0;
}

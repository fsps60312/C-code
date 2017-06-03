#define SELF
#ifndef SELF
#include "lib1885.h"
#endif
#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
#ifdef SELF
void Init(int t);
void orderCoins();
int Init(){return 1;}
const int GRADER_ANSWER[7]={0,3,4,6,2,1,5};
void answer(int *ans)
{
	bool correct=true;
	printf("ans:");for(int i=0;i<6;i++)printf(" %d",ans[i]),correct&=(ans[i]==GRADER_ANSWER[i+1]);puts("");
	puts(correct?"AC":"WA");
}
int getHeaviest(int A,int B,int C)
{
	printf("getHeaviest(%d,%d,%d)\n",A,B,C);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[2];
}
int getLightest(int A,int B,int C)
{
	printf("getLightest(%d,%d,%d)\n",A,B,C);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[0];
}
int getMedian(int A,int B,int C)
{
	printf("getMedian(%d,%d,%d)\n",A,B,C);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[1];
}
int getNextLightest(int A,int B,int C,int D)
{
	printf("getNextLightest(%d,%d,%d,%d)\n",A,B,C,D);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	int *ans=upper_bound(s,s+3,D,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	if(ans==s+3)return s[0];
	return *ans;
}
int main()
{
	Init(1);
	orderCoins();
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int TEST_COUNT;
vector<vector<int> >PERMUTATIONS,THREE_PERMUTS,FOUR_PERMUTS;
map<vector<int>,int>HEIGHT;
void BestChoice(const vector<int>&s,vector<int>&ans,vector<int>nxts_ans[3]);
int GetHeight(const vector<int>&s)
{
	{auto it=HEIGHT.find(s);if(it!=HEIGHT.end())return it->second;}
	if((int)s.size()<=1)return HEIGHT[s]=0;
	vector<int>choice,nxts[3];
	BestChoice(s,choice,nxts);
	static int kase=0;
	if((int)kase++%1000==0)
	{
		printf("collected=%d,size=%d,height=%d\n",kase,(int)s.size(),choice[0]);
	}
	return HEIGHT[s]=choice[0]+1;
}
void BestChoice(const vector<int>&s,vector<int>&ans,vector<int>nxts_ans[3])
{
	int best_ans=-1;
	{int n=s.size();while(n>1)n=(n+2)/3,best_ans++;}
	ans.clear();
	ans.push_back(INF);
	for(int type=0;type<3;type++)
	{
		vector<pair<int,vector<vector<int> > > >nxtss;
		for(int i=0;i<(int)THREE_PERMUTS.size();i++)
		{
			const auto &choice=THREE_PERMUTS[i];
			vector<vector<int> >nxts;nxts.resize(3);
			for(const int v:s)
			{
				const vector<int>&permute=PERMUTATIONS[v];
				int *tmp=new int[3]{0,1,2};
				assert(tmp[0]==0&&tmp[1]==1&&tmp[2]==2);
				sort(tmp,tmp+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
				nxts[tmp[type]].push_back(v);//type,return_index
				delete[]tmp;
			}
			nxtss.push_back(make_pair(i,nxts));
		}
		sort(nxtss.begin(),nxtss.end(),[](const pair<int,vector<vector<int> > >&a,const pair<int,vector<vector<int> > >&b)
		{
			const auto &ta=a.second,&tb=b.second;
			return max(max(ta[0].size(),ta[1].size()),ta[2].size())<max(max(tb[0].size(),tb[1].size()),tb[2].size());
		});
		for(const auto &it:nxtss)
		{
			const vector<int>&choice=THREE_PERMUTS[it.first];
			const vector<vector<int> >&nxts=it.second;
			bool valid=true;
			for(int i=0;i<3&&valid;i++)if(nxts[i].size()==s.size())valid=false;
			if(valid)
			{
				int max_height=0;
				int *order=new int[3]{0,1,2};
				sort(order,order+3,[&](const int a,const int b)->bool{return nxts[a].size()>nxts[b].size();});
				for(int _i=0;_i<3;_i++)
				{
					const int i=order[_i];
					getmax(max_height,GetHeight(nxts[i]));
					if(max_height>=ans[0])break;
				}
				delete[]order;
				if(max_height<ans[0])
				{
					ans.clear(),ans.push_back(max_height);
					ans.push_back(type);
					for(int i=0;i<3;i++)ans.push_back(choice[i]);
					for(int i=0;i<3;i++)nxts_ans[i]=nxts[i];
					assert(max_height>=best_ans);
					if(max_height==best_ans)return;
				}
			}
		}
	}
	vector<pair<int,vector<vector<int> > > >nxtss;
	for(int i=0;i<(int)FOUR_PERMUTS.size();i++)
	{
		const vector<int>&choice=FOUR_PERMUTS[i];
		vector<vector<int> >nxts;nxts.resize(3);
		for(const int v:s)
		{
			const vector<int>&permute=PERMUTATIONS[v];
			int *tmp=new int[3]{0,1,2};
			sort(tmp,tmp+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			int id=-1;
			if(permute[choice[3]]>permute[choice[tmp[2]]])id=0;
			else
			{
				for(int j=0;j<3;j++)if(permute[choice[tmp[j]]]>permute[choice[3]]){id=j;break;}
				assert(id!=-1);
			}
			nxts[id].push_back(v);
			delete[]tmp;
		}
		nxtss.push_back(make_pair(i,nxts));
	}
	sort(nxtss.begin(),nxtss.end(),[](const pair<int,vector<vector<int> > >&a,const pair<int,vector<vector<int> > >&b)
	{
		const auto &ta=a.second,&tb=b.second;
		return max(max(ta[0].size(),ta[1].size()),ta[2].size())<max(max(tb[0].size(),tb[1].size()),tb[2].size());
	});
	for(const auto &it:nxtss)
	{
		const vector<int>&choice=FOUR_PERMUTS[it.first];
		const vector<vector<int> >&nxts=it.second;
		bool valid=true;
		for(int i=0;i<3&&valid;i++)if(nxts[i].size()==s.size())valid=false;
		if(valid)
		{
			int max_height=0;
			int *order=new int[3]{0,1,2};
			sort(order,order+3,[&](const int a,const int b)->bool{return nxts[a].size()>nxts[b].size();});
			for(int _i=0;_i<3;_i++)
			{
				const int i=order[_i];
				getmax(max_height,GetHeight(nxts[i]));
				if(max_height>=ans[0])break;
			}
			delete[]order;
			if(max_height<ans[0])
			{
				ans.clear(),ans.push_back(max_height);
				ans.push_back(3);
				for(int i=0;i<4;i++)ans.push_back(choice[i]);
				for(int i=0;i<3;i++)nxts_ans[i]=nxts[i];
				assert(max_height>=best_ans);
				if(max_height==best_ans)return;
			}
		}
	}
}
void Build1()
{
	vector<int>s;
	for(int i=0;i<6;i++)s.push_back(i);
	do
	{
		PERMUTATIONS.push_back(s);
	}while(next_permutation(s.begin(),s.end()));
	assert((int)PERMUTATIONS.size()==720);
}
#include<ctime>
void Build2()
{
	vector<int>s;
	s.resize(4),s.pop_back();
	for(int &i=s[0]=0;i<6;i++)for(int &j=s[1]=i+1;j<6;j++)for(int &k=s[2]=j+1;k<6;k++)
	{
		THREE_PERMUTS.push_back(s);
		for(int d=0;d<6;d++)if(d!=i&&d!=j&&d!=k)
		{
			s.push_back(d);
			FOUR_PERMUTS.push_back(s);
			s.pop_back();
		}
	}
	srand(7122);
	assert((int)THREE_PERMUTS.size()==6*5*4/6);
	assert((int)FOUR_PERMUTS.size()==6*5*4/2);
}
void Init(int t)
{
	TEST_COUNT=t;
	Build1(),Build2();
}
void orderCoins()
{
	vector<int>now;
	for(int i=0;i<(int)PERMUTATIONS.size();i++)now.push_back(i);
	while((int)now.size()>1)
	{
		vector<int>choice,nxt[3];
		BestChoice(now,choice,nxt);
		int id;
		switch(choice[1])
		{
			case 0:id=getLightest(choice[2]+1,choice[3]+1,choice[4]+1);break;
			case 1:id=getMedian(choice[2]+1,choice[3]+1,choice[4]+1);break;
			case 2:id=getHeaviest(choice[2]+1,choice[3]+1,choice[4]+1);break;
			case 3:id=getNextLightest(choice[2]+1,choice[3]+1,choice[4]+1,choice[5]+1);break;
			default:assert(0);break;
		}
		for(int i=2;i<=4;i++)if(id==choice[i]+1){id=i-2;break;}
		now=nxt[id];
	}
	assert(now.size()==1);
	vector<int>ans;
	for(int i=0;i<6;i++)ans.push_back(PERMUTATIONS[now[0]][i]+1);
	answer(&ans[0]);
}

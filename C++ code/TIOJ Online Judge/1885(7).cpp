#define SELF
#ifndef SELF
#include "lib1885.h"
#endif
#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
#include<unordered_map>
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

#include<bitset>
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int TEST_COUNT;
vector<vector<int> >PERMUTATIONS,THREE_PERMUTS,FOUR_PERMUTS;
map<vector<int>,vector<bitset<720> > >LIGHTEST[4];
unordered_map<bitset<720>,int>HEIGHT;
void BestChoice(const bitset<720>&s,vector<int>&ans,bitset<720>nxts_ans[3]);
int GetHeight(const bitset<720>&s)
{
	if(HEIGHT.count(s))return HEIGHT[s];
	if((int)s.count()<=1)return HEIGHT[s]=0;
	vector<int>choice;
	bitset<720>nxts[3];
	BestChoice(s,choice,nxts);
	static int kase=0;
	if((int)kase++%1000==0)
	{
		printf("collected=%d,size=%d,height=%d\n",kase,(int)s.count(),choice[0]);
	}
	return HEIGHT[s]=choice[0]+1;
}
void BestChoice(const bitset<720>&s,vector<int>&ans,bitset<720>nxts_ans[3])
{
	int best_ans=-1;
	{int n=s.size();while(n>1)n=(n+2)/3,best_ans++;}
	ans.clear();
	ans.push_back(INF);
	for(int type=0;type<4;type++)for(const auto &it:LIGHTEST[type])
	{
		bitset<720>nxts[3];
		int max_height=0;
		for(int i=0;i<3;i++)
		{
			nxts[i]=s&it.second[i];
			if(nxts[i].count()*2>s.count())max_height=INF;
			else getmax(max_height,GetHeight(nxts[i]));
			if(max_height>=ans[0])break;
		}
		if(max_height<ans[0])
		{
			ans.clear(),ans.push_back(max_height);
			ans.push_back(type);
			for(const auto v:it.first)ans.push_back(v);
			for(int i=0;i<3;i++)nxts_ans[i]=nxts[i];
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
void Build3()
{
	for(const vector<int>&choice:THREE_PERMUTS)
	{
		vector<bitset<720> >nxts[3];
		for(int i=0;i<3;i++)
		{
			nxts[i].resize(3);
			for(int j=0;j<3;j++)nxts[i][j].reset();
		}
		for(int i=0;i<720;i++)
		{
			const vector<int>&permute=PERMUTATIONS[i];
			int order[3]={0,1,2};
			sort(order,order+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			for(int j=0;j<3;j++)nxts[j][order[j]].set(i,1);
		}
		for(int i=0;i<3;i++)LIGHTEST[i][choice]=nxts[i];
	}
	for(const vector<int>&choice:FOUR_PERMUTS)
	{
		vector<bitset<720> >nxts;
		nxts.resize(3);
		for(int i=0;i<3;i++)nxts[i].reset();
		for(int i=0;i<720;i++)
		{
			const vector<int>&permute=PERMUTATIONS[i];
			int order[3]={0,1,2};
			sort(order,order+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			int id=-1;
			if(permute[choice[3]]>permute[choice[order[2]]])id=0;
			else
			{
				for(int j=0;j<3;j++)if(permute[choice[order[j]]]>permute[choice[3]]){id=j;break;}
				assert(id!=-1);
			}
			nxts[id].set(i,1);
		}
		LIGHTEST[3][choice]=nxts;
	}
}
void Init(int t)
{
	TEST_COUNT=t;
	Build1(),Build2(),Build3();
}
void orderCoins()
{
	bitset<720>now(0);
	now.flip();
	while(now.count()>1)
	{
		vector<int>choice;
		bitset<720>nxt[3];
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
	assert(now.count()==1);
	int id=-1;
	for(int i=0;i<720;i++)if(now[i]==1){id=i;break;}
	assert(id!=-1);
	vector<int>ans;
	for(int i=0;i<6;i++)ans.push_back(PERMUTATIONS[id][i]+1);
	answer(&ans[0]);
}

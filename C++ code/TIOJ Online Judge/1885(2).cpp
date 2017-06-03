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
	printf("GetHeaviest(%d,%d,%d)\n",A,B,C);
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
	if((int)HEIGHT.size()%1000==0)
	{
		printf("collected=%d,size=%d,height=%d\n",(int)HEIGHT.size(),(int)s.size(),choice[0]);
	}
	return HEIGHT[s]=choice[0]+1;
}
void BestChoice(const vector<int>&s,vector<int>&ans,vector<int>nxts_ans[3])
{
	ans.clear();
	ans.push_back(INF);
	for(const vector<int>&choice:THREE_PERMUTS)
	{
		vector<int>nxts[3][3];
		for(const int v:s)
		{
			const vector<int>&permute=PERMUTATIONS[v];
			int *tmp=new int[3]{0,1,2};
			sort(tmp,tmp+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			for(int i=0;i<3;i++)nxts[i][tmp[i]].push_back(v);//type,return_index
			delete[]tmp;
		}
		for(int type=0;type<3;type++)
		{
			bool valid=true;
			for(int i=0;i<3;i++)if(nxts[type][i].size()==s.size()){valid=false;break;}
			if(valid)
			{
				int max_height=0;
				int *order=new int[3]{0,1,2};
				sort(order,order+3,[&](const int a,const int b)->bool{return nxts[type][a].size()<nxts[type][b].size();});
				for(int _i=0;_i<3;_i++)
				{
					const int i=order[_i];
					getmax(max_height,GetHeight(nxts[type][i]));
					if(max_height>=ans[0])break;
				}
				delete[]order;
				if(max_height<ans[0])
				{
					ans.clear(),ans.push_back(max_height);
					ans.push_back(type);
					for(int i=0;i<3;i++)ans.push_back(choice[i]);
					for(int i=0;i<3;i++)nxts_ans[i]=nxts[type][i];
				}
			}
		}
	}
	for(const vector<int>&choice:FOUR_PERMUTS)
	{
		vector<int>nxts[3];
		for(const int v:s)
		{
			const vector<int>&permute=PERMUTATIONS[v];
			int *tmp=new int[3]{0,1,2};
			sort(tmp,tmp+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			int id;
			if(permute[choice[3]]>permute[choice[tmp[2]]])id=0;
			else
			{
				for(int i=0;i<3;i++)if(permute[choice[tmp[i]]]>permute[choice[3]]){id=i;break;}
			}
			nxts[id].push_back(v);
			delete[]tmp;
		}
		bool valid=true;
		for(int i=0;i<3;i++)if(nxts[i].size()==s.size()){valid=false;break;}
		if(valid)
		{
			int max_height=0;
			int *order=new int[3]{0,1,2};
			sort(order,order+3,[&](const int a,const int b)->bool{return nxts[a].size()<nxts[b].size();});
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
		for(int i=2;i<=4;i++)if(id==choice[i]){id=i;break;}
		now=nxt[id];
	}
	assert(now.size()==1);
	answer(&PERMUTATIONS[now[0]][0]);
}

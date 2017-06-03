//#define SELF
#ifndef SELF
#include "lib1885.h"
#endif
#include<cstdio>
#include<cassert>
#include<algorithm>
#include<map>
using namespace std;
#ifdef SELF
int Init(){return 720;}
//const int GRADER_ANSWER[7]={0,3,4,6,2,1,5};
//int GRADER_ANSWER[7]={0,3,4,6,2,1,5};
int GRADER_ANSWER[7]={0,2,1,3,5,4,6},STEPS;
void orderCoins()
{
	static int kase=0;
	int *s=GRADER_ANSWER;
	for(int i=1;i<=6;i++)s[i]=i;
	for(int i=0;i<kase;i++)next_permutation(s+1,s+7);
	kase++;
	STEPS=0; 
}
void answer(int *ans)
{
	bool correct=true;
	printf("ans:");for(int i=0;i<6;i++)printf(" %d",ans[i]),correct&=(ans[i]==GRADER_ANSWER[i+1]);puts("");
	puts(correct?"AC":"WA");
	printf("STEPS=%d\n",STEPS);
	if(!correct||STEPS!=6)system("pause");
}
int getHeaviest(int A,int B,int C)
{
	STEPS++;
	printf("getHeaviest(%d,%d,%d)\n",A,B,C);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[2];
}
int getLightest(int A,int B,int C)
{
	STEPS++;
	printf("getLightest(%d,%d,%d)\n",A,B,C);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[0];
}
int getMedian(int A,int B,int C)
{
	STEPS++;
	printf("getMedian(%d,%d,%d)\n",A,B,C);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[1];
}
int getNextLightest(int A,int B,int C,int D)
{
	STEPS++;
	printf("getNextLightest(%d,%d,%d,%d)\n",A,B,C,D);
	int s[3]={A,B,C};
	sort(s,s+3,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	int *ans=upper_bound(s,s+3,D,[](const int a,const int b)->bool{return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	if(ans==s+3)return s[0];
	return *ans;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
vector<vector<int> >PERMUTATIONS,THREE_PERMUTS,FOUR_PERMUTS;
map<vector<int>,int>HEIGHT;
void BestChoice(const vector<int>&s,vector<int>&ans,vector<int>nxts_ans[3]);
int GetHeight(const vector<int>&s)
{
	{auto it=HEIGHT.find(s);if(it!=HEIGHT.end())return it->second;}
	if((int)s.size()<=1)return HEIGHT[s]=0;
	vector<int>choice,nxts[3];
	BestChoice(s,choice,nxts);
//	static int kase=0;
//	if((int)kase++%1000==0)
//	{
//		printf("collected=%d,size=%d,height=%d\n",kase,(int)s.size(),choice[0]);
//	}
	return HEIGHT[s]=choice[0]+1;
}
int LIGHTEST_TMP[6*5*4/6][720][3];
int FOUR_TMP[6*5*4/2][720];
void Build3()
{
	for(int choice_idx=0;choice_idx<(int)THREE_PERMUTS.size();choice_idx++)
	{
		const vector<int>&choice=THREE_PERMUTS[choice_idx];
		assert((int)choice.size()==3);
		vector<int>nxts[3][3];
		for(int v=0;v<720;v++)
		{
			const vector<int>&permute=PERMUTATIONS[v];
			int *tmp=LIGHTEST_TMP[choice_idx][v];
			for(int i=0;i<3;i++)tmp[i]=i;
			sort(tmp,tmp+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
		}
	}
	for(int choice_idx=0;choice_idx<(int)FOUR_PERMUTS.size();choice_idx++)
	{
		const vector<int>&choice=FOUR_PERMUTS[choice_idx];
		for(int v=0;v<720;v++)
		{
			const vector<int>&permute=PERMUTATIONS[v];
			int *tmp=new int[3]{0,1,2};
			sort(tmp,tmp+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			int &id=FOUR_TMP[choice_idx][v]=-1;
			if(permute[choice[3]]>permute[choice[tmp[2]]])id=tmp[0];
			else
			{
				for(int i=0;i<3;i++)if(permute[choice[tmp[i]]]>permute[choice[3]]){id=tmp[i];break;}
				assert(id!=-1);
			}
			delete[]tmp;
		}
	}
}
void Filter(const vector<int>&s,const int choice_idx,vector<int>nxts[3],const int type)
{
	if(type<3)
	{
		const vector<int>&choice=THREE_PERMUTS[choice_idx];
		for(const int v:s)
		{
			const int *tmp=LIGHTEST_TMP[choice_idx][v];
			nxts[tmp[type]].push_back(v);
		}
	}
	else
	{
		const vector<int>&choice=FOUR_PERMUTS[choice_idx];
		for(const int v:s)nxts[FOUR_TMP[choice_idx][v]].push_back(v);
	}
}
void BestChoice(const vector<int>&s,vector<int>&ans,vector<int>nxts_ans[3])
{
	int best_ans=-1;
	{int n=s.size();while(n>1)n=(n+2)/3,best_ans++;}
	ans.clear();
	ans.push_back(INF);
	for(int choice_idx=0;choice_idx<(int)THREE_PERMUTS.size();choice_idx++)
	{
		const vector<int>&choice=THREE_PERMUTS[choice_idx];
		vector<int>nxts[3][3];
		for(int type=0;type<3;type++)Filter(s,choice_idx,nxts[type],type);
		for(int type=0;type<3;type++)
		{
			bool valid=true;
			//risking
			for(int i=0;i<3&&valid;i++)if(nxts[type][i].size()==s.size())valid=false;
			if(valid)
			{
				int max_height=0;
				for(int i=0;i<3;i++)
				{
					getmax(max_height,GetHeight(nxts[type][i]));
					if(max_height>=ans[0])break;
				}
				if(max_height<ans[0])
				{
					ans.clear();
					ans.push_back(max_height);
					ans.push_back(type);
					for(int i=0;i<3;i++)ans.push_back(choice[i]);
					for(int i=0;i<3;i++)nxts_ans[i].swap(nxts[type][i]);
					assert(max_height>=best_ans);
					if(max_height==best_ans)return;
				}
			}
		}
	}
	for(int choice_idx=0;choice_idx<(int)FOUR_PERMUTS.size();choice_idx++)
	{
		const vector<int>&choice=FOUR_PERMUTS[choice_idx];
		vector<int>nxts[3];
		Filter(s,choice_idx,nxts,3);
		bool valid=true;
		//risking
		for(int i=0;i<3&&valid;i++)if(nxts[i].size()==s.size())valid=false;
		if(valid)
		{
			int max_height=0;
			for(int i=0;i<3;i++)
			{
				getmax(max_height,GetHeight(nxts[i]));
				if(max_height>=ans[0])break;
			}
			if(max_height<ans[0])
			{
				ans.clear();
				ans.push_back(max_height);
				ans.push_back(3);
				for(int i=0;i<4;i++)ans.push_back(choice[i]);
				for(int i=0;i<3;i++)nxts_ans[i].swap(nxts[i]);
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
void Build2()
{
	vector<int>s;
	s.resize(4);s.pop_back();
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
void Solve()
{
	vector<int>now;
	for(int i=0;i<(int)PERMUTATIONS.size();i++)now.push_back(i);
	if(true)
	{
		vector<int>nxts[3];
		Filter(now,find(THREE_PERMUTS.begin(),THREE_PERMUTS.end(),vector<int>{0,2,4})-THREE_PERMUTS.begin(),nxts,0);
		int id=getLightest(1,3,5)-1;
		now=nxts[id/2];
	}
	if(true)
	{
		vector<int>nxts[3];
		Filter(now,find(THREE_PERMUTS.begin(),THREE_PERMUTS.end(),vector<int>{1,3,5})-THREE_PERMUTS.begin(),nxts,1);
		int id=getMedian(2,4,6);
		now=nxts[id/2-1];
	}
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
	vector<pair<int,int> >stone;
	for(int i=0;i<6;i++)stone.push_back(make_pair(PERMUTATIONS[now[0]][i]+1,i+1));//weight,idx
	sort(stone.begin(),stone.end());
	vector<int>ans;
	for(int i=0;i<6;i++)ans.push_back(stone[i].second);
	answer(&ans[0]);
}
int main()
{
	Build1();Build2();Build3();
	int testcount=Init();
	while(testcount--)
	{
		orderCoins();
		Solve();
	}
}

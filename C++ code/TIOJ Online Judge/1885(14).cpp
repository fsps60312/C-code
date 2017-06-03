//#define SELF
#ifndef SELF
#include "lib1885.h"
#endif
#include<cstdio>
#include<cassert>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
int STEPS,JUDGE_ANS[7];
#ifdef SELF
int Init(){return 720;}
void orderCoins()
{
	STEPS=0;
	static int kase=0;
	int *s=JUDGE_ANS;
	for(int i=1;i<=6;i++)s[i]=i;
	for(int i=0;i<kase;i++)next_permutation(s+1,s+7);
	kase++;
}
int getLightest(int A,int B,int C)
{
	STEPS++;
	int s[3]={A,B,C};
	sort(s,s+3,[](int a,int b){return JUDGE_ANS[a]<JUDGE_ANS[b];});
	return s[0];
}
int getMedian(int A,int B,int C)
{
	STEPS++;
	int s[3]={A,B,C};
	sort(s,s+3,[](int a,int b){return JUDGE_ANS[a]<JUDGE_ANS[b];});
	return s[1];
}
int getHeaviest(int A,int B,int C)
{
	STEPS++;
	int s[3]={A,B,C};
	sort(s,s+3,[](int a,int b){return JUDGE_ANS[a]<JUDGE_ANS[b];});
	return s[2];
}
int getNextLightest(int A,int B,int C,int D)
{
	STEPS++;
	int s[3]={A,B,C};
	sort(s,s+3,[](int a,int b){return JUDGE_ANS[a]<JUDGE_ANS[b];});
	if(JUDGE_ANS[D]>JUDGE_ANS[s[2]])return s[0];
	for(int i=0;i<3;i++)if(JUDGE_ANS[s[i]]>JUDGE_ANS[D])return s[i];
	assert(0);return -1;
}
void answer(int *s)
{
	vector<pair<int,int> >tmp;
	for(int i=1;i<=6;i++)tmp.push_back(make_pair(JUDGE_ANS[i],i));
	sort(tmp.begin(),tmp.end());
	printf("Gives:");
	bool ac=true;
	for(int i=0;i<6;i++)ac&=(tmp[i].second==s[i]),printf(" %d(%d)",s[i],tmp[i].second);puts("");
	puts(ac?"AC":"WA");
	printf("STEPS=%d\n",STEPS);
	if(!ac||STEPS!=6)system("pause");
}
#endif
const int INF=2147483647;
void getmax(int&a,const int b){if(b>a)a=b;}
vector<vector<int> >PERMUTE,THREE,FOUR;
void Build1()
{
	vector<int>s{0,1,2,3,4,5};
	do
	{
		PERMUTE.push_back(s);
	}while(next_permutation(s.begin(),s.end()));
	for(int i=0;i<6;i++)for(int j=i+1;j<6;j++)for(int k=j+1;k<6;k++)
	{
		THREE.push_back(vector<int>{i,j,k});
		for(int d=0;d<6;d++)if(d!=i&&d!=j&&d!=k)FOUR.push_back(vector<int>{i,j,k,d});
	}
	assert(PERMUTE.size()==720&&THREE.size()==6*5*4/6&&FOUR.size()==6*5*4/2);
}
int RET_VAL1[720][6*5*4/6][3];
int RET_VAL2[720][6*5*4/2];
void Build2()
{
	for(int i=0;i<720;i++)
	{
		const vector<int>&permute=PERMUTE[i];
		for(int j=0;j<6*5*4/6;j++)
		{
			const vector<int>&choice=THREE[j];
			int *s=RET_VAL1[i][j];
			for(int k=0;k<3;k++)s[k]=k;
			sort(s,s+3,[&](int a,int b){return permute[choice[a]]<permute[choice[b]];});
		}
		for(int j=0;j<6*5*4/2;j++)
		{
			const vector<int>&choice=FOUR[j];
			int s[3]={0,1,2};
			sort(s,s+3,[&](int a,int b){return permute[choice[a]]<permute[choice[b]];});
			int &ans=RET_VAL2[i][j]=s[0];
			for(int i=0;i<3;i++)if(permute[choice[s[i]]]>permute[choice[3]]){ans=s[i];break;}
		}
	}
}
void Filter(const vector<int>&s,const int type,const int choice_idx,vector<int>nxt[3])
{
	if(type<3)
	{
		for(const int v:s)nxt[RET_VAL1[v][choice_idx][type]].push_back(v);
	}
	else for(const int v:s)nxt[RET_VAL2[v][choice_idx]].push_back(v);
}
map<vector<int>,vector<int> >HEIGHT;
const vector<int>&GetHeight(const vector<int>&s)
{
	{auto it=HEIGHT.find(s);if(it!=HEIGHT.end())return it->second;}
	vector<int>ans{INF};
	if((int)s.size()<=1){ans[0]=0;return HEIGHT[s]=ans;}
	int best_ans=-1;
	for(int n=s.size();n>1;)n=(n+2)/3,best_ans++;
	for(int type=0;type<3;type++)
	{
		for(int i=0;i<(int)THREE.size();i++)
		{
			const vector<int>&choice=THREE[i];
			vector<int>nxt[3];
			Filter(s,type,i,nxt);
			if(max(max(nxt[0].size(),nxt[1].size()),nxt[2].size())==s.size())continue;
			int max_height=0;
			for(int j=0;j<3;j++)
			{
				getmax(max_height,GetHeight(nxt[j])[0]);
				if(max_height>=ans[0])break;
			}
			if(max_height<ans[0])
			{
				ans=vector<int>{max_height,type,i};
				if(max_height==best_ans)goto return_now;
			}
		}
	}
	for(int i=0;i<(int)FOUR.size();i++)
	{
		const vector<int>&choice=FOUR[i];
		vector<int>nxt[3];
		Filter(s,3,i,nxt);
		if(max(max(nxt[0].size(),nxt[1].size()),nxt[2].size())==s.size())continue;
		int max_height=0;
		for(int j=0;j<3;j++)
		{
			getmax(max_height,GetHeight(nxt[j])[0]);
			if(max_height>=ans[0])break;
		}
		if(max_height<ans[0])
		{
			ans=vector<int>{max_height,3,i};
			if(max_height==best_ans)goto return_now;
		}
	}
	return_now:;
	assert(ans[0]!=INF);
	ans[0]++;
	return HEIGHT[s]=ans;
}
int main()
{
	Build1();Build2();
	int testcount=Init();
	while(testcount--)
	{
		orderCoins();
		vector<int>s;
		for(int i=0;i<720;i++)s.push_back(i);
		if(true)
		{
			vector<int>nxt[3];
			const int id=getLightest(1,2,3);
			Filter(s,0,0,nxt);
			s=nxt[id-1];
		}
		if(true)
		{
			vector<int>nxt[3];
			const int id=getMedian(4,5,6);
			Filter(s,1,6*5*4/6-1,nxt);
			s=nxt[id-4];
		}
		assert(s.size()==80);
		while((int)s.size()>1)
		{
			const vector<int>&choice=GetHeight(s);
			const vector<int>&three=(choice[1]<3?THREE:FOUR)[choice[2]];
			int id;
			switch(choice[1])
			{
				case 0:id=getLightest(three[0]+1,three[1]+1,three[2]+1);break;
				case 1:id=getMedian(three[0]+1,three[1]+1,three[2]+1);break;
				case 2:id=getHeaviest(three[0]+1,three[1]+1,three[2]+1);break;
				case 3:id=getNextLightest(three[0]+1,three[1]+1,three[2]+1,three[3]+1);break;
				default:assert(0);break;
			}
			vector<int>nxt[3];
			Filter(s,choice[1],choice[2],nxt);
			for(int i=0;;i++)if(id==three[i]+1){assert(i<3);s=nxt[i];break;}
		}
		assert((int)s.size()==1);
		vector<pair<int,int> >tmp;
		for(int i=0;i<6;i++)tmp.push_back(make_pair(PERMUTE[s[0]][i],i+1));
		sort(tmp.begin(),tmp.end());
		int ans[6];
		for(int i=0;i<6;i++)ans[i]=tmp[i].second;
		answer(ans);
	}
	return 0;
}

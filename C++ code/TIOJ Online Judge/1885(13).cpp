//#define SELF
#ifndef SELF
#include "lib1885.h"
#endif
#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
#ifdef SELF
int GRADER_ANSWER[7]={0,3,4,6,2,1,5},STEP_COUNT;
int Init(){return 720;}
void orderCoins()
{
	STEP_COUNT=0;
	vector<int>s;
	for(int i=1;i<=6;i++)s.push_back(i);
	static int kase=0;
	for(int i=0;i<kase;i++)next_permutation(s.begin(),s.end());
	for(int i=0;i<6;i++)GRADER_ANSWER[i+1]=s[i];
	kase++;
}
void answer(int *s)
{
	vector<pair<int,int> >tmp;
	for(int i=1;i<=6;i++)tmp.push_back(make_pair(GRADER_ANSWER[i],i));
	sort(tmp.begin(),tmp.end());
	bool correct=true;
	printf("Give:");
	for(int i=0;i<6;i++)correct&=(tmp[i].second==s[i]),printf(" %d(%d)",s[i],tmp[i].second);
	puts(correct?"Yes":"No");
	printf("step=%d\n",STEP_COUNT);
	if(!correct||STEP_COUNT!=6)system("pause");
}
int getLightest(int A,int B,int C)
{
	printf("getLightest(%d,%d,%d)\n",A,B,C);
	STEP_COUNT++;
	int s[3]={A,B,C};
	sort(s,s+3,[&](const int a,const int b){return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[0];
}
int getMedian(int A,int B,int C)
{
	printf("getMedian(%d,%d,%d)\n",A,B,C);
	STEP_COUNT++;
	int s[3]={A,B,C};
	sort(s,s+3,[&](const int a,const int b){return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[1];
}
int getHeaviest(int A,int B,int C)
{
	printf("getHeaviest(%d,%d,%d)\n",A,B,C);
	STEP_COUNT++;
	int s[3]={A,B,C};
	sort(s,s+3,[&](const int a,const int b){return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	return s[2];
}
int getNextLightest(int A,int B,int C,int D)
{
	printf("getNextLightest(%d,%d,%d,%d)\n",A,B,C,D);
	STEP_COUNT++;
	int s[3]={A,B,C};
	sort(s,s+3,[&](const int a,const int b){return GRADER_ANSWER[a]<GRADER_ANSWER[b];});
	if(GRADER_ANSWER[D]>GRADER_ANSWER[s[2]])return s[0];
	for(int i=0;i<3;i++)if(GRADER_ANSWER[s[i]]>GRADER_ANSWER[D])return s[i];
	assert(0);return -1;
}
#endif
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
vector<vector<int> >THREE,FOUR;
vector<vector<int> >PERMUTE;
void Build1()
{
	for(int i=0;i<6;i++)for(int j=i+1;j<6;j++)for(int k=j+1;k<6;k++)
	{
		THREE.push_back(vector<int>{i,j,k});
//		printf("(%d,%d,%d)\n",i,j,k);
		for(int d=0;d<6;d++)if(d!=i&&d!=j&&d!=k)FOUR.push_back(vector<int>{i,j,k,d});
	}
	assert((int)THREE.size()==6*5*4/6);
	assert((int)FOUR.size()==6*5*4/2);
	vector<int>s;
	for(int i=0;i<6;i++)s.push_back(i);
	do
	{
		PERMUTE.push_back(s);
	}while(next_permutation(s.begin(),s.end()));
	assert((int)PERMUTE.size()==720);
}
int RET_VAL1[3][720][6*5*4/6];
int RET_VAL2[720][6*5*4/2];
void Build2()
{
	for(int i=0;i<720;i++)
	{
		const vector<int>&permute=PERMUTE[i];
		assert((int)permute.size()==6);
		for(int j=0;j<6*5*4/6;j++)
		{
			const vector<int>&choice=THREE[j];
			assert((int)choice.size()==3);
			int s[3];
			for(int k=0;k<3;k++)s[k]=k;
			sort(s,s+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			for(int k=0;k<3;k++)RET_VAL1[k][i][j]=s[k];
		}
		for(int j=0;j<6*5*4/2;j++)
		{
			const vector<int>&choice=FOUR[j];
			assert((int)choice.size()==4);
			int s[3];
			for(int k=0;k<3;k++)s[k]=k;
			sort(s,s+3,[&](const int a,const int b)->bool{return permute[choice[a]]<permute[choice[b]];});
			int &ans=RET_VAL2[i][j]=s[0];
			for(int k=0;k<3;k++)if(permute[choice[s[k]]]>permute[choice[3]]){ans=s[k];break;}
		}
	}
}
void Filter(const vector<int>&s,const int type,const int choice_idx,vector<int>nxt[3])
{
	if(type<3)
	{
		for(const int v:s)nxt[RET_VAL1[type][v][choice_idx]].push_back(v);
	}
	else
	{
		for(const int v:s)nxt[RET_VAL2[v][choice_idx]].push_back(v);
	}
	assert(nxt[0].size()+nxt[1].size()+nxt[2].size()==s.size());
}
map<vector<int>,vector<int> >HEIGHT;
const vector<int>GetHeight(const vector<int>&s)
{
	{auto it=HEIGHT.find(s);if(it!=HEIGHT.end())return it->second;}
	vector<int>ans{INF};
	if((int)s.size()<=1){ans[0]=0;return HEIGHT[s]=ans;}
	int best_ans=-1;
	for(int n=s.size();n>1;)n=(n+2)/3,best_ans++;
	for(int type=0;type<3;type++)
	{
		for(int i=0;i<6*5*4/6;i++)
		{
			vector<int>nxt[3];
			Filter(s,type,i,nxt);
			if(max(nxt[0].size(),max(nxt[1].size(),nxt[2].size()))==s.size())continue;
			int max_height=0;
			for(int j=0;j<3;j++)
			{
				getmax(max_height,GetHeight(nxt[j])[0]);
				if(max_height>=ans[0])break;
			}
			assert(max_height>=best_ans);
			if(max_height<ans[0])
			{
				ans=vector<int>{max_height,type,i};
				if(max_height==best_ans)goto return_now;
			}
		}
	}
	for(int i=0;i<6*5*4/2;i++)
	{
		vector<int>nxt[3];
		Filter(s,3,i,nxt);
		if(max(nxt[0].size(),max(nxt[1].size(),nxt[2].size()))==s.size())continue;
		int max_height=0;
		for(int j=0;j<3;j++)
		{
			getmax(max_height,GetHeight(nxt[j])[0]);
			if(max_height>=ans[0])break;
		}
		assert(max_height>=best_ans);
		if(max_height<ans[0])
		{
			ans=vector<int>{max_height,3,i};
			if(max_height==best_ans)goto return_now;
		}
	}
	return_now:;
	ans[0]++;
	return HEIGHT[s]=ans;
}
int main()
{
	Build1();
	Build2();
	int testcount=Init();
	while(testcount--)
	{
		orderCoins();
		vector<int>s;
		for(int i=0;i<720;i++)s.push_back(i);
		if(true)
		{
			vector<int>nxt[3];
			Filter(s,0,find(THREE.begin(),THREE.end(),vector<int>{0,2,4})-THREE.begin(),nxt);
			s=nxt[getLightest(1,3,5)/2];
		}
		if(true)
		{
			vector<int>nxt[3];
			Filter(s,1,find(THREE.begin(),THREE.end(),vector<int>{1,3,5})-THREE.begin(),nxt);
			s=nxt[getMedian(2,4,6)/2-1];
		}
//		printf("s.size=%d\n",(int)s.size());
		while((int)s.size()>1)
		{
			const vector<int>choice=GetHeight(s);
			int id;
			const vector<int>&three=(choice[1]<3?THREE:FOUR)[choice[2]];
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
			int ti=-1;
			for(int i=0;i<3;i++)if(id==three[i]+1){ti=i;break;}
			assert(ti!=-1);
			s=nxt[ti];
		}
		assert(!s.empty());
		vector<pair<int,int> >ans;
		for(int i=0;i<6;i++)ans.push_back(make_pair(PERMUTE[s[0]][i],i));
		sort(ans.begin(),ans.end());
		static int ret[6];
		for(int i=0;i<6;i++)ret[i]=ans[i].second+1;
		answer(ret);
	}
	return 0;
}

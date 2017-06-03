#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
void Reverse(char *s)
{
	int n=-1;while(s[++n]);
	for(int l=0,r=n-1;l<r;l++,r--)swap(s[l],s[r]);
	for(int i=n;i<=1000001;i++)s[i]='0';
}
char L[1000002],R[1000002];
int SAME;
void CarryL(const int start)
{
	for(int i=start;L[i]>'9';i++)
	{
		L[i]=(char)(L[i]-10),++L[i+1];
		assert('0'<=L[i]&&L[i]<='9');
	}
}
//void CarryR(const int start)
//{
//	for(int i=start;R[i]<'0';i++)
//	{
//		R[i]=(char)(R[i]+10),--R[i+1];
//		assert('0'<=R[i]&&R[i]<='9');
//	}
//}
void Solve(vector<pair<int,vector<int> > >&ansl,vector<pair<int,vector<int> > >&ansr)
{
//	if(SAME==0){ansl.push_back(make_pair(0,vector<int>{1}));return;}
	assert(SAME>0);
	if(SAME==1){ansl.push_back(make_pair(0,vector<int>{R[0]-L[0]}));return;}
	if(L[0]!='0')ansl.push_back(make_pair(0,vector<int>{'9'-L[0]+1})),L[0]='9'+1,CarryL(0);
	if(R[0]!='0')ansr.push_back(make_pair(0,vector<int>{R[0]-'0'})),R[0]='0';
//	printf("(%d,%d)\n",(int)ansl.size(),(int)ansr.size());
	for(int move=2,pre_move=1,level=1;;pre_move=move,move<<=1,level++)
	{
		if(SAME<=move)
		{
//			puts("pass");
			if(true)
			{
				pair<int,vector<int> >s;
				s.first=level;
//				puts("a");
				for(int i=pre_move;i<SAME-1;i++)
				{
					if(L[i]!='0')s.second.push_back('9'-L[i]+1),L[i]='9'+1,CarryL(i);
					else s.second.push_back(0);
				}
//				puts("b");
				assert(L[SAME-1]<=R[SAME-1]);
				s.second.push_back(R[SAME-1]-L[SAME-1]),L[SAME-1]=R[SAME-1];
//				puts("c");
				while(!s.second.empty()&&s.second.back()==0)s.second.pop_back();
//				puts("d");
				if(!s.second.empty())ansl.push_back(s);
			}
			if(true)
			{
				pair<int,vector<int> >s;
				s.first=level;
				for(int i=pre_move;i<SAME-1;i++)s.second.push_back(R[i]-'0'),R[i]='0';
				assert(R[SAME-1]==L[SAME-1]);
				while(!s.second.empty()&&s.second.back()==0)s.second.pop_back();
				if(!s.second.empty())ansr.push_back(s);
			}
			break;
		}
		else
		{
			if(true)
			{
				pair<int,vector<int> >s;
				s.first=level;
				for(int i=pre_move;i<move;i++)
				{
					if(L[i]!='0')s.second.push_back('9'-L[i]+1),L[i]='9'+1,CarryL(i);
					else s.second.push_back(0);
				}
				while(!s.second.empty()&&s.second.back()==0)s.second.pop_back();
				if(!s.second.empty())ansl.push_back(s);
			}
			if(true)
			{
				pair<int,vector<int> >s;
				s.first=level;
				for(int i=pre_move;i<move;i++)s.second.push_back(R[i]-'0'),R[i]='0';
				while(!s.second.empty()&&s.second.back()==0)s.second.pop_back();
				if(!s.second.empty())ansr.push_back(s);
			}
		}
	}
}
//void CarryRasL(const int start)
//{
//	for(int i=start;R[i]>'9';i++)
//	{
//		R[i]=(char)(R[i]-10),++R[i+1];
//		assert('0'<=R[i]&&R[i]<='9');
//	}
//}
void CarryLasR(const int start)
{
	for(int i=start;L[i]<'0';i++)
	{
		L[i]=(char)(L[i]+10),--L[i+1];
		assert('0'<=L[i]&&L[i]<='9');
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%s%s",L,R);
	Reverse(L),Reverse(R);
	--L[0];CarryLasR(0);
	for(SAME=1000001;SAME>=0&&L[SAME]==R[SAME];--SAME);
	++SAME;
//	printf("SAME=%d\n",SAME);
	vector<pair<int,vector<int> > >ansl,ansr;
	Solve(ansl,ansr);
//	puts("Solved");
	if(!ansl.empty()&&!ansr.empty()&&ansl.back().first==ansr.back().first)
	{
		vector<int>&a=ansl.back().second,&b=ansr.back().second;
		a.resize(max(a.size(),b.size()),0);
		for(int i=0;i<(int)b.size();i++)a[i]+=b[i];
		ansr.pop_back();
		for(int i=0;i<(int)a.size();i++)if(a[i]>9)
		{
			if(i+1==(int)a.size())a.push_back(0);
			++a[i+1];
			a[i]-=10;
			assert(0<=a[i]&&a[i]<=9);
		}
	}
	while(!ansr.empty())ansl.push_back(ansr.back()),ansr.pop_back();
	printf("%d\n",(int)ansl.size());
	for(int i=0;i<(int)ansl.size();i++)
	{
		printf("%d ",ansl[i].first);
		const vector<int>&s=ansl[i].second;
		for(int j=(int)s.size()-1;j>=0;j--)putchar('0'+s[j]);
		puts("");
	}
	return 0;
}

//#include<cstdio>
#include<cassert>
#include<string>
#include<algorithm>
#include<iostream>
#include<set>
using namespace std;
int N,M;
string S[20],ANS[20];
int main()
{
//	freopen("in.txt","r",stdio);
	ios::sync_with_stdio(false);
	cin.tie(0);
	int testcount;cin>>testcount;
	while(testcount--)
	{
		cin>>N>>M;
		static bool s[20],t[20];
		for(int i=0;i<N;i++)cin>>S[i],s[i]=t[i]=true;
		for(int i=0,a,b;i<M;i++)
		{
			cin>>a>>b,--a,--b;
			ANS[b]=S[a];
			s[a]=t[b]=false;
		}
		for(int i=0,j=0;i<N;i++)if(s[i])
		{
			while(!t[j])++j;
			s[i]=t[j]=false;
			ANS[j]=S[i];
		}
		for(int i=0;i<N;i++)
		{
			if(i)cout<<' ';
			cout<<ANS[i];
		}
		cout<<'\n';
	}
	return 0;
}

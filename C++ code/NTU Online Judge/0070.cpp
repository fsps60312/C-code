//#include<cstdio>
#include<cassert>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
int N,M;
string S[20];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;cin>>testcount;
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)cin>>S[i];//,cout<<S[i]<<' ';
		for(int i=0,a,b;i<M;i++)
		{
			cin>>a>>b,--a,--b;
			if(a<b)rotate(S+a,S+(a+1),S+b);
			else rotate(S+b,S+a,S+(a+1));
		}
		for(int i=0;i<N;i++)
		{
			if(i)cout<<' ';
			cout<<S[i];
		}
		cout<<'\n';
	}
	return 0;
}

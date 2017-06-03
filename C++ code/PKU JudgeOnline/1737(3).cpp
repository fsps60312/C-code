#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Big
{
	vector<int>DATA;
	int Size()const{return DATA.size();}
	void Carry()
	{
		for(int i=0;i<Size();i++)
		{
			if(DATA[i]>=10||DATA[i]<0)
			{
				if(i+1==Size())DATA.push_back(0);
				const int goal=(DATA[i]%10+10)%10; 
				DATA[i+1]+=(DATA[i]-goal)/10;
				DATA[i]=goal;
			}
		}
		for(int i=Size()-1;i>=0&&DATA[i]==0;i--)DATA.pop_back();
	}
	Big(){}
	Big(int v)
	{
		DATA.clear(),DATA.push_back(v);
		Carry();
	}
	Big operator+(const Big &a)const
	{
		Big ans;
		ans.DATA.resize(max(Size(),a.Size()),0);
		for(int i=0;i<ans.Size();i++)
		{
			if(i<Size())ans.DATA[i]+=DATA[i];
			if(i<a.Size())ans.DATA[i]+=a.DATA[i];
		}
		ans.Carry();
		return ans;
	}
	Big operator-(const Big &a)const
	{
		Big ans;
		ans.DATA.resize(max(Size(),a.Size()),0);
		for(int i=0;i<ans.Size();i++)
		{
			ans.DATA[i]=0;
			if(i<Size())ans.DATA[i]+=DATA[i];
			if(i<a.Size())ans.DATA[i]-=a.DATA[i];
		}
		ans.Carry();
		return ans;
	}
	Big operator*(const Big &a)const
	{
		Big ans;
		ans.DATA.resize(Size()+a.Size()-1,0);
		for(int i=0;i<Size();i++)for(int j=0;j<a.Size();j++)ans.DATA[i+j]+=DATA[i]*a.DATA[j];
		ans.Carry();
		return ans;
	}
	void Print(){for(int i=Size()-1;i>=0;i--)putchar('0'+DATA[i]);puts("");}
};
Big CONNECT[51],UNCONNECT[51],ALL[51],C[51][51];
int main()
{
	for(int i=1;i<=50;i++)
	{
		C[i][0]=C[i][i]=1LL;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	ALL[0]=1LL;
	for(int i=1;i<=50;i++)
	{
		ALL[i]=ALL[i-1];
		for(int j=0;j<i-1;j++)ALL[i]=ALL[i]*2;
	}
	CONNECT[1]=1LL,UNCONNECT[1]=0LL;
	for(int n=2;n<=50;n++)
	{
		Big &ans=UNCONNECT[n]=0LL;
		for(int i=1;i<n;i++)ans=ans+C[n-1][i-1]*CONNECT[i]*ALL[n-i];
		CONNECT[n]=ALL[n]-ans;
	}
//	freopen("in.txt","r",stdin);
	for(int n;scanf("%d",&n)==1&&n;)CONNECT[n].Print();
	return 0;
}

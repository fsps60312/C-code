#include<cstdio>
#include<vector>
using namespace std;
int N,S[8];
vector<int>V,O;
int GetValue()
{
	int now1=1;
	V.clear(),O.clear();
	for(int i=0;i<8;i++)
	{
		const int &o=S[i];
		if(o==4)now1=now1*10+(i+2);
		else
		{
			V.push_back(now1);
			O.push_back(o);
			now1=i+2;
		}
	}
	V.push_back(now1);
	now1=V[0];
	int up=0,down=1,sign=1,now2=1;
	for(int i=0;i<O.size();i++)
	{
		const int &o=O[i];
		switch(o)
		{
			case 0:now1*=V[i+1];break;
			case 1:now2*=V[i+1];break;
			case 2:
			{
				up=up*now2+sign*down*now1,down*=now2;
				now1=V[i+1],now2=1;
				sign=1;
			}break;
			default:
			{
				up=up*now2+sign*down*now1,down*=now2;
				now1=V[i+1],now2=1;
				sign=-1;
			}
		}
	}
	up=up*now2+sign*down*now1,down*=now2;
	if(up%down!=0)return -1;
	return up/down;
}
int main()
{
	scanf("%d",&N);
	int ans=0;
	for(int s=0;s<390625;s++)
	{
		for(int i=0,j=s;i<8;i++,j/=5)S[i]=j%5;
		if(GetValue()==N)
		{
//			for(int i=0;i<8;i++)printf(" %d",S[i]);puts(""); 
			ans++;
		}
	}
	printf("%d\n",ans);
	return 0;
}

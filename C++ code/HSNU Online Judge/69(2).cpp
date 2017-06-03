#include<cstdio>
#include<vector>
using namespace std;
int N,S[8];
vector<int>V,O;
int GetValue()
{
	int now=1;
	V.clear(),O.clear();
	for(int i=0;i<8;i++)
	{
		const int &o=S[i];
		if(o==4)now=now*10+(i+2);
		else
		{
			V.push_back(now);
			O.push_back(o);
			now=i+2;
		}
	}
	V.push_back(now);
	now=V[0];
	int ans=0,sign=1,down=1;
	for(int i=0;i<O.size();i++)
	{
		const int &o=O[i];
		switch(o)
		{
			case 0:now*=V[i+1];break;
			case 1:
			{
				down*=V[i+1];
			}break;
			case 2:
			{
				if(now%down!=0)return -1;
				ans+=now/down*sign;
				now=V[i+1],down=1;
				sign=1;
			}break;
			default:
			{
				if(now%down!=0)return -1;
				ans+=now/down*sign;
				now=V[i+1],down=1;
				sign=-1;
			}
		}
	}
	if(now%down!=0)return -1;
	ans+=now/down*sign;
	return ans;
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

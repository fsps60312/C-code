#include<cstdio>
#include<set>
#include<vector>
#include<map>
using namespace std;
int S[16];
inline int cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int PERMUTATE[24][4]=
{
	{0,1,2,3},{0,1,3,2},{0,2,1,3},{0,2,3,1},{0,3,1,2},{0,3,2,1},
	{1,0,2,3},{1,0,3,2},{1,2,0,3},{1,2,3,0},{1,3,0,2},{1,3,2,0},
	{2,0,1,3},{2,0,3,1},{2,1,0,3},{2,1,3,0},{2,3,0,1},{2,3,1,0},
	{3,0,1,2},{3,0,2,1},{3,1,0,2},{3,1,2,0},{3,2,0,1},{3,2,1,0}
};
map<int,set<int> >SUM;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&S[0])==1&&S[0])
	{
		for(int i=1;i<16;i++)scanf("%d",&S[i]);
		for(int s=0;s<(1<<16);s++)
		{
			if(cntbits(s)!=4)continue;
			set<int>&sum=SUM[s];
			sum.clear();
			static vector<int>v;v.clear();
			for(int i=0;i<16;i++)if(s&(1<<i))v.push_back(S[i]);
			for(int i=0;i<24;i++)sum.insert(v[PERMUTATE[i][0]]+2*v[PERMUTATE[i][1]]+3*v[PERMUTATE[i][2]]+4*v[PERMUTATE[i][3]]);
		}
		puts("a");
		int ans=0;
		for(int s=0;s<(1<<16);s++)
		{
			if(cntbits(s)!=8)continue;
			for(int a=(s-1)&s,b;a;a=(a-1)&s)
			{
				if(cntbits(a)!=4)continue;
				b=s^a;
				set<int>&sa=SUM[a],&sb=SUM[b];
				for(auto it=sa.begin();it!=sa.end();it++)
				{
					if(sb.find(*it)!=sb.end())ans++;
				}
			}
			printf("s=%d\n",s);
		}
		printf("%d\n",ans);
	}
	return 0;
}

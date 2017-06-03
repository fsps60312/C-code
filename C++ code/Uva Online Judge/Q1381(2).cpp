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
int DP[1<<16];
bool VIS[16];
void GetSUM()
{
	SUM.clear();
	for(int s=0;s<(1<<16);s++)
	{
		DP[s]=0;
		if(cntbits(s)!=4)continue;
		set<int>&sum=SUM[s];sum.clear();
		static vector<int>v;v.clear();
		for(int i=0;i<16;i++)if(s&(1<<i))v.push_back(S[i]);
		for(int i=0;i<24;i++)sum.insert(v[PERMUTATE[i][0]]+2*v[PERMUTATE[i][1]]+3*v[PERMUTATE[i][2]]+4*v[PERMUTATE[i][3]]);
	}
}
void GetDP()
{
	for(auto it=SUM.begin();it!=SUM.end();it++)
	{
		const int &s=it->first;
		const set<int>&sum=it->second;
		for(int i=0;i<16;i++)VIS[i]=((s&(1<<i))!=0);
		for(int i1=0;i1<16;i1++)
		{
			if(VIS[i1])continue;
			VIS[i1]=true;
			for(int i2=0;i2<16;i2++)
			{
				if(VIS[i2])continue;
				VIS[i2]=true;
				for(int i3=0;i3<16;i3++)
				{
					if(VIS[i3])continue;
					VIS[i3]=true;
					for(int i4=0;i4<16;i4++)
					{
						if(VIS[i4])continue;
						const int &v=S[i1]+2*S[i2]+3*S[i3]+4*S[i4];
						if(sum.find(v)!=sum.end())DP[s+(1<<i1)+(1<<i2)+(1<<i3)+(1<<i4)]++;
					}
					VIS[i3]=false;
				}
				VIS[i2]=false;
			}
			VIS[i1]=false;
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&S[0])==1&&S[0])
	{
		for(int i=1;i<16;i++)scanf("%d",&S[i]);
		GetSUM();
		GetDP();
		int ans=0;
		for(int s=0;s<(1<<16);s++)
		{
			if(cntbits(s)!=8)continue;
			ans+=DP[s]*DP[((1<<16)-1)^s];
			DP[s]=0;
		}
		printf("%d\n",ans);
	}
	return 0;
}

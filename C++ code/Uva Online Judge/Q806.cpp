#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int N,QUAD[64][64];
void termin(){int a[1];for(int i=0;;i--)a[i]=9;}
bool allis(int x,int y,int d,int v)
{
	for(int i=0;i<d;i++)for(int j=0;j<d;j++)if(QUAD[x+i][y+j]!=v)return false;
	return true;
}
void dfs(vector<int> &ANS,vector<int> &BLACK,int x,int y,int d)
{
	if(allis(x,y,d,0))
	{
		ANS.push_back(0);
		BLACK.push_back(0);
		return;
	}
	else if(allis(x,y,d,1))
	{
		ANS.push_back(0);
		BLACK.push_back(1);
		return;
	}
	int idx=ANS.size();
	int hd=d/2;
	for(int i=0;i<4;i++)
	{
		dfs(ANS,BLACK,x+hd*(i%2),y+hd*(i/2),hd);
		for(int j=idx;j<ANS.size();j++)
		{
			ANS[j]*=5;
			ANS[j]+=i+1;
		}
		idx=ANS.size();
	}
}
void decodemap(vector<int> &ANS,vector<int> &BLACK)
{
	for(int i=0;i<N;i++)
	{
		char c;
		for(int j=0;j<N;j++)
		{
			scanf("%c",&c);
			if(c=='0'||c=='1')QUAD[j][i]=c-'0';
			else j--;
		}
	}
	if(allis(0,0,N,0))return;
	dfs(ANS,BLACK,0,0,N);
}
void drawblack(int x,int y,int d,int v)
{
	if(v==0)
	{
		for(int i=0;i<d;i++)for(int j=0;j<d;j++)QUAD[x+i][y+j]=1;
		return;
	}
	int ch=v%5-1;
	int hd=d/2;
	drawblack(x+hd*(ch%2),y+hd*(ch/2),hd,v/5);
}
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		if(kase>1)printf("\n");
		printf("Image %d\n",kase++);
		if(N>0)
		{
			vector<int> ans,tans,black;
			decodemap(tans,black);
			if(tans.size())
			{
				for(int i=0;i<tans.size();i++)
				{
					if(black[i])ans.push_back(tans[i]);
				}
				sort(ans.begin(),ans.end());
				if(!ans.size())termin();
				for(int i=0;i<ans.size();i++)
				{
					if(i&&i%12==0)printf("\n");
					else if(i>0)printf(" ");
					printf("%d",ans[i]);
				}
				printf("\n");
			}
			printf("Total number of black nodes = %d\n",ans.size());
		}
		else
		{
			N=-N;
			for(int i=0;i<N;i++)for(int j=0;j<N;j++)QUAD[i][j]=0;
			for(int j;;)
			{
				scanf("%d",&j);
				if(j==-1)break;
				drawblack(0,0,N,j);
			}
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<N;j++)
				{
					printf(QUAD[j][i]?"*":".");
				}
				printf("\n");
			}
		}
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int SG[51][51];
int R,C;
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("coins.in","r",stdin);
	freopen("coins.out","w",stdout);
	for(int i=0;i<=50;i++)SG[i][0]=SG[0][i]=0;
	for(int r=1;r<=50;r++)for(int c=1;c<=50;c++)
	{
		vector<int>tmp;
		for(int i=0;i<r;i++)for(int j=0;j<c;j++)
		{
			tmp.push_back(SG[i][j]^SG[r][j]^SG[i][c]);
		}
		sort(tmp.begin(),tmp.end()),tmp.resize(unique(tmp.begin(),tmp.end())-tmp.begin());
		for(int &i=SG[r][c]=0;i<(int)tmp.size()&&tmp[i]==i;i++);
	}
	while(scanf("%d%d",&R,&C)==2)
	{
		int ans=0;
		static bool is_head_up[51][51];
		for(int r=1;r<=R;r++)for(int c=1;c<=C;c++)
		{
			char type=getchar();
			switch(type)
			{
				case'0':is_head_up[r][c]=false;break;
				case'1':ans^=SG[r][c],is_head_up[r][c]=true;break;
				default:c--;break;
			}
		}
		printf("%s\n",ans==0?"Betty":"Ann");
		if(ans!=0)
		{
//			printf("ans=%d,%d\n",ans,SG[3][3]);
			for(int r=1;r<=R;r++)for(int c=1;c<=C;c++)if(is_head_up[r][c])
			{
				for(int i=0;i<r;i++)for(int j=0;j<c;j++)
				{
					if((SG[r][c]^SG[i][c]^SG[r][j]^SG[i][j])==ans)
					{
						printf("%d %d\n%d %d\n",r,c,i,j);
						goto index_found;
					}
				}
			}
			assert(0);
			index_found:;
		}
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
bool IsUpper(const char c){return 'A'<=c&&c<='Z';}
char P[5][7];
char S[1000000];
bool Input()
{
	fgets(P[0],INF,stdin);
	if(P[0][0]=='Z')return false;
	for(int i=1;i<5;i++)fgets(P[i],INF,stdin);
	for(int i=0;;)
	{
		fgets(S+i,INF,stdin);
		while(IsUpper(S[i]))i++;
		if(S[i]=='0')return true;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(Input())
	{
		int r=-1,c;
		for(int i=0;i<5;i++)for(int j=0;j<5;j++)if(P[i][j]==' ')
		{
			assert(r==-1);
			r=i,c=j;
		}
		assert(r!=-1);
		bool valid=true;
		for(int i=0;valid&&S[i]!='0';i++)
		{
			assert(P[r][c]==' ');
			switch(S[i])
			{
				case'A':valid=(r==0?false:(swap(P[r][c],P[r-1][c]),--r,true));break;
				case'B':valid=(r==4?false:(swap(P[r][c],P[r+1][c]),++r,true));break;
				case'R':valid=(c==4?false:(swap(P[r][c],P[r][c+1]),++c,true));break;
				case'L':valid=(c==0?false:(swap(P[r][c],P[r][c-1]),--c,true));break;
				default:valid=false;break;//printf("S[%d]=%c\n",i,S[i]),assert(0);break;
			}
		}
		static int kase=0;
		if(kase)puts("");
		printf("Puzzle #%d:\n",++kase);
		if(!valid)puts("This puzzle has no final configuration.");
		else
		{
			for(int i=0;i<5;i++)
			{
				for(int j=0;j<5;j++)
				{
					if(j)putchar(' ');
					putchar(P[i][j]);
				}
				puts("");
			}
		}
	}
	return 0;
}

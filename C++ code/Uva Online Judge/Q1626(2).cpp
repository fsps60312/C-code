#include<cstdio>
#include<cstdlib>
char B[101];
int T,DP[100][100],N;
struct Point
{
	int type,i;
};
Point PRE[100][100];
char anotherbracket(char a)
{
	switch(a)
	{
		case '[':return ']';
		case ']':return '[';
		case '(':return ')';
		case ')':return '(';
		default :return 0;
	}
}
bool isleft(char a){return a=='['||a=='(';}
bool samebracket(char a,char b)
{
	return isleft(a)&&b==anotherbracket(a);
}
void dfs_print(int l,int r)
{
	if(l>r)return;
	//printf("%d %d\n",l,r);
	Point &p=PRE[l][r];
	if(l==r)
	{
		char a=anotherbracket(B[l]);
		if(isleft(B[l]))printf("%c%c",B[l],a);
		else printf("%c%c",a,B[l]);
	}
	else if(p.type==0)
	{
		printf("%c",B[l]);
		dfs_print(l+1,r-1);
		printf("%c",B[r]);
	}
	else if(p.type==1)
	{
		dfs_print(l,p.i);
		dfs_print(p.i+1,r);
	}
}
bool getmin(int &a,int b)
{
	if(b<a)
	{
		a=b;
		return true;
	}
	return false;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	gets(B);
	sscanf(B,"%d",&T);
	int kase=0;
	while(T--)
	{
		gets(B);gets(B);
		N=-1;while(B[++N]);
		//printf("%s\n",B);
		if(kase++)printf("\n");
		if(N==0)
		{
			printf("\n");
			continue;
		}
		//printf("N=%d\n",N);
		for(int l=0;l<N;l++)
		{
			for(int r=l;r<N;r++)
			{
				DP[l][r]=2147483647;
				PRE[l][r]=(Point){-1,-1};
			}
		}
		for(int l=0;l<N;l++)DP[l][l]=1;
		for(int l=0;l+1<N;l++)
		{
			if(samebracket(B[l],B[l+1]))
			{
				DP[l][l+1]=0;
				PRE[l][l+1].type=0;
			}
			else
			{
				DP[l][l+1]=2;
				PRE[l][l+1]=(Point){1,l};
			}
		}
		for(int l=2;l<N;l++)
		{
			for(int p=0;p+l<N;p++)
			{
				if(samebracket(B[p],B[p+l]))
				{
					if(getmin(DP[p][p+l],DP[p+1][p+l-1]))
					{
						PRE[p][p+l].type=0;
					}
				}
				for(int i=0;i<l;i++)
				{
					if(getmin(DP[p][p+l],DP[p][p+i]+DP[p+i+1][p+l]))
					{
						PRE[p][p+l]=(Point){1,p+i};
					}
				}
			}
		}
		dfs_print(0,N-1);
		printf("\n");
	}
	return 0;
}

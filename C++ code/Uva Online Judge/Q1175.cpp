#include<cstdio>
#include<queue>
using namespace std;
short GIRL_PREFER[1001][1001],BOY_PREFER[1001][1001],GIRL_SELECT[1001],BOY_ENGAGE[1001];
short T,N;
char c,tstr[10];
inline bool isnum(char a){return a>='0'&&a<='9';}
inline char nextnum()
{
	while(1)
	{
		c=getchar();
		if(isnum(c))return c;
	}
}
inline void readshort(short &a)
{
	a=nextnum()-'0';
	while(1)
	{
		c=getchar();
		if(isnum(c))
		{
			a*=10;
			a+=c-'0';
		}
		else break;
	}
}
inline void readshorts(short *a,short l)
{
	while(l--)
	{
		readshort(*a);
		a++;
	}
}
char *t;
inline void putshort(short &a)
{
	t=tstr;
	do
	{
		*(t++)='0'+a%10;
		a/=10;
	}while(a);
	t--;
	do
	{
		putchar(*t);
	}while((t--)!=tstr);
}
int main()
{
	short kase=0;
	//freopen("in.txt","r",stdin);
	readshort(T);
	while(T--)
	{
		readshort(N);
		for(short i=1;i<=N;i++)
		{
				readshorts(GIRL_PREFER[i]+1,N);
			/*for(short j=1;j<=N;j++)
			{
				//short a;scanf("%d",&a);
				//GIRL_PREFER[i][j]=a;//girl i's j-th is boy a
			}*/
		}
		for(short i=1;i<=N;i++)
		{
			for(short j=1;j<=N;j++)
			{
				short a;readshort(a);
				BOY_PREFER[i][a]=j;//boy i likes a j-th
			}
		}
		queue<int> q;
		for(short i=1;i<=N;i++)
		{
			GIRL_SELECT[i]=1;
			BOY_ENGAGE[i]=1001;
			q.push(i);
		}
		while(!q.empty())
		{
			short girl=q.front();q.pop();
			short &boy=GIRL_PREFER[girl][GIRL_SELECT[girl]];
			short &pre_girl=BOY_ENGAGE[boy];
			short *boy_prefer=BOY_PREFER[boy];
			if(pre_girl==1001)
			{
				pre_girl=girl;
			}
			else if(boy_prefer[girl]<boy_prefer[pre_girl])
			{
				GIRL_SELECT[pre_girl]++;
				q.push(pre_girl);
				pre_girl=girl;
			}
			else
			{
				GIRL_SELECT[girl]++;
				q.push(girl);
			}
		}
		for(short i=1;i<=N;i++)
		{
			GIRL_SELECT[BOY_ENGAGE[i]]=i;
		}
		if(kase++)putchar('\n');
		for(short *i=GIRL_SELECT+1;N--;i++)
		{
			putshort(*i);
			//printf("%d",GIRL_SELECT[i]);
			putchar('\n');
			/*for(short j=1;j<=N;j++)
			{
				if(GIRL_PREFER[i][j]==GIRL_SELECT[i])
				{
					printf(" %d",j);
					break;
				}
			}
			printf("\n");*/
		}
	}
	return 0;
}

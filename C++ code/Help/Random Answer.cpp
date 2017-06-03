#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;
int A,B;
int main()
{
	srand(time(NULL));
	freopen("out.txt","w",stdout);
	scanf("%d%d",&A,&B);
	int cnt=0;
	while(A--)
	{
		printf("%d: %c\n",++cnt,'A'+rand()%4);
	}
	while(B--)
	{
		int v=rand()%(1<<5);
		while(v==0)v=rand()%(1<<5);
		printf("%d: ",++cnt);
		for(int i=0;i<5;i++)if(v&(1<<i))printf("%c",'A'+i);
		puts("");
	}
	system("pause");
	return 0;
}

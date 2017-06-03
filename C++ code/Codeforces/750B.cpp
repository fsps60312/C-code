#include<cstdio>
#include<cassert>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		int t1=0;
		bool answer=true;
		while(N--)
		{
			static char directionStr[6];
			int length;
			scanf("%d%s",&length,directionStr);
			if(!answer)continue;
			switch(directionStr[0])
			{
				case'S':
				{
					if(t1+length>20000)answer=false;
					else t1+=length;
				}break;
				case'N':
				{
					if(t1-length<0)answer=false;
					else t1-=length;
				}break;
				case'E':
				{
					if(t1==0||t1==20000)answer=false;
				}break;
				case'W':
				{
					if(t1==0||t1==20000)answer=false;
				}break;
				default:assert(0);break;
			}
//			printf("t1=%.10f\n",t1);
		}
		if(t1!=0)answer=false;
//		printf("%.10f %.10f\n",PI,t1);
		puts(answer?"YES":"NO");
	}
	return 0;
}

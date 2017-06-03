#include<cstdio>
//#include<cassert>
using namespace std;
template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
int N,M;
void assert(bool valid){if(!valid)for(;;){int a=1,b=0;a/=b+1;printf("%d %d",a,b);}}
int main()
{
//	assert(0);
	scanf("%d%d",&N,&M);
	int max_x=0,min_x=0,max_y=0,min_y=0,x=0,y=0;
	for(int now_x=1,now_y=1,cnt=0;;)
	{
//		assert(++cnt<45000);
		printf("%d %d\n",now_x,now_y);
		fflush(stdout);
//		cout.flush();
		for(int i=0;i<1000;i++);
		static char respond[100];
		scanf("%s",respond);
		if(respond[1]=='E')return 0;
		switch(respond[0])
		{
			case'U':--x,--now_x;break;
			case'D':++x,++now_x;break;
			case'L':--y,--now_y;break;
			case'R':++y,++now_y;break;
			default:assert(0);break;
		}
		getmax(max_x,x),getmin(min_x,x);
		getmax(max_y,y),getmin(min_y,y);
//		printf("(%d,%d)\n",x,y);
		int extended=false;
		if(now_y<1+(y-min_y))now_y=1+(y-min_y),extended=true;
		if(now_x<1+(x-min_x))now_x=1+(x-min_x),extended=true;
		if(!extended)++now_x;
		if(now_x>N-(max_x-x))++now_y,now_x=1+(x-min_x);
		assert(now_y<=M-(max_y-y));
	}
}

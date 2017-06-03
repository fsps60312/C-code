#include<cstdio>
#include<cassert>
using namespace std;
int *S=new int[6]+1;
void Print(const int upon,const int down)
{
	if(down==0){printf("0.00");return;}
	int ans=upon*1000/down;
	if(ans%10>=5)ans+=10;
	ans/=10;
	printf("%d.%02d",ans/100,ans%100);
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=-1;i<=4;i++)S[i]=0;
	for(int v;scanf("%d",&v)==1;)if(v>=-1&&v<=4)++S[v];
	Print(S[4]+S[3]+S[2]+S[1],S[4]+S[3]+S[2]+S[1]+S[0]);
	putchar(' ');
	Print(S[4]+S[3]+S[2]+S[1]+S[-1],S[4]+S[3]+S[2]+S[1]+S[0]+S[-1]);
	putchar(' ');
	Print(S[4]*4+S[3]*3+S[2]*2+S[1]*1,S[4]+S[3]+S[2]+S[1]+S[0]);
	putchar('\n');
	return 0;
}

#include<cstdio>
void getmax(int &a,const int b){if(b>a)a=b;}
int CntBits(int v)
{
	v=(v&0x55555555)+((v&0xaaaaaaaa)>>1);
	v=(v&0x33333333)+((v&0xcccccccc)>>2);
	v=(v&0x0f0f0f0f)+((v&0xf0f0f0f0)>>4);
	v=(v&0x00ff00ff)+((v&0xff00ff00)>>8);
	v=(v&0x0000ffff)+((v&0xffff0000)>>16);
	return v;
}
int N;
int LIKE[100],HATE[100],ALL;
int Solve(const int s)
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		int achieve=CntBits(s&LIKE[i])+CntBits((ALL^s)&HATE[i]);
		if(!achieve)return -1;
		else ans+=achieve;
	}
	return ans;
}
int main()
{
	scanf("%d",&N);
	ALL=(1<<20)-1;
	for(int i=0,ln,hn;i<N;i++)
	{
		static char like[21],hate[21];scanf("%d%d%s%s",&ln,&hn,like,hate);
		int &tl=LIKE[i]=0,&th=HATE[i]=0;
		for(int j=0;j<ln;j++)tl|=1<<(like[j]-'A');
		for(int j=0;j<hn;j++)th|=1<<(hate[j]-'A');
	}
	int ans=-1;
	for(int i=0;i<=ALL;i++)getmax(ans,Solve(i));
	printf("%d\n",ans);
	return 0;
}

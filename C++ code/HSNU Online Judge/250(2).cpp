#include<cstdio>
#include<cassert>
using namespace std;
int N,MOD;
int POW[1000000];
char S[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&MOD)==2)
	{
//		MOD=1000000000;
		POW[0]=1;
		for(int i=1;i<N;i++)(POW[i]=POW[i-1]*2)%=MOD;
		scanf("%s",&S);
		int ans=1;
		for(int i=0,h=0,mx=0,mn=0;i<N;i++)
		{
			if(S[i]=='P'&&h-1>=mx-2)
			{
				if(h-1>=mx-1)
				{
					int cnt=(N-1-i+1)/2;
					(ans+=POW[cnt])%=MOD;
//					printf("mx=%d,h=%d,i=%d,cnt=%d\n",mx,h,i,cnt);
				}
				if(h+1<=mn+2)
				{
					int cnt=(N-1-i)/2;
					(ans+=POW[cnt])%=MOD;
//					printf("mn=%d,h=%d,i=%d,cnt=%d\n",mn,h,i,cnt);
				}
				if(h-1>=mx-1&&h+1<=mn+2)(ans+=MOD-1)%=MOD;
			}
			if(S[i]=='L')h--;
			else if(S[i]=='P')h++;
			else assert(0);
			if(h>mx)mx=h;
			if(h<mn)mn=h;
		}
		//PLPPL
		//0a:LLPLP,LLPPL,LPLLP,LPLPL
		//0b:LPLPL,LPLPP,LPPLL,LPPLP
		//   -1
		//2a:
		//2b:PLLPL,PLLPP
		//3a:PLPLL,PLPLP
		//3b:PLPLP
		//   -1
		printf("%d\n",ans);
	}
	return 0;
}

#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
int N,T[1000000],S[1000000],F[1000000];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		scanf("%d%d%d",&T[i],&S[i],&F[i]);
	}
	for(int i=0;i<N;i++)
	{
		int ans=0;
		for(int j=0;j<N;j++)
		{
			if(i==j)continue;
			int t1=T[i],t2=T[j],s1=S[i],s2=S[j],f1=F[i],f2=F[j],d1,d2;
			if(s1<=f1)d1=1;
			else d1=-1;
			if(s2<=f2)d2=1;
			else d2=-1;
			if(t1<t2)s1+=d1*(t2-t1),t1=t2;
			else s2+=d2*(t1-t2),t2=t1;
			int a1=t1+abs(f1-s1),a2=t2+abs(f2-s2);
			if(a1>a2)f1-=d1*(a1-a2);
			else f2-=d2*(a2-a1);
			assert(abs(f1-s1)==abs(f2-s2));
//			printf("(%d,%d,%d),(%d,%d,%d)\n",s1,f1,d1,s2,f2,d2);
			if((f1-s1)/d1>=0&&(f2-s2)/d2>=0)
			{
//				printf("enter\n");
//				int ta=ans;
				if(s1<=f1&&f2<=s2)
				{
					if(s1<=f2&&f2<=f1)ans++;
					else if(s1<=s2&&s2<=f1)ans++;
				}
				else if(s1<=f1&&s2<=f2)
				{
					if(s1==s2)ans++;
				}
				else if(f1<=s1&&f2<=s2)
				{
					if(s1==s2)ans++;
				}
				else if(f1<=s1&&s2<=f2)
				{
					if(f1<=s2&&s2<=s1)ans++;
					else if(f1<=f2&&f2<=s1)ans++;
				}
//				if(ans>ta)printf("(%d,%d)\n",i,j);
			}
		}
		if(i)printf(" ");
		printf("%d",ans);
	}
	puts("");
	return 0;
}

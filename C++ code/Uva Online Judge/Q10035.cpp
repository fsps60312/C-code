#include<bits/stdc++.h>
using namespace std;
char A[11],B[11],C[12];
int main()
{
	while(scanf("%s%s",A,B)==2&&!(A[0]=='0'&&B[0]=='0'&&!A[1]&&!B[1]))
	{
		static int a,b,i;
		a=b=-1;
		while(A[++a]);while(B[++b]);
		for(i=0,a--,b--;a>=0||b>=0;a--,b--,i++)
		{
			C[i]='\0';
			if(a>=0)C[i]+=A[a]-'0';
			if(b>=0)C[i]+=B[b]-'0';
//			printf("%c",C[i]+'0');
		}
		int ans=0;
		for(a=0;a<i;a++)
		{
			static char ten=10;
			if(C[a]>=ten)C[a]-=ten,C[a+1]++,ans++;
		}
		if(ans==0)puts("No carry operation.");
		else if(ans==1)puts("1 carry operation.");
		else printf("%d carry operations.\n",ans);
	}
	return 0;
}

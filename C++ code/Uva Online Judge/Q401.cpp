#include<cstdio>
#include<cstdlib>
char S[30];
bool ismirrored(char a,char b)
{
	//printf("\n%c %c",a,b);
	if(a==b)
	{
		char c[]="AMYO1HTIUV8WX";
		for(int i=0;c[i];i++)
		{
			if(a==c[i]) return true;
		}
		return false;
	}
	if(a>b)
	{
		char c=a;
		a=b;
		b=c;
	}
	return (a=='5'&&b=='Z')||(a=='2'&&b=='S')||(a=='3'&&b=='E')||(a=='J'&&b=='L');
}
int main()
{
	//printf("%d %d\n",'0','A');
	while(scanf("%s",S)==1)
	{
		int n=-1;
		while(S[++n]);
		//printf("%d %c\n",n,S[n-1]);
		printf("%s -- is ",S);
		bool palindrome=true,mirrored=true;
		for(int i=0;i<=n/2&&(palindrome||mirrored);i++)
		{
			if(S[i]!=S[n-1-i]) palindrome=false;
			if(!ismirrored(S[i],S[n-1-i])) mirrored=false;
			//printf(" %d %d %d\n",i,palindrome,mirrored);
		}
		if(palindrome)
		{
			if(mirrored) printf("a mirrored palindrome.");
			else printf("a regular palindrome.");
		}
		else
		{
			if(mirrored) printf("a mirrored string.");
			else printf("not a palindrome.");
		}
		printf("\n\n");
	}
	return 0;
}

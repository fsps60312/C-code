#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
char A[105],B[105],S[105];
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%s%s",A,B)==2)
	{
		static int kase=0;
		if(kase++)puts("");
		if(true)
		{
			N=-1;while(A[++N])A[N]-='0';
			reverse(A,A+N);
			for(int i=N;i<105;i++)A[i]=0;
			M=-1;while(B[++M])B[M]-='0';
			reverse(B,B+M);
			for(int i=M;i<105;i++)B[i]=0;
		}
		for(int i=0;i<105;i++)S[i]=A[i]+B[i];
		for(bool changed=true;changed;)
		{
			changed=false;
			for(int i=0;i<105;i++)
			{
				if(S[i]>=2)
				{
					if(i==0)S[i]-=2,S[i+1]++,changed=true;
					else if(i==1)S[i-1]++,S[i]-=2,S[i+1]++,changed=true;
					else S[i-2]++,S[i]-=2,S[i+1]++,changed=true;
				}
				else if(i>0&&S[i-1]>=1&&S[i]>=1)
				{
					S[i-1]--,S[i]--,S[i+1]++,changed=true;
				}
			}
		}
		vector<char>ans;
		for(int i=0;i<105;i++)ans.push_back('0'+S[i]);
		while((int)ans.size()>1&&ans.back()=='0')ans.pop_back();
		for(int i=(int)ans.size()-1;i>=0;i--)putchar(ans[i]);puts("");
	}
	return 0;
}

#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef __int128 ULL;
//typedef unsigned long long ULL;
void getmax(int &a,const int b){if(b>a)a=b;}
int Width(ULL n){int ans=0;for(;n;n/=10,++ans);return ans;}
void PutLine(ULL n,const int width)
{
	vector<char>s;
	if(n==0)s.push_back('0');
	for(;n;n/=10)s.push_back('0'+n%10);
	while((int)s.size()<width)s.push_back(' ');
	assert((int)s.size()==width);
	for(int i=width-1;i>=0;i--)putchar(s[i]);
	puts("");
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(long long _a,_b;scanf("%lld%lld",&_a,&_b)==2;)
	{
		ULL a=_a,b=_b;
		vector<ULL>ans;
		ans.push_back(a);
		ans.push_back(b);
		if(a==0||b==0)ans.push_back(0);
		else
		{
			ULL result=a*b;
			int cnt=0;
			for(;b;b/=10)
			{
				ans.push_back(a*(b%10));
				if(b%10)cnt++;
			}
			if(cnt<=1)
			{
				while((int)ans.size()>2)ans.pop_back();
			}
			ans.push_back(result);
		}
		int upw=1,downw=Width(ans.back()),width=1;
		for(int i=0;i<2;i++)getmax(upw,Width(ans[i]));
		for(int i=2;i+1<(int)ans.size();i++)getmax(width,Width(ans[i]));
		getmax(width,upw),getmax(width,downw);
		PutLine(ans[0],width);
		PutLine(ans[1],width);
		for(int i=0;i<width-upw;i++)putchar(' ');
		for(int i=0;i<upw;i++)putchar('-');
		puts("");
		if((int)ans.size()>3)
		{
			for(int i=2;i+1<(int)ans.size();i++)if(ans[i])PutLine(ans[i],width-(i-2));
			for(int i=0;i<width-downw;i++)putchar(' ');
			for(int i=0;i<downw;i++)putchar('-');
			puts("");
		}
		PutLine(ans.back(),width);
		puts("");
	}
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
vector<int>ReadLine()
{
	vector<int>ans;
	for(;;)
	{
		char c=getchar();
		while(c<'0'||'9'<c)
		{
			if(c=='\n'||c==EOF)goto go_ret;
			c=getchar();
		}
		int v=0;
		while('0'<=c&&c<='9')v=v*10+(c-'0'),c=getchar();
		ans.push_back(v);
		if(c=='\n'||c==EOF)goto go_ret;
	}
	go_ret:;
	return ans;
}
vector<int>X,Y;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount=ReadLine()[0];
	while(testcount--)
	{
		X=ReadLine(),Y=ReadLine();
		sort(X.begin(),X.end()),sort(Y.begin(),Y.end());
		const int n=X.size();
//		printf("n=%d\n",n);
		double ans=0.0;
		for(int i=0;i<n;i++)ans+=sqrt(X[i]*X[i]+Y[n-1-i]*Y[n-1-i]);//,printf("%d %d\n",X[i],Y[i]);
		printf("%d\n",(int)ans);
	}
	return 0;
}

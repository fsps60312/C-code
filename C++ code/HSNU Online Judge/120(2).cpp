#include"interactive/120.h"
#include<cstdio>
#include<algorithm>
using namespace std;
int N;
vector<int>S;
void Insert(const int idx,const int v)
{
	S.push_back(int());
	for(int i=S.size()-1;i>idx;i--)S[i]=S[i-1];
	S[idx]=v;
}
int main()
{
	N=GetN();
	S.push_back(1),S.push_back(2);
	for(int sz=2;sz<N;sz++)
	{
		int v=Med3(sz+1,S[0],S[sz-1]);
		if(v!=sz+1)
		{
			v=Med3(sz+1,S[0],S[1]);
			if(v==S[0])Insert(0,sz+1);
			else Insert(sz,sz+1);
		}
		else
		{
			int l=0,r=sz-1,mid;
			while(r-l>1)
			{
				mid=(r+l)/2;
				v=Med3(sz+1,S[l],S[mid]);
				if(v==sz+1)r=mid;
				else l=mid+1;
			}
			Insert(r,sz+1);
		}
	}
	Answer(S[N/2]);
	return 0;
}

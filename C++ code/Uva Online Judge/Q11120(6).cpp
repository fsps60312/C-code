#include<cstdio>
#include<vector>
#include<cassert>
#include<queue>
using namespace std;
int N;
queue<int>BUFFER;
struct Deq
{
	vector<int>s;
	int l,r;
	void clear(){s.clear();l=0,r=-1;}
	void push_back(const int v){s.push_back(v);r++;}
	void pop_front(){l++;}
	int front()const{return s[l];}
	int back()const{return s[r];}
	bool Subtractable(const vector<int>&a)const
	{
		assert(front());
		if(r-a.size()+1!=l)return l<r-a.size()+1;
		for(int i=(int)a.size()-1;i>=0;i--)if(s[r-i]!=a[i])return s[r-i]>a[i];
		return true;
	}
	void Sub(const vector<int>&a)
	{
		for(int i=(int)a.size()-1;i>=0;i--)s[r-i]-=a[i];
		for(int i=r;i>=l;i--)if(s[i]<0)
		{
			assert(i>l);
			s[i-1]--,s[i]+=10,assert(s[i]>=0);
		}
		while(front()==0)pop_front();
	}
}DEQ;
int Pop(){int ans=BUFFER.front();BUFFER.pop();return ans;}
void ExpandBUFFER(){BUFFER.push(0),BUFFER.push(0);}
void Extract(){DEQ.push_back(Pop()),DEQ.push_back(Pop());ExpandBUFFER();}
void BuildBUFFER()
{
	vector<int>tmp;
	while(N)tmp.push_back(N%10),N/=10;
	while(!BUFFER.empty())BUFFER.pop();
	for(int i=tmp.size()-1;i>=0;i--)BUFFER.push(tmp[i]);
	ExpandBUFFER();
}
vector<int>ADD;
vector<int>Plus(const vector<int>&a,const int b)
{
	vector<int>ans=a;
	if(ans.empty())ans.push_back(b);
	else ans[0]+=b;
	for(int i=0;i<ans.size();i++)if(ans[i]>=10)
	{
		if(i+1==ans.size())ans.push_back(0);
		ans[i+1]+=ans[i]/10,ans[i]%=10;
	}
	return ans;
}
vector<int>Mul(const vector<int>&a,const int b)
{
	vector<int>ans;
	for(int i=0;i<a.size();i++)ans.push_back(a[i]*b);
	for(int i=0;i<ans.size();i++)if(ans[i]>=10)
	{
		if(i+1==ans.size())ans.push_back(0);
		ans[i+1]+=ans[i]/10,ans[i]%=10;
	}
	return ans;
}
bool FindAns(const vector<int>&seq)
{
	if(seq.size()<3)return false;
	const int r=seq.size()-1;
	return seq[r]==seq[r-1]&&seq[r]==seq[r-2];
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		if(!N)continue;
		printf("%d ",N);
		BuildBUFFER();
		vector<int>ans;
		DEQ.clear();
		ADD.clear();
		for(;;)
		{
			Extract();
			ADD=Mul(ADD,10);
			int d=0;
			while(DEQ.Subtractable(Mul(Plus(ADD,d+1),d+1)))d++;
			assert(d>=0&&d<=9);
			DEQ.Sub(Mul(Plus(ADD,d),d));
			ADD=Plus(ADD,d*2);
			ans.push_back(d);
			if(FindAns(ans))
			{
				printf("%d %d\n",ans.size()-3,ans[ans.size()-1]);
				break;
			}
		}
	}
	return 0;
}

#include<cstdio>
#include<cassert>
using namespace std;
struct Node
{
	Node *green,*edge[26];
	int max_len;
	Node(const int _max_len):green(NULL),max_len(_max_len){for(int i=0;i<26;i++)edge[i]=NULL;}
}*ROOT,*LAST;
void Extend(const int c)
{
	Node *cursor=LAST;LAST=new Node((LAST->max_len)+1);
	for(;cursor&&!cursor->edge[c];cursor=cursor->green)cursor->edge[c]=LAST;//�K�[LAST���Ҧ��¦�r�� 
	if(!cursor)LAST->green=ROOT;//���ϤW�S���e����䪺�I�A�N��ۥ��������O�������V�N��Ŧꪺ�ڵ��I�� 
	else
	{
		Node *potential_green=cursor->edge[c];//��X�̪������r��(���F�n��LAST�N��Ҧ����A�n�M�w�����s���)�A�b�ϤW�|������Ӹ`�I 
		if((potential_green->max_len)==(cursor->max_len+1))LAST->green=potential_green;//���npotential_green�N���r��������OLAST�����A�i�H�����NLAST�����r��K�[���� 
		else
		{
			assert((potential_green->max_len)>(cursor->max_len+1));//potential_green���Ǧr�ꤣ�OLAST�����
			Node *seperated_node=new Node((cursor->max_len)+1);//�qpotential_green�����X�Q�n���`�I�A��n�N��LAST���Ҧ����r�� 
			for(;cursor&&cursor->edge[c]==potential_green;cursor=cursor->green)cursor->edge[c]=seperated_node;//�K�[seperated_node���Ҧ��¦�r��A�P�ɥi�෴������potential_green���N��r�궰�X 
			for(int i=0;i<26;i++)seperated_node->edge[i]=potential_green->edge[i];//��seperated_node���ޭ쥻potential_green�¦��䪺�\�� 
			seperated_node->green=potential_green->green;//�K�[seperated_node���Ҧ����r�� 
			potential_green->green=seperated_node;//�Q�κ����״_potential_green���N��r�궰�X 
			LAST->green=seperated_node;//�K�[LAST���Ҧ����r�� 
		}
	}
}
char S[10000001],A[10000001];
int N;
int main()
{
	scanf("%d%s",&N,S);
	ROOT=LAST=new Node(0);//SAM���ڵ��I�N��Ŧ�Amax_len��M�O0 
	for(int i=0;S[i];i++)Extend(S[i]-'a');
	while(N--)
	{
		scanf("%s",A);
		Node *cursor=ROOT;
		bool ans=true;
		for(int i=0;A[i];i++)
		{
			cursor=cursor->edge[A[i]-'a'];
			if(!cursor){ans=false;break;}//�ϤW�S�����i�H���F�A�DS���l�r�� 
		}
		puts(ans?"Yes":"No");
	}
	return 0;
}

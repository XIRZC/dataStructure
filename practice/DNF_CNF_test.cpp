//������ |  , ������ &   ,������ ->  ,˫���� <=> ,������ !
 
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>
#include <sstream>
using namespace std;
string zhong;  //��׺���ʽ
char hou[1000];   //��׺���ʽ
string alpha;   //���������ĸ����
map<char,int> M;   //ӳ�䣬����ĸ������0��1һһ��Ӧ
 
struct note
{
	int a[100];
};
vector<note> zhen;  //���������飬�������ȡ��ʽ��Ӧ��ĸ������01�����Ҳ���Ǳ��ʽ��ֵΪT
vector<note> jia;  //���������飬�������ȡ��ʽ��Ӧ��ĸ������01�����Ҳ���Ǳ��ʽ��ֵ��F
 
void ddd()   //Ԥ����ȥ����׺���ʽ������->�е�>,��˫����<=>�е�= and > ,�����������������һ���ַ�����������
{
	string::iterator i=zhong.begin();
	int flag=1;
	while(flag)
    {
        flag=0;
        for(i=zhong.begin();i!=zhong.end();++i)
        {
            if(*i=='>')
            {
                zhong.erase(i);
                flag=1;
                break;
            }
            if(*i=='=')
            {
                zhong.erase(i);
                flag=1;
                break;
            }
        }
	}
}
 
int icp(char a)
{
	if(a=='#') return 0;
	if(a=='(') return 12;
	if(a=='!') return 10;
	if(a=='&') return 8;
	if(a=='|') return 6;
	if(a=='-') return 4;
	if(a=='<') return 2;
	if(a==')') return 1;
}
int isp(char a)
{
	if(a=='#') return 0;
	if(a=='(') return 1;
	if(a=='!') return 11;
	if(a=='&') return 9;
	if(a=='|') return 7;
	if(a=='-') return 5;
	if(a=='<') return 3;
	if(a==')') return 12;
}
 
 
void change()    //��׺���ʽת����׺���ʽ
{
	int j=0;
	stack<char> s;
	char ch,y;
	s.push('#');
	char t1,t2;
	stringstream ss(zhong);
	while(ss>>ch,ch!='#')
	{
		if(isalpha(ch))
		{
			hou[j++]=ch;
			if(alpha.find(ch)==-1)
			{
				alpha.push_back(ch);
			}
		}
		else if(ch==')')
		{
			for(y=s.top(),s.pop();y!='(';y=s.top(),s.pop())
			{
				hou[j++]=y;
			}
		}
		else
		{
			for(y=s.top(),s.pop();icp(ch)<=isp(y);y=s.top(),s.pop())
			{
				hou[j++]=y;
			}
			s.push(y);
			s.push(ch);
		}
	}
	while(!s.empty())
	{
		y=s.top();
		s.pop();
		if(y!='#')
		{
			hou[j++]=y;
		}
	}
	hou[j]='#';
}
 
 
int cal()   //�Ը�ֵ��ĺ�׺���ʽ���м���
{
	stack<int> s;
	char ch;
	int j=0;
	int t1,t2;
	while(1)
	{
		ch=hou[j];
		if(ch=='#') break;
		if(ch==0) break;
		j++;
		if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
		{
			s.push(M[ch]);
		}
		else
		{
			if(ch=='!')
			{
				t1=s.top();
				s.pop();
				s.push(!t1);
			}
			else if(ch=='&')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==1&&t2==1)
				{
					s.push(1);
				}
				else
				{
					s.push(0);
				}
			}
			else if(ch=='|')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==0&&t2==0)
				{
					s.push(0);
				}
				else
				{
					s.push(1);
				}
			}
			else if(ch=='-')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if(t1==0&&t2==1)
				{
					s.push(0);
				}
				else
				{
					s.push(1);
				}
			}
			else if(ch=='<')
			{
				t1=s.top();
				s.pop();
				t2=s.top();
				s.pop();
				if((t1==1&&t2==1)||(t1==0&&t2==0))
				{
					s.push(1);
				}
				else
				{
					s.push(0);
				}
			}
		}
	}
	int ans=s.top();
	return ans;
}
 
 
 
 
 
 
 
 
 
void dfs(int cur)   //�ݹ�ö��ÿһ���ַ�������ȡֵ���
{
	if(cur==alpha.size())
	{
		int ans=cal();
		for(int i=0;i<alpha.size();i++)
		{
			if(M[alpha[i]])
			{
				printf("T\t");
			}
			else
			{
				printf("F\t");
			}
		}
		if(ans==1)   //��ֵΪT ���뵽zhen���飬�Դ���������ȡ��ʽʹ��
		{
			printf("T\n");
			note t;
			for(int i=0;i<alpha.size();i++)
			{
				t.a[i]=M[alpha[i]];
			}
			zhen.push_back(t);
		}
		else   //��ֵΪF  ���뵽jia���飬�Դ���������ȡ��ʽʹ��
		{
			printf("F\n");
			note t;
			for(int i=0;i<alpha.size();i++)
			{
				t.a[i]=M[alpha[i]];
			}
			jia.push_back(t);
		}
		return ;
	}
	M[alpha[cur]]=1;
	dfs(cur+1);
	M[alpha[cur]]=0;
	dfs(cur+1);
}
 
 
 
 
 
int main()
{
	while(true)
	{
		int i;
		M.clear();
		alpha.clear();
		zhen.clear();
		jia.clear();
		printf("������Ϊ |  , ������Ϊ &   ,������Ϊ ->  ,˫������ <=> ,������Ϊ !\n");
		printf("��������ʽ,�س�����\n");
	 	cin>>zhong;
	 	zhong.append("#");
	 	ddd();
	 	change();
	 	for(i=0;i<alpha.size();i++)
	 	{
	 		printf("%c\t",alpha[i]);
	 	}
	 	printf("���ʽ��ֵ\n");
	 	dfs(0);
	 	printf("����ȡ��ʽΪ\n");
		int lena=zhen.size();
		for(i=0;i<lena;i++)
		{
			if(i!=0) printf("��");
			int *p=zhen[i].a;
			printf("(");
			for(int j=0;j<alpha.size();j++)
			{
				if(j!=0) printf("��");
				if(p[j]==1)
				{
					printf("%c",alpha[j]);
				}
				else
				{
					printf("�V%c",alpha[j]);
				}
			}
			printf(")");
		}
		printf("\n");
		printf("����ȡ��ʽΪ\n");
		for(i=0;i<jia.size();i++)
		{
			if(i!=0) printf("��");
			int *p=jia[i].a;
			printf("(");
			for(int j=0;j<alpha.size();j++)
			{
				if(j!=0) printf("��");
				if(p[j]==0)
				{
					printf("%c",alpha[j]);
				}
				else
				{
					printf("�V%c",alpha[j]);
				}
			}
			printf(")");
		}
		printf("\n\n");
	 }
	return 0;
}
 
 

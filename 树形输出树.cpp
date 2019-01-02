#include<stdio.h>
#include<stdlib.h>

#define Maxlength 50
#define Maxtree 50

typedef char ElemType;

typedef struct tnode
{
	ElemType data;
	struct tnode *hp;//ָ��ͬ�н�� 
	struct tnode *vp;//ָ���ӽ�� 
}TSBNode;

void start(void);
void CreatTree(TSBNode *&a,ElemType str[],int &strnum);
void GetTree(TSBNode *a,ElemType str[Maxtree][2*Maxtree],int length);
char MaxLength(ElemType str[Maxtree][2*Maxtree],int length);
void display(ElemType str[Maxtree][2*Maxtree]);
void DestoryTree(TSBNode *&a);

int main()
{
	start();
	return 0;
}

//��ʼ���򣬽���һ�������ظ����е�ѭ�� 
void start(void)
{
	int choice=0;
	do{
		//���� 
		system("cls");
		//����һ��ָ������ָ�� 
		TSBNode *a=NULL;
		//����û�������ַ��� 
		ElemType str[Maxlength];
		puts("�����봴�������õ��ַ���!");
		scanf("%s",str);
		//�������Ĵ��� 
		int strnum=0;
		CreatTree(a,str,strnum);
		//������Ľṹ����ӡ�����������ṹ 
		ElemType str1[Maxtree][2*Maxtree]={'\0'}; 
		GetTree(a,str1,0);
		display(str1);
		
		//��ʾ����������ʾ����� 
		puts("\n\n\n\n\n\n\n\n\n-------------------------------------------------");
		puts("����һ��  1\t��������  others");
		scanf("%d",&choice);
		DestoryTree(a); 
	}while(choice==1);
	
} 


//�Ժ����ֵ����ķ�ʽ����һ���� 
void CreatTree(TSBNode *&a,ElemType str[],int &strnum)
{
	//strnum����ǰ��ȡ���ַ���λ�� 
	//����β�巨 
	TSBNode *p=a,*tail=a;
	//��ȡ�ַ��� 
	char ch;
	ch=str[strnum++];
	while(ch!='\0')
	{
		if(ch==')')
			break;
			//ֱ�ӷ��� 
		else if(ch=='(')
			CreatTree(p->vp,str,strnum);
		//���еݹ���� 
		else if(ch==',');//ʲôҲ���� 
		else
		{
			//����һ���µĽ�㣬β�巨 
			p=(TSBNode *)malloc(sizeof(TSBNode));
			p->hp=p->vp=NULL;
			p->data=ch;
			if(tail==NULL)
				a=p;
			else
				tail->hp=p;
			tail=p;		
		}
		ch=str[strnum++];		 
	}
}


//������������Ȼ���������Ľṹ�洢��һ��������
//����ĵ�һ�е������֣������洢���������һ�߶ȵ����ұߵ�λ�� 
void GetTree(TSBNode *a,ElemType str[Maxtree][2*Maxtree],int length)
{
	//str�����������	length����ǰ���ĸ߶� 
	TSBNode *p=a;
	int flag=0;//����ָʾǰһ������Ƿ���ں��ӽ��
	//������ú����ĵ�һ�����
	str[length][0]++;
	str[length][str[length][0]]='{';
	str[length][0]++;
	str[length][str[length][0]]=p->data;
	//�ж����Ƿ���ں��ӽ�㣬���������ݹ���� 
	if(p->vp!=NULL)
		{
			str[length+1][0]=str[length][0]-2;	
			//���������㷨�ص㣬����ƶ���λ���ô洢{�ͽ�����ݣ�ʹ�����¶��� 
			GetTree(p->vp,str,length+1);
			//�����к��ӽ�� 
			flag=1;
		}
		
	p=p->hp;
	//�ж��Ƿ����ֵܽ�� 
	while(p!=NULL)
	{
		if(flag==1)
		{
			if(p->vp!=NULL)
			{
				//ǰһ���ֵܽ����ں��ӽ�㲢�ұ��ڵ���ں��ӽ��
	//�ҵ��˽ڵ����������ֵ��֮�󽫱��ڵ����ƫ�ƣ�ƫ��֮��ʹ���ӽ���{�ͽ��ֵ���Լ����� 
				str[length][0]=MaxLength(str,length+1)+2;
				str[length][str[length][0]]=p->data;
				str[length+1][0]=str[length][0]-2;
				GetTree(p->vp,str,length+1);
				//�ؼ����� 
				flag=1;
			}
			else
			{
				//ǰһ���ֵܽ����ں��ӽ�㲢�ұ��ڵ���ں��ӽ��
				//���ֲ���Ҫ���Ǻ��ӽ���{�����������ֻ��ƫ��1����λ���� 
				str[length][0]=MaxLength(str,length+1)+1;
				str[length][str[length][0]]=p->data;
				//�ؼ����� 
				flag=0;
			}
		}
		else
		{
			if(p->vp!=NULL)
			{
				//ǰһ���ֵܽ�㲻���ں��ӽ�㲢�ұ��ڵ���ں��ӽ��
		//��������޷�ͨ��������������ֵ����ƫ�ƣ���ֱ�ӿ����ڱ��н���ƫ�� ��ƫ��Ϊ2������{ 
				str[length][0]+=2;
				str[length][str[length][0]]=p->data;
				str[length+1][0]=str[length][0]-2;
				GetTree(p->vp,str,length+1);
				//�ؼ����� 
				flag=1;
			}
			else
			{
				//ǰһ���ֵܽ�㲻���ں��ӽ�㲢�ұ��ڵ㲻���ں��ӽ��
		//��������޷�ͨ��������������ֵ����ƫ�ƣ���ֱ�ӿ����ڱ��н���ƫ�� ��ƫ��Ϊ1
				str[length][0]+=1;
				str[length][str[length][0]]=p->data;
				//�ؼ����� 
				flag=0;
			}
		}
		
		p=p->hp;
	} 
	//���÷��ص�������� 
	str[length][0]++;
	str[length][str[length][0]]='}';
}

//�õ���������һ����֮��Ĳ����������һ��ĳ��� 
ElemType MaxLength(ElemType str[Maxtree][2*Maxtree],int length)
{
	ElemType ret=str[length][0];
	while(str[length][0] != '\0')
	{
		if(str[length][0]>ret)
			ret=str[length][0];
		length++;
	}
	return ret;
}

//���õ��������ӡ���������Ե�һ�� 
void display(ElemType str[Maxtree][2*Maxtree])
{
	for(int i=0;str[i][0]!='\0';i++)
	{
		for(int j=1;j<=str[i][0];j++)
		{
			printf("%-2c",str[i][j]);
		}
		printf("\n");
	}
}


void DestoryTree(TSBNode *&a)
{
	TSBNode *p=a;
	//�ж�����ȥ������� 
	if(p->vp!=NULL)
		DestoryTree(p->vp);
	//����û�ˣ����ֵ� 
	if(p->hp!=NULL)
		DestoryTree(p->hp);
	//���� 
	free(p);
} 

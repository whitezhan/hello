// snake.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"

#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
int GameOver=0;

struct Body//��������ṹ��
{
	int x,y;//����������
	Body *next;//��һ�����
};

void SetPos(int i,int j)//�趨���λ��
{
	COORD pos={i-1,j-1};//�������
	HANDLE Out=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ������
	SetConsoleCursorPosition(Out,pos);//�趨���λ��
}

class Sneak//̰������
{
private:
	Body *head;//��ͷָ��
	int Direction;//�ƶ�����1,2,3,4��Ӧ��������
	int Count;//�߳�
	int Speed;//�ٶȣ��ȼ���
	int FoodExist;//ʳ����ڱ��
	int Food_x;//ʳ��X����
	int Food_y;//ʳ��Y����
public:
	Sneak(int a=3,int b=4,int c=1,int d=0)//���캯��
	{ 
		FoodExist=d;//��ʼ������ʳ��
		Body *temp1,*temp2;
		head=new(Body);//������ʼ����3��
		head->x=4;
		head->y=2;

		temp1=new(Body);
		temp1->x=3;
		temp1->y=2;

		temp2=new(Body);
		temp2->x=2;
		temp2->y=2;

		head->next=temp1;
		temp1->next=temp2;
		temp2->next=NULL;

		Direction=b;//����Ϊ��
		Count=a;//��Ϊ3
		Speed=c;//�ȼ�1
	}
	void Map();//�����溯��
	void Paint();//��������
	void Food();//����ʳ��
	int Over();//�ж���Ϸ�Ƿ����
	void Gaming();//��Ϸ���̺���
	void Move();//�ƶ�
};

void Sneak::Map()//ʹ��
{
	int i;
	for(i=1;i<=50;i++)
	{
		SetPos(i,1);
		cout<<"-";
	}
	for(i=2;i<=25;i++)
	{
		SetPos(1,i);
		cout<<"|";
		SetPos(50,i);
		cout<<"|";
	}
	for(i=1;i<=50;i++)
	{
		SetPos(i,25);
		cout<<"-";
	}
	SetPos(54,3);
	cout<<"̰����";
	SetPos(54,5);
	cout<<"����:"<<Count;
	SetPos(54,7);
	cout<<"LEVEL:"<<Speed;
}

void Sneak::Food()
{
	Body *p;
	int InBody=0;	//�ж�ʳ���Ƿ������������
	srand((int)time(0));//��ϵͳʱ���������������
	while(1)
	{
		Food_x=rand()%48+2;//�����ʳ�������
		Food_y=rand()%23+2;
		p=head;
		while(p!=NULL)//�ж�ʳ���Ƿ������������
		{
			if(p->x==Food_x&&p->y==Food_y)
			{
				InBody=1;
				break;
			}
			p=p->next;
		}
		if(InBody==0)//ʳ�ﲻ���������ɳɹ�
			break;
		InBody=0;
	}
}

int Sneak::Over()
{
	Body *p;
	p=head;
	if((head->x)>=50||(head->x)<=1||(head->y)<=1||(head->y)>=25)//�Ƿ�ײ����Ե
		return 1;
	p=head->next;
	while(p!=NULL)//�Ƿ�ײ������
	{
		if((head->x==p->x)&&(head->y==p->y))
			return 1;
		p=p->next;
	}
	return 0;
}

void Sneak::Paint()
{
	Body *p;
	p=head;
	while(p!=NULL)
	{
		SetPos(p->x,p->y);
		cout<<"*";
		p=p->next;
	}
	SetPos(Food_x,Food_y);
	cout<<"*";
}

void Sneak::Move()
{
	Body *New;
	New=new(Body);//�µ�������
	if(Direction==1)//ȷ������ͷ������	
	{
		New->x=head->x;
		New->y=head->y-1;
		New->next=head;
		head=New;
	}
	if(Direction==2)
	{
		New->x=head->x-1;
		New->y=head->y;
		New->next=head;
		head=New;
	}
	if(Direction==3)
	{
		New->x=head->x;
		New->y=head->y+1;
		New->next=head;
		head=New;
	}
	if(Direction==4)
	{
		New->x=head->x+1;
		New->y=head->y;
		New->next=head;
		head=New;
	}
}

void Sneak::Gaming()
{
	system("cls");//ˢ����Ļ
	char x;
	Body *p;
	Map();//���������
	Paint();//�ٻ�����
	while(1)
	{
		if(_kbhit())//_kbhit()�ж��Ƿ��м��̲���
		{
			x=_getch();//�ػ���������һ���ַ�����x
			if((x=='W'||x=='w')&&Direction!=3)//�ı��ߵķ��򣨲������Ƿ�����
				Direction=1;
			if((x=='S'||x=='s')&&Direction!=1)
				Direction=3;
			if((x=='A'||x=='a')&&Direction!=4)
				Direction=2;
			if((x=='D'||x=='d')&&Direction!=2)
				Direction=4;
			while(_kbhit())//������֮�����еļ�������
				_getch();
		}
		if(FoodExist==0)//���ʳ�ﱻ���˻�տ�ʼ��Ϸ��Ҫ�����µ�ʳ��
		{
			Food();
			FoodExist=1;
		}
		Move();//�ƶ���
		if(head->x==Food_x&&head->y==Food_y)//����߳Ե���ʳ��
		{
			FoodExist=0;
			Count++;//����+1
			SetPos(54,5);
			cout<<"����:"<<Count;//�ı������Ϣ
			if(Count%10==0)//ÿʮ��������һ��
			{
				Speed++;
				SetPos(54,7);
				cout<<"LEVEL:"<<Speed;
			}
			if(Speed==10)//��ߵȼ���ɡ��˳���Ϸ
				break;
		}
		Paint();//���µ�����
		if(FoodExist==1)//���û�гԵ�ʳ���Ҫɾ����β��
		{
			p=head;
			while((p->next)->next!=NULL)
				p=p->next;
			SetPos(p->next->x,p->next->y);
			cout<<" ";
			delete(p->next);
			p->next=NULL;
		}
		if(Over())//�ж��Ƿ���Ϸ����
			break;
		Sleep(500-Speed*50);//�ȴ�������ʱ��͵ȼ��й�
	}
	system("cls");
	if(Speed==10)//ͨ��
	{
		SetPos(25,25);
		cout<<"�ﱤ-_-||��ͨ����"<<endl;
		system("pause");
	}
	else//ʧ��
	{
		SetPos(25,10);
		cout<<"-0- ~~����ˣ����ճ���Ϊ "<<Count<<endl;
		system("pause");
	}
}
int main()
{
	Sneak game;
	system("cls");
	cout<<"*****************************************************"<<endl;
	cout<<"*                        ̰����                     *"<<endl;
	cout<<"*****************************************************"<<endl;
	cout<<"*                ˵��                               *"<<endl;
	cout<<"*            W,A,S,D�����ƶ�                        *"<<endl;
	cout<<"*       ÿ10��������һ����������ٶȣ�10��ͨ��      *"<<endl;
	cout<<"*****************************************************"<<endl;
	cout<<"*      ��ĳ���������ٶ�ID��HapHapYear               *"<<endl;
	cout<<"*********         �������ʼ   **********************"<<endl;
	_getch();
	game.Gaming();
	return 0;
}
#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#define TMX 1000
FILE *fp;
char count[11],dco[11];
char ch[TMX][TMX],tm[11]="0";
void nread() //��ȡ��ǰ�����ļ���
{
	fp=fopen("num.memo","r");
	fgets(count,11,fp);
	fclose(fp);
}
void dread()//��ȡɾ������ 
{
	fp=fopen("den.memo","r");
	fgets(dco,11,fp);
	fclose(fp); 
}
void creat()//�½���Ϣ
{ 
	char ren[100]="ren m.txt m",end[6]=".memo",fln[20]="m",move[20]="move ",end2[10]=" message";
	int t,i=0,num=0,dn=0,s=0;
	char k;
	while(count[i])  //ת���ļ���������num 
	{
		num*=10;
		num+=count[i++]-48;//'0' 
	}
	i=0;
	while(dco[i]) //ת��ɾ����������dn 
	{
		dn*=10;
		dn+=dco[i++]-48;
	}
	s=dn+num;
	fp=fopen("m.txt","w");
	fclose(fp);
	system("date /t >>m.txt"); //������� 
	system("time /t >>m.txt"); //���ʱ��
	printf("----------------\n\n");
	printf("��ǰʱ��\n");
	system("date /t");
	system("time /t");
	printf("��������Ϣ(��������ed����)\n");
	printf("\n----------------\n");
	fp=fopen("m.txt","a");
	for(i=0;;i++)
	{
		gets(ch[i]);
		if(ch[i][0]=='e'&&ch[i][1]=='d'&&ch[i][2]=='\0') break;
		fputs(ch[i],fp);
		fputs("\n",fp);
		
	}
	fclose(fp);
	for(i=0;s!=0;i++)  //��ֹ������ͻ
	{
		count[i]=s%10+'0';
		s/=10;
	}
	for(i=0;i<=strlen(count)/2;i++)
	k=count[i],count[i]=count[strlen(count)-1],count[strlen(count)-1]=k;
	strcat(ren,count); //�����ļ����Լ�¼ 
	strcat(ren,end);
	system(ren);
	strcat(fln,count); //�ƶ��ļ���message�ļ���
	strcat(fln,end);
	strcat(move,fln);
	strcat(move,end2);
	system(move);
	num++;
	for(i=0;num!=0;i++)  //��д�����ļ��� 
	{
		count[i]=num%10+'0';
		num/=10;
	}
	for(i=0;i<=strlen(count)/2;i++)
	k=count[i],count[i]=count[strlen(count)-1],count[strlen(count)-1]=k;
	fp=fopen("num.memo","w");
	fputs(count,fp);
	fclose(fp);
	system("cls");
	printf("\n����ɹ�!\n");
	printf("----------------\n");
	printf("0:�������˵�\n\n1:�����½���Ϣ\n");
	printf("----------------\n:");
	scanf("%d",&t);
	if(t==1){system("cls");creat();}
}
int read() //�鿴��Ϣ 
{
	int del(int b,char c[]);
	nread();dread();
	int t;
	char re[40]="type .\\message\\m",fln[20],end[6]=".memo";
	printf("----------------\n");
	system("dir message /b/od");
	printf("----------------\n");
	printf("���������Բ鿴��Ϣ(0~n)");
	printf("\n----------------\n:");
	scanf("%s",fln);
	strcat(re,fln);
	strcat(re,end); //ƴ����� 
	system("cls");
	printf("\n----------------\n\n");
	system(re);
	printf("\n----------------\n");
	printf("0:�������˵�\n\n1:�����鿴��Ϣ\n\n2:ɾ������Ϣ\n");
	printf("----------------\n:");
	scanf("%d",&t);
	if(t==1) {system("cls");read();}
	if(t==2) {system("cls");del(1,fln);}
	return 0;
}
void dela()//ɾ��ȫ�� 
{
	system("del .\\message\\*.memo*");
	printf("----------------\n");
	printf("��ȫ��ɾ��\n");
	fp=fopen("num.memo","w");
	fputs("0",fp);
	fclose(fp);
	fp=fopen("den.memo","w");
	fputs("0",fp);
	fclose(fp);
	printf("(���س����������˵�)");
	getchar();getchar();
}
int del(int b,char c[]) //ɾ������ 
{
	nread();dread();
	char dele[30]="del .\\message\\m" ,end[10]=".memo",n[11],k;
	char re[30]=".\\message\\m";
	int dn=0,num=0,i=0,t;
	if(b==0)
	{
	printf("----------------\n");
	system("dir message /b/od"); 
	printf("----------------\n");
	printf("(������Ҫɾ����Ϣ�����)\n");
	printf("----------------\n:");
	scanf("%s",n);
	}
	strcat(re,n);
	strcat(re,end);
	if((fp=fopen(re,"rt"))==NULL)  //�ж��Ƿ���ڸ��ļ� 
	{
		fclose(fp);
		system("cls");
		printf("----------------\n");
		printf("���ļ�������!\n");
		printf("----------------\n");
		printf("0:�������˵�\n\n1:����ɾ����Ϣ\n");
		printf("----------------\n:");
		scanf("%d",&t);
		if(t==1) {system("cls");del(0,tm);}
		return 0;
	}
	fclose(fp);
	i=0;
	while(count[i])  //ת���ļ���������num 
	{
		num*=10;
		num+=count[i++]-48;
	}
	i=0;
	while(dco[i]) //ת��ɾ����������dn 
	{
		dn*=10;
		dn+=dco[i++]-48;
	}
	dn++;
	num--;
	system("cls");
	if(num==0){dela();return 0;}
	if(b) strcat(dele,c);
	else strcat(dele,n);
	strcat(dele,end);
	system(dele);
	for(i=0;dn>0;i++)  //��дɾ���� 
	{
		dco[i]=dn%10+'0';
		dn/=10;
	}
	for(i=0;num>0;i++)  //��д�����ļ��� 
	{
		count[i]=num%10+'0';
		num/=10;
	}
	printf("----------------\n");
	printf("�ѳɹ�ɾ��\n");
	for(i=0;i<=strlen(count)/2;i++)
	k=count[i],count[i]=count[strlen(count)-1],count[strlen(count)-1]=k;
	for(i=0;i<=strlen(dco)/2;i++)
	k=dco[i],dco[i]=dco[strlen(dco)-1],dco[strlen(dco)-1]=k; 
	fp=fopen("den.memo","w");
	fputs(dco,fp);
	fclose(fp);
	fp=fopen("num.memo","w");
	fputs(count,fp);
	fclose(fp);
	printf("----------------\n");
	printf("0:�������˵�\n\n1:����ɾ����Ϣ\n");
	printf("----------------\n:");
	scanf("%d",&t);
	if(t==1) {system("cls");del(0,tm);}
	return 0;
}
void rall() //�鿴ȫ�� 
{
	system("type .\\message\\*.txt");
	printf("----------------\n");
	printf("\n(���س����������˵�)");
	getchar();getchar();
	system("cls");
 } 
int main() //���˵� 
{
	while(1)
	{	system("cls");
		int t;
		nread();dread();
		printf("----------------\n\n");
		printf("[��ǰMemo����%s����Ϣ]\n\n",count);
		printf("[������������]\n\n");
		printf("0:�½���Ϣ\n\n");
		printf("1:�鿴������Ϣ\n\n");
		printf("2:�鿴������Ϣ\n\n");
		printf("3:ɾ��������Ϣ\n\n");
		printf("4:ɾ��������Ϣ\n\n");
		printf("5:�˳�����\n");
		printf("\n----------------\n:");
		scanf("%d",&t);
		switch(t) 
		{
			case 0:system("cls");creat();break;
			case 1:system("cls");read();break; 
			case 2:system("cls");rall();break;
			case 3:system("cls");del(0,tm);break;
			case 4:system("cls");dela();break;
			case 5:{system("cls");
			printf("��лʹ�����ɵ�Memo!");
			Sleep(500);
			return 0;}
		}
	}
}

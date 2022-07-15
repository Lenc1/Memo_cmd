#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#define TMX 1000
FILE *fp;
char count[11],dco[11];
char ch[TMX][TMX],tm[11]="0";
void nread() //读取当前备忘文件数
{
	fp=fopen("num.memo","r");
	fgets(count,11,fp);
	fclose(fp);
}
void dread()//读取删除次数 
{
	fp=fopen("den.memo","r");
	fgets(dco,11,fp);
	fclose(fp); 
}
void creat()//新建信息
{ 
	char ren[100]="ren m.txt m",end[6]=".memo",fln[20]="m",move[20]="move ",end2[10]=" message";
	int t,i=0,num=0,dn=0,s=0;
	char k;
	while(count[i])  //转存文件数到数字num 
	{
		num*=10;
		num+=count[i++]-48;//'0' 
	}
	i=0;
	while(dco[i]) //转存删除数到数字dn 
	{
		dn*=10;
		dn+=dco[i++]-48;
	}
	s=dn+num;
	fp=fopen("m.txt","w");
	fclose(fp);
	system("date /t >>m.txt"); //添加日期 
	system("time /t >>m.txt"); //添加时间
	printf("----------------\n\n");
	printf("当前时间\n");
	system("date /t");
	system("time /t");
	printf("请输入信息(空行输入ed结束)\n");
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
	for(i=0;s!=0;i++)  //防止命名冲突
	{
		count[i]=s%10+'0';
		s/=10;
	}
	for(i=0;i<=strlen(count)/2;i++)
	k=count[i],count[i]=count[strlen(count)-1],count[strlen(count)-1]=k;
	strcat(ren,count); //更改文件名以记录 
	strcat(ren,end);
	system(ren);
	strcat(fln,count); //移动文件到message文件夹
	strcat(fln,end);
	strcat(move,fln);
	strcat(move,end2);
	system(move);
	num++;
	for(i=0;num!=0;i++)  //重写存在文件数 
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
	printf("\n保存成功!\n");
	printf("----------------\n");
	printf("0:返回主菜单\n\n1:继续新建信息\n");
	printf("----------------\n:");
	scanf("%d",&t);
	if(t==1){system("cls");creat();}
}
int read() //查看信息 
{
	int del(int b,char c[]);
	nread();dread();
	int t;
	char re[40]="type .\\message\\m",fln[20],end[6]=".memo";
	printf("----------------\n");
	system("dir message /b/od");
	printf("----------------\n");
	printf("输入数字以查看信息(0~n)");
	printf("\n----------------\n:");
	scanf("%s",fln);
	strcat(re,fln);
	strcat(re,end); //拼接命令串 
	system("cls");
	printf("\n----------------\n\n");
	system(re);
	printf("\n----------------\n");
	printf("0:返回主菜单\n\n1:继续查看信息\n\n2:删除此消息\n");
	printf("----------------\n:");
	scanf("%d",&t);
	if(t==1) {system("cls");read();}
	if(t==2) {system("cls");del(1,fln);}
	return 0;
}
void dela()//删除全部 
{
	system("del .\\message\\*.memo*");
	printf("----------------\n");
	printf("已全部删除\n");
	fp=fopen("num.memo","w");
	fputs("0",fp);
	fclose(fp);
	fp=fopen("den.memo","w");
	fputs("0",fp);
	fclose(fp);
	printf("(按回车键返回主菜单)");
	getchar();getchar();
}
int del(int b,char c[]) //删除单条 
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
	printf("(请输入要删除信息的序号)\n");
	printf("----------------\n:");
	scanf("%s",n);
	}
	strcat(re,n);
	strcat(re,end);
	if((fp=fopen(re,"rt"))==NULL)  //判断是否存在该文件 
	{
		fclose(fp);
		system("cls");
		printf("----------------\n");
		printf("该文件不存在!\n");
		printf("----------------\n");
		printf("0:返回主菜单\n\n1:继续删除信息\n");
		printf("----------------\n:");
		scanf("%d",&t);
		if(t==1) {system("cls");del(0,tm);}
		return 0;
	}
	fclose(fp);
	i=0;
	while(count[i])  //转存文件数到数字num 
	{
		num*=10;
		num+=count[i++]-48;
	}
	i=0;
	while(dco[i]) //转存删除数到数字dn 
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
	for(i=0;dn>0;i++)  //重写删除数 
	{
		dco[i]=dn%10+'0';
		dn/=10;
	}
	for(i=0;num>0;i++)  //重写存在文件数 
	{
		count[i]=num%10+'0';
		num/=10;
	}
	printf("----------------\n");
	printf("已成功删除\n");
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
	printf("0:返回主菜单\n\n1:继续删除信息\n");
	printf("----------------\n:");
	scanf("%d",&t);
	if(t==1) {system("cls");del(0,tm);}
	return 0;
}
void rall() //查看全部 
{
	system("type .\\message\\*.txt");
	printf("----------------\n");
	printf("\n(按回车键返回主菜单)");
	getchar();getchar();
	system("cls");
 } 
int main() //主菜单 
{
	while(1)
	{	system("cls");
		int t;
		nread();dread();
		printf("----------------\n\n");
		printf("[当前Memo中有%s条信息]\n\n",count);
		printf("[请输入操作序号]\n\n");
		printf("0:新建信息\n\n");
		printf("1:查看单条信息\n\n");
		printf("2:查看所有信息\n\n");
		printf("3:删除单条信息\n\n");
		printf("4:删除所有信息\n\n");
		printf("5:退出程序\n");
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
			printf("感谢使用珞晟的Memo!");
			Sleep(500);
			return 0;}
		}
	}
}

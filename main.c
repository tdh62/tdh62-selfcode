//头文件及一些声明
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "conio.h"
//函数声明
int clear();
int welcome(int wtype);
void outputline();
int checkstate();
int getchoose();
void mainpage();
int newstudent();
int newsocks();
int getsocks(int a);
int order();
void out(int a);
int checkchange();
int changest(int a);
int socksadd1(int a);
int socksadd1c();
int socksadd2();
int socksadd2c();
int tofile();
int fromfile();
int savesetting();
int readsetting();
//变量声明
static char emptyc=' ',socname[6][100]={0},keyCode;
static int i,j,k,lastaddst=0,lastaddsoc2=-1,stunull=1;
static int choosetype,choose;//对于是否选择，选择1：是，选择2：否，
static int nowselect=1,q=1,s[6]={0,0,0,0,0,0};
#define studentidlen 100
#define studentnamelen 80
#define fileopen fp=fopen("a.txt","ab+")
#define newfileopen fp=fopen("a.txt","wb+")
//student infomation
struct student {
	char id[studentidlen];
	char name[studentnamelen];
    int so[5];
}stu[100],temp;
FILE * fp;
FILE * in;
FILE * sout;


//End
//主函数，通过主函数实现主要功能
void main (){
	int st;
	clear();
	st = welcome(1);
	mainpage();
	
}
//欢迎屏幕
int welcome(int wtype){
	int state;
	if(wtype==1){
		SetConsoleTitle("学生成绩管理系统----by谭道桓");//通过Windows.h里的SetConsoleTitle设置标题
		clear();//清空屏幕
		printf("\n\n\n\n%28c欢迎使用学生成绩管理系统\n%33c设计：谭道桓\n%31c学号:201511106312\n\n%15c正在加载中",emptyc,emptyc,emptyc,emptyc);
		for(i=0;i<10;i++){
			Sleep(30);
			for(j=0;j<i;j++){
				printf("#");
			}
			
			for(k=38-i;k>=0;k--){
				printf("-");
			}
			printf(">\r%15c读取设置<",emptyc);
		}
		
		readsetting();//读取设置
		for(i=10;i<30;i++){
			Sleep(30);
			for(j=0;j<i;j++){
				printf("#");
			}
			
			for(k=38-i;k>=0;k--){
				printf("-");
			}
			printf(">\r%15c读取信息<",emptyc);
		}
		Sleep(100);
		fromfile();//读取数据
		for(i=30;i<40;i++){
			Sleep(15);
			for(j=0;j<i;j++){
				printf("#");
			}
			
			for(k=38-i;k>=0;k--){
				printf("-");
			}
			printf(">\r%15c调整效果<",emptyc);
		}
		Sleep(300);
		system("mode con cols=80 lines=35");
		//调整窗口效果，宽度80，显示35行
		printf("\n\n\n\n%28c欢迎使用学生成绩管理系统\n%33c设计：谭道桓\n%31c学号:201511106312\n",emptyc,emptyc,emptyc,emptyc);
		
		
		printf("\n%34c加载完成！\n",emptyc);
		
		//初始化成绩
		for(i=0;i<=100;i++){
			for(j=0;j<=5;j++){
				stu[i].so[j]=0;
			}
		}
		//Sleep
		
		Sleep(1500);
		clear();
	}//首次加载
	outputline();
	state=checkstate();
    system("color f9");//设定输出窗口颜色
	
	if(state==1){
		printf("你还没有录入任何学生信息，录入学生信息请输入Y或者直接按回车，坚持不录入学生信息请输入N\n注意：如果没有录入学生信息，之后部分功能将异常或无法使用。\n");
		choose=getchoose(2);//chooseose类型1：数字，类型2：是否
		if(choose==1){
			return 11;
		}
		else if(choose==2){
			return 888;
		}
		else {
			return 999;
		}
	}
	if(state==2){
		printf("你刚刚创建了学生信息表，马上录入成绩请输入Y或者直接按回车，不录入输入N\n");
		choose=getchoose(2);//chooseose类型1：数字，类型2：是否
		if(choose==1){
			return 21;
		}
		else if(choose==2){
			return 888;
		}
		else {
			return 999;
		}
	}
	if(wtype!=1){
		return 1000;
	}
	return 0;
}
//主界面处理


void mainpage(){
	char keyCode;
	int nowselect=1,q=1;
	for(;;){
		for(;;){
			clear();
			q=nowselect;
			if(q==1)
				printf("\n\n\n\t\t<---    1.录入学生信息\t\t--->\n\n\n");
			else
				printf("\n\n\n\t\t\t1.录入学生信息\n\n\n");
			if(q==2)
				printf("\t\t<---    2.批量录入成绩\t\t--->\n\n\n");
			else 
				printf("\t\t\t2.批量录入成绩\n\n\n");
			if(q==3)
				printf("\t\t<---    3.查看成绩\t\t--->\n\n\n");
			else 
				printf("\t\t\t3.查看成绩\n\n\n");
			if(q==4)
				printf("\t\t<---    4.输出成绩表\t\t--->\n\n\n");
			else
				printf("\t\t\t4.输出成绩表\n\n\n");
			if(q==5)
				printf("\t\t<---    5.数据查询更改\t\t--->\n\n\n");
			else
				printf("\t\t\t5.数据查询更改\n\n\n");
			if(q==0)
				printf("\t\t<---    0.退出程序\t--->\n\n\n");
			else
				printf("\t\t\t0.退出程序\n\n\n");
			printf("通过Tab和方向键可以轮换选择或直接输入数字，按下Enter来确认选择");
			fflush(stdin);
			keyCode=getch();
			if(keyCode==9){
				if(nowselect==5)
					nowselect=0;
				else
					nowselect=nowselect+1;
			}
			else if(keyCode==13){
				break;
			}
			else if(keyCode==-32){
				keyCode=getch();
				if(keyCode==72)
					if(nowselect==0)
						nowselect=5;
					else 
						nowselect=nowselect-1;
					if(keyCode==80)
						if(nowselect==5)
							nowselect=0;
						else nowselect=nowselect+1;
			}
			else if(keyCode-48<=5 &&keyCode-48>=0){
				nowselect=keyCode-48;
			}
		}
		//选择结束
		if(nowselect==0){
			fclose(in);
			fclose(fp);
			system("del a.txt");
			system("del setting.txt");
			tofile();
			savesetting();
			exit(0);
		}
		if(nowselect==1){
			newstudent();
		}
		if(nowselect==2){
			newsocks();
		}
		if(nowselect==3){
			getsocks(0);
		}
		if(nowselect==4){
			getsocks(1);
		}
		if(nowselect==5){
			if(stunull==1){
				clear();
				printf("你还没有建立学生信息档案,按任意键返回");
				getch();
			}
			else checkchange();
		}
	}
} 

//正式处理数据
int newstudent(){
	int oldlastaddst;
	clear();
	
	printf("\n\n\t本程序最多允许录入100名学生信息。按任意键继续或N返回主页面");
	
	if(getchoose(3)!=1){
		return 0;
	}
	clear();
	oldlastaddst=lastaddst;
	for(i=lastaddst;i<=100;i++){
		printf("\n\n\t\t\t录入学生信息：\n\n");
		printf("\t学号：");
		scanf("%s",stu[i].id);
		fflush(stdin);
		printf("\t姓名：");
		scanf("%s",stu[i].name);
		fflush(stdin);
		lastaddst=i;
		printf("\n\t录入成功，按任意键继续或按N返回主页面");
		stunull=0;
		if(getchoose(3)==0){
			break;
		}
		clear();
		printf("\t\t\t本次录入的学生信息\n\n");
		printf("\t\t----------------+----------------\n");
		printf("\t\t|\t学号\t+\t姓名\t|\n");
		printf("\t\t|---------------+---------------|\n");
		for(j=oldlastaddst;j<=i;j++){
			printf("\t\t|\t%s\t+\t%s\t|\n",stu[j].id,stu[j].name);
		}
		printf("\t\t----------------+----------------\n");
	}
	return 0;
	
}
int newsocks(){
	int nowselect=1;
	char keyCode;
	for(;;){
		clear();
		
		if(nowselect==1)
			printf("\n\n\n\t\t<---    1.单门学科成绩录入\t\t--->\n\n\n");
		else
			printf("\n\n\n\t\t\t1.单门学科成绩录入\n\n\n");
		if(nowselect==2)
			printf("\t\t<---    2.同时录入多个成绩\t\t--->\n\n\n");
		else 
			printf("\t\t\t2.同时录入多个成绩\n\n\n");
		printf("\t批量录入请根据提示输入对应学生的成绩\n\t最多允许记录5个不同的成绩\n");
		printf("\t模式说明：如果希望录入同一个学生的多个成绩请选择2\n\t如果希望录入单门学科全班成绩请选择1\n\n");
		printf("通过Tab和方向键可以轮换选择或直接输入数字，按下Enter来确认选择");
		fflush(stdin);
		keyCode=getch();
		if(keyCode==9 || keyCode==-32){
			if(nowselect==1)
				nowselect=2;
			else
				nowselect=1;
		}
		else if(keyCode==13){
			break;
		}
		else{
			if(keyCode-48==1 || keyCode-48==2)
				nowselect=keyCode-48;
		}
	}
	if(stunull==1){
		clear();
		printf("你还没有建立学生信息档案,按任意键返回");
		getch();
		return 0;
	}
	else if(nowselect==1)
		socksadd1c();
	else
		socksadd2();
	return 0;
}
int socksadd1c(){
	
	//------------------------------------------------------------------------------------------------------
	int nowselect=1,q=1;
	char keyCode;
	system("color f0");
	for(;;){
		for(;;){
			clear();
			q=nowselect;
			printf("请选择即将录入的成绩");
			if(q==1){
				printf("\n\n\n\t\t<---    1.");
				if(socname[1][0]!='\0')
					printf("%s",socname[1]);
				else
					printf("[空]");
				printf("\t\t--->\n\n\n");}
			else{
				printf("\n\n\n\t\t\t1.");
				if(socname[1][0]!='\0')
					printf("%s",socname[1]);
				else
					printf("[空]");
				printf("\n\n\n");}
			if(q==2){
				printf("\t\t<---    2.");
				if(socname[2][0]!='\0')
					printf("%s",socname[2]);
				else
					printf("[空]");
				printf("\t\t--->\n\n\n");}
			else {
				printf("\t\t\t2.");
				if(socname[2][0]!='\0')
					printf("%s",socname[2]);
				else
					printf("[空]");
				printf("\n\n\n");}
			if(q==3){
				printf("\t\t<---    3.");
				if(socname[3][0]!='\0')
					printf("%s",socname[3]);
				else
					printf("[空]");
				printf("\t\t--->\n\n\n");}
			else {
				printf("\t\t\t3.");
				if(socname[3][0]!='\0')
					printf("%s",socname[3]);
				else
					printf("[空]");
				printf("\n\n\n");}
			if(q==4){
				printf("\t\t<---    4.");
				if(socname[4][0]!='\0')
					printf("%s",socname[4]);
				else
					printf("[空]");
				printf("\t\t--->\n\n\n");}
			else{
				printf("\t\t\t4.");
				if(socname[4][0]!='\0')
					printf("%s",socname[4]);
				else
					printf("[空]");
				printf("\n\n\n");}
			if(q==5){
				printf("\t\t<---    5.");
				if(socname[5][0]!='\0')
					printf("%s",socname[5]);
				else
					printf("[空]");
				printf("\t\t--->\n\n\n");}
			else{
				printf("\t\t\t5.");
				if(socname[5][0]!='\0')
					printf("%s",socname[5]);
				else
					printf("[空]");
				printf("\n\n\n");}
			if(q==0)
				printf("\t\t<---    0.退出录入\t--->\n\n\n");
			else
				printf("\t\t\t0.退出录入\n\n\n");
			printf("通过Tab和方向键可以轮换选择或直接输入数字，按下Enter来确认选择\n注意：一旦您选择了批量录入，请录入全部的信息,如需更改，请使用数据查询更改功能。");
			fflush(stdin);
			keyCode=getch();
			if(keyCode==9){
				if(nowselect==5)
					nowselect=0;
				else
					nowselect=nowselect+1;
			}
			else if(keyCode==13){
				break;
			}
			else if(keyCode==-32){
				keyCode=getch();
				if(keyCode==72)
					if(nowselect==0)
						nowselect=5;
					else 
						nowselect=nowselect-1;
					if(keyCode==80)
						if(nowselect==5)
							nowselect=0;
						else nowselect=nowselect+1;
			}
			else if(keyCode-48<=5 &&keyCode-48>=0){
				nowselect=keyCode-48;
			}
		}
		//选择结束
		if(nowselect==0){
			return 0;
		}
		if(nowselect==1){
			socksadd1(1);
		}
		if(nowselect==2){
			socksadd1(2);
		}
		if(nowselect==3){
			socksadd1(3);
		}
		if(nowselect==4){
			socksadd1(4);
		}
		if(nowselect==5){
			socksadd1(5);
		}
	}
	
	
	
	//------------------------------------------------------------------------------------------------------
	system("color f9");
	return 0;
}
int socksadd1(int st){
	int gsoc;
	clear();
	if(socname[st][0]=='\0'){
		printf("\n您还没有为该成绩确定名称，请输入名称：");
		scanf("%s",socname[st]);
		fflush(stdin);
		printf("\n是否继续录入成绩？任意键来确定或输入N取消");
		if(getchoose(3)==0)
			return 0;
	}
	//===========================================================================================
	
	clear();
	printf("\t\t请直接输入对应学生的成绩\n");
	printf("\t----------------+---------------+---------------|\n");
	printf("\t|\t学号\t+\t姓名\t|\t");
	printf("%s",socname[st]);
	printf("\t|\n");
	printf("\t|---------------+---------------+---------------|\n");
	for(j=0;j<=lastaddst;j++){
		
		printf("\t|\t%s\t+\t%s\t|\t",stu[j].id,stu[j].name);
		fflush(stdin);
		scanf("%d",&gsoc);
		stu[j].so[st] = gsoc;
	}
	printf("\t----------------+---------------+----------------\n");
	printf("\n\t全部录入完成,按任意键返回");
	fflush(stdin);
	getch();
	return 0;
	//===========================================================================================
	
}
int socksadd2(){
	char keyCode;
	int cango=0;
	//------------------------------------------------------------------------------------------------------
	
	for(;;){
		for(;;){
			clear();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
			q=nowselect;
			printf("请选择即将录入的成绩，按空格键或回车选择/取消选择\n\n");
			
			for(i=1;i<=5;i++){
				if(q==i){
					printf("\t\t<---    ");
					printf("%d.",i);
					if(socname[i][0]!='\0'){
						printf("%s",socname[i]);
						if(s[i]==1){
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
							printf("√已选择");
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						}
						else{
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
							printf("×未选择");
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						}
					}	
					else
						printf("[空]");
					
					printf("\t\t--->\n\n\n");}
				else{
					printf("\t\t\t");
					printf("%d.",i);
					if(socname[i][0]!='\0'){
						printf("%s",socname[i]);
						if(s[i]==1){
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
							printf("√已选择");
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						}
						else{
							HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
							SetConsoleTextAttribute(hConsole, FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
							printf("×未选择");
							SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						}
					}
					else
						printf("[空]");
					
					printf("\n\n\n");}
				
			}
			
			
			
			for(i=1;i<=5;i++){
				if(s[i]==1){
					if(q==6){
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						printf("\t\t<---    6.确认选择");
						printf("√可用");
						cango=1;
						printf("\t--->\n\n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						break;
					}
					else{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						
						printf("\t\t\t6.确认选择");
						
						printf("√可用");
						cango=1;
						printf("\n\n\n");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
						break;
					}
				}
				cango=0;
				
			}
			
			
			if(cango==0){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
				
				printf("\t\t\t6.确认选择");
				
				printf("×不可用");
				printf("\n\n\n");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_INTENSITY|BACKGROUND_INTENSITY|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED);
			}
			
			
			
			
			
			
			
			
			if(q==0)
				printf("\t\t<---    0.退出录入\t--->\n\n\n");
			else
				printf("\t\t\t0.退出录入\n\n\n");
			
			printf("通过Tab和方向键可以轮换选择或直接输入数字，按下Enter来确认选择\n注意：一旦您选择了批量录入，请录入全部的信息,如需更改，请使用数据查询更改功能。");
			fflush(stdin);
			keyCode=getch();
			if(keyCode==9){
				if(nowselect==5)
					if(cango=0)
						nowselect=0;
					else
						nowselect=6;
					else
						nowselect=nowselect+1;
			}
			else if(keyCode==13||keyCode==32){
				if(nowselect==0){
					system("color f9");
					return 0;
				}
				for(i=1;i<=5;i++){
					if(nowselect==i){
						if(socname[i][0]=='\0'){
							clear();
							printf("\n您还没有为该成绩确定名称，请输入名称：");
							scanf("%s",socname[i]);
							fflush(stdin);
						}
						if(s[i]==0){
							s[i]=1;
						}
						else{
							s[i]=0;
						}
					}
				}
				if(nowselect==6){
					system("color f9");
					break;
				}
			}
			else if(keyCode==-32){
				keyCode=getch();
				if(keyCode==72)
					if(nowselect==0)
						nowselect=6;
					else 
						nowselect=nowselect-1;
					if(keyCode==80)
						if(nowselect==6)
							nowselect=0;
						else nowselect=nowselect+1;
			}
			else if(keyCode-48<=6 &&keyCode-48>=0){
				nowselect=keyCode-48;
			}
		}
		//选择结束
		break;
	}
	socksadd2c();
	
	return 0;
	//------------------------------------------------------------------------------------------------------
	
	
}

int socksadd2c(){
	int line=2,q1,q2,q3,gsoc;
	for(i=1;i<=5;i++){
		if(s[i]==1)
			line++;
	}
	//调整视觉效果
	switch(line)
	{
    case 3:
		system("mode con cols=51 lines=30");
		break;
    case 4:
		system("mode con cols=66 lines=30");
		break;
    case 5:
		system("mode con cols=81 lines=30");
		break;
    case 6:
		system("mode con cols=98 lines=30");
		break;
    case 7:
		system("mode con cols=113 lines=30");
		break;
    default:
		system("mode con cols=81 lines=30");
	}
	if(lastaddsoc2<=4){
		q1=lastaddsoc2;
		if(lastaddsoc2!=-1)
			q2=0;
		else
			q2=lastaddsoc2;
		if(q2+6>=lastaddst)
			q3=lastaddst;
		else
			q3=q2+6;
	}
	else{
		q1=lastaddsoc2-5;
		q2=lastaddsoc2;
		if(q2+6>=lastaddst)
			q3=lastaddst;
		else
			q3=q2+7;
	}
	
	for(k=0;k<=lastaddst;k++){
		clear();
		printf("\t\t成绩录入\n\n");
		for(i=1;i<=line;i++)
			printf("+---------------");
		printf("\n");
		printf("|\t学号\t+\t姓名\t");
		for(i=1;i<=5;i++){
			if(s[i]==1){
				printf("+\t%s\t",socname[i]);
			}
		}
		printf("|\n");
		if(1){
		/*未来继续完善，本次作业暂时不完成本显示
		for(i=1;i<=line;i++)
		printf("+---------------");
		printf("\n");
		for(j=q1;j<=q2;j++){
		printf("|\t%s\t+\t%s\t",stu[j].id,stu[j].name);
		for(i=1;i<=5;i++){
		if(s[i]==1){
		}
		}		printf("+\t%s\t",stu[j].so[i]);
		
		  printf("|\n");
		  }
		  
			*/
			
			fflush(stdin);
			printf("当前录入：\n");
			printf("\t学号：%s\t姓名：%s\t\n请依次输入录入的信息",stu[k].id,stu[k].name);
			for(i=0;i<=5;i++){
				if(s[i]==1){
					printf("%s：",socname[i]);
					printf("\n");
					fflush(stdin);
					scanf("%d",&gsoc);
					stu[j].so[i] = gsoc;
				}
			}
			
			if(lastaddsoc2!=lastaddst-1){
				printf("\t\t等待录入\n");
				printf("\t\t----------------+----------------\n");
				printf("\t\t|\t学号\t+\t姓名\t|\n");
				printf("\t\t|---------------+---------------|\n");
				for(j=q2+2;j<=q3;j++){
					printf("\t\t|\t%s\t+\t%s\t|\n",stu[j].id,stu[j].name);
				}
				printf("\t\t----------------+----------------\n");
			}
			/***********************************************************************************************************************************************/
			
			
			
			
		}
		
	}
	fflush(stdin);
	printf("录入完成，按任意键返回");
	lastaddsoc2++;
	system("mode con cols=80 lines=35");
	getch();
	fflush(stdin);
	return 0;
}



int getsocks(int mod){
	int line=2;
	for(;;){
		for(;;){
			clear();
			q=nowselect;
			printf("请选择排序依据\n\n\n");
			for(i=1;i<=5;i++){
				if(socname[i][0]!='\0'){
					if(q==i){
						printf("\t\t<---    %d.",i);
						printf("根据 %s 排序",socname[i]);
						printf("\t\t--->\n\n");}
					else{
						printf("\t\t\t%d.",i);
						printf("根据 %s 排序",socname[i]);
						printf("\n\n");}
				}
			}
			if(q==6){
				printf("\t\t<---    6.");
				printf("根据总分排序");
				printf("\t\t--->\n\n");}
			else{
				printf("\t\t\t6.");
				printf("根据总分排序");
				printf("\n\n");}
			if(q==0)
				printf("\t\t<---    0.返回主页面\t--->\n\n\n");
			else
				printf("\t\t\t0.返回主页面\n\n\n");
			printf("通过Tab和方向键可以轮换选择或直接输入数字，按下Enter来确认选择\n注意：一旦您选择了批量录入，请录入全部的信息,如需更改，请使用数据查询更改功能。");
			fflush(stdin);
			keyCode=getch();
			if(keyCode==9){
				if(nowselect==5)
					nowselect=0;
				else
					nowselect=nowselect+1;
			}
			else if(keyCode==13){
				break;
			}
			else if(keyCode==-32){
				keyCode=getch();
				if(keyCode==72)
					if(nowselect==0)
						nowselect=5;
					else 
						nowselect=nowselect-1;
					if(keyCode==80)
						if(nowselect==5)
							nowselect=0;
						else nowselect=nowselect+1;
			}
			else if(keyCode-48<=5 &&keyCode-48>=0){
				nowselect=keyCode-48;
			}
		}
		//选择结束
		if(nowselect==0){
			return 0;
		}
		if(nowselect==1){
			order(1);
		}
		if(nowselect==2){
			order(2);
		}
		if(nowselect==3){
			order(3);
		}
		if(nowselect==4){
			order(4);
		}
		if(nowselect==5){
			order(5);
		}
	clear();
		printf("\n\n\n\t\t\t调整中。。。");
	for(i=1;i<=5;i++){
		if(socname[i][0]!='\0')
			line++;
	}
	//调整视觉效果
	switch(line)
	{
    case 3:
		system("mode con cols=51 lines=30");
		break;
    case 4:
		system("mode con cols=66 lines=30");
		break;
    case 5:
		system("mode con cols=81 lines=30");
		break;
    case 6:
		system("mode con cols=98 lines=30");
		break;
    case 7:
		system("mode con cols=113 lines=30");
		break;
    default:
		system("mode con cols=81 lines=30");
	}
		Sleep(1000);
		clear();
		if(mod==1){
				printf("处理中，请稍后\n");
				sout = freopen("out.txt", "w", stdout);//输出重定向
				}
		out(line);
		if(mod==1){
			
			
		sout = freopen("CON", "w", stdout);//重新输出到屏幕
		tofile();
		savesetting();
		printf("成绩报表保存到out.txt成功\n数据已经保存，如果返回之后显示出现问题请重启本程序");
		
		}
		printf("按任意键返回主页面");
		getchoose(3);

		system("mode con cols=81 lines=30");
		return 0;
}


}
void out(int line){

		for(i=1;i<=line;i++)
			printf("+---------------");
		printf("\n");
		printf("|\t学号\t+\t姓名\t");
		for(i=1;i<=5;i++){
			if(socname[i][0]!='\0'){
				printf("+\t%s\t",socname[i]);
			}
		}
		printf("|\n");
		for(i=0;i<=lastaddst;i++){
			printf("|\t%s\t+\t%s\t",stu[i].id,stu[i].name);
			for(j=1;j<=5;j++){
				if(socname[j][0]!='\0'){
					printf("+\t%d\t",stu[i].so[j]);
							}
							
			}
		printf("|\n");
		}
			for(i=1;i<=line;i++)
			printf("+---------------");
		
		
	}

int order(int st){
	for(i=0;i<100;i++){
		if(st==6){
		stu[i].so[0]=stu[i].so[1]+stu[i].so[2]+stu[i].so[3]+stu[i].so[4]+stu[i].so[5];
		st=0;
	}
	}
	for(i=0;i<100;i++)
		for(j=i+1;j<100;j++)
			if(stu[i].so[st]<stu[j].so[st]){
				temp=stu[i];
				stu[i]=stu[j];
				stu[j]=temp;
			}
			return 0;
}

int checkchange(){
	int exit=0,change=0;
	int nowselect=0;
	char keyCode;
	for(;;){
		clear();
		printf("\t\t----------------+----------------\n");
		printf("\t\t|\t学号\t+\t姓名\t|\n");
		printf("\t\t|---------------+---------------|\n");
		for(j=0;j<=lastaddst;j++){
			if(j!=nowselect)
				printf("\t\t|\t%s\t+\t%s\t|\n",stu[j].id,stu[j].name);
			else
				printf("\t   ====>\t%s\t+\t%s\t<====\n",stu[j].id,stu[j].name);
		}
		printf("\t\t----------------+----------------\n");
		printf("\t\t按ESC返回主页面\n");
		fflush(stdin);
		keyCode=getch();
		if(keyCode==27){
			exit=1;
		}
		if(keyCode==9){
			if(nowselect==lastaddst)
				nowselect=0;
			else
				nowselect=nowselect+1;
		}
		else if(keyCode==13){
			change=1;
		}
		else if(keyCode==-32){
			keyCode=getch();
			if(keyCode==72)
				if(nowselect==0)
					nowselect=lastaddst;
				else 
					nowselect=nowselect-1;
				if(keyCode==80)
					if(nowselect==lastaddst)
						nowselect=0;
					else nowselect=nowselect+1;
		}
		if(exit==1)
			return 0;
		if(change==1)
			changest(nowselect);
		change=0;
		
	}
	
}
//信息修改
int changest(int a){
	int nowselect=0,all=2,gsoc;
	char keyCode;
	for(;;){
		clear();
		printf("\n\n\t\t\t将修改学生信息：\n\n");
		printf("\t\t|\t%s\t+\t%s\t|\n",stu[a].id,stu[a].name);
		printf("请选择需要更改的内容，按回车确认，选择取消放弃更改\n");
		if(nowselect==0)
			printf("    ===> 取消更改  <===\n");
		else
			printf("\t 取消更改\n");
		if(nowselect==1)
			printf("    ===>学号：%s   <===\n",stu[a].id);
		else
			printf("\t学号：%s\n",stu[a].id);
		if(nowselect==2)
			printf("    ===>姓名：%s   <===\n",stu[a].name);
		else
			printf("\t姓名：%s\n",stu[a].name);
		if(nowselect==3)
			printf("    ===>%s：%d   <===\n",socname[1],stu[a].so[1]);
		else
			printf("\t%s：%d\n",socname[1],stu[a].so[1]);
		if(nowselect==4)
			printf("    ===>%s：%d   <===\n",socname[2],stu[a].so[2]);
		else
			printf("\t%s：%d\n",socname[2],stu[a].so[2]);
		if(nowselect==5)
			printf("    ===>%s：%d   <===\n",socname[3],stu[a].so[3]);
		else
			printf("\t%s：%d\n",socname[3],stu[a].so[3]);
		if(nowselect==6)
			printf("    ===>%s：%d   <===\n",socname[4],stu[a].so[4]);
		else
			printf("\t%s：%d\n",socname[4],stu[a].so[4]);
		if(nowselect==7)
			printf("    ===>%s：%d   <===\n",socname[5],stu[a].so[5]);
		else
			printf("\t%s：%d\n",socname[5],stu[a].so[5]);
		
		
		
		
		///////////////////////////////////////////////////////////////////////////////////////////////
		fflush(stdin);
		keyCode=getch();
		if(keyCode==13){
			printf("\n请输入更改后的信息");
			fflush(stdin);
			if(nowselect==0)
				return 0;
			if(nowselect==1)
				scanf("%s",stu[a].id);
			if(nowselect==2)
				scanf("%s",stu[a].name);
			if(nowselect==3){
				if(socname[1][0]=='\0'){
					printf("\n您还没有为该成绩确定名称，请输入名称：");
					scanf("%s",socname[1]);
					fflush(stdin);
					clear();
					printf("\n请输入更改后的信息:");
				}
				fflush(stdin);
				scanf("%d",&gsoc);
				stu[a].so[1] = gsoc;
			}
			if(nowselect==4){
				if(socname[2][0]=='\0'){
					printf("\n您还没有为该成绩确定名称，请输入名称：");
					fflush(stdin);
					scanf("%s",socname[2]);
					fflush(stdin);
					clear();
					printf("\n请输入更改后的信息:");
				}
				scanf("%d",&gsoc);
				stu[a].so[2] = gsoc;
			}
			if(nowselect==5){
				if(socname[3][0]=='\0'){
					printf("\n您还没有为该成绩确定名称，请输入名称：");
					fflush(stdin);
					scanf("%s",socname[3]);
					fflush(stdin);
					clear();
					printf("\n请输入更改后的信息:");
				}
				scanf("%d",&gsoc);
				stu[a].so[3] = gsoc;
			}
			if(nowselect==6){
				if(socname[4][0]=='\0'){
					printf("\n您还没有为该成绩确定名称，请输入名称：");
					fflush(stdin);
					scanf("%s",socname[4]);
					fflush(stdin);
					clear();
					printf("\n请输入更改后的信息:");
				}
				scanf("%d",&gsoc);
				stu[a].so[4] = gsoc;
			}
			if(nowselect==7){
				if(socname[5][0]=='\0'){
					printf("\n您还没有为该成绩确定名称，请输入名称：");
					fflush(stdin);
					scanf("%s",socname[5]);
					fflush(stdin);
					clear();
					printf("\n请输入更改后的信息:");
				}
				scanf("%d",&gsoc);
				stu[a].so[5] = gsoc;
			}
			break;
		}
		else if(keyCode==-32){
			keyCode=getch();
			if(keyCode==72)
				if(nowselect==0)
					nowselect=7;
				else 
					nowselect=nowselect-1;
				if(keyCode==80)
					if(nowselect==7)
						nowselect=0;
					else nowselect=nowselect+1;
		}
	}
	clear();
	printf("修改成功,按任意键返回");
	fflush(stdin);
	getch();
	return 0;
}


//清空屏幕上所有内容
int clear(){
	system("cls");
	return 1;
}
int getchoose(int t){
	if(t==3){
		char ch;
		fflush(stdin);
		ch=getchar();
		fflush(stdin);
		if(ch!='n' && ch!='N'){
			return 1;
		}
		else return 0;
	}
	else return 1;
}
//output
void outputline(){
	for(i=0;i<79;i++){
		printf("*");
	}
	printf("\n");
}
int checkstate(){
	return 55;
}

int tofile(){
	if((newfileopen)==NULL){
		clear();
		printf("文件读取失败！按任意键继续");
		fflush(stdin);
		getch();
		return 0;
	}
	for(i=0;i<=lastaddst;i++){
		fwrite(&stu[i], sizeof(stu[i]),1,fp);
	}
	rewind(fp);
	return 0;
	
	
}
int fromfile(){
	if((newfileopen)==NULL){
		clear();
		printf("文件读取失败！按任意键继续");
		fflush(stdin);
		getch();
		return 0;
	}
	for(i=0;i<=lastaddst;i++){
		fread(&stu[i], sizeof(stu[i]),1,fp);
	}
	rewind(fp);
	return 0;
	
}
int savesetting(){
	in=fopen("setting.txt","ab+");
	rewind(in);
	for(i=0;i<=5;i++){
		fwrite(&socname[i],sizeof(socname[i]),1,in);
	}
	fprintf(in,"%d",lastaddst);
	rewind(in);
	return 0;
}
int readsetting(){
	in=fopen("setting.txt","ab+");
	rewind(in);
	for(i=0;i<=5;i++){
		fread(&socname[i],sizeof(socname[i]),1,in);
	}
	fscanf(in,"%d",&lastaddst);
	stunull=0;
	rewind(in);
	return 0;
}

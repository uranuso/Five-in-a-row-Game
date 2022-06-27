#include<stdio.h>
#include<windows.h>
#include<time.h>
#define SIZEOFCHESS 15

int p=1;
int remindx,remindy;
int chess[50][50];
int grade[50][50]={{0}};
struct node
{
	int row;
	int col;
	int po;
}mem;

void initialize();
void outputini();
void outputres();
int  win();
void pvp();
void pve1();
void pve2();
void eve();
int  getype(int x,int y,int i,int j,int k);
void score(int k);
void find(int k);
void replay();

int main()
{
	initialize();
	
	HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
	// 获取标准输入输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	INPUT_RECORD	mouseRec;
	DWORD			res;
	COORD			crPos,crHome={0,0};
	while(1)
	{
		ReadConsoleInput(hIn,&mouseRec,1,&res);
		if (mouseRec.EventType==MOUSE_EVENT)
		{
			crPos=mouseRec.Event.MouseEvent.dwMousePosition;
			GetConsoleScreenBufferInfo(hOut,&bInfo);
			SetConsoleCursorPosition(hOut,crHome);
			//printf("[Cursor Position] X: %2lu  Y: %2lu ",crPos.X,crPos.Y);
			SetConsoleCursorPosition(hOut, bInfo.dwCursorPosition);
			if(mouseRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if((crPos.X>=6)&&(crPos.X<=17)&&(crPos.Y==2))
				{
					SetConsoleCursorPosition(hOut,crHome);
					pvp();
					break;
				}  
				else if((crPos.X>=6)&&(crPos.X<=24)&&(crPos.Y==3))
				{
					SetConsoleCursorPosition(hOut,crHome);
					pve1();
					break;
				}
				else if((crPos.X>=6)&&(crPos.X<=24)&&(crPos.Y==4))
				{
					SetConsoleCursorPosition(hOut,crHome);
					pve2();
					break;
				}
				else if((crPos.X>=6)&&(crPos.X<=17)&&(crPos.Y==5))
				{
					SetConsoleCursorPosition(hOut,crHome);
					eve();
					break;
				}
				else if((crPos.X>=8)&&(crPos.X<=15)&&(crPos.Y==6))
				{
					SetConsoleCursorPosition(hOut,crHome);
					replay();
					break;
				}
				else if((crPos.X>=9)&&(crPos.X<=14)&&(crPos.Y==8))
				{
					break;
				}
			}
		}		
	}
	CloseHandle(hOut);  // 关闭标准输出设备句柄 
	CloseHandle(hIn);   // 关闭标准输入设备句柄
	return 0;
}

void initialize()
{
	printf("\n\n      *Start  PVP*");
	printf("\n      *Start  PVE*(black)");
	printf("\n      *Start  PVE*(white)");
	printf("\n      *Start  EVE*");
	printf("\n        *Replay*");
	printf("\n\n         *QUIT*");
	printf("\n\nUse your mouse to click!");
	printf("\n请先关闭控制台属性中的\n    <快速编辑模式>");
}
void outputres()
{
	printf("\n");
	printf("  1 ");
	for(int i=2;i<=SIZEOFCHESS;i++)
	{
		printf("%-2d",i);
	}
	printf("\n");
	for(int col=1;col<=SIZEOFCHESS;col++)
	{
		printf("%-2d",col);
		for(int row=1;row<=SIZEOFCHESS;row++)
		{
			if(chess[row][col]==1)
				printf("●");
			else if(chess[row][col]==-1)
				printf("○");
			else if(chess[row][col]==0)
				printf("# ");
		}
		printf("\n");
	}
}
void outputini()
{
	printf("\n");
	printf("  1 ");
	for(int i=2;i<=SIZEOFCHESS;i++)
	{
		printf("%-2d", i);
	}
	printf("\n");
	for(int col=1;col<=SIZEOFCHESS;col++)
	{
		printf("%-2d",col);
		for(int row=1;row<=SIZEOFCHESS;row++)
		{
			printf("# ");
		}
		printf("\n");
	}
}
int win()
{
	//行
	for(int row=1;row<=SIZEOFCHESS;row++)
	{
		for(int col=1;col<=SIZEOFCHESS-4;col++)
		{
			int sum=0;
			for(int i=0;i<5;i++)
				sum+=chess[row][col+i];
			if(sum==5)
				return 1;
			else if(sum==-5)
				return -1;
		}
	}
	//列
	for(int col=1;col<=SIZEOFCHESS;col++)
	{
		for(int row=1;row<=SIZEOFCHESS-4;row++)
		{
			int sum=0;
			for(int i=0;i<5;i++)
				sum+=chess[row+i][col];
			if(sum==5)
				return 1;
			else if(sum==-5)
				return -1;
		}
	}
	//主对角线 
	for(int row=1; row<=SIZEOFCHESS-4;row++)
	{
		for(int col=1;col<=SIZEOFCHESS-4;col++)
		{
			int sum=0;
			for(int i=0;i<5;i++)
				sum+=chess[row+i][col+i];
			if(sum==5)
				return 1;
			else if(sum==-5)
				return -1;
		}
	}
	//副对角线 
	for(int row=1;row<=SIZEOFCHESS-4;row++)
	{
		for(int col=SIZEOFCHESS;col>=5;col--)
		{
			int sum=0;
			for(int i=0;i<5;i++)
				sum+=chess[row+i][col-i];
			if(sum==5)
				return 1;
			else if(sum==-5)
				return -1;
		}
	}
	return 0;
}
void pvp()
{
	int num=0;
	node mem[400];
	
	HANDLE hOut1=GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn1=GetStdHandle(STD_INPUT_HANDLE);
	// 获取标准输入输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo1;
	INPUT_RECORD	mouseRec1;
	DWORD			res1;
	COORD			crPos1,crHome1={0,0},crEnd1={0,22};
	
	outputini();
	while(1)
	{
		ReadConsoleInput(hIn1,&mouseRec1,1,&res1);
 
		if (mouseRec1.EventType==MOUSE_EVENT)
		{
			/*
			if (mouseRec1.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (mouseRec1.Event.MouseEvent.dwEventFlags==DOUBLE_CLICK)
				{
					SetConsoleCursorPosition(hOut1,crEnd1);
					break;	// 左键双击 退出循环
				}
			}	
			*/
			crPos1=mouseRec1.Event.MouseEvent.dwMousePosition;
			GetConsoleScreenBufferInfo(hOut1,&bInfo1);
			SetConsoleCursorPosition(hOut1,crHome1);
			printf("PVP   单击#以落子               ");//printf("[Cursor Position] X: %2lu  Y: %2lu", crPos1.X, crPos1.Y);
			SetConsoleCursorPosition(hOut1,bInfo1.dwCursorPosition);
			
			if(mouseRec1.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if((crPos1.X%2==0)&&(crPos1.X>=2)&&(crPos1.X<=2*SIZEOFCHESS)&&(crPos1.Y>=2)&&(crPos1.Y<=SIZEOFCHESS+1))
				{
					SetConsoleCursorPosition(hOut1,crEnd1);
					printf("\n                "); 
					if(num%2==1)
					{
						if(chess[crPos1.X/2][crPos1.Y-1]==0)
						{
							chess[crPos1.X/2][crPos1.Y-1]=1;
							SetConsoleCursorPosition(hOut1, crPos1);
							printf("●");
							num++;
							mem[num].row=crPos1.X/2;
							mem[num].col=crPos1.Y-1;
							mem[num].po=1;
						}
						else
						{
							SetConsoleCursorPosition(hOut1,crEnd1);
							printf("\n请在合适区域落子"); 
						}
					}
					else
					{
						if(chess[crPos1.X/2][crPos1.Y-1]==0)
						{
							chess[crPos1.X/2][crPos1.Y-1]=-1;
							SetConsoleCursorPosition(hOut1, crPos1);
							printf("○");
							num++;
							mem[num].row=crPos1.X/2;
							mem[num].col=crPos1.Y-1;
							mem[num].po=-1;
						}
						else
						{
							SetConsoleCursorPosition(hOut1,crEnd1);
							printf("\n请在合适区域落子"); 
						}	
					}
				}
				else 
				{
					SetConsoleCursorPosition(hOut1,crEnd1);
					printf("\n请在合适区域落子"); 
				} 
			}
			
			if(win()==1)
			{
				SetConsoleCursorPosition(hOut1,crEnd1);
				printf("White win!");
				break;
			}
			else if(win()==-1)
			{
				SetConsoleCursorPosition(hOut1,crEnd1);
				printf("Black win!");
				break;
			}
			if(num==SIZEOFCHESS*SIZEOFCHESS)
			{
				SetConsoleCursorPosition(hOut1,crEnd1);
				printf("Draw!");
				break;
			}
		}		
	}
	char fname[50];
	memset(fname,'0',sizeof(fname));
	printf("\n若无需保存则直接关闭此窗口 \n保存棋局请输入此棋局要保存的文件名："); 
	scanf("%s",&fname);
	FILE*fp;
	fp=fopen(fname,"w+");
	if((fp=fopen(fname,"w+"))==NULL)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\ncan't open the file");
        exit(0);
    }
    for(int i=1;i<=num;i++)
		fwrite(&mem[i],sizeof(struct node),1,fp);
	fclose(fp);
	CloseHandle(hOut1);  // 关闭标准输出设备句柄  
	CloseHandle(hIn1);   // 关闭标准输入设备句柄
	return;
}
void pve1()
{//人先手 机器后手 
	int num=0;
	node mem[400];
	
	HANDLE hOut2=GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn2=GetStdHandle(STD_INPUT_HANDLE);
	// 获取标准输入输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo2;
	INPUT_RECORD	mouseRec2;
	DWORD			res2;
	COORD			crPos2,crHome2={0,0},crEnd2={0,22};
	
	outputres();
	
	while (1)
	{
		ReadConsoleInput(hIn2,&mouseRec2,1,&res2);

		if (mouseRec2.EventType==MOUSE_EVENT)
		{
			crPos2=mouseRec2.Event.MouseEvent.dwMousePosition;
			GetConsoleScreenBufferInfo(hOut2,&bInfo2);
			SetConsoleCursorPosition(hOut2,crHome2);
			printf("PVE   先手黑棋   单击#以落子         ");//printf("[Cursor Position] X: %2lu  Y: %2lu", crPos2.X, crPos2.Y);
			SetConsoleCursorPosition(hOut2,bInfo2.dwCursorPosition);
			
			if(mouseRec2.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if((crPos2.X%2==0)&&(crPos2.X>=2)&&(crPos2.X<=2*SIZEOFCHESS)&&(crPos2.Y>=2)&&(crPos2.Y<=SIZEOFCHESS+1))
				{
					SetConsoleCursorPosition(hOut2,crEnd2);
					printf("\n                 "); 
					if(chess[crPos2.X/2][crPos2.Y-1]==0)
					{
						num++;
						chess[crPos2.X/2][crPos2.Y-1]=-1;
						SetConsoleCursorPosition(hOut2, crPos2);
						printf("○");
						mem[num].row=crPos2.X/2;
						mem[num].col=crPos2.Y-1;
						mem[num].po=-1;
						if(win()==1)
						{
							SetConsoleCursorPosition(hOut2,crEnd2);
							printf("White win!");
							break;
						}
						else if(win()==-1)
						{
							SetConsoleCursorPosition(hOut2,crEnd2);
							printf("Black win!");
							break;
						}
						if(num==SIZEOFCHESS*SIZEOFCHESS)
						{
							SetConsoleCursorPosition(hOut2,crEnd2);
							printf("Draw!");
							break;
						}
						score(p);
						find(p);
						num++;
						mem[num].row=remindy;
						mem[num].col=remindx;
						mem[num].po=1;
						SetConsoleCursorPosition(hOut2, crHome2);
						outputres();
						printf("last coordinate:%d %d   \nit's your turn  ",remindx,remindy);
						printf("\n\"steps:%d\"",num);
						/* 
						SetConsoleCursorPosition(hOut2,{0,20});
						for(int y=1;y<=SIZEOFCHESS;y++)
						{
							for(int x=1;x<=SIZEOFCHESS;x++)
								printf("%d ",grade[x][y]);
							printf("\n");
						}//输出grade 
						*/ 
						for(int x=1;x<=SIZEOFCHESS;x++)
							for(int y=1;y<=SIZEOFCHESS;y++)
								grade[x][y]=0;//grade清零
						if(win()==1)
						{
							SetConsoleCursorPosition(hOut2,crEnd2);
							printf("White win!");
							break;
						}
						else if(win()==-1)
						{
							SetConsoleCursorPosition(hOut2,crEnd2);
							printf("Black win!");
							break;
						}
						if(num==SIZEOFCHESS*SIZEOFCHESS)
						{
							SetConsoleCursorPosition(hOut2,crEnd2);
							printf("Draw!");
							break;
						}		
					}
					else
					{
						SetConsoleCursorPosition(hOut2,crEnd2);
						printf("\n请在合适区域落子"); 
					}
				}
				else
				{
					SetConsoleCursorPosition(hOut2,crEnd2);
					printf("\n请在合适区域落子"); 
				}
				
			}
		}		
	}
	char fname[50];
	memset(fname,'0',sizeof(fname));
	printf("\n若无需保存则直接关闭此窗口 \n保存棋局请输入此棋局要保存的文件名：");  
	scanf("%s",&fname);
	FILE*fp;
	fp=fopen(fname,"w+");
	if((fp=fopen(fname,"w+"))==NULL)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\ncan't open the file");
        exit(0);
    }
    for(int i=1;i<=num;i++)
		fwrite(&mem[i],sizeof(struct node),1,fp);
	fclose(fp);
	CloseHandle(hOut2);  // 关闭标准输出设备句柄  
	CloseHandle(hIn2);   // 关闭标准输入设备句柄
	return; 
}
void pve2()
{//机器先手 人后手 
	int num=0;
	node mem[400];
	
	HANDLE hOut3=GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn3=GetStdHandle(STD_INPUT_HANDLE);
	// 获取标准输入输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo3;
	INPUT_RECORD	mouseRec3;
	DWORD			res3;
	COORD			crPos3,crHome3={0,0},crEnd3={0,22};
	
	chess[(SIZEOFCHESS+1)/2][(SIZEOFCHESS+1)/2]=-1;
	remindx=(SIZEOFCHESS+1)/2;
	remindy=(SIZEOFCHESS+1)/2;
	num++;
	mem[num].row=remindy;
	mem[num].col=remindx;
	mem[num].po=-1;
	outputres();
	printf("last coordinate:%d %d   \nit's your turn  ",remindx,remindy);
	printf("\n\"steps:%d\"",num);//第一步 
	
	while (1)
	{
		ReadConsoleInput(hIn3,&mouseRec3,1,&res3);

		if (mouseRec3.EventType==MOUSE_EVENT)
		{
			crPos3=mouseRec3.Event.MouseEvent.dwMousePosition;
			GetConsoleScreenBufferInfo(hOut3,&bInfo3);
			SetConsoleCursorPosition(hOut3,crHome3);
			printf("PVE   后手白棋   单击#以落子         ");//printf("[Cursor Position] X: %2lu  Y: %2lu", crPos2.X, crPos2.Y);
			SetConsoleCursorPosition(hOut3,bInfo3.dwCursorPosition);
			
			if(mouseRec3.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if((crPos3.X%2==0)&&(crPos3.X>=2)&&(crPos3.X<=2*SIZEOFCHESS)&&(crPos3.Y>=2)&&(crPos3.Y<=SIZEOFCHESS+1))
				{
					if(chess[crPos3.X/2][crPos3.Y-1]==0)//人先手 机器后手 
					{
					
						SetConsoleCursorPosition(hOut3,crEnd3);
						printf("\n                 "); 
				
						num++;
						chess[crPos3.X/2][crPos3.Y-1]=1;
						mem[num].row=crPos3.X/2;
						mem[num].col=crPos3.Y-1;
						mem[num].po=1;
						SetConsoleCursorPosition(hOut3, crPos3);
						printf("●");
						if(win()==1)
						{
							SetConsoleCursorPosition(hOut3,crEnd3);
							printf("White win!");
							break;
						}
						else if(win()==-1)
						{
							SetConsoleCursorPosition(hOut3,crEnd3);
							printf("Black win!");
							break;
						}
						if(num==SIZEOFCHESS*SIZEOFCHESS)
						{
							SetConsoleCursorPosition(hOut3,crEnd3);
							printf("Draw!");
							break;
						}
						score(-p);
						find(-p);
						num++;
						mem[num].row=remindy;
						mem[num].col=remindx;
						mem[num].po=-1;
						SetConsoleCursorPosition(hOut3, crHome3);
						outputres();
						printf("last coordinate:%d %d   \nit's your turn  ",remindx,remindy);
						printf("\n\"steps:%d\"",num);
						/* 
						SetConsoleCursorPosition(hOut3,{0,20});
						for(int y=1;y<=SIZEOFCHESS;y++)
						{
							for(int x=1;x<=SIZEOFCHESS;x++)
								printf("%d ",grade[x][y]);
							printf("\n");
						}//输出grade 
						*/ 
						for(int x=1;x<=SIZEOFCHESS;x++)
							for(int y=1;y<=SIZEOFCHESS;y++)
								grade[x][y]=0;//grade清零
						if(win()==1)
						{
							SetConsoleCursorPosition(hOut3,crEnd3);
							printf("White win!");
							break;
						}
						else if(win()==-1)
						{
							SetConsoleCursorPosition(hOut3,crEnd3);
							printf("Black win!");
							break;
						}
						if(num==SIZEOFCHESS*SIZEOFCHESS)
						{
							SetConsoleCursorPosition(hOut3,crEnd3);
							printf("Draw!");
							break;
						}
					}
					else
					{
						SetConsoleCursorPosition(hOut3,crEnd3);
						printf("\n请在合适区域落子"); 
					}
				}
				else
				{
					SetConsoleCursorPosition(hOut3,crEnd3);
					printf("\n请在合适区域落子"); 
				}
			}
		}
	}
	char fname[50];
	memset(fname,'0',sizeof(fname));
	printf("\n若无需保存则直接关闭此窗口 \n保存棋局请输入此棋局要保存的文件名："); 
	scanf("%s",&fname);
	FILE*fp;
	fp=fopen(fname,"w+");
	if((fp=fopen(fname,"w+"))==NULL)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\ncan't open the file");
        exit(0);
    }
    for(int i=1;i<=num;i++)
		fwrite(&mem[i],sizeof(struct node),1,fp);
	fclose(fp);
	CloseHandle(hOut3);  // 关闭标准输出设备句柄  
	CloseHandle(hIn3);   // 关闭标准输入设备句柄
	return; 
}
void eve()
{
	HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE in=GetStdHandle(STD_INPUT_HANDLE);
	COORD crStart={0,0};
	int num=0;
	node mem[400];
	chess[(SIZEOFCHESS+1)/2][(SIZEOFCHESS+1)/2]=-1;
	remindx=(SIZEOFCHESS+1)/2;
	remindy=(SIZEOFCHESS+1)/2;
	num++;
	mem[num].row=remindy;
	mem[num].col=remindx;
	mem[num].po=-1;
	outputres();
	printf("\n\"steps:%d\"",num);//第一步 
	while(1)
	{
		score(p);
		find(p);
		num++;
		mem[num].row=remindy;
		mem[num].col=remindx;
		mem[num].po=1;
		SetConsoleCursorPosition(out,crStart);
		outputres();
		if(win()==1)
		{
			printf("White win!");
			break;
		}
		else if(win()==-1)
		{
			printf("Black win!");
			break;
		}
		if(num==SIZEOFCHESS*SIZEOFCHESS)
		{
			printf("Draw!");
			break;
		}		
		for(int x=1;x<=SIZEOFCHESS;x++)
			for(int y=1;y<=SIZEOFCHESS;y++)
				grade[x][y]=0;//grade清零
		score(-p);
		find(-p);
		num++;
		mem[num].row=remindy;
		mem[num].col=remindx;
		mem[num].po=-1;
		SetConsoleCursorPosition(out,crStart);
		outputres();
		for(int x=1;x<=SIZEOFCHESS;x++)
			for(int y=1;y<=SIZEOFCHESS;y++)
				grade[x][y]=0;//grade清零
		if(win()==1)
		{
			printf("White win!");
			break;
		}
		else if(win()==-1)
		{
			printf("Black win!");
			break;
		}
		if(num==SIZEOFCHESS*SIZEOFCHESS)
		{
			printf("Draw!");
			break;
		}
	}
	char fname[50];
	memset(fname,'0',sizeof(fname));
	printf("\n若无需保存则直接关闭此窗口 \n保存棋局请输入此棋局要保存的文件名："); 
	scanf("%s",&fname);
	FILE*fp;
	fp=fopen(fname,"w+");
	if((fp=fopen(fname,"w+"))==NULL)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\ncan't open the file");
        exit(0);
    }
    for(int i=1;i<=num;i++)
		fwrite(&mem[i],sizeof(struct node),1,fp);
	fclose(fp);
	return;
}
int getype(int x,int y,int i,int j,int k)
{
	switch(i)
	{
		/*6 7 8
		   \|/
		  5-.-1
		   /|\
		  4 3 2*/
		case 1:
			x=x+j;
			break;
		case 2:
			x=x+j;
			y=y+j;
			break;
		case 3:
			y=y+j;
			break;
		case 4:
			x=x-j;
			y=y+j;
			break;
		case 5:
			x=x-j;
			break;
		case 6:
			x=x-j;
			y=y-j;
			break;
		case 7:
			y=y-j;
			break;
		case 8:
			x=x+j;
			y=y-j;
			break;
	}
	if((x==0)||(y==0)||(x==SIZEOFCHESS+1)||(y==SIZEOFCHESS+1))return 2;
	else if((x<0)||(y<0)||(x>SIZEOFCHESS+1)||(y>SIZEOFCHESS+1))return 3;
	else return chess[x][y];
}
void score(int k)
{
	int l=k;
	int one=100000,two=50000,three=8000,four=3000,five=50;
	int gradeji,gradedui;
	for(int x=1;x<=SIZEOFCHESS;x++)
	{
		for(int y=1;y<=SIZEOFCHESS;y++)
		{
			if(chess[x][y]==0)
			{
				gradeji=0;
				gradedui=0;
				for(int i=1;i<=8;i++)
				{
					//01为棋子 _为参考点 -为空位 
					//双活2必堵? 己方双活2<对方活3<己方活3 同方双活2 = 双眠3 < 活3 
					if(getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==k&&getype(x,y,i,-3,l)==k&&getype(x,y,i,-4,l)==k&&getype(x,y,i,-5,l)==0)
					{
						gradeji+=one;//己方活4 _0000_
						break;
					}	
					if(getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==k&&getype(x,y,i,-3,l)==k&&getype(x,y,i,-4,l)==k&&(getype(x,y,i,-5,l)==-k||getype(x,y,i,-5,l)==2))
    	            {
						gradeji+=one;//己方冲4 _00001
						break;
					}
        	        if(getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==k&&getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k)
            	    {
						gradeji+=one/2;//己方冲4 00_00 会算2次 
						break;
					}
                	if(getype(x,y,i,-1,l)==k&&getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k)
                	{
						gradeji+=one;//己方冲4 0_000
						break;
					}
					if(getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==-k&&getype(x,y,i,-3,l)==-k&&getype(x,y,i,-4,l)==-k&&getype(x,y,i,-5,l)==0)
    	            	gradedui+=two;//对方活4 _0000_
        	        if(getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==-k&&getype(x,y,i,-3,l)==-k&&getype(x,y,i,-4,l)==-k&&(getype(x,y,i,-5,l)==k||getype(x,y,i,-5,l)==2))
            	    	gradedui+=two;//对方冲4 _00001
                	if(getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==-k&&getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k)
            	    	gradedui+=two/2;//对方冲4 00_00 会算2次 
                	if(getype(x,y,i,-1,l)==-k&&getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k)
                		gradedui+=two;//对方冲4 0_000
            		if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k&&getype(x,y,i,4,l)==0&&getype(x,y,i,-1,l)==0)
                		gradeji+=three;//己方活3 -_000_-
            	    if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==0&&getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==0)
                		gradeji+=three;//己方跳活3 -0_00- 换个参考点?
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k&&getype(x,y,i,4,l)==0&&getype(x,y,i,-1,l)==0)
                		gradedui+=three-1000;//对方活3 -_000_-
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==0&&getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==0)
                		gradedui+=three-1000;//对方跳活3 -0_00- 换个参考点?
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k&&(getype(x,y,i,4,l)==-k||getype(x,y,i,4,l)==2)&&getype(x,y,i,-1,l)==-0)
                		gradeji+=four;//己方眠3 1000_- 同等情况下己方分数应更高? 
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k&&getype(x,y,i,4,l)==k&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=four;//己方眠3 1000-_ 
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&(getype(x,y,i,3,l)==-k||getype(x,y,i,3,l)==2)&&getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==0)
                		gradeji+=four;//己方眠3 100_0-
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==k&&getype(x,y,i,4,l)==k&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=four;//己方眠3 100-0_
                	if(getype(x,y,i,1,l)==k&&(getype(x,y,i,2,l)==-k||getype(x,y,i,2,l)==2)&&getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==k&&getype(x,y,i,-3,l)==0)
                		gradeji+=four;//己方眠3 10_00-
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==k&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=four;//己方眠3 10-00_
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k&&getype(x,y,i,-1,l)==k)
                		gradeji+=four;//己方眠3 0_-00
					if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==k)
                		gradeji+=four;//己方眠3 0-_00
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==k&&getype(x,y,i,-1,l)==k)
                		gradeji+=four;//己方眠3 0_0_0
                	if((getype(x,y,i,-1,l)==-k||getype(x,y,i,-1,l)==2)&&getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k&&getype(x,y,i,4,l)==0&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=four;//己方眠3 1_000_1
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k&&(getype(x,y,i,4,l)==k||getype(x,y,i,4,l)==2)&&getype(x,y,i,-1,l)==0)
                		gradedui+=four-500;//对方眠3 1000_-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k&&getype(x,y,i,4,l)==-k&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=four-500;//对方眠3 1000-_ 
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&(getype(x,y,i,3,l)==k||getype(x,y,i,3,l)==2)&&getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==0)
                		gradedui+=four-500;//对方眠3 100_0-
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==-k&&getype(x,y,i,4,l)==-k&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=four-500;//对方眠3 100-0_
                	if(getype(x,y,i,1,l)==-k&&(getype(x,y,i,2,l)==k||getype(x,y,i,2,l)==2)&&getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==-k&&getype(x,y,i,-3,l)==0)
                		gradedui+=four-500;//对方眠3 10_00-
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==-k&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=four-500;//对方眠3 10-00_
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k&&getype(x,y,i,-1,l)==-k)
                		gradedui+=four-500;//对方眠3 0_-00
					if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==-k)
                		gradedui+=four-500;//对方眠3 0-_00
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==-k&&getype(x,y,i,-1,l)==-k)
            			gradedui+=four-500;//对方眠3 0_0_0
                	if((getype(x,y,i,-1,l)==k||getype(x,y,i,-1,l)==2)&&getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k&&getype(x,y,i,4,l)==0&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=four-500;//对方眠3 1_000_1
                	if(getype(x,y,i,-1,l)==0&&getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==0)
                		gradeji+=four;//己方活2 -_00_-
                	if(getype(x,y,i,-1,l)==0&&getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==k&&getype(x,y,i,4,l)==0&&getype(x,y,i,5,l)==0)
                		gradeji+=four;//己方活2 -_0-0_- 
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==0&&getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==0&&getype(x,y,i,-3,l)==0)
                		gradeji+=four/2;//己方活2 --0_0-- 会算2次 
                	/*if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==k&&getype(x,y,i,5,l)==0)
                		gradeji+=four;//己方活2 _0--0_*/
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==k&&getype(x,y,i,-3,l)==0)
                		gradeji+=four;//己方活2 -0__0-
                	if(getype(x,y,i,-1,l)==0&&getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==0)
                		gradedui+=four-500;//对方活2 -_00_-
                	if(getype(x,y,i,-1,l)==0&&getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==-k&&getype(x,y,i,4,l)==0&&getype(x,y,i,5,l)==0)
                		gradedui+=four-500;//对方活2 -_0-0_- 
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==0&&getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==0&&getype(x,y,i,-3,l)==0)
                		gradedui+=four/2-250;//对方活2 --0_0-- 会算2次 
                	/*if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==-k&&getype(x,y,i,5,l)==0)
                		gradedui+=four-500;//对方活2 _0--0_*/
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==-k&&getype(x,y,i,-3,l)==0)
                		gradedui+=four-500;//对方活2 -0__0-
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==k&&(getype(x,y,i,3,l)==-k||getype(x,y,i,3,l)==2)&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==0)
                		gradeji+=five;//己方眠2 100_--
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==k&&(getype(x,y,i,4,l)==-k||getype(x,y,i,4,l)==2)&&getype(x,y,i,-1,l)==0)
                		gradeji+=five;//己方眠2 100-_-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==k&&getype(x,y,i,4,l)==k&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=five;//己方眠2 100--_
                	if(getype(x,y,i,1,l)==k&&(getype(x,y,i,2,l)==-k||getype(x,y,i,2,l)==2)&&getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==0&&getype(x,y,i,-3,l)==0)
                		gradeji+=five;//己方眠2 10_0--
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==k&&(getype(x,y,i,4,l)==-k||getype(x,y,i,4,l)==2)&&getype(x,y,i,-1,l)==0)
                		gradeji+=five;//己方眠2 10-0_-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==k&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==k&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=five;//己方眠2 10-0-_
                	if(getype(x,y,i,1,l)==k&&(getype(x,y,i,2,l)==-k||getype(x,y,i,2,l)==2)&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==k&&getype(x,y,i,-3,l)==0)
                		gradeji+=five;//己方眠2 10_-0-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==k&&(getype(x,y,i,3,l)==-k||getype(x,y,i,3,l)==2)&&getype(x,y,i,-1,l)==k&&getype(x,y,i,-2,l)==0)
                		gradeji+=five;//己方眠2 10-_0-
                	if(getype(x,y,i,1,l)==k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==k&&(getype(x,y,i,5,l)==-k||getype(x,y,i,5,l)==2))
                		gradeji+=five;//己方眠2 10--0_
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==k&&getype(x,y,i,-1,l)==k)
                		gradeji+=five;//己方眠2 0_--0
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==k&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==k)
                		gradeji+=five/2;//己方眠2 0-_-0 会算两次 
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==-k&&(getype(x,y,i,3,l)==k||getype(x,y,i,3,l)==2)&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==0)
                		gradedui+=five;//对方眠2 100_--
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==-k&&(getype(x,y,i,4,l)==k||getype(x,y,i,4,l)==2)&&getype(x,y,i,-1,l)==0)
                		gradedui+=five;//对方眠2 100-_-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==-k&&getype(x,y,i,4,l)==-k&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=five;//对方眠2 100--_
                	if(getype(x,y,i,1,l)==-k&&(getype(x,y,i,2,l)==k||getype(x,y,i,2,l)==2)&&getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==0&&getype(x,y,i,-3,l)==0)
                		gradedui+=five;//对方眠2 10_0--
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==-k&&(getype(x,y,i,4,l)==k||getype(x,y,i,4,l)==2)&&getype(x,y,i,-1,l)==0)
                		gradedui+=five;//对方眠2 10-0_-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==-k&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==-k&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=five;//对方眠2 10-0-_
                	if(getype(x,y,i,1,l)==-k&&(getype(x,y,i,2,l)==k||getype(x,y,i,2,l)==2)&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==-k&&getype(x,y,i,-3,l)==0)
                		gradedui+=five;//对方眠2 10_-0-
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==-k&&(getype(x,y,i,3,l)==k||getype(x,y,i,3,l)==2)&&getype(x,y,i,-1,l)==-k&&getype(x,y,i,-2,l)==0)
                		gradedui+=five;//对方眠2 10-_0-
                	if(getype(x,y,i,1,l)==-k&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==0&&getype(x,y,i,4,l)==-k&&(getype(x,y,i,5,l)==k||getype(x,y,i,5,l)==2))
                		gradedui+=five;//对方眠2 10--0_
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==0&&getype(x,y,i,3,l)==-k&&getype(x,y,i,-1,l)==-k)
                		gradedui+=five;//对方眠2 0_--0
                	if(getype(x,y,i,1,l)==0&&getype(x,y,i,2,l)==-k&&getype(x,y,i,-1,l)==0&&getype(x,y,i,-2,l)==-k)
                		gradedui+=five/2;//对方眠2 0-_-0 会算两次 
                	if(getype(x,y,i,1,l)==k)
						gradeji++;
					if(getype(x,y,i,1,l)==-k)
						gradedui++;
				}
				grade[x][y]=gradeji>gradedui?gradeji:gradedui;
			}
		}
	}
}
void find(int k)
{
	int max=0;
	int c=0,r,grdmx[SIZEOFCHESS*SIZEOFCHESS][2];
	for(int i=1;i<=SIZEOFCHESS;i++)
		for(int j=1;j<=SIZEOFCHESS;j++)
			if(chess[i][j]==0)
				if(grade[i][j]>max)max=grade[i][j];
				
	for(int i=1;i<=SIZEOFCHESS;i++)
	{
		for(int j=1;j<=SIZEOFCHESS;j++)
		{
			if(chess[i][j]==0)
			{
				if(grade[i][j]==max)
				{
					c++;
					grdmx[c][0]=i;
					grdmx[c][1]=j;
				}
			}
		}
	}
	srand((unsigned)time(NULL));
	r=rand()%c+1;
	chess[grdmx[r][0]][grdmx[r][1]]=k;
	remindx=grdmx[r][1];
	remindy=grdmx[r][0];
}
void replay()
{
	printf("请输入要回放对局的文件名：");
	
	HANDLE out=GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE in=GetStdHandle(STD_INPUT_HANDLE);
	COORD crStart={0,0};
	
	char fname[50];
	scanf("%s",&fname);
	FILE*fp;
	fp=fopen(fname,"r+");
	if((fp=fopen(fname,"r+"))==NULL)
    {
        printf("\n\n\n\n\n\n\n\n\n\n\n\ncan't open the file");
        exit(0);
    }
	
	int cnt=0;
	while(fread(&mem,sizeof(struct node),1,fp)==1)
	{
		chess[mem.row][mem.col]=mem.po;
		cnt++;
		SetConsoleCursorPosition(out,crStart);
		outputres();
		printf("last coordinate:%d %d   \nsteps:%d  \n",mem.col,mem.row,cnt);
		if(win()==1)
		{
			printf("White win!");
			break;
		}
		else if(win()==-1)
		{
			printf("Black win!");
			break;
		}
		if(cnt==SIZEOFCHESS*SIZEOFCHESS)
		{
			printf("Draw!");
			break;
		}
		Sleep(300);
	}
	fclose(fp);
	return;
}

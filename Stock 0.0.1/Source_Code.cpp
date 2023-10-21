#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <thread>
#include <string.h>
#include <queue>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*
����

�ݵ�ü

�����

�ڵ���
����
ö��

���̿�

ȭ��

������

�������̸�Ʈ

��ǰ

��Ÿ

����ȭ��

*/
char news[2][1000]={"[�ܵ�]���ȣ ��û�̰� �ֽĽ���"};

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;

void click(int *xx, int *yy, int *lr)
{
    while (1)
    {
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // �ܼ�â �Է��� �޾Ƶ���.
        if (rec.EventType == MOUSE_EVENT) // ���콺 �̺�Ʈ�� ���
        {

            if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)  // ���� ��ư�� Ŭ���Ǿ��� ���
            {
                int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X�� �޾ƿ�
                int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y�� �޾ƿ�

                *xx=mouse_x; //x���� �ѱ�
                *yy=mouse_y; //y���� �ѱ�
                *lr=1; //���콺 Ŭ�����¸� �ѱ�

                break;
            }
            else if(rec.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)   // ���� ��ư�� Ŭ���Ǿ��� ���
            {
                int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X�� �޾ƿ�
                int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y�� �޾ƿ�

                *xx=mouse_x; //x���� �ѱ�
                *yy=mouse_y; //y���� �ѱ�
                *lr=2; //���콺 Ŭ�����¸� �ѱ�

                break;
            }
        }
    }
}

void color(int a) //������ ������ �� ����. a ���� 0~255
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void gotoxy(int x,int y) //�ܼ� ���� ��ǥ������ �̵�
{
    COORD pos= {x*2,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void cursorhide() //Ŀ���� ����� �Լ�
{
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void clear_all(void)
{
    int i,j;
    for(i = 0; i <= 100; i++)
    {
        for(j = 0; j<=100; j++)
        {
            cursorhide();
            gotoxy(j,i);
            printf("  ");
        }
    }
}

class types
{
public:
    char name[100];

    char stock_names[100][100];

    float prize[100];

    float before_prize[100];

    float bought_prize[100];

    int numbers[100] = {0,};

    int size;

    float c = 5.1;

    float best = 10;

    void change_prize(void)
    {
        int i,r;

        srand(time(NULL));

        for(i = 0; i < size; i++)
        {
            before_prize[i] = prize[i];

            r = rand()%101;

            prize[i] += (((float)r / 100) * best - c)/100*prize[i];
            if(prize[i]<50)
            {
                prize[i] = 50;
            }

            if(prize[i]<100&&c/best > 0.5)
            {
                srand(time(NULL));
                strcpy(news[1],news[0]);

                sprintf(news[0],"[����] %sȸ�� ������ �絵�� ���ɼ� �־�...                ",name);
                best = 8;
                c = 3.9;
            }


            if(prize[i]>750000&&c/best < 0.5)
            {

                srand(time(NULL));
                strcpy(news[1],news[0]);

                sprintf(news[0],"[����] %sȸ�� ������ �ް��� �����ȭ ����                  ",name);
                best = 10;
                c = 5.6;

            }

            if(prize[i]>1000000)
            {
                prize[i]=1000000;
            }

        }
    }

    float total()
    {
        int i;
        float sum1 = 0;
        for(i = 0;i < size;i++)
        {
            sum1 += growth(i);
        }
        return sum1/(float)size;
    }

    float growth(int num)
    {
        return (prize[num]-before_prize[num])/before_prize[num];
    }


};

types stocks[20];


void set_stock(void)
{
    strcpy(stocks[0].name,"����");
    strcpy(stocks[1].name,"���&IT");
    strcpy(stocks[2].name,"���̿�");
    strcpy(stocks[3].name,"�ڵ���");
    strcpy(stocks[4].name,"ö��");
    strcpy(stocks[5].name,"����");
    strcpy(stocks[6].name,"ȭ��");
    strcpy(stocks[7].name,"������");
    strcpy(stocks[8].name,"�������θ�Ʈ");
    strcpy(stocks[9].name,"��ǰ&���");
    strcpy(stocks[10].name,"����");
    strcpy(stocks[11].name,"�Ǽ�");

    strcpy(stocks[0].stock_names[0],"�ϴ�����");
    strcpy(stocks[0].stock_names[1],"������������");
    strcpy(stocks[0].stock_names[2],"�����̾���ũ");
    strcpy(stocks[0].stock_names[3],"������������");
    stocks[0].prize[0] = 30000;
    stocks[0].prize[1] = 14000;
    stocks[0].prize[2] = 25000;
    stocks[0].prize[3] = 20000;
    stocks[0].size = 4;

    strcpy(stocks[1].stock_names[0],"��������");
    strcpy(stocks[1].stock_names[1],"��������Ȧ�α׷�");
    strcpy(stocks[1].stock_names[2],"ǳ�����");
    strcpy(stocks[1].stock_names[3],"�����̾�����");
    strcpy(stocks[1].stock_names[4],"�����ݵ�ü");
    strcpy(stocks[1].stock_names[5],"������");
    strcpy(stocks[1].stock_names[6],"���۳����Ʈ");
    stocks[1].prize[0] = 15000;
    stocks[1].prize[1] = 30000;
    stocks[1].prize[2] = 25000;
    stocks[1].prize[3] = 31000;
    stocks[1].prize[4] = 29000;
    stocks[1].prize[5] = 17000;
    stocks[1].prize[6] = 17500;
    stocks[1].size = 7;

    strcpy(stocks[2].stock_names[0],"��������̿�");
    strcpy(stocks[2].stock_names[1],"������");
    strcpy(stocks[2].stock_names[2],"Ǯ�̹̾�");
    stocks[2].prize[0] = 17500;
    stocks[2].prize[1] = 30000;
    stocks[2].prize[2] = 25000;
    stocks[2].size = 3;

    strcpy(stocks[3].stock_names[0],"�õ����ڵ���");
    strcpy(stocks[3].stock_names[1],"�����̾��ڵ���");
    strcpy(stocks[3].stock_names[2],"�ٴ��ڵ���");
    strcpy(stocks[3].stock_names[3],"��������Ÿ�̾�");
    stocks[3].prize[0] = 18000;
    stocks[3].prize[1] = 20000;
    stocks[3].prize[2] = 25000;
    stocks[3].prize[3] = 15000;
    stocks[3].size = 4;

    strcpy(stocks[4].stock_names[0],"�ڵ�ȭ��ö");
    strcpy(stocks[4].stock_names[1],"�ٴ�����");
    strcpy(stocks[4].stock_names[2],"����������ƿ");
    strcpy(stocks[4].stock_names[3],"���ִ°�ö");
    stocks[4].prize[0] = 14000;
    stocks[4].prize[1] = 25000;
    stocks[4].prize[2] = 20000;
    stocks[4].prize[3] = 15500;
    stocks[4].size = 4;

    strcpy(stocks[5].stock_names[0],"�ڵ�ȭ����");
    strcpy(stocks[5].stock_names[1],"�õ��Ѽ���");
    strcpy(stocks[5].stock_names[2],"�����̾�����");
    strcpy(stocks[5].stock_names[3],"����������");
    stocks[5].prize[0] = 15000;
    stocks[5].prize[1] = 8000;
    stocks[5].prize[2] = 17000;
    stocks[5].prize[3] = 9000;
    stocks[5].size = 4;

    strcpy(stocks[6].stock_names[0],"�����̾�ȭ��");
    strcpy(stocks[6].stock_names[1],"�߼��ɹ���");
    strcpy(stocks[6].stock_names[2],"ơơ����ȭ��");
    strcpy(stocks[6].stock_names[3],"�߾Ͻż���");
    strcpy(stocks[6].stock_names[4],"���ڿ�ȭ��");
    stocks[6].prize[0] = 37500;
    stocks[6].prize[1] = 20000;
    stocks[6].prize[2] = 35000;
    stocks[6].prize[3] = 16500;
    stocks[6].prize[4] = 25000;
    stocks[6].size = 5;

    strcpy(stocks[7].stock_names[0],"�쿡�����ַ��");
    strcpy(stocks[7].stock_names[1],"��缱������");
    strcpy(stocks[7].stock_names[2],"����������������");
    strcpy(stocks[7].stock_names[3],"�������Ŀ�");
    strcpy(stocks[7].stock_names[4],"������ǳ��");
    stocks[7].prize[0] = 20000;
    stocks[7].prize[1] = 15000;
    stocks[7].prize[2] = 10000;
    stocks[7].prize[3] = 16500;
    stocks[7].prize[4] = 15500;
    stocks[7].size = 5;

    strcpy(stocks[8].stock_names[0],"�����̾�ENM");
    strcpy(stocks[8].stock_names[1],"�߼ҽ�Ʃ���");
    strcpy(stocks[8].stock_names[2],"��¿TV");
    strcpy(stocks[8].stock_names[3],"POP����");
    strcpy(stocks[8].stock_names[4],"���ڿ���ȹ");
    stocks[8].prize[0] = 20000;
    stocks[8].prize[1] = 11200;
    stocks[8].prize[2] = 12500;
    stocks[8].prize[3] = 16500;
    stocks[8].prize[4] = 14500;
    stocks[8].size = 5;

    strcpy(stocks[9].stock_names[0],"�����̾����");
    strcpy(stocks[9].stock_names[1],"�˸����");
    strcpy(stocks[9].stock_names[2],"����Ǵ�");
    strcpy(stocks[9].stock_names[3],"�Ĺ�����");
    strcpy(stocks[9].stock_names[4],"���ڿ����");
    strcpy(stocks[9].stock_names[5],"�α�츮��");
    strcpy(stocks[9].stock_names[6],"��ٶ���ǰ");
    strcpy(stocks[9].stock_names[7],"C�Ѹ���");
    strcpy(stocks[9].stock_names[8],"���ҽ�ǰ");
    strcpy(stocks[9].stock_names[9],"�õ��ѳ��۹�");
    stocks[9].prize[0] = 15000;
    stocks[9].prize[1] = 12200;
    stocks[9].prize[2] = 16000;
    stocks[9].prize[3] = 15000;
    stocks[9].prize[4] = 17000;
    stocks[9].prize[5] = 10000;
    stocks[9].prize[6] = 16800;
    stocks[9].prize[7] = 22222;
    stocks[9].prize[8] = 10000;
    stocks[9].prize[9] = 18000;
    stocks[9].size = 10;

    strcpy(stocks[10].stock_names[0],"�����̾��Ǿ�");
    strcpy(stocks[10].stock_names[1],"������������");
    strcpy(stocks[10].stock_names[2],"��¿�˾�");
    strcpy(stocks[10].stock_names[3],"�ٴ�����");
    strcpy(stocks[10].stock_names[4],"��缱��ǰ");
    stocks[10].prize[0] = 20000;
    stocks[10].prize[1] = 18000;
    stocks[10].prize[2] = 14000;
    stocks[10].prize[3] = 16500;
    stocks[10].prize[4] = 25000;
    stocks[10].size = 5;

    strcpy(stocks[11].stock_names[0],"�ٴ�Ǽ�");
    strcpy(stocks[11].stock_names[1],"�����̾��Ǽ�");
    strcpy(stocks[11].stock_names[2],"�ڵ�ȭ����");
    strcpy(stocks[11].stock_names[3],"���Ǽ�");
    strcpy(stocks[11].stock_names[4],"�õ��ѰǼ�");
    stocks[11].prize[0] = 25000;
    stocks[11].prize[1] = 20000;
    stocks[11].prize[2] = 30000;
    stocks[11].prize[3] = 20000;
    stocks[11].prize[4] = 25000;
    stocks[11].size = 5;
}

void chang_prize()
{
    int i;

    for(i = 0;i < 12;i++)
    {
        stocks[i].change_prize();
    }
}

void events(void)
{
    srand(time(NULL));

    int r;
    int temp1;
    int temp;
    r = rand()%40;

    switch(r)
    {
    case 0:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        sprintf(news[0],"[��Ȱ&��ȭ] %c�� ��ȭ��ǰ�� ������ �ص��� Ȯ��Ǿ�...            ",rand()%26+'A');
        stocks[8].c -= 0.2;
        stocks[1].c -= 0.05;
        break;
    case 1:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[�Ӻ�] %s ȸ�� ȸ���� �������� �յ��� \"���\"...            ",stocks[temp].name);
        stocks[temp].c += 0.3;
        break;

    case 2:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[����]\"�� �ֽ� �� ������\" ��ν��� �ֽİ���                      ");
        stocks[temp].best += 0.3;
        stocks[temp].c -= 0.1;
        break;


    case 3:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[����]\"����ȭ�� ��ġ ����\" ���� �λ�� \"����\"...           ");
        stocks[1].best += 0.3;
        stocks[1].c += 0.3;
        break;

    case 4:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[IT/����] NFT ������ �Ϸ翡 1�� ����.                    ");

        stocks[1].c -= 0.3;
        break;

    case 5:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[��Ȱ&��ȭ] ���� �������� �̵���� ��ģ��...                    ");
        stocks[1].c += 0.05;
        stocks[8].c += 0.3;
        break;
    case 6:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[����] %s ȸ���� ���� 10�� �����ؾ�...                    ",stocks[temp].name);

        stocks[temp].best -= 0.3;
        break;

    case 7:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[����]�� ������ ����ȸ�翡�Դ� ��ȭ����...                   ");

        stocks[2].c -= 0.3;
        stocks[10].c -= 0.3;
        break;

    case 8:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[����]�ֱ� �� ������ ����ȸ�縸 ��θ��� �Ѵ�...                   ");

        stocks[2].c += 0.3;
        stocks[10].c += 0.3;
        break;
    case 9:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        temp1 = rand()%2;
        sprintf(news[0],"[��ġ] %s ��� \'%s��\' ���� �����μ� ����                      ",stocks[temp].name,temp1==0?"��":"��");

        stocks[temp].c -= 0.4;
        break;
    case 10:

        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        temp1 = rand()%2;
        sprintf(news[0],"[����] �⸧�� ���� ����... ������ \"������ �� ����\"...                    ");
        stocks[4].c += 0.05;
        stocks[5].c += 0.3;
        stocks[1].c += 0.05;
        stocks[3].c += 0.3;
        stocks[6].c += 0.2;
        stocks[7].c -= 0.05;
        break;
    case 11:

        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        temp1 = rand()%2;
        sprintf(news[0],"[��Ȱ&��ȭ]�����³�ȭ�� ���� ��� ����                     ");

        stocks[9].c += 0.25;
        stocks[7].c += 0.15;
        break;

    default:
        break;
    }



}

int main()
{
    float money = 500000;

    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT);

    DWORD consoleModePrev;
    HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(handle, &consoleModePrev);
    SetConsoleMode(handle, consoleModePrev & ~ENABLE_QUICK_EDIT_MODE);

    set_stock();

    int window = 0;

    int x,y,l;
    int i;



    while(1)
    {
        Sleep(1);
        clear_all();

        gotoxy(0,0);

        if(window == 0)
        {
            while(1)
            {
                gotoxy(0,0);
                printf("����");
                gotoxy(0,1);
                printf(news[0]);
                gotoxy(0,2);
                printf(news[1]);
                events();

                chang_prize();
                gotoxy(0,3);
                printf("������ : %.2f��           ",money);

                gotoxy(0,4);
                printf("����");

                for(i = 0; i < 12; i++)
                {
                    gotoxy(1,i+5);
                    printf(stocks[i].name);
                    gotoxy(20,i+5);
                    if(stocks[i].total()<0)
                    {
                        color(9);
                        printf("(");
                    }
                    else if(stocks[i].total()>0)
                    {
                        color(12);
                        printf("(");
                        printf("+");
                    }
                    else{

                        color(8);
                    printf("(");
                    }
                    printf("%.1f%%)         ",stocks[i].total()*100);
                    color(7);

                    cursorhide();
                }
                click(&x,&y,&l);

                if(y >= 5&&y<=16)
                {
                    if(x>=2&&x<=strlen(stocks[y-5].name))
                    {
                        window = y;
                        break;

                    }
                }
            }




        }
        else if(window>=5&&window<=16)
        {
            while(1)
            {
                gotoxy(0,0);
                printf("����");
                gotoxy(0,1);
                printf(news[0]);
                gotoxy(0,2);
                printf(news[1]);
                events();

                chang_prize();
                gotoxy(0,3);
                printf("������ : %.2f��         ",money);
                gotoxy(0,4);
                printf(stocks[window-5].name);
                gotoxy(12,4);
                printf("���ư���");
                for(i = 0; i < stocks[window-5].size;i++)
                {
                    gotoxy(1,i+5);
                    printf(stocks[window-5].stock_names[i]);
                    gotoxy(11,i+5);
                    printf("%.2f��          ",stocks[window-5].prize[i]);
                    gotoxy(21,i+5);

                    if(stocks[window-5].growth(i)<0)
                    {
                        color(9);
                        printf("(");
                    }
                    else if(stocks[window-5].growth(i)>0)
                    {
                        color(12);
                        printf("(");
                        printf("+");
                    }
                    else{

                        color(8);
                    printf("(");
                    }
                    printf("%.1f%%)         ",stocks[window-5].growth(i)*100);
                    color(7);

                    gotoxy(30,i+5);
                    if(money >= stocks[window-5].prize[i])
                    {
                        color(15);
                    }
                    else
                    {
                        color(8);
                    }

                    printf("[�ż�]");

                    gotoxy(35,i+5);

                    if(stocks[window-5].numbers[i]!=0)
                    {
                        color(15);
                    }
                    else
                    {
                        color(8);
                    }

                    printf("[�ŵ�]");

                    color(7);

                    gotoxy(40,i+5);
                    printf("����:%d     ",stocks[window-5].numbers[i]);
                    gotoxy(45,i+5);
                    printf("���:%.2f��        ",stocks[window-5].bought_prize[i]);

                }

                click(&x,&y,&l);

                if(y == 4&&x>=24&&x<=32)
                {
                    window = 0;
                    break;
                }
                if(y >= 5&&y <= stocks[window-5].size+4)
                {
                    if(x>=60&&x<=66)
                    {
                        if(stocks[window-5].prize[y-5]<=money)
                        {
                            money-=stocks[window-5].prize[y-5];

                            stocks[window-5].bought_prize[y-5]=
                            (stocks[window-5].bought_prize[y-5]*
                            (float)stocks[window-5].numbers[y-5] +
                            stocks[window-5].prize[y-5])/(float)(stocks[window-5].numbers[y-5]+1);

                            stocks[window-5].numbers[y-5]++;
                        }
                    }

                    if(x>=70&&x<=76)
                    {
                        if(stocks[window-5].numbers[y-5]!=0)
                        {
                            money+=stocks[window-5].prize[y-5];
                            stocks[window-5].numbers[y-5]--;
                            if(stocks[window-5].numbers[y-5]==0)
                            {
                                stocks[window-5].bought_prize[y-5]=0;
                            }
                        }
                    }
                }


            }

        }
        gotoxy(0,20);
        printf("%d %d",x,y);
    }


    return 0;
}

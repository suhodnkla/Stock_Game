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
금융

반도체

경공업

자동차
조선
철강

바이오

화학

에너지

엔터테이먼트

식품

기타

가상화폐

*/
char news[2][1000]={"[단독]대부호 멍청이가 주식시작"};

INPUT_RECORD rec;
DWORD dwNOER;
HANDLE CIN = 0;

void click(int *xx, int *yy, int *lr)
{
    while (1)
    {
        ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rec, 1, &dwNOER); // 콘솔창 입력을 받아들임.
        if (rec.EventType == MOUSE_EVENT) // 마우스 이벤트일 경우
        {

            if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)  // 좌측 버튼이 클릭되었을 경우
            {
                int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X값 받아옴
                int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y값 받아옴

                *xx=mouse_x; //x값을 넘김
                *yy=mouse_y; //y값을 넘김
                *lr=1; //마우스 클릭상태를 넘김

                break;
            }
            else if(rec.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)   // 우측 버튼이 클릭되었을 경우
            {
                int mouse_x = rec.Event.MouseEvent.dwMousePosition.X; // X값 받아옴
                int mouse_y = rec.Event.MouseEvent.dwMousePosition.Y; // Y값 받아옴

                *xx=mouse_x; //x값을 넘김
                *yy=mouse_y; //y값을 넘김
                *lr=2; //마우스 클릭상태를 넘김

                break;
            }
        }
    }
}

void color(int a) //색상을 지정할 수 있음. a 값은 0~255
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a);
}

void gotoxy(int x,int y) //콘솔 내의 좌표값으로 이동
{
    COORD pos= {x*2,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void cursorhide() //커서를 숨기는 함수
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

                sprintf(news[0],"[경제] %s회사 앞으로 재도약 가능성 있어...                ",name);
                best = 8;
                c = 3.9;
            }


            if(prize[i]>750000&&c/best < 0.5)
            {

                srand(time(NULL));
                strcpy(news[1],news[0]);

                sprintf(news[0],"[경제] %s회사 앞으로 급격한 성장둔화 예상                  ",name);
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
    strcpy(stocks[0].name,"금융");
    strcpy(stocks[1].name,"통신&IT");
    strcpy(stocks[2].name,"바이오");
    strcpy(stocks[3].name,"자동차");
    strcpy(stocks[4].name,"철강");
    strcpy(stocks[5].name,"조선");
    strcpy(stocks[6].name,"화학");
    strcpy(stocks[7].name,"에너지");
    strcpy(stocks[8].name,"엔터테인먼트");
    strcpy(stocks[9].name,"식품&농업");
    strcpy(stocks[10].name,"제약");
    strcpy(stocks[11].name,"건설");

    strcpy(stocks[0].stock_names[0],"하늘은행");
    strcpy(stocks[0].stock_names[1],"가뭄금융지주");
    strcpy(stocks[0].stock_names[2],"프리미엄뱅크");
    strcpy(stocks[0].stock_names[3],"오리지날금융");
    stocks[0].prize[0] = 30000;
    stocks[0].prize[1] = 14000;
    stocks[0].prize[2] = 25000;
    stocks[0].prize[3] = 20000;
    stocks[0].size = 4;

    strcpy(stocks[1].stock_names[0],"역학전자");
    strcpy(stocks[1].stock_names[1],"오리지날홀로그램");
    strcpy(stocks[1].stock_names[2],"풍문통신");
    strcpy(stocks[1].stock_names[3],"프리미엄전자");
    strcpy(stocks[1].stock_names[4],"조개반도체");
    strcpy(stocks[1].stock_names[5],"반전하");
    strcpy(stocks[1].stock_names[6],"소작농소프트");
    stocks[1].prize[0] = 15000;
    stocks[1].prize[1] = 30000;
    stocks[1].prize[2] = 25000;
    stocks[1].prize[3] = 31000;
    stocks[1].prize[4] = 29000;
    stocks[1].prize[5] = 17000;
    stocks[1].prize[6] = 17500;
    stocks[1].size = 7;

    strcpy(stocks[2].stock_names[0],"샐러드바이오");
    strcpy(stocks[2].stock_names[1],"고래종묘");
    strcpy(stocks[2].stock_names[2],"풀이미엄");
    stocks[2].prize[0] = 17500;
    stocks[2].prize[1] = 30000;
    stocks[2].prize[2] = 25000;
    stocks[2].size = 3;

    strcpy(stocks[3].stock_names[0],"올드한자동차");
    strcpy(stocks[3].stock_names[1],"프리미엄자동차");
    strcpy(stocks[3].stock_names[2],"근대자동차");
    strcpy(stocks[3].stock_names[3],"오리지날타이어");
    stocks[3].prize[0] = 18000;
    stocks[3].prize[1] = 20000;
    stocks[3].prize[2] = 25000;
    stocks[3].prize[3] = 15000;
    stocks[3].size = 4;

    strcpy(stocks[4].stock_names[0],"자동화제철");
    strcpy(stocks[4].stock_names[1],"근대제강");
    strcpy(stocks[4].stock_names[2],"오리지날스틸");
    strcpy(stocks[4].stock_names[3],"맛있는강철");
    stocks[4].prize[0] = 14000;
    stocks[4].prize[1] = 25000;
    stocks[4].prize[2] = 20000;
    stocks[4].prize[3] = 15500;
    stocks[4].size = 4;

    strcpy(stocks[5].stock_names[0],"자동화조선");
    strcpy(stocks[5].stock_names[1],"올드한선박");
    strcpy(stocks[5].stock_names[2],"프리미엄조선");
    strcpy(stocks[5].stock_names[3],"조선의조선");
    stocks[5].prize[0] = 15000;
    stocks[5].prize[1] = 8000;
    stocks[5].prize[2] = 17000;
    stocks[5].prize[3] = 9000;
    stocks[5].size = 4;

    strcpy(stocks[6].stock_names[0],"프리미엄화학");
    strcpy(stocks[6].stock_names[1],"중세케미컬");
    strcpy(stocks[6].stock_names[2],"퉤퉤정밀화학");
    strcpy(stocks[6].stock_names[3],"발암신소재");
    strcpy(stocks[6].stock_names[4],"비자연화학");
    stocks[6].prize[0] = 37500;
    stocks[6].prize[1] = 20000;
    stocks[6].prize[2] = 35000;
    stocks[6].prize[3] = 16500;
    stocks[6].prize[4] = 25000;
    stocks[6].size = 5;

    strcpy(stocks[7].stock_names[0],"흠에너지솔루션");
    strcpy(stocks[7].stock_names[1],"방사선에너지");
    strcpy(stocks[7].stock_names[2],"이이퀄엠씨스퀘어");
    strcpy(stocks[7].stock_names[3],"오리진파워");
    strcpy(stocks[7].stock_names[4],"레쿠쟈풍력");
    stocks[7].prize[0] = 20000;
    stocks[7].prize[1] = 15000;
    stocks[7].prize[2] = 10000;
    stocks[7].prize[3] = 16500;
    stocks[7].prize[4] = 15500;
    stocks[7].size = 5;

    strcpy(stocks[8].stock_names[0],"프리미엄ENM");
    strcpy(stocks[8].stock_names[1],"중소스튜디오");
    strcpy(stocks[8].stock_names[2],"어쩔TV");
    strcpy(stocks[8].stock_names[3],"POP극장");
    strcpy(stocks[8].stock_names[4],"비자연기획");
    stocks[8].prize[0] = 20000;
    stocks[8].prize[1] = 11200;
    stocks[8].prize[2] = 12500;
    stocks[8].prize[3] = 16500;
    stocks[8].prize[4] = 14500;
    stocks[8].size = 5;

    strcpy(stocks[9].stock_names[0],"프리미엄재배");
    strcpy(stocks[9].stock_names[1],"똥맛비료");
    strcpy(stocks[9].stock_names[2],"농사의덕");
    strcpy(stocks[9].stock_names[3],"식물극장");
    strcpy(stocks[9].stock_names[4],"비자연농업");
    strcpy(stocks[9].stock_names[5],"인기우리쌀");
    strcpy(stocks[9].stock_names[6],"비바라기식품");
    strcpy(stocks[9].stock_names[7],"C뿌리기");
    strcpy(stocks[9].stock_names[8],"질소식품");
    strcpy(stocks[9].stock_names[9],"올드한농작물");
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

    strcpy(stocks[10].stock_names[0],"프리미엄의약");
    strcpy(stocks[10].stock_names[1],"오리지날제약");
    strcpy(stocks[10].stock_names[2],"어쩔알약");
    strcpy(stocks[10].stock_names[3],"근대제약");
    strcpy(stocks[10].stock_names[4],"방사선약품");
    stocks[10].prize[0] = 20000;
    stocks[10].prize[1] = 18000;
    stocks[10].prize[2] = 14000;
    stocks[10].prize[3] = 16500;
    stocks[10].prize[4] = 25000;
    stocks[10].size = 5;

    strcpy(stocks[11].stock_names[0],"근대건설");
    strcpy(stocks[11].stock_names[1],"프리미엄건설");
    strcpy(stocks[11].stock_names[2],"자동화건축");
    strcpy(stocks[11].stock_names[3],"방방건설");
    strcpy(stocks[11].stock_names[4],"올드한건설");
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
        sprintf(news[0],"[생활&문화] %c사 문화상품권 사용범위 극도로 확대되어...            ",rand()%26+'A');
        stocks[8].c -= 0.2;
        stocks[1].c -= 0.05;
        break;
    case 1:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[속보] %s 회사 회사장 뇌물혐의 잇따라 \"충격\"...            ",stocks[temp].name);
        stocks[temp].c += 0.3;
        break;

    case 2:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[경제]\"이 주식 꼭 오른다\" 경민쌤의 주식강의                      ");
        stocks[temp].best += 0.3;
        stocks[temp].c -= 0.1;
        break;


    case 3:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[세계]\"가상화폐 가치 없다\" 세계 인사들 \"폭언\"...           ");
        stocks[1].best += 0.3;
        stocks[1].c += 0.3;
        break;

    case 4:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[IT/과학] NFT 예술가 하루에 1억 번다.                    ");

        stocks[1].c -= 0.3;
        break;

    case 5:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[생활&문화] 과한 국가규제 미디어산업 해친다...                    ");
        stocks[1].c += 0.05;
        stocks[8].c += 0.3;
        break;
    case 6:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[경제] %s 회사장 향후 10년 생각해야...                    ",stocks[temp].name);

        stocks[temp].best -= 0.3;
        break;

    case 7:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[경제]이 전염병 제약회사에게는 전화위복...                   ");

        stocks[2].c -= 0.3;
        stocks[10].c -= 0.3;
        break;

    case 8:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        sprintf(news[0],"[경제]최근 이 전염병 제약회사만 배부르게 한다...                   ");

        stocks[2].c += 0.3;
        stocks[10].c += 0.3;
        break;
    case 9:
        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        temp1 = rand()%2;
        sprintf(news[0],"[정치] %s 산업 \'%s당\' 경제 과제로서 지원                      ",stocks[temp].name,temp1==0?"야":"여");

        stocks[temp].c -= 0.4;
        break;
    case 10:

        srand(time(NULL));
        strcpy(news[1],news[0]);
        temp = rand()%12;
        temp1 = rand()%2;
        sprintf(news[0],"[경제] 기름값 폭등 예상... 전문가 \"예측할 수 없어\"...                    ");
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
        sprintf(news[0],"[생활&문화]지구온난화로 올해 흉년 예상                     ");

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
                printf("뉴스");
                gotoxy(0,1);
                printf(news[0]);
                gotoxy(0,2);
                printf(news[1]);
                events();

                chang_prize();
                gotoxy(0,3);
                printf("소지금 : %.2f원           ",money);

                gotoxy(0,4);
                printf("종목");

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
                printf("뉴스");
                gotoxy(0,1);
                printf(news[0]);
                gotoxy(0,2);
                printf(news[1]);
                events();

                chang_prize();
                gotoxy(0,3);
                printf("소지금 : %.2f원         ",money);
                gotoxy(0,4);
                printf(stocks[window-5].name);
                gotoxy(12,4);
                printf("돌아가기");
                for(i = 0; i < stocks[window-5].size;i++)
                {
                    gotoxy(1,i+5);
                    printf(stocks[window-5].stock_names[i]);
                    gotoxy(11,i+5);
                    printf("%.2f원          ",stocks[window-5].prize[i]);
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

                    printf("[매수]");

                    gotoxy(35,i+5);

                    if(stocks[window-5].numbers[i]!=0)
                    {
                        color(15);
                    }
                    else
                    {
                        color(8);
                    }

                    printf("[매도]");

                    color(7);

                    gotoxy(40,i+5);
                    printf("수량:%d     ",stocks[window-5].numbers[i]);
                    gotoxy(45,i+5);
                    printf("평균:%.2f원        ",stocks[window-5].bought_prize[i]);

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

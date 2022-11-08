#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
//가로 11칸   //벽 22
int x = 7, y = 3;
int current_block_index = -1, next_block_index = -1;
int block_direction = -1;
int isnext = 1;
int g_oflag = 1;
typedef enum
{
    NOCURSOR, SOLIDCURSOR, NORMALCURSOR
}CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 
int block[7][4][4][4] =   // 블럭갯수, 방향변화횟수, (블럭 칸)  t k j i
{
   {
      {
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0}
      },
      {
         {0,0,0,0},
         {0,0,0,0},
         {1,1,1,1},
         {0,0,0,0}
      },
      {
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0},
         {0,1,0,0}
      },
      {
         {0,0,0,0},
         {0,0,0,0},
         {1,1,1,1},
         {0,0,0,0}
      }
   },  //직선도형  0
   {
      {
         {0,0,0,0},
         {1,0,0,0},
         {1,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {1,1,0,0},
         {1,0,0,0},
         {1,0,0,0}
      },
      {
         {0,0,0,0},
         {1,1,1,0},
         {0,0,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,0,1,0},
         {0,0,1,0},
         {0,1,1,0}
      }
   },   //ㄴ 도형  1
   {
      {
         {0,0,0,0},
         {0,0,1,0},
         {1,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,0,0},
         {0,1,0,0},
         {0,1,1,0}
      },
      {
         {0,0,0,0},
         {1,1,1,0},
         {1,0,0,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,1,0},
         {0,0,1,0},
         {0,0,1,0}
      }   //역 ㄴ 도형 2
   },
   {
      {
         {0,0,0,0},
         {0,1,1,0},
         {1,1,0,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {1,0,0,0},
         {1,1,0,0},
         {0,1,0,0}
      },
      {
         {0,0,0,0},
         {0,1,1,0},
         {1,1,0,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {1,0,0,0},
         {1,1,0,0},
         {0,1,0,0}
      }
   },   // Z 도형 3
   {
      {
         {0,0,0,0},
         {1,1,0,0},
         {0,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,0,0},
         {1,1,0,0},
         {1,0,0,0}
      },
      {
         {0,0,0,0},
         {1,1,0,0},
         {0,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,0,0},
         {1,1,0,0},
         {1,0,0,0}
      }   //역 Z 도형 4
   },
   {
      {
         {0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,1,0},
         {0,1,1,0},
         {0,0,0,0}
      }
   },  // ㅁ 도형 5
   {
      {
         {0,0,0,0},
         {0,1,0,0},
         {1,1,1,0},
         {0,0,0,0}
      },
      {
         {0,0,0,0},
         {0,1,0,0},
         {0,1,1,0},
         {0,1,0,0}
      },
      {
         {0,0,0,0},
         {0,0,0,0},
         {1,1,1,0},
         {0,1,0,0}
      },
      {
         {0,0,0,0},
         {0,1,0,0},
         {1,1,0,0},
         {0,1,0,0}
      }   //ㅗ 도형 6
   }
};
int made_wall[22][11] =    //1~9
{
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1}
};
void gotoxy(int x, int y);
void move_block();
void setcursortype(CURSOR_TYPE c);
void show_wall();
void print_block();
void random_block();
int limit_block(int x, int y);
void solidify_block();
int check_crash(int x, int y);
void clean_block();
int trans_block(int check_trans_block);
int limit_line();
void down_auto();
void del_bottom_line();
void down_block(int line_count);
void show_next_block();
void restart_game();
int main()
{
    setcursortype(NOCURSOR);
    while (1)
    {
        if (g_oflag == 0)  //게임오버
        {
            restart_game();
        }
        show_wall();
        move_block();
        random_block();
        print_block();
        show_next_block();
        down_auto();
        Sleep(500);
    }
}
void down_auto()  //블럭 자동 하행
{   
    if (limit_block(x, y + 1) == 1)
    {
        clean_block();
        gotoxy(x, y);
        y++;
        random_block();
        print_block();
    }
}
void random_block()   //블럭 모양 선택
{
    srand(time(NULL));
    if (isnext == 1)
    {
        if (next_block_index != -1)
        {
            current_block_index = next_block_index;
        }
        else
        {
            current_block_index = rand() % 7;
        }
        next_block_index = rand() % 7;
        block_direction = 0;
        isnext = 0;
        
    }
}
void setcursortype(CURSOR_TYPE c)  //커서숨기는 함수
{
    CONSOLE_CURSOR_INFO CurInfo;
    switch (c)
    {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle
    (STD_OUTPUT_HANDLE), &CurInfo);
}
void show_wall()   //벽 출력
{
    int wallx = 3, wally = 3;   //벽 위치
    for (int j = 0; j < 22; j++)
    {
        for (int i = 0; i < 11; i++)
        {
            if (j == 3 && i == 1)
            {
                gotoxy(wallx + i, wally + j);
                printf(". . . . . . . . . ");
            }
            else if (made_wall[j][i] == 1)
            {
                gotoxy(wallx + i, wally + j);
                if ((j == 21 || i == 0 || i == 10))   //바닥 좌측 우측
                {
                    printf("▦");
                }
                else
                {
                    printf("■");
                }
            }
            else if (j != 3 && made_wall[j][i] == 0)
            { 
                gotoxy(wallx + i, wally + j);
                printf("  ");
            }
        }
    }
}
int trans_block(int check_trans_block)   //블럭 방향전환
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][check_trans_block][j][i] == 1 && made_wall[y - 3 + j][x - 3 + i] == 1)
            {
                return 0;  ///못 돌림
            }
        }
    }
    return 1;
}
int limit_line()   //블럭 상한선 제한, 게임오버
{
    for (int i = 1; i < 10; i++)
    {
        if (made_wall[3][i] == 1)
        {
            printf("game over!");
            g_oflag = 0;
            return 1;
        }
    }
}
void restart_game()  
{
    system("cls");
    for (int i = 0; i < 21; i++)
    {
        for (int j = 1; j < 10; j++)
        {
            made_wall[i][j] = 0;
        }
    }
    g_oflag = 1;
}
int limit_block(int modi_x, int modi_y)   //블럭 충돌 확인 (왼쪽, 오른쪽, 밑으로 이동할 수 있는가?)
{
    int index_x = modi_x - 3, index_y = modi_y - 3;     // 블록의 좌표를 index에 맞게 바꾼 것
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][block_direction][j][i] == 1 && made_wall[index_y + j][index_x + i] == 1) // 못 갈 때
            {
                check_crash(x, y + 1);
                return 0;
            }
        }
    }
    return 1;   // 갈 수 있을 때
}
int check_crash(int bottom_x, int bottom_y)   // 더 이상 블록을 움직일 수 없을 때 == 아래가 막혔을 때
{
    int index_x = bottom_x - 3, index_y = bottom_y - 3;
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][block_direction][j][i] == 1 && made_wall[index_y + j][index_x + i])
            {
                solidify_block();
                return 0;
            }
        }
    }
    return 1;
}
void solidify_block()   //블럭 굳히기
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][block_direction][j][i] == 1)
            {
                made_wall[y + j - 3][x + i - 3] = 1;
            }
        }
    }
    isnext = 1;
    x = 7, y = 3;
    limit_line();
    del_bottom_line();
}
void del_bottom_line()  //완성된 줄 지우기
{
    int count = 0;
    int line_count = 0;
    for (int j = 4; j < 21; j++)
    {
        count = 0;
        for (int i = 1; i < 10; i++)
        {
            if (made_wall[j][i] == 1)
            {
                count++;
            }
        }
        if (count == 9)
        {
            line_count = j;
            for (int i = 1; i < 10; i++)
            {
                made_wall[j][i] = 0;
                gotoxy(3 + i, 3 + j);
                printf("  ");
            }
            down_block(line_count);
        }
    }
}
void down_block(int line_count)  //블럭 내리기 (줄내리기)
{
    int wallx = 3, wally = 3;
    for (int j = line_count; j > 3; j--)
    {
        for (int i = 1; i < 10; i++)
        {
            made_wall[j][i] = made_wall[j - 1][i];
        }
    }
}
void print_block()  //블럭 출력
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {

            if (block[current_block_index][block_direction][i][j] == 1)
            {
                gotoxy(x + j, y + i);
                printf("□");
            }
        }
    }
}
void print_next_block()  //다음 블럭 보여주기
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[next_block_index][0][i][j] == 1)
            {
                gotoxy(17 + j, 6 + i);
                printf("□");
            }
        }
    }
}
void show_next_block()   //다음 블럭 보여주기
{
    gotoxy(15, 5);
    printf("+-  N E X T  -+");
    gotoxy(15, 6);
    printf("|             |");
    gotoxy(15, 7);
    printf("|             |");
    gotoxy(15, 8);
    printf("|             |");
    gotoxy(15, 9);
    printf("|             |");
    gotoxy(15, 10);
    printf("+-- -  -  - --+");
    print_next_block();
}
void clean_block()   //블럭 잔상 지우기
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][block_direction][i][j] == 1)
            {
                gotoxy(x + j, y + i);
                printf("  ");
            }
        }
    }
}
void move_block()   //블럭 움직이기
{
    char move_key;
    if (_kbhit())
    {
        move_key = _getch();
        switch (move_key)
        {
        case 32:   //블럭 떨구기
            while (limit_block(x, y + 1) == 1)
            {
                y++;
            }
            show_wall();
            break;
        case'w':case'W':  //블럭 방향 바꾸기
            if (block_direction == 3)
            {
                if (trans_block(block_direction - 3) == 1)
                {
                    clean_block();
                    block_direction = 0;
                }
            }
            else if (block_direction < 3)
            {
                if (trans_block(block_direction + 1) == 1)
                {
                    clean_block();
                    block_direction++;
                }
            }
            break;
        case 'a':case'A':
            if (limit_block(x - 1, y) == 1)
            {
                clean_block();
                x--;
            }
            break;
        case's':case'S':
            if (limit_block(x, y + 1) == 1)
            {
                clean_block();
                y++;
            }
            break;
        case'd':case'D':
            if (limit_block(x + 1, y) == 1)
            {
                clean_block();
                x++;
            }
            break;
        }
    }
    while (_kbhit())
    {
        _getch();
    }
}
void gotoxy(int x, int y)
{
    COORD pos = { (short)2 * (short)x,(short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
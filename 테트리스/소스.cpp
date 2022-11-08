#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
//���� 11ĭ   //�� 22
int x = 7, y = 3;
int current_block_index = -1, next_block_index = -1;
int block_direction = -1;
int isnext = 1;
int g_oflag = 1;
typedef enum
{
    NOCURSOR, SOLIDCURSOR, NORMALCURSOR
}CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 
int block[7][4][4][4] =   // ������, ���⺯ȭȽ��, (�� ĭ)  t k j i
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
   },  //��������  0
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
   },   //�� ����  1
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
      }   //�� �� ���� 2
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
   },   // Z ���� 3
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
      }   //�� Z ���� 4
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
   },  // �� ���� 5
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
      }   //�� ���� 6
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
        if (g_oflag == 0)  //���ӿ���
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
void down_auto()  //�� �ڵ� ����
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
void random_block()   //�� ��� ����
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
void setcursortype(CURSOR_TYPE c)  //Ŀ������� �Լ�
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
void show_wall()   //�� ���
{
    int wallx = 3, wally = 3;   //�� ��ġ
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
                if ((j == 21 || i == 0 || i == 10))   //�ٴ� ���� ����
                {
                    printf("��");
                }
                else
                {
                    printf("��");
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
int trans_block(int check_trans_block)   //�� ������ȯ
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][check_trans_block][j][i] == 1 && made_wall[y - 3 + j][x - 3 + i] == 1)
            {
                return 0;  ///�� ����
            }
        }
    }
    return 1;
}
int limit_line()   //�� ���Ѽ� ����, ���ӿ���
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
int limit_block(int modi_x, int modi_y)   //�� �浹 Ȯ�� (����, ������, ������ �̵��� �� �ִ°�?)
{
    int index_x = modi_x - 3, index_y = modi_y - 3;     // ����� ��ǥ�� index�� �°� �ٲ� ��
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[current_block_index][block_direction][j][i] == 1 && made_wall[index_y + j][index_x + i] == 1) // �� �� ��
            {
                check_crash(x, y + 1);
                return 0;
            }
        }
    }
    return 1;   // �� �� ���� ��
}
int check_crash(int bottom_x, int bottom_y)   // �� �̻� ����� ������ �� ���� �� == �Ʒ��� ������ ��
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
void solidify_block()   //�� ������
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
void del_bottom_line()  //�ϼ��� �� �����
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
void down_block(int line_count)  //�� ������ (�ٳ�����)
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
void print_block()  //�� ���
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {

            if (block[current_block_index][block_direction][i][j] == 1)
            {
                gotoxy(x + j, y + i);
                printf("��");
            }
        }
    }
}
void print_next_block()  //���� �� �����ֱ�
{
    for (int j = 0; j < 4; j++)
    {
        for (int i = 0; i < 4; i++)
        {
            if (block[next_block_index][0][i][j] == 1)
            {
                gotoxy(17 + j, 6 + i);
                printf("��");
            }
        }
    }
}
void show_next_block()   //���� �� �����ֱ�
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
void clean_block()   //�� �ܻ� �����
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
void move_block()   //�� �����̱�
{
    char move_key;
    if (_kbhit())
    {
        move_key = _getch();
        switch (move_key)
        {
        case 32:   //�� ������
            while (limit_block(x, y + 1) == 1)
            {
                y++;
            }
            show_wall();
            break;
        case'w':case'W':  //�� ���� �ٲٱ�
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
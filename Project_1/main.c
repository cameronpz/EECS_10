#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 4
#define N 13

/* goes to menu where users can pick if they want to play, exit program, or adjust settings */
/* lets players pick symbols */
void Settings(char *player_symbol)
{
  int player;
  int validinput=0;

  while (!validinput)
  {
    printf("Choose Player (1 or 2):\n");
    scanf("%d", &player);
    if ((player==1)||(player==2))
    {
        validinput=1;
    }
  }
  printf("Select your symbol\n");
  scanf(" %c", &player_symbol[player-1]);

}

int Menu(char *player_symbol)
{
    int retval;
    int menu_option= 0;
    int do_settings=1;

    while (do_settings)
    {
        printf("Select one of the following numbers\n1 Start New Game \n2 Settings \n3 Exit Program\n");
        scanf("%d", &menu_option);

        while ((menu_option != 1) && (menu_option != 2) && (menu_option != 3))
        {
            scanf("%d", &menu_option);
        }

        if (menu_option == 1)
        {
          do_settings=0;
          retval=1;
        }
        if (menu_option == 2)
        {
          Settings(player_symbol);
          retval=1;
        }
        if (menu_option == 3)
        {
            printf("Exiting Program");
            retval= 0;
            do_settings=0;
        }
    }


    return retval;
}

/* prints board */
void Board_Print(char board[][N])
{
    for (int i=0; i<M; i++)
    {
    printf("%s\n", board[i]);
    }
}

/* reset the board every game */
void Init_Board(char board[][N])
{
   strcpy(board[0], "3___|___|___");
   strcpy(board[1], "2___|___|___");
   strcpy(board[2], "1___|___|___");
   strcpy(board[3], "  A   B   C ");
   Board_Print(board);
}

/* collect player move, add to the board */
int Game_Play(int player, char board[][N], char *player_symbol)
{
 int valid;
 char mv[4];
 int retval=0;
 printf("Next Move\n");
 scanf("%s", mv);

 valid=0;
 while ( !valid )
 {

        if (!(strcmp(mv, "A3")))
        {
            if (board[0][2] == '_')
            {
                board[0][2] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }

        else if (!(strcmp(mv,"B3")))
        {
          if (board[0][6] == '_')
            {
                board[0][6] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }

        else if (!(strcmp(mv,"C3")))
        {
           if (board[0][10] == '_')
            {
                board[0][10] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }

        else if (!(strcmp(mv,"A2")))
        {
            if (board[1][2] == '_')
            {
                board[1][2] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }

        else if (!(strcmp(mv,"B2")))
        {
           if (board[1][6] == '_')
            {
                board[1][6] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }

        else if (!(strcmp(mv,"C2")))
        {
           if (board[1][10] == '_')
            {
                board[1][10] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }
        else if (!(strcmp(mv,"A1")))
        {
            if (board[2][2] == '_')
            {
                board[2][2] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }
        else if (!(strcmp(mv,"B1")))
        {
            if (board[2][6] == '_')
            {
                board[2][6] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }


        else if (!(strcmp(mv,"C1")))
        {
            if (board[2][10] == '_')
            {
                board[2][10] = player_symbol[player-1];
                valid=1;
            }
            else
                valid=0;
        }

        else if (!(strcmp(mv, "quit")))
        {
            retval=1;
            valid=1;

        }
        if (!valid) // not valid
        {

            printf("invalid input, please enter again\n");
            scanf("%s", mv);
        }
 }
 return retval;
}



/* look in the board for 3 in a row */
/* return 0 = continue, no winner or tie */
/* return 1 = winner by current player */
/* return 2 = tie, game over */
int BoardCheck(char board[][N], char *player_symbol, int currentplayer, int count)
{
char current_symbol;
int retval=0;

if (currentplayer == 1)
{
    current_symbol = player_symbol[0];
}
else if (currentplayer == 2)
{
    current_symbol = player_symbol[1];
}
//checking diagonal cases
if ( (board[0][2]== current_symbol) && (board[1][6]== current_symbol) && (board[2][10]== current_symbol) )
{
    retval= 1;
}
if ( (board[2][2]== current_symbol) && (board[1][6]== current_symbol) && (board[0][10]== current_symbol) )
{
    retval = 1;
}

//checking row cases
for (int i=0; i<3; i++)
{
    if ((board[i][2]== current_symbol) && (board[i][6]== current_symbol) && (board[i][10]== current_symbol))
    {
        retval= 1;
    }
}
//checking column cases
for (int i=2; i<11; i=i+4)
{
   if ((board[0][i] == current_symbol) && (board[1][i] == current_symbol) && (board[2][i] == current_symbol))
   {
       retval= 1;
   }
}
//checking for tie cases
if ((retval==0)&&(count==9))
    retval = 2;

//no end cases have been hit
return retval;
}

int main()
{
    int gamestatus=0;
    int currentplayer;
    int count;
    char player_symbol[2] = {'X','O'};
    char board[M][N] =
    {"3___|___|___", "2___|___|___", "1___|___|___", "  A   B   C "};


    while (Menu(player_symbol))
    {
       /* New Game Begins */
       printf("Game Begins...\n");
       printf("Player 1 Symbol: %c\n", player_symbol[0]);
       printf("Player 2 Symbol: %c\n", player_symbol[1]);

       Init_Board(board);
       currentplayer = 2;
       count = 0;
       while (!gamestatus)
       {
            count++;
            /* keeping track of which player's turn it is */
            currentplayer++;
            if (currentplayer==3)
            {
                currentplayer=1;
            }
            /* collect player player move */
            if (!Game_Play(currentplayer, board, player_symbol))
            {
                /* display board */
                Board_Print(board);

                /* check board to see if someone won */
                gamestatus = BoardCheck(board, player_symbol, currentplayer, count);
            }
            else
                gamestatus = 3;

       }
        if (gamestatus == 1)
       {
            printf("Player %d has won the game\n", currentplayer);
       }
        if (gamestatus == 2)
        {
            printf("Tie, game over\n");
        }

        if (gamestatus==3)
        {
            printf("Quit Game, Exiting\n");
        }
        gamestatus=0;
    }
    return 0;
}

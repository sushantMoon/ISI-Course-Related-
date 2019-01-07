/*-----------------------------------
Name: Sushant Moon
Roll number: MTC1807
Date: 31 July, 2018
Program description: Stick Game, Mode 1 : computer wins if played 1st  Mode 2 : computer plays optimally
Acknowledgements: 
------------------------------------*/

#include <stdio.h>
#define STICKS 11
#define MIN_PER_TERM 1
#define MAX_PER_TERM 3

int player_plays(int sticks){
    int turn;
    while(1==1){
        printf("Please enter, how many sticks you want to remove:\n");
        scanf("%d", &turn);
        if ( (turn >= MIN_PER_TERM) && (turn <= MAX_PER_TERM) && (sticks-turn >= 0) )
            break;
        else
            printf("Invalid entry provided. Re-try..\n");
    }
    return turn;
}

int computer_wins_if_first(int player_played, int sticks, int turn){
    int computer_played = 0;
    if (player_played == -1){
        computer_played = 2;         // First turn for the computer
    }
    else{
        if (turn == 2){
            if ((sticks - 4 + player_played)>=3){
                computer_played = 4-player_played;
            }
            else if (sticks < 4){
                computer_played = sticks;
            }
        }
        else{
            if ((sticks-(4-player_played))>0){
                computer_played = 4-player_played;
            }
            else{
                computer_played = sticks;
            }
        }
    }
    return computer_played;
}

int computer_plays_optimally(int player_played, int sticks){
    int computer_played = 0;
    if (player_played == -1){
        computer_played = 2;         // First turn for the computer
    }
    else{
        if (sticks == 10){
            computer_played = 1;
        }
        else if (sticks == 9){
            computer_played = 1;
        }
        else if (sticks < 9 && sticks > 5){
            computer_played = sticks - 5;
        }
        else if (sticks > 4){
            computer_played = 4-player_played;
        }
        else if (sticks == 4){
            computer_played = 3;
        }
        else if (sticks > 1 && sticks < 4 ){
            computer_played = sticks - 1;
        }
        else{
            computer_played = sticks;
        }
    }
    return computer_played;
}

int check_loss(int sticks, char *entity){
    if (sticks <= 0){
        printf("%s has lost the game !!!\n", entity);
    }
    return 1;
}

int game_engine(int player_turn,int mode){
    int sticks = STICKS;
    if (mode == 1){
        printf("Mode 1 : computer wins if and only if it has the first turn\n");
        int player_played = -1;
        int computer_played = -1;
        while(sticks > 0){
            if (player_turn == 1){
                printf("Player's Turn :\n");
                player_played = player_plays(sticks);
                sticks -= player_played;
                printf("You removed %d sticks , Remaining Sticks : %d\n", player_played, sticks);
                check_loss(sticks, "Player");
                if (sticks > 0){
                    printf("Computer's Turn :\n");
                    computer_played = computer_wins_if_first(player_played, sticks, 2);
                    sticks -= computer_played;
                    printf("Computer removed %d sticks , Remaining Sticks : %d\n", computer_played, sticks);
                    check_loss(sticks, "Computer");
                }
            }
            else if (player_turn == 2){
                printf("Computer's Turn :\n");
                computer_played = computer_wins_if_first(player_played, sticks, 1);
                sticks -= computer_played;
                printf("Computer removed %d sticks , Remaining Sticks : %d\n", computer_played, sticks);
                check_loss(sticks, "Computer");
                if (sticks > 0){
                    printf("Player's Turn :\n");
                    player_played = player_plays(sticks);
                    sticks -= player_played;
                    printf("You removed %d sticks , Remaining Sticks : %d\n", player_played, sticks);
                    check_loss(sticks, "Player");
                }
            }
        }
        return 1;
    }
    else if (mode == 2){
        printf("Mode 2: Computer will win optimally.\n");
        int player_played = -1;
        int computer_played = -1;
        while(sticks > 0){
            if (player_turn == 1){
                printf("Player's Turn :\n");
                player_played = player_plays(sticks);
                sticks -= player_played;
                printf("You removed %d sticks , Remaining Sticks : %d\n", player_played, sticks);
                check_loss(sticks, "Player");
                if (sticks > 0){
                    printf("Computer's Turn :\n");
                    computer_played = computer_plays_optimally(player_played, sticks);
                    sticks -= computer_played;
                    printf("Computer removed %d sticks , Remaining Sticks : %d\n", computer_played, sticks);
                    check_loss(sticks, "Computer");
                }
            }
            else if (player_turn == 2){
                printf("Computer's Turn :\n");
                computer_played = computer_plays_optimally(player_played, sticks);
                sticks -= computer_played;
                printf("Computer removed %d sticks , Remaining Sticks : %d\n", computer_played, sticks);
                check_loss(sticks, "Computer");
                if (sticks > 0){
                    printf("Player's Turn :\n");
                    player_played = player_plays(sticks);
                    sticks -= player_played;
                    printf("You removed %d sticks , Remaining Sticks : %d\n", player_played, sticks);
                    check_loss(sticks, "Player");
                }
            }
        } 
        
    }
    else{
        printf("Terminating the game, as invalid entry for mode of game was provided.\n");
    }
    return 1;
}


int main()
{
    printf( "Enter 1 for : The computer wins if and only if it has the first turn.\n"
            "Enter 2 for : The computer always optimally.\n" );
    int mode = 0;
    scanf("%d",&mode);
    printf("Choose to play 1st (enter 1) or 2nd (enter 2)\n");
    int player_turn;
    scanf("%d", &player_turn);
    if (player_turn == 1 || player_turn == 2)
        game_engine(player_turn, mode);
    else
        printf("Invalid entry for player turn was provided.\n");
    return 0;
}

// NAME: Daniil
// Belousov
// ID 2491827

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define R 5 // R = rows
#define C 4 // C = columns

int randomPowerTwo(int);
int shootMerge( int [R][C], int );
void displayBoard(int [R][C]);
int fullorNot(int [R][C], int);


int main()
{
    int Board[R][C],NewNumber, maxpower=1, shot=0, i, j, checkpoint1=0, checkpoint3=0,
    CheckTheLoad=0, WillToPlay=1;
    char ChoicetoPlay;
    srand(time(NULL));

    for (i=0;i<R;i++){
        for (j=0;j<C;j++){
            Board[i][j]=0;
        }
    }
    printf("C1\tC2\tC3\tC4\t\n\n");
    //Creating a loop to start the game
    while (WillToPlay!=0){

        do{
            // generating a random number
            NewNumber=randomPowerTwo(maxpower);
            // checking if the board is full
            checkpoint1=fullorNot(Board,NewNumber);
            // based on the result of the fullness of the board we either play the game or finish it
            // as long as the board is not full we play
            if (checkpoint1==0){
            //counting the number of shots taken
                maxpower=shootMerge(Board,NewNumber);
                shot+=1;
                displayBoard(Board);
                printf("%d shots so far\n",shot);
                printf("\n");
            }
            else
                CheckTheLoad=1;


        }while (CheckTheLoad!=1);

    // displaying the final board

    displayBoard(Board);

    // asking the user if he/she wants to play again, if yes, we set everything to the starting values

    printf("Do you want to play again (Y/N)");
    fflush(stdin);
    scanf("%c", &ChoicetoPlay);
    while(checkpoint3!=1){
        if (ChoicetoPlay=='N'){
            WillToPlay=0;
            checkpoint3=1;
            }
        else if (ChoicetoPlay=='Y'){
            WillToPlay=1;
            checkpoint3=1;
            for (i=0;i<R;i++){
                for (j=0;j<C;j++){
                    Board[i][j]=0;
                }
            }
            printf("\n\n\n\nC1\tC2\tC3\tC4\t\n\n");
        }
        else {
            printf("Invalid input, please try again");
            fflush(stdin);
            scanf("%c", &ChoicetoPlay);

        }

    }


    }

    return 0;

}

// Creating the random number between 2 and 64 in in base 2
int randomPowerTwo(int maxpower){
    int returnvalue;
    returnvalue=pow(2,(rand()%6+1));
    if (returnvalue<=pow(2,maxpower))
        return returnvalue;
    else
        return randomPowerTwo(maxpower);

}

int shootMerge( int Board[R][C], int NewNumber){
    int columnchoice, i=(C-1), j,k=0, checkpoint1=0, checkpoint2=0,checkpoint3=0, n=0,maxpower=0;

    // asking the user where he wants to shoot the number

    printf("You have %d, which column would you like to shoot [1-4]? ");
    scanf("%d",&columnchoice);

    // checking if the number could be entered to the column


    while (checkpoint2!=1){
        checkpoint3=0;

        // checking if the user entered a valid column

        while (checkpoint3!=1){
            if ((columnchoice<=4)&&(columnchoice>=1)){
                    checkpoint3=1;
            }
            else{
                printf("Invalid column number, please try again: ");
                scanf("%d",&columnchoice);
            }
            }

        if (((Board[R-1][columnchoice-1]>NewNumber) ||  (Board[R-1][columnchoice-1]<NewNumber)) && (Board[R-1][columnchoice-1]!=0)  ){
            printf("You cannot place your number there as the one there is not the same as yours\n");
            printf("Please enter the column you want to place the number [1-4]? ");
            scanf("%d",&columnchoice);

        }
        else
            checkpoint2=1;

    }



    // checking if the column that the user chose has the same number in the row before the place where we will place the new number and sum them if possiable
    // this check is only for the last row
    if (((Board[R-1][columnchoice-1])!=0 )   &&  ((Board[R-1][columnchoice-1])==NewNumber)) {
        Board[R-1][columnchoice-1]+=NewNumber;
        n+=1;
    }



    // checking if the column the person chose is free or could be merged


    for (i=0;i<R;i++){
        if (((Board[i][columnchoice-1])==0)&&(n==0)){
            Board[i][columnchoice-1]=NewNumber;
            n+=1;
            }
        else if (((Board[i][columnchoice-1])==NewNumber)&&(n==0)&&((Board[i+1][columnchoice-1])==0) ){
            Board[i][columnchoice-1]+=NewNumber;
            n+=1;
        }
    }


    // loop to merge everything thats possible and move the numbers do they would not have gaps in the columns

    for (i=R-1;i>0;i--){
        if (Board[i][columnchoice-1]==Board[i-1][columnchoice-1]){
            Board[i-1][columnchoice-1]+=Board[i][columnchoice-1];
            Board[i][columnchoice-1]=0;
        }
        if ((Board[i-1][columnchoice-1]==0)&&(Board[i][columnchoice-1]!=0)){
            Board[i-1][columnchoice-1]=Board[i][columnchoice-1];

            }

    }


    // looking for the greatest power of the values in the column

    for (i=0;i<R;i++){
        for (j=0;j<C;j++){
            if ((Board[i][j]!=0)&&(log2(Board[i][j])>maxpower))
                maxpower=log2(Board[i][j]);
                }

            }

    return maxpower;

}

void displayBoard(int Board[R][C]){
    int i, j, n, k;
    printf("C1\tC2\tC3\tC4\t\n");

    // creating a loop to output values
    // if there are no values in the row, we do not display it
    for (i=0;i<R;i++){
            n=0;
        for (j=0;j<C;j++){
            if (Board[i][j]==0)
                n++;
            else{
                for (k=0;k<n;k++){
                    printf("  \t");
                    }
                n=0;
                printf("%d\t", Board[i][j]);
        }

        }
        if (n<C)
            printf("\n");
            }
    printf("\n");
}

int fullorNot(int Board[R][C], int NewNumber){
    int k=0, i, j;
    // checking if we have any free space to shoot the number and if the new number could be merged with any other value in the last row
    // that is already in the table
    for (i=0;i<C;i++){
        if (((Board[R-1][i])>NewNumber    )|| ((Board[R-1][i])<NewNumber )&&((Board[R-1][i])!=0 )) {
            k+=1;
            }
    }
    if (k>=4){
        printf("You have %d\n",NewNumber);
        printf("Sorry, no free spaces to place the number \n");
        return 1;
        }
    else
        return 0;

}



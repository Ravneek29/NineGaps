#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    
    int main_board[9]={1,2,3,4,5,6,7,8,9}; // define the main board to store all the values from 1-9
    int missing_array[9]; // define an array of size 9 to keep track of missing values
    int game_board[9]; // define an array to form the actual game board with random numbers and hidden values
    int temp_board[9]; // define an array which is a copy of the game_board and will be displayed to the user and will be updated in each iteration
    int column_results[3]; // this is an array that stores the results of calculation of each column
    int row_results[3]; // this is an array that stores the results of calculation of each row
    char operators_array[12]; // this is an array that stores random operations
    int i,j; // these variables will be used for loop indexes
    int rand_num,temp1; // rand_num will be used to store the result of random number generations, temp1 will be used as a temporary variable
    int level; // this variable stores the level of difficulty
    char check_game; // this is a flag variable to determine if the user solves the game correctly
    int play_again; // this is flag variable to determine if the user wants to play again or not
    int missing_count; // this is a variable that keep track of the number of missing values in the game board.
    srand(time(NULL));
 
    do{
        check_game=1;
        level=0;
        printf("Welcome to Nine-Gaps game!...\n");
	    printf("*****************************\n");
	    printf("      *****************      \n");
	    printf("            *****            \n");
	    printf("              *              \n");
	
        // get the level of difficulty from the user
        do{
		    puts("Choose the level of difficulty (1-Beginner, 2-Intermediate, 3-Advanced, 4-Expert):");
		    scanf("%d",&level);
		    if ((level < 1) || (level > 4))
			    puts("The entered value is not valid");
		    else{
		        switch (level){
		            case 1:
		                puts("You have chosen the Beginner level");
		                break;
		            case 2:
		                puts("You have chosen the Intermediate level");
		                break;
		            case 3:
		                puts("You have chosen the Advanced level");
		                break;
		            case 4:
		                puts("You have chosen the Expert level");
		                break;
		        }
		        break;
		    }
	    } while (1);
        //////////////////////////////////////////////////
    
        //generate a random main board by shuffling the manin_board
        for (i = 8; i > 0; i--){
            rand_num = rand() % i;
		    temp1 = main_board[i];
		    main_board[i] = main_board[rand_num];
		    main_board[rand_num] = temp1;
	    } // end for
        /////////////////////////////////////////////////
    

        //generate random operators ( + , - , x )
    
        for (i = 0; i < 12; i++){           						
		    rand_num = 1 + rand() % 3;
		    if (rand_num == 1)
			    operators_array[i] = '+';
		    else if (rand_num == 2)
    		    operators_array[i] = '-';
		    else
			    operators_array[i] = '*';
	    } // end for
        /////////////////////////////////////////////////
        
        // calculate the results in columns and rows

        for (i=0;i<3;i++){
            for (j=0;j<3;j++){
                if (j==0){
                    column_results[i]=main_board[i];
                    row_results[i]=main_board[3*i];
                }
                else{
                    switch (operators_array[(2*i) + (j-1)]){      // calculate column results
                        case '+':
                            row_results[i]=row_results[i] + main_board[(3*i) +j];
                            break;
                        case '-':
                            row_results[i]=row_results[i] - main_board[(3*i) +j];
                            break;
                        case '*':
                            row_results[i]=row_results[i] * main_board[(3*i) +j];
                            break;
                    } // end switch
                    switch (operators_array[(3*(j+1)) + i]){      // calculate row results
                        case '+':
                            column_results[i]= column_results[i] + main_board[(3*j) + i];
                            break;
                        case '-':
                            column_results[i]= column_results[i] - main_board[(3*j) + i];
                            break;
                        case '*':
                            column_results[i]= column_results[i] * main_board[(3*j) + i];
                            break;
                    } // end swithch
                }  // end else 
            } // end for j
        } // end for i
        ////////////////////////////////////////////////////////
    
        /// initializing missing array to 0
        for (i=0;i<9;i++)
            missing_array[i]=0;
    
        ////////////////////////////////////////////////////////
        
        
        /// copy the main board into game_board
    
        for(i = 0; i < 9; i++)
            game_board[i] = main_board[i];
    
        /////////////////////////////////////////////////////////
    
    
        // Based on the selected level, 3 or 5 or 7 board values will be hidden.
    
        i=0; // initializing i to 0
    
        while (i < level*2+1){								
		    int r = rand() % 3;
		    int c = rand() % 3;
		    if (game_board[3*r+c]!='?'){ 
			    missing_array[game_board[3*r+c]-1]= game_board[3*r+c]; // the hidden values will be added to the set of missing values
		        game_board[3*r+c] = '?';
			    i++;
		    } // end of if
	    } // end of while
	    ////////////////////////////////////////////////////////
	
        /// Copy the game board into a temporary board
        for(i = 0; i < 9; i++)
            temp_board[i] = game_board[i];
        
        ///////////////////////////////////////////////////////
    
        // the inner loop to get values from the user
        do{
        
            // Display the game board after each update
            
            printf("Game Board:\n");
	        printf("---------------------------------------------------\n");
            for (i=0;i<3;i++){
                if (i>0){                   // show the column opertors
                    for (j=0;j<3;j++){
                        printf(" %c\t\t", operators_array[3*(i+1)+ j]);
                    }
                    printf("\n");
                }
                
                for (j=0;j<3;j++){          // show the rows
                    if (game_board[(i*3)+j]!='?')
                        printf(" %d\t ", temp_board[(i*3)+j]);
                    else if (game_board[(i*3)+j]!=temp_board[(i*3)+j]){
                        printf(" %d?\t ", temp_board[(i*3)+j]);
                    }
                    else
                        printf(" ?\t ");
                
                    if (j<2)
                        printf(" %c\t", operators_array[(i*2) + j]);
                    else
                        printf("= %d", row_results[i]);       // show the rows results
                }
                printf("\n");
                if (i==2)
                    printf (" =\t\t =\t\t =\n");    
            }
            for (i=0;i<3;i++)               // show the columnar results
                printf(" %d\t\t", column_results[i]);
            printf("\n---------------------------------------------------\n");
        
        ////////////////////////////////////////////////////////
        
        // Display the missing values and update missing_count
        
            missing_count=0;
            printf("List of Missing Values=\n");    
            for(i = 0; i < 9; i++)
                if (missing_array[i]>0){
                    printf("\t%d ", missing_array[i]);
                    missing_count+=1;
                }
            printf("\n---------------------------------------------------\n");
        
        /////////////////////////////////////////////////////////
        
            if (missing_count==0) // break if the missing values are empty
                break;
        
        // Get user's guess (location and value) and check inputs' validity

	        printf("Enter a row number (1-3), column(1-3), value(One of the missing values):\n");
	        int r, c, v; 
	        scanf("%d %d %d", &r, &c, &v);
	        if (r==0 || c==0 || v==0)
	            break;
	        
	        if (r < 1 || r > 3 || c < 1 || c > 3){
	            puts("Invalid row and/or column numbers. Try again.");
	            continue;
	        }
	        
	        if (v < 1 || v > 9) {
	            puts("Invalid cell value. Try again.");
	            continue;
	        }
	        
	        if (missing_array[v-1]<1) {
	            puts("This value is already there. Try again.");
	            continue;
	        }
            
            if (game_board[3*(r-1) + (c-1)]!='?') {
                puts("This cell could not be changed. Try again.");
	            continue;
	        }
	        else{
	            if (game_board[3*(r-1) + (c-1)]==temp_board[3*(r-1) + (c-1)]){
	                temp_board[3*(r-1) + (c-1)]=v;
	                missing_array[v-1]=-1;
	            }
	            else{                                                             // Return value to missing values and update the temp_board
	                missing_array[temp_board[3*(r-1) + (c-1)]-1]=temp_board[3*(r-1) + (c-1)];
	                temp_board[3*(r-1) + (c-1)]=v;
	                missing_array[v-1]=-1;
	            }
	        continue;
	        }

        } while (1); // end of the inner loop
    
    
        for (i=0;i<9;i++)           // check the results
            if (temp_board[i]!=main_board[i]){
            check_game=0;
            break;
            }
        
        if (check_game)             // display Win/Loose Message
            printf ("**** Congratulations!!!****\n ***You Won!!!!*** \n");
        else
            printf ("Sorry it is not correct \n");
        
        printf("#######################################\n");
        printf ("   Do you want to play again? (Yes:1, No:0)\n"); // ask the user to play again
        printf("#######################################\n");
        scanf ("%d", &play_again);
        
        if (!play_again){
            printf("Bye\n");
            break;
        }
    } while (1); // end of the outer loop
}

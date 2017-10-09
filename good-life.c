/// http://www.dreamincode.net/forums/topic/55572-conways-game-of-life/
/// downloaded by copy-paste on 8/19/2015 and modified to use an infinite loop
/// and have different Rule functions.
///
/// This code needs serious work in these areas:
/// <ol>
/// <li>  syntax: there are a number of warnings that cause errors.
/// </li>
/// <li>  semantics: the game algorithm implementation is incorrect.
/// </li>
/// <li>  design: the implementation needs function and value refactoring.
/// </li>
/// <li>  style: formatting is poor; the mix of TAB and spaces indentation
/// needs correction, and spacing between tokens is inconsistent.
/// The course style puts the '{' at the end of the function header, not
/// on a line of its own, and function headers belong at the left margin.
/// </li>
/// <li>  documentation: documentation is non-existent except for this block.
/// </li>
/// </ol>
///
/// @editor: Sameen Luo xxl2398@rit.edu
/// @filename: good-life.c
/// @description: plays out Conway's game of life
/// 		DEATH-
/// 	       	  if a populated cell has 0 or 1 neighbor, organism dies out of loneliness
///		  if a populated cell has 4-8 neighbors, organism dies out of overpopulation
///		  only 2 or 3 neighbors' organisms' cells survive
///		BIRTH-
///		  if a cell is empty and it has 3 neighbors, an organism is born
///			
/// @date: 9/20/2017


#define _BSD_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "display.h"


const int SIZE = 20;
const int CYCLE = 100;


/*
 * function for program header
 * return: nothing
 */
void header( void ) {
	printf("\n\t..Welcome to the Game of life..\n");
}


/*
 * count the number of neighbors of the [row][col] cell on the "life" board
 * param: row  int  row number of the cell we are counting neighbors at
 *        col  int  column number of the cell we are counting neighbors at
 *        life 2Darray the current configuration of the life board
 * return: int the number of neighbors around [row][col] cell
 */
int neighborCount(int row, int col , char life[][SIZE])
{
	
	int neighbors = 0;


	if(life[(row - 1) % SIZE][(col - 1 )% SIZE] == '*')	//add modulo to make the board "wrap around"
		++neighbors;
	if(life[(row - 1) % SIZE][col] == '*')
		++neighbors;
	if(life[(row - 1) % SIZE][(col + 1) % SIZE] == '*')
		++neighbors;
	if(life[row][(col - 1) % SIZE] == '*')
		++neighbors;
        if(life[row][(col + 1) % SIZE] == '*')
		++neighbors;
	if(life[(row + 1) % SIZE][(col - 1) % SIZE] == '*')
                ++neighbors;
        if(life[(row + 1) % SIZE][col] == '*')
                ++neighbors;
        if(life[(row + 1) % SIZE][(col + 1) % SIZE] == '*')
                ++neighbors;

	return neighbors;

}



/*
 * perform one generation of game of life. 
 * param: life 2Darray to hold the current configuration of the board
 * return: nothing
 */

void evolve(char life[][SIZE])
{
	//copy the 2D array
	char copy[SIZE][SIZE];
	for (int x =0 ; x<SIZE ; x++)
	{
		for (int y=0; y<SIZE; y++)
		{
			copy[x][y] = life[x][y];
		}
	}	

		
			
	int neighbors = 0;

	for ( int row = 0; row < SIZE ; row++)
	{
		for (int col = 0; col < SIZE ; col++ )
		{
			
	
			neighbors = neighborCount(row, col, copy);			/////? what's wrong?
			
			if (life[row][col] == '*')
			{
				if (neighbors == 0 || neighbors == 1 || neighbors >= 4)
				//die out of loneliness and overpopulation
				{
					life[row][col] = ' ';
				}
			}
			else //unpopulated cell
			{
				if (neighbors == 3)	//if neighbor reach 3, new organism is born
				{
					life[row][col] = '*';
				}
			}

		}
			
	}



}


	

/*
 * main function.
 * initialize, prompt for starting number of organisms, 
 * perform 100 cycles of game of life and print out the results. 
 * return: 0 if runs succesfully
 */   	
int main(void)
{
	char life[SIZE][SIZE];
	int orgs;// gens;    //fix unused
	int i, row, col;    //fix unused
	int count = 0;
	//int x = 19;   //fix from unused
	//int y = 19;   //fix from unused
	// char ans;    //fix ununsed
   	
	header();

	printf("\nPlease enter the initial number of organisms: ");
	scanf("%i", &orgs);
	  
	srand( 31 );
			  
	for(i = 0; i < orgs ; i++)
	{
		row = rand();
		row %= SIZE;
		col = rand();
		col %= SIZE;
		life[row][col] = '*';  //fix 2
	}
		 
	for(row = 0; row < SIZE ; row++)
	{
		for(col = 0; col < SIZE ; col++)
		{
			if(life[row][col] != '*')
			life[row][col] = ' ';    //fix 2
		}
	}
/*			  
	for(row = 0; row< SIZE ; row++)
	{
		for(col = 0; col< SIZE ; col++)
		{
			printf("%c", life[row][col]);  //fix 1
		}
		puts(" ");
	}

*/
	clear();			 
	while ( 1 )
	{			

		//birthRule( life );    //fix from unused
		//survivalRule( life );   //fix from unused
		
			//put in some sort of loop????
		set_cur_pos(1, 1);
		
		
		for(row = 0; row < SIZE ; row++)
		{
			for(col = 0; col < SIZE ; col++)
			{
				put( life[row][col]);
			//	printf("%c", life[row][col]);//fix 1 
			}
			puts(" ");

		}
		printf("\ngeneration: %d\n", count);
		count++;	
		evolve( life );
		usleep( 81000 );		
	}
		  
   	
	return 0;
}
			

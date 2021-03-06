/* 
 * shared.h - a header for shared.c
 *
 * 
 * shared stores functions used by solve and create, mostly validating aspects of the grid
 * C-median Dartmouth CS50 20S
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "node.h"
#include "bag.h"


/**************** checkNode ****************/
/*checks that a note is correctly placed:
return
True - there are no conflicts 
False - there is an error with the placement

Note: zeros are IGNORED, so a blank grid with one node will return true
*/
bool checkNode(node_t *node, int **grid);

/**************** gimme *****************/
/*checks to see if the given node has only one valid solution
return:
true: yes a gimme, value is set to correct value
false: not a gimme*/
int gimme(node_t *node,int **grid);

/******************* gimmeScanner **************/
/*scans a board and fills it with integers of gimmes until
there are no more*/
void gimmeScanner(int **grid);

/****************** pushGuesses **************/
/*takes a grid and bag, and pushes all valid guesses into the bag
Return True on at least one guess added to bag
Return false on null node or no valid guesses*/
bool pushGuesses(node_t *node, int **grid, bag_t *bag);

/*************** randomValueBag **************/
/* returns a bag containing integers 1-9 in random order; user  
 * responsible for deallocating bag memory */
bag_t * randomValueBag(void);

/*************** arrayCheck ***************/
/* checks whether given value is in given array*/
bool arrayCheck(int i, int *trackerArray);

/**************** getNextNode ***************/
/*gets the next zero in the grid and returns a node to that location*/
node_t *getNextNode(int **grid);


/**************** gridCheck ***************/
/*checks to see if a given board is a solution*/
bool gridCheck(int **grid);

/************* getRandomNode ***********/
node_t *getRandomNode(int **grid);



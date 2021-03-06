/* 
 * solver.h - a header for solver.c


 * solver contains the functions necessary to solve a sudoku grid
 * C-median Dartmouth CS50 20S
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "node.h"
#include "shared.h"
#include "bag.h"


/******************* solve *****************/
/*takes a grid and a value that says whether or not to print
* return number of solutions 
*/
int solve(int **grid, bool print){
    gimmeScanner(grid); //fill in all gimmes (only one possible value)
#ifdef MYTEST
	fprintf(stdout, "Scanned for all gimmes (meaning nodes where there is only one possible value)\n");
#endif
    if(gridCheck(grid)){
        if(print){
            gridPrint(grid);
        }
        return 1;
        //only one solution if passed a true grid or all gimmes
    }
    
    int solcount = 0; //track number of solutions 
    bag_t *stack = bag_new(); //create a bag to stack possibilities 
    bag_t *backtrace = bag_new(); //create a bag for backtracing 

    node_t *currentNode,*nextNode,*btNode; //create the current and next nodes
    currentNode = getNextNode(grid); //start at the first node of the grid
#ifdef MYTEST
    if (currentNode==NULL)
    	fprintf(stderr, "getNextNode(grid) returned null\n");
#endif
    pushGuesses(currentNode,grid,stack); //stack all possible solutions for first node
#ifdef MYTEST
    fprintf(stdout, "Pushed all of the guesses to the bag, and the current bag of guesses is: \n");
    nodePrint(stdout, stack);
    fprintf(stdout, "\n");
#endif
    nodeDelete(currentNode); //delete the first node 
    currentNode = bag_extract(stack); //pull the first item from the stack
    //insert a copy of the item into the backtrace so we have a "root" for the backtrace stack
    if(currentNode!=NULL) bag_insert(backtrace,nodeNew(nodeGetRow(currentNode),nodeGetColumn(currentNode),0));
#ifdef MYTEST
    else
	fprintf(stderr, "The first node to visit is null!\n");
#endif
    while(currentNode!=NULL){ //while there are untried possibilites
        grid[nodeGetRow(currentNode)][nodeGetColumn(currentNode)] = nodeGetValue(currentNode); //set the grid to that possiblity
        nextNode = getNextNode(grid); //get next unsolved node in the grid
        if(nextNode!=NULL){ //if there is a next node
            if(pushGuesses(nextNode,grid,stack)){ //push all possibilites for that node to the stack
                bag_insert(backtrace,nextNode); //push the node onto the backtrace
            } 
            else{
            nodeDelete(nextNode); //clear the nextNode because its not in a bag

                /*backtrace:
                backtracing checks the next item in the bag. if its not the current node  
                implying we have jumped back at least 1, we simply follow the backtrace 
                stack backwards and set the grid to 0 as we go*/
                if(!nodeSameLocation(currentNode,bag_peek(stack))){ 
                    while(!nodeSameLocation(bag_peek(stack),bag_peek(backtrace))){
                        btNode = bag_extract(backtrace);
                        grid[nodeGetRow(btNode)][nodeGetColumn(btNode)] = 0;
                        nodeDelete(btNode);
                    }
                }
            }
        }
        else{ //on full grid 
            if(gridCheck(grid)){  //check if it solves
                solcount++; //add to count of solutions 
                if(solcount==1){
                    if(print){ //if print is enabled
#ifdef MYTEST
	fprintf(stdout, "Printing the resulting grid:\n");
#endif
                        gridPrint(grid); //print the grid 
                        printf("\n");
                    }
                }
                else {
                    nodeDelete(currentNode);
                    bag_delete(stack,nodeDelete); //clear bags
                    bag_delete(backtrace,nodeDelete);
                    return solcount;
                }
            }
            //same backtrace as above, here executed to jump back after checking a solution
            //necessary to find multiple solutions
            if(!nodeSameLocation(currentNode,bag_peek(stack))){
                while(!nodeSameLocation(bag_peek(stack),bag_peek(backtrace))){
                    btNode = bag_extract(backtrace);
                    grid[nodeGetRow(btNode)][nodeGetColumn(btNode)] = 0;
                    nodeDelete(btNode);
                }
            }
        }

        //check for a backtrace and execute a backtrace if necessary
        nodeDelete(currentNode);
        currentNode = bag_extract(stack);
    }
    bag_delete(stack,nodeDelete); //clear bags
    bag_delete(backtrace,nodeDelete);
   
    return(solcount);
}

#ifdef MYTEST
int main(int argc, char *argv[]){
	// print the command line so the user can view what was called on the solver
	for (int n = 0; n < argc; n++){
        	fprintf(stdout, " %s ", argv[n]);
	}
	fprintf(stdout, "\n");

	if (argc != 1){
		fprintf(stderr,"Incorrect number of arguments\nUsage: ./solveTest. \nSee readme for more\n");
        	return 1;
	}

	// initialize grid and record an error if gridNew returns null
	int **grid = gridNew();
	if (grid == NULL)
		fprintf(stderr, "gridNew returned a null value.\n");

	// call gridcopy, and print the resulting grid
	gridCopy(grid);
	fprintf(stdout, "gridCopy was called, printing the grid that was entered as input:\n");
	gridPrint(grid);

	// test the gridSolver
	printf("calling solve(grid, true)\n");
	int numSol = solve(grid, true);
	printf("number of solutions is: %d\n",numSol);

	// test gridDelete
	gridDelete(grid);
	fprintf(stdout, "gridDelete was called\n");

	fprintf(stdout, "End of this unit test\n\n");
	fprintf(stdout, "---------------------------------------------\n");
	return 0;	
}

#endif

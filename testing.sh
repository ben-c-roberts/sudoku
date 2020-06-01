#!/bin/bash
#
# File: testing.sh
#
# Description: fuzztesting for ./sudoku create, ./sudoku solve  
# 	      
# Input: User provides commandline argument denoting the number of tests to run
# Output: For each test, outputs create grid before and after solve, along with the  
# 	  number of possible solutions for the template grid
#
# C-Median, CS50, May 31, 2020


# Check to see if at least one argument given
if [ "$#" != 1 ]; then
    echo 1>&2 "Usage: one command line argument denoting number of tests to run"
    exit 1
fi

# Fuzz testing
# For each argument, find it in array and print "field-number:field-name"
echo Beginning fuzz testing
TEST_NUM=0
while [ $TEST_NUM -lt $1 ]; do  
	./sudoku create > file
	printf "Template:\n"
	cat file
	printf "\n"
	printf "Solution:\n"
        ./sudoku solve < file	
	printf  "–––––––––––––––––––––––––\n\n"
	((TEST_NUM = TEST_NUM + 1))
	sleep 1
done

rm -f file

#unit testing of solve
echo End of fuzz testing
echo Beginning unit testing of solve
./solver/solveTest solve < testgrids/test1
./solver/solveTest solve < testgrids/test2
./solver/solveTest solve < testgrids/test3
echo End of unit testing of solve

exit 0
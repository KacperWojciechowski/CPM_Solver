# Overview

This program allows user to perform a Critical Path Method optimization in work organization problems. 

# How to use

In order to use the CPM solver, user must prepare a file in square matrix format, where each of the numbers represent the cost of going from the source task (row number) to the adjacent task (column number). 
Tasks between which there is no connection are marked via -1. This implementation allows user to insert tasks between which the travel cost is equal to 0.

After creating an object from the source stream and calling the CPM_methode() function, user will be asked if he is searching for the minimum or maximum value (the maximum variant can be used to optimize problems such as the throughtput of network).
As a result, user will get a structure containing a vector of critical paths and the critical path value. 

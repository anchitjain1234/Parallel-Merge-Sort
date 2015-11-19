# Parallel Merge Sort

Merge sort by creating child processes using fork bomb to sort the inputs and then merging the sorted output by child processes in parent process.

#### Compiling
Type the following command to generate a binary named **merge**
``` sh
$ make
```

#### Running
* Generate a file **input.txt** having integers to be sorted , one per line with first line having total numbers to be sorted.Example input file:-  
5  
10  
8  
9  
6  
7  
1<sup>st</sup> line tells 5 integers are to be sorted.  
Next 5 lines contain innteger to be sorted, one every line.
* Run the program by following command.This will give sorted result on the standard output.

	``` sh
	$ ./merge
	```  
	
   
#### Todos
* If no more processes could be created (all PID's have been used) this program couldn't sort yet.Need to improve  upon this.


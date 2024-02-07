# Plagiarism-Detector
Project: 
Plagiarism Detection 
by Kary Sutariya (40193909)
M.A.C.S, Concordia University.

This project is based on C++ language. 

# Requirements
1. C++

# Warning: 
-> Before executing of make command, make sure that C++ is installed. 

# Run Command using make  

The syntax of the command to execute is as per below. 
-> make FILE1="<location of file 1>" FILE2="<location of file 2>" run
-> Here FILE1 and FILE2 are the two files that will be compared, and the program will check whether there is copy-paste work or not. Adding to that
<location of file 1> and <location of file 2> need to be replaced by the actual path of files in the system.  

Following is an example of a command. 
-> make FILE1="../data/okay02/1.txt" FILE2="../data/okay02/2.txt" run

# Explanation of code

-> First, the program reads the content of both files.
-> In the next phase, I am removing the bibliography from the content. Subsequently, references that are taken from other's work will be removed through the function name "remove_ref".
-> After all of this, all the stop words will be removed from the data as well and special characters will not have any specific important meaning therefore, those special characters
can be removed too. 
-> Now, Rabin-Karp has been applied to the clean data. This is an algorithm that can search patterns using the hash value. Further details about the algorithm can be found here (https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm).
-> Rabin-Karp requires the size of n-gram (in code it is n_gram with the value of 5) which is a parameter. Its value can be between 3 to 6. 
-> Then, the similarity of both data files has been calculated in percentage using the following equation.
-> Equation = ((2 * (length of common hash values of both data files))/ (count of different hashes of data file 1 + count of different hashes of data file 2)) * 100
-> Thrash hold is 28.5. Meaning if the similarity is less than 28.5, it returns 0 (that means there is no plagiarism). Otherwise, the program will return 1 (that means plagiarism has been detected).

Word Polygon Solver
=====================

Solver for word polygon puzzle of custom dimentions.
Solves using trie and backtracking.
Comments are added for code readbility.

Input format
-------------
Program will keep taking in input indefinitely.
To end program enter row_count and/or column_count as 0(zero).

Each case should be in following format:

	(row_count) <whitespace> (column_count) <whitespace> (n*m characters for grid row wise)

where \<whitespace\> can be any whitespace including newline. Characters can contain \<whitespace\> between them<br>

#### Sample input ####
	3 3
	GOD
	ABS
	YES
	3 4
	SMALLINSMALL
	0 0

Output format
--------------
Output of different cases will be seperated by a blank line.<br>
Words in ouput will be sorted by length in decreasing order, if lenghts of words are same, they will be sorted lexicographically.

Running
--------
if input is being given via console wait for program to print "Trie Prepared" (takes 1-2 seconds), trie will be prepared only once initially, on every run.<br>

	eg: ./a.out < in.txt > out.txt

Change dict.txt file to change dictionary list. dict.txt should contain all allowed words with 1 word per line.

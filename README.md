# sort_algorithm

this is a C program compiled with latest version of GCC as for 2022 April. code is well tested and works great.

clone the repository or download release. in either case type make and makefile will do it

examples:

make
gcc sort.c abort.h structures.h parsing_args.h integers.h characters.h -o sort -Wall

./sort --help
USAGE: sort [--integers] or [--characters], [integers or characters(words or chars) separated by the whitespaces].

./sort --characters musk bezos gates zuckerberg busch trump kennedy Bezos Gates kEnnedy Musk trUMp
ascending: Bezos bezos busch Gates gates kEnnedy kennedy Musk musk trUMp trump zuckerberg 
descending: zuckerberg trump trUMp musk Musk kennedy kEnnedy gates Gates busch bezos Bezos

./sort --integers 8 9 2 6 4 1 7 5 3 -1 -10 -7
ascending:  -10  -7  -1  1  2  3  4  5  6  7  8  9 
descending:  9  8  7  6  5  4  3  2  1  -1  -7  -10

# GA_T1

A test to try and get a simple genetic algorithm working. Has a 32 bit chromosome, and tries to get it to total a target number from an initial population.
Command line arguments are target number, number of generations to try, and initial population size.
Chromosome parsing is:

- 0000 - 1001 : Digits 0 to 9
- 1010 : +
- 1011 : -
- 1100 : *
- 1101 : /
- 1110 : %
- 1111 : Junk - returns 'e'

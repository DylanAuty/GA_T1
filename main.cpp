#include <cstdlib>
#include <cmath>
#include <string>
#include <random>
#include <iostream>
#include <ctime>

#define CHSIZE 32	// Define length in bits of chromosome.

// FUNCTION PROTOTYPES
void genChrom(int size, int (&out)[CHSIZE]);
void printChrom(int (&in)[CHSIZE]);
int calcFitness(int(&in)[CHSIZE], int target);

using namespace std;

int main(int argc, char *argv[]){
	// Takes 3 arguments: <destination_num> <generation_num> <population_size>
	if (argc != 4) {
		cout << "Invalid number of arguments - 4 required" << endl;
		exit(0);
	}
	
	srand(time(NULL));
	rand();	//Seed random number generator with the time then discard first generated

	// Fetch arguments and write to their variables
	int target = atoi(argv[1]);
	int gens = atoi(argv[2]);
	int popSize = atoi(argv[3]);

	cout << "Target num: " << target << endl;
	cout << "Generation num: " << gens << endl;
	cout << "Initial Population Size: " << popSize << endl;
	
	int pop[popSize][CHSIZE];	// Create 2D array to hold the chromosomes
	for (int i = 0; i < popSize; i++){
		genChrom(CHSIZE, pop[i]);
		printChrom(pop[i]);
	}	//Initialise population - no function as size only known at runtime which makes passing by reference with 2D array a pain
	
	int fitness[popSize];
	// Assess population fitness
	for (int i = 0; i < popSize; i++){
		fitness[i] = calcFitness(pop[i], target);
	}



	return 1;
}

// FUNCTION DEFINITIONS

int calcFitness(int(&in)[CHSIZE], int target){
	/* PARSING:
	 * 0000 - 1001: Digits 0-9
	 * 1010 = +
	 * 1011 = -
	 * 1100 = *
	 * 1101 = /
	 * 1110 = %
	 * 1111 = Junk (nothing) - returns 'e'.
	 */
	// Fitness determined by distance from goal
	// For the time being using string of numbers multiplied together instead of trying to do string parsing
	int fitness = 0;
	int temp[4];
	int parseRes = 1;
	for (int i = 0; i < CHSIZE; i+4){
		for (int j = 0; j < 4; j++){
			temp[j] = in[i + j];
		}
		parseRes *= atoi(parseChar(temp));
	}
	// At the end of the chain of multiplications, do some stuff
	fitness = target - parseRes;
}

char parseChar(int(&in)[4]){
	if(in[0] == 0 && in[1] == 0 && in[2] == 0 && in[3] == 0){
		// 0000
		return '0';
	}
	else if(in[0] == 0 && in[1] == 0 && in[2] == 0 && in[3] == 1){
		// 0001
		return '1';
	}
	else if(in[0] == 0 && in[1] == 0 && in[2] == 1 && in[3] == 0){
		// 0010
		return '2';
	}
	else if(in[0] == 0 && in[1] == 0 && in[2] == 1 && in[3] == 1){
		// 0011
		return '3';
	}
	else if(in[0] == 0 && in[1] == 1 && in[2] == 0 && in[3] == 0){
		// 0100
		return '4';
	}
	else if(in[0] == 0 && in[1] == 1 && in[2] == 0 && in[3] == 1){
		// 0101
		return '5';
	}
	else if(in[0] == 0 && in[1] == 1 && in[2] == 1 && in[3] == 0){
		// 0110
		return '6';
	}
	else if(in[0] == 0 && in[1] == 1 && in[2] == 1 && in[3] == 1){
		// 0111
		return '7';
	}
	else if(in[0] == 1 && in[1] == 0 && in[2] == 0 && in[3] == 0){
		// 1000
		return '8';
	}
	else if(in[0] == 1 && in[1] == 0 && in[2] == 0 && in[3] == 1){
		// 1001
		return '9';
	}
	else if(in[0] == 1 && in[1] == 0 && in[2] == 1 && in[3] == 0){
		// 1010
		return '+';
	}
	else if(in[0] == 1 && in[1] == 0 && in[2] == 1 && in[3] == 1){
		// 1011
		return '-';
	}
	else if(in[0] == 1 && in[1] == 1 && in[2] == 0 && in[3] == 0){
		// 1100
		return '*';
	}
	else if(in[0] == 1 && in[1] == 1 && in[2] == 0 && in[3] == 1){
		// 1101
		return '/';
	}
	else if(in[0] == 1 && in[1] == 1 && in[2] == 1 && in[3] == 0){
		// 1110
		return '%';
	}
	else if(in[0] == 1 && in[1] == 1 && in[2] == 1 && in[3] == 1){
		// 1111
		return '^';
	}
	else {
		return 'e';
	}
}

void genChrom(int size, int (&out)[CHSIZE]){
	static const int binChars[2] = {0, 1};
	int random = 0;
	int i = 0;
	for (i = 0; i < size; i++){
		out[i] = binChars[rand() % 2];
	}
}

void printChrom(int (&in)[CHSIZE]){
	for (int i = 0; i < CHSIZE; i++){
		cout << in[i];
	}
	cout << endl;
}


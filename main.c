#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>

char answer[128];
char guess;
char player[2][16];
int i, j;
int turn;
int round;
int complete;
int life[2];
int score[2];
int complete;
int attempt;
int correct = 0;
int correct_total;

int i,j,k,l,m,N;

void init();
void player_name();
void scan_word();
void lower_string(char s[]);
void print_hangman(int life);
void print_word(int a[]);
void scan_letter();
void calculate(int a[]);

int main() {
	
	player_name();
	init();

	while(life[0]>0){
		life[0] = 5;
		life[1] = 5;
		complete = 0;
		
		scan_word();
		
		// Set the mask array - mask[i] is true if the
		// character s[i] has been guessed.  The mask
		// must be allocated, and initialized to all false
		N = strlen(answer);
		int mask[N];
		for (i=0; i < N; ++i) {
			mask[i] = 0;
		}

		while ((complete == 0) && (life[turn]>0)) {
			print_hangman(life[turn]);
			print_word(mask);
			scan_letter();
			calculate(mask);
		}
		score[turn]++;
		turn = (turn+1)%2;
		round++;
	}

	system("cls");
	if(life[0]<=0){
		printf("Pemenangnya adalah : %s\n", player[(turn+1)%2]);
		printf("Jawabannya adalah \"%s\".\n", answer);
	}

	return 0;
}



void lower_string(char s[]) {
   int c = 0;
   
	while (s[c] != '\0') {
		if (s[c] >= 'A' && s[c] <= 'Z') {
			s[c] = s[c] + 32;
		}
	c++;
	}
}

void print_hangman(int life){
	system("cls");
	printf("\nRonde\t: %d \nGiliran\t: %s \nScore\t: %d - %d \n\n", round, player[turn], score[0], score[1]);
	switch(life){
		case 0:
			printf("       +----------+\n");
			printf("       |          |\n");
			printf("       |          |\n");
			printf("       |         (x)\n");
			printf("       |         /|\\\n");
			printf("       |        | | |\n");
			printf("       |         / \\\n");
			printf("       |        /   \\\n");
			printf("       |        '   '\n");
			printf("       |\n");
			printf("+------+------------------+\n");
			printf("|                         |\n");
			printf("|                         +----+\n");
			printf("|                              |\n");
			printf("+------------------------------+\n");
			break;
		case 1:
			printf("       +----------+\n");
			printf("       |          |\n");
			printf("       |          |\n");
			printf("       |         (.)\n");
			printf("       |         /|\\\n");
			printf("       |        | | |\n");
			printf("       |         / \\\n");
			printf("       |         |_|\n");
			printf("       |         / \\\n");
			printf("       |        /   \\\n");
			printf("+------+------------------+\n");
			printf("|                         |\n");
			printf("|                         +----+\n");
			printf("|                              |\n");
			printf("+------------------------------+\n");
			break;
		case 2:
			printf("       +----------+\n");
			printf("       |          |\n");
			printf("       |          |\n");
			printf("       |         ( )\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("+------+------------------+\n");
			printf("|                         |\n");
			printf("|                         +----+\n");
			printf("|                              |\n");
			printf("+------------------------------+\n");
			break;
		case 3:
			printf("       +----------+\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("+------+------------------+\n");
			printf("|                         |\n");
			printf("|                         +----+\n");
			printf("|                              |\n");
			printf("+------------------------------+\n");
			break;
		case 4:
			printf("       +\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("       |\n");
			printf("+------+------------------+\n");
			printf("|                         |\n");
			printf("|                         +----+\n");
			printf("|                              |\n");
			printf("+------------------------------+\n");
			break;
		case 5:
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");
			printf("+------+------------------+\n");
			printf("|                         |\n");
			printf("|                         +----+\n");
			printf("|                              |\n");
			printf("+------------------------------+\n");
			break;
	}
}

void player_name(){
	printf("Masukkan nama player 1 : ");
	scanf("%s",player[0]);
	printf("Masukkan nama player 2 : ");
	scanf("%s",player[1]);
	system("cls");
}

void init(){
	srand(time(0));
	turn = rand() % 2;
	round = 1;
	life[0] = 5;
	life[1] = 5;
	score[0] = 0;
	score[1] = 0;
}

void scan_word(){
	system("cls");
	printf("\nRonde\t: %d \nGiliran\t: %s \nScore\t: %d - %d \n\n", round, player[(turn+1)%2], score[0], score[1]);
	printf("Masukkan sebuah kata : ");
	fflush(stdout);
	scanf(" %s", answer);
	lower_string(answer);
}

void print_word(int a[]){
	printf("The word is : ");
	for(j=0; j < N; ++j){
		if (a[j]) {
			printf("%c ", answer[j]);
		}else{
			printf("_ ");
		}
	}
	printf("\n");
}

void scan_letter(){
		printf("Masukkan jawaban : ");
		fflush(stdout);
		scanf(" %c", &guess);
		guess = tolower(guess);
}

void calculate(int a[]){
	for(k=0; k < N; ++k) {
		if (answer[k] == guess) {
			a[k] = 1;
			correct = 1;
		}
	}
	if(correct == 0){
		life[turn]--;
	}
	correct = 0;
	
	complete = 1;
	for(m = 0; m < N; ++m) {
		if (!mask[m]) {
			complete = 0;
			break;
		}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <time.h>
//===============================================================================================================================================================================================================================================================// pendefinisian konstanta
#define ARROW_UP 72
#define ARROW_DOWN 80
#define ARROW_RIGHT 77
#define ARROW_LEFT 75
#define ENTER 13
#define ESC 27

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define LLBLUE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define LGREY 7
#define GREY 8
#define LBLUE 9
#define LGREEN 10
#define LLLBLUE 11
#define PINK 12
#define LPURPLE 13
#define LYELLOW 1

#define CONTINUE_POS 0xfff

//===============================================================================================================================================================================================================================================================
char answer[128];
int mask[100];
char guess;
char player[2][16];
int i, j;
int turn;
int round;
int life[2];
int score[2];
int complete;
int attempt;
int correct = 0;
int correct_total;
FILE *fp;

int i,j,k,l,m,N;

typedef struct {
    HANDLE stdInput;
    HANDLE stdOutput;
    HANDLE stdError;
}ALL_HANDLE;
ALL_HANDLE Handle;

//===============================================================================================================================================================================================================================================================
void init();
int menu();
int help();

void fullscreen();
void res(int x, int y);
void get_handle();
void hidecursor();
void y_screensize(int y);
void color(int ForgC, int BackC);
void header();
void footer();
void highlight(int realP, int hlP);
void printimg(char* x, int y);

SYSTEMTIME myTime;
char month[12][5]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

void game(int mode);
void game_init();
void player_name(int a);
void scan_word(int a, int b);
void masking_init();
void lower_string(char s[]);
void print_hangman(int life);
void print_word();
void scan_letter();
void calculate();

//===============================================================================================================================================================================================================================================================
void main() {
	
	init();
	menu();
}

//===============================================================================================================================================================================================================================================================// deklarasi global
void init()
{
	SetConsoleTitle("HangmanGame");
	fullscreen();
	res(1366, 768);
	system("COLOR 0E");
	get_handle();
	srand(time(0));
	hidecursor();
	y_screensize(48);
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t     _    _                                           ____        _   _   _      \n");
	printf("\t\t\t\t\t    | |  | |                                         |  _ \\      | | | | | |     \n");
	printf("\t\t\t\t\t    | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __   | |_) | __ _| |_| |_| | ___ \n");
	printf("\t\t\t\t\t    |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\  |  _ < / _` | __| __| |/ _ \\\n");
	printf("\t\t\t\t\t    | |  | | (_| | | | | (_| | | | | | | (_| | | | | | |_) | (_| | |_| |_| |  __/\n");
	printf("\t\t\t\t\t    |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| |____/ \\__,_|\\__|\\__|_|\\___|\n");
	printf("\t\t\t\t\t                         __/ |                                                   \n");
	printf("\t\t\t\t\t                        |___/    												\n");
	printf("\t\t\t\t\t                                                                         Made by:\n");
	printf("\t\t\t\t\t                                              Qisas Tazkia Hasanudin - 1806200210\n");
	printf("\t\t\t\t\t                                              Edwiansyah Zaky Ashadi - 1806200186\n");  
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t ");
	Sleep(1000);
	color(0, 15);
	printimg("                                                  ",20);
	Sleep(500);
}

//===============================================================================================================================================================================================================================================================//
int menu()
{
    int key = 0;
	int position = 1;
	int maxoption = 4;
    while(key != ENTER){
    	system("cls");
    	y_screensize(48);
    	header();
		printf("\t\t\t\t\t\t\t\t=================================\n");
    	printf("\t\t\t\t\t\t\t\t|           Main Menu           |\n");
    	printf("\t\t\t\t\t\t\t\t=================================\n\n\n\n\n\n");
	    printf("\t\t\t\t\t\t\t\t=================================\n");
		color(14, 0);
		printf("\t\t\t\t\t\t\t\t");
		highlight(1,position);
		printf("|       Play Singleplayer       |\n");
		printf("\t\t\t\t\t\t\t\t");
		highlight(2,position);
		printf("|       Play Multiplayer        |\n");
		printf("\t\t\t\t\t\t\t\t");
		highlight(3,position);
		printf("|             Help              |\n");
		printf("\t\t\t\t\t\t\t\t");
		highlight(4,position);
		printf("|             Exit              |\n");
		color(14, 0);
		printf("\t\t\t\t\t\t\t\t=================================\n");
    	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    	footer();
		
		while((key!=ARROW_DOWN)&&(key!=ARROW_UP)&&(key!=ENTER)){
			key = getch();	
		}
		
		if(key == ARROW_DOWN && position != maxoption){
			position++;
			key = 0;
		}else if(key == ARROW_UP && position != 1){
			position--;
			key = 0;
		}else{
			if(key!=ENTER){
				position = position;
				key = 0;
			}
		}
	}
	switch(position){
		case 1:
			game(1);
			break;
		case 2:
			game(2);
			break;
		case 3:
			help();
			break;
		case 4:
			res(1920, 1080);
        	exit(0);
	}
}

//===============================================================================================================================================================================================================================================================//
int help()
{
	system("cls");
	y_screensize(48);
	header();
	printf("\t\t\t\t\t\t\t\t=================================\n");
    printf("\t\t\t\t\t\t\t\t|         Help section          |\n");
    printf("\t\t\t\t\t\t\t\t=================================\n\n");
	printf("\t\t");
	printf("This game is a multiplayer Hangman classic word game in which you must guess the secret word one letter at a time with folowing rules :");
	printf("\n\n\t\t");
	printf("1. Both players will enter their in nicknames. The game will be started by one of the two players.");
	printf("\n\t\t");
	printf("2. One of the players will give a word to be guessed by another player.");
	printf("\n\t\t");
	printf("3. Guesser needs to guess the word that has been given by the other player, 1 letter at a time, to reveal the secret word.");
	printf("\n\t\t");
	printf("4. Each incorrect guess adds a part to the hangman drawing. You can only make up to 5 incorrect guesses.");
	printf("\n\t\t");
	printf("6. If the guesser manages to find the answer, he/she has to give another word for the other player to guess.");
	printf("\n\t\t");
	printf("7. The game will repeat itself until the guesser fails to guess the word, and the winner is the player who gives the question.");
	printf("\n\n\t\t");
    system("pause");
    return menu();
}

//===============================================================================================================================================================================================================================================================//
void header()
{
	system("COLOR 0E");
	GetSystemTime(&myTime);
	int utc=myTime.wHour+7;
	printf("\n=======================================================================================================================================================================\n");
	printf("\t\t\t\t\t     _    _                                           ____        _   _   _      \n");
	printf("\t\t\t\t\t    | |  | |                                         |  _ \\      | | | | | |     \n");
	printf("\t\t\t\t\t    | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __   | |_) | __ _| |_| |_| | ___ \n");
	printf("\t\t\t\t\t    |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\  |  _ < / _` | __| __| |/ _ \\\n");
	printf("\t\t\t\t\t    | |  | | (_| | | | | (_| | | | | | | (_| | | | | | |_) | (_| | |_| |_| |  __/\n");
	printf("\t\t\t\t\t    |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_| |____/ \\__,_|\\__|\\__|_|\\___|\n");
	printf("\t\t\t\t\t                         __/ |                                                   \n");
	printf("\t\t\t\t\t                        |___/    												\n");
	printf("\t\t\t\t\t                                                                         Made by:\n");
	printf("\t\t\t\t\t                                              Qisas Tazkia Hasanudin - 1806200210\t\t\t    %s %d %d\n",month[(myTime.wMonth)-1],myTime.wDay,myTime.wYear);
	printf("\t\t\t\t\t                                              Edwiansyah Zaky Ashadi - 1806200186\t\t\t     %d:%d WIB\n",(utc>24)?utc-24:utc,myTime.wMinute);
	printf("=======================================================================================================================================================================\n\n");
}

//===============================================================================================================================================================================================================================================================//  
void footer()
{
    color(14, 0);
	printf("\n\n");
	printf(" _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____  _____ \n");
	printf("|  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  ||  _  |\n");
	printf(" )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)(  )(_)( \n");
	printf("|_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____||_____|\n");
}

//===============================================================================================================================================================================================================================================================
void game(int mode){
	int difficulty;
	
	if(mode == 1){
		player_name(mode);
		difficulty = diff();	
		game_init();
		while(life[turn]>0){
			life[0] = 5;
			turn = 0;
			int complete = 0;
			
			scan_word(mode, difficulty);
			masking_init();
	
			while ((complete == 0) && (life[turn]>0)) {
				print_hangman(life[turn]);
				print_word();
				scan_letter();
				calculate();
				
				// menentukan apa jawaban sudah diselesaikan atau belum
				complete = 1;
				for(m = 0; m < N; ++m) {
					if (!mask[m]) {
						complete = 0;
						break;
					}
				}
			}
			
			score[turn]++;
			round++;
		}
	
		system("cls");
		if(life[turn]<=0){
			print_hangman(life[turn]);
			printf("Game Over.");
			printf("Jawabannya adalah \"%s\".\n", answer);
			system("pause");
			menu();
		}
	}
	
	else if(mode == 2){
		player_name(mode);
		game_init();
		while(life[turn]>0){
			life[0] = 5;
			life[1] = 5;
			turn = (turn+1)%2;
			int complete = 0;
			
			scan_word(mode, difficulty);
			masking_init();
	
			while ((complete == 0) && (life[turn]>0)) {
				print_hangman(life[turn]);
				print_word();
				scan_letter();
				calculate();
				
				// menentukan apa jawaban sudah diselesaikan atau belum
				complete = 1;
				for(m = 0; m < N; ++m) {
					if (!mask[m]) {
						complete = 0;
						break;
					}
				}
			}
			
			score[turn]++;
			round++;
		}
	
		system("cls");
		if(life[turn]<=0){
			print_hangman(life[turn]);
			printf("Pemenangnya adalah : %s\n", player[(turn+1)%2]);
			printf("Jawabannya adalah \"%s\".\n", answer);
			system("pause");
			menu();
		}
	}
}

//===============================================================================================================================================================================================================================================================
void game_init(){
	srand(time(0));
	turn = rand() % 2;
	round = 1;
	life[0] = 5;
	life[1] = 5;
	score[0] = 0;
	score[1] = 0;
}

//===============================================================================================================================================================================================================================================================
void player_name(int a){
	system("cls");
	header();
	printf("Masukkan nama player 1 : ");
	scanf("%s",player[0]);
	if(a==2){
		printf("Masukkan nama player 2 : ");
		scanf("%s",player[1]);
	}
	system("cls");
}

//===============================================================================================================================================================================================================================================================
int diff(){
	int a;
	system("cls");
	header();
	printf("Tingkat Kesulitan:\n1. Easy\n2. Medium\n3. Hard\n\nPilih dengan mengetikkan angka : ");
	scanf("%d", &a);
	system("cls");
	return a;
}



//===============================================================================================================================================================================================================================================================
void scan_word(int a, int b){
	system("cls");
	header();
	printf("\nRonde\t: %d \nGiliran\t: %s \nScore\t: %d - %d \n\n", round, player[(turn+1)%2], score[0], score[1]);
	
	switch(a){
		case 1:
			srand(time(0));
			int n;
			switch (b){
				case 1:
					n = rand()%191;
					break;
				case 2:
					n = 191 + rand()%260;
					break;
				case 3:
					n = 260 + rand()%359;
					break;
			}

			fp = fopen("words.txt","r");
			for(i=0; i<n; i++){
				fgets(answer, 128, fp);
			}
			int len = strlen(answer);
			if(answer[len-1]=='\n')
			answer[len-1]='\0';
			break;
		case 2:
			printf("Masukkan sebuah kata : ");
			fflush(stdout);
			scanf(" %s", answer);
			break;
	}

	lower_string(answer);
}

//===============================================================================================================================================================================================================================================================
void lower_string(char s[]) {
   int c = 0;
	while (s[c] != '\0') {
		if (s[c] >= 'A' && s[c] <= 'Z') {
			s[c] = s[c] + 32;
		}
	c++;
	}
}

//===============================================================================================================================================================================================================================================================
void print_hangman(int life){
	system("cls");
	header();
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

//===============================================================================================================================================================================================================================================================
void print_word(){
	printf("\n");
	for(j=0; j < N; ++j){
		if (mask[j] == 1) {
			printf("%c ", answer[j]);
		}else{
			printf("_ ");
		}
	}
	printf("\n");
}

//===============================================================================================================================================================================================================================================================
void masking_init(){
	N = strlen(answer);
		for (i=0; i < N; ++i) {
			mask[i] = 0;
		}
}

//===============================================================================================================================================================================================================================================================
void scan_letter(){
		printf("Masukkan jawaban : ");
		fflush(stdout);
		scanf(" %c", &guess);
		guess = tolower(guess);
}

//===============================================================================================================================================================================================================================================================
void calculate(){
	for(k=0; k < N; ++k) {
		if (answer[k] == guess) {
			mask[k] = 1;
			correct = 1;
		}
	}
	if(correct == 0){
		life[turn]--;
	}
	correct = 0;
}

//===============================================================================================================================================================================================================================================================//
void fullscreen()
{
keybd_event(VK_MENU,0x38,0,0);
keybd_event(VK_RETURN,0x1c,0,0);
keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}

void res(int x, int y)
{
	DEVMODE devmode;
	devmode.dmPelsWidth = x;
	devmode.dmPelsHeight = y;
	devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
	devmode.dmSize = sizeof(DEVMODE);
	ChangeDisplaySettings(&devmode, 0);
}

void get_handle()
{
    Handle.stdInput=GetStdHandle(STD_INPUT_HANDLE);
    Handle.stdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    Handle.stdError=GetStdHandle(STD_ERROR_HANDLE);
}

void hidecursor()
{
	CONSOLE_CURSOR_INFO info;
    info.dwSize=100;
    info.bVisible=FALSE;
    SetConsoleCursorInfo(Handle.stdOutput,&info);
}

void y_screensize(int y)
{
   	CONSOLE_SCREEN_BUFFER_INFO info;
   	GetConsoleScreenBufferInfo(Handle.stdOutput, &info);
   	COORD new_size = {info.srWindow.Right-info.srWindow.Left+1, y};
   	SetConsoleScreenBufferSize(Handle.stdOutput, new_size);
}

void color(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

void printimg(char* x, int y)
{
	int i;
	for(i=0;i<strlen(x);i++){
		printf("%c",x[i]);
		Sleep(y);
	}
}

void highlight(int realP, int hlP)
{
	if(realP == hlP){
		color(0, 15);
	}else{
		color(14, 0);
	}
}

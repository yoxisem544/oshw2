#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
// LIBS += -lcurses
//for getch in unix
#include <termios.h>
#include <unistd.h>
//thread
#include <pthread.h>

int G_x, G_y;
int r_p_p = 10, l_p_p = 10;
int yo;
int dir_x = 2, dir_y = 1;
WINDOW *field;
int ball_speed = 50000;
int yar,yal;
char c[64];
int r_s = 0, l_s = 0;
int offset = 10;
int shifting = 0;
void int2str(int i, char *s) {
  sprintf(s,"%d",i);
}
//getch in linux by my self......
int _getch(){
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
void clean_field(WINDOW *screen)
{
	int x, y, i, j;
	getmaxyx(screen, y, x);

	for (i = 1; i < x - 1 ; i++)
	{
		for (j = 1; j < y - 1; j++)
		{
			mvwprintw(screen, j, i, " ");
		}
	}
	for (i = 1; i <= 24; i++)
		mvwprintw(screen, i, 40, "|");
	//score
	int2str(r_s,c);
	mvwprintw(screen, 1, 40-3, c);	
	int2str(l_s,c);
	mvwprintw(screen, 1, 40+3, c);

	//draw picture
	srand(time(NULL));
	mvwprintw(screen, (offset)%23+2, 10+shifting, " _____     _     _        _____                _     ");
	mvwprintw(screen, (1+offset)%23+2, 10+shifting, "|_   _|   | |   | |      |_   _|              (_)    ");
	mvwprintw(screen, (2+offset)%23+2, 10+shifting, "  | | __ _| |__ | | ___    | | ___ _ __  _ __  _ ___ ");
	mvwprintw(screen, (3+offset)%23+2, 10+shifting, "  | |/ _` | '_ \\| |/ _ \\   | |/ _ \\ '_ \\| '_ \\| / __|");
	mvwprintw(screen, (4+offset)%23+2, 10+shifting, "  | | (_| | |_) | |  __/   | |  __/ | | | | | | \\__ \\");
	mvwprintw(screen, (5+offset)%23+2, 10+shifting, "  \\_/\\__,_|_.__/|_|\\___|   \\_/\\___|_| |_|_| |_|_|___/");
	offset += 1;
	shifting = rand()%10;
	usleep(25000);
}

void draw_borders(WINDOW *screen) {
	int x, y, i;
	getmaxyx(screen, y, x);
	// 4 corners 角
	mvwprintw(screen, 0, 0, "+");
	mvwprintw(screen, y - 1, 0, "+");
	mvwprintw(screen, 0, x - 1, "+");
	mvwprintw(screen, y - 1, x - 1, "+");
	// sides 邊
	for (i = 1; i < (y - 1); i++) {
	  mvwprintw(screen, i, 0, "|");
	  mvwprintw(screen, i, x - 1, "|");
	}
	// top and bottom
	for (i = 1; i < (x - 1); i++) {
	  mvwprintw(screen, 0, i, "-");
	  mvwprintw(screen, y - 1, i, "-");
	}
}

void draw_ball(WINDOW *screen)
{
	int x, y, i;
	getmaxyx(screen, y, x);
	
	//draw ball
	mvwprintw(screen, G_y, G_x, "@");
}
void draw_player(WINDOW *screen)
{
	int x, y, i;
	getmaxyx(screen, y, x);
	
	//draw ball
	mvwprintw(screen, r_p_p, 2, "{");
	mvwprintw(screen, r_p_p-1, 2, "{");
	mvwprintw(screen, r_p_p+1, 2, "{");
	mvwprintw(screen, r_p_p-2, 2, "{");
	mvwprintw(screen, r_p_p+2, 2, "{");

	mvwprintw(screen, l_p_p, 80, "}");
	mvwprintw(screen, l_p_p-1, 80, "}");
	mvwprintw(screen, l_p_p+1, 80, "}");
	mvwprintw(screen, l_p_p-2, 80, "}");
	mvwprintw(screen, l_p_p+2, 80, "}");
}
void i_m_keyboard()
{
	while(1)
	{
		yo = _getch();
		if (yo == 'r' || yo == 'R')
			ball_speed += 10000;
		if (yo == 't' || yo == 'T')
			if (ball_speed <= 10000)
				ball_speed = 20000;
			else
				ball_speed -= 10000;
		if (yo == 'w' || yo == 'W') yar = yo;
		if (yo == 's' || yo == 'S') yar = yo;
		if (yo == 'i' || yo == 'I') yal = yo;
		if (yo == 'k' || yo == 'K') yal = yo;
	}
}

void r_player()
{
	while(1)
	{
		if (yar == 'w' || yar == 'W' || yar == 'S' || yar == 's')
		{
			if (yar == 'w' || yar == 'W')
			{ // move up
				if (r_p_p <= 3)
					r_p_p = 3;
				else
					r_p_p -= 1;
			}
			else if (yar == 's' || yar == 'S')
			{
				if (r_p_p >= 22)
					r_p_p = 22;
				else
					r_p_p += 1; // move down
			}
			yar = ' ';
			usleep(50000);
		}
	}
}
void l_player()
{
	while(1)
	{
		if (yal == 'i' || yal == 'I' || yal == 'k' || yal == 'K')
		{
			if (yal == 'i' || yal == 'I')
			{ // move up
				if (l_p_p <= 3)
					l_p_p = 3;
				else
					l_p_p -= 1;
			}
			else if (yal == 'k' || yal == 'K')
			{
				if (l_p_p >= 22)
					l_p_p = 22;
				else
					l_p_p += 1; // move down
			}
			yal = ' ';
			usleep(50000);
		}
	}
}
//counting position thread 
void position()
{
	int i = 0;
	while(1)
	{	
		if (G_x == 0) 
		{
			G_x = 1;
		}
		if (G_y == 0) G_y = 1;
		if (G_x > 81) 
		{ 
			G_x = G_x/81;
		}
		G_x += dir_x;
		if (G_y > 24) G_y = G_y/24;
		G_y += dir_y;
		//change direction

		//verify hitting
		if (G_x == 3)
		{
			int helloworld = abs(r_p_p - G_y);
			if (helloworld <= 3)
			{
				//hit player
				dir_x *= (-1);
			}
		}
		else if (G_x == 79)
		{
			int helloworld = abs(l_p_p - G_y);
			if (helloworld <= 3)
			{
				//hit player
				dir_x *= (-1);
			}
		}

		//hit wall
		if (G_x >= 81 || G_x == 1) 
		{
			dir_x *= (-1);
			// scoring region
			if (G_x >= 81) r_s += 1;
			if (G_x <= 1)  l_s += 1;
		}
		srand(time(NULL));
		if (G_y == 24 || G_y == 1)
		{ 
			dir_y *= (-1);
		}
		usleep(ball_speed);
	}
	printf("end of position thread for debugging.\n");
}

int main()
{
	int parent_x = 20, parent_y = 50;
	int a;
	//thread
		pthread_t id, id_for_keyboard, l_id, r_id, r_key, l_key;
        int i,ret;
	//
	initscr();
	noecho();
	curs_set(FALSE);
	// get our maximum window dimensions
	//stdscr i think in this.screen......
	printf("Game will start in a 1 second!\n");
	getmaxyx(stdscr, parent_y, parent_x);
	// set up initial windows
	field = newwin(parent_y, parent_x, 0, 0);
	
	// draw to our windows
	mvwprintw(field, 0, 0, "Field");
	// refresh each window
	wrefresh(field);
	sleep(1);

	//thread region
    ret = pthread_create(&id,NULL,(void *)position,NULL);
    if (ret != 0)
    {
        printf("Create thread error!\r\n");
        exit(1);
    }
    ret = pthread_create(&id_for_keyboard, NULL, (void *)i_m_keyboard, NULL);
    if (ret != 0)
    {
    	printf("Create thread error!\r\n");
        exit(1);
    }
    ret = pthread_create(&r_id, NULL, (void *)r_player, NULL);
    if (ret != 0)
    {
    	printf("Create thread error!\r\n");
        exit(1);
    }
    ret = pthread_create(&l_id, NULL, (void *)l_player, NULL);
    if (ret != 0)
    {
    	printf("Create thread error!\r\n");
        exit(1);
    }
    
	//--------

	// draw our borders
	draw_borders(field);
	// simulate the game loop
	while(1) {
		// draw to our windows
		mvwprintw(field, 1, 1, "Field");
		clean_field(field);
		draw_player(field);
		draw_ball(field);
	  	// refresh each window
	    wrefresh(field);
	}

	return 0;
}
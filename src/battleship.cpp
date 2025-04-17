#include "logic/board.hpp"
#include "game.hpp"

void initNcurses()
{
    initscr();
	cbreak();
	refresh();
	noecho();
	setlocale(LC_ALL,"");
}

void initPair()
{
	init_pair(0, COLOR_BLACK, -1);
#if defined(_WIN32)
	init_pair(1, COLOR_BLUE, -1);
	init_pair(4, COLOR_RED, -1);
	init_pair(3, COLOR_CYAN, -1);
	init_pair(6, COLOR_YELLOW, -1);
#else
	init_pair(1, COLOR_RED, -1);
	init_pair(4, COLOR_BLUE, -1);
	init_pair(3, COLOR_YELLOW, -1);
	init_pair(6, COLOR_CYAN, -1);
#endif
	init_pair(2, COLOR_GREEN, -1);
	init_pair(5, COLOR_MAGENTA, -1); 
    init_pair(7, COLOR_WHITE, -1);
}

int main()
{
    initNcurses();
    if(!has_colors())
	{
		endwin();
		printf("Your terminal does not support color\n");
		return -1;
	}
	start_color();
	use_default_colors();
	initPair();
	
    Game game;
    game.run();

    endwin();
    return 0;
}
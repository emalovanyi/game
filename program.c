#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define N 10

struct Object{
    int xpos;
    int ypos;

    unsigned char zone;
    chtype zone_1;
};

struct Object obj[N] = {};

int wbox = 0;
int lev = 0;

//function_with_colors
void design(){
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

//function_with_maps
void maps(int *height, int *width, int *ar, int y, int x, int j){

    //test_map
    if(j == 0){
        *height = 7;
        *width =  9;
        int map_0[7][9] = {
            {1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,1},
            {1,2,0,3,0,3,0,2,1},
            {1,0,0,0,4,0,0,0,1},
            {1,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1}
        };
        *ar = map_0[y][x];
    }

    //map_1
    if(j == 1){
        *height = 8;
        *width = 8;
        int map_1[8][8] = {
            {0,0,1,1,1,1,1,1},
            {1,1,1,0,0,0,0,1},
            {1,0,4,0,3,3,0,1},
            {1,1,1,1,1,0,0,1},
            {1,2,1,2,1,0,0,1},
            {1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1},
        };
        *ar = map_1[y][x];
    }

    //map_2
    if(j == 2){
        *height = 8;
        *width = 9;
        int map_2[8][9] = {
            {0,0,1,1,1,1,0,0,0},
            {0,0,1,2,0,1,0,0,0},
            {0,0,1,0,0,1,1,1,1},
            {1,1,1,0,3,0,3,2,1},
            {1,2,0,0,3,0,1,1,1},
            {1,1,1,1,0,0,1,0,0},
            {0,0,0,1,0,4,1,0,0},
            {0,0,0,1,1,1,1,0,0},
        };
        *ar = map_2[y][x];

    }

    //map_3
    if(j == 3){
        *height = 7;
        *width = 8;
        int map_3[7][8] = {
            {1,1,1,1,1,1,1,1},
            {1,0,0,1,0,0,4,1},
            {1,0,0,0,3,1,0,1},
            {1,2,3,3,0,2,0,1},
            {1,0,1,2,1,3,1,1},
            {1,0,0,2,0,0,1,0},
            {1,1,1,1,1,1,1,0},
        };
        *ar = map_3[y][x];
    }
}

//fuction_with_characters
void character(int c){
    clear();

    int ct_1_y = 12;
    int ct_2_x = 6;

    attron(COLOR_PAIR(2));
    mvprintw(2,9, "Level -> %d", lev);
    attron(COLOR_PAIR(2));
    mvprintw(ct_1_y, ct_2_x, "Move -> W, S, A, D");
    attron(COLOR_PAIR(5));
    mvprintw(6, 40, "New game -> N");
    mvprintw(7, 40, "Level -> L");
    mvprintw(8, 40, "Exit -> E");

    int x = 0;
    int y = 0;
    int height = 1;
    int width = 1;
    int charact;

    wbox = 0;

    for(y = 0; y < height; y++){
        for(x = 0; x < width; x++){
            maps(&height, &width, &charact, y, x, c);
            switch(charact){

                case 0:
                    attron(COLOR_PAIR(3));
                    mvaddch(y + 4, x + 10, '-');
                    break;

                case 1:
                    attron(COLOR_PAIR(1));
                    mvaddch(y + 4, x + 10, '#');
                    break;

                case 2:
                    attron(COLOR_PAIR(2));
                    mvaddch(y + 4, x + 10, 'x');
                    break;

                case 3:
                    attron(COLOR_PAIR(3));
                    mvaddch(y + 4, x + 10, '-');
                    wbox += 1;
                    obj[wbox].zone_1 = mvinch(y + 4, x + 10);
                    obj[wbox].ypos = y + 4;
                    obj[wbox].xpos = x + 10;
                    obj[wbox].zone = '@';
                    attron(COLOR_PAIR(4));
                    mvaddch(obj[wbox].ypos, obj[wbox].xpos, obj[wbox].zone);
                    break;

                case 4:
                    attron(COLOR_PAIR(3));
                    mvaddch(y + 4, x + 10, '-');
                    obj[0].zone_1 = mvinch(y + 4, x + 10);
                    obj[0].ypos = y + 4;
                    obj[0].xpos = x + 10;
                    obj[0].zone = 'A';
                    attron(COLOR_PAIR(4));
                    mvaddch(obj[0].ypos, obj[0].xpos, obj[0].zone);
                    break;
            }
        }
    }
    move(obj[0].ypos, obj[0].xpos);
}

//function_with_game
void game(int input){
   int t;

   bool restart = FALSE;

   chtype up;
   chtype left;
   chtype down;
   chtype right;
   chtype up_1;
   chtype left_1;
   chtype down_1;
   chtype right_1;

   up = (mvinch(obj[0].ypos - 1, obj[0].xpos) & A_CHARTEXT);
   up_1 = (mvinch(obj[0].ypos - 2, obj[0].xpos) & A_CHARTEXT);

   left = (mvinch(obj[0].ypos, obj[0].xpos - 1) & A_CHARTEXT);
   left_1 = (mvinch(obj[0].ypos, obj[0].xpos - 2) & A_CHARTEXT);

   down = (mvinch(obj[0].ypos + 1, obj[0].xpos) & A_CHARTEXT);
   down_1 = (mvinch(obj[0].ypos + 2, obj[0].xpos) & A_CHARTEXT);

   right = (mvinch(obj[0].ypos, obj[0].xpos + 1) & A_CHARTEXT);
   right_1 = (mvinch(obj[0].ypos, obj[0].xpos + 2) & A_CHARTEXT);

   for(t = 0; t <= wbox; t++){
      mvaddch(obj[t].ypos, obj[t].xpos, obj[t].zone_1);
   }

   switch(input){


        case 'l':
        case 'L':
        restart = TRUE;
        if(lev < 3){
            lev +=1;
        }
        else{
            lev = 0;
        }
        character(lev);
        break;

        case 'n':
        case 'N':
        restart = TRUE;
        character(lev);
        break;



        case 'w':
        case 'W':
        if(up != 35){

                        if(up != 64){
                                obj[0].ypos = obj[0].ypos - 1;
                        }

            if(up == 64 && (up_1 == 45 || up_1 == 120)){
                obj[0].ypos = obj[0].ypos - 1;
                for(t = 1; t <= wbox; t++){
                    if((obj[0].ypos == obj[t].ypos) && (obj[0].xpos == obj[t].xpos)){
                        obj[t].ypos = obj[0].ypos - 1;
                    }
                }
            }
        }
        break;

        case 'a':
        case 'A':
        if(left != 35){

            if(left != 64){
                obj[0].xpos = obj[0].xpos - 1;
            }

            if(left == 64 && (left_1 == 45 || left_1 == 120)){
                obj[0].xpos = obj[0].xpos - 1;
                for(t = 1; t <= wbox; t++){
                    if((obj[0].ypos == obj[t].ypos) && (obj[0].xpos == obj[t].xpos)){
                        obj[t].xpos = obj[0].xpos - 1;
                    }
                }
            }
        }
        break;


        case 's':
        case 'S':
        if(down != 35){

            if(down != 64){
                obj[0].ypos = obj[0].ypos + 1;
            }

            if(down == 64 && (down_1 == 45 || down_1 == 120)){
                obj[0].ypos = obj[0].ypos + 1;
                for(t = 1; t <= wbox; t++){
                    if((obj[0].ypos == obj[t].ypos) && (obj[0].xpos == obj[t].xpos)){
                        obj[t].ypos = obj[0].ypos + 1;
                    }
                }
            }
        }
        break;

        case 'd':
        case 'D':
        if(right != 35){

            if(right != 64){
                obj[0].xpos = obj[0].xpos + 1;
            }

            if(right == 64 && (right_1 == 45 || right_1 == 120)){
                obj[0].xpos = obj[0].xpos + 1;
                for(t = 1; t <= wbox; t++){
                    if((obj[0].ypos == obj[t].ypos) && (obj[0].xpos == obj[t].xpos)){
                        obj[t].xpos = obj[0].xpos + 1;
                    }
                }
            }
        }
        break;

   }

   if(!restart){
        for(t = 0; t <= wbox; t++){
            obj[t].zone_1 = mvinch(obj[t].ypos, obj[t].xpos);
            mvaddch(obj[t].ypos, obj[t].xpos, obj[t].zone | ((t == 0) ? COLOR_PAIR(3) : COLOR_PAIR(4)));
        }
        move(obj[0].ypos, obj[0].xpos);
   }
   else{
        restart = FALSE;
   }
}

int main(){
    int i;

    initscr();
        keypad(stdscr, TRUE);
    start_color();
    design();
    character(lev);

        while ((i = getch()) != 'e')
    {
        game(i);
    }

    endwin();

    return 0;
}

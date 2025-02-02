#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <locale.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>

#include "main_page.h"
#include "globals.h"


#define WIDTH 200
#define HEIGHT 60
#define start_red wattron(game_win, COLOR_PAIR(1))
#define finish_red wattroff(game_win, COLOR_PAIR(1))
#define start_yellow wattron(game_win, COLOR_PAIR(2))
#define finish_yellow wattroff(game_win, COLOR_PAIR(2))
#define yellow1 wattron(message_win, COLOR_PAIR(2))
#define yellow2 wattroff(message_win, COLOR_PAIR(2))
#define start_blue wattron(game_win, COLOR_PAIR(3))
#define finish_blue wattroff(game_win, COLOR_PAIR(3))
#define start_white wattron(game_win, COLOR_PAIR(4))
#define finish_white wattroff(game_win, COLOR_PAIR(4))
#define start_gray wattron(game_win, COLOR_PAIR(5))
#define finish_gray wattroff(game_win, COLOR_PAIR(5))
#define start_green wattron(game_win, COLOR_PAIR(6))
#define finish_green wattroff(game_win, COLOR_PAIR(6))
#define start_magenta wattron(game_win, COLOR_PAIR(7))
#define finish_magenta wattroff(game_win, COLOR_PAIR(7))
#define start_cyan wattron(game_win, COLOR_PAIR(8))
#define finish_cyan wattroff(game_win, COLOR_PAIR(8))
#define bold1 attron(A_BOLD)
#define bold2 attroff(A_BOLD)
#define message_box wattron(message_win , COLOR_PAIR(8)); box(message_win, '|', '-') ; wattroff(message_win , COLOR_PAIR(8))
#define draw_karbar start_blue; bold1 ; mvwaddch(game_win , y , x , '@'); finish_blue; bold2; karbar.y = y; karbar.x = x
#define enemy1 move_enemy(y , x)
#define check1 check_location (int y , int x)
#define poor start_green; mvwaddch(game_win , karbar.y ,karbar.x , '.'); finish_green; map[y][x] = 0

const char* gold_icon = "\u0024";//
const char* dimond_icon = "\u0024";
const char* obstacles_icon = "O"; //
const char* mace_icon = "\u26CF";
const char* sword_icon = "S";
const char* knife_icon = "K";
const char* wand_icon = "W";//
const char* arrow_icon = "A";//
const char* bad_food_icon = "F";//
const char* normal_food_icon = "F";//
const char* magic_food_icon = "F"; //
const char* golden_food_icon = "★";//
const char* powerـtalisman_icon = "~";
const char* health_talisman_icon = "\u2764";//
const char* speed_talisman_icon = "&";
const char* deamon_icon = "D";//
const char* Fire_Breathing_Monster_icon = "M";//
const char* Giant_icon = "G";
const char* Snake_icon = "S";
const char* Undead_icon = "U";

int map[80][210] = {{-1}} , x , adad , timer = 0 , damage = 0 , speed = 0 ;
int num_deamon=0 , num_fire=0 , num_giant=0 , num_snake=0 , num_undead=0;

WINDOW *game_win;
WINDOW *message_win;
WINDOW *detail_win;

typedef struct {
    int x, y, width, height;
    int door_x, door_y;
} Room;
Room number[10];
typedef struct {
    int weapon ;
    int x , y ;
    int gold , dimond ;
    int bad_food , normal_food , magic_food , golden_food;
    bool mace , sword ; 
    int dagger , wand , arrow ;
    int health_talisman , power_talisman , speed_talisman ;
    int in_room_number , floor ;
} human;
human karbar;
typedef struct {
    int x , y , health, move;
} st1;
st1 Deamon[10];
typedef struct {
    int x , y , health , move;
} st2;
st2 Fire_Breathing_Monster[10];
typedef struct {
    int x , y , health , move;
} st3;
st3 Giant[10];
typedef struct {
    int x , y , health , move;
} st4;
st4 snake[10];
typedef struct {
    int x , y , health , move;
} st5;
st5 undead[10];
void megdar(){
    for (int i = 0 ; i < 210; i++) {
        for (int j = 0; j < 80; j++) {
            map[j][i] = -1 ;
        }
    }
}
void initialize () {
    karbar.x = 95 ; karbar.y = 55;
    karbar.gold = 0 ; karbar.dimond = 0;
    karbar.bad_food = 0; karbar.golden_food = 0 ; 
    karbar.normal_food = 0 ; karbar.magic_food = 0;
    karbar.mace = true ; karbar.sword = false ;
    karbar.dagger = 0 ; karbar.wand = 0;
    karbar.arrow = 0 ; karbar.health_talisman = 0;
    karbar.power_talisman = 0 ; karbar.speed_talisman = 0;
    karbar.in_room_number = 0 ; karbar.weapon = 1 ;
    karbar.floor = 1 ;
}
int check_room ( int i ) {

    for ( int j = 0 ; j < i ; j++){

        if (number[j].x <= number[i].x+5 &&
            number[j].x + number[j].width >= number[i].x-5 &&
            number[j].y <= number[i].y+5 &&
            number[j].y + number[j].height >= number[i].y-5)
                return 0 ;

        else if (number[j].x <= number[i].x+5 &&
            number[j].x + number[j].width >= number[i].x-5 &&
            number[j].y <= number[i].y + number[i].height+5 &&
            number[j].y + number[j].height >= number[i].y + number[i].height-5 )
                return 0 ;

        else if (number[j].x <= number[i].x + number[i].width+5 &&
            number[j].x + number[j].width >= number[i].x + number[i].width-5 &&
            number[j].y <= number[i].y+5 &&
            number[j].y + number[j].height >= number[i].y-5 )
                return 0 ;

        else if (number[j].x <= number[i].x + number[i].width+5 &&
            number[j].x + number[j].width >= number[i].x + number[i].width-5 &&
            number[j].y <= number[i].y + number[i].height+5 &&
            number[j].y + number[j].height >= number[i].y + number[i].height-5) 
                return 0 ;
    }
    return 1 ;
}
void draw_room(int n) {

    for ( int i = number[n].x ; i <= number[n].x + number[n].width ; i++){

        for ( int j = number[n].y ; j <= number[n].y + number[n].height ; j++){

            if (j == number[n].y || j == number[n].y + number[n].height){
                mvwaddch(game_win , j , i , '-');
                map [j][i] = 1 ;
            }
            else if (i == number[n].x || i == number[n].x + number[n].width){
                mvwaddch(game_win , j , i , '|');
                map [j][i] = 10;
            }
            else {
                mvwaddch(game_win , j , i , '.');
                map [j][i] = 0 ;
            }
        }
    }
    // قرار دادن در روی یکی از دیوارهای اتاق
    int wall = rand() % 4;
    if (wall == 0) { // دیوار بالا
        number[n].door_x = number[n].x + rand() % number[n].width;
        number[n].door_y = number[n].y;
    } else if (wall == 1) { // دیوار پایین
        number[n].door_x = number[n].x + rand() % number[n].width;
        number[n].door_y = number[n].y + number[n].height;
    } else if (wall == 2) { // دیوار چپ
        number[n].door_x = number[n].x;
        number[n].door_y = number[n].y + rand() % number[n].height;
    } else { // دیوار راست
        number[n].door_x = number[n].x + number[n].width;
        number[n].door_y = number[n].y + rand() % number[n].height;
    }
    mvwaddch(game_win, number[n].door_y, number[n].door_x, '+');
    map[number[n].door_y][number[n].door_x] = 3;
}
void create_room_1 (){

    number[0].x = 85 ;
    number[0].y = 50 ;
    number[0].width = 20 ;
    number[0].height = 10 ;
}
int create_rooms(int d ) {

    int rooms_number = rand() % 2 + 5 ; if ( d == 2 ) rooms_number += 2 ;

    for ( int i = 1 ; i < rooms_number ; i++){

        number[i].width = rand() % 25 + 10 ;
        number[i].x = rand() % (170 - number[i].width) + 10 ;
        number[i].height = rand() % 25 + 10 ;
        number[i].y = rand() % (50 - number[i].height) + 5 ;
        if ((i == 4 || i == 3) && number[i].height*number[i].width < 250) i--;
        else if (!check_room(i)) i--;
    }
    return rooms_number;
}
void draw_corridor(int x1, int y1, int x2, int y2) {
    int intermediate_x = x1;
    int intermediate_y = y1;

    while (intermediate_x != x2) {
        if (mvwinch(game_win, intermediate_y, intermediate_x) == ' ') {
            mvwaddch(game_win, intermediate_y, intermediate_x, '#');
            map[intermediate_y][intermediate_x] = 2;
        }
        intermediate_x += (x2 > intermediate_x) ? 1 : -1;
    }

    while (intermediate_y != y2) {
        if (mvwinch(game_win, intermediate_y, intermediate_x) == ' ') {
            mvwaddch(game_win, intermediate_y, intermediate_x, '#');
            map[intermediate_y][intermediate_x] = 2;
        }
        intermediate_y += (y2 > intermediate_y) ? 1 : -1;
    }
}
void connect_rooms(int total_rooms) {
    for (int i = 0; i < total_rooms - 1; i++) {
        int x1 = number[i].door_x;
        int y1 = number[i].door_y;
        int x2 = number[i + 1].door_x;
        int y2 = number[i + 1].door_y;

        draw_corridor(x1, y1, x2, y2);
    }
    draw_corridor(number[total_rooms-1].door_x, number[total_rooms-1].door_y , number[0].door_x, number[0].door_y);
}
void place_doors_on_walls(int num_rooms) {

    for (int i = 0; i < num_rooms; i++) {
        for (int x = number[i].x; x <= number[i].x + number[i].width; x++) {
            for (int y = number[i].y; y <= number[i].y + number[i].height; y++) {
                chtype ch = mvwinch(game_win, y , x)& A_CHARTEXT;
                if ((ch == '+') && ((mvwinch(game_win , y - 1, x)& A_CHARTEXT) == '#' || (mvwinch(game_win , y + 1, x)& A_CHARTEXT) == '#' ||
                    (mvwinch(game_win , y, x - 1)& A_CHARTEXT) == '#' || (mvwinch(game_win , y, x + 1)& A_CHARTEXT) == '#')) {
                    start_white;
                    mvwaddch(game_win , y, x, '+'); map[y][x] = 3 ;
                    finish_white;
                }
                else if ((ch == '+') &&
                        (((mvwinch(game_win , y - 1, x)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y - 1, x)& A_CHARTEXT) == '.' || (mvwinch(game_win , y - 1, x)& A_CHARTEXT)== '|') &&
                        ((mvwinch(game_win , y + 1, x)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y + 1, x)& A_CHARTEXT) == '.' || (mvwinch(game_win , y + 1, x)& A_CHARTEXT) == '|') &&
                        ((mvwinch(game_win , y, x - 1)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y, x - 1)& A_CHARTEXT) == '.' ) && 
                        ((mvwinch(game_win , y, x + 1)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y, x + 1)& A_CHARTEXT) == '.' ))){
                    start_green;
                    mvwaddch(game_win , y, x, '|'); map[y][x] = 10 ;
                    finish_green;
                }
                else if ((ch == '+') &&
                        (((mvwinch(game_win , y - 1, x)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y - 1, x)& A_CHARTEXT) == '.' ) &&
                        ((mvwinch(game_win , y + 1, x)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y + 1, x)& A_CHARTEXT) == '.' ) &&
                        ((mvwinch(game_win , y, x - 1)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y, x - 1)& A_CHARTEXT) == '.' || (mvwinch(game_win , y, x - 1)& A_CHARTEXT) == '-' ) && 
                        ((mvwinch(game_win , y, x + 1)& A_CHARTEXT) == ' ' || (mvwinch(game_win , y, x + 1)& A_CHARTEXT) == '.' || (mvwinch(game_win , y, x + 1)& A_CHARTEXT) == '-'))){
                    start_green;
                    mvwaddch(game_win , y, x, '-'); map[y][x] = 1 ;
                    finish_green;
                } else if ((ch == '-' || ch == '|') &&
                        ((mvwinch(game_win , y - 1, x)& A_CHARTEXT) == '#'||
                        (mvwinch(game_win , y + 1, x)& A_CHARTEXT) == '#' ||
                        (mvwinch(game_win , y, x - 1)& A_CHARTEXT) == '#' ||
                        (mvwinch(game_win , y, x + 1)& A_CHARTEXT) == '#' )){
                    start_white;
                    mvwaddch(game_win , y, x, '+'); map[y][x] = 3 ;
                    finish_white;
                }
            }
        }
    }
}
void add_obstacles(int num_rooms) {

    for (int i = 0; i < num_rooms; i++) {

        int num_obstacles = rand() % 3 ; 
       
        for (int j = 0; j < num_obstacles; j++) {
            
            int x = number[i].x + 2 + rand() % (number[i].width - 3) ;
            int y = number[i].y + 2 + rand() % (number[i].height - 3);
            mvwprintw(game_win , y , x , "%s" , obstacles_icon); 
            map [y][x] = 5 ;
        }
    }
    wrefresh(game_win);
}
void add_ladder(int floor) {

    int i = 1 ; 
    if ( floor == 1 ) return ;         
    int x = number[i].x + 2 + rand() % (number[i].width - 3) ;
    int y = number[i].y + 2 + rand() % (number[i].height - 3);
    bold1 ; 
    mvwaddch(game_win , y , x , '<'); bold2 ;
    map [y][x] = 6 ;
        
    wrefresh(game_win);
}
void add_ladder2(int floor) {

    if ( floor != 4 ){ 
    int i = rand() % 5 + 1 ;
    int x = number[i].x + 2 + rand() % (number[i].width - 3) ;
    int y = number[i].y + 2 + rand() % (number[i].height - 3);
    start_blue; bold1 ;
    mvwaddch(game_win , y , x , '<'); finish_blue; bold2 ;
    map [y][x] = 7 ;
    wrefresh(game_win);
    }
}
void add_dimond (int num_rooms ) {
    start_yellow;
    for (int i = 0; i < num_rooms; i++) {

        int num_obstacles = rand() % 2 ; 
       
        for (int j = 0; j < num_obstacles; j++) {
            
            int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
            int y = number[i].y + 3 + rand() % (number[i].height - 6);
            mvwprintw(game_win, y, x, "%s" , dimond_icon );
            map [y][x] = 12 ; 
        }
    } finish_yellow;
    wrefresh(game_win);
}
void add_gold (int num_rooms ) {

    for (int i = 0; i < num_rooms; i++) {

        int num_obstacles = rand() % 3 ; 
       
        for (int j = 0; j < num_obstacles; j++) {
            
            int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
            int y = number[i].y + 3 + rand() % (number[i].height - 6);
            mvwprintw(game_win, y, x, "%s" , gold_icon );
            map [y][x] = 11 ; 
        }
    }
    wrefresh(game_win);
}
void add_trap (int num_rooms ) {

    for (int i = 0; i < num_rooms; i++) {

        int num_obstacles = rand() % 6 + 1 ; 
       
        for (int j = 0; j < num_obstacles; j++) {
            
            int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
            int y = number[i].y + 3 + rand() % (number[i].height - 6);
            if (!map[y][x]){
                map [y][x] = 4 ; 
                wrefresh(game_win);
            }
            else j--;
        }
    }
}
void add_dagger (int num_rooms ) {
    start_white;
    int k = rand() % (num_rooms-1) ;
    if ( k == 4 ) add_dagger (num_rooms);
    else {
        int x = number[k].x + 3 + rand() % (number[k].width - 6) ;
        int y = number[k].y + 3 + rand() % (number[k].height - 6);
        if (!map[y][x]){
            map [y][x] = 13 ;
            mvwprintw(game_win, y, x, "%s" , knife_icon ); 
            wrefresh(game_win);
        }
        else add_dagger(num_rooms);
    } finish_white;
}
void add_wand (int num_rooms ) {
    start_white;
    int k = rand() % (num_rooms-1) ;
    if ( k == 4 ) add_wand (num_rooms);
    else {
        int x = number[k].x + 3 + rand() % (number[k].width - 6) ;
        int y = number[k].y + 3 + rand() % (number[k].height - 6);
        if (!map[y][x]){
            map [y][x] = 14 ; 
            mvwprintw(game_win, y, x, "%s" , wand_icon );
            wrefresh(game_win);
        }
        else add_wand(num_rooms);
    } finish_white;
}
void add_arrow (int num_rooms ) {
    start_white;
    int k = rand() % (num_rooms-1) ;
    if ( k == 4 ) add_arrow (num_rooms);
    else {
        int x = number[k].x + 3 + rand() % (number[k].width - 6) ;
        int y = number[k].y + 3 + rand() % (number[k].height - 6);
        if (!map[y][x]){
            map [y][x] = 15 ; 
            mvwprintw(game_win, y, x, "%s" , arrow_icon );
            wrefresh(game_win);
        }
        else add_arrow(num_rooms);
    } finish_white;
}
void add_sword (int num_rooms ) {
    start_white;
    int k = rand() % (num_rooms-1) ;
    if ( k == 4 ) add_sword (num_rooms);
    else {
        int x = number[k].x + 3 + rand() % (number[k].width - 6) ;
        int y = number[k].y + 3 + rand() % (number[k].height - 6);
        if (!map[y][x]){
            map [y][x] = 16 ; 
            mvwprintw(game_win, y, x, "%s" , sword_icon );
            wrefresh(game_win);
        }
        else add_sword(num_rooms);
    } finish_white;
}
void add_normal_food (int num_rooms ) {
    start_green;
    for (int i = 0; i < num_rooms; i++) {
        if ( i == 4 ) i++;
        if ( rand() % 3 != 0 ) {
            int num_obstacles = rand() % 2 ; 

            for (int j = 0; j < num_obstacles; j++) {
            
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , normal_food_icon );
                    map [y][x] = 17 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    }finish_green;
}
void add_bad_food (int num_rooms ) {
    start_gray;
    for (int i = 0; i < num_rooms; i++) {
        if ( i == 4 ) i++;
        if ( rand() % 3 != 0 ) {
            int num_obstacles = rand() % 2 ; 

            for (int j = 0; j < num_obstacles; j++) {
            
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , bad_food_icon );
                    map [y][x] = 20 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    } finish_gray;
}
void add_magic_food (int num_rooms ) {
    start_magenta;
    for (int i = 0; i < num_rooms; i++) {
        if ( i == 4 ) i++;
        if ( rand() % 3 == 0 ) {
            int num_obstacles = rand() % 2 ; 

            for (int j = 0; j < num_obstacles; j++) {
            
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , magic_food_icon );
                    map [y][x] = 18 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    }finish_magenta;
}
void add_golden_food (int num_rooms ) {

    for (int i = 0; i < num_rooms; i++) { ;
        
        if ( i == 4 ) i++;
        if ( (rand() % 4 == 0)) {
            int num_obstacles = rand() % 2 ; 
            for (int j = 0; j < num_obstacles; j++) {
            
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , golden_food_icon );
                    map [y][x] = 19 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    }
}
void add_health_talisman (int num_rooms ) {
    start_green;
    for (int i = 0; i < num_rooms ; i++) {
        int b = 0 ;
        if (i == 3) b = 1 ;
        if ( i == 4 ) i++;
        if ( rand() % 4 == 0 || b ) {
            int num_obstacles = rand() % 2 ; 
            if (b) num_obstacles += 2 ;
            for (int j = 0; j < num_obstacles; j++) {
                
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , health_talisman_icon );
                    map [y][x] = 21 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    } finish_green;
}
void add_power_talisman (int num_rooms ) {

    for (int i = 0; i < num_rooms ; i++) {
        int b = 0 ;
        if (i == 3) b = 1 ;
        if ( i == 4 ) i++;
        if ( rand() % 4 == 0 || b) {
            int num_obstacles = rand() % 2 ; 
            if (b) num_obstacles += 1 ;
            for (int j = 0; j < num_obstacles; j++) {
            
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , powerـtalisman_icon );
                    map [y][x] = 22 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    }
}
void add_speed_talisman (int num_rooms ) {

    for (int i = 0; i < num_rooms ; i++) {
        int b = 0 ;
        if (i == 3) b = 1 ;
        if ( i == 4 ) i++;
        if ( rand() % 4 == 0 || b) {
            int num_obstacles = rand() % 2 ; 
            if (b) num_obstacles += 1 ;
            for (int j = 0; j < num_obstacles; j++) {
                
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , speed_talisman_icon );
                    map [y][x] = 23 ; 
                    wrefresh(game_win);
                } else j--;
            }
        }
    }
}
void add_fox (int num_rooms) {
    start_red; int num = 0 ;
    for (int i = 0; i < num_rooms ; i++) {
        int b = 0 ;
        if (i == 4) b = 1 ;
        if ( i == 3 ) i++;
        if ( i != 0 ) {
            int num_obstacles = 1 ; 
            if (b) num_obstacles = 2 ;
            for (int j = 0; j < num_obstacles; j++) {
                
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , Fire_Breathing_Monster_icon );
                    map [y][x] = 25 ; 
                    Fire_Breathing_Monster[num].x = x ;
                    Fire_Breathing_Monster[num].y = y ;
                    Fire_Breathing_Monster[num].health = 10 ;
                    num++;
                    num_fire++;
                    wrefresh(game_win);
                } else j--;
            }
        }
    }
    finish_red;
}
void add_loin (int num_rooms) {
    start_red; int num = 0 ;
    for (int i = 0; i < num_rooms ; i++) {
        int b = 0 ;
        if (i == 4) b = 1 ;
        if ( i == 3 ) i++;
        if ( i != 0 ) {
            int num_obstacles = rand() % 2 ; 
            if (b) num_obstacles = 1 ;
            for (int j = 0; j < num_obstacles; j++) {
                
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , Giant_icon );
                    map [y][x] = 26 ; 
                    Giant[num].x = x ;
                    Giant[num].y = y ;
                    Giant[num].health = 15 ;
                    num++; num_giant++;
                    wrefresh(game_win);
                } else j--;
            }
        }
    }
    finish_red;
}
void add_snake (int num_rooms) {
    start_red; int num = 0 ;
    for (int i = 0; i < num_rooms ; i++) {
    
        if ( i == 4 || i == 6 ) {
            int num_obstacles = 1 ;
            for (int j = 0; j < num_obstacles; j++) {
                
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , Snake_icon );
                    map [y][x] = 27 ;
                    snake[num].x = x ;
                    snake[num].y = y ;
                    snake[num].health = 20 ;
                    num++; num_snake++;
                    wrefresh(game_win);
                } else j--;
            }
        }
    }
    finish_red;
}
void add_dragon (int num_rooms) {
    start_red; int num = 0 ;
    int i = 4 ;
    int num_obstacles = 1 ; 
            
    for (int j = 0; j < num_obstacles; j++) {
           
        int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
        int y = number[i].y + 3 + rand() % (number[i].height - 6);
        if (!map[y][x]){
            mvwprintw(game_win, y, x, "%s" , Undead_icon );
            map [y][x] = 28 ; 
            undead[num].x = x ;
            undead[num].y = y ;
            undead[num].health = 30 ;
            num++; num_undead++;
            wrefresh(game_win);
        } else j--;
    } finish_red;    
}
void add_deamon (int num_rooms) {
    start_red; int num = 0 ;
    for (int i = 0; i < num_rooms ; i++) {
        int b = 0 ;
        if (i == 4) b = 1 ;
        if ( i == 3 ) i++;
        if ( i != 0 ) {
            int num_obstacles = (rand() % 2) + 1 ; 
            if (b) num_obstacles = 2 ;
            for (int j = 0; j < num_obstacles; j++) {
                
                int x = number[i].x + 3 + rand() % (number[i].width - 6) ;
                int y = number[i].y + 3 + rand() % (number[i].height - 6);
                if (!map[y][x]){
                    mvwprintw(game_win, y, x, "%s" , deamon_icon );
                    map [y][x] = 24 ; 
                    Deamon[num].x = x ;
                    Deamon[num].y = y ;
                    Deamon[num].health = 5 ;
                    num++; num_deamon++;
                    wrefresh(game_win);
                } else j--;
            }
        }
    } finish_red ;
}
void create_room_5 (){

    for ( int i = number[5].x+1 ; i < number[5].x + number[5].width ; i++) {
        for (int j = number[5].y+1 ; i < number[5].y + number[5].height ; j++) {
            start_gray; mvwaddch(game_win, j , i , '.'); finish_gray;
            if (rand() % 12 == 0) {
                mvwprintw(game_win, j , i , "%s" , dimond_icon );
            } else if (rand() % 12 == 1) {
                mvwprintw(game_win, j , i , "%s" , gold_icon );
            }
        }
    }
}
void in_room (int y , int x , int num_rooms) {
    if ( map[y][x] == 2) karbar.in_room_number = -1;
    for (int i = 0 ; i < num_rooms ; i++) 
        if (y >= number[i].y && y <= number[i].y+number[i].height && x >= number[i].x && x <= number[i].x+number[i].width )        
            karbar.in_room_number = i ;
}
void show_map () {
    WINDOW *win = newwin(HEIGHT, WIDTH, 3, 7);
    wattron(win , COLOR_PAIR(1)); box(win, '|', '-') ;wattroff(win , COLOR_PAIR(1));

    for (int i = 0; i < 210; i++){
        for (int j = 0; j < 60; j++) {
            if (map[j][i] == 0 || map[j][i] == 4){
                wattron(win , COLOR_PAIR(6)); mvwaddch(win, j , i , '.'); wattroff(win , COLOR_PAIR(6));
            } else if (map[j][i] == 1){
                wattron(win , COLOR_PAIR(6)); mvwaddch(win, j , i , '-'); wattroff(win , COLOR_PAIR(6));
            } else if (map[j][i] == 10){
                wattron(win , COLOR_PAIR(6)); mvwaddch(win, j , i , '|'); wattroff(win , COLOR_PAIR(6));
            } else if (map[j][i] == 3){
                wattron(win , COLOR_PAIR(4)); mvwaddch(win, j , i , '+'); wattroff(win , COLOR_PAIR(4));
            } else if (map[j][i] == 5){
                wattron(win , COLOR_PAIR(4)); mvwaddch(win, j , i , 'O'); wattroff(win , COLOR_PAIR(4));
            } else if (map[j][i] == 6){
                wattron(win , COLOR_PAIR(2)); mvwaddch(win, j , i , '<'); wattroff(win , COLOR_PAIR(2));
            } else if (map[j][i] == 7){
                wattron(win , COLOR_PAIR(3)); mvwaddch(win, j , i , '<'); wattroff(win , COLOR_PAIR(3));
            } else if (map[j][i] == 11){
                mvwprintw(win, j , i , "%s" , gold_icon );
            } else if (map[j][i] == 12){
                mvwprintw(win, j , i , "%s" , dimond_icon );
            } else if (map[j][i] == 13){
                wattron(win , COLOR_PAIR(4)); mvwprintw(win, j , i , "%s" , knife_icon ); wattroff(win , COLOR_PAIR(4));
            } else if (map[j][i] == 14){
                wattron(win , COLOR_PAIR(4)); mvwprintw(win, j , i , "%s" , wand_icon ); wattroff(win , COLOR_PAIR(4));
            } else if (map[j][i] == 15){
                wattron(win , COLOR_PAIR(4)); mvwprintw(win, j , i , "%s" , arrow_icon ); wattroff(win , COLOR_PAIR(4));
            } else if (map[j][i] == 16){
                wattron(win , COLOR_PAIR(4)); mvwprintw(win, j , i , "%s" , sword_icon ); wattroff(win , COLOR_PAIR(4));
            } else if (map[j][i] == 17){
                wattron(win , COLOR_PAIR(6)); mvwprintw(win, j , i , "%s" , normal_food_icon );wattroff(win , COLOR_PAIR(6));
            } else if (map[j][i] == 18){
                wattron(win , COLOR_PAIR(7)); mvwprintw(win, j , i , "%s" , magic_food_icon ); wattroff(win , COLOR_PAIR(7));
            } else if (map[j][i] == 19){
                wattron(win , COLOR_PAIR(2));mvwprintw(win, j , i , "%s" , golden_food_icon );wattroff(win , COLOR_PAIR(2));
            } else if (map[j][i] == 20){
                wattron(win , COLOR_PAIR(5)); mvwprintw(win, j , i , "%s" , bad_food_icon ); wattroff(win , COLOR_PAIR(5));
            } else if (map[j][i] == 21){
                wattron(win , COLOR_PAIR(6)); mvwprintw(win, j , i , "%s" , health_talisman_icon );wattroff(win , COLOR_PAIR(6));
            } else if (map[j][i] == 22){
                mvwprintw(win, j , i , "%s" , powerـtalisman_icon );
            } else if (map[j][i] == 23){
                mvwprintw(win, j , i , "%s" , speed_talisman_icon );
            } else if (map[j][i] == 24){
                wattron(win , COLOR_PAIR(1));mvwprintw(win, j , i , "%s" , deamon_icon );wattroff(win , COLOR_PAIR(1));
            } else if (map[j][i] == 25){
                wattron(win , COLOR_PAIR(1));mvwprintw(win, j , i , "%s" , Fire_Breathing_Monster_icon );wattroff(win , COLOR_PAIR(1));
            } else if (map[j][i] == 26){
                wattron(win , COLOR_PAIR(1));mvwprintw(win, j , i , "%s" , Giant_icon );wattroff(win , COLOR_PAIR(1));
            } else if (map[j][i] == 27){
                wattron(win , COLOR_PAIR(1));mvwprintw(win, j , i , "%s" , Snake_icon );wattroff(win , COLOR_PAIR(1));
            } else if (map[j][i] == 28){
                wattron(win , COLOR_PAIR(1));mvwprintw(win, j , i , "%s" , Undead_icon );wattroff(win , COLOR_PAIR(1));
            } else if (map[j][i] == 2){
                wattron(win , COLOR_PAIR(4)); mvwaddch(win, j , i , '#'); wattroff(win , COLOR_PAIR(4));
            } else if ( j == karbar.y && i == karbar.x ){
                wattron(win , COLOR_PAIR(3)); mvwaddch(win, j , i , '@'); wattroff(win , COLOR_PAIR(3));
            }
        }
    } wrefresh(win);werase(message_win);message_box;
    yellow1; mvwprintw(message_win, 3, 2, "Press m to close the map"); yellow2;
    wrefresh(message_win);
    while (1) {

        int ch = wgetch(win);
        if (ch == 'm'){
            werase(win); wrefresh(win); break;
        }
    } werase(message_win); message_box; start_red; box(game_win, '|', '-') ; finish_red; wrefresh(game_win);
}
void show_corridor (int y , int x) {

    start_white;
    for (int i = -3 ; i <= 6 ; i++) 
        for (int j = -1 ; j <= 1; j++){ 
            if (map[y+j][x+i] == 2) 
                mvwaddch(game_win, y+j , x+i , '#');
            if (map[y+j][x+i] == 3) 
                mvwaddch(game_win, y+j , x+i , '+');
        }
    for (int j = -3 ; j <= 6 ; j++) 
        for (int i = -1 ; i <= 1; i++){ 
            if (map[y+j][x+i] == 2) 
                mvwaddch(game_win, y+j , x+i , '#');
            if (map[y+j][x+i] == 3) 
                mvwaddch(game_win, y+j , x+i , '+');
        }
    finish_white;
    start_blue; mvwaddch(game_win, y , x , '@');finish_blue;
}
void show_room () {

    if (karbar.in_room_number == -1) return;
    for (int i = number[karbar.in_room_number].x ; i <= number[karbar.in_room_number].x+number[karbar.in_room_number].width; i++) {
        for (int j = number[karbar.in_room_number].y; j <= number[karbar.in_room_number].y + number[karbar.in_room_number].height; j++){
            if (map[j][i] == 0 || map[j][i] == 4){
                start_green; mvwaddch(game_win, j , i , '.'); finish_green;
            } else if (map[j][i] == 1){
                start_green; mvwaddch(game_win, j , i , '-'); finish_green;
            } else if (map[j][i] == 10){
                start_green; mvwaddch(game_win, j , i , '|'); finish_green;
            } else if (map[j][i] == 3){
                start_white; mvwaddch(game_win, j , i , '+'); finish_white;
            } else if (map[j][i] == 5){
                start_white; mvwaddch(game_win, j , i , 'O'); finish_white;
            } else if (map[j][i] == 6){
                start_yellow; mvwaddch(game_win, j , i , '<'); finish_yellow;
            } else if (map[j][i] == 7){
                start_blue; mvwaddch(game_win, j , i , '<'); finish_blue;
            } else if (map[j][i] == 11){
                mvwprintw(game_win, j , i , "%s" , gold_icon );
            } else if (map[j][i] == 12){
                mvwprintw(game_win, j , i , "%s" , dimond_icon );
            } else if (map[j][i] == 13){
                start_white; mvwprintw(game_win, j , i , "%s" , knife_icon ); finish_white;
            } else if (map[j][i] == 14){
                start_white; mvwprintw(game_win, j , i , "%s" , wand_icon ); finish_white;
            } else if (map[j][i] == 15){
                start_white; mvwprintw(game_win, j , i , "%s" , arrow_icon ); finish_white;
            } else if (map[j][i] == 16){
                start_white; mvwprintw(game_win, j , i , "%s" , sword_icon ); finish_white;
            } else if (map[j][i] == 17){
                start_green; mvwprintw(game_win, j , i , "%s" , normal_food_icon );finish_green;
            } else if (map[j][i] == 18){
                start_magenta; mvwprintw(game_win, j , i , "%s" , magic_food_icon ); finish_magenta;
            } else if (map[j][i] == 19){
                start_yellow;mvwprintw(game_win, j , i , "%s" , golden_food_icon );finish_yellow;
            } else if (map[j][i] == 20){
                start_gray;mvwprintw(game_win, j , i , "%s" , bad_food_icon );finish_gray;
            } else if (map[j][i] == 21){
                start_green ;mvwprintw(game_win, j , i , "%s" , health_talisman_icon );finish_green;
            } else if (map[j][i] == 22){
                mvwprintw(game_win, j , i , "%s" , powerـtalisman_icon );
            } else if (map[j][i] == 23){
                mvwprintw(game_win, j , i , "%s" , speed_talisman_icon );
            } else if (map[j][i] == 24){
                start_red;mvwprintw(game_win, j , i , "%s" , deamon_icon );finish_red;
            } else if (map[j][i] == 25){
                start_red;mvwprintw(game_win, j , i , "%s" , Fire_Breathing_Monster_icon );finish_red;
            } else if (map[j][i] == 26){
                start_red;mvwprintw(game_win, j , i , "%s" , Giant_icon );finish_red;
            } else if (map[j][i] == 27){
                start_red;mvwprintw(game_win, j , i , "%s" , Snake_icon );finish_red;
            } else if (map[j][i] == 28){
                start_red;mvwprintw(game_win, j , i , "%s" , Undead_icon );finish_red;
            }
        }
    }
}
void draw_detail_win () {

    wattron(detail_win , COLOR_PAIR(1));mvwprintw(detail_win, 4, 3, "Health: %d", health); wattroff(detail_win , COLOR_PAIR(1));
    wattron(detail_win , COLOR_PAIR(2)); mvwprintw(detail_win, 10, 3, "Gold: %d", karbar.gold); wattroff(detail_win , COLOR_PAIR(2));
    wattron(detail_win , COLOR_PAIR(5));mvwprintw(detail_win, 8, 3, "Point: %d", point);wattroff(detail_win , COLOR_PAIR(5));
    wattron(detail_win , COLOR_PAIR(6));mvwprintw(detail_win, 6, 3, "Food: %d", food);wattroff(detail_win , COLOR_PAIR(6));
    wattron(detail_win , COLOR_PAIR(7));mvwprintw(detail_win, 11, 1 , "------------------");wattroff(detail_win , COLOR_PAIR(7));
    wattron(detail_win , COLOR_PAIR(4));mvwprintw(detail_win, 13, 3 , "Inventory (1)");wattroff(detail_win , COLOR_PAIR(4));
    wattron(detail_win , COLOR_PAIR(4));mvwprintw(detail_win, 15, 3 , "Backpack (2)");wattroff(detail_win , COLOR_PAIR(4));
    wattron(detail_win , COLOR_PAIR(7)); box(detail_win, '|', '-') ; wattroff(detail_win , COLOR_PAIR(7));
    wrefresh(detail_win);
}
void weapon_menu () {
    
    WINDOW *win = newwin (60 , 20 , 3 , 215 );
    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 4 , 3 , "Select weapon");wattroff(win , COLOR_PAIR(1));
    mvwprintw(win , 6 , 3 , "1.Mace (M) ✓" );
    if (karbar.sword)
        mvwprintw(win , 8 , 3 , "2.Sword (%s) ✓" , sword_icon );
    else 
        mvwprintw(win , 8 , 3 , "2.Sword (%s) ×" , sword_icon );
        
    mvwprintw(win , 10 , 3 , "3.Dagger (%s) %d" , knife_icon );
    mvwprintw(win , 12 , 3 , "4.Wand (%s) %d" , wand_icon );
    mvwprintw(win , 14 , 3 , "5.Arrow (%s) %d" , arrow_icon );
    wattron(win , COLOR_PAIR(7)); box(win , '|' , '-'); wattroff(win , COLOR_PAIR(7));
    wrefresh(win);
    while (1) {
        int c = wgetch(win);

        if ( c == '1') {
            WINDOW *win = newwin(17, 17, 64 , 214);
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Mace selected" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            karbar.weapon = 1;
            break;
        } else if ( c == '2' ){
            if (karbar.sword){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Sword selected" ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.weapon = 2;
                break;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '3' ){
            if (karbar.dagger > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Dagger selected" ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.weapon = 3;
                break;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '4' ){
            if (karbar.wand > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Wand selected" ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.weapon = 4;
                break;
            }
            else { 

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '5' ){
            if (karbar.arrow > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Arrow selected" ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.weapon = 5 ;
                break;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        }
    }
    wrefresh(win); werase(win);wrefresh(win); delwin(win);
    draw_detail_win();
}
void food_menu () {

    WINDOW *win = newwin (60 , 20 , 3 , 215 );
    while (1) {
    
        wattron(win , COLOR_PAIR(1)); mvwprintw(win , 4 , 3 , "Food bar");wattroff(win , COLOR_PAIR(1));
        mvwprintw(win , 6 , 3 , "1. Normal (%s) %d" , normal_food_icon , karbar.normal_food );
        mvwprintw(win , 8 , 3 , "2. bad (%s) %d" , bad_food_icon , karbar.bad_food );   
        mvwprintw(win , 10 , 3 , "3. magic (%s) %d" , magic_food_icon , karbar.magic_food);
        mvwprintw(win , 12 , 3 , "4. golden (%s) %d" , golden_food_icon , karbar.golden_food);
        mvwprintw(win , 14 , 3 , "5. Back" );
        wattron(win , COLOR_PAIR(7)); box(win , '|' , '-'); wattroff(win , COLOR_PAIR(7));
        wrefresh(win);
        int c = wgetch(win);

        if ( c == '1' ){
            if (karbar.normal_food){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ," +50 health" );
                mvwprintw(win , 2 , 1 ," +10 food" ) ; wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.normal_food -= 1;
                health += 50; food += 10 ;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '2' ){
            if (karbar.bad_food > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ," +50 health" ) ;
                mvwprintw(win , 2 , 1 ," +5 food" ); wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.bad_food -= 1;
                health += 50; timer += 20; food += 5;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '3' ){
            if (karbar.magic_food > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ," +80 health" ) ;
                mvwprintw(win , 2 , 1 ," +15 food" ) ; wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.magic_food -= 1; food += 15;
                health += 80;
            }
            else { 

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '4' ){
            if (karbar.golden_food > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ," +100 health" ) ;
                mvwprintw(win , 2 , 1 ," +20 food" ) ; wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.golden_food -= 1; food += 20 ;
                health += 100; timer = 0 ;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '5'){
            break;
        }
    }
    wrefresh(win); werase(win);wrefresh(win); delwin(win); draw_detail_win();
}
void poison_menu () {

    WINDOW *win = newwin (60 , 20 , 3 , 215 );
    while (1) {
    
        wattron(win , COLOR_PAIR(1)); mvwprintw(win , 4 , 3 , "poison menu");wattroff(win , COLOR_PAIR(1));
        mvwprintw(win , 6 , 3 , "1. health (%s) %d" , health_talisman_icon , karbar.health_talisman );
        mvwprintw(win , 8 , 3 , "2. power (%s) %d" , powerـtalisman_icon , karbar.power_talisman );   
        mvwprintw(win , 10 , 3 , "3. speed (%s) %d" , speed_talisman_icon , karbar.speed_talisman);
        mvwprintw(win , 12 , 3 , "4. Back" );
        wattron(win , COLOR_PAIR(7)); box(win , '|' , '-'); wattroff(win , COLOR_PAIR(7));
        wrefresh(win);
        int c = wgetch(win);

        if ( c == '1' ){
            if (karbar.health_talisman){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ," +200 health" ); wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.health_talisman -= 1;
                health += 200 ;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '2' ){
            if (karbar.power_talisman > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ,"Damage ×2" ) ; wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.power_talisman -= 1;
                damage = 10 ;
            }
            else {

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '3' ){
            if (karbar.speed_talisman > 0 ){
                WINDOW *win = newwin(17, 17, 64 , 214);
                wattron(win , COLOR_PAIR(6)); mvwprintw(win , 1 , 1 ,"Speed ×2" ); wattroff(win , COLOR_PAIR(6));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                karbar.speed_talisman -= 1 ;
                speed = 10 ;
            }
            else { 

                WINDOW *win = newwin(15, 15, 64 , 214);
                wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"doesn't exist." ) ; wattroff(win , COLOR_PAIR(1));
                wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
            }    
        } else if ( c == '4'){
            break;
        }
    }
    wrefresh(win); werase(win);wrefresh(win); delwin(win); draw_detail_win();
}
void charge_enemy (int y , int x){

    for (int n = 0; n < num_deamon; n++) {
        for (int i = -1 ; i < 2 ; i++) {
            for (int j = -1 ; j < 2 ; j++) {
                if (i == Deamon[n].x && j == Deamon[n].y )
                    Deamon[n].move = 5 ;
            }
        }
    }
    for (int n = 0; n < num_fire; n++) {
        for (int i = -1 ; i < 2 ; i++) {
            for (int j = -1 ; j < 2 ; j++) {
                if (i == Fire_Breathing_Monster[n].x && j == Fire_Breathing_Monster[n].y )
                    Fire_Breathing_Monster[n].move = 5 ;
            }
        }
    }
    for (int n = 0; n < num_giant; n++) {
        for (int i = -1 ; i < 2 ; i++) {
            for (int j = -1 ; j < 2 ; j++) {
                if (i == Giant[n].x && j == Giant[n].y )
                    Giant[n].move = 5 ;
            }
        }
    }
    for (int n = 0; n < num_snake; n++) {
        for (int i = -1 ; i < 2 ; i++) {
            for (int j = -1 ; j < 2 ; j++) {
                if (i == snake[n].x && j == snake[n].y )
                    snake[n].move = 100000 ;
            }
        }
    }
    for (int n = 0; n < num_undead; n++) {
        for (int i = -1 ; i < 2 ; i++) {
            for (int j = -1 ; j < 2 ; j++) {
                if (i == undead[n].x && j == undead[n].y )
                    undead[n].move = 5 ;
            }
        }
    }
}
void move_enemy (int y , int x) {}
void show_trap (int y , int x) {

    start_red;
    for (int i = -2 ; i < 3 ; i++) {
        for (int j = -2; j < 3; j++) {
            if (map[j][i] == 4 ) mvwaddch(game_win , j , i , '*');
        }
    } finish_red; start_green;
    while (1) {
        int ch = wgetch(game_win);
        if (ch == 's'){
            for (int i = -2 ; i < 3 ; i++) {
                for (int j = -2; j < 3; j++) {
                    if (map[j][i] == 4 ) mvwaddch(game_win , j , i , '.');
                }  
            }
        }
    }finish_green;
}
void hit (int y , int x) {

    if ( karbar.weapon == 1) {
        for (int i = -1 ; i < 2; i++) {
            for (int j = -1; j < 2; j++) {

                for (int n = 0; n < num_deamon; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == Deamon[n].x && j == Deamon[n].y && Deamon[n].health > 0) {
                                if (Deamon[n].health > 5){
                                    Deamon[n].health -= 5 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit Deamon!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    Deamon[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill Deamon!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_fire; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == Fire_Breathing_Monster[n].x && j == Fire_Breathing_Monster[n].y && Fire_Breathing_Monster[n].health > 0) {
                                if (Fire_Breathing_Monster[n].health > 5){
                                    Fire_Breathing_Monster[n].health -= 5 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit Fire_Breathing_Monster!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    Fire_Breathing_Monster[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill Fire_Breathing_Monster!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_giant; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == Giant[n].x && j == Giant[n].y && Giant[n].health > 0) {
                                if (Giant[n].health > 5){
                                    Giant[n].health -= 5 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit Giant!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    Giant[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill Giant!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_snake; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == snake[n].x && j == snake[n].y && snake[n].health > 0) {
                                if (snake[n].health > 5){
                                    snake[n].health -= 5 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit snake!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    snake[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill snake!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_undead; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == undead[n].x && j == undead[n].y && undead[n].health > 0) {
                                if (undead[n].health > 5){
                                    undead[n].health -= 5 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit undead!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    undead[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill undead!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if (karbar.weapon == 2) {

        for (int i = -1 ; i < 2; i++) {
            for (int j = -1; j < 2; j++) {

                for (int n = 0; n < num_deamon; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == Deamon[n].x && j == Deamon[n].y && Deamon[n].health > 0) {
                                if (Deamon[n].health > 10){
                                    Deamon[n].health -= 10 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit Deamon!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    Deamon[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill Deamon!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_fire; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == Fire_Breathing_Monster[n].x && j == Fire_Breathing_Monster[n].y && Fire_Breathing_Monster[n].health > 0) {
                                if (Fire_Breathing_Monster[n].health > 10){
                                    Fire_Breathing_Monster[n].health -= 10 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit Fire_Breathing_Monster!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    Fire_Breathing_Monster[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill Fire_Breathing_Monster!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_giant; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == Giant[n].x && j == Giant[n].y && Giant[n].health > 0) {
                                if (Giant[n].health > 10) {
                                    Giant[n].health -= 10 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit Giant!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    Giant[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill Giant!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_snake; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == snake[n].x && j == snake[n].y && snake[n].health > 0) {
                                if (snake[n].health > 10) {
                                    snake[n].health -= 10 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit snake!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    snake[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill snake!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
                for (int n = 0; n < num_undead; n++) {
                    for (int i = -1 ; i < 2 ; i++) {
                        for (int j = -1 ; j < 2 ; j++) {
                            if (i == undead[n].x && j == undead[n].y && undead[n].health > 0) {
                                if (undead[n].health > 10) {
                                    undead[n].health -= 10 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You hit undead!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                } else {
                                    undead[n].health = 0 ;
                                    werase(message_win); message_box; yellow1;
                                    mvwprintw(message_win, 3, 2, "You kill undead!");
                                    yellow2; wrefresh(message_win); napms(1000); werase(message_win); message_box;
                                }
                            }
                        }
                    }
                }
            }
        }

    } else {

        
    }
}
void check_location (int y , int x) {

    if (map[y][x] == 5 || map[y][x] == 1 || map[y][x] == 10 ){
        move_enemy(karbar.y , karbar.x);

    } else if (map[y][x] == 0) {
        if (map[karbar.y][karbar.x] != 3 && map[karbar.y][karbar.x] != 2 ){
            map[karbar.y][karbar.x] = 0; start_green;
            mvwaddch(game_win , karbar.y ,karbar.x , '.'); finish_green;
            draw_karbar; move_enemy(y , x);
        } else if (map[karbar.y][karbar.x] == 3 ) {
            map[karbar.y][karbar.x] = 3; start_white;
            mvwaddch(game_win , karbar.y ,karbar.x , '+'); finish_white;
            draw_karbar; move_enemy(y , x);
        } else if (map[karbar.y][karbar.x] == 2 ) {
            map[karbar.y][karbar.x] = 3; start_white;
            mvwaddch(game_win , karbar.y ,karbar.x , '#'); finish_white;
            draw_karbar; move_enemy(y , x);
        }
    } else if (map[y][x] == -1 ) {
    } else if (map[y][x] == 2 || map[y][x] == 3 ) {
        if (map[karbar.y][karbar.x] == 2) {
            start_white; mvwaddch(game_win , karbar.y ,karbar.x , '#');finish_white;
        } else if (map[karbar.y][karbar.x] == 3) {
            start_white; mvwaddch(game_win , karbar.y ,karbar.x , '+');finish_white;
        } else if (map[karbar.y][karbar.x] == 0) {
            start_green; mvwaddch(game_win , karbar.y ,karbar.x , '.'); finish_green;
        }
        draw_karbar;

    } else if (map[y][x] == 4) {
        health -= 50 ;
        start_green; mvwaddch(game_win , karbar.y ,karbar.x , '.'); finish_green;
        draw_karbar;
        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "Oops, that was a trap!!! Your health decreased by 50 points.");
        yellow2; wrefresh(message_win);
        enemy1; map[y][x] = 0 ;
    } else if (map[y][x] == 7 || map[y][x] == 6) {
        karbar.floor += 1 ;
    } else if (map[y][x] == 11) {
        karbar.gold += 5 ; point += 5;
        werase(message_win);message_box; yellow1; 
        mvwprintw(message_win, 3, 2, "You got 5 gold");
        yellow2;  wrefresh(message_win);
        poor; draw_karbar;
        enemy1;map[y][x] = 0 ;
    } else if (map[y][x] == 12) {
        karbar.gold += 15 ; point += 15 ;
        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "You got 15 gold");
        yellow2; wrefresh(message_win);
        poor; draw_karbar;
        enemy1;map[y][x] = 0 ;
    } else if (map[y][x] == 13) {
        karbar.dagger += 10 ;
        werase(message_win); message_box; yellow1;
        mvwprintw(message_win, 3, 2, "You got 10 dagger");
        yellow2; wrefresh(message_win);
        poor; draw_karbar;
        enemy1;map[y][x] = 0 ;
    } else if (map[y][x] == 14) {
        karbar.wand += 8 ;
        werase(message_win);message_box; yellow1;
        mvwprintw(message_win, 3, 2, "You got 8 wand");
        yellow2; wrefresh(message_win);
        poor; draw_karbar;
        enemy1;map[y][x] = 0 ;
    } else if (map[y][x] == 15) {
        karbar.arrow += 20 ;
        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "You got 20 arrow");
        yellow2; wrefresh(message_win);
        poor; draw_karbar;
        enemy1;map[y][x] = 0 ;
    } else if (map[y][x] == 16) {
        karbar.sword = true ;
        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "You got Sword");
        yellow2; wrefresh(message_win);
        poor; draw_karbar;
        enemy1;
    } else if (map[y][x] == 17) {

        if (karbar.bad_food + karbar.normal_food + karbar.golden_food + karbar.golden_food < 6){
            
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Press 1 to collect the Normal food or 2 to ignore it");
            yellow2; wrefresh(message_win);
            
            while (1) {
                char ch = wgetch(game_win);
                if ( ch == '1'){
                    karbar.normal_food += 1 ;
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "You got a normal food");
                    yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box ;yellow1;
                    mvwprintw(message_win, 3, 2, "Normal food is gone!");
                    yellow2; wrefresh(message_win); break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214); 
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                }
            }    
        } else{
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Inventory is full , food is gone!");
            yellow2; wrefresh(message_win);
        }     
        enemy1; poor; draw_karbar;
    } else if (map[y][x] == 18) {

       if (karbar.bad_food + karbar.normal_food + karbar.golden_food + karbar.golden_food < 6){
            
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Press 1 to collect the Magic food or 2 to ignore it");
            yellow2; wrefresh(message_win);
            
            while (1) {
                char ch = wgetch(game_win);
                if ( ch == '1'){
                    karbar.magic_food += 1 ;
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "You got a magic food");
                    yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "Magic food is gone!");
                    yellow2; wrefresh(message_win);break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214);
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                }
            }    
        } else{
            
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Inventory is full , magic food is gone!");
            yellow2; wrefresh(message_win);
        }     
        enemy1; poor; draw_karbar;

    } else if (map[y][x] == 19) {

        if (karbar.bad_food + karbar.normal_food + karbar.golden_food + karbar.golden_food < 6){
            
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Press 1 to collect the golden food or 2 to ignore it");
            yellow2; wrefresh(message_win);
            
            while (1) {
                char ch = wgetch(game_win);
                if ( ch == '1'){
                    karbar.golden_food += 1 ;
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "You got a golden food");
                    yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "Golden food is gone!");
                    yellow2; wrefresh(message_win);break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214);
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                }
            }    
        } else{
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Inventory is full , golden food is gone!");
            yellow2; wrefresh(message_win);
        }     
        enemy1; poor; draw_karbar;

    } else if (map[y][x] == 20) {

        if (karbar.bad_food + karbar.normal_food + karbar.golden_food + karbar.golden_food < 6){
            
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Press 1 to collect the bad food or 2 to ignore it");
            yellow2; wrefresh(message_win);
            
            while (1) {
                char ch = wgetch(game_win);
                if ( ch == '1'){
                    karbar.bad_food += 1 ;
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "You got a bad food");
                    yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "Bad food is gone!");
                    yellow2; wrefresh(message_win);break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214);
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); 
                }
            }    
        } else{
            werase(message_win); message_box;yellow1;
            mvwprintw(message_win, 3, 2, "Inventory is full , bad food is gone!");
            yellow2; wrefresh(message_win);
        }     
        enemy1; poor; draw_karbar;
    } else if (map[y][x] == 21) {

        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "Press 1 to collect the health talisman or 2 to ignore it");
        yellow2; wrefresh(message_win);
        
        while (1) {
            char ch = wgetch(game_win);
            if ( ch == '1'){
                karbar.health_talisman += 1 ;
                werase(message_win); message_box;yellow1;
                mvwprintw(message_win, 3, 2, "You got a health talisman");
                yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "Health talisman food is gone!");
                    yellow2; wrefresh(message_win);break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214);
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win);
                }
            } enemy1; poor; draw_karbar;

    } else if (map[y][x] == 22) {

        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "Press 1 to collect the power talisman or 2 to ignore it");
        yellow2; wrefresh(message_win);
        
        while (1) {
            char ch = wgetch(game_win);
            if ( ch == '1'){
                karbar.power_talisman += 1 ;
                werase(message_win); message_box;yellow1;
                mvwprintw(message_win, 3, 2, "You got a power talisman");
                yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "Power talisman food is gone!");
                    yellow2; wrefresh(message_win);break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214);
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win);
                }
            } enemy1; poor; draw_karbar;

    } else if (map[y][x] == 23) {

        werase(message_win); message_box;yellow1;
        mvwprintw(message_win, 3, 2, "Press 1 to collect the speed talisman or 2 to ignore it");
        yellow2; wrefresh(message_win);
        
        while (1) {
            char ch = wgetch(game_win);
            if ( ch == '1'){
                karbar.speed_talisman += 1 ;
                werase(message_win); message_box;yellow1;
                mvwprintw(message_win, 3, 2, "You got a speed talisman");
                yellow2; wrefresh(message_win);break;
                } else if (ch == '2'){
                    werase(message_win); message_box;yellow1;
                    mvwprintw(message_win, 3, 2, "Speed talisman food is gone!");
                    yellow2; wrefresh(message_win);break;
                } else {
                    WINDOW *win = newwin(15, 15, 64 , 214);
                    wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
                    wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win);
                }
            } enemy1; poor; draw_karbar;

    } else if (map[y][x] == 24) {
        enemy1;
    } else if (map[y][x] == 25) {
        enemy1;
    } else if (map[y][x] == 26) {
        enemy1;
    } else if (map[y][x] == 27) {
        enemy1;
    } else if (map[y][x] == 28) {
        enemy1;
    }
}
void start_map (int difficulty_level , int floor ){

    clear(); srand(time(0));
    game_win = newwin(HEIGHT, WIDTH, 3, 7);
    message_win = newwin( 7 , 200 , 65 , 7);
    detail_win = newwin (60 , 20 , 3 , 215 );
    cbreak(); noecho(); megdar();
    start_red ; box(game_win, '|', '-') ; finish_red ;
    message_box;
    wattron(detail_win , COLOR_PAIR(7)); box(detail_win, '|', '-') ; wattroff(detail_win , COLOR_PAIR(7));
    curs_set(FALSE); 
    create_room_1(); 

    int num_rooms = create_rooms(difficulty_level);
    adad = num_rooms ;
    start_green ; for (int i = 0; i < num_rooms; i++)
                    draw_room(i); finish_green ;

    start_white; connect_rooms(num_rooms); finish_white;
    place_doors_on_walls(num_rooms);
    start_white ; add_obstacles(num_rooms); finish_white ;
    //start_yellow ;  add_ladder(floor); finish_yellow ;

    add_ladder2(floor);
    add_gold(num_rooms); add_dimond (num_rooms);
    add_trap(num_rooms); add_dagger(num_rooms); add_wand(num_rooms);
    add_arrow(num_rooms);add_sword(num_rooms); add_normal_food(num_rooms);
    add_magic_food(num_rooms);add_golden_food(num_rooms);
    add_bad_food(num_rooms);add_health_talisman(num_rooms);
    add_power_talisman(num_rooms); add_speed_talisman(num_rooms);
    add_deamon(num_rooms);add_fox(num_rooms); add_loin(num_rooms); 
    add_snake(num_rooms);add_dragon(num_rooms); 
    if ( floor == 4 ) create_room_5 ();
    yellow1; mvwprintw(message_win, 3, 2, "Look at the map carefully. The game will start soon!"); yellow2;
    wrefresh(game_win); wrefresh(message_win); wrefresh(detail_win);
    
    wtimeout(game_win, 6000);
    int ch = wgetch(game_win);
    if (ch == ERR); 
    else if (ch == 'R') 
        start_map(difficulty_level , floor);
    if ( floor == 1) {
        werase(message_win); message_box; yellow1;
        mvwprintw(message_win, 3, 2, "The game is started , Let's go %s!" , name);yellow2; wrefresh(message_win);
        werase(game_win); wrefresh(game_win);
    } else {
        werase(message_win); message_box; yellow1;
        mvwprintw(message_win, 3, 2, "Congratulations! You've reached the floor number %d. 🎉" , floor);yellow2; wrefresh(message_win);
        werase(game_win); wrefresh(game_win);
    }
    start_red; box(game_win, '|', '-') ; finish_red; wrefresh(game_win);
}
void start_new_game( int difficulty_level , int  hero_color ) {
    karbar.x = 95 ; karbar.y = 55;
    karbar.gold = 0 ; karbar.dimond = 0;
    karbar.bad_food = 0; karbar.golden_food = 0 ; 
    karbar.normal_food = 0 ; karbar.magic_food = 0;
    karbar.mace = true ; karbar.sword = false ;
    karbar.dagger = 0 ; karbar.wand = 0;
    karbar.arrow = 0 ; karbar.health_talisman = 0;
    karbar.power_talisman = 0 ; karbar.speed_talisman = 0;
    karbar.in_room_number = 0 ; karbar.weapon = 1 ;
    karbar.floor = 1 ;
    initialize(); keypad(game_win , TRUE);
    for (int i = 1 ; i <= 4 ; i++) {

        megdar(); karbar.x = 95 ; karbar.y = 55; 
        karbar.in_room_number = 0 ;
        start_map(difficulty_level , i);
        int health_counter = 0 ; 
        x = 1 ;
        while (x) {
            charge_enemy(karbar.y , karbar.x);
            int health_copy = health ;
            in_room(karbar.y , karbar.x , adad ); show_room (); 
            if ( hero_color == 2 ) {
                start_yellow; bold1 ; mvwaddch(game_win , karbar.y , karbar.x , '@'); finish_yellow; bold2;
            } else {
                start_blue; bold1 ; mvwaddch(game_win , karbar.y , karbar.x , '@'); finish_blue; bold2;
            }
            show_corridor(karbar.y , karbar.x);
            draw_detail_win (); char ch = wgetch(game_win);
            if ( timer ) {
                timer-- ;
                health -= 2;
            }  int p = 1 ;
            if (speed){p = 2;}
            if (damage) damage--;
            if (ch == 'w') {
                check_location(karbar.y-(1*p) , karbar.x );
            } else if (ch == 'W') {
                check_location(karbar.y-(2*p) , karbar.x );
            } else if (ch == 'e') {
                check_location(karbar.y-(1*p) , karbar.x+(1*p) );
            } else if (ch == 'd') {
                check_location(karbar.y , karbar.x+(1*p) );
            } else if (ch == 'D') {
                check_location(karbar.y , karbar.x+(2*p) );
            } else if (ch == 'c') {
                check_location(karbar.y+(1*p) , karbar.x+(p*1) );
            } else if (ch == 'x') {
                check_location(karbar.y+(1*p) , karbar.x );
            } else if (ch == 'X') {
                check_location(karbar.y+(2*p) , karbar.x );
            } else if (ch == 'z') {
                check_location(karbar.y+(1*p) , karbar.x-(1*p) );
            } else if (ch == 'a') {
                check_location(karbar.y , karbar.x-1*p );
            } else if (ch == 'A') {
                check_location(karbar.y , karbar.x-2*p );
            } else if (ch == 'q') {
                check_location(karbar.y-1*p , karbar.x-1*p );
            } else if (ch == 'm') {
                show_map ();
            } else if (ch == 's') {
                show_trap(karbar.y , karbar.x);
            } else if (ch == '1') {
                weapon_menu();
            } else if (ch == '2') {
                food_menu();
            } else if (ch == ' ') {
                move_enemy(karbar.y , karbar.x); hit(karbar.y , karbar.x);
            } else if (ch == '4') {
            } else if (ch == '5') {
                start_map (difficulty_level , i);
            }
            
            if (health_copy <= health && food >= 90) health_counter++ ;
            else health_counter = 0 ;
            if (health_counter >= 10) health += 4;
            if (health > 1000) health = 1000;
            if (food > 100) food = 100 ; 
            if ( i != karbar.floor ) break;
        }
    }   
}


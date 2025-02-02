#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <regex.h>
#include <wchar.h>
#include <locale.h>

#include "globals.h"
#include "main_page.h"
#include "game.h"
void start_new_game(int difficulty_level , int  hero_color) ;


int difficulty_level = 1 , music = 0 ;

void continue_game() { 


}

void new_game() { 
    
    start_new_game(difficulty_level , hero_color );
}

void show_scores() { 


}

void change_difficulty() {

    WINDOW *difficulty_win = newwin(15, 60, 14, 55); curs_set(FALSE);
    move(18, 60); clrtoeol(); wattron(difficulty_win, COLOR_PAIR(4)); cbreak(); refresh();

    mvwprintw(difficulty_win, 1, 1, "Select Game Difficulty:");
    mvwprintw(difficulty_win, 3, 1, "1. Hard");
    mvwprintw(difficulty_win, 4, 1, "2. Very Hard");
    mvwprintw(difficulty_win, 5, 1, "3. Back to settings");
    wattroff(difficulty_win, COLOR_PAIR(4));
    wattron(difficulty_win, COLOR_PAIR(1));  attron(A_UNDERLINE); attron(A_BOLD);
    mvwprintw(difficulty_win, 7, 1, "Be fearless and be a hero");
    wattroff(difficulty_win, COLOR_PAIR(1)); attroff(A_UNDERLINE);attroff(A_BOLD);
    wrefresh(difficulty_win);

    while (1) {

        char c = wgetch(difficulty_win);

        if (c == '1') {
            difficulty_level = 1 ; break; health = 1000;

        } else if (c == '2') {
            difficulty_level = 2 ; break; health = 800 ;

        } else if (c == '3') {
            werase(difficulty_win); delwin(difficulty_win); difficulty_level = 1 ; break;

        } else {
            
            WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
}

void change_music(){

    WINDOW *music_win = newwin(15, 60, 14, 55); curs_set(FALSE);
    move(18, 60); clrtoeol(); wattron(music_win, COLOR_PAIR(4)); cbreak(); refresh();

    mvwprintw(music_win, 1, 1, "Select music:");
    mvwprintw(music_win, 3, 1, "1. Interstellar day one");
    mvwprintw(music_win, 4, 1, "2. Mohsen lorestani (suggested)");
    mvwprintw(music_win, 5, 1, "3. Back to settings");
    wattroff(music_win, COLOR_PAIR(4));
    
    wrefresh(music_win);

    while (1) {

        char c = wgetch(music_win);

        if (c == '1') {
            music = 1 ; break;

        } else if (c == '2') {
            music = 2 ; break;

        } else if (c == '3') {
            werase(music_win); delwin(music_win); music = 0 ; break;

        } else {
            
            WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
}
void change_hero_color(){

    WINDOW *color_win = newwin(15, 60, 14, 55);curs_set(FALSE);
    move(18, 60); clrtoeol(); wattron(color_win, COLOR_PAIR(4)); cbreak(); refresh();

    mvwprintw(color_win, 1, 1, "Select hero color:"); 
    mvwprintw(color_win, 5, 1, "3. Back to settings");
    wattroff(color_win, COLOR_PAIR(4));
    wattron(color_win, COLOR_PAIR(3));
    mvwprintw(color_win, 3, 1, "1. blue");
    wattroff(color_win, COLOR_PAIR(3));
    wattron(color_win, COLOR_PAIR(2));
    mvwprintw(color_win, 4, 1, "2. yellow");
    wattroff(color_win, COLOR_PAIR(2));
    
    wrefresh(color_win);

    while (1) {

        char c = wgetch(color_win);

        if (c == '1') {
            hero_color = 1 ; break;

        } else if (c == '2') {
            hero_color = 2 ; break;

        } else if (c == '3') {
            werase(color_win); delwin(color_win); hero_color = 1 ; break;

        } else {
            
            WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
}

void settings() { 

     while (1) {

        WINDOW *settings_win = newwin(15, 60, 14, 55); 
        move(18, 60); clrtoeol(); curs_set(FALSE);
        wattron(settings_win, COLOR_PAIR(4)); cbreak(); refresh();

        mvwprintw(settings_win, 1, 1, "1. Change Game Difficulty");
        mvwprintw(settings_win, 2, 1, "2. Change Hero Color"); 
        mvwprintw(settings_win, 3, 1, "3. Select Background Music"); 
        mvwprintw(settings_win, 4, 1, "4. Back to Main Menu"); 

        wattroff(settings_win, COLOR_PAIR(4)); wrefresh(settings_win); 

        char c = wgetch(settings_win);

        if ( c == '1') {

            change_difficulty();

        } else if ( c == '2') { 

            change_hero_color();

        } else if ( c == '3'){

            change_music();

        } else if ( c == '4'){

            werase(settings_win); delwin(settings_win); break;

        } else {
            
            WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
}
void game_menu() { 

    while (1) {

        WINDOW *menu_win = newwin(15, 60, 14, 55); 
        move(18, 60); clrtoeol(); curs_set(FALSE);
        wattron(menu_win, COLOR_PAIR(4)); cbreak(); refresh();
        mvwprintw(menu_win, 1, 1, "1. Continue Previous Game"); 
        mvwprintw(menu_win, 2, 1, "2. New Game"); 
        mvwprintw(menu_win, 3, 1, "3. Scoreboard");
        mvwprintw(menu_win, 4, 1, "4. Settings");  
        mvwprintw(menu_win, 5, 1, "5. Back to Main Menu");
        wattroff(menu_win, COLOR_PAIR(4)); wrefresh(menu_win); 
    
         // مال تنظیماتن

        char c = wgetch(menu_win);

        if ( c == '1') {

            //continue_game(); 

        } else if ( c == '2') { 

            werase(menu_win);
            wrefresh(menu_win);
            erase();
            refresh();
            new_game();

        } else if ( c == '3'){

            //show_scores();

        } else if ( c == '4'){

            settings(); 

        } else if ( c == '5'){

            werase(menu_win); delwin(menu_win); break; 

        } else {
            
            WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
}
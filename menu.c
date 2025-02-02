#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <regex.h>
#include <wchar.h>
#include <locale.h>
#include "globals.h"

#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

void game_menu();

#endif

#ifndef GAME_H
#define GAME_H

void start_new_game(int difficulty_level , int  hero_color);
#endif
#include "main_page.h"
#include "game.h"

extern void start_new_game( int difficulty_level , int  hero_color );
char name[100];
int point = 0 ;
int health = 1000 ;
int food = 100 ;
int hero_color = 1 ;

void make_color(){

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    init_color( 10 , 500, 500, 500);
    init_pair(5, 10 , COLOR_BLACK); // خاکستری
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_MAGENTA, COLOR_BLACK);// یه صورتی مانند
    init_pair(8, COLOR_CYAN, COLOR_BLACK);// آبی کمرنگ فیروزه ای
}
void create_map(){

    for ( int i = 10 ; i < 169 ; i ++){
        mvprintw(0  , i  , "_");
        mvprintw(35 , i  , "_");
    }

    for ( int i = 1 ; i < 36 ; i++){
        if ( i != 18) {
            mvprintw( i , 10 , "|");
            mvprintw( i , 168 , "|");
        }
    }
}
int check_email(const char *email){ 

    regex_t reg ; int result ;

    const char *pattern = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$";
    result = regcomp(&reg, pattern, REG_EXTENDED); // نفهمیدم دقیق ولی انکاری لازمه

    if (result) return 0 ;

    result = regexec(&reg, email, 0, NULL, 0); // مطابقت داشته باشه صفر میده و اوکیه 
    regfree(&reg);

    return !result ;
}
int check_password(const char *password){

    if (strlen(password) < 7)  
        return 0;

    int upper = 0, lower = 0, digit = 0;
    for (int i = 0; i < strlen(password); i++) {
        if (isupper(password[i])) upper = 1;
        if (islower(password[i])) lower = 1;
        if (isdigit(password[i])) digit = 1;
    }

    return upper && lower && digit ;
}
void random_pass(char *password, int len){

    const char ch[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < len; i++) 
        password[i] = ch[rand() % (sizeof(ch) - 1)]; // مودش رو به اندازه اون بگیریم که بزرگتر ازش نشه 
    
    password[len] = '\0';
    if (!check_password(password)) random_pass(password , 12);
}
int is_username_taken(const char *username) {

    FILE *file = fopen("users.txt", "r");
    if (!file) {
        return 0;
    }

    char line[50];
    while (fgets(line, sizeof(line), file)) {
        
        char stored_username[50];
        sscanf(line, "%s", stored_username);
        if (strcmp(username, stored_username) == 0) {
            fclose(file);
            return 1;
        }
    }  fclose(file);
    return 0;
}
int check_password_correct(const char *username, const char *password) {

    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printw("Error: Cannot open file.\n");
        return 0;
    }
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[50], stored_password[50], stored_email[100];
        sscanf(line, "%s %s %s", stored_username, stored_password, stored_email);
        if (strcmp(username, stored_username) == 0 && strcmp(password, stored_password) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0; 
}
int check_email_correct(const char *username, const char *email) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printw("Error: Cannot open file.\n");
        return 0;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[50], stored_password[50], stored_email[100];
        sscanf(line, "%s %s %s", stored_username, stored_password, stored_email);
        if (strcmp(username, stored_username) == 0 && strcmp(email, stored_email) == 0) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0; 
}
void save_user(const char *username, const char *password, const char *email) {
    FILE *file = fopen("users.txt", "a");
    if (!file) {
        printw("Error: Cannot open file to save user.\n");
        return;
    }

    fprintf(file, "%s %s %s\n", username, password, email);
    fclose(file);
}
void fill_password(const char *username, char *password) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        printw("Error: Cannot open file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char stored_username[50], stored_password[50], stored_email[100];
        sscanf(line, "%s %s %s", stored_username, stored_password, stored_email);
        if (strcmp(username, stored_username) == 0) {
            strcpy(password, stored_password);
            fclose(file);
            return;
        }
    }
}
void trim(char *str) {
    char *end;

    while (isspace((unsigned char) *str)) str++;

    if (*str == 0) return;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;
    *(end + 1) = 0;
}
void get_input(WINDOW *win , char *input, int max_len) {

    char ch; int i = 0 ;

    keypad(stdscr, TRUE);
    wrefresh(win); noecho();

    while (i < max_len - 1) {
        ch = wgetch(win); 

        if (ch == '\n' && i == 0) {

            wprintw(win, "\b");
            wrefresh(win);    
        }
        else if (ch == '\n') break;
        else if (ch == 27) break; // کلید ESC برای لغو
        else if (ch == 127 && i > 0) {
            input[--i] = '\0'; // برای حذف آخرین کاراکتر
            wprintw(win, "\b \b");
            wrefresh(win);
        } else {
            input[i++] = ch;
            wprintw(win, "%c", ch);
            wrefresh(win);
        }
    }
    input[i] = '\0';
    if (max_len == 50) trim(input);   
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void create_account (){ 

    char username[50] , password[50] , email[100] , c ;

    clear();
    WINDOW *win = newwin(15, 60, 14 , 55);
    move( 18 , 60 ); clrtoeol(); wattron(win , COLOR_PAIR(4)); cbreak(); refresh();
    
    mvwprintw( win , 1 , 1 , "1. Enter Username : "); wrefresh(win); wmove(win, 1 , 21 ) ; curs_set(true);
    get_input (win , username , 50);

    if (is_username_taken(username)) {

        wattroff(win ,COLOR_PAIR(4)); wattron(win ,COLOR_PAIR(1));
        wprintw(win, "\nError: Username already taken!\n"); wattroff(win , COLOR_PAIR(1)); wattron(win , COLOR_PAIR(4));
        wrefresh(win); napms(4000);
        clear() ;  endwin();
        create_account();
    }

    mvwprintw( win , 3 , 1 , "2. Enter password : ");wattroff(win , COLOR_PAIR(4)); wattron(win , COLOR_PAIR(5)); mvwprintw( win , 3 , 21 , "press 1 for random");
    wattroff(win , COLOR_PAIR(5)); wattron(win , COLOR_PAIR(4)) ; wmove(win, 3 , 21 ); curs_set(true); wrefresh(win);
    c = getch(); 
    if (c == '1') { random_pass(password , 18); wprintw(win , "%s" , password); }
    else {
        password[0] = c ;wprintw(win , "%c                  " , c); wmove(win, 3 , 22 ); get_input(win, password+1 , 50 );
    } wrefresh(win);

    if (!check_password(password)) {

        wattroff(win , COLOR_PAIR(4)); wattron(win , COLOR_PAIR(1));
        wprintw(win, "\nError: Password must be at least 7 characters long, contain at least one uppercase letter, one lowercase letter, and one digit.\n");
        wattroff(win , COLOR_PAIR(1)); wattron(win , COLOR_PAIR(4));
        wrefresh(win); napms(6000);
        clear() ;  endwin();
        create_account();
    }

    mvwprintw( win , 5 , 1 , "3. Enter your Email Address : "); wrefresh(win); wmove(win , 5 , 32) ; curs_set(true);
    get_input(win, email , 100 ); wrefresh(win);

    if (!check_email(email)) {

        wattroff(win , COLOR_PAIR(4)); wattron(win , COLOR_PAIR(1));
        wprintw(win, "\nError: Invalid email format!\n"); wattroff(win , COLOR_PAIR(1)); wattron(win , COLOR_PAIR(4));
        wrefresh(win); napms(4000);
        clear() ;  endwin();
        create_account();
    }
    save_user(username, password, email);wattroff(win , COLOR_PAIR(4)); wattron(win , COLOR_PAIR(2));
    wprintw(win, "\n\nUser registered successfully!\n"); 
    wrefresh(win); wprintw(win , "\n\n\npress any key to continue..."); wattroff(win , COLOR_PAIR(2));  wrefresh(win);
    getch(); 
    endwin(); strcpy(name , username);
    game_menu();
}

void login (){

    char username[50] , password[50] , email[100] , c ;

    WINDOW *win = newwin(35, 166 , 1 , 10);
    wbkgd(win, COLOR_PAIR(1)) ; attron(COLOR_PAIR(1)); box(win , '|', '-'); attroff(COLOR_PAIR(1));
    move( 18 , 60 ); clrtoeol(); wattron(win , COLOR_PAIR(4)); cbreak(); wrefresh(win);
    
    
    mvwprintw( win , 14 , 46 , "1. Enter Username : "); wrefresh(win); wmove(win, 14 , 66 ) ; curs_set(true);
    get_input (win , username , 50);

    if (!is_username_taken(username)) {

        wattroff(win ,COLOR_PAIR(4)); wattron(win ,COLOR_PAIR(1));
        wprintw(win, "\nError: Username doesn't exist!\n"); wattroff(win , COLOR_PAIR(1)); wattron(win , COLOR_PAIR(4));
        wrefresh(win); napms(2000);
        werase(win);wrefresh(win); delwin(win); refresh();
        login();
    }

    mvwprintw( win , 16 , 46 , "2. Enter password : ");  wrefresh(win); wmove(win, 16 , 66 ); curs_set(true);
    get_input(win, password , 50 ); wrefresh(win);

    if (!check_password_correct(username , password)){ 

        wattroff(win ,COLOR_PAIR(4)); wattron(win ,COLOR_PAIR(1));
        mvwprintw(win , 18 , 46 , "Error: Incorrect password! try again(t)          Forgot password?(F)");
        wrefresh(win); wattroff(win , COLOR_PAIR(1)); wattron(win , COLOR_PAIR(4));
        
        WINDOW *win2 = newwin(35, 166 , 1 , 10);
        wbkgd(win2, COLOR_PAIR(1)) ; attron(COLOR_PAIR(1)); box(win2 , '|', '-'); attroff(COLOR_PAIR(1));
        while (1) {
            c = ' ';
            while (c == ' ' || c == '\n') c = getch();  
    
            if ( c == 'f' || c == 'F'){
                
                delwin(win);
                WINDOW *win = newwin(35, 166 , 1 , 10);
                wbkgd(win, COLOR_PAIR(1)) ; attron(COLOR_PAIR(1)); box(win , '|', '-'); attroff(COLOR_PAIR(1));
                wattron(win , COLOR_PAIR(4)); wrefresh(win);
                mvwprintw( win , 18 , 46 , "3. Enter your Email Address : "); wrefresh(win); wmove(win , 18 , 76) ;
                ; curs_set(true); get_input(win, email , 100 ); 
                wrefresh(win); wattroff(win , COLOR_PAIR(4)) ;

                if ( check_email_correct(username , email)){

                    fill_password(username , password); wattron(win , COLOR_PAIR(2));
                    mvwprintw( win , 12 , 46 , "your password is : "); wmove(win, 12 , 65 );
                    wprintw( win ,"%s" , password); wrefresh(win);
                    wattroff(win , COLOR_PAIR(2)) ; login();

                } else {

                    wattroff(win , COLOR_PAIR(4)); wattron(win , COLOR_PAIR(1));
                    wprintw(win, "\nError: Incorrect email! try again\n"); wattroff(win , COLOR_PAIR(1)); wattron(win , COLOR_PAIR(4));
                    wrefresh(win); napms(4000);
                    clear() ; endwin();
                    login();
                }

            } else if ( c == 't' || c == 'T' ){

                delwin(win);  endwin(); login();
            } else {

                WINDOW *win1 = newwin(10, 30, 24 , 30); 
                wattron(win1 , COLOR_PAIR(1)); mvwprintw(win1 , 1 , 1 ,"Invalid key!" ) ; wattroff(win1 , COLOR_PAIR(1));
                wrefresh(win1); napms(1000); werase(win1);wrefresh(win1); delwin(win1); refresh();
            }
        }
    }
    else {
    strcpy(name , username);
    delwin(win); endwin() ; game_menu();}

}
void main_login(){

    WINDOW *win_main_login = newwin(20, 65, 14 , 55);
    move( 18 , 60 ); clrtoeol(); wattron(win_main_login , COLOR_PAIR(2)); cbreak(); 
    mvwprintw(win_main_login , 4 ,5 , "Have any account?(1)                              Guest(2)");
    wrefresh(win_main_login);
    wattroff(win_main_login , COLOR_PAIR(2));
    int x = 1 ; napms(4000);
    while (x) {
        char c = getch();
        if ( c == '1') {
            x = 0 ; move( 18 , 60 ); clrtoeol(); 
            wrefresh(win_main_login); login ();
        }
        else if ( c == '2') {
            x = 0 ; move( 18 , 60 ); clrtoeol() ;
            strcpy(name , "Guest");
            game_menu();
            break;
        }
        else { WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
}

int main() {
    
    setlocale(LC_ALL, "");
    while (1) {

        clear();
        initscr(); noecho();
        keypad(stdscr, TRUE);
        curs_set(FALSE);
        start_color();
        make_color();

        attron(COLOR_PAIR(1)); attron(A_BOLD);
        mvprintw( 9  , 87 , "ROGUE");  
        attroff(A_BOLD); 
        create_map();
        attroff(COLOR_PAIR(1));

        attron(COLOR_PAIR(2)); 
        mvprintw( 18 , 76 , "press any key to continue..."); 
        attroff(COLOR_PAIR(2));

        getch(); refresh();
        move( 18 , 75); clrtoeol(); refresh();
    
        attron(COLOR_PAIR(2)); mvprintw( 18 , 73 , "Create new account(C) / Login or Guest(L)") ; attroff(COLOR_PAIR(2));
        refresh();

        char c = getch();
    
        if ( c == 'c' || c == 'C') { 

            create_account ();
    
        } else if ( c == 'l' || c== 'L') { 
         
            main_login();
    
        } else { 
        
           WINDOW *win = newwin(10, 30, 24 , 30); 
            wattron(win , COLOR_PAIR(1)); mvwprintw(win , 1 , 1 ,"Invalid key!" ) ; wattroff(win , COLOR_PAIR(1));
            wrefresh(win); napms(1000); werase(win);wrefresh(win); delwin(win); refresh();
        }
    }
    endwin();  
    return 0;
}
#ifndef GLOBALS_H
#define GLOBALS_H

extern char name[100];
extern int point;
extern int health;
extern int food;
extern int hero_color;
void start_new_game( int difficulty_level , int  hero_color );
void draw_detail_win ();
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#include "values.h"

int cube[6][3][3] = {
        {{0,0,0},{0,0,0},{0,0,0}},
        {{1,1,1},{1,1,1},{1,1,1}},
        {{2,2,2},{2,2,2},{2,2,2}},
        {{3,3,3},{3,3,3},{3,3,3}},
        {{4,4,4},{4,4,4},{4,4,4}},
        {{5,5,5},{5,5,5},{5,5,5}},
    };

bool int_in_array(int*, int, int);
void cube_rotate(int, int);
void draw_cube_development();
int main(int argc, char** argv)
{
    int scramble_length = 25;
    if(argc != 1) scramble_length = atoi(argv[1]);
    int history[2]={INT_MAX,INT_MAX};
    int rotate_symbol_id;
    int add_symbol_id;
    srand((unsigned)time(NULL));
    
    for(int i=0;i<scramble_length;i++){
        do {
            rotate_symbol_id = rand()%6;
        } while (int_in_array(history, 2, rotate_symbol_id));
        printf("%c", int_to_rotate_symbol(rotate_symbol_id));
        history[i%2] = rotate_symbol_id;
        
        add_symbol_id = rand()%3; 
        printf("%c ", int_to_add_symbol(add_symbol_id));
    }
    printf("\n");
   
    // DEBUG
    cube_rotate(1,1);
    cube_rotate(2,1);
    cube_rotate(1,0);
    draw_cube_development();
    printf("==============\n");
    cube_rotate(1,1);
    cube_rotate(2,1);
    cube_rotate(1,0);
    draw_cube_development();
    printf("==============\n");
    cube_rotate(1,1);
    cube_rotate(2,1);
    cube_rotate(1,0);
    draw_cube_development();
    printf("==============\n");
    cube_rotate(1,1);
    cube_rotate(2,1);
    cube_rotate(1,0);
    draw_cube_development();
    printf("==============\n");

    
    return 0;
}

void draw_cube_development(){
    // UP(C:W,cube[0])
    for(int i=0;i<3;i++){
        printf("        ");
        for(int j=0;j<3;j++){
            print_block_with_color(cube[0][i][j]);
        }
        printf("\n");
    }
    printf("\n");
    
    //    LEFT(C:O,cube[5])  -> FRONT(C:G,cube[3])
    // -> RIGHT(C:R,cube[4]) -> BACK(C:B,cube[2])
    for(int i=0;i<3;i++){
        // LEFT
        for(int j=0;j<3;j++){
            print_block_with_color(cube[5][i][j]);
        }
        printf("  ");
        // FRONT
        for(int j=0;j<3;j++){
            print_block_with_color(cube[3][i][j]);
        }
        printf("  ");
        // RIGHT
        for(int j=0;j<3;j++){
            print_block_with_color(cube[4][i][j]);
        }
        printf("  ");
        // BACK
        for(int j=0;j<3;j++){
            print_block_with_color(cube[2][i][j]);
        }
        printf("\n");
    }
    printf("\n");
    // DOWN(C:Y,cube[1])
    for(int i=0;i<3;i++){
        printf("        ");
        for(int j=0;j<3;j++){
            print_block_with_color(cube[1][i][j]);
        }
        printf("\n");
    }
    printf("\n");

}

bool int_in_array(int* array, int length, int value)
{
    for(int i=0; i<length; i++)
        if(array[i] == value) return true;
    return false;
}

int* int_array_to_cube_position_p(int val[3])
{
    return &cube[val[0]][val[1]][val[2]];
}

void four_cube_rotate(int val[4][3], int add_symbol_id)
{
    int swap;
    switch(add_symbol_id){
    case 0:
        swap = *int_array_to_cube_position_p(val[0]);
        *int_array_to_cube_position_p(val[0]) = *int_array_to_cube_position_p(val[1]);
        *int_array_to_cube_position_p(val[1]) = *int_array_to_cube_position_p(val[2]);
        *int_array_to_cube_position_p(val[2]) = *int_array_to_cube_position_p(val[3]);
        *int_array_to_cube_position_p(val[3]) = swap;
        break;
    case 1:
        swap = *int_array_to_cube_position_p(val[3]);
        *int_array_to_cube_position_p(val[3]) = *int_array_to_cube_position_p(val[2]);
        *int_array_to_cube_position_p(val[2]) = *int_array_to_cube_position_p(val[1]);
        *int_array_to_cube_position_p(val[1]) = *int_array_to_cube_position_p(val[0]);
        *int_array_to_cube_position_p(val[0]) = swap;
        break;
    case 2:
        swap = *int_array_to_cube_position_p(val[0]);
        *int_array_to_cube_position_p(val[0]) = *int_array_to_cube_position_p(val[2]);
        *int_array_to_cube_position_p(val[2]) = swap;
        swap = *int_array_to_cube_position_p(val[1]);
        *int_array_to_cube_position_p(val[1]) = *int_array_to_cube_position_p(val[3]);
        *int_array_to_cube_position_p(val[3]) = swap;
        break;
    }
}

void cube_rotate(int rotate_symbol_id, int add_symbol_id)
{
    for(int i=0;i<5;i++){
        four_cube_rotate(rotate_list[rotate_symbol_id][i], add_symbol_id);
    }
}
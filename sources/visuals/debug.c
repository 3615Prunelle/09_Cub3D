#include "cub3d.h"

void    ft_spike(t_cube *game, int i, int *borders)
{
     if (i < 10 || i > VIEW_WIDTH - 10)
         return ;
    if (borders[0] < VIEW_HEIGHT / 2 - (int)((((MAP_SCALE / 8) * game->viewdistance / game->rays[i + 1]->length)) / 2)
         && borders[0] > VIEW_HEIGHT / 2 - (int)((((MAP_SCALE / 8) * game->viewdistance / game->rays[i + 2]->length)) / 2) && i < VIEW_WIDTH - 4)
	    printf("%d problems:\t r-6: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r-5: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r-4: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r-3: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r-2: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r-1: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r1: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r2: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r3: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r4: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r5: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r6: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r7: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n", i,
             game->rays[i - 6]->contact_x, game->rays[i - 6]->contact_y, game->rays[i - 6]->step_x, game->rays[i - 6]->step_y, game->rays[i - 6]->length, game->rays[i - 6]->degree,
             game->rays[i - 5]->contact_x, game->rays[i - 5]->contact_y, game->rays[i - 5]->step_x, game->rays[i - 5]->step_y, game->rays[i - 5]->length, game->rays[i - 5]->degree,
             game->rays[i - 4]->contact_x, game->rays[i - 4]->contact_y, game->rays[i - 4]->step_x, game->rays[i - 4]->step_y, game->rays[i - 4]->length, game->rays[i - 4]->degree,
             game->rays[i - 3]->contact_x, game->rays[i - 3]->contact_y, game->rays[i - 3]->step_x, game->rays[i - 3]->step_y, game->rays[i - 3]->length, game->rays[i - 3]->degree,
             game->rays[i - 2]->contact_x, game->rays[i - 2]->contact_y, game->rays[i - 2]->step_x, game->rays[i - 2]->step_y, game->rays[i - 2]->length, game->rays[i - 2]->degree,
             game->rays[i - 1]->contact_x, game->rays[i - 1]->contact_y, game->rays[i - 1]->step_x, game->rays[i - 1]->step_y, game->rays[i - 1]->length, game->rays[i - 1]->degree,
             game->rays[i]->contact_x, game->rays[i]->contact_y, game->rays[i]->step_x, game->rays[i]->step_y, game->rays[i]->length, game->rays[i]->degree,
             game->rays[i + 1]->contact_x, game->rays[i + 1]->contact_y, game->rays[i + 1]->step_x, game->rays[i + 1]->step_y, game->rays[i + 1]->length, game->rays[i + 1]->degree,
             game->rays[i + 2]->contact_x, game->rays[i + 2]->contact_y, game->rays[i + 2]->step_x, game->rays[i + 2]->step_y, game->rays[i + 2]->length, game->rays[i + 2]->degree,
             game->rays[i + 3]->contact_x, game->rays[i + 3]->contact_y, game->rays[i + 3]->step_x, game->rays[i + 3]->step_y, game->rays[i + 3]->length, game->rays[i + 3]->degree,
             game->rays[i + 4]->contact_x, game->rays[i + 4]->contact_y, game->rays[i + 4]->step_x, game->rays[i + 4]->step_y, game->rays[i + 4]->length, game->rays[i + 4]->degree,
             game->rays[i + 5]->contact_x, game->rays[i + 5]->contact_y, game->rays[i + 5]->step_x, game->rays[i + 5]->step_y, game->rays[i + 5]->length, game->rays[i + 5]->degree,
             game->rays[i + 6]->contact_x, game->rays[i + 6]->contact_y, game->rays[i + 6]->step_x, game->rays[i + 6]->step_y, game->rays[i + 6]->length, game->rays[i + 6]->degree);//debug
    else if (borders[0] > VIEW_HEIGHT / 2 - (int)((((MAP_SCALE / 8) * game->viewdistance / game->rays[i + 1]->length)) / 2)
         && borders[0] < VIEW_HEIGHT / 2 - (int)((((MAP_SCALE / 8) * game->viewdistance / game->rays[i + 2]->length)) / 2) && i < VIEW_WIDTH - 4)
	    printf("%d problems:\t r1: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r2: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n\t\t r3: c: [%.3f/%.3f] s: [%.2f/%.2f] l: %.2f d:%.2f\n", i,
             game->rays[i]->contact_x, game->rays[i]->contact_y, game->rays[i]->step_x, game->rays[i]->step_y, game->rays[i]->length, game->rays[i]->degree,
             game->rays[i + 1]->contact_x, game->rays[i + 1]->contact_y, game->rays[i + 1]->step_x, game->rays[i + 1]->step_y, game->rays[i + 1]->length, game->rays[i + 1]->degree,
             game->rays[i +2 ]->contact_x, game->rays[i +2 ]->contact_y, game->rays[i +2 ]->step_x, game->rays[i +2 ]->step_y, game->rays[i +2 ]->length, game->rays[i +2 ]->degree);//debug
}
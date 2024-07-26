#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


#define SPRITE_WIDTH 2
#define SPRITE_HEIGHT 2
#define IMAGE_WIDTH 20
#define IMAGE_HIGHT 20

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *data_addr;
    int     line_size;
    char    **colectable;
}           t_game;

void    put_pixel(char *data_addr, char *color);
void    put_sprite(t_game *game, int pos_x, int pos_y, int version);
void    put_line(char *data_addr, char *sprite_data);

void    put_sprite(t_game *game, int pos_x, int pos_y, int version)
{
    int y = 0;
    while (y < SPRITE_HEIGHT)
    {
        int index = (y + pos_y) * game->line_size + pos_x;
        put_line(&game->data_addr[index], &game->colectable[version][y * SPRITE_WIDTH]);
        y++;
    }
}

void    put_line(char *data_addr, char *sprite_data)
{
    int i = 0;
    while (i < SPRITE_WIDTH)
    {
        if (sprite_data[i*4] != 0)
            put_pixel(&data_addr[i*4], &sprite_data[i*4]);
        i++;
    }
}

void    put_pixel(char *data_addr, char *color)
{
    data_addr[0] = color[0];
    data_addr[1] = color[1];
    data_addr[2] = color[2];
    data_addr[3] = color[3];
}

int main()
{
    int x = 0;
    int y = 0;
    char image[IMAGE_WIDTH * IMAGE_HIGHT] = {0};
    char sprite[SPRITE_WIDTH * SPRITE_HEIGHT] = {1,1,1,1};
    
    t_game *game = malloc(sizeof(t_game));
    if (game == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    game->data_addr = image;
    game->line_size = IMAGE_WIDTH;
    game->colectable = malloc(sizeof(char*));
    if (game->colectable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(game);
        return 1;
    }
    game->colectable[0] = sprite;
    
    put_sprite(game, 1, 1, 0);
    
    y = 0;
    while (y < IMAGE_HIGHT)
    {
        x = 0;
        while (x < IMAGE_WIDTH)
        {
            printf("%d ", image[y * IMAGE_WIDTH + x]);
            x++;
        }
        printf("\n");
        y++;
    }
    
    free(game->colectable);
    free(game);
    
    return 0;
}

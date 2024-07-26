#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SPRITE_WIDTH 2
#define SPRITE_HEIGHT 2

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
    int x, y;
    for (y = 0; y < SPRITE_HEIGHT; y++)
    {
        for (x = 0; x < SPRITE_WIDTH; x++)
        {
            int index = (y + pos_y) * game->line_size + (x + pos_x);
            put_line(&game->data_addr[index], &game->colectable[version][y * SPRITE_WIDTH]);
        }
    }
}

void    put_line(char *data_addr, char *sprite_data)
{
    for (int i = 0; i < SPRITE_WIDTH; i++)
    {
        if (sprite_data[i * 4] != 0)
            put_pixel(&data_addr[i * 4], &sprite_data[i * 4]);
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
    int x, y;
    char image[9] = {0};
    char sprite[4] = {1,1,1,1};
    
    t_game *game = malloc(sizeof(t_game));
    if (game == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    game->data_addr = image;
    game->line_size = 3;
    game->colectable = malloc(sizeof(char*));
    if (game->colectable == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(game);
        return 1;
    }
    game->colectable[0] = sprite;
    
    put_sprite(game, 1, 1, 0);
    
    for (y = 0; y < 3; y++)
    {
        for (x = 0; x < 3; x++)
        {
            printf("%d ", image[y * 3 + x]);
        }
        printf("\n");
    }
    
    free(game->colectable);
    free(game);
    
    return 0;
}

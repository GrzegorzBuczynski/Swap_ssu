
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# define SPRITE_WIDTH 2 //50
# define SPRITE_HIGHT 2 //50

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		line_size;
	char	**colectable;

}			t_game;

void	put_pixel(char *data_addr, char *color);
void	put_sprite(t_game *game, int pos_x, int pos_y, int version);
void	put_line(char *data_addr, char *sprite_data);

//should works
void	put_sprite(t_game *game, int pos_x, int pos_y, int version)
{
	int	x;
	int	y;

	y = 0;
	while (y < pos_y+SPRITE_HIGHT)
	{
		x = y * game->line_size + pos_x;
		put_line(&game->data_addr[x], &game->colectable[version][y * SPRITE_WIDTH]);
	}

}

//should works
void	put_line(char *data_addr, char *sprite_data)
{
	int	i;

	i = 0;
	while (i < SPRITE_WIDTH)
	{
		if (&sprite_data[i * 4] != 0)
			put_pixel(data_addr, &sprite_data[i * 4]);
		i++;
	}
}


//should works
void	put_pixel(char *data_addr, char *color)
{
	data_addr[1] = color[1];
	data_addr[2] = color[2];
	data_addr[3] = color[3];
}



int main()
{
	int x = 0;
	int y = 0;
	int image[9] = {0,0,0,
					0,0,0,
					0,0,0};

	int sprite[4] = {1,1,1,1};
	
	t_game *game = malloc(sizeof(t_game));

	game->data_addr = (char *)&image;
	game->colectable[0] = (char *)&sprite;
	put_sprite(game, 2, 2, 1);
	while (y < 3)
		{
			while(x < 3)
			{
				write(1, image, 1);
				x++;
			}
		y++;
		}

}

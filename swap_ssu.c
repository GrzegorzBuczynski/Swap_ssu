# define SPRITE_WIDTH 50
# define SPRITE_HIGHT 50

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		line_size;

}			t_game;

//in work
void	put_sprite(t_game *game, char *sprite_data, int pos_x, int pos_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < pos_y*SPRITE_HIGHT)
	{
		x = 0;


	while (j < 50)
	{
		while (i < 50)
		{
			if (&sprite_data[j * 50 + i] != 0)
				put_pixel(game->data_addr, &sprite_data[j * 50 + i]);
			i++;
		}
		i = 0;
		j++;
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

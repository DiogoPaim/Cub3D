#include "../cub3d.h"

void	print_map(char **map)
{
	int	row;
	int col;

	row = -1;
	col = -1;
	while (map[++row])
	{
		col = -1;
		while (map[row][++col])
		{
			printf("%c", map[row][col]);
		}
	}
}
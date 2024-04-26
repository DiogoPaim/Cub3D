#include "../cub3d.h"

char	**hard_map(void)
{
	char	**map;
	int		i;

	map = calloc(11 ,sizeof(char *));
	i = 0;
	map[i] = "1111111111\n";
	while (i++ < 8)
	{
		if (i == 5)
			map[i] = "1000N00001\n";
		map[i] = "1000000001\n";
	}
	map[i] = "1111111111\n";
	map[i + 1] = NULL;
	return (map);
}
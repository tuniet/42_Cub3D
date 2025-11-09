#include "../include/cub3D.h"

void initdata(t_data **data)
{
    *data = ft_calloc(1, sizeof(t_data));
    (*data)->map = ft_calloc(1, sizeof(t_map));
    (*data)->game = ft_calloc(1, sizeof(t_game));
    (*data)->map_fd = 0;
}
int main(int ac, char *av[])
{
    t_data *data;
    initdata(&data);
    if(ac != 2 || av[1][0] == '\0')
        return(printf("Error\nUsage: ./cub3D [.cub map]\n"), exit(1), 1);
    mainloop(data);
    return 0;
}

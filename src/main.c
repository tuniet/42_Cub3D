#include "../include/cub3D.h"

void initdata(t_data **data)
{
    *data = calloc(1, sizeof(t_data));
    (*data)->map = calloc(1, sizeof(t_map));
    (*data)->map_fd = 0;
}
int main(int ac, char *av[])
{
    t_data *data;
    initdata(&data);
    if(ac != 2 || av[1][0] == '\0' || !valid_extension(av) || !map_exists(av, data))
        return(printf("Error\nUsage: ./cub3D [.cub map]\n"), exit(1), 1);
    if(!parse_map(data))
        exit(1);
    return 0;
}

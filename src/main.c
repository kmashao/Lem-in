
#include "../includes/lemin.h"

void		init_farm(t_farm *farm)
{
	farm->nb_ants = 0;
	farm->nb_rooms = 0;
	farm->line = NULL;
	farm->start_name = NULL;
	farm->end_name = NULL;
	farm->rooms = NULL;
	farm->file = NULL;
}

void		print_links(t_room *rooms)
{
	t_room	*room;
	t_link	*link;

	room = rooms;
	while (room)
	{
		link = room->link;
		printf("\nNAME: %s ADDRESS:%p\n", room->name, room);
		printf("=--------------------------------------=\n");
		while (link)
		{
			printf("--->Name:%s Address: %p\n", link->room->name, link->room);
			link = link->next;
		}
		room = room->next;
	}
}
void		print_path(t_path *path)
{
	while (path)
	{
		ft_putstr(path->name);
		ft_putstr("->");
		path = path->next;
	}
	ft_putendl("");
}

void print_ant(int ant, char *room)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(room);
	ft_putchar(' ');
}


void print_ant_path(t_path *path, t_farm *farm)
{
	int ant = 1;
	t_path *room = NULL;
	while(ant <= farm->nb_ants)
	{
		room = path;
		while(room)
		{
			print_ant(ant, room->name);
			putchar('\n');
			room = room->next;
		}
		ant++;
	}	
}

int			main(void)
{
	t_farm	farm;
	t_path	*path;

	init_farm(&farm);
	get_num_ants(&farm);
	parse_rooms(&farm);
	parse_links(&farm);
	check_error(&farm);
	print_file(farm.file);
	path = find_start(&farm);
	print_ant_path(path,&farm);
}

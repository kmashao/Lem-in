
#include "../includes/lemin.h"

void			ft_error(char *message)
{
	if (message)
		ft_putendl(message);
	exit(0);
}

static void		no_start_or_end(t_farm *farm)
{
	if (!farm->start_name || !farm->end_name)
		ft_error("Error: start or end room not provided.");
}

static void		duplicate_rooms(t_room *rooms)
{
	t_room		*tmp;
	t_room		*iter;

	tmp = rooms;
	while (tmp->next)
	{
		iter = tmp->next;
		if (tmp->name[0] == 'L')
			ft_error("Error: illegal room name.");
		while (iter)
		{
			if (ft_strequ(tmp->name, iter->name))
				ft_error("Error: duplicate rooms");
			iter = iter->next;
		}
		tmp = tmp->next;
	}
}

void			check_error(t_farm *farm)
{
	no_start_or_end(farm);
	duplicate_rooms(farm->rooms);
}
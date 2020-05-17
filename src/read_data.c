
#include "../includes/lemin.h"

static void		first_link(t_farm *farm)
{
	char **pipe;

	if (!ft_strchr(farm->line, '-') && farm->line[0] != '#')
		ft_error("Error: invalid link");
	if (farm->line[0] != '#')
	{
		pipe = ft_strsplit(farm->line, '-');
		add_link(farm, pipe[0], pipe[1]);
		add_link(farm, pipe[1], pipe[0]);
		ft_del_2D(pipe);
	}
	add_to_file(farm);
	free(farm->line);
}

void			get_num_ants(t_farm *farm)
{
	if (get_next_line(0, &farm->line) < 1)
		ft_error("Error: could not read file");
	while (farm->line[0]== '#' && !ft_strequ(farm->line, "##start") &&
			!ft_strequ(farm->line, "##end"))
		get_next_line(0, &farm->line);
	if (!ft_isnum(farm->line))
		ft_error("Error: invalid ants or no ants given");
	if ((farm->nb_ants = ft_atoi(farm->line)) < 1)
		ft_error("Error: ants value must be >= 1");
	add_to_file(farm);
	free(farm->line);
}

void			parse_rooms(t_farm *farm)
{
	int	len;
	int	status;

	while (get_next_line(0, &farm->line) > 0)
	{
		if (!ft_strchr(farm->line, ' ') && farm->line[0] != '#')
			break ;
		if (!ft_strcmp(farm->line, "##start"))
			status = 1;
		if (!ft_strcmp(farm->line, "##end"))
			status = 2;
		if (farm->line[0] != '#')
		{
			len = ft_strchr(farm->line, ' ') - farm->line;
			add_room(farm, len);
			if (status == 1)
				farm->start_name = ft_strndup(farm->line, len);
			if (status == 2)
				farm->end_name = ft_strndup(farm->line, len);
			status = 0;
		}
		add_to_file(farm);
		free(farm->line);
	}
}

void			parse_links(t_farm *farm)
{
	char **links;

	if (farm->line)
		first_link(farm);
	while (get_next_line(0, &farm->line) > 0)
	{
		if (!ft_strchr(farm->line, '-') && farm->line[0] != '#')
			break ;
		if (farm->line[0] != '#')
		{
			links = ft_strsplit(farm->line, '-');
			if (ft_strequ(links[0], links[1]))
			{
				ft_del_2D(links);
				ft_error("Error: room cannot link to itself");
			}
			add_link(farm, links[0], links[1]);
			add_link(farm, links[1], links[0]);
			ft_del_2D(links);
		}
		add_to_file(farm);
		free(farm->line);
	}
}

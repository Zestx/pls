
#include "ft_ls.h"

t_entry			*ll_generate(t_entry *head, DIR *dir, char *path, char *opts)
{
	struct dirent	*entry;
	char			*new_path;

	new_path = NULL;
	while ((entry = readdir(dir)))
	{
		if (!(new_path = subdir_path(path, entry->d_name)))
			return (NULL);
		if (entry->d_name[0] != '.' || (opts && ft_strchr(opts, 'a')))
		{
			if (!(head = ll_append_node(head, new_path, entry->d_name)))
				return (NULL);

		}
		ft_sfree(new_path);
	}
	return (head);
}

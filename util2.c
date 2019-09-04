/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:50:42 by qbackaer          #+#    #+#             */
/*   Updated: 2019/09/04 19:52:02 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void        init_cursors(t_cursors *llc, t_entry *lst)
{
	llc->curs_c = lst;
	llc->curs_p = llc->curs_c;
	llc->wkst_c = llc->curs_c;
	llc->wkst_p = llc->curs_p;

}

void        alpha_free_wpr(t_entry *entry, char *path)
{
	free(entry->filename);
	free(entry);
	free(path);

}

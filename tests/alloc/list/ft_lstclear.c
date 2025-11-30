/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:55:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:55:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstclear, null_list_noop) { ft_lstclear(NULL, spy_and_free_del); }

Test(ft_lstclear, clears_all_nodes_and_calls_del) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  spy_del_reset();
  ft_lstclear(&list, spy_and_free_del);
  cr_assert_eq(spy_del_count(), 3);
  cr_assert_null(list);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:40:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:40:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstlast, null_returns_null) { cr_assert_null(ft_lstlast(NULL)); }

Test(ft_lstlast, single_returns_same_node) {
  t_list* n = make_int_node(1);
  cr_assert_eq(ft_lstlast(n), n);
  ft_lstdelone(n, free_int_content);
}

Test(ft_lstlast, multiple_returns_last_node) {
  t_list* list = NULL;
  ft_lstadd_back(&list, make_int_node(1));
  ft_lstadd_back(&list, make_int_node(2));
  ft_lstadd_back(&list, make_int_node(3));
  t_list* last = ft_lstlast(list);
  cr_assert_not_null(last);
  cr_assert_eq(*(int*)last->content, 3);
  ft_lstclear(&list, free_int_content);
}

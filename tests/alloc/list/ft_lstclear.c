/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:30:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/list.h"

static int freed_count;
static void counting_del(void* p) {
  (void)p;
  freed_count++;
}

Test(ft_lstclear, clears_all_nodes_and_sets_null) {
  freed_count = 0;
  t_list* a = ft_lstnew(malloc(1));
  t_list* b = ft_lstnew(malloc(1));
  t_list* c = ft_lstnew(malloc(1));

  ft_lstadd_back(&a, b);
  ft_lstadd_back(&a, c);

  ft_lstclear(&a, counting_del);
  cr_assert_null(a);
  cr_assert_eq(freed_count, 3);
}

Test(ft_lstclear, null_list_noop) {
  freed_count = 0;
  ft_lstclear(NULL, counting_del);
  cr_assert_eq(freed_count, 0);
}

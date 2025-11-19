/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:20:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:09:35 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/list.h"

static int* make_int(int v) {
  int* p = malloc(sizeof(*p));
  if (p) *p = v;
  return p;
}

static void free_int(void* p) { free(p); }

Test(ft_lstlast, empty_list) { cr_assert_null(ft_lstlast(NULL)); }

Test(ft_lstlast, single_node) {
  t_list* n = ft_lstnew(make_int(9));
  cr_assert_eq(ft_lstlast(n), n);
  ft_lstdelone(n, free_int);
}

Test(ft_lstlast, multiple_nodes) {
  t_list* a = ft_lstnew(make_int(1));
  t_list* b = ft_lstnew(make_int(2));
  t_list* c = ft_lstnew(make_int(3));
  ft_lstadd_back(&a, b);
  ft_lstadd_back(&a, c);

  cr_assert_eq(ft_lstlast(a), c);

  ft_lstclear(&a, free_int);
}

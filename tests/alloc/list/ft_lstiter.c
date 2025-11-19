/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:35:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "42/alloc/list.h"

static void add_five(void* p) {
  if (!p) return;
  int* x = p;
  *x += 5;
}

Test(ft_lstiter, applies_function_to_each_node) {
  t_list* a = ft_lstnew(malloc(sizeof(int)));
  *(int*)a->content = 1;
  t_list* b = ft_lstnew(malloc(sizeof(int)));
  *(int*)b->content = 2;
  t_list* c = ft_lstnew(malloc(sizeof(int)));
  *(int*)c->content = 3;

  ft_lstadd_back(&a, b);
  ft_lstadd_back(&a, c);

  ft_lstiter(a, add_five);

  cr_assert_eq(*(int*)a->content, 6);
  cr_assert_eq(*(int*)a->next->content, 7);
  cr_assert_eq(*(int*)a->next->next->content, 8);

  ft_lstclear(&a, free);
}

Test(ft_lstiter, null_list_or_function_noop) {
  ft_lstiter(NULL, add_five);
  t_list* a = ft_lstnew(malloc(sizeof(int)));
  *(int*)a->content = 4;
  ft_lstiter(a, NULL);
  cr_assert_eq(*(int*)a->content, 4);
  ft_lstclear(&a, free);
}

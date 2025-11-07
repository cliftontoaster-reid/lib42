/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:25:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:09:42 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/list.h"

static int del_called = 0;
static void del_flag(void* p) {
  (void)p;
  del_called++;
}

Test(ft_lstdelone, calls_del_and_frees_node) {
  del_called = 0;
  int* p = malloc(sizeof(*p));
  *p = 123;
  t_list* n = ft_lstnew(p);

  ft_lstdelone(n, del_flag);
  cr_assert_eq(del_called, 1);
}

Test(ft_lstdelone, null_input_noop) {
  del_called = 0;
  ft_lstdelone(NULL, del_flag);
  cr_assert_eq(del_called, 0);
}

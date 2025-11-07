/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 12:00:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:10:20 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "alloc/list.h"

Test(ft_lstnew, alloc_with_content) {
  int* p = malloc(sizeof(*p));
  cr_assert_not_null(p);
  *p = 42;

  t_list* node = ft_lstnew(p);
  cr_assert_not_null(node);
  cr_assert_eq(node->content, p);
  cr_assert_null(node->next);

  free(p);
  free(node);
}

Test(ft_lstnew, null_content) {
  t_list* node = ft_lstnew(NULL);
  cr_assert_not_null(node);
  cr_assert_null(node->content);
  cr_assert_null(node->next);
  free(node);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 14:30:29 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 14:31:25 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "alloc/vec.h"

Test(vec_free, free_null_pointer_no_crash) {
  vec_free(NULL);
  cr_assert(true);
}

Test(vec_free, free_empty_vector) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  vec_free(v);
  cr_assert(true);
}

Test(vec_free, free_after_push_elements) {
  t_vec* v = vec_create(sizeof(int));
  cr_assert_not_null(v);
  int a = 1, b = 2, c = 3;
  vec_push_back(v, &a);
  vec_push_back(v, &b);
  vec_push_back(v, &c);
  vec_free(v);
  cr_assert(true);
}

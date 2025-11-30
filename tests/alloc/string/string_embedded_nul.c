/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_embedded_nul.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:15:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 21:15:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/alloc/string.h"

Test(string_embedded_nul, find_and_append_with_embedded_null) {
  t_string* s = string_new();
  cr_assert(string_resize(s, 5, '\0'));
  // fill with bytes a b \0 c d
  s->data[0] = 'a';
  s->data[1] = 'b';
  s->data[2] = '\0';
  s->data[3] = 'c';
  s->data[4] = 'd';
  s->size = 5;
  s->data[5] = '\0';

  // find substring "cd" starting at 0 should return index 3
  cr_assert_eq(string_find_cstr(s, "cd", 0), 3);

  // append another t_string with embedded nul
  t_string* t = string_new();
  cr_assert(string_resize(t, 2, '\0'));
  t->data[0] = 'x';
  t->data[1] = '\0';
  t->size = 2;
  t->data[2] = '\0';

  cr_assert(string_append(s, t));
  // appended size increased by 2
  cr_assert_eq(s->size, 7);
  // check tail bytes
  cr_assert_eq(s->data[5], 'x');
  cr_assert_eq(s->data[6], '\0');
  string_free(s);
  string_free(t);
}

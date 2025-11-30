/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_pop_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:10:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:10:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_pop_char, pop_returns_char_and_shrinks) {
  t_string* s = string_from("abc");
  char out;
  cr_assert(string_pop_char(s, &out));
  cr_assert_eq(out, 'c');
  cr_assert_eq(s->size, 2);
  cr_assert_str_eq(string_cstr(s), "ab");
  // pop without out
  cr_assert(string_pop_char(s, NULL));
  cr_assert_eq(s->size, 1);
  string_free(s);
}

Test(string_pop_char, empty_returns_false) {
  t_string* s = string_new();
  char out;
  cr_assert_not(string_pop_char(s, &out));
  string_free(s);
}

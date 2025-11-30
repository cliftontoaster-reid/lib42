/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:00:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:00:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_new, returns_valid_empty_string) {
  t_string* s = string_new();
  cr_assert_not_null(s);
  cr_assert_eq(s->size, 0);
  cr_assert_geq(s->capacity, 1);
  cr_assert(string_tagged(s));
  cr_assert_null(string_cstr(s));
  string_free(s);
}

Test(string_new, can_append_after_new) {
  t_string* s = string_new();
  cr_assert_not_null(s);
  cr_assert(string_append_cstr(s, "hello"));
  cr_assert_eq(s->size, 5);
  cr_assert_not_null(string_cstr(s));
  cr_assert_str_eq(string_cstr(s), "hello");
  string_free(s);
}

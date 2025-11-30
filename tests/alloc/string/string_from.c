/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_from.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:05:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:05:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_from, null_returns_empty_string) {
  t_string* s = string_from(NULL);
  cr_assert_not_null(s);
  cr_assert_eq(s->size, 0);
  cr_assert(string_tagged(s));
  cr_assert_null(string_cstr(s));
  string_free(s);
}

Test(string_from, copies_content_and_not_aliases_input) {
  const char* input = "hello world";
  t_string* s = string_from(input);
  cr_assert_not_null(s);
  cr_assert_eq(s->size, 11);
  char* c = string_cstr(s);
  cr_assert_not_null(c);
  cr_assert_str_eq(c, input);
  // Ensure the underlying data pointer is distinct from the input literal
  cr_assert_neq((void*)c, (void*)input);
  string_free(s);
}

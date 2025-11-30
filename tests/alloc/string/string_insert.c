/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:30:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 19:30:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_insert_string, insert_middle_and_edges) {
  t_string* s = string_from("helloworld");
  t_string* ins = string_from(" ");
  // insert space at position 5 to make "hello world"
  cr_assert(string_insert_string(s, 5, ins));
  cr_assert_str_eq(string_cstr(s), "hello world");
  // insert at beginning
  cr_assert(string_insert_string(s, 0, ins));
  cr_assert_str_eq(string_cstr(s), " hello world");
  // insert at end
  cr_assert(string_insert_string(s, s->size, ins));
  cr_assert_str_eq(string_cstr(s), " hello world ");
  string_free(s);
  string_free(ins);
}

Test(string_insert_cstr, pos_out_of_bounds_returns_false) {
  t_string* s = string_from("abc");
  cr_assert_not(string_insert_cstr(s, 4, "x"));
  string_free(s);
}

Test(string_insert, null_src_returns_false) {
  t_string* s = string_from("a");
  cr_assert_not(string_insert(s, 1, NULL));
  string_free(s);
}

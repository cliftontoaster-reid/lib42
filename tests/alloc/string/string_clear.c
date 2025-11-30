/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:05:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 21:05:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_clear, clears_size_and_zeroes_data_but_keeps_capacity) {
  t_string* s = string_from("abcdef");
  size_t cap = s->capacity;
  string_clear(s);
  cr_assert_eq(s->size, 0);
  cr_assert_eq(s->capacity, cap);
  cr_assert_null(string_cstr(s));
  string_free(s);
}

Test(string_clear, clear_null_is_noop) {
  string_clear(NULL);  // should not crash
}

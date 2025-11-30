/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_reserve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:05:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:05:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_reserve, increases_capacity) {
  t_string* s = string_new();
  size_t initial = s->capacity;
  cr_assert(string_reserve(s, initial * 4 + 1));
  cr_assert_geq(s->capacity, initial * 4 + 1);
  string_free(s);
}

Test(string_reserve, noop_when_sufficient) {
  t_string* s = string_from("abc");
  size_t before = s->capacity;
  cr_assert(string_reserve(s, before));
  cr_assert_eq(s->capacity, before);
  string_free(s);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_shrink_to_fit.c                              :+:      :+:    :+: */
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

Test(string_shrink_to_fit, shrinks_capacity_to_fit_size) {
  t_string* s = string_from("hello_world");
  // increase capacity
  cr_assert(string_reserve(s, 1024));
  size_t large = s->capacity;
  cr_assert_geq(large, 1024);
  // shrink to fit
  cr_assert(string_shrink_to_fit(s));
  cr_assert_lt(s->capacity, large);
  cr_assert_geq(s->capacity, s->size + 1);
  string_free(s);
}

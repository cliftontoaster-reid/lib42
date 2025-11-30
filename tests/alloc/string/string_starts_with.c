/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_starts_with.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell <lfiorell@student.42nice.fr>               +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:30:00 by lfiorell          #+#    #+#             */
/*   Updated: 2025/11/30 20:30:00 by lfiorell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>

#include "42/alloc/string.h"
#include "support/string_helpers.h"

Test(string_starts_with, prefix_cases) {
  t_string* s = string_from("https://example.com");
  cr_assert(string_starts_with(s, "https://"));
  cr_assert_not(string_starts_with(s, NULL));
  cr_assert(string_starts_with(s, ""));
  cr_assert_not(string_starts_with(s, "http://examples://"));
  string_free(s);
}

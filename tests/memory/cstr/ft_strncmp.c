/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:12:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strncmp, equal_within_n) {
  cr_assert_eq(ft_strncmp("hello", "hello", 5), 0);
}

Test(ft_strncmp, equal_n_less_than_len) {
  cr_assert_eq(ft_strncmp("hello", "help", 3), 0);
}

Test(ft_strncmp, different_within_n) {
  cr_assert_lt(ft_strncmp("abc", "abd", 3), 0);
}

Test(ft_strncmp, n_zero) { cr_assert_eq(ft_strncmp("abc", "xyz", 0), 0); }

Test(ft_strncmp, n_larger_than_strings) {
  cr_assert_eq(ft_strncmp("hi", "hi", 10), 0);
}

Test(ft_strncmp, first_less_second) {
  cr_assert_lt(ft_strncmp("abc", "abd", 5), 0);
}

Test(ft_strncmp, first_greater_second) {
  cr_assert_gt(ft_strncmp("xyz", "abc", 5), 0);
}

Test(ft_strncmp, empty_strings) { cr_assert_eq(ft_strncmp("", "", 5), 0); }

Test(ft_strncmp, empty_vs_nonempty) { cr_assert_lt(ft_strncmp("", "a", 1), 0); }

Test(ft_strncmp, nonempty_vs_empty) { cr_assert_gt(ft_strncmp("a", "", 1), 0); }

Test(ft_strncmp, stops_at_n) {
  /* even though strings differ later, only compare first n */
  cr_assert_eq(ft_strncmp("testing123", "testing456", 7), 0);
}

Test(ft_strncmp, unsigned_comparison) {
  const char s1[] = {(char)250, '\0'};
  const char s2[] = {(char)100, '\0'};
  int result = ft_strncmp(s1, s2, 1);
  cr_assert_gt(result, 0); /* 250 > 100 unsigned */
}

Test(ft_strncmp, comparison_with_libc) {
  const char* pairs[][2] = {{"hello", "hello"},    {"abc", "abd"},
                            {"test", "testing"},   {"", ""},
                            {"same", "different"}, {"prefix", "prefix123"}};
  size_t ns[] = {5, 3, 4, 0, 10, 6};
  for (size_t i = 0; i < sizeof(pairs) / sizeof(pairs[0]); i++) {
    int ft_result = ft_strncmp(pairs[i][0], pairs[i][1], ns[i]);
    int libc_result = strncmp(pairs[i][0], pairs[i][1], ns[i]);
    if (ft_result < 0)
      cr_assert_lt(libc_result, 0);
    else if (ft_result > 0)
      cr_assert_gt(libc_result, 0);
    else
      cr_assert_eq(libc_result, 0);
  }
}

Test(ft_strncmp, partial_match) {
  cr_assert_eq(ft_strncmp("abcdef", "abcxyz", 3), 0);
  cr_assert_neq(ft_strncmp("abcdef", "abcxyz", 4), 0);
}

Test(ft_strncmp, single_char) {
  cr_assert_eq(ft_strncmp("a", "a", 1), 0);
  cr_assert_lt(ft_strncmp("a", "b", 1), 0);
}

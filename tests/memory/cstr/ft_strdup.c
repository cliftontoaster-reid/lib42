/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@invalid>                   +#+  +:+       +#+ */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by copilot           #+#    #+#             */
/*   Updated: 2025/11/07 10:12:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strdup, duplicate_simple_string) {
  const char* src = "hello";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, src);
  cr_assert_neq(dup, src); /* different pointers */
  free(dup);
}

Test(ft_strdup, duplicate_empty_string) {
  const char* src = "";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "");
  free(dup);
}

Test(ft_strdup, returns_new_pointer) {
  const char* src = "test";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_neq(dup, src);
  free(dup);
}

Test(ft_strdup, null_terminated) {
  const char* src = "abc";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_eq(dup[3], '\0');
  free(dup);
}

Test(ft_strdup, long_string) {
  const char* src = "This is a much longer string to test duplication";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, src);
  free(dup);
}

Test(ft_strdup, with_special_chars) {
  const char* src = "hello\tworld\n!";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, src);
  free(dup);
}

Test(ft_strdup, modify_dup_not_affect_original) {
  const char* src = "original";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  dup[0] = 'X';
  cr_assert_str_eq(src, "original");
  cr_assert_str_eq(dup, "Xriginal");
  free(dup);
}

Test(ft_strdup, comparison_with_libc) {
  const char* strings[] = {"test", "", "hello world", "a", "123"};
  for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
    char* ft_dup = ft_strdup(strings[i]);
    char* libc_dup = strdup(strings[i]);
    cr_assert_not_null(ft_dup);
    cr_assert_not_null(libc_dup);
    cr_assert_str_eq(ft_dup, libc_dup);
    free(ft_dup);
    free(libc_dup);
  }
}

Test(ft_strdup, single_char) {
  const char* src = "x";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "x");
  free(dup);
}

Test(ft_strdup, numbers_and_symbols) {
  const char* src = "12345!@#$%";
  char* dup = ft_strdup(src);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, src);
  free(dup);
}

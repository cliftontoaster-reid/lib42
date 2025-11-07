/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strndup, duplicate_entire_string) {
  const char* src = "hello";
  char* dup = ft_strndup(src, 10);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "hello");
  free(dup);
}

Test(ft_strndup, duplicate_partial_string) {
  const char* src = "hello";
  char* dup = ft_strndup(src, 3);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "hel");
  free(dup);
}

Test(ft_strndup, n_zero) {
  const char* src = "hello";
  char* dup = ft_strndup(src, 0);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "");
  free(dup);
}

Test(ft_strndup, n_equals_length) {
  const char* src = "test";
  char* dup = ft_strndup(src, 4);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "test");
  free(dup);
}

Test(ft_strndup, always_null_terminated) {
  const char* src = "abcdef";
  char* dup = ft_strndup(src, 3);
  cr_assert_not_null(dup);
  cr_assert_eq(dup[3], '\0');
  cr_assert_str_eq(dup, "abc");
  free(dup);
}

Test(ft_strndup, empty_string) {
  const char* src = "";
  char* dup = ft_strndup(src, 5);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "");
  free(dup);
}

Test(ft_strndup, single_char) {
  const char* src = "a";
  char* dup = ft_strndup(src, 1);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "a");
  free(dup);
}

Test(ft_strndup, returns_new_pointer) {
  const char* src = "test";
  char* dup = ft_strndup(src, 4);
  cr_assert_not_null(dup);
  cr_assert_neq(dup, src);
  free(dup);
}

Test(ft_strndup, n_larger_than_string_length) {
  const char* src = "hi";
  char* dup = ft_strndup(src, 100);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "hi");
  cr_assert_eq(strlen(dup), 2);
  free(dup);
}

Test(ft_strndup, with_special_chars) {
  const char* src = "tab\there";
  char* dup = ft_strndup(src, 5);
  cr_assert_not_null(dup);
  cr_assert_eq(memcmp(dup, "tab\th", 5), 0);
  cr_assert_eq(dup[5], '\0');
  free(dup);
}

Test(ft_strndup, modify_dup_not_affect_original) {
  const char* src = "original";
  char* dup = ft_strndup(src, 4);
  cr_assert_not_null(dup);
  dup[0] = 'X';
  cr_assert_eq(src[0], 'o');
  cr_assert_str_eq(dup, "Xrig");
  free(dup);
}

Test(ft_strndup, long_string_partial) {
  const char* src = "This is a very long string";
  char* dup = ft_strndup(src, 7);
  cr_assert_not_null(dup);
  cr_assert_str_eq(dup, "This is");
  free(dup);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "memory/cstr.h"

Test(ft_strlen, empty_string) {
  const char* s = "";
  cr_assert_eq(ft_strlen(s), 0);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, single_char) {
  const char* s = "a";
  cr_assert_eq(ft_strlen(s), 1);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, normal_string) {
  const char* s = "hello";
  cr_assert_eq(ft_strlen(s), 5);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, string_with_spaces) {
  const char* s = "hello world";
  cr_assert_eq(ft_strlen(s), 11);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, string_with_special_chars) {
  const char* s = "hello\tworld\n!";
  cr_assert_eq(ft_strlen(s), 13);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, long_string) {
  const char* s =
      "This is a much longer string to test the function with more characters";
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, string_with_numbers) {
  const char* s = "123456789";
  cr_assert_eq(ft_strlen(s), 9);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, string_with_nulls_before_end) {
  const char s[] = "hello\0world";
  /* strlen stops at first null */
  cr_assert_eq(ft_strlen(s), 5);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, very_long_string) {
  char s[1001];
  memset(s, 'a', 1000);
  s[1000] = '\0';
  cr_assert_eq(ft_strlen(s), 1000);
  cr_assert_eq(ft_strlen(s), strlen(s));
}

Test(ft_strlen, unicode_utf8_multibyte) {
  const char* s = "héllo wørld";
  /* strlen counts bytes, not characters */
  cr_assert_eq(ft_strlen(s), strlen(s));
}

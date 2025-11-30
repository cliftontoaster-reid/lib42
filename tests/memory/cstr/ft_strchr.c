/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:12:00 by lfiorell@st           #+#    #+# */
/*   Updated: 2025/11/07 14:11:58 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <string.h>

#include "42/memory/cstr.h"

Test(ft_strchr, char_found_at_start) {
  const char* s = "hello";
  char* result = ft_strchr(s, 'h');
  cr_assert_eq(result, s);
}

Test(ft_strchr, char_found_in_middle) {
  const char* s = "hello";
  char* result = ft_strchr(s, 'l');
  cr_assert_eq(result, s + 2);
}

Test(ft_strchr, char_found_at_end) {
  const char* s = "hello";
  char* result = ft_strchr(s, 'o');
  cr_assert_eq(result, s + 4);
}

Test(ft_strchr, char_not_found) {
  const char* s = "hello";
  char* result = ft_strchr(s, 'x');
  cr_assert_null(result);
}

Test(ft_strchr, find_null_terminator) {
  const char* s = "hello";
  char* result = ft_strchr(s, '\0');
  cr_assert_eq(result, s + 5);
}

Test(ft_strchr, empty_string_find_null) {
  const char* s = "";
  char* result = ft_strchr(s, '\0');
  cr_assert_eq(result, s);
}

Test(ft_strchr, empty_string_find_char) {
  const char* s = "";
  char* result = ft_strchr(s, 'a');
  cr_assert_null(result);
}

Test(ft_strchr, first_occurrence) {
  const char* s = "hello";
  char* result = ft_strchr(s, 'l');
  cr_assert_eq(result, s + 2); /* finds first 'l', not second */
}

Test(ft_strchr, special_characters) {
  const char* s = "hello\tworld";
  char* result = ft_strchr(s, '\t');
  cr_assert_eq(result, s + 5);
}

Test(ft_strchr, comparison_with_libc) {
  const char* strings[] = {"test", "hello world", "", "a", "find me!"};
  int chars[] = {'t', 'o', 'x', 'a', '!', '\0'};
  for (size_t i = 0; i < sizeof(strings) / sizeof(strings[0]); i++) {
    for (size_t j = 0; j < sizeof(chars) / sizeof(chars[0]); j++) {
      char* ft_result = ft_strchr(strings[i], chars[j]);
      char* libc_result = strchr(strings[i], chars[j]);
      cr_assert_eq(ft_result, libc_result);
    }
  }
}

Test(ft_strchr, unsigned_char_cast) {
  const char* s = "test";
  /* c is passed as int but treated as unsigned char */
  char* result = ft_strchr(s, 't' + 256);
  cr_assert_eq(result, s); /* should find 't' */
}

Test(ft_strchr, binary_data) {
  const char s[] = {1, 2, 3, 4, 0};
  char* result = ft_strchr(s, 3);
  cr_assert_eq(result, s + 2);
}

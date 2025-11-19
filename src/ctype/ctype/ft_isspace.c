/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:48:27 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:55:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "42/ctype/ctype.h"

bool ft_isspace(char c) {
  unsigned char uc = (unsigned char)c;
  return (uc == ' ') || (uc == '\f') || (uc == '\n') || (uc == '\r') ||
         (uc == '\t') || (uc == '\v');
}

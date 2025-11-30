/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfiorell@student.42nice.fr <lfiorell>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:46:43 by lfiorell@st       #+#    #+#             */
/*   Updated: 2025/11/07 10:55:38 by lfiorell@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "42/ctype/ctype.h"

bool ft_isprint(char c) {
  unsigned char uc = (unsigned char)c;
  return uc >= 32 && uc <= 126;
}

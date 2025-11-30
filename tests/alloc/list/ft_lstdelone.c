/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: github-lfiorell <lfiorell@student.42nice.fr>        +#+  +:+       +#+
 */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:50:00 by lfiorell            #+#    #+# */
/*   Updated: 2025/11/30 19:50:00 by lfiorell           ###   ########.fr */
/*                                                                            */
/* ************************************************************************** */

#include <criterion/criterion.h>
#include <stdlib.h>

#include "support/list_helpers.h"

Test(ft_lstdelone, del_called_and_frees_content_on_standalone_node) {
  t_list* node = make_int_node(42);
  spy_del_reset();
  ft_lstdelone(node, spy_and_free_del);
  cr_assert_eq(spy_del_count(), 1);
}

Test(ft_lstdelone, del_not_called_when_del_is_null) {
  t_list* node = make_int_node(1);
  spy_del_reset();
  ft_lstdelone(node, NULL);
  cr_assert_eq(spy_del_count(), 0);
}

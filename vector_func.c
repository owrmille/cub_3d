/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meroshen <meroshen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:39:17 by meroshen          #+#    #+#             */
/*   Updated: 2024/12/20 23:41:35 by meroshen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector	vector_create(double x, double y)
{
	t_vector	a;

	a.x = x;
	a.y = y;
	return (a);
}

t_int_vector	vector_int_create(int x, int y)
{
	t_int_vector	a;

	a.x = x;
	a.y = y;
	return (a);
}

t_vector	vector_koef(t_vector a, double koef)
{
	a.x *= koef;
	a.y *= koef;
	return (a);
}

t_vector	vector_add(t_vector a, t_vector b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vector	vector_rot(t_vector a, double alpha)
{
	t_vector	rot;

	rot.x = cos(alpha) * a.x + sin(alpha) * a.y;
	rot.y = -sin(alpha) * a.x + cos(alpha) * a.y;
	return (rot);
}

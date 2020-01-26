/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_rand.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/26 18:04:48 by chamada      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/26 18:05:44 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

unsigned int	ft_rand(unsigned int min, unsigned int max)
{
	static unsigned int	rand = 0xACE1U;

	if (min == max)
		return (min);
	rand += 0x3AD;
	rand %= max;
	while (rand < min)
		rand = rand + max - min;
	return (rand);
}

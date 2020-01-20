/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redirections.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: chamada <chamada@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 22:36:56 by plamtenz     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/20 08:49:33 by chamada     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
int     redirections(t_cmd *prcss1, char *fn, int status)
{
    int     pid;
    int     fd;
    char    *std;

    if ((pid = fork()) < 0)
        return (-1);
    if (!pid && status & OP_SDTIN) /*   '<'   */
    {
        ft_mencpy(std, prcss1->av[]); //end , don tknow i need this line
        if ((fd = open(fn, O_RDONLY, 0)) < 0)
            return (-1);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    else if (!pid && status & OP_STDOUT)/* '>'    */
    {
        ft_mencpy(std, prcss1->av[]); //end
        if ((fd = open(fn, O_CREAT, 0)) < 0) // create AND WRITE CHECK SECOND AND THIRD PARAM
            return (-1);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
    //here i excute command using stdin or out
    while (!(wait(NULL) > 0))
        ;





}
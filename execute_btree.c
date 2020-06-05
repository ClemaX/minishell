#include "btree.h"
#include "lexer.h"
#include "ft_term.h"

#define BASH_ERROR_CODE      127

int g_pid;

int         builting_not_in_slash_bin(char *name, char **argv, t_term *t)
{
    if (!ft_strncmp(name, "echo", 5))
        return (ft_echo()); // false is true
    else if (!ft_strncmp(name, "cd", 3))
        return (ft_cd());
    else if (!ft_strncmp(name, "pwd", 4))
        return (ft_pwd());
    else if (!ft_strncmp(name, "export", 7))
        return (ft_export());
    else if (!ft_strncmp(name, "unset", 6))
        return (ft_unset());
    else if (!ft_strncmp(name, "env", 4))
        return (ft_env());
    else if (!ft_strncmp(name, "exit", 5))
        return (ft_exit());
    return (true);
}

void        set_redirection(t_token *bt)
{        
    if (bt->next && bt->type & S_DG && (bt->next->type |= NOT_REPEAT))
        bt->next->type |= S_DG;
    else if (bt->next && bt->type & S_G && (bt->next->type |= NOT_REPEAT))
        bt->next->type |= S_G;
    else if (bt->next && bt->type & S_DL && (bt->next->type |= NOT_REPEAT))
        bt->next->type |= S_DL;
    else if (bt->next && bt->type & S_L && (bt->next->type |= NOT_REPEAT))
        bt->next->type |= S_L;
}

int         execute_redirection(t_token *bt, t_term *t)
{
    // think about redirections with ()
    if (bt->type & NOT_REPEAT)
        ; // do nothing just is the path, just save pid status * last pid status if it exist and put symbol in next <--- IMPORTANT AF (AND OR)
    else if (bt->next && bt->next->type & NOT_REPEAT)
    {
        if (bt->type & S_DG)
            execute_double_graether();
        else if (bt->type & S_G)
            execute_graether();
        else if (bt->type & S_DL)
            execute_double_lesser();
        else if (bt->type & S_L)
            execute_lesser();
        // need to save pid in all cases here
    }
    return (execute_btree(bt->next, t));
}

int        execute_simple_comand(t_token *bt, t_term *t)
{
    char **argv = data_tokenize(bt);
    char *name = argv[0];
    (*argv)++;
    if (bt->type & S_G || bt->type & S_L || bt->type & S_DG || bt->type & S_DL)
    {
        set_redirection(bt);
        return (execute_redirection(bt, t));
    }
    if (bt->type & S_INOR || bt->type & S_INAND)
        ; // save pid status * last pid status if it exist and put symbol in next <--- IMPORTANT AF (AND OR)
    else if (builting_not_in_slash_bin(name, argv, t) && !(g_pid = fork()))
    {
        execve(get_path(name), argv, t->env); // remenber to pass the good env here
        ft_printf("execve returned! errno is [%d]\n", name); // name or errno ?
		return (true);
    }
    else if (g_pid < 0)
        return (BASH_ERROR_CODE);
    while (waitpid(g_pid, NULL, 0) < 0)
		;
	g_pid = 0;
	return (execute_btree(bt->next, t));
}

int         execute_pipe(t_token *bt, t_term *t)
{
    if (bt->type & S_PIPE && bt->next)
        bt->next->type |= S_PIPE2;
    ; // execute the cmd
    ; // save ret value
    ; // save fd 
    ; // next bt has to have a pipe symbol
    if ((bt->type & S_INAND || bt->type & S_INOR) && bt->type & S_PIPE2)
        ; // save ret status * last ret status if it exist and put symbol in next <--- IMPORTANT AF (AND OR)
    if (!(bt->type & NOT_REPEAT) && !(bt->type & S_PIPE))
        set_redirection(bt);
    if (bt->type & S_PIPE2) // check in this condition if next->type & NOT_REPEAT
        ; // to stuff for the second part
    if (bt->next && bt->next->type & NOT_REPEAT)
        execute_redirection(bt, t);
    else
        return(execute_btree(bt->next, t));
    
}

bool        execute_job(t_token *bt, t_term *t)
{
    if (bt->type & S_PIPE || bt->type & S_PIPE2)
        execute_pipe(bt, t);
    else if (bt->type & NONE || !(bt->type & NOT_REPEAT))
        execute_simple_command(bt, t);
    else if (bt->type & NOT_REPEAT) // not good
        execute_redirection(bt, t);
}

bool        execute_btree(t_token *bt, t_term *t)
{
    if (bt == NULL)
        return (true);
    else if (bt->type & S_SEM) // works if sem has same status structure than && || |
    {
        bt->type &= ~S_INAND;
        bt->type &= ~S_INOR;
    }
    else if (bt->type & OPEN_PAR)
        ; // check if operator before, true ? inherit it, () status = () status + 1 and inherit it until ')' 
        ; // check if pipe before, true ? calc () and inherit and special symbol for this case until ')'
        ; // in all the cases calc the value into
    else if (bt->type & CLOSE_PAR)
        ; // conditionals has been calculated, if after oprator give the result to operator, () status = () status - 1
        ; // takes the value of the calc of (), do something with symbols for take this value to pipe2
        ; // check if after has a pipe, takes the calc value to pipe
        ; // check if redirection after, redirect value () to filepath
    execute_job(bt, t);
}
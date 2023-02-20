#ifndef PARSER_H
#define PARSER_H
# include <signal.h>
#include "../lib_ft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <sys/stat.h>


typedef struct s_lexer
{
  char *src;
  int index;
  char c;
}             t_lexer;

typedef struct s_global_data{
	int		exit_status;
	t_list	*env;
}	t_global_data;

t_global_data	g_data;

typedef struct s_parser
{
  char    **cmd;
  int     in_file;
  int     out_file;
  
}             t_parser;

typedef struct s_token
{
  char *value;
  enum
  {
    TOKEN_STRING,
    TOKEN_REDIRECT,
    TOKEN_LREDIRECT, 
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_PIPE,
    TOKEN_EOF,
  }type;
}           t_token;

typedef struct s_env
{
	char	*key;
	char	separateur;
	char	*value;
}             t_env;

          //lexer//
void    init_lexer(t_lexer *lexer ,char *src);
void    lexer_next(t_lexer * lexer);
void    skip_spaces(t_lexer *lexer);
char    *append_to_str(char *str , char c);
t_list  *lexer(char *src);

          //tokenizer//
t_token *init_token(char *value, int type);
t_token *_switch(t_lexer *lexer);
t_token *get_token(t_lexer *lexer);
void    debug_print_token(t_token *token);
int     istoken(char c);
        
          //parser//
t_list  *fill_command(t_list *tokens);
int     check_syntax(t_list *tokens);
void    init_parser(t_parser *cmd);
char	*string_parser(char *str);

        //parser_utils.c//
void  deallocate(t_list *list);
void  ft_free(char	**t);
char  **realloc_cmd(char **cmd, char *str);
void  debug_print_token(t_token *token);
void  print_tokens(t_list *list);
void  print_cmd(t_list *list);
char *expand(char *result, char *var_name);
char *get_var_name(char *str);

       //execution_utils.c//
t_list  *get_env(char **env);
size_t  get_env_size(char **env);
char    *add_path(char *cmd);
char    **env_to_tab(t_list *list);


      //builtins//
int		builtins(t_list *list);
void	ft_unset(char **var);
void	ft_env(void);
void	ft_export(char **var);
void	ft_pwd(void);
void	ft_echo(char **s);
void	ft_exit(char **s);
void	ft_cd(char **s);
int	size_par(char **s);
char	*get_new_env(char *s);
int	check_builtin(t_list *list);

      //execut//
int   start(t_list *list);
void  execute(t_list *cmds , char **env);

      // signlas // 
void handler();
void rl_replace_line (char *, int);

#endif

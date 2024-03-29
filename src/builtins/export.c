#include "../../include/minishell.h"

/*
PARAMETERS
      A  parameter  is an entity that stores values.  It can be a name, a number, or one of the special characters listed below under Special Parameters.  A
       variable is a parameter denoted by a name.  A variable has a value and zero or more attributes.  Attributes are assigned  using  the  declare  builtin
       command (see declare below in SHELL BUILTIN COMMANDS).

       A  parameter  is  set  if  it has been assigned a value.  The null string is a valid value.  Once a variable is set, it may be unset only by using the
       unset builtin command (see SHELL BUILTIN COMMANDS below).

       A variable may be assigned to by a statement of the form

              name=[value]

       If value is not given, the variable is assigned the null string.  All values undergo tilde expansion, parameter and variable expansion,  command  sub-
       stitution,  arithmetic  expansion, and quote removal (see EXPANSION below).  If the variable has its integer attribute set, then value is evaluated as
       an arithmetic expression even if the $((...)) expansion is not used (see Arithmetic Expansion below).  Word  splitting  is  not  performed,  with  the
       exception  of  "$@" as explained below under Special Parameters.  Pathname expansion is not performed.  Assignment statements may also appear as argu-
       ments to the alias, declare, typeset, export, readonly, and local builtin commands.*/

// export varname=varval
// export varname="varval"
// export varname=""
// export varname=
/* 
export 0="ONE"
bash: export: `0=ONE': not a valid identifier 
echo $?  -> 1


*/

void  print_export_error(char *var, char *val, char *message)
{

      ft_putstr_fd("bash: export: `", 2);
      if (var)
            ft_putstr_fd(var, 2);
      ft_putstr_fd(val, 2);
      ft_putchar_fd('\'', 2);
      ft_putstr_fd(message, 2);
      ft_putstr_fd("\n", 2);
}

int is_valid_var_start(unsigned char c)
{
      if (ft_isalnum(c) || c == '_')
            return (1);
      else
            return (0);
}

int is_valid_var_char(char *var)
{
      int i = 0;

      while (var[i] != '\0')
      {
            if (!(ft_isalpha((unsigned char)var[i]) || var[i] == '_'))
                  return (0);
            i ++;
      }
      return (1);
}

char *remove_one_quote_set(char *str)
{
      size_t end;

      end = 0;
      end = ft_strlen(str) - 1;
      if (str[0] == '\'' && str[end] == '\'')
            str = ft_strtrim(str, "\'");
      else if (str[0] == '\"' && str[end] == '\"')
            str = ft_strtrim(str, "\"");
      return (str);
}

void   export_one_var(char **arr, t_envp *my_data)
{
      char *var;
      char *val;
      char *str;

      var = arr[0];
      val = arr[1];
      if (val == NULL)
            val = ft_strdup("");
      str = ft_strjoin(var, ft_strdup("="));
      str = ft_strjoin(str, val);
      printf("%s\n", str);
      unset_one_var(var, my_data);
      ft_lstadd_back(&my_data->envlist, ft_lstnew(str));
      my_data->count++;
}

void  print_variables_list(char **arr)
{
      int i = 0;

      if (!arr || !arr[i])
            return;
      while (arr[i])
      {
            ft_putstr_fd("declare -x ", STDOUT_FILENO);
            ft_putendl_fd(arr[i], STDOUT_FILENO);
            i ++;
      }
}

void real_export(char **argv, t_envp *my_data)
{
      char *arr[3];
      int i = 1;
      char **temp = NULL;

      arr[0] = NULL;
      arr[1] = NULL;
      arr[2] = NULL;
      while(argv[i] != NULL)
      {
            if (ft_strchr(argv[i], '='))
            {
                  if (ft_strcmp(argv[i], "=") != 0)
                  {
                        temp = ft_split(argv[i], '=');
                        if (temp[0])
                              arr[0] = ft_strdup(temp[0]);
                        if (temp[1])
                              arr[1] = ft_strdup(temp[1]);
                        free_arr(temp, get_arg_count(temp));
                  }
                  else
                  {
                        arr[0] = ft_strdup(argv[i - 1]);
                        if (argv[i + 1] != NULL )
                              arr[1] = ft_strdup(argv[i + 1]);
                  }
                  if (!is_valid_var_start(arr[0][0]) || !is_valid_var_char(arr[0]))
                  {
                        g_exit_status = 1;
                        print_export_error(arr[0], arr[2]," : not a valid identifier");
                  }
                  else
                        export_one_var(arr, my_data);
            }
            i ++;
      }
}


/* The double and single quotes wrapping the entire export command
string will be removed by parser/lexer*/

void    exec_export(char **argv, t_envp *my_data)
{
      int count;
      char **arr;
      
      count = 0;
      arr = NULL;
      count = count_non_empty_strings(argv);
      arr = strip_empty_strings(argv);
      g_exit_status = 0;
      if (count == 1 || arr == NULL)
      {
            print_variables_list(my_data->envarr);
            return;
      }
      else if (count == 2 && arr != NULL)
      {
            if (!ft_strcmp(arr[1], "#"))
            {
                  print_variables_list(my_data->envarr);
                  return;
            }
            else if (ft_strchr(arr[1], '='))
                  real_export(arr, my_data);
            else if (!is_valid_var_start(arr[1][0]) || !is_valid_var_char(arr[1]))
            {
                  g_exit_status = 1;
                  print_export_error(arr[1], NULL," : not a valid identifier");
            }
            else
                  return;
      }
      else
      {
            real_export(arr, my_data);
            return ;
      }
}
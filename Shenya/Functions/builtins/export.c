#include "../minishell.h"

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

void   export_one_var(char **arr, t_envp *my_data)
{
      char *var;
      char *val;
      char *str;

      var = arr[0];
      val = arr[1];
      /*if val is null make it an empty string*/
      if (val == NULL)
            val = ft_strdup("");
      /*if var exists in env, remove it - unset */
      unset_one_var(var, my_data);
      /* add the variable and set value */
      str = ft_strjoin(var, ft_strdup("="));
      str = ft_strjoin(str, val);
      ft_lstadd_back(&my_data->envlist, ft_lstnew(str));
      g_exit_status = 0;
}

void    exec_export(char **argv, t_envp *my_data)
{
      int i = 1;
      char **arr;

      arr = NULL;
      while (argv[i] != NULL)
      {
            if (ft_strchr(argv[i], '='))
            {
                  arr = ft_split(argv[i], '=');
                  export_one_var(arr, my_data);
                  free_arr(arr, get_arg_count(arr));
            }
            i ++;
      }     
}
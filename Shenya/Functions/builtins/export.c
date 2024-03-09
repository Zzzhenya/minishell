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
void    exec_export(char **argv, t_envp *my_data)
{
      char **arr;
      char *var;
      char *val;

      arr = NULL;
      arr = ft_split(argv[1], '=');
      var = arr[0];
      val = arr[1];
      printf("var %s\n", var);
      printf("val %s\n", val);
      /*if val is null make it an empty string*/
      /*if var exists in env, remove it - unset */
      /* add the variable and set value */
      free(var);
      free(val);
      free(arr);
      (void)my_data;

}
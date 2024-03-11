/*
//  [Propose]
//  1. scan the buffer(=Input)
//  2. find the next token.
//
//  [Example]
//  BUFFER: "_  _  x  x  x  x  _  _  Y  Y  Y  _  \n  \0"
//          5-1    3        4       5-2               2
//            \                     /
//          str[0]               str[1]
//            1                    1
//
//  [Parameter]
//  1: b_scan       Begin of scanned input  // points to *str
//  2: e_scan       End of scanned input
//  3: b_token      Begin of token
//  4: e_token      End of token
//  5: str          Begin fo (curr)str
*/
s
char    white_space[] = " \t\r\n\v";
char    symbols[] = "<|>&;()";

//                 **ps           *es           **q             **eq
int get_token(char **b_scan, char *e_scan, char **b_token, char **e_token)
{
    char    *str;
    int     res;

    str = *b_scan;
    while (str < e_scan && strchr(white_space, *str))
        str++;
    if (b_token)
        *b_token = str;
    res = *str;
    switch(*str)
    {
        case 0:
            break;
        case '|':
        case '(':
        case ')':
        case ';':
        case '&':
        case '<':
            str++;
            break;
        case '>':
            str++;
            if (*str == '>')
            {
                res = '+';
                str++;
            }
            break;
        default:
            res = 'a';
            while (str < e_scan && !strchr(white_space, *str) && !strchr(symbols, *str))
                str++;
            break;
    }
    if (e_token)
        *e_token = str;
    while (str < e_scan && strchr(white_space, *str))
        str++;
    *b_scan = str;
    return (res);
}
/*
//  [For switch]
//  (token)   ->    (return)
//  |               |
//  ;               ;
//  &               &
//  )               )
//  (               (
//  <               <
//  >               >
//  >>              +
//  other           a (just indicate)
//  end             0 (= '\0')
*/

int get_token(char **b_scan, char *e_scan, char **b_token, char **e_token)
{
    char    *str;
    int     res;

    str = *b_scan;
    while (str < e_scan && strchr(white_space, *str))
        str++;
    if (b_token)
        *b_token = str;
    res = *str;
    if (res == '|'|| res == '(' || res == ')' || res == ';' || res == '&' || res == '<')
    {
        if (res == '>')
        {
            if (*str == '>')
            {
                res = '+';
                str++;
            }
        }
        else
            str++;
    }
    else if (res != 0)
    {
            res = 'a';
            while (str < e_scan && !strchr(white_space, *str) && !strchr(symbols, *str))
                str++;
    }
    if (e_token)
        *e_token = str;
    while (str < e_scan && strchr(white_space, *str))
        str++;
    *b_scan = str;
    return (res);
}

int	token_length(int *token)
{
	int	i;

	i = 0;
	while (token[i] != 0)
		i ++;
	return (i);
}

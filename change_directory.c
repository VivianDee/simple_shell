#include "main.h"

/**
 *change_directory - changes the location to a given directory
 *@parameters: is the destination directory
 *Return: nothing
 */

void change_directory(char *parameters[])
{
	char *prev_dir = getenv("OLDPWD"), *home_dir = getenv("HOME"), error_no[10];
	int error = 1;

	if (parameters[1])
	{
		if (strstr(parameters[1], "-") != NULL)
		{
			error = chdir(prev_dir);

			if (error != 0)
				perror("cd");

			sprintf(error_no, "%d", error);
			setenv("LASTEXITCODE", error_no, 1);
		} else
		{
			error = chdir(parameters[1]);

			if (error != 0)
				perror("cd");

			sprintf(error_no, "%d", error);
			setenv("LASTEXITCODE", error_no, 1);
		}
	} else
	{
		error = chdir(home_dir);

		if (error != 0)
			perror("cd");

		sprintf(error_no, "%d", error);
		setenv("LASTEXITCODE", error_no, 1);
	}
	update_pwd_in_env();
}

/**
 *update_pwd_in_env - effects the change made to the present working directory
 *Return: nothing
 */
void update_pwd_in_env(void)
{
	char cwd[LETTERS];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("PWD", cwd, 1);
	}
	else
	{
		perror("getcwd");
	}
}

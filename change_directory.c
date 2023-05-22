#include "main.h"

void change_directory(char *parameters[])
{
	char *prev_dir = getenv("OLDPWD"), *home_dir = getenv("HOME"), error_no[10];
	int error = 1;

	if (parameters[1])
	{
		if (strstr(parameters[1], "-") != NULL)
		{
			if (prev_dir)
			{
				if ((error = chdir(prev_dir)) != 0)
					perror("cd");

				sprintf(error_no, "%d", error);
				setenv("LASTEXITCODE", error_no, 1);
			}
		}
		else
		{
			if ((error = chdir(parameters[1])) != 0)
				perror("cd");

			sprintf(error_no, "%d", error);
			setenv("LASTEXITCODE", error_no, 1);
		}
	}
	else
	{
		if (home_dir)
		{
			if ((error = chdir(home_dir)) != 0)
				perror("cd");

			sprintf(error_no, "%d", error);
			setenv("LASTEXITCODE", error_no, 1);
		}
	}

	update_pwd_in_env();
}

void update_pwd_in_env()
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

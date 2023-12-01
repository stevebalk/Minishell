/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:05:04 by jopeters          #+#    #+#             */
/*   Updated: 2023/12/01 17:25:59 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/minishell.h"
/*
The cd command in Bash (Bourne Again SHell) is used for changing the current working directory. Here are various ways you can use the cd command with different types of path specifications:

Absolute Path: Specify the full path from the root directory.
Example: cd /usr/local/bin

Relative Path: Specify the path relative to the current directory.
Example: cd Documents/Projects (Moves into the 'Projects' directory inside 'Documents' from the current directory)

Home Directory (~): This represents the user's home directory.
Example: cd ~ or simply cd (Moves to the user's home directory)

Parent Directory (..): Moves up one directory level.
Example: cd .. (Moves to the parent directory of the current directory)

Current Directory (.): Represents the current directory.
Example: cd . (Stays in the current directory)

Dash (-): Moves to the last working directory.
Example: cd - (Switches between the current and last directories)
OLDPWD  in environment

Environment Variables: Use environment variables in the path.
Example: cd $HOME/Downloads (Moves to the 'Downloads' directory inside the user's home directory)

Subshell Expansion: Navigate to directories using command substitution.
Example: cd $(dirname $(which python)) (Moves to the directory where the Python executable is located)

Brace Expansion: Useful for navigating to similarly named directories.
Example: cd /usr/{local,bin} (This will try to move to '/usr/local', and if it fails, it will try '/usr/bin')

These are the common ways to use the cd command in Bash. The actual path you specify will depend on the directory structure of your system and where you want to navigate.
*/

/*
Jonas:
.. and . works fine ... nothing to do

~(home directory)		does not work 

Fehlermeldung wenn Verzeichnis nicht vorhanden
cd pipp
bash: cd: pipp: No such file or directory

Fehlermeldung wenn Rechte nicht passen
mkdir TEST
bash-3.2$ chmod 000 TEST
bash-3.2$ cd TEST/
bash: cd: TEST/: Permission denied

export HOME=/Users/jonas/shelltests/nonexistingfolder			---> works, but 
cd ~				---> does NOT work
bash: cd: /Users/jonas/shelltests/nonexistingfolder: No such file or directory


After starting a new Terminal
cd -
bash: cd: OLDPWD not set
*/



void	builtin_cd(t_ms *ms, t_list **env_llst, t_list **env_llst_sorted, char *in)
{
	char *tmp_str;
	(void)tmp_str;
	(void)env_llst;
	(void)env_llst_sorted;
	tmp_str = NULL;
	

	c_yellow(); printf("builtin_cd()  >%s<\n", in); c_reset();
	
	if (ft_strncmp(in, "-", 1) == 0 && ft_strlen(in) == 1)
	{
		// switching to last dir
		// if !OLDWPD  --> "cd: OLDPWD not set"
		tmp_str = get_val_of_var(&ms->env_llst, "OLDPWD");
		c_purple(); printf("switching to last dir   >%s< \n", tmp_str); c_reset();
		if (!tmp_str)
		{
			c_red();
			printf("cd: OLDPWD not set\n");
			c_reset();
		}
		else
		{
			builtin_cd_change_dir(&ms->env_llst, &ms->env_llst_sorted, tmp_str);
			free(tmp_str);
		}
	}
	else if (ft_strncmp(in, "~", 1) == 0 && ft_strlen(in) == 1)
	{
		// switching to home dir from 
		c_purple(); printf("switching to home dir()   >%s< \n", ms->home_dir); c_reset();
		builtin_cd_change_dir(&ms->env_llst, &ms->env_llst_sorted, ms->home_dir);
	}
	else if (ft_strncmp(in, "", 0) == 0 && ft_strlen(in) == 0)
	{
		// switching to env home dir  
		tmp_str = get_val_of_var(&ms->env_llst, "HOME");
		c_purple(); printf("switching to env HOME  dir()   >%s< \n", tmp_str); c_reset();
		if (tmp_str)
			builtin_cd_change_dir(&ms->env_llst, &ms->env_llst_sorted, tmp_str);
		else
		{
			printf("cd: HOME not set\n");
		}
		free(tmp_str);
	}

	else 
	{
		printf("go to dir --> \n");
		builtin_cd_change_dir(env_llst, env_llst_sorted, in);
	}

	// if new change directory is valid --> copy pwd  to old pwd
	//if (tmp_str)
	free(tmp_str);
		
	c_red(); printf("~builtin_cd()\n"); c_reset();
}

void builtin_cd_change_dir(t_list **env_llst, t_list **env_llst_sorted, char *path)
{
	//const char *path = "./libs/libft"; 

	c_yellow(); printf("builtin_cd_change_dir()  >%s<\n", path); 	c_reset();
	char *last_pwd;
	char *tmp_value;
	
	last_pwd = get_val_of_var(env_llst, "PWD");

	c_purple(); printf("last pwd from env >%s<\n", last_pwd); c_reset();
    // Change the current working directory
    if (chdir(path) != 0) 
	{
		c_blue(); printf("MIST\n"); c_reset();
        perror("chdir failed");
		free(last_pwd);
        exit(EXIT_FAILURE);
    }
	else
	{	
		tmp_value = join_three_string("OLDPWD", "=", last_pwd);
		c_blue(); printf("set OLD PWD   new DIR >%s<\n", tmp_value); c_reset();

		export_single_arg(env_llst, env_llst_sorted, tmp_value);
		builtin_pwd(env_llst, env_llst_sorted, 1);
		free(tmp_value);
	}

	free(last_pwd);
	c_red(); printf("~builtin_cd_change_dir()\n"); c_reset();
}



// ######## TEST ########
// #############   OLD Test Stuff   ###############
void test_change_dir(void) 
{
    //const char *path = "../"; // 
	//const char *path = ".."; 			// works
	//const char *path = "."; 			// works

	
	//const char *path = "~"; 			// not work			--> go to home dir
	//const char *path = "-"; 			// not work			--> go to last working! dir

	const char *path = "./libs/libft"; 

	c_yellow(); printf("test_change_dir()\n"); c_reset();
	
    // Change the current working directory
    if (chdir(path) != 0) 
	{
        perror("chdir failed");
        exit(EXIT_FAILURE);
    }

	builtin_pwd(NULL, NULL, 1);
	

	c_red(); printf("~test_change_dir()\n"); c_reset();
}

void test_getcwd(void)
{
	c_yellow(); printf("test_get_cwd()\n"); c_reset();

	char *buffer;
    size_t size = 1024;

    // Allocate memory for the buffer
    buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL) 
	{
        perror("Unable to allocate buffer");
        exit(1);
    }

    // Get the current working directory
	if (getcwd(buffer, size) == NULL) 
	{
        perror("Error getting current directory");
        exit(1);
	}

    // Print the current working directory
    printf("Current working directory: %s\n", buffer);

    // Free the allocated memory
    free(buffer);

    //return 0;
}


void test_opendir(void)
{
	DIR *d;
    struct dirent *dir;
	c_yellow(); printf("test_opendir()\n"); c_reset();

    d = opendir("."); // Open the current directory
    if (d) 
	{
        while ((dir = readdir(d)) != NULL) 
		{
            printf("%s\n", dir->d_name); // Print the name of the entry
        }
        closedir(d); // Close the directory
    } else 
	{
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

}

void test_is_dir_valid(char *dir)
{
	c_yellow(); printf("test_is_dir_valid()  dir >%s<\n", dir); c_reset();

	DIR *d;
	d = opendir(dir);	
	
	if (d)
	{
		c_green();printf("dir >%s< exists()\n", dir); c_reset();
	}	
	else
	{
		c_red();printf("dir >%s< NOT exists()\n", dir); c_reset();
	}
	closedir(d);
		
}
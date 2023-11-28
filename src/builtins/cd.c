/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:05:04 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/28 16:21:35 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

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
*/

// ######## TEST ########

void	builtin_cd(char *in)
{
	if (ft_strncmp(in, "-", 1) == 0 && ft_strlen(in) == 1)
	{
		// switching to last dir
	}
	if (ft_strncmp(in, "~", 1) == 0 && ft_strlen(in) == 1)
	{
		// switching to home dir
	}
	
}

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

	builtin_pwd(NULL, NULL);
	

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
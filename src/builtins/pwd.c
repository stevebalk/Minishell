/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:40:32 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/27 16:59:53 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include <dirent.h>
			
void builtin_pwd(t_list **env_llst, t_list **env_llst_sorted)
{
	c_yellow(); printf("builtin_pwd()\n"); c_reset();

	char *buffer;
	char *pwd;
    size_t size = 1024;
	(void)env_llst;
	(void)env_llst_sorted;

    buffer = (char *)malloc(size * sizeof(char));
    if (buffer == NULL) 
	{
        perror("Unable to allocate buffer");
        exit(1);
    }

	if (getcwd(buffer, size) == NULL) 
	{
        perror("Error getting current directory");
        exit(1);
	}

	c_green();
	printf("%s\n", buffer);
	
	pwd = join_three_string("PWD", "=", buffer);
	//export_single_arg(env_llst, env_llst_sorted, pwd);
    //printf("Current working directory: %s\n", buffer);

    // Free the allocated memory
	free(pwd);
    free(buffer);
}


// ######## TEST ########
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
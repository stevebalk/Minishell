/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:05:04 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/27 17:28:12 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

// ######## TEST ########

void test_change_dir(void) 
{
    const char *path = "../"; // Define the directory to change to

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
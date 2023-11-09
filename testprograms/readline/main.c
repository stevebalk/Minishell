/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:48:54 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/09 12:03:07 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main(void)
{
    char *input;

    input = readline("Enter your name: ");

    printf("Hello, %s!\n", input);

    free(input);

    return 0;
}


/*

gcc main.c -lreadline

*/
/*
** EPITECH PROJECT, 2019
** unit_test_function_ex02
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string>

void redirect_all_std()
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(koala, nigoala)
{
    cr_assert_eq(std::string("ta mere"), "ta mere");
}

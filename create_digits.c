#include "main.h"

/**
 * is_digit - Check if a character is a digit.
 * @c: The character to be checked.
 * Return: 1 if it's a digit, 0 otherwise.
 */
int is_digit(int c)
{
    return (c >= '0' && c <= '9');
}

/**
 * string_length - Calculate the length of a string.
 * @s: The string.
 * Return: The length of the string.
 */
int string_length(char *s)
{
    int length = 0;

    while (*s)
    {
        length++;
        s++;
    }
    
    return length;
}

/**
 * print_formatted_number - Print a formatted number.
 * @str: The base number as a string.
 * @format: The formatting options.
 * Return: The number of characters printed.
 */
int print_formatted_number(char *str, FormatOptions *format)
{
    int characters_printed = 0;
    int is_negative = (!format->unsigned_num && *str == '-');

    if (!format->precision && *str == '0' && !str[1])
        str = "";

    if (is_negative)
    {
        str++;
        characters_printed--;
    }

    if (format->precision != UINT_MAX)
    {
        while (string_length(str) < format->precision)
        {
            *--str = '0';
            characters_printed++;
        }
    }

    if (is_negative)
    {
        *--str = '-';
        characters_printed++;
    }

    if (!format->left_aligned)
    {
        characters_printed += print_number_right_shift(str, format);
    }
    else
    {
        characters_printed += print_number_left_shift(str, format);
    }

    return characters_printed;
}

/**
 * print_number_right_shift - Print a right-aligned number with options.
 * @str: The base number as a string.
 * @format: The formatting options.
 * Return: The number of characters printed.
 */
int print_number_right_shift(char *str, FormatOptions *format)
{
    int characters_printed = 0;
    int is_negative = (!format->unsigned_num && *str == '-');
    char padding_char = ' ';

    if (format->zero_padded && !format->left_aligned)
    {
        padding_char = '0';
    }

    if (is_negative)
    {
        str++;
        characters_printed--;
    }

    if ((format->show_plus && !is_negative) ||
        (!format->show_plus && format->space_for_positive && !is_negative))
    {
        string_length(str) += 1;
        characters_printed++;
    }

    if (is_negative && padding_char == '0')
    {
        characters_printed += _putchar('-');
    }

    if (format->show_plus && !is_negative && padding_char == '0' && !format->unsigned_num)
    {
        characters_printed += _putchar('+');
    }
    else if (!format->show_plus && format->space_for_positive && !is_negative && !format->unsigned_num && !format->zero_padded)
    {
        characters_printed += _putchar(' ');
    }

    while (string_length(str) < format->width)
    {
        _putchar(padding_char);
        characters_printed++;
    }

    if (is_negative && padding_char == ' ')
    {
        characters_printed += _putchar('-');
    }

    if (format->show_plus && !is_negative && padding_char == ' ' && !format->unsigned_num)
    {
        characters_printed += _putchar('+');
    }
    else if (!format->show_plus && format->space_for_positive && !is_negative && !format->unsigned_num && !format->zero_padded)
    {
        characters_printed += _putchar(' ');
    }

    characters_printed += _puts(str);

    return characters_printed;
}

/**
 * print_number_left_shift - Print a left-aligned number with options.
 * @str: The base number as a string.
 * @format: The formatting options.
 * Return: The number of characters printed.
 */
int print_number_left_shift(char *str, FormatOptions *format)
{
    int characters_printed = 0;
    int is_negative = (!format->unsigned_num && *str == '-');
    char padding_char = ' ';

    if (format->zero_padded && !format->left_aligned)
    {
        padding_char = '0';
    }

    if (format->show_plus && !is_negative && !format->unsigned_num)
    {
        characters_printed += _putchar('+');
        string_length(str) += 1;
    }
    else if (format->space_for_positive && !is_negative && !format->unsigned_num)
    {
        characters_printed += _putchar(' ');
        string_length(str) += 1;
    }

    characters_printed += _puts(str);

    while (string_length(str) < format->width)
    {
        _putchar(padding_char);
        characters_printed++;
    }

    return characters_printed;
}


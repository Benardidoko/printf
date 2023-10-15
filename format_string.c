#include "main.h"

/**
 * extract_precision - Extracts the precision from the format string.
 * @formatString: The format string.
 * @parameters: Parameters structure.
 * @argPointer: Argument pointer.
 * Return: New pointer in the format string.
 */
char *extract_precision(char *formatString, Parameters *parameters, va_list argPointer)
{
    int precisionValue = 0;

    if (*formatString != '.')
    {
        return formatString;
    }

    formatString++; // Move past the '.' character

    if (*formatString == '*')
    {
        precisionValue = va_arg(argPointer, int);
        formatString++;
    }
    else
    {
        while (_isdigit(*formatString))
        {
            precisionValue = precisionValue * 10 + (*formatString - '0');
            formatString++;
        }
    }

    parameters->precision = precisionValue;

    return formatString;
}


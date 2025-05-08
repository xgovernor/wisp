#include "utils.h"
#include <string.h>
#include "../modules/symbol_table.h"

char *interpolate(const char *template)
{
    static char buffer[512];
    int bufpos = 0;
    for (int i = 0; template[i] != '\0' && bufpos < 511;)
    {
        if (template[i] == '{')
        {
            int j = i + 1;
            char varname[MAX_NAME_LEN] = {0};
            int k = 0;
            while (template[j] != '}' && template[j] != '\0' && k < MAX_NAME_LEN - 1)
            {
                varname[k++] = template[j++];
            }
            varname[k] = '\0';
            if (template[j] == '}')
            {
                Variable *v = find_variable(varname);
                if (v)
                {
                    int l = 0;
                    while (v->value[l] != '\0' && bufpos < 511)
                        buffer[bufpos++] = v->value[l++];
                }
                i = j + 1;
                continue;
            }
        }
        buffer[bufpos++] = template[i++];
    }
    buffer[bufpos] = '\0';
    return buffer;
}

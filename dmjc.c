#include <stdio.h>
#include <string.h>

int main()
{
    FILE *src = fopen("hello.dmj", "r");

    if(src == NULL)
    {
        printf("Cannot open hello.dmj\n");
        return 1;
    }

    FILE *out = fopen("output.cpp", "w");

    fprintf(out, "#include <iostream>\n");
    fprintf(out, "#include <string>\n");
    fprintf(out, "using namespace std;\n\n");
    fprintf(out, "int main()\n{\n");

    char line[256];

    while(fgets(line, sizeof(line), src))
    {
        /* Skip comments */
        if(strncmp(line, "--", 2) == 0)
            continue;

        /* Variables */
        if(strncmp(line, "var ", 4) == 0)
        {
            char name[50];
            char value[200];

            /* String */
            if(sscanf(line,
                      "var %s = \"%[^\"]\"",
                      name,
                      value) == 2)
            {
                fprintf(out,
                        "    string %s = \"%s\";\n",
                        name,
                        value);

                continue;
            }

            /* Number */
            if(sscanf(line,
                      "var %s = %s",
                      name,
                      value) == 2)
            {
                if(strchr(value, '.'))
                {
                    fprintf(out,
                            "    double %s = %s;\n",
                            name,
                            value);
                }
                else
                {
                    fprintf(out,
                            "    int %s = %s;\n",
                            name,
                            value);
                }

                continue;
            }
        }

        /* show text */
        if(strncmp(line, "show \"", 6) == 0)
        {
            char text[200];

            if(sscanf(line,
                      "show \"%[^\"]\"",
                      text) == 1)
            {
                fprintf(out,
                        "    cout << \"%s\" << endl;\n",
                        text);
            }

            continue;
        }

        /* ask variable */
        if(strncmp(line, "ask ", 4) == 0)
        {
            char name[50];

            if(sscanf(line,
                      "ask %s",
                      name) == 1)
            {
                fprintf(out,
                        "    string %s;\n"
                        "    getline(cin, %s);\n",
                        name,
                        name);
            }

            continue;
        }

        /* show variable */
        if(strncmp(line, "show ", 5) == 0 &&
           line[5] != '"')
        {
            char name[50];

            if(sscanf(line,
                      "show %s",
                      name) == 1)
            {
                fprintf(out,
                        "    cout << %s << endl;\n",
                        name);
            }

            continue;
        }
    }

    fprintf(out, "\n    return 0;\n");
    fprintf(out, "}\n");

    fclose(src);
    fclose(out);

    printf("DMJScript compilation successful!\n");

    return 0;
}
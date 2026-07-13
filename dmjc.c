#include <stdio.h>
#include <string.h>

void writeIndent(FILE *out, int indent)
{
    for(int i = 0; i < indent; i++)
    {
        fprintf(out, "    ");
    }
}

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

    int indent = 1;

    char line[256];

    while(fgets(line, sizeof(line), src))
    {
        line[strcspn(line, "\n")] = 0;

        if(strlen(line) == 0)
            continue;

        while(line[0] == ' ' || line[0] == '\t')
        {
            memmove(line, line + 1, strlen(line));
        }

        if(strncmp(line, "--", 2) == 0)
            continue;

        /* Variables */
        if(strncmp(line, "var ", 4) == 0)
        {
            char name[50];
            char value[200];

            if(sscanf(line,
                      "var %s = \"%[^\"]\"",
                      name,
                      value) == 2)
            {
                writeIndent(out, indent);

                fprintf(out,
                        "string %s = \"%s\";\n",
                        name,
                        value);

                continue;
            }

            if(sscanf(line,
                      "var %s = %s",
                      name,
                      value) == 2)
            {
                writeIndent(out, indent);

                if(strchr(value, '.'))
                {
                    fprintf(out,
                            "double %s = %s;\n",
                            name,
                            value);
                }
                else
                {
                    fprintf(out,
                            "int %s = %s;\n",
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
                writeIndent(out, indent);

                fprintf(out,
                        "cout << \"%s\" << endl;\n",
                        text);
            }

            continue;
        }

        /* ask */
        if(strncmp(line, "ask ", 4) == 0)
        {
            char name[50];

            if(sscanf(line,
                      "ask %s",
                      name) == 1)
            {
                writeIndent(out, indent);
                fprintf(out,
                        "string %s;\n",
                        name);

                writeIndent(out, indent);
                fprintf(out,
                        "getline(cin, %s);\n",
                        name);
            }

            continue;
        }

        /* if */
        if(strncmp(line, "if ", 3) == 0)
        {
            char condition[200];

            strcpy(condition, line + 3);

            char *thenPos = strstr(condition, " then");

            if(thenPos != NULL)
                *thenPos = '\0';

            writeIndent(out, indent);
            fprintf(out,
                    "if(%s)\n",
                    condition);

            writeIndent(out, indent);
            fprintf(out, "{\n");

            indent++;

            continue;
        }

        /* else */
        if(strcmp(line, "else") == 0)
        {
            indent--;

            writeIndent(out, indent);
            fprintf(out, "}\n");

            writeIndent(out, indent);
            fprintf(out, "else\n");

            writeIndent(out, indent);
            fprintf(out, "{\n");

            indent++;

            continue;
        }

        /* repeat */
        if(strncmp(line, "repeat ", 7) == 0)
        {
            int count;

            if(sscanf(line,
                      "repeat %d",
                      &count) == 1)
            {
                writeIndent(out, indent);

                fprintf(out,
                        "for(int i = 0; i < %d; i++)\n",
                        count);

                writeIndent(out, indent);
                fprintf(out, "{\n");

                indent++;
            }

            continue;
        }

        /* end */
        if(strcmp(line, "end") == 0)
        {
            indent--;

            writeIndent(out, indent);
            fprintf(out, "}\n");

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
                writeIndent(out, indent);

                fprintf(out,
                        "cout << %s << endl;\n",
                        name);
            }

            continue;
        }
    }

    fprintf(out, "\n");

    writeIndent(out, 1);
    fprintf(out, "return 0;\n");

    fprintf(out, "}\n");

    fclose(src);
    fclose(out);

    printf("DMJScript compilation successful!\n");

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 50000

void writeIndentToBuffer(char *buffer, int indent)
{
    for(int i = 0; i < indent; i++)
    {
        strcat(buffer, "    ");
    }
}

void addLine(char *buffer, const char *text)
{
    strcat(buffer, text);
}

int main()
{
    FILE *src = fopen("hello.dmj", "r");

    if(src == NULL)
    {
        printf("Cannot open hello.dmj\n");
        return 1;
    }

    char functions[BUFFER_SIZE] = "";
    char mainCode[BUFFER_SIZE] = "";

    int inFunction = 0;

    char line[256];
    char currentFunction[50];

    int mainIndent = 1;
    int functionIndent = 1;

    while(fgets(line, sizeof(line), src))
    {
        line[strcspn(line, "\n")] = 0;

        if(strlen(line) == 0)
            continue;

        while(line[0] == ' ' || line[0] == '\t')
        {
            memmove(line,
                    line + 1,
                    strlen(line));
        }

        if(strncmp(line, "--", 2) == 0)
            continue;

        char *target =
            inFunction ? functions : mainCode;

        int *indent =
            inFunction ? &functionIndent : &mainIndent;

        /* function */

        if(strncmp(line, "function ", 9) == 0)
        {
            sscanf(line,
                   "function %s",
                   currentFunction);

            char temp[256];

            sprintf(temp,
                    "\nvoid %s()\n{\n",
                    currentFunction);

            strcat(functions, temp);

            inFunction = 1;
            functionIndent = 1;

            continue;
        }

        /* call */

        if(strncmp(line, "call ", 5) == 0)
        {
            char name[50];

            if(sscanf(line,
                      "call %s",
                      name) == 1)
            {
                writeIndentToBuffer(target,
                                    *indent);

                char temp[100];

                sprintf(temp,
                        "%s();\n",
                        name);

                strcat(target, temp);
            }

            continue;
        }
                /* string variable */

        if(strncmp(line, "var ", 4) == 0)
        {
            char name[50];
            char value[200];

            if(sscanf(line,
                      "var %s = \"%[^\"]\"",
                      name,
                      value) == 2)
            {
                writeIndentToBuffer(target,
                                    *indent);

                char temp[300];

                sprintf(temp,
                        "string %s = \"%s\";\n",
                        name,
                        value);

                strcat(target, temp);

                continue;
            }

            char expr[200];

            if(sscanf(line,
                      "var %s = %[^\n]",
                      name,
                      expr) == 2)
            {
                writeIndentToBuffer(target,
                                    *indent);

                char temp[300];

                if(strchr(expr, '+') ||
                   strchr(expr, '-') ||
                   strchr(expr, '*') ||
                   strchr(expr, '/'))
                {
                    sprintf(temp,
                            "int %s = %s;\n",
                            name,
                            expr);
                }
                else if(strchr(expr, '.'))
                {
                    sprintf(temp,
                            "double %s = %s;\n",
                            name,
                            expr);
                }
                else
                {
                    sprintf(temp,
                            "int %s = %s;\n",
                            name,
                            expr);
                }

                strcat(target, temp);

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
                writeIndentToBuffer(target,
                                    *indent);

                char temp[300];

                sprintf(temp,
                        "cout << \"%s\" << endl;\n",
                        text);

                strcat(target, temp);
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
                writeIndentToBuffer(target,
                                    *indent);

                char temp[200];

                sprintf(temp,
                        "cout << %s << endl;\n",
                        name);

                strcat(target, temp);
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
                writeIndentToBuffer(target,
                                    *indent);

                char temp[300];

                sprintf(temp,
                        "string %s;\n",
                        name);

                strcat(target, temp);

                writeIndentToBuffer(target,
                                    *indent);

                sprintf(temp,
                        "getline(cin, %s);\n",
                        name);

                strcat(target, temp);
            }

            continue;
        }
                /* if */

        if(strncmp(line, "if ", 3) == 0)
        {
            char condition[200];

            strcpy(condition, line + 3);

            char *thenPos = strstr(condition,
                                   " then");

            if(thenPos != NULL)
                *thenPos = '\0';

            writeIndentToBuffer(target,
                                *indent);

            strcat(target, "if(");
            strcat(target, condition);
            strcat(target, ")\n");

            writeIndentToBuffer(target,
                                *indent);

            strcat(target, "{\n");

            (*indent)++;

            continue;
        }

        /* else */

        if(strcmp(line, "else") == 0)
        {
            (*indent)--;

            writeIndentToBuffer(target,
                                *indent);

            strcat(target, "}\n");

            writeIndentToBuffer(target,
                                *indent);

            strcat(target, "else\n");

            writeIndentToBuffer(target,
                                *indent);

            strcat(target, "{\n");

            (*indent)++;

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
                writeIndentToBuffer(target,
                                    *indent);

                char temp[200];

                sprintf(temp,
                        "for(int i = 0; i < %d; i++)\n",
                        count);

                strcat(target, temp);

                writeIndentToBuffer(target,
                                    *indent);

                strcat(target, "{\n");

                (*indent)++;
            }

            continue;
        }

        /* end */

        if(strcmp(line, "end") == 0)
        {
            (*indent)--;

            writeIndentToBuffer(target,
                                *indent);

            strcat(target, "}\n");

            if(inFunction && *indent == 0)
            {
                inFunction = 0;
                functionIndent = 1;
            }

            continue;
        }
    }

    fclose(src);

    FILE *out = fopen("output.cpp", "w");

    fprintf(out,
            "#include <iostream>\n");
    fprintf(out,
            "#include <string>\n");
    fprintf(out,
            "using namespace std;\n\n");

    fprintf(out,
            "%s\n",
            functions);

    fprintf(out,
            "int main()\n{\n");

    fprintf(out,
            "%s",
            mainCode);

    fprintf(out,
            "    return 0;\n");

    fprintf(out,
            "}\n");

    fclose(out);

    printf("DMJScript v0.8 compilation successful!\n");

    return 0;
}
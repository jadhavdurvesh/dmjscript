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

int runMode = 0;

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: dmjc <file.dmj>\n");
        printf("Usage: dmjc run <file.dmj>\n");
        return 1;
    }

    if(argc == 3 && strcmp(argv[1], "run") == 0)
    {
        runMode = 1;
    }

char *sourceFile;

if(runMode)
    sourceFile = argv[2];
else
    sourceFile = argv[1];

FILE *src = fopen(sourceFile, "r");

    if(src == NULL)
    {
        printf("Cannot open %s\n", sourceFile);
        return 1;
    }

    char functions[BUFFER_SIZE] = "";
    char mainCode[BUFFER_SIZE] = "";

    char ledPins[50][50];
int ledPinNumbers[50];
int ledCount = 0;
    int inFunction = 0;
    int arduinoMode = 0;

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
/* hardware */

if(strcmp(line, "hardware arduino") == 0)
{
    arduinoMode = 1;
    continue;
}
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
                if(expr[0] == '[')
{
    writeIndentToBuffer(target,
                        *indent);

    char temp[500];

    char values[300];
    strcpy(values, expr);

    values[strlen(values)-1] = '\0';

    sprintf(temp,
            "vector<int> %s = {%s};\n",
            name,
            values + 1);

    strcat(target, temp);

    continue;
}
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

       /* led */

if(strncmp(line, "led ", 4) == 0)
{
    char name[50];
    int pin;

    if(sscanf(line,
              "led %s = %d",
              name,
              &pin) == 2)
    {
        writeIndentToBuffer(target,
                            *indent);

        char temp[200];

        sprintf(temp,
                "int %s = %d;\n",
                name,
                pin);

        strcat(target, temp);

        /* Store LED pin for Arduino mode */

        strcpy(ledPins[ledCount], name);
        ledPinNumbers[ledCount] = pin;
        ledCount++;
    }

    continue;
}
/* on */

if(strncmp(line, "on ", 3) == 0)
{
    char name[50];

    if(sscanf(line,
              "on %s",
              name) == 1)
    {
        writeIndentToBuffer(target,
                            *indent);

        char temp[200];

        sprintf(temp,
                "digitalWrite(%s, HIGH);\n",
                name);

        strcat(target, temp);
    }

    continue;
}
/* off */

if(strncmp(line, "off ", 4) == 0)
{
    char name[50];

    if(sscanf(line,
              "off %s",
              name) == 1)
    {
        writeIndentToBuffer(target,
                            *indent);

        char temp[200];

        sprintf(temp,
                "digitalWrite(%s, LOW);\n",
                name);

        strcat(target, temp);
    }

    continue;
}
/* wait */

if(strncmp(line, "wait ", 5) == 0)
{
    int ms;

    if(sscanf(line,
              "wait %d",
              &ms) == 1)
    {
        writeIndentToBuffer(target,
                            *indent);

        char temp[200];

        sprintf(temp,
                "delay(%d);\n",
                ms);

        strcat(target, temp);
    }

    continue;
}
/* servo */

if(strncmp(line, "servo ", 6) == 0)
{
    char name[50];
    int pin;

    if(sscanf(line,
              "servo %s = %d",
              name,
              &pin) == 2)
    {
        writeIndentToBuffer(target,
                            *indent);

        char temp[300];

        sprintf(temp,
                "Servo %s;\n",
                name);

        strcat(target, temp);

        writeIndentToBuffer(target,
                            *indent);

        sprintf(temp,
                "%s.attach(%d);\n",
                name,
                pin);

        strcat(target, temp);
    }

    continue;
}

/* move */

if(strncmp(line, "move ", 5) == 0)
{
    char name[50];
    int angle;

    if(sscanf(line,
              "move %s %d",
              name,
              &angle) == 2)
    {
        writeIndentToBuffer(target,
                            *indent);

        char temp[200];

        sprintf(temp,
                "%s.write(%d);\n",
                name,
                angle);

        strcat(target, temp);
    }

    continue;
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

    char outputFile[256];

strcpy(outputFile, argv[1]);

char *dot = strrchr(outputFile, '.');

if(dot != NULL)
{
    strcpy(dot, ".cpp");
}
else
{
    strcat(outputFile, ".cpp");
}

FILE *out = fopen(outputFile, "w");

    if(arduinoMode)
{
    fprintf(out,
            "#include <Arduino.h>\n\n");
}
else
{
    fprintf(out,
        "#include <iostream>\n");
fprintf(out,
        "#include <string>\n");
fprintf(out,
        "#include <vector>\n");
fprintf(out,
        "using namespace std;\n\n");
}

    fprintf(out,
            "%s\n",
            functions);

    if(arduinoMode)
{
    fprintf(out,
            "void setup()\n{\n");
}
else
{
    fprintf(out,
            "int main()\n{\n");
}
if(arduinoMode)
{
    for(int i = 0; i < ledCount; i++)
    {
        fprintf(out,
                "    pinMode(%d, OUTPUT);\n",
                ledPinNumbers[i]);
    }

    fprintf(out, "\n");
}

    fprintf(out,
            "%s",
            mainCode);

    if(!arduinoMode)
{
    fprintf(out,
            "    return 0;\n");
}

fprintf(out,
        "}\n");

        if(arduinoMode)
{
    fprintf(out,
            "\nvoid loop()\n{\n}\n");
}

    fclose(out);

   printf("Generated: %s\n", outputFile);
printf("DMJScript v1.0 compilation successful!\n"); 

if(runMode)
{
    printf("Compiling...\n");

    system("g++ run.cpp -o run");

    printf("Running...\n");

    system("./run");
}

    return 0;
}
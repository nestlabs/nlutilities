/*
 *
 *    Copyright (c) 2012-2018 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

/**
 *    @file
 *      This file implements a framework for an interactive command line
 *      user interface.
 *
 *      @note The actual commands, set/show parameters, and prompt are
 *            configured at the project level.
 *
 */

#include <nluif.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int make_argv (char *cmdline, char *argv[]);

/* Preprocessor Definitions */

#define ANSI_BOLD_BRIGHT_BLUE_STR "\033[1;34m"
#define ANSI_NORMAL_STR           "\033[m"

#define UIF_CMD_STR ANSI_BOLD_BRIGHT_BLUE_STR "%s" ANSI_NORMAL_STR " "

/********************************************************************/
/*
 * Global messages
 */
#define HELPMSG "Enter 'help' for help.\n"

#define INVARG "Error: Invalid argument: %s\n"

#define INVALUE "Error: Invalid value: %s\n"

/*
 * Strings used by this file only
 */
#define INVCMD "Error: No such command: %s\n"

#define SYNTAX "Error: Invalid syntax for: %s\n"

#define INVOPT "Error:  Invalid set/show option: %s\n"

#define OPTFMT "%12s: "

static char inputBuf [UIF_MAX_LINE];
#ifdef SUPPORT_CMD_HISTORY
static char cmdHistory[UIF_HISTORY_CNT][UIF_MAX_LINE];
static int chQueryIdx = 0; // command history query index
static int chAddIdx = 0; // command history add index
#endif
static int  inputPos;
#ifdef BUILD_FEATURE_SHELL_REPEAT
static char lastCommand [UIF_MAX_LINE];
#endif
static char promptstr [UIF_MAX_PROMPT] = ">";

/********************************************************************/
void uif_set_prompt(const char *s)
{
    snprintf(promptstr, sizeof(promptstr), "%s", s);
}

void uif_prompt(void)
{
    printf("%s ", promptstr);
}

/*
 * List available commands which are match with specified partial command string
 * */
static void list_available_cmd(const char *curstr)
{
    int curlen, i, j = 0;

    printf("\n");

    curlen = strlen(curstr);

    for (i = 0; i < UIF_NUM_CMD; i++) {
        if (strncmp(UIF_CMDTAB[i].cmd, curstr, curlen) == 0) {
            j++;
            printf("%-24s ", UIF_CMDTAB[i].cmd);
            if (j % 3 == 0) {
                printf("\n");
            }
        }
    }

    /* next prompt */
    printf("\n");
    uif_prompt();
    printf("%s", curstr);
}

/*
 * Get next available character by current partial command string
 * return value:
 *  0: success, available character is store in *ch
 *  -1: no more available character
 *  -2: already has complete command
 * */
static int get_cmd_nxt_ch(const char *curstr, char *ch)
{
    int curlen, i, found = 0;

    if (curstr == NULL || ch == NULL) {
        return -1;
    }
    curlen = strlen(curstr);
    if (curlen == 0) {
        return -1;
    }
    if (strchr(curstr, ' ') != 0 || strchr(curstr, '\t') != 0) {
        return -1;
    }

    for (i = 0; i < UIF_NUM_CMD; i++) {
        if (strncmp(UIF_CMDTAB[i].cmd, curstr, curlen) == 0) {
            if (found) {
                if (UIF_CMDTAB[i].cmd[curlen] != *ch) {
                    /* no matched unique next char */
                    list_available_cmd(curstr);
                    return -1;
                }
            }
            else if (UIF_CMDTAB[i].cmd[curlen] == '\0') {
                /* match complete command */
                return -2;
            }
            else {
                found = 1;
                *ch = UIF_CMDTAB[i].cmd[curlen];
            }
        }
    }

    if (found) {
        return 0;
    }
    else {
        return -1;
    }
}

int
uif_handle_input_char(int ch)
{
    int res = 0;
#ifdef SUPPORT_CMD_HISTORY
	int i, lastInputPos;
    static char esc = 0;
    static char arrow = 0;
    if (esc) {
        if (ch == 0x5b) {
            arrow = 1;
        }
        /* if the next character after 0x1b is not 0x5b, then the 0x1b is really ESC key, just ignore it */
        esc = 0;
        return 0;
    }
    else if (arrow) {
        /* Update command history query index */
        if (ch == 0x41) {
            // up arrow
            if (chQueryIdx == 0) {
                chQueryIdx = UIF_HISTORY_CNT - 1;
            }
            else {
                chQueryIdx--;
            }
        }
        else if (ch == 0x42) {
            // down arrow
            if (chQueryIdx == UIF_HISTORY_CNT - 1) {
                chQueryIdx = 0;
            }
            else {
                chQueryIdx++;
            }
        }
        if (ch == 0x41 || ch == 0x42) {
            lastInputPos = inputPos;
            snprintf(inputBuf, sizeof(inputBuf), "%s", cmdHistory[chQueryIdx]);
            inputPos = strlen(inputBuf);
            /* clear the last command */
            putchar('\r');
            uif_prompt();
            for (i = 0; i < lastInputPos; i++) {
                putchar(' ');
            }
            /* print prompt and command */
            putchar('\r');
            uif_prompt();
            printf("%s", inputBuf);
        }

        arrow = 0;
        return 0;
    }
#endif // SUPPORT_CMD_HISTORY
    switch (ch)
    {
        case 0x03:      /* Ctrl-C */
            inputPos = 0;
            inputBuf[0] = '\0';
#ifdef SUPPORT_CMD_HISTORY
            chQueryIdx = chAddIdx;
#endif
            putchar(0x0D);    /* CR */
            putchar(0x0A);    /* LF */
            uif_prompt();
            break;

        case 0x08:      /* Backspace */
        case 0x7F:      /* Delete */
            if (inputPos > 0)
            {
            	inputPos -= 1;
            	putchar(0x08);    /* backspace */
            	putchar(' ');
            	putchar(0x08);    /* backspace */
            }
            break;

        case 0x0D:      /* CR */
        case 0x0A:      /* LF */
        	putchar(0x0D);    /* CR */
        	putchar(0x0A);    /* LF */
            inputBuf[inputPos] = '\0';
#ifdef SUPPORT_CMD_HISTORY
            if (strlen(inputBuf) != 0) {
                snprintf(cmdHistory[chAddIdx], sizeof(cmdHistory[chAddIdx]), "%s", inputBuf);
                if (chAddIdx == UIF_HISTORY_CNT - 1) {
                    chAddIdx = 0;
                }
                else {
                    chAddIdx++;
                }
                chQueryIdx = chAddIdx;
            }
#endif //SUPPORT_CMD_HISTORY
            res = 1;
            break;

/* No tab completion in minishell config. */
#if !NLUIF_USE_MINISHELL
        case '\t':      /* Tab */
            if (inputPos == 0)
                break;

            inputBuf[inputPos] = '\0';

            while (1) {
            	// This value will be overwritten on success.
            	char c = ' ';
            	int getRes = get_cmd_nxt_ch(inputBuf, &c);
                if (getRes >= 0) {
                	inputBuf[inputPos++] = c;
                	inputBuf[inputPos] = '\0';
                	putchar(c);
                }
                else if (getRes == -2) {
                	inputBuf[inputPos++] = ' ';
                	inputBuf[inputPos] = '\0';
                	putchar(' ');
                    break;
                }
                else {
                    break;
                }
            }
            break;
#endif /* !NLUIF_USE_MINISHELL */

#ifdef SUPPORT_CMD_HISTORY
        case 0x1b:
            esc = 1;
            break;
#endif
        default:
            if ((inputPos+1) < sizeof(inputBuf))
            {
                if ((ch > 0x1f) && (ch < 0x80))
                {
                	inputBuf[inputPos++] = (char)ch;
                	putchar((char)ch);
                }
            }
            break;
    }

    return res;
}

/********************************************************************/
int
make_argv (char *cmdline, char *argv[])
{
    int argc, i;
    bool in_text;
	int quote;

    /*
     * Break cmdline into strings and argv
     * It is permissible for argv to be NULL, in which case
     * the purpose of this routine becomes to count args
     */
    argc = 0;
    i = 0;
    in_text = false;
	quote = 0;

    while (cmdline[i] != '\0')  /* getline() must place 0x00 on end */
    {
        if (((cmdline[i] == ' ') || (cmdline[i] == '\t')))
        {
            if (in_text)
            {
                if (!quote)
                {
					/* end of command line argument */
					cmdline[i] = '\0';
					in_text = false;
                }
            }
            else
            {
                /* still looking for next argument */

            }
        }
		else if (cmdline[i] == '"')
		{
			if (!quote)
			{
				quote = cmdline[i];
				cmdline[i] = '\0';
			}
			else
			{
				cmdline[i] = '\0';
				quote = 0;
			}
		}
        else
        {
            /* got non-whitespace character */
            if (in_text)
            {
            }
            else
            {
                /* start of an argument */
                in_text = true;
                if (argc < UIF_MAX_ARGS)
                {
                    if (argv != NULL)
                        argv[argc] = &cmdline[i];
                    argc++;
                }
                else
                    /*return argc;*/
                    break;
            }

        }
        i++;    /* proceed to next character */
    }
    if (argv != NULL)
        argv[argc] = NULL;
    return argc;
}

/********************************************************************/
void
uif_run_cmd (void)
{
    /*
     * Global array of pointers to emulate C argc, argv interface
     */
    int argc;
    char *argv[UIF_MAX_ARGS + 1];   /* one extra for null terminator */

    inputBuf[inputPos] = 0;

#ifdef BUILD_FEATURE_SHELL_REPEAT
    if (!(argc = make_argv(inputBuf, argv)))
    {
        /* no command entered, just a blank line */
        if (strlen(lastCommand) != 0) {
            printf("repeat command: %s\n", lastCommand);
        }
        strcpy(inputBuf, lastCommand);
        argc = make_argv(inputBuf, argv);
    }
    lastCommand[0] = '\0';
#else
    argc = make_argv(inputBuf, argv);
#endif
    if (argc)
    {
        int i;
        for (i = 0; i < UIF_NUM_CMD; i++)
        {
            if (strcmp(UIF_CMDTAB[i].cmd, argv[0]) == 0)
            {
#if NLUIF_USE_MINISHELL
                UIF_CMDTAB[i].func(argc, argv);
                goto done;
#else
                if (((argc-1) >= UIF_CMDTAB[i].min_args) &&
                    ((argc-1) <= UIF_CMDTAB[i].max_args))
                {
#ifdef BUILD_FEATURE_SHELL_REPEAT
                    if (UIF_CMDTAB[i].flags & UIF_CMD_FLAG_REPEAT)
                    {
                        int j;
                        for (j = 0; j < argc; j++) {
                            snprintf(lastCommand + strlen(lastCommand), sizeof(lastCommand) - strlen(lastCommand),
                                     "%s ", argv[j]);
                        }
                    }
#endif
                    UIF_CMDTAB[i].func(argc, argv);
                    goto done;
                }
                else
                {
                    printf(SYNTAX, argv[0]);
                    goto done;
                }
#endif /* NLUIF_USE_MINISHELL */
            }
        }
#if !NLUIF_USE_MINISHELL
        printf(INVCMD, argv[0]);
        printf("%s", HELPMSG);
#endif /* NLUIF_USE_MINISHELL */
    }

done:
    inputPos = 0;
}
/********************************************************************/
uint32_t
uif_get_value (const char *s, bool *success, int base)
{
    uint32_t value;
    char *p;

    value = strtoul(s, &p, base);
    if ((value == 0) && (p == s))
    {
        *success = false;
        return 0;
    }
    else
    {
        *success = true;
        return value;
    }
}

#if !NLUIF_USE_MINISHELL

/********************************************************************/
static void print_help(const UIF_CMD *entry)
{
    bool syntaxFunc = entry->flags & UIF_CMD_FLAG_SYNTAX_FUNC;

    printf(UIF_CMD_STR, entry->cmd);

#if NLUIF_USE_DESCRIPTION
    printf(" %-25s", entry->description);
#endif

#if NLUIF_USE_SYNTAX
    if (!syntaxFunc)
    {
        printf(" %s %s", entry->cmd, (char*) entry->syntax);
    }
#endif

    printf("\n");

#if NLUIF_USE_SYNTAX
    if (syntaxFunc)
    {
        UIF_SYNTAX_FUNC func = entry->syntax;

        func(entry->cmd);
    }
#endif
}

void
uif_cmd_help (int argc, char **argv)
{
    int argi = 1;
    char *cmd = (argi < argc ? argv[argi++] : NULL);
    int index;

    printf("\n");
    for (index = 0; index < UIF_NUM_CMD; index++)
    {
        const UIF_CMD *entry = &UIF_CMDTAB[index];

        if ((cmd == NULL) || (strcmp(cmd, entry->cmd) == 0))
        {
            print_help(entry);
            if (cmd != NULL)
            {
                break;
            }
        }
    }
    if ((cmd != NULL) && (index == UIF_NUM_CMD))
    {
        printf(INVCMD, cmd);
    }
    printf("\n");
}
/********************************************************************/
void
uif_cmd_set (int argc, char **argv)
{
    int index;

    printf("\n");
    if (argc == 1)
    {
        printf("Valid 'set' options:\n");
        for (index = 0; index < UIF_NUM_SETCMD; ++index)
        {
            printf(OPTFMT, UIF_SETCMDTAB[index].option);
#if NLUIF_USE_SYNTAX
            printf("%s\n", UIF_SETCMDTAB[index].syntax);
#endif
        }
        printf("\n");
        return;
    }

    if (argc != 3)
    {
        printf("Error: Invalid argument list\n");
        return;
    }

    for (index = 0; index < UIF_NUM_SETCMD; index++)
    {
        if (strcmp(UIF_SETCMDTAB[index].option, argv[1]) == 0)
        {
            if (((argc-1-1) >= UIF_SETCMDTAB[index].min_args) &&
                ((argc-1-1) <= UIF_SETCMDTAB[index].max_args))
            {
                UIF_SETCMDTAB[index].func(argc, argv);
                return;
            }
            else
            {
                printf(INVARG, argv[1]);
                return;
            }
        }
    }
    printf(INVOPT, argv[1]);
}

/********************************************************************/
void
uif_cmd_show (int argc, char **argv)
{
    int index;

    printf("\n");
    if (argc == 1)
    {
        /*
         * Show all Option settings
         */
        argc = 2;
        argv[2] = NULL;
        for (index = 0; index < UIF_NUM_SETCMD; index++)
        {
            printf(OPTFMT, UIF_SETCMDTAB[index].option);
            UIF_SETCMDTAB[index].func(argc, argv);
            printf("\n");
        }
        printf("\n");
        return;
    }

    for (index = 0; index < UIF_NUM_SETCMD; index++)
    {
        if (strcmp(UIF_SETCMDTAB[index].option, argv[1]) == 0)
        {
            if (((argc-1-1) >= UIF_SETCMDTAB[index].min_args) &&
                ((argc-1-1) <= UIF_SETCMDTAB[index].max_args))
            {
                printf(OPTFMT, UIF_SETCMDTAB[index].option);
                UIF_SETCMDTAB[index].func(argc, argv);
                printf("\n\n");
                return;
            }
            else
            {
                printf(INVARG, argv[1]);
                return;
            }
        }
    }
    printf(INVOPT, argv[1]);
}

/********************************************************************/
#endif /* !NLUIF_USE_MINISHELL */
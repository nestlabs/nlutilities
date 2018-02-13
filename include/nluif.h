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
 *      This file defines a framework for an interactive command line
 *      user interface.
 *
 *      @note The actual commands, set/show parameters, and prompt are
 *            configured at the project level.
 *
 */

#ifndef NLUTILITIES_NLUIF_H
#define NLUTILITIES_NLUIF_H

#include <stdbool.h>
#include <stdint.h>

/********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Function prototypes
 */
void
uif_set_prompt(const char *s);

void
uif_prompt(void);

int
uif_handle_input_char(int ch);

uint32_t
uif_get_value (const char *, bool *, int);

void
uif_run_cmd (void);

void
uif_cmd_help (int, char **);

void
uif_cmd_set (int, char **);

void
uif_cmd_show (int, char **);

/*
 * Maximum command line arguments
 */
#define UIF_MAX_ARGS    29

/*
 * Maximum length of the command line
 */
#define UIF_MAX_LINE    768

#define UIF_HISTORY_CNT 5

/*
 * Maximum length of the prompt string
 */
#define UIF_MAX_PROMPT    8

#ifndef UIF_USE_VERBOSE
#define UIF_USE_VERBOSE 1
#endif

#if UIF_USE_VERBOSE
#define UIF_USE_DESCRIPTION 1
#define UIF_USE_SYNTAX      1
#else
#define UIF_USE_DESCRIPTION 0
#define UIF_USE_SYNTAX      0
#endif /* UIF_USE_VERBOSE */

/*
 * The command table entry data structure
 */
typedef struct
{
    const char *  cmd;              /* command name user types, ie. GO  */
    int     min_args;               /* min num of args command accepts  */
    int     max_args;               /* max num of args command accepts  */
    int     flags;                  /* command flags (e.g. repeat)      */
    void    (*func)(int, char **);  /* actual function to call          */
#if UIF_USE_DESCRIPTION
    const char *  description;      /* brief description of command     */
#endif
#if UIF_USE_SYNTAX
    const void *  syntax;           /* syntax of command                */
#endif
} UIF_CMD;

typedef void (*UIF_SYNTAX_FUNC)(const char *name);

#if UIF_USE_DESCRIPTION && UIF_USE_SYNTAX
#define DECLARE_UIF_CMD(name, min, max, flags, func, desc, syntax) \
	{ name, min, max, flags, func, desc, syntax }
#elif UIF_USE_DESCRIPTION && !UIF_USE_SYNTAX
#define DECLARE_UIF_CMD(name, min, max, flags, func, desc, syntax) \
	{ name, min, max, flags, func, desc }
#elif !UIF_USE_DESCRIPTION && UIF_USE_SYNTAX
#define DECLARE_UIF_CMD(name, min, max, flags, func, desc, syntax) \
	{ name, min, max, flags, func, syntax }
#else
#define DECLARE_UIF_CMD(name, min, max, flags, func, desc, syntax) \
	{ name, min, max, flags, func }
#endif /* UIF_USE_DESCRIPTION && UIF_USE_SYNTAX */

/*
 * Prototype and macro for size of the command table
 */
extern const UIF_CMD UIF_CMDTAB[];
extern const int UIF_NUM_CMD;
#define UIF_CMDTAB_SIZE             (sizeof(UIF_CMDTAB)/sizeof(UIF_CMD))

#define UIF_CMD_FLAG_REPEAT         0x1
#define UIF_CMD_FLAG_SYNTAX_FUNC    0x2

/*
 * Macros for User InterFace command table entries
 */
#ifndef UIF_CMD_HELP
#define UIF_CMD_HELP    \
    DECLARE_UIF_CMD("?", 0, 1, 0, uif_cmd_help, "show available commands", ""), \
    DECLARE_UIF_CMD("help", 0, 1, 0, uif_cmd_help, "show available commands", "")
#endif

#ifndef UIF_CMD_SET
#define UIF_CMD_SET \
    DECLARE_UIF_CMD("set", 0, 2, 0, uif_cmd_set, "Set Config", "<option value>")
#endif

#ifndef UIF_CMD_SHOW
#define UIF_CMD_SHOW    \
    DECLARE_UIF_CMD("show", 0, 1, 0, uif_cmd_show, "Show Config", "<option>")
#endif

/*
 * Macro to include all standard user interface commands
 */
#define UIF_CMDS_ALL    \
    UIF_CMD_HELP, 	\
	UIF_CMD_SET, 	\
	UIF_CMD_SHOW

/*
 * The set/show table entry data structure
 */
typedef struct
{
    const char *  option;
    int           min_args;
    int           max_args;
    void          (*func)(int, char **);
    const char *  syntax;
} UIF_SETCMD;

/*
 * Prototype and macro for size of the table
 */
extern const UIF_SETCMD UIF_SETCMDTAB[];
extern const int UIF_NUM_SETCMD;
#define UIF_SETCMDTAB_SIZE      (sizeof(UIF_SETCMDTAB)/sizeof(UIF_SETCMD))

/********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* NLUTILITIES_NLUIF_H */

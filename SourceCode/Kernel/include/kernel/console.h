#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "libc/stdint.h"

#define CONSOLE_CMD_NAME 64         /* max cmd name len */
#define CONSOLE_CMD_NUM 64         /* max cmd number */
#define CONSOLE_BUFFER_SIZE 512     /* console input or output buffer len */
#define CONSOLE_MAX_PARAM_NUM 5     /* cmd max param num */
#define CONSOLE_HISTORY_CMD_NUM 10  /* num of list history cmd */

struct ConsoleDevice;
struct ConsoleCmdManager;
struct ConsoleCmdParam;
struct ConsoleIO;
struct  ConsoleCmdHistory;

typedef void (* consoleCmdHandle) (struct ConsoleDevice *cmd);

typedef struct ConsoleCmd{
    char name[CONSOLE_CMD_NAME];
    consoleCmdHandle handle;
}ConsoleCmd;

typedef ConsoleCmd * (* CmdManagerMatchCmd) (struct ConsoleCmdManager *, const uint8_t *name);
typedef void (* CmdManagerRegisterCmd) (struct ConsoleCmdManager *, struct ConsoleCmd *);
typedef void (* CmdManagerUnregisterCmd) (struct ConsoleCmdManager *, struct ConsoleCmd *);
typedef void (* CmdManagerInit) (struct ConsoleCmdManager *);
typedef int (*CmdManagerGetAllCmd) (struct ConsoleCmdManager *, char *, int);
typedef void (* CmdManagerCmdIteratorStart) (struct ConsoleCmdManager *);
typedef ConsoleCmd *(* CmdManagerCmdIteratorNext) (struct ConsoleCmdManager *);

typedef struct CmdManagerOpr{
    CmdManagerRegisterCmd registerCmd;
    CmdManagerUnregisterCmd unregisterCmd;
    CmdManagerMatchCmd matchCmd;
    CmdManagerInit init;
    CmdManagerGetAllCmd getAllCmd;
    CmdManagerCmdIteratorStart iterStart;
    CmdManagerCmdIteratorNext iterNext;
}CmdManagerOpr;

typedef struct ConsoleCmdManager{
    int current;
    struct ConsoleCmd cmd[CONSOLE_CMD_NUM];
    struct CmdManagerOpr operation;
}ConsoleCmdManager;

typedef void (* ConsoleCmdHistoryIteratorStart) (struct ConsoleCmdHistory *);
typedef ConsoleCmd *(* ConsoleCmdHistoryIteratorNext) (struct ConsoleCmdHistory *);
typedef ConsoleCmd *(* ConsoleCmdHistoryIteratorPrev) (struct ConsoleCmdHistory *);
typedef void (* ConsoleCmdHistoryInit) (struct ConsoleCmdHistory *);
typedef void (* ConsoleCmdHistoryCycleAdd) (struct ConsoleCmdHistory *, struct ConsoleCmd *);


typedef enum KEYNAME {
    KEY_UP = 0,
    KEY_DOWN,
    KEY_LEFT,
    KET_RIGHT,
    KET_INVAILD,
}KEYNAME;

typedef struct KeyMap{
    KEYNAME keyName;
    char keycode[3]; 
}KeyMap;

typedef struct ConsoleCmdHistory{
    int current;
    int iterIndex;
    struct ConsoleCmd *historyCmd[CONSOLE_HISTORY_CMD_NUM];
    ConsoleCmdHistoryIteratorNext cmdHistoryIterNext;
    ConsoleCmdHistoryIteratorStart cmdHistoryIterStart;
    ConsoleCmdHistoryIteratorPrev cmdHistoryIterPrev;
    ConsoleCmdHistoryCycleAdd cmdHistoryCycleAdd;
    ConsoleCmdHistoryInit cmdHistoryInit;
} ConsoleCmdHistory;

typedef enum CONSOLE_MACHINE_STATUS{
    CONSOLE_MACHINE_INIT,
    CONSOLE_MACHINE_ACCEPT,
    CONSOLE_MACHINE_PARSING,
    CONSOLE_MACHINE_HANDLE,
    CONSOLE_MACHINE_RESPONSE,
    CONSOLE_MACHINE_ERROR_HANDLE,
}CONSOLE_MACHINE_STATUS;

typedef enum CONSOLE_STATUS{
    CONSOLE_OK = 0,            /* need to forwad to handle */
    CONSOLE_PARSED_ERROR,      /* parse input string failed */
    CONSOLE_HANDLE_ERROR,      /* handle cmd failed */
    CONSOLE_CMD_TOO_LONG,      /* input is too long */
    CONSOLE_CMD_INVALID,       /* cmd is invalid */
    CONSOLE_CMD_NOT_FIND,      /* cmd not find */
}CONSOLE_STATUS;

typedef uint8_t * (*console_cmd_get_param)(struct ConsoleCmdParam *, uint8_t index);
typedef void (*console_cmd_clear_param)(struct ConsoleCmdParam *);

typedef struct ConsoleCmdParam{
    uint8_t paramNum;
    uint8_t *param[CONSOLE_MAX_PARAM_NUM];
    console_cmd_get_param cmdGetParam;
    console_cmd_clear_param cmdClearParam;
}ConsoleCmdParam;

typedef int (* consoleInlineEditInput)(struct ConsoleDevice *cmd, char currentCh);

typedef struct ConsoleInlineEditor {
    int mactchIndex;
    consoleInlineEditInput editInput;
}ConsoleInlineEditor;

/* this function will block, return only when receive '\n' or '\r' */
typedef void (* consoleReceiveInput)(struct ConsoleDevice *cmd);
typedef int (* consoleParseInput)(struct ConsoleDevice *console);
typedef uint8_t (* consoleResposeOutput)(struct ConsoleDevice *console, uint8_t *out);
typedef void (* consoleRun)(struct ConsoleDevice *cmd);
typedef void (* consoleStateMachine)(struct ConsoleDevice *cmd);
typedef void (* consoleHandleCmd)(struct ConsoleDevice *cmd);
typedef void (* consoleErrorHandle)(struct ConsoleDevice *);
typedef void (* consoleWelcome)(struct ConsoleDevice *);
typedef void (* consolePrompt)(struct ConsoleDevice *);
typedef void (* consoleInlineEditor)(struct ConsoleDevice *);

typedef void (* consoleIoPutChar)(uint8_t ch);
typedef uint8_t (* consoleIoGetChar)(struct ConsoleIO *consoleIO);

typedef struct ConsoleIO{
    uint8_t echoSwitch;   /* input echo switch */
    consoleIoPutChar putChar;
    consoleIoGetChar getChar;
}ConsoleIO;

typedef struct consoleOpr{
    consoleReceiveInput receiveInput;
    consoleResposeOutput resposeOutput;
    consoleRun run;
    consoleStateMachine Statemachine;
    consoleParseInput parseInput;
    consoleHandleCmd handleCmd;
    consoleErrorHandle errorHandle;
    consoleWelcome welcome;
    consolePrompt prompt;
    consoleInlineEditor inlineEditor;
}consoleOpr;

typedef struct ConsoleDevice{
    CONSOLE_MACHINE_STATUS states;
    CONSOLE_STATUS errorCode;
    uint8_t receiveBuf[CONSOLE_BUFFER_SIZE];

    struct ConsoleIO consoleIO;
    struct consoleOpr operation;
    struct ConsoleCmd *currentCmd;
    struct ConsoleCmdParam cmdParam;
    struct ConsoleCmdManager cmdManager;
    struct ConsoleCmdHistory cmdHistory;
    struct ConsoleInlineEditor inlineEditor;
} ConsoleDevice;

void create_console(struct ConsoleDevice *console);
#endif
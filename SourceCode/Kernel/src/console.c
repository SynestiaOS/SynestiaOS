#include "libc/string.h"
#include "kernel/console.h"
#include "kernel/thread.h"
#include "kernel/scheduler.h"

struct ConsoleCmd *cmd_manager_match_cmd(struct ConsoleCmdManager *manager, const uint8_t *name) {
    struct ConsoleCmd *nextCmd = nullptr;

    manager->operation.iterStart(manager);
    while((nextCmd = manager->operation.iterNext(manager)) != nullptr){
        if (nextCmd->handle == nullptr) {
            continue;
        }
        if (strcmp((char *)name, (char *)nextCmd->name) == 1) {
            return nextCmd;
        }
    }
    return nullptr;
}

void cmd_manager_register_cmd(struct ConsoleCmdManager *manager, struct ConsoleCmd *cmd) {
    struct ConsoleCmd *nextCmd;

    manager->operation.iterStart(manager);

    while ((nextCmd = manager->operation.iterNext(manager)) != nullptr) {
        if ((nextCmd->handle == nullptr) && (strlen(nextCmd->name) == 0))
        {
            break;
        }
    }
    
    nextCmd->handle = cmd->handle;
    strcpy(nextCmd->name, cmd->name);
}

void cmd_manager_unregister_cmd(struct ConsoleCmdManager *manager, struct ConsoleCmd *cmd) {
    struct ConsoleCmd *nextCmd;

    nextCmd = manager->operation.matchCmd(manager, (const uint8_t*)cmd->name);

    if (nextCmd != nullptr) {
        memset(nextCmd->name, 0, CONSOLE_CMD_NAME);
        nextCmd->handle = nullptr;
    }
}

void cmd_manager_init(struct ConsoleCmdManager *manager)
{
    struct ConsoleCmd *nextCmd;

    manager->operation.iterStart(manager);
    while ((nextCmd = manager->operation.iterNext(manager)) != nullptr) {
        memset((void *)nextCmd->name, 0 , CONSOLE_CMD_NAME);
        nextCmd->handle = nullptr;
    } 
}

int cmd_manager_get_all_cmd (struct ConsoleCmdManager *manager, char *result, int size) {
    struct ConsoleCmd *nextCmd;
    int len = strlen(result);
    int lenCmdName;

    manager->operation.iterStart(manager);
    while ((nextCmd = manager->operation.iterNext(manager)) != nullptr) {
        
        if(nextCmd->handle == nullptr) {
            continue;
        }
        lenCmdName = strlen(nextCmd->name);
        if((len + lenCmdName) >= size) {
            return -1;
        }
        strcpy(result + len, nextCmd->name);
        strcpy(result + len + lenCmdName, "\n");
        len = len + lenCmdName + 1;
    }

    return 0;
}

void cmd_manager_iterator_start(struct ConsoleCmdManager *manager) {
    manager->current = 0;
}

ConsoleCmd * cmd_manager_iterator_next(struct ConsoleCmdManager *manager) {
    if (manager->current >= CONSOLE_CMD_NUM) {
        return nullptr;
    }
    return &manager->cmd[manager->current++];
}

int console_parse_input_default(struct ConsoleDevice *console) {

    uint8_t flagParamstart = 0;
    uint8_t count = 0;
    uint8_t *iterator = console->receiveBuf;

    console->cmdParam.cmdClearParam(&console->cmdParam);

    while (((*iterator) != '\0')/* && (iterator - console->receiveBuf) <= CONSOLE_BUFFER_SIZE*/)
    {
        if (*iterator != ' '  && 
            *iterator != '\n' && 
            *iterator != '\t' &&
            *iterator != '\r') {
                if (flagParamstart == 0) {
                    console->cmdParam.param[count] = iterator;
                    count++;
                    flagParamstart = 1;
                }
            } else {
                if (flagParamstart == 1) {
                    flagParamstart = 0;
                }
                *iterator = '\0';
            }
            iterator++;
    }
    console->cmdParam.paramNum = count;

    if(count == 0) {
        console->errorCode = CONSOLE_CMD_INVALID;
    }
    return 0;
}

void console_handle_cmd_default(struct ConsoleDevice *console) {
    uint8_t *cmdName = console->cmdParam.cmdGetParam(&console->cmdParam, 0);
    ConsoleCmd *cmd = console->cmdManager.operation.matchCmd(&console->cmdManager, cmdName);

    if (cmd == nullptr) {
        console->errorCode = CONSOLE_CMD_NOT_FIND;
        return;
    }

    cmd->handle(console);
}

void console_state_machine_default(struct ConsoleDevice *console) {
    
    while (1)
    {
        switch (console->states)
        {
        case CONSOLE_MACHINE_INIT:
            console->operation.welcome(console);
            console->states = CONSOLE_MACHINE_ACCEPT;
            break;
        case CONSOLE_MACHINE_ACCEPT:
            console->operation.receiveInput(console);
            console->states = CONSOLE_MACHINE_PARSING;
            break;
        case CONSOLE_MACHINE_PARSING:
            console->operation.parseInput(console);
            console->states = CONSOLE_MACHINE_HANDLE;
            break;
        case CONSOLE_MACHINE_HANDLE:
            console->operation.handleCmd(console);
            console->states = CONSOLE_MACHINE_ACCEPT;
        default:
            break;
        }

        if (console->errorCode != CONSOLE_OK) {
            console->operation.errorHandle(console);
        }
    }
}

void console_receive_input_default(struct ConsoleDevice *console){
     uint8_t receive; 

     memset(&console->receiveBuf, 0, CONSOLE_BUFFER_SIZE);
     console->operation.prompt(console);

     while (1)
     {
        receive = console->consoleIO.getChar(&console->consoleIO);
 
        if(0 == console->inlineEditor.editInput(console, receive)) {
            break;
        }
    }
 }

void console_show_version(struct ConsoleDevice *console) {
   console->operation.resposeOutput(console, (uint8_t *)"Welcom to Synestia Console v1.0\n");
}

void console_show_prompt(struct ConsoleDevice *console) {
   console->operation.resposeOutput(console, (uint8_t *)"#");
}

 uint8_t console_respose_output_default(struct ConsoleDevice *console, uint8_t *out){
     printf("%s", out);
     return 0;
 }

void console_run_default(struct ConsoleDevice *console) {
    while (1) {
        console->operation.Statemachine(console);
    }
}

void console_error_handle_default(struct ConsoleDevice *console) {
    uint8_t *errStr = nullptr;
    uint8_t errStrFlag = 1;

    switch (console->errorCode)
    {
    case CONSOLE_PARSED_ERROR :
        errStr = (uint8_t *)" input is invalid\n";
        break;
    case CONSOLE_HANDLE_ERROR :
        errStr =  (uint8_t *)" cmd handle failed\n";
        break;
    case CONSOLE_CMD_TOO_LONG :
        errStr =  (uint8_t *)" cmd is too long\n";
        break;
    case CONSOLE_CMD_NOT_FIND:
        errStr =  (uint8_t *)" cmd not find\n";
        console->operation.resposeOutput(console, console->cmdParam.cmdGetParam(&console->cmdParam ,0));
        break;
    case CONSOLE_CMD_INVALID :
    default:
        errStrFlag = 0;
        break;
    }
    if (errStrFlag) {
        console->operation.resposeOutput(console, errStr);
    }
    console->errorCode = CONSOLE_OK;
    console->states = CONSOLE_MACHINE_ACCEPT;
}

void console_io_put_char(uint8_t ch){
    uart_put_char(ch);
}

uint8_t console_io_get_char(struct ConsoleIO *consoleIO) {
    uint8_t ch = do_uart_get_char();
    
    if(consoleIO->echoSwitch == 1) {
        consoleIO->putChar(ch);
    }
    return ch;
}

uint8_t * console_cmd_get_param_default(struct ConsoleCmdParam *cmdParam, uint8_t index)
{
        if(cmdParam->paramNum < index){
            return nullptr;
        }
        return cmdParam->param[index];
}

void console_cmd_clear_param_default(struct ConsoleCmdParam *cmdParam) {
    cmdParam->paramNum = 0;
    memset(&cmdParam->param, 0, CONSOLE_MAX_PARAM_NUM * sizeof(int));
}


void console_cmd_history_iterator_Start (struct ConsoleCmdHistory *history){
    history->iterIndex = history->current;
}

ConsoleCmd * console_cmd_history_iterator_next(struct ConsoleCmdHistory * history){
    if (history->iterIndex >= CONSOLE_HISTORY_CMD_NUM)
        history->iterIndex = 0;

    if (history->historyCmd[history->iterIndex] == nullptr) {
        return nullptr;
    }
    
    if(history->iterIndex >= history->current) {
        return nullptr;
    }

    return history->historyCmd[history->iterIndex++];
}

ConsoleCmd * console_cmd_history_iteratorPrev (struct ConsoleCmdHistory *history){
    int currentPrev = history->iterIndex - 1;

    if (currentPrev < 0)
        currentPrev = CONSOLE_HISTORY_CMD_NUM -1 ;
    
    if (history->historyCmd[currentPrev] == nullptr) {
        return nullptr;
    }

    /* all cmd is checked */
    if (currentPrev < history->current) {
        return nullptr;
    }

    history->iterIndex = currentPrev;
    return history->historyCmd[currentPrev];
}

void console_cmd_history_cycle_add(struct ConsoleCmdHistory *history, struct ConsoleCmd *cmd)
{
    history->historyCmd[history->current] = cmd;
}

void console_cmd_history_init(struct ConsoleCmdHistory *history) {
    int index = 0;

    for(index = 0; index < CONSOLE_HISTORY_CMD_NUM; index++) {
        history->historyCmd[index] = nullptr;
    }

    history->current = 0;
    history->iterIndex = 0;
}
/*  return 0: have receive a complete cmd */
int console_inline_editor(struct ConsoleDevice * console, char receive){
    static int len = 0;

 /*   KeyMap keyMap[3] = {
        {KEY_UP,    {0x1b,0x5b, 0x41},},
        {KEY_DOWN,  {0x1b,0x5b, 0x42},},
        {KET_RIGHT, {0x1b,0x5b, 0x43},},
        {KEY_LEFT,  {0x1b,0x5b, 0x44},},
    }; */

    /* handle delete char */
    if (receive == '\b' || receive == 127) {
        len--;
        if (len < 0)
            len = 0;
    }

    console->receiveBuf[len++] = receive;
    if (len >= CONSOLE_BUFFER_SIZE - 1) {
        console->errorCode = CONSOLE_CMD_TOO_LONG;
    }

    if (receive == '\n' || receive == '\r') {
        len = 0;
        return 0;
    }
    return 1;
}

void create_console_cmd_history(struct ConsoleCmdHistory *history) {

    history->cmdHistoryCycleAdd = console_cmd_history_cycle_add;
    history->cmdHistoryIterNext = console_cmd_history_iterator_next;
    history->cmdHistoryIterPrev = console_cmd_history_iteratorPrev;
    history->cmdHistoryIterStart = console_cmd_history_iterator_Start;

    history->cmdHistoryInit = console_cmd_history_init;
    history->cmdHistoryInit(history);
}

static void create_array_cmd_manager(struct ConsoleCmdManager *manager)
{
    manager->operation.init = cmd_manager_init;
    manager->operation.matchCmd = cmd_manager_match_cmd;
    manager->operation.registerCmd = cmd_manager_register_cmd;
    manager->operation.unregisterCmd = cmd_manager_unregister_cmd;
    manager->operation.iterNext = cmd_manager_iterator_next;
    manager->operation.iterStart = cmd_manager_iterator_start;
    manager->operation.getAllCmd = cmd_manager_get_all_cmd;
    manager->current = 0;
    
    manager->operation.init(manager);
}

void create_console(struct ConsoleDevice *console) {

    console->states = CONSOLE_MACHINE_INIT;
    memset(console->receiveBuf, 0, CONSOLE_BUFFER_SIZE);

    console->operation.handleCmd = console_handle_cmd_default;
    console->operation.parseInput = console_parse_input_default;
    console->operation.receiveInput = console_receive_input_default;
    console->operation.resposeOutput = console_respose_output_default;
    console->operation.welcome = console_show_version;
    console->operation.prompt = console_show_prompt;
    console->operation.run = console_run_default;
    console->operation.Statemachine = console_state_machine_default;
    console->operation.errorHandle = console_error_handle_default;

    console->cmdParam.cmdGetParam = console_cmd_get_param_default;
    console->cmdParam.cmdClearParam = console_cmd_clear_param_default;
    console->inlineEditor.editInput = console_inline_editor;

    console->consoleIO.getChar = console_io_get_char;
    console->consoleIO.putChar = console_io_put_char;
    console->consoleIO.echoSwitch = 1;

    create_console_cmd_history(&console->cmdHistory);
    create_array_cmd_manager(&console->cmdManager);

    console->errorCode = CONSOLE_OK;
}

/* client code begin */
void HelpCmdHandle (struct ConsoleDevice *console) {
    char result[128] = {0};
    ConsoleCmdManager *manager = &console->cmdManager;

    manager->operation.getAllCmd(manager, result, 128);
    console->operation.resposeOutput(console, (uint8_t *)result);   
}

void VersionCmdHandle (struct ConsoleDevice *console) {
    console->operation.resposeOutput(console, (uint8_t *)"Synestia Console v1.0\n");
}

int console_atoi(char* pstr)
{
	int integer = 0;
	int sign = 1;

	if(pstr == nullptr) {
		return 0;
    }

	if(*pstr == '-') {
		sign = -1;
	}

	if(*pstr == '-' || *pstr == '+') {
		pstr++;
	}

	while(*pstr >= '0' && *pstr <= '9') {
		integer = integer * 10 + *pstr - '0';
		pstr++;
	}
	integer = sign * integer;
	return integer;
}

void AddCmdHandle (struct ConsoleDevice *console) {
    int num1 = 0;
    int num2 = 0;
    uint8_t result[64] = {0};

    if(console->cmdParam.paramNum != 3) {
        console->operation.resposeOutput(console, (uint8_t *)"Invalid param\nUsage: add numa numb\n");
        return;
    } 

    num1 = console_atoi((const char *)console->cmdParam.cmdGetParam(&console->cmdParam ,1));
    num2 = console_atoi((const char *)console->cmdParam.cmdGetParam(&console->cmdParam ,2));

    sprintf((char *)result, "%d + %d = %d\n", num1, num2, num1 + num2);
    console->operation.resposeOutput(console, (uint8_t *)result);
}

void MeminfoCmdHandle (struct ConsoleDevice *console) {
    console->operation.resposeOutput(console, (uint8_t *)"meminfo: \n");   
}

/* you can to add command here */
ConsoleCmd basicCmdTable[] = {
    {"add", AddCmdHandle},
    {"version", VersionCmdHandle},
    {"help", HelpCmdHandle},
    {"meminfo", MeminfoCmdHandle}
};

extern Scheduler cfsScheduler;
struct  ConsoleDevice console;

void create_basic_cmd(struct ConsoleDevice *console, ConsoleCmd *cmdTable, int cmdNum)
{
    int index = 0;
    
    while (index < cmdNum)
    {
        console->cmdManager.operation.registerCmd(&console->cmdManager, &cmdTable[index++]);
    }
}

_Noreturn uint32_t * console_run(int args) {
        console.operation.run(&console);
}

void create_synestia_console()
{
    create_console(&console);
    create_basic_cmd(&console, basicCmdTable, sizeof(basicCmdTable)/sizeof(ConsoleCmd));

    Thread *consoleThread = thread_create("console", (ThreadStartRoutine) &console_run, 0, 0,
                                                   sysModeCPSR());
    consoleThread->cpuAffinity = cpu_number_to_mask(0);
    cfsScheduler.operation.addThread(&cfsScheduler, consoleThread, 1);   
}

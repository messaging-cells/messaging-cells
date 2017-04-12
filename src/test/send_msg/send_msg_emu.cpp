
#include "send_msg.hh"
#include "core_main.h"

void (*CORE_MAIN_FUNC)() = &pru_send_msg;

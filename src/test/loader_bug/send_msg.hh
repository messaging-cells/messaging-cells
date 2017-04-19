
// pru_1.h

#ifndef SEND_MSG_HH
#define SEND_MSG_HH

#include "actor.hh"

#ifdef __cplusplus
bj_c_decl {
#endif

int main();
void recv_actor_handler(missive* msg);
void pru_send_msg() bj_code_dram;

#ifdef __cplusplus
}
#endif

#endif // SEND_MSG_HH



#include <cstdlib>
#include <new>

#include "global.h"
#include "trace.h"
#include "ids.h"
#include "cpp_main.h"
#include "row.hh"

//----------------------------------------------------------------------------
// To FAKE std c++ lib initialization and destructions of global objects
// DO NOT FORGET to call initializers explicitly.

extern "C" int 
__cxa_atexit(void* obj, void (*destruc) (void*), void* dso_hndl){
	static_cast<void>(obj);
	static_cast<void>(destruc);
	static_cast<void>(dso_hndl);
	return 0;
}

void* __dso_handle = bj_null;

//----------------------------------------------------------------------------

class actor;
class message;
class core_actor;

typedef void (*message_handler_t)(message* msg);

class bj_align(8) actor{
public:
	static
	char*	CL_NAME;

	virtual
	char*	get_cls_name(){
		return actor::CL_NAME;
	}

	message_handler_t	handler;
};

char*	actor::CL_NAME = as_pt_char("{actor}");


class bj_align(8) message{
public:
	actor*	dst;
	actor*	src;
	bj_size_t	size;
};

class bj_align(8) msg_request{
public:
	core_actor* 	src;
	bj_size_t 		size;

	msg_request(){
		src = bj_null;
		size = 0x0;
	}
	~msg_request(){}
};

class bj_align(8) core_receiver: public actor {
public:
	msg_request	mailbox;
	
	core_receiver(){
	}
	~core_receiver(){}
};

class bj_align(8) core_sender: public actor {
public:
	message*	send_addr;
	
	core_sender(){
		send_addr = bj_null;
	}
	~core_sender(){}

	void 
	request_send(bj_id_t core, bj_size_t sz);
};

#define BJ_MAX_TOP_SENDERS 10

core_receiver bj_top_receiver;	// need explicit initialization

core_sender	bg_top_senders[BJ_MAX_TOP_SENDERS];

#define BJ_MAX_READY_MESSAGES 100
#define BJ_MAX_WAITING_MESSAGES 100

message* bj_ready_messages[BJ_MAX_READY_MESSAGES];
message* bj_waiting_messages[BJ_MAX_WAITING_MESSAGES];

void 
init_cpp_main(){
	init_all_class_ids();
	//new (&bj_top_actor) bj_core_actor(); 
}

void
cpp_main(){
	init_cpp_main();
}


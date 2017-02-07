
#include <cstdlib>
#include <new>

#include "global.h"
#include "trace.h"
#include "actor.h"

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

/*
void * operator new(size_t sz) noexcept {
	return 0;
}

void operator delete(void *pt) noexcept {
}

void * operator new[](size_t sz) noexcept {
	return operator new(sz);
}

void operator delete[](void *pt) noexcept {
	operator delete(pt);
}

void * operator new(size_t sz, std::nothrow_t) noexcept {
	return operator new(sz);
}

void operator delete(void *pt, std::nothrow_t) noexcept {
	operator delete(pt);
}*/

typedef uint8_t bj_class_id_t;

#define bj_class_id(cls) BJ_CLASS_##cls

#define as_pt_char(the_str) (const_cast<char *>(the_str))

#define bj_class_set_id(cls) \
	bj_all_class_ids_arr[bj_class_id(cls)] = as_pt_char("{" #cls "}");


enum bj_all_classes_ids {
	bj_invalid_id = 10,

	bj_class_id(bj_actor),
	bj_class_id(bj_message),
	bj_class_id(bj_core_actor),

	bj_tot_class_ids
};

char* bj_all_class_ids_arr[bj_tot_class_ids];

void 
bj_init_all_actor_ids(){
	//bj_memset((uint8_t*)bj_all_class_ids_arr, 0, sizeof(bj_all_class_ids_arr));

	bj_class_set_id(bj_actor);
	bj_class_set_id(bj_message);
	bj_class_set_id(bj_core_actor);
};

class bj_actor;
class bj_message;
class bj_core_actor;

typedef void (*bj_message_handler_t)(bj_message* msg);


class bj_align(8) bj_actor{
public:
	bj_message_handler_t	handler;
};

class bj_align(8) bj_message{
public:
	bj_actor*	dst;
	bj_actor*	src;
	bj_size_t	size;
};

class bj_align(8) bj_msg_request{
public:
	bj_core_actor* 	src;
	bj_size_t 		size;

	bj_msg_request(){
		src = bj_null;
		size = 0x0;
	}
	~bj_msg_request(){}
};

class bj_align(8) bj_core_receiver: public bj_actor {
public:
	bj_msg_request	mailbox;
	
	bj_core_receiver(){
	}
	~bj_core_receiver(){}
};

class bj_align(8) bj_core_sender: public bj_actor {
public:
	bj_message*	send_addr;
	
	bj_core_sender(){
		send_addr = bj_null;
	}
	~bj_core_sender(){}

	void 
	request_send(bj_id_t core, bj_size_t sz);
};

#define BJ_MAX_TOP_SENDERS 10

bj_core_receiver bj_top_receiver;	// need explicit initialization

bj_core_sender	bg_top_senders[BJ_MAX_TOP_SENDERS];

#define BJ_MAX_READY_MESSAGES 100
#define BJ_MAX_WAITING_MESSAGES 100

bj_message* bj_ready_messages[BJ_MAX_READY_MESSAGES];
bj_message* bj_waiting_messages[BJ_MAX_WAITING_MESSAGES];

void 
bj_init_cpp_main(){
	bj_init_all_actor_ids();
	//new (&bj_top_actor) bj_core_actor(); 
}

void
cpp_main(){
	bj_init_cpp_main();
}


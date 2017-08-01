
#include "cell.hh"

#include "nervenet.hh"

MCK_DEFINE_ACQUIRE_ALLOC(nervenet, 32);	// defines nervenet::acquire_alloc

MCK_DEFINE_MEM_METHODS(neupole, 32, bj_ava_neupoles)
MCK_DEFINE_MEM_METHODS(neuron, 32, bj_ava_neurons)
MCK_DEFINE_MEM_METHODS(synapse, 32, bj_ava_synapses)

BJ_DEFINE_nervenet_methods();

nervenode::nervenode(){ 
	ki = nd_invalid; 
	id = 0; 
	sz = 0; 
} 

nervenode::~nervenode(){} 

neupole::neupole(){ 
	handler_idx = idx_neupole;
	opp = mc_null; 
} 

neupole::~neupole(){} 

neuron::neuron(){} 

neuron::~neuron(){} 

synapse::synapse(){
	handler_idx = idx_synapse;
	owner = mc_null;
	parent = mc_null;
	mate = mc_null;
	group_sz = 0;
} 

synapse::~synapse(){} 


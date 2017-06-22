
//----------------------------------------------------------------------------
/*! \file hello_world.cpp

\brief Minimal library example.

\details 

\include hello_world.cpp

*/

#include "cell.hh"

void mc_cores_main() {
	kernel::init_sys();

	mck_slog2("HELLO_WORLD\n");	

	kernel::finish_sys();
}


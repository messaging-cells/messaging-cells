

#include "global.h"

//----------------------------------------------------------------------------
/*! \mainpage <h1>Introduction</h1>

<p>
This is the doxy generated documentation of the <a href="https://github.com/joseluisquiroga/ben-jose" target="blank">
Ben-Jose</a> Trainable SAT Solver Library. It is not a complete reference of all the classes and functions. It is a selection of the most releveant classes and functions that help in the understanding of the innerworkig of the library.

<p> The \ref docgrp_API of the library is implemented in the files ben_jose.cpp and ben_jose.h, and documented in:

<ul>
<li> \ref docgrp_API
</ul>

<p>
The architecture of the ben-jose library is strongly monolitic in the sense that the basic functionality of the whole library is basically one function (brain::solve_instance) with three presentations: 

<ul>
<li> \ref bj_solve_file
<li> \ref bj_solve_data 
<li> \ref bj_solve_literals
</ul>

<p>
That means that every piece of code within the 'library' directory of the source tree is tightly coupled. Having said that, this documentations should give a good idea of it's architecture.

<p>
The most relevant classes of the library implementation can be grouped as:

<ul>
<li> \ref docgrp_CDCL_classes
<li> \ref docgrp_stab_classes
<li> \ref docgrp_matching_classes
<li> \ref docgrp_database_classes
</ul>

<p>
The macro behavior of the innerwork of the library is described in:

<ul>
<li> macro_algorithm_ben_jose.cpp
</ul>

*/

//============================================================
/*! \defgroup docgrp_CDCL_classes DPLL+BCP+CDCL classes

This group corresponds to all classes relating to DPLL+BCP+CDCL processing.
*/

//============================================================
/*! \defgroup docgrp_stab_classes Stabilization classes

This group corresponds to all classes relating to the stabilization processes. The process of calculating a BDUST canonical form formula (BCFF) is called stabilization.
*/



int main() {
	mc_cores_main();
	return 0;
}


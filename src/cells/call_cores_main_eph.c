

#include "global.h"

//----------------------------------------------------------------------------
/*! \mainpage <h1>Introduction</h1>

<p>
This selected doxy generated documentation of the <a href="https://github.com/messaging-cells/messaging-cells" target="blank">Messaging Cells</a> Library is a description of the most releveant classes and functions that help in the understanding of the API and inner-workig of the library.

<p>
This documentation is gruped in the following <a href="modules.html">modules</a> :

<p>
\ref docgrp_debug_features

<p>
\ref docgrp_messaging

<p>
\ref docgrp_memory_features

<p>
\ref docgrp_addressing_features

<p>
\ref docgrp_linking_features

<p>
\ref docgrp_loading_features 

<p>
\ref docgrp_inner_working

*/

//============================================================
/*! \defgroup docgrp_debug_features Debug features

\brief Module describing debug features

\details 
<p>
The debug features are basically two:

<ul>
<li>
All functions in \ref log.h to print and log in the host. Functions like: \ref mck_slog and \ref mck_slog2. 
<li>
Functions to get the stack trace. When calling \ref mck_get_call_stack_trace and when aborting execution by calling \ref mck_abort you get the stack trace printed in the host.
</ul>

<p>
The most simple example of usage of a log function is \includedoc hello_world.cpp program.


*/

//============================================================
/*! \defgroup docgrp_messaging Messaging

\brief Module describing messaging

\details 
<p>
Messagging is done beetween two \ref cell s by sending \ref missive s. So no messages ;)

<p>
The most simple example of messaging usage is the \includedoc send_msg.cpp program.

<p>
The classical more complex example of the 
<a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem">eating philosophers</a> 
is coded in the \includedoc philo.cpp program and shows some
\ref docgrp_addressing_features and \ref docgrp_memory_features of the library.

*/

//============================================================
/*! \defgroup docgrp_memory_features Memory features

\brief Module describing memory features

\details 

*/

//============================================================
/*! \defgroup docgrp_addressing_features Addressing features

\brief Module describing addressing convertion functions.

\details 

*/

//============================================================
/*! \defgroup docgrp_linking_features Linking features

\brief Module describing linking features.

\details 
<p>
This group corresponds to two main areas:

<ul>
<li>
The values you can set in the link script.
<li>
THe techniques used to partition your code in modules.
</ul>


*/

//============================================================
/*! \defgroup docgrp_loading_features Loading features

\brief Module describing loading features.

\details 
<p>
This group corresponds to basically two main features:
<ul>
<li> The posibility to customize the tree that defines the order in which the library's kernel is loaded in the cores.
<li> The posibility to load different modules in different cores.
</ul>


*/

//============================================================
/*! \defgroup docgrp_inner_working Inner-working

\brief Module describing basic inner-working of the library.

\details 

*/


int main() {
	mc_cores_main();
	return 0;
}


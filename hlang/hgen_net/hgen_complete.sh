#/usr/bin/env bash

_hgen_lognet_completions()
{
	export COMP_CWORD
	eval $COMP_LINE ++
	mapfile -t COMPREPLY < <( cat hgen_lognet_outocomplete_options.txt )
}

complete -F _hgen_lognet_completions hgen_lognet


#/usr/bin/env bash

_hgen_lognet_completions()
{
	export COMP_CWORD
	mapfile -t COMPREPLY < <( $COMP_LINE ++ )
}

complete -F _hgen_lognet_completions hgen_lognet




#include <iostream>
#include <cstdlib>
#include <map>
#include <regex>
 
#include "hgen_net.h"

bool gh_str_is_prefix(const std::string& the_str, const std::string& pfx){
	return (the_str.compare(0, pfx.size(), pfx) == 0);
}

bool gh_args_get_candidates(const gh_str_set_t& map, const std::string& search_for, gh_str_set_t& all_cand){
	bool found_it = false;
	for(std::set<std::string>::iterator ii = map.lower_bound(search_for); ((ii != map.end()) && gh_str_is_prefix(*ii, search_for)); ii++){
		all_cand.insert(*ii);
	}
	auto jj = all_cand.begin();
	if((all_cand.size() == 1) && (jj != all_cand.end()) && (*jj == search_for)){
		found_it = true;
	}
	return found_it;
}

void gh_args_print_candidates(const gh_str_set_t& all_cand){
	for(auto ii = all_cand.begin(); ii != all_cand.end(); ii++){
		std::string cand = *ii;
		fprintf(stdout, "%s\n", cand.c_str());
	}
}

void gh_args_print(int argc, char *argv[]){
	fprintf(stdout, "\n");
	for(int aa = 0; aa < argc; aa++){
		fprintf(stdout, "arg %i = %s \n", aa, argv[aa]);
	}
	if(GH_GLOBALS.args_compl_idx != GH_INVALID_COMPLETE_IDX){
		fprintf(stdout, "compl_idx = %i \n", GH_GLOBALS.args_compl_idx);
	}
	fprintf(stdout, "\n");
}

void gh_dec_args(int& argc, char**& argv, int num_dec){
	for(; num_dec > 0; num_dec--){
		GH_GLOBALS.args_compl_idx--;
		argc--;
		argv = (argv + 1);
	}
}


char** gh_args_get_tail(char *argv[]){
	return (argv + 1);
}

bool gh_args_is_complete_command(int argc, char *argv[]){
	return (((argc - 1) >= 0) && (((std::string)argv[argc - 1]) == "++"));
}

int gh_args_get_complete_index(){
	const char* env_p = gh_null;
	int idx = 1;
	if((env_p = std::getenv("COMP_CWORD")) != gh_null){
		idx = atoi(env_p);
	}
	return idx;
}

bool
gh_args_select_one_of(int argc, char *argv[], gh_str_set_t choices, std::string& sel){
	int cmpl_idx = GH_GLOBALS.args_compl_idx;
	bool is_cmpl = gh_args_is_complete_command(argc, argv);
	
	if(! is_cmpl && (cmpl_idx == GH_INVALID_COMPLETE_IDX)){
		fprintf(stdout, "WARNING. autocomplete is NOT installed. Run \n\t source hgen_complete.sh \nto get it installed.\n");
	}
	if(argc < 1){
		if(! is_cmpl){
			fprintf(stdout, "First parameter must be one of these: \n");
		}
		gh_args_print_candidates(choices);
		return false;
	}
	const std::string pm0 = argv[0];
	gh_str_set_t selec;
	bool found_it = gh_args_get_candidates(choices, pm0, selec);
	if(found_it){
		sel = pm0;
		return true;
	} 
	
	if(! is_cmpl){
		fprintf(stdout, "parameter '%s' is NOT valid. It must be one of these: \n", pm0.c_str());
	} 
	if(! found_it && (selec.size() == 0)){
		gh_args_print_candidates(choices);
	} else {
		gh_args_print_candidates(selec);
	}
	return false;
}

int
main(int argc, char *argv[]){

	gh_str_set_t lv1_commds;
	lv1_commds.insert("test");
	lv1_commds.insert("generate");
	
	GH_GLOBALS.args_compl_idx = gh_args_get_complete_index();
	
	gh_dec_args(argc, argv);
	std::string cho1;
	
	bool ok1 = gh_args_select_one_of(argc, argv, lv1_commds, cho1);
	if(! ok1){
		return -1;
	}
	
	int resp = 0;
	gh_dec_args(argc, argv);
	if(cho1 == "test"){
		resp = test_hlogne2(argc, argv);
	}
		
	return resp;
}



/*

-----------------------------------------

#/usr/bin/env bash

_hgen_lognet_completions()
{
	hgen_lognet ++
	#  COMPREPLY+=("now")
}

complete -F _hgen_lognet_completions hgen_lognet

-----------------------------------------


GET_ENVIROMENT VARIABLE:
if(const char* env_p = std::getenv("COMP_LINE"))
     std::cout << "Your PATH is: " << env_p << '\n';

---------------------------------------

COMP_WORDS: an array of all the words typed after the name of the program the compspec belongs to

COMP_CWORD: an index of the COMP_WORDS array pointing to the word the current cursor is at - in other words, the index of the word the cursor was when the tab key was pressed

COMP_LINE: the current command line

COMPREPLY is an array variable used to store the completions - the completion mechanism uses this variable to display its contents as completions

#include <map>
#include <regex>
using namespace std;

int main()
{
    string env = "[key1,val1][key2,val2]"; //getenv("varname");

    regex rx("\\[([^,]+),([^\\]]+)\\]");
    map<string, string> res;

    for(regex_iterator<string::iterator> it(env.begin(), env.end(), rx), end; it != end; it++)
        res[(*it)[1]] = (*it)[2];

    for(auto it : res) 
        cout << it.first << " = " << it.second << endl;

    return 0;
}

*/




#include <iostream>
#include <cstdlib>
#include <map>
#include <regex>
 
#include "hgen_net.h"

bool gh_str_is_prefix(const std::string& the_str, const std::string& pfx){
	return (the_str.compare(0, pfx.size(), pfx) == 0);
}

void gh_args_get_list(gh_str_list_t& lt_args, int argc, char *argv[]){
	lt_args.resize(0);
	for(int aa = 0; aa < argc; aa++){
		gh_string_t pm = argv[aa];
		lt_args.push_back(pm);
	}
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
		fprintf(GH_GLOBALS.args_compl_output, "%s\n", cand.c_str());
	}
}

void gh_args_print(gh_str_list_t& lt_args){
	fprintf(stdout, "\n");
	int aa = 0;
	fprintf(stdout, "sz=%ld\n", lt_args.size());
	for(auto it = lt_args.begin(); it != lt_args.end(); it++, aa++){
		fprintf(stdout, "arg %i = %s \n", aa, (*it).c_str());
	}
	if(GH_GLOBALS.args_compl_idx != GH_INVALID_COMPLETE_IDX){
		fprintf(stdout, "compl_idx = %i \n", GH_GLOBALS.args_compl_idx);
	}
	fprintf(stdout, "\n");
}

void gh_dec_args(gh_str_list_t& lt_args, int num_dec){
	for(; num_dec > 0; num_dec--){
		GH_GLOBALS.args_compl_idx--;
		lt_args.pop_front();
	}
}

void gh_args_print_last_complete(gh_str_list_t& lt_args){
	//gh_args_print(lt_args);
	FILE* of = GH_GLOBALS.args_compl_output;
	bool is_cmpl = gh_args_is_complete_command(lt_args);
	if(is_cmpl){
		int cmpl_idx = GH_GLOBALS.args_compl_idx;
		if((cmpl_idx >= 0) && (cmpl_idx == (int)(lt_args.size() - 2))){
			auto it = lt_args.rbegin();
			if(it == lt_args.rend()){ return; }
			it++;
			if(it == lt_args.rend()){ return; }
			fprintf(of, "%s ", (*it).c_str());
		}
	}
}

bool gh_args_is_complete_command(gh_str_list_t& lt_args){
	auto it = lt_args.rbegin();
	if(it == lt_args.rend()){ return false; }
	return (*it == "++");
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
gh_args_select_one_of(gh_str_list_t& lt_args, gh_str_set_t& choices, std::string& sel){
	int cmpl_idx = GH_GLOBALS.args_compl_idx;
	bool is_cmpl = gh_args_is_complete_command(lt_args);
	
	if(! is_cmpl && (cmpl_idx == GH_INVALID_COMPLETE_IDX)){
		fprintf(stdout, "WARNING. autocomplete is NOT installed. Run \n\t source hgen_complete.sh \nto get it installed.\n");
	}
	long sz = (long)lt_args.size();
	if(sz < 1){
		if(! is_cmpl){
			fprintf(stdout, "Next parameter must be one of these: \n");
		}
		gh_args_print_candidates(choices);
		return false;
	}
	const std::string& pm0 = lt_args.front();
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

	gh_str_list_t lt_args;
	gh_args_get_list(lt_args, argc, argv);
		
	gh_str_set_t lv1_commds;
	lv1_commds.insert("test");
	lv1_commds.insert("generate");
	
	bool is_cmpl = gh_args_is_complete_command(lt_args);
	if(is_cmpl){
		GH_GLOBALS.args_compl_idx = gh_args_get_complete_index();
		GH_GLOBALS.args_compl_output = fopen(GH_GLOBALS.args_output_name, "w");
		if(GH_GLOBALS.args_compl_output == NULL){
			GH_GLOBALS.args_compl_output = stdout;
		}
	}
	
	gh_dec_args(lt_args);
	std::string cho1;
	
	bool ok1 = gh_args_select_one_of(lt_args, lv1_commds, cho1);
	if(! ok1){
		return -1;
	}
	
	int resp = 0;
	gh_dec_args(lt_args);
	if(cho1 == "test"){
		resp = test_hlogne2(lt_args);
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


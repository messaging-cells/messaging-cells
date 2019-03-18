

#ifndef HL_SEND_TEST_H
#define HL_SEND_TEST_H

#include "hlang.hh"


enum snd_tok_t : hl_token_t {
	tk_snd_invalid,
	tk_snd_start,
	tk_snd_val1,
	tk_snd_val2,
	tk_snd_add,
};

htoken(pr_tok_snd_start, tk_snd_start);
htoken(pr_tok_snd_val1, tk_snd_val1);
htoken(pr_tok_snd_val2, tk_snd_val2);
htoken(pr_tok_snd_add, tk_snd_add);

class cls_snd;

hconst(char, k0, 0);
hconst(char, k1, 11);
hconst(int, k2, 123);

class cls_snd : public hcell {
public:
	hcell_class(cls_snd);
	
	hreference(cls_snd, dst);
	hchar(v1);
	hint(v2);
	hlong(sum);

	hnucleus(central);
	
	hmethod(mth_start);
	
	cls_snd(){}

	~cls_snd(){}
};

void hl_send_test(int argc, char *argv[]);

#endif		// HL_SEND_TEST_H


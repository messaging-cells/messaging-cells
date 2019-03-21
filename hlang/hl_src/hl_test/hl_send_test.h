

#ifndef HL_SEND_TEST_H
#define HL_SEND_TEST_H

#include "hlang.hh"

class cls_snd;

hdeclare_token(pr_tok_snd_start);
hdeclare_token(pr_tok_snd_val1);
hdeclare_token(pr_tok_snd_val2);
hdeclare_token(pr_tok_snd_add);

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


/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#include <stdio.h>
#include "flib/rta.h"
#include "test_common.h"

enum rta_sec_era rta_sec_era;

unsigned dual_2(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	uint64_t ctx = (uint64_t) 0xdf8093280ull;
	int ctx_size = 16;
	uint64_t cipher_key = (uint64_t) 0x5c36c3700ull;
	int cipher_key_size = 16;
	uint64_t auth_key = (uint64_t) 0xc835c4200ull;
	int auth_key_size = 4;
	uint64_t auth = (uint64_t) 0x150c8e140ull;
	int auth_size = 31;
	uint64_t ct_in = (uint64_t) 0x103e40740ull;
	uint64_t pt_out = (uint64_t) 0x7dfa8ff00ull;
	int msg_len = 128;
	uint64_t icv = (uint64_t) 0x91cad53b0ull;
	int icv_size = 32;

	PROGRAM_CNTXT_INIT(buff, 0);
	PROGRAM_SET_36BIT_ADDR();

	JOB_HDR(SHR_NEVER, 0, 0, 0);
	{
		LOAD(ctx, CONTEXT1, 0, ctx_size, 0);
		KEY(KEY1, 0, cipher_key, cipher_key_size, 0);
		KEY(KEY2, 0, auth_key, auth_key_size, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA256, OP_ALG_AAI_HMAC,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_ENABLE,
			      OP_ALG_DECRYPT);
		MOVE(CONTEXT1, 0, IFIFOAB2, 0, ctx_size, WAITCOMP | IMMED);
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_CBC,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_DECRYPT);
		FIFOLOAD(MSG2, auth, auth_size, 0);
		FIFOLOAD(MSGOUTSNOOP, ct_in, msg_len, LAST1 | LAST2);
		FIFOSTORE(MSG, 0, pt_out, msg_len, 0);
		FIFOLOAD(ICV2, icv, icv_size, LAST2);
	}

	return PROGRAM_FINALIZE();
}

uint32_t prg_buff[1000];

int main(int argc, char **argv)
{
	unsigned size;

	pr_debug("DUAL_2 example program\n");
	rta_set_sec_era(RTA_SEC_ERA_2);
	size = dual_2(prg_buff);
	pr_debug("size = %d\n", size);
	print_prog(prg_buff, size);

	return 0;
}

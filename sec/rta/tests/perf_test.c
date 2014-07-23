/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#include <stdio.h>
#include "flib/rta.h"
#include "test_common.h"

enum rta_sec_era rta_sec_era;

unsigned test_perf(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int seqnum = 1;

	PROGRAM_CNTXT_INIT(buff, 0);
	LABEL(test1);
	LABEL(test2);
	LABEL(encap_iv);
	LABEL(seqoutptr);
	LABEL(new_seqinptr);

	{
		SHR_HDR(SHR_ALWAYS, 0, 0);
		WORD(0x17feff00);	/* type 0x17 / protocol version */
		WORD(0x00010000);	/* Epoch / upper bits of SeqNum */
		WORD(seqnum);	/* Lower bits of SeqNum */

		JUMP(test1, LOCAL_JUMP, ALL_TRUE, 0);
		MATHB(MATH0, ADD, 0x0840010008880000, MATH3, 8, IMMED2);
		MATHB(0x08400100009990, XOR, MATH1, MATH3, 8, IMMED);
		SET_LABEL(test1);
		MATHB(0x0840010000aaa0, XOR, MATH1, MATH3, 8, IMMED);
		SET_LABEL(test2);
		MATHB(MATH2, XOR, MATH1, MATH3, 4, 0);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);
		JUMP(test2, LOCAL_JUMP, ALL_TRUE, 0);
		MATHU(MATH0, BSWAP, MATH1, 8, 0);
		/* SYNC (NO_PEND_INPUT); */

		LOAD(4, ICV1SZ, 0, 4, IMMED);
		LOAD(4, ICV2SZ, 0, 4, IMMED);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);
		MATHB(0x0840010000aaa0, XOR, MATH1, MATH3, 8, IMMED);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);
		WORD(0x17feff00);	/* type 0x17 / protocol version */
		WORD(0x00010000);	/* Epoch / upper bits of SeqNum */
		WORD(seqnum);	/* Lower bits of SeqNum */
		JUMP(test1, LOCAL_JUMP, ALL_TRUE, 0);
		MATHB(MATH0, XOR, 0x0840010008880000, MATH3, 8, IMMED2);
		MATHB(0x08400100009990, XOR, MATH1, MATH3, 8, IMMED);
		MATHB(0x0840010000aaa0, XOR, MATH1, MATH3, 8, IMMED);
		MATHB(MATH2, XOR, MATH1, MATH3, 4, 0);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);
		JUMP(test2, LOCAL_JUMP, ALL_TRUE, 0);
		MATHU(MATH0, BSWAP, MATH1, 8, 0);
		/* SYNC (NO_PEND_INPUT); */
		LOAD(4, ICV2SZ, 0, 4, IMMED);
		LOAD(4, ICV1SZ, 0, 4, IMMED);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);
		MATHB(0x0840010000aaa0, XOR, MATH1, MATH3, 8, IMMED);
		MATHU(MATH2, BSWAP, MATH3, 2, NFU);

		SET_LABEL(encap_iv);
		/* All of the IV, both next and previous */
		COPY_DATA(((uint8_t[]) { 00, 00}), 2);

		MOVE(DESCBUF, seqoutptr, MATH0, 0, 16, WAITCOMP | IMMED);
		MATHB(MATH0, XOR, 0x0840010000000000, MATH0, 8, IMMED2);
		MOVE(MATH0, 0, DESCBUF, new_seqinptr, 8, IMMED);
		SET_LABEL(new_seqinptr);
		WORD(0x0);
		WORD(0x0);
		/* NOP(); */
		SEQLOAD(MATH2, 0, 8, 0);
		/* JUMP_COND(all[calm], ADD1); */
		MATHB(MATH0, XOR, MATH2, NONE, 8, 0);
		MATHB(MATH1, XOR, MATH3, NONE, 8, 0);
		/* HALT_COND(all[z], 255); */
		MOVE(MATH0, 0, DESCBUF, encap_iv, 32, IMMED);
		seqoutptr = 8;
	}

	return PROGRAM_FINALIZE();
}

uint32_t prg_buff[1000];

int main(int argc, char **argv)
{
	unsigned size;

	pr_debug("Perf example program\n");
	rta_set_sec_era(RTA_SEC_ERA_4);
	size = test_perf(prg_buff);
	pr_debug("size = %d\n", size);
	print_prog(prg_buff, size);

	return 0;
}

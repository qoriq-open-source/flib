/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#include <stdio.h>
#include "flib/rta.h"
#include "test_common.h"

enum rta_sec_era rta_sec_era;

struct program capwap_program;
struct program job_desc_snippet;

uint32_t capwap_buf[1000];
uint32_t job_buf[1000];

LABEL(label_different_desc);
REFERENCE(label_different_ref);

unsigned generate_capwap_code(struct program *program, uint32_t *buff)
{
	PROGRAM_CNTXT_INIT(buff, 0);
	SHR_HDR(SHR_ALWAYS, 0, 0);

	label_different_ref = JUMP(label_different_desc, LOCAL_JUMP, ALL_TRUE,
				   0);

	return PROGRAM_FINALIZE();
}

unsigned generate_job_desc(struct program *program, uint32_t *buff)
{
	PROGRAM_CNTXT_INIT(buff, 0x20);
	SET_LABEL(label_different_desc);
	MATHB(MATH2, XOR, MATH1, MATH3, 4, 0);
	MATHU(MATH2, BSWAP, MATH3, 2, NFU);

	return PROGRAM_FINALIZE();
}

int main(int argc, char **argv)
{
	unsigned sd_size, jd_size;

	rta_set_sec_era(RTA_SEC_ERA_4);

	sd_size = generate_capwap_code(&capwap_program, capwap_buf);
	jd_size = generate_job_desc(&job_desc_snippet, job_buf);
	PATCH_JUMP_NON_LOCAL(&capwap_program, label_different_ref,
			     label_different_desc);

	pr_debug("Shared desc\n");
	pr_debug("size = %d\n", sd_size);
	print_prog(capwap_buf, sd_size);

	pr_debug("Job desc\n");
	pr_debug("size = %d\n", jd_size);
	print_prog(job_buf, jd_size);

	return 0;
}

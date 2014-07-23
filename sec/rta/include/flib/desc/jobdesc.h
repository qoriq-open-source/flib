/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __DESC_JOBDESC_H__
#define __DESC_JOBDESC_H__

#include "flib/rta.h"
#include "common.h"

/**
 * DOC: Job Descriptor Constructors
 *
 * Job descriptors for certain tasks, like generating MDHA split keys.
 */

/**
 * cnstr_jobdesc_mdsplitkey - Generate an MDHA split key
 * @descbuf: pointer to buffer to hold constructed descriptor
 * @bufsize: pointer to size of descriptor once constructed
 * @ps: if 36/40bit addressing is desired, this parameter must be true
 * @alg_key: pointer to HMAC key to generate ipad/opad from
 * @keylen: HMAC key length
 * @cipher: HMAC algorithm selection, one of OP_ALG_ALGSEL_*
 *     The algorithm determines key size (bytes):
 *     -  OP_ALG_ALGSEL_MD5    - 16
 *     -  OP_ALG_ALGSEL_SHA1   - 20
 *     -  OP_ALG_ALGSEL_SHA224 - 28
 *     -  OP_ALG_ALGSEL_SHA256 - 32
 *     -  OP_ALG_ALGSEL_SHA384 - 48
 *     -  OP_ALG_ALGSEL_SHA512 - 64
 * @padbuf: pointer to buffer to store generated ipad/opad
 *
 * Split keys are IPAD/OPAD pairs. For details, refer to MDHA Split Keys chapter
 * in SEC Reference Manual.
 */

static inline void cnstr_jobdesc_mdsplitkey(uint32_t *descbuf,
					    unsigned *bufsize, bool ps,
					    uint64_t alg_key,
					    uint8_t keylen,
					    uint32_t cipher,
					    uint64_t padbuf)
{
	/* Sizes for MDHA pads (*not* keys) in bytes */
	static const uint8_t mdpadlen[] = {
		16,	/* MD5 */
		20,	/* SHA1 */
		32,	/* SHA224 */
		32,	/* SHA256 */
		64,	/* SHA384 */
		64	/* SHA512 */
	};
	uint32_t split_key_len, idx;
	struct program prg;
	struct program *program = &prg;

	idx = (cipher & OP_ALG_ALGSEL_SUBMASK) >> OP_ALG_ALGSEL_SHIFT;
	split_key_len = (uint32_t)(mdpadlen[idx] * 2);

	PROGRAM_CNTXT_INIT(descbuf, 0);
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	JOB_HDR(SHR_NEVER, 1, 0, 0);
	KEY(KEY2, 0, alg_key, keylen, 0);
	ALG_OPERATION(cipher,
		      OP_ALG_AAI_HMAC,
		      OP_ALG_AS_INIT,
		      ICV_CHECK_DISABLE,
		      OP_ALG_DECRYPT);
	FIFOLOAD(MSG2, 0, 0, LAST2 | IMMED | COPY);
	JUMP(1, LOCAL_JUMP, ALL_TRUE, CLASS2);
	FIFOSTORE(MDHA_SPLIT_KEY, 0, padbuf, split_key_len, 0);
	*bufsize = PROGRAM_FINALIZE();
}

#endif /* __DESC_JOBDESC_H__ */

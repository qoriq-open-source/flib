#include <stdio.h>
#include "flib/rta.h"

uint rta_sec_era;

int test_op_cipher(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int size;

	PROGRAM_CNTXT_INIT(buff, 0);
	{
/* RNG tests */
		ALG_OPERATION(OP_ALG_ALGSEL_RNG, OP_ALG_AAI_RNG, 0, 0, 0);
/* DESA family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_DES, OP_ALG_AAI_ECB, 0, 0,
			      OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_3DES, OP_ALG_AAI_CBC, 0, 0,
			      OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_3DES, OP_ALG_AAI_OFB, 0, 0,
			      OP_ALG_DECRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_DES, OP_ALG_AAI_CFB, 0, 0,
			      OP_ALG_DECRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_3DES, OP_ALG_AAI_OFB,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_CCM,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_ENCRYPT);
/* AESA family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_ECB, 0, 0,
			      OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_CBC, 0, 0,
			      OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_CBC,
			      OP_ALG_AS_INIT, 0, OP_ALG_DECRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_3DES, OP_ALG_AAI_CBC,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_AES, OP_ALG_AAI_CBC, 0, 0,
				OP_ALG_DECRYPT);
/* Kasumi family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_F8,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_GSM,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_DECRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_EDGE,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_DECRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_KASUMI, OP_ALG_AAI_F9,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_ENABLE,
			      OP_ALG_ENCRYPT);
/* SNOW 3G family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_SNOW_F8, OP_ALG_AAI_F8,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_SNOW_F9, OP_ALG_AAI_F9,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_ENABLE,
			      OP_ALG_ENCRYPT);
/* ARC4 family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_ARC4, 0, OP_ALG_AS_INIT, 0,
			      OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_ARC4, 0, OP_ALG_AS_INIT, 0, 0);
/* CRC family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_CRC,
			      WITH(OP_ALG_AAI_802 | OP_ALG_AAI_DIS |
				   OP_ALG_AAI_DOS | OP_ALG_AAI_DOC |
				   OP_ALG_AAI_IVZ), OP_ALG_AS_INITFINAL,
			      ICV_CHECK_ENABLE, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_CRC,
			      WITH(OP_ALG_AAI_3385 | OP_ALG_AAI_DIS |
				   OP_ALG_AAI_DOS | OP_ALG_AAI_DOC |
				   OP_ALG_AAI_IVZ), OP_ALG_AS_UPDATE,
			      ICV_CHECK_ENABLE, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_CRC,
			      WITH(OP_ALG_AAI_CUST_POLY | OP_ALG_AAI_DIS |
				   OP_ALG_AAI_DOS | OP_ALG_AAI_DOC |
				   OP_ALG_AAI_IVZ), OP_ALG_AS_INIT,
			      ICV_CHECK_ENABLE, OP_ALG_DECRYPT);
	}
	size = PROGRAM_FINALIZE();

	return size;
}

int test_op_alg_mdha(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int size;

	PROGRAM_CNTXT_INIT(buff, 0);
	{
/* MDHA family tests */
		ALG_OPERATION(OP_ALG_ALGSEL_MD5, OP_ALG_AAI_HASH,
			      OP_ALG_AS_INIT, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA1, OP_ALG_AAI_HASH,
			      OP_ALG_AS_UPDATE, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA224, OP_ALG_AAI_HASH,
			      OP_ALG_AS_FINALIZE, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA256, OP_ALG_AAI_HASH, 0, 0,
			      OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA384, OP_ALG_AAI_HASH,
			      OP_ALG_AS_INITFINAL, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA384, OP_ALG_AAI_HASH,
			      OP_ALG_AS_INITFINAL, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA512, OP_ALG_AAI_HASH,
			      OP_ALG_AS_INITFINAL, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_MD5, OP_ALG_AAI_SMAC,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_ENABLE, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA1, OP_ALG_AAI_SMAC,
			      OP_ALG_AS_UPDATE, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_MD5, OP_ALG_AAI_HMAC,
			      OP_ALG_AS_INIT, 0, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA1, OP_ALG_AAI_HMAC,
			      OP_ALG_AS_UPDATE, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA224, OP_ALG_AAI_HMAC,
			      OP_ALG_AS_FINALIZE, ICV_CHECK_ENABLE, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA256, OP_ALG_AAI_HMAC, 0, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA384, OP_ALG_AAI_HMAC,
			      OP_ALG_AS_INITFINAL, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA512, OP_ALG_AAI_HMAC,
			      OP_ALG_AS_INITFINAL, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_MD5, OP_ALG_AAI_HMAC_PRECOMP,
			      OP_ALG_AS_INIT, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA1, OP_ALG_AAI_HMAC_PRECOMP,
			      OP_ALG_AS_UPDATE, 0, OP_ALG_ENCRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA224, OP_ALG_AAI_HMAC_PRECOMP,
			      OP_ALG_AS_FINALIZE, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA256, OP_ALG_AAI_HMAC_PRECOMP, 0,
			      0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA384, OP_ALG_AAI_HMAC_PRECOMP,
			      OP_ALG_AS_INITFINAL, 0, 0);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA512, OP_ALG_AAI_HMAC_PRECOMP,
			      OP_ALG_AS_INITFINAL, 0, OP_ALG_DECRYPT);
		ALG_OPERATION(OP_ALG_ALGSEL_SHA384, OP_ALG_AAI_HMAC_PRECOMP,
			      OP_ALG_AS_INITFINAL, ICV_CHECK_ENABLE, 0);
	}
	size = PROGRAM_FINALIZE();

	return size;
}

int prg_buff[1000];

static void print_prog(uint32_t *buff, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%08X\n", buff[i]);
}

int main(int argc, char **argv)
{
	int size;

	rta_set_sec_era(1);

	printf("OPERATION ALGORITHM CIPHER program\n");
	size = test_op_cipher((uint32_t *) prg_buff);
	printf("size = %d\n", size);
	print_prog((uint32_t *) prg_buff, size);

	printf("OPERATION ALGORITHM MDHA program\n");
	size = test_op_alg_mdha((uint32_t *) prg_buff);
	printf("size = %d\n", size);
	print_prog((uint32_t *) prg_buff, size);

	return 0;
}

#include <stdio.h>
#include "flib/rta.h"

uint rta_sec_era;

int pointer_size_1(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int size;

	PROGRAM_CNTXT_INIT(buff, 0);
	JOB_HDR(SHR_NEVER, 200, WITH(SHR));
	{
		FIFOLOAD(PKN, PTR(0x4), 4, 0);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXPO);
	}
	size = PROGRAM_FINALIZE();
	return size;
}

int pointer_size_2(uint32_t *buff)
{
	struct program prg;
	struct program *program = &prg;
	int size;

	PROGRAM_CNTXT_INIT(buff, 0);
	PROGRAM_SET_36BIT_ADDR();

	JOB_HDR(SHR_NEVER, 200, WITH(SHR));
	{
		FIFOLOAD(PKN, PTR(0x4), 4, 0);
		PKHA_OPERATION(OP_ALG_PKMODE_MOD_EXPO);
	}
	size = PROGRAM_FINALIZE();
	return size;
}

int prg_buff[1000];

static void print_prog(uint32_t *buff, int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%08x\n", buff[i]);
}

int main(int argc, char **argv)
{
	int size;

	rta_set_sec_era(1);

	printf("POINTER_SIZE_1 example program\n");
	size = pointer_size_1((uint32_t *) prg_buff);
	printf("size = %d\n", size);
	print_prog((uint32_t *) prg_buff, size);

	printf("POINTER_SIZE_2 example program\n");
	size = pointer_size_2((uint32_t *) prg_buff);
	printf("size = %d\n", size);
	print_prog((uint32_t *) prg_buff, size);

	return 0;
}

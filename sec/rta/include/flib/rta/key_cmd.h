/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __RTA_KEY_CMD_H__
#define __RTA_KEY_CMD_H__

extern enum rta_sec_era rta_sec_era;

/* Allowed encryption flags for each SEC Era */
static const uint32_t key_enc_flags[] = {
	ENC,
	ENC | NWB | EKT | TK,
	ENC | NWB | EKT | TK,
	ENC | NWB | EKT | TK,
	ENC | NWB | EKT | TK,
	ENC | NWB | EKT | TK,
	ENC | NWB | EKT | TK | PTS,
	ENC | NWB | EKT | TK | PTS
};

static inline unsigned rta_key(struct program *program, uint32_t key_dst,
			       int key_type, uint32_t encrypt_flags,
			       uint64_t src, int src_type, uint32_t length,
			       uint32_t flags)
{
	uint32_t opcode = 0, is_seq_cmd = 0;
	unsigned start_pc = program->current_pc;

	if (key_type != REG_TYPE) {
		pr_debug("KEY: Incorrect key type. SEC PC: %d; Instr: %d\n",
			 program->current_pc, program->current_instruction);
		goto err;
	}

	if (encrypt_flags & ~key_enc_flags[rta_sec_era]) {
		pr_debug("KEY: Flag(s) not supported by SEC Era %d\n",
			 USER_SEC_ERA(rta_sec_era));
		goto err;
	}

	/* write cmd type */
	if (flags & SEQ) {
		opcode = CMD_SEQ_KEY;
		is_seq_cmd = 1;
	} else {
		opcode = CMD_KEY;
	}

	if (src_type == IMM_DATA)
		flags |= IMMED;

	/* check parameters */
	if (is_seq_cmd) {
		if ((flags & IMMED) || (flags & SGF)) {
			pr_debug("SEQKEY: Invalid flag. SEC PC: %d; Instr: %d\n",
				 program->current_pc,
				 program->current_instruction);
			goto err;
		}
		if ((rta_sec_era <= RTA_SEC_ERA_5) &&
		    ((flags & VLF) || (flags & AIDF))) {
			pr_debug("SEQKEY: Flag(s) not supported by SEC Era %d\n",
				 USER_SEC_ERA(rta_sec_era));
			goto err;
		}
	} else {
		if ((flags & AIDF) || (flags & VLF)) {
			pr_debug("KEY: Invalid flag. SEC PC: %d; Instr: %d\n",
				 program->current_pc,
				 program->current_instruction);
			goto err;
		}
		if ((flags & SGF) && (flags & IMMED)) {
			pr_debug("KEY: Invalid flag. SEC PC: %d; Instr: %d\n",
				 program->current_pc,
				 program->current_instruction);
			goto err;
		}
	}

	if ((encrypt_flags & PTS) &&
	    ((encrypt_flags & ENC) || (encrypt_flags & NWB) ||
	     (key_dst == _PKE))) {
		pr_debug("KEY: Invalid flag / destination. SEC PC: %d; Instr: %d\n",
			 program->current_pc,
			 program->current_instruction);
		goto err;
	}

	if (key_dst == _AFHA_SBOX) {
		if (rta_sec_era == RTA_SEC_ERA_7) {
			pr_debug("KEY: AFHA S-box not supported by SEC Era %d\n",
				 USER_SEC_ERA(rta_sec_era));
			goto err;
		}

		if (flags & IMMED) {
			pr_debug("KEY: Invalid flag. SEC PC: %d; Instr: %d\n",
				 program->current_pc,
				 program->current_instruction);
			goto err;
		}

		/*
		 * Sbox data loaded into the ARC-4 processor must be exactly
		 * 258 bytes long, or else a data sequence error is generated.
		 */
		if (length != 258) {
			pr_debug("KEY: Invalid length. SEC PC: %d; Instr: %d\n",
				 program->current_pc,
				 program->current_instruction);
			goto err;
		}
	}

	/* write key destination and class fields */
	switch (key_dst) {
	case (_KEY1):
		opcode |= KEY_DEST_CLASS1;
		break;
	case (_KEY2):
		opcode |= KEY_DEST_CLASS2;
		break;
	case (_PKE):
		opcode |= KEY_DEST_CLASS1 | KEY_DEST_PKHA_E;
		break;
	case (_AFHA_SBOX):
		opcode |= KEY_DEST_CLASS1 | KEY_DEST_AFHA_SBOX;
		break;
	case (_MDHA_SPLIT_KEY):
		opcode |= KEY_DEST_CLASS2 | KEY_DEST_MDHA_SPLIT;
		break;
	default:
		pr_debug("KEY: Invalid destination. SEC PC: %d; Instr: %d\n",
			 program->current_pc, program->current_instruction);
		goto err;
		break;
	}

	/* write key length */
	length &= KEY_LENGTH_MASK;
	opcode |= length;

	/* write key command specific flags */
	if (encrypt_flags & ENC) {
		/* Encrypted (black) keys must be padded to 8 bytes (CCM) or
		   16 bytes (ECB) depending on EKT bit. AES-CCM encrypted keys
		   (EKT = 1) have 6-byte nonce and 6-byte MAC after padding.
		 */
		opcode |= KEY_ENC;
		if (encrypt_flags & EKT) {
			opcode |= KEY_EKT;
			length = ALIGN(length, 8);
			length += 12;
		} else {
			length = ALIGN(length, 16);
		}
		if (encrypt_flags & TK)
			opcode |= KEY_TK;
	}
	if (encrypt_flags & NWB)
		opcode |= KEY_NWB;
	if (encrypt_flags & PTS)
		opcode |= KEY_PTS;

	/* write general command flags */
	if (!is_seq_cmd) {
		if (flags & IMMED)
			opcode |= KEY_IMM;
		if (flags & SGF)
			opcode |= KEY_SGF;
	} else {
		if (flags & AIDF)
			opcode |= KEY_AIDF;
		if (flags & VLF)
			opcode |= KEY_VLF;
	}

	__rta_out32(program, opcode);
	program->current_instruction++;

	if (flags & IMMED)
		__rta_inline_data(program, src, src_type, length);
	else
		__rta_out64(program, program->ps, src);

	return start_pc;

 err:
	program->first_error_pc = start_pc;
	program->current_instruction++;
	return start_pc;
}

#endif /* __RTA_KEY_CMD_H__ */

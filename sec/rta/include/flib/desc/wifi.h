/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __DESC_WIFI_H__
#define __DESC_WIFI_H__

#include "flib/rta.h"
#include "common.h"

/**
 * DOC: WiFi Shared Descriptor Constructors
 *
 * Shared descriptors for WiFi (802.11i) protocol.
 */

/*
 * IEEE 802.11 WiFi Protocol Data Block
 */
#define WIFI_PDBOPTS_FCS	0x01
#define WIFI_PDBOPTS_AR		0x40

/**
 * WIFI_B0_FLAGS - The value of B0 flags used for WiFi AES-CCM Context
 *                 construction.
 */
#define WIFI_B0_FLAGS			0x59

/**
 * WIFI_FRM_CTRL_MASK - The Frame Control Mask value used in computing the
 *                      additional authentication data (AAD).
 */
#define WIFI_FRM_CTRL_MASK		0x8fc7

/**
 * WIFI_SEQ_CTRL_MASK - The Sequence Control Mask value used in computing the
 *                      additional authentication data (AAD).
 */
#define WIFI_SEQ_CTRL_MASK		0x0f00

/**
 * WIFI_CTR_FLAGS - The value of Counter Flags used for CCM Counter block
 *                  construction.
 */
#define WIFI_CTR_FLAGS			0x01

struct wifi_encap_pdb {
	uint16_t mac_hdr_len;	/* MAC Header Length - 24 or 30 bytes */
	uint8_t rsvd;		/* Reserver bits */
	uint8_t options;	/* Options byte */
	uint8_t b0_flags;	/* CCM B0 block flags */
	uint8_t pri;		/* Frame Priority */
	uint16_t pn1;		/* Packet Number MS 16 bits */
	uint32_t pn2;		/* Packet Number LS 32 bits */
	uint16_t frm_ctrl_mask; /* Frame Control mask */
	uint16_t seq_ctrl_mask; /* Sequence Control mask */
	uint16_t rsvd1;	    /* Reserved bits */
	uint8_t cnst;		/* CCM Counter block constant - 0x0000 */
	uint8_t key_id;		/* Key ID*/
	uint8_t ctr_flags;	/* CCM Counter block flags */
	uint8_t rsvd2;		/* Reserved bits */
	uint16_t ctr_init;	/* CCM Counter block init counter */
};

struct wifi_decap_pdb {
	uint16_t mac_hdr_len;	/* MAC Header Length - 24 or 30 bytes */
	uint8_t rsvd;		/* Reserver bits */
	uint8_t options;	/* Options byte */
	uint8_t b0_flags;	/* CCM B0 block flags */
	uint8_t pri;		/* Frame Priority */
	uint16_t pn1;		/* Packet Number MS 16 bits */
	uint32_t pn2;		/* Packet Number LS 32 bits */
	uint16_t frm_ctrl_mask; /* Frame Control mask */
	uint16_t seq_ctrl_mask; /* Sequence Control mask */
	uint32_t rsvd1;	    /* Reserved bits */
	uint8_t ctr_flags;	/* CCM Counter block flags */
	uint8_t rsvd2;		/* Reserved bits */
	uint16_t ctr_init;	/* CCM Counter block init counter */
};

/**
 * cnstr_shdsc_wifi_encap - IEEE 802.11i WiFi encapsulation
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: pointer to descriptor size, updated at completion
 * @ps: if 36/40bit addressing is desired, this parameter must be true
 * @mac_hdr_len: PDB MAC header length (24 or 28 bytes)
 * @pn: PDB Packet Number
 * @priority: PDB Packet priority
 * @key_id: PDB Key ID
 * @cipherdata: block cipher transform definitions
 */
static inline void cnstr_shdsc_wifi_encap(uint32_t *descbuf, unsigned *bufsize,
		bool ps, uint16_t mac_hdr_len, uint64_t pn, uint8_t priority,
		uint8_t key_id, struct alginfo *cipherdata)
{
	struct program prg;
	struct program *program = &prg;
	struct wifi_encap_pdb pdb;

	LABEL(pdbend);
	REFERENCE(phdr);
	LABEL(keyjump);
	REFERENCE(pkeyjump);
	LABEL(startloop);
	REFERENCE(pstartloop);

	memset(&pdb, 0, sizeof(struct wifi_encap_pdb));
	pdb.mac_hdr_len = mac_hdr_len;
	pdb.b0_flags = WIFI_B0_FLAGS;
	pdb.pri = priority;
	pdb.pn1 = (uint16_t)upper_32_bits(pn);
	pdb.pn2 = lower_32_bits(pn);
	pdb.frm_ctrl_mask = WIFI_FRM_CTRL_MASK;
	pdb.seq_ctrl_mask = WIFI_SEQ_CTRL_MASK;
	pdb.key_id = key_id;
	pdb.ctr_flags = WIFI_CTR_FLAGS;

	PROGRAM_CNTXT_INIT(descbuf, 0);
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	phdr = SHR_HDR(SHR_SERIAL, pdbend, SC);
	COPY_DATA((uint8_t *)&pdb, sizeof(struct wifi_encap_pdb));
	SET_LABEL(pdbend);
	pkeyjump = JUMP(keyjump, LOCAL_JUMP, ALL_TRUE, SHRD | SELF);
	KEY(KEY1, cipherdata->key_enc_flags, cipherdata->key,
	    cipherdata->keylen, IMMED | COPY);
	SET_LABEL(keyjump);
	PROTOCOL(OP_TYPE_ENCAP_PROTOCOL, OP_PCLID_WIFI, OP_PCL_WIFI);

	/* Errata A-005487: PN is written in reverse order in CCM Header. */
	if (rta_sec_era <= RTA_SEC_ERA_5) {
		/*
		 * Copy MAC Header len in MATH2 and (Const + KeyID) in MATH3
		 * to be used later in CCMP header reconstruction.
		 */
		MATHB(ZERO, AND, MATH3, MATH3, 8, IFB|NFU);
		MOVE(DESCBUF, 0, MATH2, 0, 6, IMMED);
		MOVE(DESCBUF, 20, MATH3, 0, 4, IMMED);

		/*
		 * Protocol operation leaves in MATH0 the incremented PN as
		 * xx xx PN0 PN1 PN2 PN3 PN4 PN5. Before byte-reversing the
		 * MATH0, first the PN is decremented and transformed as
		 * PN0 PN1 PN2 PN3 00 00 PN4 PN5.
		 */
		MATHB(MATH0, SUB, ONE, MATH0, 8, IFB|NFU);
		MATHB(ZERO, ADD, MATH0, MATH1, 2, IFB|NFU);
		MATHB(MATH0, XOR, MATH1, MATH0, 8, IFB|NFU);
		MATHB(MATH0, LSHIFT, 16, MATH0, 8, IFB|NFU|IMMED2);
		MATHB(MATH1, OR, MATH0, MATH0, 8, IFB|NFU);

		/*
		 * Prepare to byte-reverse MATH0: copy MATH0 input into Input
		 * DATA FIFO and place loop value (8) into MATH1.
		 */
		LOAD(0, DCTRL, LDOFF_DISABLE_AUTO_NFIFO, 0, IMMED);
		MOVE(MATH0, 0, IFIFOAB1, 0, 8, IMMED);
		LOAD(0, DCTRL, LDOFF_ENABLE_AUTO_NFIFO, 0, IMMED);

		MOVE(IFIFOABD, 0, MATH0, 0, 1, IMMED);
		MATHB(ZERO, ADD, 8, MATH1, 4, IFB|NFU|IMMED2);
		MATHB(MATH1, SUB, ONE, VSEQINSZ, 4, IFB|NFU);

		/*
		 * loop to reverse MATH0 content from PN0 PN1 PN2 PN3 00 00
		 * PN4 PN5 --> PN5 PN4 00 00 PN3 PN2 PN1 PN0; during n-th
		 * iteration, right shift MATH0 with 8 bytes and copy into
		 * MATH0 at offset 0 the n-th byte from Input Data FIFO.
		 */
		SET_LABEL(startloop);
		MATHB(VSEQINSZ, SUB, ONE, VSEQINSZ, 4, IFB);
		MATHB(MATH0, RSHIFT, MATH1, MATH0, 8, IFB|NFU);
		MOVE(IFIFOABD, 0, MATH0, 0, 1, IMMED);
		JUMP(1, LOCAL_JUMP, ALL_TRUE, 0);
		pstartloop = JUMP(startloop, LOCAL_JUMP, ALL_FALSE, MATH_Z);

		/*
		 * Prepare to write the correct CCMP header to output frame.
		 * Copy MAC Header Len into VSOL and complete CCMP header in
		 * MATH3 with Const + keyID.
		 */
		MATHB(MATH2, RSHIFT, 16, VSEQOUTSZ, 2, IFB|NFU|IMMED2);
		MATHB(MATH0, OR, MATH3, MATH3, 8, IFB|NFU);

		/*
		 * write the correct CCMP header from MATH3 to output frame.
		 * set length for Ouput Sequence operation at 48B, larger than
		 * largest MAC header length(30) + CCMP header length(8)
		 */
		SEQOUTPTR(0, 48, RTO);
		SEQFIFOSTORE(SKIP, 0, 0, VLF);
		SEQSTORE(MATH3, 0, 8, 0);

		PATCH_JUMP(pstartloop, startloop);
	}
	PATCH_HDR(phdr, pdbend);
	PATCH_JUMP(pkeyjump, keyjump);

	*bufsize = PROGRAM_FINALIZE();
}

/**
 * cnstr_shdsc_wifi_decap - IEEE 802.11 WiFi decapsulation
 * @descbuf: pointer to descriptor-under-construction buffer
 * @bufsize: pointer to descriptor size, updated at completion
 * @ps: if 36/40bit addressing is desired, this parameter must be true
 * @mac_hdr_len: PDB MAC header length (24 or 28 bytes)
 * @pn: PDB Packet Number
 * @priority: PDB Packet priority
 * @cipherdata: block cipher transform definitions
 **/
static inline void cnstr_shdsc_wifi_decap(uint32_t *descbuf, unsigned *bufsize,
		bool ps, uint16_t mac_hdr_len, uint64_t pn, uint8_t priority,
		struct alginfo *cipherdata)
{
	struct program prg;
	struct program *program = &prg;
	struct wifi_decap_pdb pdb;

	LABEL(phdr);
	REFERENCE(pdbend);
	LABEL(keyjump);
	REFERENCE(pkeyjump);

	memset(&pdb, 0x00, sizeof(struct wifi_encap_pdb));
	pdb.mac_hdr_len = mac_hdr_len;
	pdb.b0_flags = WIFI_B0_FLAGS;
	pdb.pri = priority;
	pdb.pn1 = (uint16_t)upper_32_bits(pn);
	pdb.pn2 = lower_32_bits(pn);
	pdb.frm_ctrl_mask = WIFI_FRM_CTRL_MASK;
	pdb.seq_ctrl_mask = WIFI_SEQ_CTRL_MASK;
	pdb.ctr_flags = WIFI_CTR_FLAGS;

	PROGRAM_CNTXT_INIT(descbuf, 0);
	if (ps)
		PROGRAM_SET_36BIT_ADDR();
	phdr = SHR_HDR(SHR_SERIAL, pdbend, SC);
	COPY_DATA((uint8_t *)&pdb, sizeof(struct wifi_decap_pdb));
	SET_LABEL(pdbend);
	pkeyjump = JUMP(keyjump, LOCAL_JUMP, ALL_TRUE, SHRD | SELF);
	KEY(KEY1, cipherdata->key_enc_flags, cipherdata->key,
	    cipherdata->keylen, IMMED | COPY);
	SET_LABEL(keyjump);
	PROTOCOL(OP_TYPE_DECAP_PROTOCOL, OP_PCLID_WIFI, OP_PCL_WIFI);

	PATCH_HDR(phdr, pdbend);
	PATCH_JUMP(pkeyjump, keyjump);
	*bufsize = PROGRAM_FINALIZE();
}

#endif /* __DESC_WIFI_H__ */

/* Copyright 2008-2013 Freescale Semiconductor, Inc. */

#ifndef __RTA_PROTOCOL_CMD_H__
#define __RTA_PROTOCOL_CMD_H__

extern enum rta_sec_era rta_sec_era;

static inline int __rta_ssl_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_SSL30_RC4_40_MD5_2:
	case OP_PCL_SSL30_RC4_128_MD5_2:
	case OP_PCL_SSL30_RC4_128_SHA_5:
	case OP_PCL_SSL30_RC4_40_MD5_3:
	case OP_PCL_SSL30_RC4_128_MD5_3:
	case OP_PCL_SSL30_RC4_128_SHA:
	case OP_PCL_SSL30_RC4_128_MD5:
	case OP_PCL_SSL30_RC4_40_SHA:
	case OP_PCL_SSL30_RC4_40_MD5:
	case OP_PCL_SSL30_RC4_128_SHA_2:
	case OP_PCL_SSL30_RC4_128_SHA_3:
	case OP_PCL_SSL30_RC4_128_SHA_4:
	case OP_PCL_SSL30_RC4_128_SHA_6:
	case OP_PCL_SSL30_RC4_128_SHA_7:
	case OP_PCL_SSL30_RC4_128_SHA_8:
	case OP_PCL_SSL30_RC4_128_SHA_9:
	case OP_PCL_SSL30_RC4_128_SHA_10:
	case OP_PCL_TLS_ECDHE_PSK_RC4_128_SHA:
		if (rta_sec_era == RTA_SEC_ERA_7)
			return -1;
		/* fall through if not Era 7 */
	case OP_PCL_SSL30_DES40_CBC_SHA:
	case OP_PCL_SSL30_DES_CBC_SHA_2:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_5:
	case OP_PCL_SSL30_DES40_CBC_SHA_2:
	case OP_PCL_SSL30_DES_CBC_SHA_3:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_6:
	case OP_PCL_SSL30_DES40_CBC_SHA_3:
	case OP_PCL_SSL30_DES_CBC_SHA_4:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_7:
	case OP_PCL_SSL30_DES40_CBC_SHA_4:
	case OP_PCL_SSL30_DES_CBC_SHA_5:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_8:
	case OP_PCL_SSL30_DES40_CBC_SHA_5:
	case OP_PCL_SSL30_DES_CBC_SHA_6:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_9:
	case OP_PCL_SSL30_DES40_CBC_SHA_6:
	case OP_PCL_SSL30_DES_CBC_SHA_7:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_10:
	case OP_PCL_SSL30_DES_CBC_SHA:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA:
	case OP_PCL_SSL30_DES_CBC_MD5:
	case OP_PCL_SSL30_3DES_EDE_CBC_MD5:
	case OP_PCL_SSL30_DES40_CBC_SHA_7:
	case OP_PCL_SSL30_DES40_CBC_MD5:
	case OP_PCL_SSL30_AES_128_CBC_SHA:
	case OP_PCL_SSL30_AES_128_CBC_SHA_2:
	case OP_PCL_SSL30_AES_128_CBC_SHA_3:
	case OP_PCL_SSL30_AES_128_CBC_SHA_4:
	case OP_PCL_SSL30_AES_128_CBC_SHA_5:
	case OP_PCL_SSL30_AES_128_CBC_SHA_6:
	case OP_PCL_SSL30_AES_256_CBC_SHA:
	case OP_PCL_SSL30_AES_256_CBC_SHA_2:
	case OP_PCL_SSL30_AES_256_CBC_SHA_3:
	case OP_PCL_SSL30_AES_256_CBC_SHA_4:
	case OP_PCL_SSL30_AES_256_CBC_SHA_5:
	case OP_PCL_SSL30_AES_256_CBC_SHA_6:
	case OP_PCL_TLS12_AES_128_CBC_SHA256_2:
	case OP_PCL_TLS12_AES_128_CBC_SHA256_3:
	case OP_PCL_TLS12_AES_128_CBC_SHA256_4:
	case OP_PCL_TLS12_AES_128_CBC_SHA256_5:
	case OP_PCL_TLS12_AES_256_CBC_SHA256_2:
	case OP_PCL_TLS12_AES_256_CBC_SHA256_3:
	case OP_PCL_TLS12_AES_256_CBC_SHA256_4:
	case OP_PCL_TLS12_AES_256_CBC_SHA256_5:
	case OP_PCL_TLS12_AES_128_CBC_SHA256_6:
	case OP_PCL_TLS12_AES_256_CBC_SHA256_6:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_2:
	case OP_PCL_SSL30_AES_128_CBC_SHA_7:
	case OP_PCL_SSL30_AES_256_CBC_SHA_7:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_3:
	case OP_PCL_SSL30_AES_128_CBC_SHA_8:
	case OP_PCL_SSL30_AES_256_CBC_SHA_8:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_4:
	case OP_PCL_SSL30_AES_128_CBC_SHA_9:
	case OP_PCL_SSL30_AES_256_CBC_SHA_9:
	case OP_PCL_SSL30_AES_128_GCM_SHA256_1:
	case OP_PCL_SSL30_AES_256_GCM_SHA384_1:
	case OP_PCL_SSL30_AES_128_GCM_SHA256_2:
	case OP_PCL_SSL30_AES_256_GCM_SHA384_2:
	case OP_PCL_SSL30_AES_128_GCM_SHA256_3:
	case OP_PCL_SSL30_AES_256_GCM_SHA384_3:
	case OP_PCL_SSL30_AES_128_GCM_SHA256_4:
	case OP_PCL_SSL30_AES_256_GCM_SHA384_4:
	case OP_PCL_SSL30_AES_128_GCM_SHA256_5:
	case OP_PCL_SSL30_AES_256_GCM_SHA384_5:
	case OP_PCL_SSL30_AES_128_GCM_SHA256_6:
	case OP_PCL_TLS_DH_ANON_AES_256_GCM_SHA384:
	case OP_PCL_TLS_PSK_AES_128_GCM_SHA256:
	case OP_PCL_TLS_PSK_AES_256_GCM_SHA384:
	case OP_PCL_TLS_DHE_PSK_AES_128_GCM_SHA256:
	case OP_PCL_TLS_DHE_PSK_AES_256_GCM_SHA384:
	case OP_PCL_TLS_RSA_PSK_AES_128_GCM_SHA256:
	case OP_PCL_TLS_RSA_PSK_AES_256_GCM_SHA384:
	case OP_PCL_TLS_PSK_AES_128_CBC_SHA256:
	case OP_PCL_TLS_PSK_AES_256_CBC_SHA384:
	case OP_PCL_TLS_DHE_PSK_AES_128_CBC_SHA256:
	case OP_PCL_TLS_DHE_PSK_AES_256_CBC_SHA384:
	case OP_PCL_TLS_RSA_PSK_AES_128_CBC_SHA256:
	case OP_PCL_TLS_RSA_PSK_AES_256_CBC_SHA384:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_11:
	case OP_PCL_SSL30_AES_128_CBC_SHA_10:
	case OP_PCL_SSL30_AES_256_CBC_SHA_10:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_12:
	case OP_PCL_SSL30_AES_128_CBC_SHA_11:
	case OP_PCL_SSL30_AES_256_CBC_SHA_11:
	case OP_PCL_SSL30_AES_128_CBC_SHA_12:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_13:
	case OP_PCL_SSL30_AES_256_CBC_SHA_12:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_14:
	case OP_PCL_SSL30_AES_128_CBC_SHA_13:
	case OP_PCL_SSL30_AES_256_CBC_SHA_13:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_15:
	case OP_PCL_SSL30_AES_128_CBC_SHA_14:
	case OP_PCL_SSL30_AES_256_CBC_SHA_14:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_16:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_17:
	case OP_PCL_SSL30_3DES_EDE_CBC_SHA_18:
	case OP_PCL_SSL30_AES_128_CBC_SHA_15:
	case OP_PCL_SSL30_AES_128_CBC_SHA_16:
	case OP_PCL_SSL30_AES_128_CBC_SHA_17:
	case OP_PCL_SSL30_AES_256_CBC_SHA_15:
	case OP_PCL_SSL30_AES_256_CBC_SHA_16:
	case OP_PCL_SSL30_AES_256_CBC_SHA_17:
	case OP_PCL_TLS_ECDHE_ECDSA_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDHE_ECDSA_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDH_ECDSA_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDH_ECDSA_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDHE_RSA_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDHE_RSA_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDH_RSA_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDH_RSA_AES_256_CBC_SHA384:
	case OP_PCL_TLS_ECDHE_ECDSA_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDHE_ECDSA_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDH_ECDSA_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDH_ECDSA_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDHE_RSA_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDHE_RSA_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDH_RSA_AES_128_GCM_SHA256:
	case OP_PCL_TLS_ECDH_RSA_AES_256_GCM_SHA384:
	case OP_PCL_TLS_ECDHE_PSK_3DES_EDE_CBC_SHA:
	case OP_PCL_TLS_ECDHE_PSK_AES_128_CBC_SHA:
	case OP_PCL_TLS_ECDHE_PSK_AES_256_CBC_SHA:
	case OP_PCL_TLS_ECDHE_PSK_AES_128_CBC_SHA256:
	case OP_PCL_TLS_ECDHE_PSK_AES_256_CBC_SHA384:
	case OP_PCL_TLS12_3DES_EDE_CBC_MD5:
	case OP_PCL_TLS12_3DES_EDE_CBC_SHA160:
	case OP_PCL_TLS12_3DES_EDE_CBC_SHA224:
	case OP_PCL_TLS12_3DES_EDE_CBC_SHA256:
	case OP_PCL_TLS12_3DES_EDE_CBC_SHA384:
	case OP_PCL_TLS12_3DES_EDE_CBC_SHA512:
	case OP_PCL_TLS12_AES_128_CBC_SHA160:
	case OP_PCL_TLS12_AES_128_CBC_SHA224:
	case OP_PCL_TLS12_AES_128_CBC_SHA256:
	case OP_PCL_TLS12_AES_128_CBC_SHA384:
	case OP_PCL_TLS12_AES_128_CBC_SHA512:
	case OP_PCL_TLS12_AES_192_CBC_SHA160:
	case OP_PCL_TLS12_AES_192_CBC_SHA224:
	case OP_PCL_TLS12_AES_192_CBC_SHA256:
	case OP_PCL_TLS12_AES_192_CBC_SHA512:
	case OP_PCL_TLS12_AES_256_CBC_SHA160:
	case OP_PCL_TLS12_AES_256_CBC_SHA224:
	case OP_PCL_TLS12_AES_256_CBC_SHA256:
	case OP_PCL_TLS12_AES_256_CBC_SHA384:
	case OP_PCL_TLS12_AES_256_CBC_SHA512:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA160:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA384:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA224:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA512:
	case OP_PCL_TLS_PVT_AES_192_CBC_SHA256:
	case OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FE:
	case OP_PCL_TLS_PVT_MASTER_SECRET_PRF_FF:
		return 0;
	}

	return -1;
}

static inline int __rta_ike_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_IKE_HMAC_MD5:
	case OP_PCL_IKE_HMAC_SHA1:
	case OP_PCL_IKE_HMAC_AES128_CBC:
	case OP_PCL_IKE_HMAC_SHA256:
	case OP_PCL_IKE_HMAC_SHA384:
	case OP_PCL_IKE_HMAC_SHA512:
	case OP_PCL_IKE_HMAC_AES128_CMAC:
		return 0;
	}

	return -1;
}

static inline int __rta_ipsec_proto(uint16_t protoinfo)
{
	uint16_t proto_cls1 = protoinfo & OP_PCL_IPSEC_CIPHER_MASK;
	uint16_t proto_cls2 = protoinfo & OP_PCL_IPSEC_AUTH_MASK;

	switch (proto_cls1) {
	case OP_PCL_IPSEC_NULL:
	case OP_PCL_IPSEC_AES_NULL_WITH_GMAC:
		if (rta_sec_era < RTA_SEC_ERA_2)
			return -1;
		break;
	case OP_PCL_IPSEC_AES_CCM8:
	case OP_PCL_IPSEC_AES_CCM12:
	case OP_PCL_IPSEC_AES_CCM16:
	case OP_PCL_IPSEC_AES_GCM8:
	case OP_PCL_IPSEC_AES_GCM12:
		if (proto_cls2 == OP_PCL_IPSEC_HMAC_NULL)
			return 0;
		/* no break */
	case OP_PCL_IPSEC_DES_IV64:
	case OP_PCL_IPSEC_DES:
	case OP_PCL_IPSEC_3DES:
	case OP_PCL_IPSEC_AES_CBC:
	case OP_PCL_IPSEC_AES_CTR:
		break;
	default:
		return -1;
	}

	switch (proto_cls2) {
	case OP_PCL_IPSEC_HMAC_MD5_96:
	case OP_PCL_IPSEC_HMAC_SHA1_96:
	case OP_PCL_IPSEC_AES_XCBC_MAC_96:
	case OP_PCL_IPSEC_HMAC_MD5_128:
	case OP_PCL_IPSEC_HMAC_SHA1_160:
	case OP_PCL_IPSEC_AES_CMAC_96:
	case OP_PCL_IPSEC_HMAC_SHA2_256_128:
	case OP_PCL_IPSEC_HMAC_SHA2_384_192:
	case OP_PCL_IPSEC_HMAC_SHA2_512_256:
		return 0;
	}

	return -1;
}

static inline int __rta_srtp_proto(uint16_t protoinfo)
{
	uint16_t proto_cls1 = protoinfo & OP_PCL_SRTP_CIPHER_MASK;
	uint16_t proto_cls2 = protoinfo & OP_PCL_SRTP_AUTH_MASK;

	switch (proto_cls1) {
	case OP_PCL_SRTP_AES_CTR:
		switch (proto_cls2) {
		case OP_PCL_SRTP_HMAC_SHA1_160:
			return 0;
		}
		/* no break */
	}

	return -1;
}

static inline int __rta_macsec_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_MACSEC:
		return 0;
	}

	return -1;
}

static inline int __rta_wifi_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_WIFI:
		return 0;
	}

	return -1;
}

static inline int __rta_wimax_proto(uint16_t protoinfo)
{
	switch (protoinfo) {
	case OP_PCL_WIMAX_OFDM:
	case OP_PCL_WIMAX_OFDMA:
		return 0;
	}

	return -1;
}

/* Allowed blob proto flags for each SEC Era */
static const uint32_t proto_blob_flags[] = {
	OP_PCL_BLOB_FORMAT_MASK | OP_PCL_BLOB_BLACK,
	OP_PCL_BLOB_FORMAT_MASK | OP_PCL_BLOB_BLACK | OP_PCL_BLOB_TKEK |
		OP_PCL_BLOB_EKT | OP_PCL_BLOB_REG_MASK,
	OP_PCL_BLOB_FORMAT_MASK | OP_PCL_BLOB_BLACK | OP_PCL_BLOB_TKEK |
		OP_PCL_BLOB_EKT | OP_PCL_BLOB_REG_MASK,
	OP_PCL_BLOB_FORMAT_MASK | OP_PCL_BLOB_BLACK | OP_PCL_BLOB_TKEK |
		OP_PCL_BLOB_EKT | OP_PCL_BLOB_REG_MASK | OP_PCL_BLOB_SEC_MEM,
	OP_PCL_BLOB_FORMAT_MASK | OP_PCL_BLOB_BLACK | OP_PCL_BLOB_TKEK |
		OP_PCL_BLOB_EKT | OP_PCL_BLOB_REG_MASK | OP_PCL_BLOB_SEC_MEM
};

static inline int __rta_blob_proto(uint16_t protoinfo)
{
	if (protoinfo & ~proto_blob_flags[rta_sec_era])
		return -1;

	switch (protoinfo & OP_PCL_BLOB_FORMAT_MASK) {
	case OP_PCL_BLOB_FORMAT_NORMAL:
	case OP_PCL_BLOB_FORMAT_MASTER_VER:
	case OP_PCL_BLOB_FORMAT_TEST:
		break;
	default:
		return -1;
	}

	switch (protoinfo & OP_PCL_BLOB_REG_MASK) {
	case OP_PCL_BLOB_AFHA_SBOX:
		if (rta_sec_era < RTA_SEC_ERA_3)
			return -1;
		/* no break */
	case OP_PCL_BLOB_REG_MEMORY:
	case OP_PCL_BLOB_REG_KEY1:
	case OP_PCL_BLOB_REG_KEY2:
	case OP_PCL_BLOB_REG_SPLIT:
	case OP_PCL_BLOB_REG_PKE:
		return 0;
	}

	return -1;
}

static inline int __rta_dlc_proto(uint16_t protoinfo)
{
	if ((rta_sec_era < RTA_SEC_ERA_2) &&
	    (protoinfo & (OP_PCL_PKPROT_DSA_MSG | OP_PCL_PKPROT_HASH_MASK |
	     OP_PCL_PKPROT_EKT_Z | OP_PCL_PKPROT_DECRYPT_Z |
	     OP_PCL_PKPROT_DECRYPT_PRI)))
		return -1;

	switch (protoinfo & OP_PCL_PKPROT_HASH_MASK) {
	case OP_PCL_PKPROT_HASH_MD5:
	case OP_PCL_PKPROT_HASH_SHA1:
	case OP_PCL_PKPROT_HASH_SHA224:
	case OP_PCL_PKPROT_HASH_SHA256:
	case OP_PCL_PKPROT_HASH_SHA384:
	case OP_PCL_PKPROT_HASH_SHA512:
		break;
	default:
		return -1;
	}

	return 0;
}

static inline int __rta_rsa_enc_proto(uint16_t protoinfo)
{
	switch (protoinfo & OP_PCL_RSAPROT_OP_MASK) {
	case OP_PCL_RSAPROT_OP_ENC_F_IN:
		if ((protoinfo & OP_PCL_RSAPROT_FFF_MASK) !=
		    OP_PCL_RSAPROT_FFF_RED)
			return -1;
		break;
	case OP_PCL_RSAPROT_OP_ENC_F_OUT:
		switch (protoinfo & OP_PCL_RSAPROT_FFF_MASK) {
		case OP_PCL_RSAPROT_FFF_RED:
		case OP_PCL_RSAPROT_FFF_ENC:
		case OP_PCL_RSAPROT_FFF_EKT:
		case OP_PCL_RSAPROT_FFF_TK_ENC:
		case OP_PCL_RSAPROT_FFF_TK_EKT:
			break;
		default:
			return -1;
		}
		break;
	default:
		return -1;
	}

	return 0;
}

static inline int __rta_rsa_dec_proto(uint16_t protoinfo)
{
	switch (protoinfo & OP_PCL_RSAPROT_OP_MASK) {
	case OP_PCL_RSAPROT_OP_DEC_ND:
	case OP_PCL_RSAPROT_OP_DEC_PQD:
	case OP_PCL_RSAPROT_OP_DEC_PQDPDQC:
		break;
	default:
		return -1;
	}

	switch (protoinfo & OP_PCL_RSAPROT_PPP_MASK) {
	case OP_PCL_RSAPROT_PPP_RED:
	case OP_PCL_RSAPROT_PPP_ENC:
	case OP_PCL_RSAPROT_PPP_EKT:
	case OP_PCL_RSAPROT_PPP_TK_ENC:
	case OP_PCL_RSAPROT_PPP_TK_EKT:
		break;
	default:
		return -1;
	}

	if (protoinfo & OP_PCL_RSAPROT_FMT_PKCSV15)
		switch (protoinfo & OP_PCL_RSAPROT_FFF_MASK) {
		case OP_PCL_RSAPROT_FFF_RED:
		case OP_PCL_RSAPROT_FFF_ENC:
		case OP_PCL_RSAPROT_FFF_EKT:
		case OP_PCL_RSAPROT_FFF_TK_ENC:
		case OP_PCL_RSAPROT_FFF_TK_EKT:
			break;
		default:
			return -1;
		}

	return 0;
}

static inline int __rta_3g_dcrc_proto(uint16_t protoinfo)
{
	if (rta_sec_era == RTA_SEC_ERA_7)
		return -1;

	switch (protoinfo) {
	case OP_PCL_3G_DCRC_CRC7:
	case OP_PCL_3G_DCRC_CRC11:
		return 0;
	}

	return -1;
}

static inline int __rta_3g_rlc_proto(uint16_t protoinfo)
{
	if (rta_sec_era == RTA_SEC_ERA_7)
		return -1;

	switch (protoinfo) {
	case OP_PCL_3G_RLC_NULL:
	case OP_PCL_3G_RLC_KASUMI:
	case OP_PCL_3G_RLC_SNOW:
		return 0;
	}

	return -1;
}

static inline int __rta_lte_pdcp_proto(uint16_t protoinfo)
{
	if (rta_sec_era == RTA_SEC_ERA_7)
		return -1;

	switch (protoinfo) {
	case OP_PCL_LTE_ZUC:
		if (rta_sec_era < RTA_SEC_ERA_5)
			break;
	case OP_PCL_LTE_NULL:
	case OP_PCL_LTE_SNOW:
	case OP_PCL_LTE_AES:
		return 0;
	}

	return -1;
}

static inline int __rta_lte_pdcp_mixed_proto(uint16_t protoinfo)
{
	switch (protoinfo & OP_PCL_LTE_MIXED_AUTH_MASK) {
	case OP_PCL_LTE_MIXED_AUTH_NULL:
	case OP_PCL_LTE_MIXED_AUTH_SNOW:
	case OP_PCL_LTE_MIXED_AUTH_AES:
	case OP_PCL_LTE_MIXED_AUTH_ZUC:
		break;
	default:
		return -1;
	}

	switch (protoinfo & OP_PCL_LTE_MIXED_ENC_MASK) {
	case OP_PCL_LTE_MIXED_ENC_NULL:
	case OP_PCL_LTE_MIXED_ENC_SNOW:
	case OP_PCL_LTE_MIXED_ENC_AES:
	case OP_PCL_LTE_MIXED_ENC_ZUC:
		return 0;
	}

	return -1;
}

struct proto_map {
	uint32_t optype;
	uint32_t protid;
	int (*protoinfo_func)(uint16_t);
};

static const struct proto_map proto_table[] = {
/*1*/	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_SSL30_PRF,	 __rta_ssl_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_TLS10_PRF,	 __rta_ssl_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_TLS11_PRF,	 __rta_ssl_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_TLS12_PRF,	 __rta_ssl_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DTLS10_PRF,	 __rta_ssl_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_IKEV1_PRF,	 __rta_ike_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_IKEV2_PRF,	 __rta_ike_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_PUBLICKEYPAIR, __rta_dlc_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DSASIGN,	 __rta_dlc_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DSAVERIFY,	 __rta_dlc_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_IPSEC,         __rta_ipsec_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_SRTP,	         __rta_srtp_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_SSL30,	 __rta_ssl_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_TLS10,	 __rta_ssl_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_TLS11,	 __rta_ssl_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_TLS12,	 __rta_ssl_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_DTLS10,	 __rta_ssl_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_MACSEC,        __rta_macsec_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_WIFI,          __rta_wifi_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_WIMAX,         __rta_wimax_proto},
/*21*/	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_BLOB,          __rta_blob_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_DIFFIEHELLMAN, __rta_dlc_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_RSAENCRYPT,	 __rta_rsa_enc_proto},
	{OP_TYPE_UNI_PROTOCOL,   OP_PCLID_RSADECRYPT,	 __rta_rsa_dec_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_3G_DCRC,       __rta_3g_dcrc_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_3G_RLC_PDU,    __rta_3g_rlc_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_3G_RLC_SDU,    __rta_3g_rlc_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_LTE_PDCP_USER, __rta_lte_pdcp_proto},
/*29*/	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_LTE_PDCP_CTRL, __rta_lte_pdcp_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_PUBLICKEYPAIR, __rta_dlc_proto},
/*31*/	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_DSASIGN,	 __rta_dlc_proto},
/*32*/	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_LTE_PDCP_CTRL_MIXED, __rta_lte_pdcp_mixed_proto},
	{OP_TYPE_DECAP_PROTOCOL, OP_PCLID_IPSEC_NEW,     __rta_ipsec_proto},
};

/*
 * Allowed OPERATION protocols for each SEC Era.
 * Values represent the number of entries from proto_table[] that are supported.
 */
static const unsigned proto_table_sz[] = {21, 29, 29, 29, 29, 29, 31};

static inline unsigned rta_proto_operation(struct program *program,
					   uint32_t optype, uint32_t protid,
					   uint16_t protoinfo)
{
	uint32_t opcode = CMD_OPERATION;
	int i, found = 0;
	uint32_t optype_tmp = optype;
	unsigned start_pc = program->current_pc;

	for (i = 0; i < proto_table_sz[rta_sec_era]; i++) {
		/* clear last bit in optype to match also decap proto */
		optype_tmp &= ~(1 << OP_TYPE_SHIFT);
		if (optype_tmp == proto_table[i].optype) {
			if (proto_table[i].protid == protid) {
				/* nothing else to verify */
				if (proto_table[i].protoinfo_func == NULL) {
					found = 1;
					break;
				}
				/* check protoinfo */
				if (-1 == (*proto_table[i].protoinfo_func)
						(protoinfo)) {
					pr_debug("PROTO_DESC: Bad PROTO Type. SEC Program Line: %d\n",
						 program->current_pc);
					goto err;
				}
				found = 1;
				break;
			}
		}
	}
	if (!found) {
		pr_debug("PROTO_DESC: Operation Type Mismatch. SEC Program Line: %d\n",
			 program->current_pc);
		goto err;
	}

	__rta_out32(program, opcode | optype | protid | protoinfo);
	program->current_instruction++;
	return start_pc;

 err:
	program->first_error_pc = start_pc;
	program->current_instruction++;
	return start_pc;
}

#endif /* __RTA_PROTOCOL_CMD_H__ */

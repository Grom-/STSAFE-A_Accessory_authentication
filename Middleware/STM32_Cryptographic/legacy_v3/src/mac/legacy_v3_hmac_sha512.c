/**
  *******************************************************************************
  * @file    legacy_v3_hmac_sha512.c
  * @author  MCD Application Team
  * @brief   This file provides HMAC SHA512 functions of helper for
  *          migration of cryptographics library V3 to V4
  *******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  *******************************************************************************
  */

#include "mac/legacy_v3_hmac_sha512.h"
#include "err_codes.h"

/* Initialize a new HMAC SHA512 context */
int32_t HMAC_SHA512_Init(HMAC_SHA512ctx_stt *P_pHMAC_SHA512ctx)
{
  cmox_mac_retval_t cmox_retval;
  int32_t retval;

  if (P_pHMAC_SHA512ctx == NULL)
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }
  P_pHMAC_SHA512ctx->mac_handle = cmox_hmac_construct(&P_pHMAC_SHA512ctx->hmac_handle,
                                                      CMOX_HMAC_SHA512);
  if (P_pHMAC_SHA512ctx->mac_handle == NULL)
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }
  cmox_retval = cmox_mac_init(P_pHMAC_SHA512ctx->mac_handle);
  if (cmox_retval != CMOX_MAC_SUCCESS)
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }

  cmox_retval = cmox_mac_setTagLen(P_pHMAC_SHA512ctx->mac_handle, (size_t)P_pHMAC_SHA512ctx->mTagSize);
  if (cmox_retval != CMOX_MAC_SUCCESS)
  {
    retval = HASH_ERR_BAD_CONTEXT;
    goto error;
  }

  cmox_retval = cmox_mac_setKey(P_pHMAC_SHA512ctx->mac_handle,
                                P_pHMAC_SHA512ctx->pmKey,
                                (size_t)P_pHMAC_SHA512ctx->mKeySize);
  if (cmox_retval != CMOX_MAC_SUCCESS)
  {
    retval = HASH_ERR_BAD_CONTEXT;
    goto error;
  }

  retval = HASH_SUCCESS;

error:
  return retval;
}

/* HMAC-SHA512 Update function, process input data and update a HMAC_SHA512ctx_stt */
int32_t HMAC_SHA512_Append(HMAC_SHA512ctx_stt *P_pHMAC_SHA512ctx, const uint8_t *P_pInputBuffer, int32_t P_inputSize)
{
  cmox_mac_retval_t cmox_retval;
  int32_t retval;

  if ((P_pHMAC_SHA512ctx == NULL) || (P_pInputBuffer == NULL) || (P_inputSize < 0))
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }

  cmox_retval = cmox_mac_append(P_pHMAC_SHA512ctx->mac_handle, P_pInputBuffer, (size_t)P_inputSize);

  if (cmox_retval == CMOX_MAC_ERR_BAD_OPERATION)
  {
    retval = HASH_ERR_BAD_OPERATION;
    goto error;
  }

  if (cmox_retval != CMOX_MAC_SUCCESS)
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }

  retval = HASH_SUCCESS;

error:
  return retval;
}

/* HMAC-SHA512 Finish function, produce the output HMAC-SHA512 tag */
int32_t HMAC_SHA512_Finish(HMAC_SHA512ctx_stt *P_pHMAC_SHA512ctx, uint8_t *P_pOutputBuffer, int32_t *P_pOutputSize)
{
  cmox_mac_retval_t cmox_retval;
  int32_t retval;
  /* Temporal value for storing the computed output length. This is needed
     because of the possible (e.g. in 64 bits architectures) different dimension
     between int32_t (used in legacy helper) and size_t (used by the library
     for specifying lengths). */
  size_t tempOutputLen;

  if ((P_pHMAC_SHA512ctx == NULL) || (P_pOutputBuffer == NULL) || (P_pOutputSize == NULL))
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }

  cmox_retval = cmox_mac_generateTag(P_pHMAC_SHA512ctx->mac_handle, P_pOutputBuffer, &tempOutputLen);

  if (cmox_retval != CMOX_MAC_SUCCESS)
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }

  /* Copy the cast to int32_t of tempOutputLen in order to not overwrite
     other data close to P_pOutputSize. */
  *P_pOutputSize = (int32_t)tempOutputLen;

  cmox_retval = cmox_mac_cleanup(P_pHMAC_SHA512ctx->mac_handle);
  if (cmox_retval != CMOX_MAC_SUCCESS)
  {
    retval = HASH_ERR_BAD_PARAMETER;
    goto error;
  }

  retval = HASH_SUCCESS;

error:
  return retval;
}
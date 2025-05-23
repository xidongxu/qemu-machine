/** @file
  TCG2 Standalone MM driver that updates TPM2 items in ACPI table and registers
  SMI2 callback functions for Tcg2 physical presence, ClearMemory, and
  sample for dTPM StartMethod.

  Caution: This module requires additional review when modified.
  This driver will have external input - variable and ACPINvs data in SMM mode.
  This external input must be validated carefully to avoid security issue.

  PhysicalPresenceCallback() and MemoryClearCallback() will receive untrusted input and do some check.

Copyright (c) 2015 - 2024, Intel Corporation. All rights reserved.<BR>
Copyright (c) Microsoft Corporation.
SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include "Tcg2Smm.h"
#include <Library/StandaloneMmMemLib.h>
#include <Library/HobLib.h>

/**
  Notify the system that the SMM variable driver is ready.
**/
VOID
Tcg2NotifyMmReady (
  VOID
  )
{
  // Do nothing
}

/**
  This function is for the Primary Buffer validation routine.
  The Primary Buffer is the communication buffer requested from
  Communicate protocol/PPI.

  @param Buffer  The buffer start address to be checked.
  @param Length  The buffer length to be checked.

  @retval TRUE  This buffer is valid.
  @retval FALSE This buffer is not valid.
**/
BOOLEAN
Tcg2IsPrimaryBufferValid (
  IN EFI_PHYSICAL_ADDRESS  Buffer,
  IN UINT64                Length
  )
{
  return TRUE;
}

/**
  This function is for the Secondary Buffer validation routine.
  The Secondary Buffer is the buffer which is pointed from the
  communication buffer.

  @param Buffer  The buffer start address to be checked.
  @param Length  The buffer length to be checked.

  @retval TRUE  This buffer is valid.
  @retval FALSE This buffer is not valid.
**/
BOOLEAN
Tcg2IsNonPrimaryBufferValid (
  IN EFI_PHYSICAL_ADDRESS  Buffer,
  IN UINT64                Length
  )
{
  return MmIsBufferOutsideMmValid (Buffer, Length);
}

/**
  This function checks if the required DTPM instance is TPM 2.0.

  @retval TRUE  The required DTPM instance is equal to gEfiTpmDeviceInstanceTpm20DtpmGuid.
  @retval FALSE The required DTPM instance is not equal to gEfiTpmDeviceInstanceTpm20DtpmGuid.
**/
BOOLEAN
IsTpm20Dtpm (
  VOID
  )
{
  VOID  *GuidHob;

  GuidHob = GetFirstGuidHob (&gEdkiiTpmInstanceHobGuid);
  if (GuidHob != NULL) {
    if (CompareGuid ((EFI_GUID *)GET_GUID_HOB_DATA (GuidHob), &gEfiTpmDeviceInstanceTpm20DtpmGuid)) {
      return TRUE;
    }

    DEBUG ((DEBUG_ERROR, "No TPM2 DTPM instance required! - %g\n", (EFI_GUID *)GET_GUID_HOB_DATA (GuidHob)));
  } else {
    DEBUG ((DEBUG_ERROR, "No gEdkiiTpmInstanceHobGuid!\n"));
  }

  return FALSE;
}

/**
  The driver's entry point.

  It install callbacks for TPM physical presence and MemoryClear, and locate
  SMM variable to be used in the callback function.

  @param[in] ImageHandle  The firmware allocated handle for the EFI image.
  @param[in] SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS     The entry point is executed successfully.
  @retval Others          Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
InitializeTcgStandaloneMm (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_MM_SYSTEM_TABLE  *SystemTable
  )
{
  return InitializeTcgCommon ();
}

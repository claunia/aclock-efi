/** @file
  Aclock is an analog clock program for text mode console displays, terminals, or terminal emulators.
  This program is obviously absolutely useless, except for turning your old, expensive mainframe or
  supercomputer into a wall clock.

  Copyright (c) 1994-2016 Antoni Sawicki <as@tenoware.com>
  Copyright (c) 2016 Natalia Portillo <claunia@claunia.com>
**/

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>

/**
  as the real entry point for the application.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  Print(L"Hello World \n"); 
  return EFI_SUCCESS;
}


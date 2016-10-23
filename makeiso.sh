#!/bin/bash
mkdir -p iso/EFI/BOOT
cp -n binaries/aclock-efi-x86_64.efi iso/EFI/BOOT/BOOTX64.EFI
cp -n binaries/aclock-efi-ia32.efi iso/EFI/BOOT/BOOTX86.EFI
cp -n binaries/aclock-efi-ia64.efi iso/EFI/BOOT/BOOTI64.EFI
cp -n binaries/aclock-efi-arm.efi iso/EFI/BOOT/BOOTARM.EFI
cp -n binaries/aclock-efi-arm64.efi iso/EFI/BOOT/BOOTAA64.EFI
mkisofs -o binaries/aclock-efi.iso iso
rm -Rfv iso
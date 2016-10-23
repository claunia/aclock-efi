ARCH            = $(shell uname -m | sed s,i[3456789]86,ia32,)

OBJS            = s_fabs.o k_rem_pio2.o e_rem_pio2.o k_cos.o k_sin.o s_cos.o s_sin.o Aclock.o
TARGET          = aclock-efi-$(ARCH).efi

EFIINC          = /usr/include/efi
EFIINCS         = -I$(EFIINC) -I$(EFIINC)/$(ARCH) -I$(EFIINC)/protocol
LIB             = /usr/lib64
EFILIB          = /usr/lib64
EFI_CRT_OBJS    = $(EFILIB)/crt0-efi-$(ARCH).o
EFI_LDS         = $(EFILIB)/elf_$(ARCH)_efi.lds

CFLAGS          = $(EFIINCS) -DGNU_EFI -fno-stack-protector -fpic \
					-fshort-wchar -mno-red-zone -Wall
ifeq ($(ARCH),x86_64)
  CFLAGS += -DEFI_FUNCTION_WRAPPER
endif

LDFLAGS         = -nostdlib -znocombreloc -T $(EFI_LDS) -shared \
		  -Bsymbolic -L $(EFILIB) -L $(LIB) $(EFI_CRT_OBJS) 

all: $(TARGET)

aclock-efi-$(ARCH).so: $(OBJS)
	ld $(LDFLAGS) $(OBJS) -o $@ -lefi -lgnuefi

%.efi: %.so
	objcopy -j .text -j .sdata -j .data -j .dynamic \
		-j .dynsym  -j .rel -j .rela -j .reloc \
		--target=efi-app-$(ARCH) $^ binaries/$@
ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS=-Wall -g
AM_CFLAGS+=-D DEBUG
AM_CFLAGS+=-D WARNING
AM_CFLAGS+=-D BIG_ENDIAN_SIMULATOR
# Uncomment if performance when running with -DDEBUG is an issue
# Warning, if uncommented, issuing calls to debug functions during options
# parsing might result in debug flag incorrectly set to 0 for some files
#AM_CFLAGS+=-D CACHE_DEBUG_FLAG

LDADD=-lpthread


SUBDIRS=
SUBDIRS+=. Examples_loader

bin_PROGRAMS=
bin_PROGRAMS+=ARM_runner_example
bin_PROGRAMS+=test_section
bin_PROGRAMS+=fusion
bin_PROGRAMS+=fusion_symbol_tab

COMMON=debug.h debug.c util.h util.c type_liste_symb.c type_liste_symb.h lecture.c lecture.h affichage.c affichage.h mains.c mains.h gestion_endian.c gestion_endian.h elf32_reloc_table.c elf32_reloc_table.h

EXTRA_DIST=filtre.pl
SIMULATOR_INTERFACE=csapp.h csapp.c scanner.h scanner.l gdb_protocol.h gdb_protocol.c arm_simulator_interface.h arm_simulator_interface.c

ARM_runner_example_SOURCES=$(COMMON) $(SIMULATOR_INTERFACE) ARM_runner_example.c
test_section_SOURCES=$(COMMON) sectionTest.c
fusion_SOURCES=$(COMMON) fusion.c
fusion_symbol_tab_SOURCES=$(COMMON) fusion_table_symboles.h fusion_table_symboles.c

EXTRA_DIST+=sample_run.sh

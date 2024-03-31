/* This linker script generated from xt-genldscripts.tpp for LSP rtos-ram */
/* Linker Script for default link */
/*  Customer ID=14794; Build=0x87a3c; Copyright (c) 2005-2020 Tensilica Inc.  */
/*
 *  This is one of four linker scripts generated for general-purpose,
 *  and for use by RTOS in particular.
 *
 *  These scripts have the property that the -Ttext, -Tdata and -Tbss
 *  linker options generally work as expected (unlike the default linker
 *  scripts generated by xt-genldscripts).  That is, these options
 *  move the text, data and/or bss sections in memory as specified.
 *  This approach implies there is NO memory overflow or overlap checking
 *  on the .text, .data and .bss sections because these are directed to
 *  an unrestricted MEMORY region in the linker script (covering 4 GB).
 *
 *  Note:  these linker scripts do not yet have easy support of ROMs
 *	other than the system ROM (eg. of instruction and data ROMs).
 *  Note:  no configuration file *system* info is reflected in these linker
 *	scripts except system ROM, system RAM, and vector locations/sizes.
 *
 *  The four linker scripts emit/pack sections as follows:
 *
 *			<> = vaddr = paddr
 *			{} = vaddr (copied-from-packed or zeroed)
 *			[] = paddr (packed)
 *  rtos-ram LSP:
 *	RAM contents:	<ramvecs>...  <text+rodata><data><bss>
 *	ROM contents:	(none)
 *	---
 *	Linker script for RAM images.
 *	This has no unpack table; the various discontiguous RAM sections
 *	(vectors, etc) are loaded by an external ELF loader.
 *
 *  rtos-ramp LSP:
 *	RAM contents:	{ramvecs}...  <text+rodata+unpack><data>[ramvecs] <bss>
 *	ROM contents:	(none)
 *	---
 *	This script is similar to rtosram.ld, but packs RAM vectors after
 *	the .data section.  The RAM vectors must be unpacked in the image's
 *	initialization code (before any C code).  This arrangement is
 *	necessary when the image gets loaded by anything more complicated
 *	than an assembler loop that immediately jumps to the code, because
 *	otherwise loading the RAM vectors would corrupt operation of
 *	the loading process (eg. VxWorks bootrom has a full kernel
 *	running during boot loading, with TFTP/FTP/RSH/TCP/IP/etc. tasks).
 *	It is also necessary when one needs one contiguous block of bytes,
 *	eg. for compression.
 *
 *  rtos-rom LSP:
 *	RAM contents:	{ramvecs}...  {text+rodata}{data}{bss}
 *	ROM contents:	<romvecs>...  <srom+unpack>[text+rodata][data][ramvecs]
 *	---
 *	Linker script for ROM images, where most sections are copied to RAM
 *	before being executed.  This is a typical scenario when executing
 *	directly from ROM is too slow for normal operation.  The unpacking
 *	code is typically put in the .srom.* sections (or in the reset vector
 *	if it is large enough).
 *
 *  rtos-res LSP:
 *	RAM contents:	{ramvecs}...  {data}{bss}
 *	ROM contents:	<romvecs>...  <srom+text+rodata+unpack>[data][ramvecs]
 *	---
 *	Linker script for ROM images, where code executes directly out of ROM.
 *	Initialized data and RAM vectors need to be copied to RAM, so this
 *	image also needs unpacking code early in initialization.
 *
 *
 *  VxWorks uses these linker scripts as follows:
 *	Image type:	Script			Flags   (lohi = RAM_LOW_ADRS
 *	----------	------			-----        or RAM_HIGH_ADRS)
 *	RAM:		rtosramp.ld	RAM	-Ttext=lohi
 *	ROM-resident:	rtosres.ld	ROM	-Tdata=lohi -Ttext=ROM_TEXT_ADRS
 *	ROM-uncmp:	rtosrom.ld	ROM	-Ttext=lohi
 *	ROM-cmp-inner:	rtosramp.ld	RAM	-Ttext=lohi
 *	ROM-cmp-outer:	rtosrom.ld	ROM	-Ttext=lohi
 *
 */
/*
 *  Virtual memory ranges where sections can be directed
 *  (these are called 'segments' in Xtensa internal documentation).
 *
 *  Entries are of the form:
 *	name (attr) : ORIGIN = e, LENGTH = e
 *	name (attr) : org = e, len = e
 *	name (attr) : o = e, l = e
 *  where attr is a combination of:
 *	R=readonly
 *	W=read/write
 *	X=executable
 *	A=allocated
 *	I=L=initialized
 *	!=invert sense of following attributes
 */
MEMORY
{
  sram1_seg :                         	org = 0xA0000400, len = 0x17C
  sram2_seg :                         	org = 0xA000057C, len = 0x20
  sram3_seg :                         	org = 0xA000059C, len = 0x20
  sram4_seg :                         	org = 0xA00005BC, len = 0x20
  sram5_seg :                         	org = 0xA00005DC, len = 0x20
  sram6_seg :                         	org = 0xA00005FC, len = 0x20
  sram7_seg :                         	org = 0xA000061C, len = 0x24
  sram8_seg :                         	org = 0xA0000640, len = 0xFFFF9C0
  /*  Entry covering the entire address space, to avoid linker errors
      due to mixing sections that are directed to MEMORY regions and
      others that are not:  */
  ALLMEMORY :				org = 0, len = 0xFFFFFFFF
}

PHDRS
{
/*
 *  ELF linker scripts can contain explicit program headers
 *  (which tell the loader what to load where), eg.:
 *	PHDRS { <entries>... }
 *  where <entries> are of the form:
 *	NAME TYPE [ FILEHDR ] [ PHDRS ] [ AT ( ADDRESS ) ] [ FLAGS ( FLAGS ) ] ;
 */
  sram0_phdr PT_LOAD;
  sram1_phdr PT_LOAD;
  sram2_phdr PT_LOAD;
  sram3_phdr PT_LOAD;
  sram4_phdr PT_LOAD;
  sram5_phdr PT_LOAD;
  sram6_phdr PT_LOAD;
  sram7_phdr PT_LOAD;
  sram8_phdr PT_LOAD;
}


/*  Default entry point:  */
ENTRY(_start)


/*  Memory boundary addresses:  */
_memmap_mem_sram_start = 0xa0000000;
_memmap_mem_sram_end   = 0xb0000000;

/*  Memory segment boundary addresses:  */
_memmap_seg_sram1_start = 0xa0000400;
_memmap_seg_sram1_max   = 0xa000057c;
_memmap_seg_sram2_start = 0xa000057c;
_memmap_seg_sram2_max   = 0xa000059c;
_memmap_seg_sram3_start = 0xa000059c;
_memmap_seg_sram3_max   = 0xa00005bc;
_memmap_seg_sram4_start = 0xa00005bc;
_memmap_seg_sram4_max   = 0xa00005dc;
_memmap_seg_sram5_start = 0xa00005dc;
_memmap_seg_sram5_max   = 0xa00005fc;
_memmap_seg_sram6_start = 0xa00005fc;
_memmap_seg_sram6_max   = 0xa000061c;
_memmap_seg_sram7_start = 0xa000061c;
_memmap_seg_sram7_max   = 0xa0000640;
_memmap_seg_sram8_start = 0xa0000640;
_memmap_seg_sram8_max   = 0xb0000000;

_rom_store_table = 0;
PROVIDE(_memmap_reset_vector = 0xa0000640);
PROVIDE(_memmap_vecbase_reset = 0xa0000400);
/* Various memory-map dependent cache attribute settings: */
_memmap_cacheattr_wb_base = 0x00141000;
_memmap_cacheattr_wt_base = 0x00343000;
_memmap_cacheattr_bp_base = 0x00444000;
_memmap_cacheattr_unused_mask = 0xFF000FFF;
_memmap_cacheattr_wb_trapnull = 0x44141440;
_memmap_cacheattr_wba_trapnull = 0x44141440;
_memmap_cacheattr_wbna_trapnull = 0x44242440;
_memmap_cacheattr_wt_trapnull = 0x44343440;
_memmap_cacheattr_bp_trapnull = 0x44444440;
_memmap_cacheattr_wb_strict = 0x00141000;
_memmap_cacheattr_wt_strict = 0x00343000;
_memmap_cacheattr_bp_strict = 0x00444000;
_memmap_cacheattr_wb_allvalid = 0x44141444;
_memmap_cacheattr_wt_allvalid = 0x44343444;
_memmap_cacheattr_bp_allvalid = 0x44444444;
_memmap_region_map = 0x00000038;
PROVIDE(_memmap_cacheattr_reset = _memmap_cacheattr_wb_trapnull);
/*
 *  Other commands and functions of interest:
 *	PROVIDE(var = value);
 *	ABSOLUTE(e)		non-section-relative expr
 *	ADDR(e)			vaddr
 *	LOADADDR(e)		paddr (=vaddr if not AT())
 *	ALIGN(e)		(. + e - 1) & ~(e - 1)
 *	NEXT(e)			like ALIGN(), but if MEMORY is used, may skip to next available region
 *	DEFINED(sym)		1 if sym defined, else 0
 *	SIZEOF(section)		size of section if allocated
 *	SIZEOF_HEADERS		size in byte of output file's headers
 *	MAX(e1,e2)
 *	MIN(e1,e2)
 */
/*
 *  Mapping of input sections to output sections when linking.
 *
 *  Entries are of the form:
 *	SECNAME START BLOCK(ALIGN) (NOLOAD) : AT ( LDADR )
 *		{ CONTENTS } >REGION :PHDR [... or :NONE] =FILL
 *  or
 *	/DISCARD/ : { IGNORED_SECTIONS... }
 *
 *  Also in sections:
 *	BYTE(e) SHORT(e) LONG(e) QUAD(e) SQUAD(e)
 */

SECTIONS
{

  /*  -Ttext moves vaddr of what follows:  */
  .text 0xA0000640 : ALIGN(4)
  {
    _stext = .;
    _text_start = ABSOLUTE(.);
    *(.entry.text)
    *(.init.literal)
    KEEP(*(.init))
    *(.literal.sort.* SORT(.text.sort.*))
    KEEP (*(.literal.keepsort.* SORT(.text.keepsort.*) .literal.keep.* .text.keep.* .literal.*personality* .text.*personality*))
    *(.literal .text .literal.* .text.* .stub .gnu.warning .gnu.linkonce.literal.* .gnu.linkonce.t.*.literal .gnu.linkonce.t.*)
    *(.fini.literal)
    KEEP(*(.fini))
    *(.gnu.version)
    KEEP (*(.ResetVector.text))
    *(.ResetHandler.literal .ResetHandler.text)
    *(.sram.rodata)
    *(.clib.rodata)
    *(.rtos.rodata)
    *(.rodata)
    *(SORT(.rodata.sort.*))
    KEEP (*(SORT(.rodata.keepsort.*) .rodata.keep.*))
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    __XT_EXCEPTION_TABLE__ = ABSOLUTE(.);
    KEEP (*(.xt_except_table))
    KEEP (*(.gcc_except_table))
    *(.gnu.linkonce.e.*)
    *(.gnu.version_r)
    KEEP (*(.eh_frame))
    /*  C++ constructor and destructor tables, properly ordered:  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /*  C++ exception handlers table:  */
    __XT_EXCEPTION_DESCS__ = ABSOLUTE(.);
    *(.xt_except_desc)
    *(.gnu.linkonce.h.*)
    __XT_EXCEPTION_DESCS_END__ = ABSOLUTE(.);
    *(.xt_except_desc_end)
    *(.dynamic)
    *(.gnu.version_d)
    . = ALIGN(4);		/* this table MUST be 4-byte aligned */
    _bss_table_start = ABSOLUTE(.);
    LONG(_bss_start)
    LONG(_bss_end)
    _bss_table_end = ABSOLUTE(.);
    *(.sram.literal .sram.text)
    *(.clib.literal .clib.text)
    *(.rtos.literal .rtos.text)
    . = ALIGN (4);
    _text_end = ABSOLUTE(.);
    _etext = .;
  } >ALLMEMORY :sram8_phdr

  /*  -Tdata moves vaddr of what follows:  */
  .data : ALIGN(4)
  {
    _data_start = ABSOLUTE(.);
    *(.data)
    *(SORT(.data.sort.*))
    KEEP (*(SORT(.data.keepsort.*) .data.keep.*))
    *(.data.*)
    *(.gnu.linkonce.d.*)
    KEEP(*(.gnu.linkonce.d.*personality*))
    *(.data1)
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    *(.sdata2)
    *(.sdata2.*)
    *(.gnu.linkonce.s2.*)
    KEEP(*(.jcr))
    *(__llvm_prf_cnts)
    *(__llvm_prf_data)
    *(__llvm_prf_vnds)
    *(.clib.data)
    *(.clib.percpu.data)
    *(.rtos.percpu.data)
    *(.rtos.data)
    *(.sram.data)
    *(__llvm_prf_names)
    . = ALIGN (4);
    _data_end = ABSOLUTE(.);
  } >ALLMEMORY :sram8_phdr

  /*  -Tbss moves vaddr of what follows:  */
  .bss (NOLOAD) : ALIGN(8)
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);
    *(.dynsbss)
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    *(.scommon)
    *(.sbss2)
    *(.sbss2.*)
    *(.gnu.linkonce.sb2.*)
    *(.dynbss)
    *(.bss)
    *(SORT(.bss.sort.*))
    KEEP (*(SORT(.bss.keepsort.*) .bss.keep.*))
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    *(.clib.bss)
    *(.clib.percpu.bss)
    *(.rtos.percpu.bss)
    *(.rtos.bss)
    *(.sram.bss)
    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
    _end = ALIGN(0x8);
    PROVIDE(end = ALIGN(0x8));
    _stack_sentry = ALIGN(0x8);
    _memmap_seg_sram8_end = ALIGN(0x8);
  } >ALLMEMORY :NONE

  PROVIDE(__stack = 0xb0000000);
  _heap_sentry = 0xb0000000;


  .WindowVectors.text : ALIGN(4)
  {
    _WindowVectors_text_start = ABSOLUTE(.);
    KEEP (*(.WindowVectors.text))
    . = ALIGN (4);
    _WindowVectors_text_end = ABSOLUTE(.);
  } >sram1_seg :sram1_phdr

  .Level2InterruptVector.literal : ALIGN(4)
  {
    _Level2InterruptVector_literal_start = ABSOLUTE(.);
    *(.Level2InterruptVector.literal)
    . = ALIGN (4);
    _Level2InterruptVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram1_end = ALIGN(0x8);
  } >sram1_seg :sram1_phdr


  .Level2InterruptVector.text : ALIGN(4)
  {
    _Level2InterruptVector_text_start = ABSOLUTE(.);
    KEEP (*(.Level2InterruptVector.text))
    . = ALIGN (4);
    _Level2InterruptVector_text_end = ABSOLUTE(.);
  } >sram2_seg :sram2_phdr

  .Level3InterruptVector.literal : ALIGN(4)
  {
    _Level3InterruptVector_literal_start = ABSOLUTE(.);
    *(.Level3InterruptVector.literal)
    . = ALIGN (4);
    _Level3InterruptVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram2_end = ALIGN(0x8);
  } >sram2_seg :sram2_phdr


  .Level3InterruptVector.text : ALIGN(4)
  {
    _Level3InterruptVector_text_start = ABSOLUTE(.);
    KEEP (*(.Level3InterruptVector.text))
    . = ALIGN (4);
    _Level3InterruptVector_text_end = ABSOLUTE(.);
  } >sram3_seg :sram3_phdr

  .DebugExceptionVector.literal : ALIGN(4)
  {
    _DebugExceptionVector_literal_start = ABSOLUTE(.);
    *(.DebugExceptionVector.literal)
    . = ALIGN (4);
    _DebugExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram3_end = ALIGN(0x8);
  } >sram3_seg :sram3_phdr


  .DebugExceptionVector.text : ALIGN(4)
  {
    _DebugExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.DebugExceptionVector.text))
    . = ALIGN (4);
    _DebugExceptionVector_text_end = ABSOLUTE(.);
  } >sram4_seg :sram4_phdr

  .KernelExceptionVector.literal : ALIGN(4)
  {
    _KernelExceptionVector_literal_start = ABSOLUTE(.);
    *(.KernelExceptionVector.literal)
    . = ALIGN (4);
    _KernelExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram4_end = ALIGN(0x8);
  } >sram4_seg :sram4_phdr


  .KernelExceptionVector.text : ALIGN(4)
  {
    _KernelExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.KernelExceptionVector.text))
    . = ALIGN (4);
    _KernelExceptionVector_text_end = ABSOLUTE(.);
  } >sram5_seg :sram5_phdr

  .UserExceptionVector.literal : ALIGN(4)
  {
    _UserExceptionVector_literal_start = ABSOLUTE(.);
    *(.UserExceptionVector.literal)
    . = ALIGN (4);
    _UserExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram5_end = ALIGN(0x8);
  } >sram5_seg :sram5_phdr


  .UserExceptionVector.text : ALIGN(4)
  {
    _UserExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.UserExceptionVector.text))
    . = ALIGN (4);
    _UserExceptionVector_text_end = ABSOLUTE(.);
  } >sram6_seg :sram6_phdr

  .DoubleExceptionVector.literal : ALIGN(4)
  {
    _DoubleExceptionVector_literal_start = ABSOLUTE(.);
    *(.DoubleExceptionVector.literal)
    . = ALIGN (4);
    _DoubleExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram6_end = ALIGN(0x8);
  } >sram6_seg :sram6_phdr


  .DoubleExceptionVector.text : ALIGN(4)
  {
    _DoubleExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.DoubleExceptionVector.text))
    . = ALIGN (4);
    _DoubleExceptionVector_text_end = ABSOLUTE(.);
  } >sram7_seg :sram7_phdr

  .ResetVector.literal : ALIGN(4)
  {
    _ResetVector_literal_start = ABSOLUTE(.);
    *(.ResetVector.literal)
    . = ALIGN (4);
    _ResetVector_literal_end = ABSOLUTE(.);
    _memmap_seg_sram7_end = ALIGN(0x8);
  } >sram7_seg :sram7_phdr

  .debug  0 :  { *(.debug) }
  .line  0 :  { *(.line) }
  .debug_srcinfo  0 :  { *(.debug_srcinfo) }
  .debug_sfnames  0 :  { *(.debug_sfnames) }
  .debug_aranges  0 :  { *(.debug_aranges) }
  .debug_pubnames  0 :  { *(.debug_pubnames) }
  .debug_info  0 :  { *(.debug_info) }
  .debug_abbrev  0 :  { *(.debug_abbrev) }
  .debug_line  0 :  { *(.debug_line) }
  .debug_frame  0 :  { *(.debug_frame) }
  .debug_str  0 :  { *(.debug_str) }
  .debug_loc  0 :  { *(.debug_loc) }
  .debug_macinfo  0 :  { *(.debug_macinfo) }
  .debug_weaknames  0 :  { *(.debug_weaknames) }
  .debug_funcnames  0 :  { *(.debug_funcnames) }
  .debug_typenames  0 :  { *(.debug_typenames) }
  .debug_varnames  0 :  { *(.debug_varnames) }
  .xt.insn 0 :
  {
    KEEP (*(.xt.insn))
    KEEP (*(.gnu.linkonce.x.*))
  }
  .xt.prop 0 :
  {
    KEEP (*(.xt.prop))
    KEEP (*(.xt.prop.*))
    KEEP (*(.gnu.linkonce.prop.*))
  }
  .xt.lit 0 :
  {
    KEEP (*(.xt.lit))
    KEEP (*(.xt.lit.*))
    KEEP (*(.gnu.linkonce.p.*))
  }
  .debug.xt.callgraph 0 :
  {
    KEEP (*(.debug.xt.callgraph .debug.xt.callgraph.* .gnu.linkonce.xt.callgraph.*))
  }
}


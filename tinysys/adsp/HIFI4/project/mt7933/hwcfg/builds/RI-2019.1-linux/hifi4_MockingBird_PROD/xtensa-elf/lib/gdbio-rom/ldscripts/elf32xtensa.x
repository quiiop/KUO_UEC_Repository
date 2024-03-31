/* This linker script generated from xt-genldscripts.tpp for LSP gdbio-rom */
/* Linker Script for default link */
/*  Some problem in the LSP memory map file used to generate this linker script
    prevented generating a working linker script.  However, it is a common issue
    that the user can correct by editing the memory map, so rather than not
    include this standard LSP, the LSP is installed anyway and the linker issues
    an error if any attempt is made to link using this LSP.  This linker error
    is accomplished using the following linker ASSERT statement.  */
_dummy_symbol_ = ASSERT(0,"
ERROR: The gdbio-rom LSP is unavailable.
ERROR: ROMING option specified in LSP memory map but .rom.store section not found.
ERROR: This error normally occurs when no ROM was configured.
ERROR: Edit the LSP's memory map and rerun xt-genldscripts to correct this error.
ERROR: Refer to the Xtensa LSP Reference Manual for more details.");
SECTIONS { /DISCARD/ : { *(*) } }

ENTRY(dupeng)

SECTIONS
{
	. = 0x08048000 + SIZEOF_HEADERS;
	dupeng : { *(.text) *(.data) *(.rodata) }
	/DISCARD/ : { *(.comment) }
}

	.module main.c
	.area text(rom, con, rel)
	.dbfile C:\LCM3\main.c
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
_var_XX#c::
	.blkb 1
	.area idata(rom)
	.byte 0
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
_conf_lcd#A_c::
	.blkb 2
	.area idata(rom)
	.byte 40,8
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 12,1
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 6,255
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
_a_Cx#A_c::
	.blkb 2
	.area idata(rom)
	.byte 32,5
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 32,'C
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 'x,255
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
_a_Cp#A_c::
	.blkb 2
	.area idata(rom)
	.byte 32,5
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 32,'C
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 'p,255
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
_a_vC0#A_c::
	.blkb 2
	.area idata(rom)
	.byte 32,5
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 32,'C
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c
	.blkb 2
	.area idata(rom)
	.byte 48,255
	.area data(ram, con, rel)
	.dbfile C:\LCM3\main.c


./bin/backtrace.elf:     file format elf32-epiphany


Disassembly of section link_symbols_data:

8e000000 <bjk_external_ram_load_data>:
8e000000:	0000      	beq 8e000000 <bjk_external_ram_load_data>
8e000002:	0200      	beq 8e000006 <bjk_external_ram_load_data+0x6>
8e000004:	0000      	beq 8e000004 <bjk_external_ram_load_data+0x4>
8e000006:	0080      	blt 8e000006 <bjk_external_ram_load_data+0x6>
8e000008:	0000      	beq 8e000008 <bjk_external_ram_load_data+0x8>
8e00000a:	0080      	blt 8e00000a <bjk_external_ram_load_data+0xa>
8e00000c:	0000      	beq 8e00000c <bjk_external_ram_load_data+0xc>
8e00000e:	0080      	blt 8e00000e <bjk_external_ram_load_data+0xe>
8e000010:	0000      	beq 8e000010 <bjk_external_ram_load_data+0x10>
8e000012:	0080      	blt 8e000012 <bjk_external_ram_load_data+0x12>
8e000014:	0000      	beq 8e000014 <bjk_external_ram_load_data+0x14>
8e000016:	8e00      	beq 8dffff32 <LD_EXTERNAL_RAM_SIZE+0x8bffff32>
8e000018:	0000      	beq 8e000018 <bjk_external_ram_load_data+0x18>
8e00001a:	8e00      	beq 8dffff36 <LD_EXTERNAL_RAM_SIZE+0x8bffff36>
8e00001c:	0000      	beq 8e00001c <bjk_external_ram_load_data+0x1c>
8e00001e:	8e80      	blt 8dffff3a <LD_EXTERNAL_RAM_SIZE+0x8bffff3a>
8e000020:	0000      	beq 8e000020 <bjk_external_ram_load_data+0x20>
8e000022:	8f00      	beq 8dffff40 <LD_EXTERNAL_RAM_SIZE+0x8bffff40>
8e000024:	0000      	beq 8e000024 <bjk_external_ram_load_data+0x24>
8e000026:	8f80      	blt 8dffff44 <LD_EXTERNAL_RAM_SIZE+0x8bffff44>
	...

Disassembly of section ivt_reset:

00000000 <_start>:
   0:	cee8 0000 	b 19c <normal_start>

Disassembly of section ivt_software_exception:

00000004 <irq1_entry>:
   4:	12e8 0001 	b 228 <bjk_software_exception_handler>

Disassembly of section ivt_page_miss:

00000008 <irq2_entry>:
   8:	46e8 0001 	b 294 <bjk_page_miss_handler>

Disassembly of section ivt_timer0:

0000000c <irq3_entry>:
   c:	7ae8 0001 	b 300 <bjk_timer0_handler>

Disassembly of section external_code_ram:

8e000038 <bj_cores_main>:
8e000038:	d57c 2700 	strd lr,[sp],-0x2
8e00003c:	f41b 2402 	add fp,sp,16
8e000040:	100b 0042 	mov r0,0x480
8e000044:	000b 18e2 	movt r0,0x8e00
8e000048:	0152      	jalr r0
8e00004a:	080b 0032 	mov r0,0x340
8e00004e:	000b 1002 	movt r0,0x0
8e000052:	1cdc 0500 	str r0,[fp,-0x1]
8e000056:	2003      	mov r1,0x0
8e000058:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00005c:	528b 0002 	mov r2,0x94
8e000060:	400b 18e2 	movt r2,0x8e00
8e000064:	0952      	jalr r2
8e000066:	2423      	mov r1,0x21
8e000068:	0a0b 0032 	mov r0,0x350
8e00006c:	000b 1002 	movt r0,0x0
8e000070:	4c8b 0012 	mov r2,0x164
8e000074:	400b 1002 	movt r2,0x0
8e000078:	0952      	jalr r2
8e00007a:	078b 0092 	mov r0,0x93c
8e00007e:	000b 18e2 	movt r0,0x8e00
8e000082:	0152      	jalr r0
8e000084:	01a2      	nop
8e000086:	d56c 2400 	ldrd lr,[sp,+0x2]
8e00008a:	b41b 2402 	add sp,sp,16
8e00008e:	194f 0402 	rts
8e000092:	01a2      	nop

8e000094 <bjk_aux_sout>:
8e000094:	d67c 2700 	strd lr,[sp],-0x4
8e000098:	f41b 2404 	add fp,sp,32
8e00009c:	1edc 0500 	str r0,[fp,-0x5]
8e0000a0:	3f5c 0500 	str r1,[fp,-0x6]
8e0000a4:	108b 0032 	mov r0,0x384
8e0000a8:	000b 1002 	movt r0,0x0
8e0000ac:	0044      	ldr r0,[r0]
8e0000ae:	02cc 0001 	ldr r0,[r0,+0xd]
8e0000b2:	2033      	sub r1,r0,0
8e0000b4:	8b08 0000 	beq 8e0001ca <bjk_aux_sout+0x136>
8e0000b8:	0043      	mov r0,0x2
8e0000ba:	1e9c 0500 	strb r0,[fp,-0x5]
8e0000be:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0000c2:	380b 0032 	mov r1,0x3c0
8e0000c6:	200b 18e2 	movt r1,0x8e00
8e0000ca:	0552      	jalr r1
8e0000cc:	1cbc 0500 	strh r0,[fp,-0x1]
8e0000d0:	3cac 0500 	ldrh r1,[fp,-0x1]
8e0000d4:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e0000d8:	458b 0012 	mov r2,0x12c
8e0000dc:	083a      	sub r0,r2,r0
8e0000de:	443a      	sub r2,r1,r0
8e0000e0:	0a90      	blte 8e0000f4 <bjk_aux_sout+0x60>
8e0000e2:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e0000e6:	000b 1002 	movt r0,0x0
8e0000ea:	258b 0012 	mov r1,0x12c
8e0000ee:	043a      	sub r0,r1,r0
8e0000f0:	1cbc 0500 	strh r0,[fp,-0x1]
8e0000f4:	108b 0032 	mov r0,0x384
8e0000f8:	000b 1002 	movt r0,0x0
8e0000fc:	0044      	ldr r0,[r0]
8e0000fe:	021b 0007 	add r0,r0,60
8e000102:	1ddc 0500 	str r0,[fp,-0x3]
8e000106:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e00010a:	3dcc 0500 	ldr r1,[fp,-0x3]
8e00010e:	041a      	add r0,r1,r0
8e000110:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000114:	44e2      	mov r2,r1
8e000116:	3ecc 0500 	ldr r1,[fp,-0x5]
8e00011a:	6e8b 0032 	mov r3,0x374
8e00011e:	600b 18e2 	movt r3,0x8e00
8e000122:	0d52      	jalr r3
8e000124:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000128:	2316      	lsl r1,r0,0x18
8e00012a:	2706      	lsr r1,r1,0x18
8e00012c:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000130:	2014      	strb r1,[r0]
8e000132:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000136:	0093      	add r0,r0,1
8e000138:	2003      	mov r1,0x0
8e00013a:	2014      	strb r1,[r0]
8e00013c:	108b 0032 	mov r0,0x384
8e000140:	000b 1002 	movt r0,0x0
8e000144:	0044      	ldr r0,[r0]
8e000146:	1e5c 0500 	str r0,[fp,-0x4]
8e00014a:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00014e:	634c 0001 	ldr r3,[r0,+0xe]
8e000152:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000156:	20e2      	mov r1,r0
8e000158:	200b 1002 	movt r1,0x0
8e00015c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000160:	041a      	add r0,r1,r0
8e000162:	000b 1002 	movt r0,0x0
8e000166:	5dcc 0500 	ldr r2,[fp,-0x3]
8e00016a:	20e2      	mov r1,r0
8e00016c:	0ce2      	mov r0,r3
8e00016e:	7f8b 00e2 	mov r3,0xefc
8e000172:	600b 18e2 	movt r3,0x8e00
8e000176:	0d52      	jalr r3
8e000178:	1d3c 0500 	strh r0,[fp,-0x2]
8e00017c:	22e0      	b 8e0001c0 <bjk_aux_sout+0x12c>
8e00017e:	4003      	mov r2,0x0
8e000180:	2003      	mov r1,0x0
8e000182:	1763      	mov r0,0xbb
8e000184:	610b 0172 	mov r3,0x1708
8e000188:	600b 18e2 	movt r3,0x8e00
8e00018c:	0d52      	jalr r3
8e00018e:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000192:	634c 0001 	ldr r3,[r0,+0xe]
8e000196:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e00019a:	20e2      	mov r1,r0
8e00019c:	200b 1002 	movt r1,0x0
8e0001a0:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0001a4:	041a      	add r0,r1,r0
8e0001a6:	000b 1002 	movt r0,0x0
8e0001aa:	5dcc 0500 	ldr r2,[fp,-0x3]
8e0001ae:	20e2      	mov r1,r0
8e0001b0:	0ce2      	mov r0,r3
8e0001b2:	7f8b 00e2 	mov r3,0xefc
8e0001b6:	600b 18e2 	movt r3,0x8e00
8e0001ba:	0d52      	jalr r3
8e0001bc:	1d3c 0500 	strh r0,[fp,-0x2]
8e0001c0:	1d2c 0500 	ldrh r0,[fp,-0x2]
8e0001c4:	2033      	sub r1,r0,0
8e0001c6:	dc00      	beq 8e00017e <bjk_aux_sout+0xea>
8e0001c8:	02e0      	b 8e0001cc <bjk_aux_sout+0x138>
8e0001ca:	01a2      	nop
8e0001cc:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0001d0:	b41b 2404 	add sp,sp,32
8e0001d4:	194f 0402 	rts

8e0001d8 <bjk_aux_iout>:
8e0001d8:	d7fc 2700 	strd lr,[sp],-0x7
8e0001dc:	96dc 0401 	str r4,[sp,+0xd]
8e0001e0:	f41b 2407 	add fp,sp,56
8e0001e4:	1cdc 0501 	str r0,[fp,-0x9]
8e0001e8:	3d5c 0501 	str r1,[fp,-0xa]
8e0001ec:	5ddc 0501 	str r2,[fp,-0xb]
8e0001f0:	14ef 0402 	mov r0,sp
8e0001f4:	80e2      	mov r4,r0
8e0001f6:	108b 0032 	mov r0,0x384
8e0001fa:	000b 1002 	movt r0,0x0
8e0001fe:	0044      	ldr r0,[r0]
8e000200:	02cc 0001 	ldr r0,[r0,+0xd]
8e000204:	2033      	sub r1,r0,0
8e000206:	0410      	bne 8e00020e <bjk_aux_iout+0x36>
8e000208:	0003      	mov r0,0x0
8e00020a:	8be8 0000 	b 8e000320 <bjk_aux_iout+0x148>
8e00020e:	00c3      	mov r0,0x6
8e000210:	1f3c 0500 	strh r0,[fp,-0x6]
8e000214:	1f2c 0500 	ldrh r0,[fp,-0x6]
8e000218:	20e2      	mov r1,r0
8e00021a:	2793      	add r1,r1,-1
8e00021c:	3e5c 0500 	str r1,[fp,-0x4]
8e000220:	40ef 4002 	mov r18,r0
8e000224:	600b 4002 	mov r19,0x0
8e000228:	2baf 0806 	lsr r1,r18,0x1d
8e00022c:	ec7f 4806 	lsl r23,r19,0x3
8e000230:	e7ff 410a 	orr r23,r1,r23
8e000234:	c87f 4806 	lsl r22,r18,0x3
8e000238:	00ef 4002 	mov r16,r0
8e00023c:	200b 4002 	mov r17,0x0
8e000240:	23af 0806 	lsr r1,r16,0x1d
8e000244:	a47f 4806 	lsl r21,r17,0x3
8e000248:	a6ff 410a 	orr r21,r1,r21
8e00024c:	807f 4806 	lsl r20,r16,0x3
8e000250:	039b 0000 	add r0,r0,7
8e000254:	0066      	lsr r0,r0,0x3
8e000256:	0076      	lsl r0,r0,0x3
8e000258:	b43f 240a 	sub sp,sp,r0
8e00025c:	141b 0401 	add r0,sp,8
8e000260:	0013      	add r0,r0,0
8e000262:	1edc 0500 	str r0,[fp,-0x5]
8e000266:	1d4c 0501 	ldr r0,[fp,-0xa]
8e00026a:	2316      	lsl r1,r0,0x18
8e00026c:	2706      	lsr r1,r1,0x18
8e00026e:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000272:	2014      	strb r1,[r0]
8e000274:	1dcc 0501 	ldr r0,[fp,-0xb]
8e000278:	2316      	lsl r1,r0,0x18
8e00027a:	2706      	lsr r1,r1,0x18
8e00027c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000280:	2094      	strb r1,[r0,0x1]
8e000282:	1e1b 04fb 	add r0,fp,-36
8e000286:	1f5c 0500 	str r0,[fp,-0x6]
8e00028a:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00028e:	2004      	ldrb r1,[r0]
8e000290:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000294:	2114      	strb r1,[r0,0x2]
8e000296:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00029a:	2084      	ldrb r1,[r0,0x1]
8e00029c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0002a0:	2194      	strb r1,[r0,0x3]
8e0002a2:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0002a6:	2104      	ldrb r1,[r0,0x2]
8e0002a8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0002ac:	2214      	strb r1,[r0,0x4]
8e0002ae:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0002b2:	2184      	ldrb r1,[r0,0x3]
8e0002b4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0002b8:	2294      	strb r1,[r0,0x5]
8e0002ba:	108b 0032 	mov r0,0x384
8e0002be:	000b 1002 	movt r0,0x0
8e0002c2:	0044      	ldr r0,[r0]
8e0002c4:	1fdc 0500 	str r0,[fp,-0x7]
8e0002c8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0002cc:	034c 0001 	ldr r0,[r0,+0xe]
8e0002d0:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e0002d4:	5ecc 0500 	ldr r2,[fp,-0x5]
8e0002d8:	7f8b 00e2 	mov r3,0xefc
8e0002dc:	600b 18e2 	movt r3,0x8e00
8e0002e0:	0d52      	jalr r3
8e0002e2:	1ebc 0500 	strh r0,[fp,-0x5]
8e0002e6:	18e0      	b 8e000316 <bjk_aux_iout+0x13e>
8e0002e8:	4003      	mov r2,0x0
8e0002ea:	2003      	mov r1,0x0
8e0002ec:	1763      	mov r0,0xbb
8e0002ee:	610b 0172 	mov r3,0x1708
8e0002f2:	600b 18e2 	movt r3,0x8e00
8e0002f6:	0d52      	jalr r3
8e0002f8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0002fc:	034c 0001 	ldr r0,[r0,+0xe]
8e000300:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000304:	5ecc 0500 	ldr r2,[fp,-0x5]
8e000308:	7f8b 00e2 	mov r3,0xefc
8e00030c:	600b 18e2 	movt r3,0x8e00
8e000310:	0d52      	jalr r3
8e000312:	1ebc 0500 	strh r0,[fp,-0x5]
8e000316:	1eac 0500 	ldrh r0,[fp,-0x5]
8e00031a:	2033      	sub r1,r0,0
8e00031c:	e600      	beq 8e0002e8 <bjk_aux_iout+0x110>
8e00031e:	0023      	mov r0,0x1
8e000320:	b0ef 2002 	mov sp,r4
8e000324:	20b3      	sub r1,r0,1
8e000326:	bc1b 24f9 	add sp,fp,-56
8e00032a:	d7ec 2400 	ldrd lr,[sp,+0x7]
8e00032e:	96cc 0401 	ldr r4,[sp,+0xd]
8e000332:	b41b 2407 	add sp,sp,56
8e000336:	194f 0402 	rts
8e00033a:	01a2      	nop

8e00033c <bj_get_aligment>:
8e00033c:	20e3      	mov r1,0x7
8e00033e:	20da      	and r1,r0,r1
8e000340:	0900      	beq 8e000352 <bj_get_aligment+0x16>
8e000342:	2063      	mov r1,0x3
8e000344:	20da      	and r1,r0,r1
8e000346:	0800      	beq 8e000356 <bj_get_aligment+0x1a>
8e000348:	03f6      	lsl r0,r0,0x1f
8e00034a:	0103      	mov r0,0x8
8e00034c:	2203      	mov r1,0x10
8e00034e:	0472      	movgte r0,r1
8e000350:	04e0      	b 8e000358 <bj_get_aligment+0x1c>
8e000352:	0803      	mov r0,0x40
8e000354:	02e0      	b 8e000358 <bj_get_aligment+0x1c>
8e000356:	0403      	mov r0,0x20
8e000358:	194f 0402 	rts

8e00035c <bj_memset>:
8e00035c:	2716      	lsl r1,r1,0x18
8e00035e:	2706      	lsr r1,r1,0x18
8e000360:	6003      	mov r3,0x0
8e000362:	8d3f 200a 	sub ip,r3,r2
8e000366:	0400      	beq 8e00036e <bj_memset+0x12>
8e000368:	2191      	strb r1,[r0,r3]
8e00036a:	6c93      	add r3,r3,1
8e00036c:	fbe0      	b 8e000362 <bj_memset+0x6>
8e00036e:	194f 0402 	rts
8e000372:	01a2      	nop

8e000374 <bj_memcpy>:
8e000374:	6003      	mov r3,0x0
8e000376:	8d3f 200a 	sub ip,r3,r2
8e00037a:	0700      	beq 8e000388 <bj_memcpy+0x14>
8e00037c:	8589 2000 	ldrb ip,[r1,+r3]
8e000380:	8199 2000 	strb ip,[r0,+r3]
8e000384:	6c93      	add r3,r3,1
8e000386:	f8e0      	b 8e000376 <bj_memcpy+0x2>
8e000388:	194f 0402 	rts

8e00038c <bj_memmove>:
8e00038c:	20bf 400a 	sub r17,r0,r1
8e000390:	04ef 4002 	mov r16,r1
8e000394:	88ef 2002 	mov ip,r2
8e000398:	0620      	bgtu 8e0003a4 <bj_memmove+0x18>
8e00039a:	6e8b 0032 	mov r3,0x374
8e00039e:	600b 18e2 	movt r3,0x8e00
8e0003a2:	0d42      	jr r3
8e0003a4:	011a      	add r0,r0,r2
8e0003a6:	28e2      	mov r1,r2
8e0003a8:	413a      	sub r2,r0,r2
8e0003aa:	2793      	add r1,r1,-1
8e0003ac:	67b3      	sub r3,r1,-1
8e0003ae:	0500      	beq 8e0003b8 <bj_memmove+0x2c>
8e0003b0:	6089 0800 	ldrb r3,[r16,+r1]
8e0003b4:	6891      	strb r3,[r2,r1]
8e0003b6:	fae0      	b 8e0003aa <bj_memmove+0x1e>
8e0003b8:	023f 008a 	sub r0,r0,ip
8e0003bc:	194f 0402 	rts

8e0003c0 <bj_strlen>:
8e0003c0:	f75c 2700 	str fp,[sp],-0x6
8e0003c4:	f4ef 2402 	mov fp,sp
8e0003c8:	1ddc 0400 	str r0,[fp,+0x3]
8e0003cc:	0003      	mov r0,0x0
8e0003ce:	1dbc 0401 	strh r0,[fp,+0xb]
8e0003d2:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0003d6:	2033      	sub r1,r0,0
8e0003d8:	0810      	bne 8e0003e8 <bj_strlen+0x28>
8e0003da:	0003      	mov r0,0x0
8e0003dc:	10e0      	b 8e0003fc <bj_strlen+0x3c>
8e0003de:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0003e2:	0093      	add r0,r0,1
8e0003e4:	1dbc 0401 	strh r0,[fp,+0xb]
8e0003e8:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0003ec:	3dcc 0400 	ldr r1,[fp,+0x3]
8e0003f0:	041a      	add r0,r1,r0
8e0003f2:	0004      	ldrb r0,[r0]
8e0003f4:	2033      	sub r1,r0,0
8e0003f6:	f410      	bne 8e0003de <bj_strlen+0x1e>
8e0003f8:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0003fc:	f74c 2400 	ldr fp,[sp,+0x6]
8e000400:	b41b 2403 	add sp,sp,24
8e000404:	194f 0402 	rts

8e000408 <bj_extnl_ram_load_data_fill>:
8e000408:	f75c 2700 	str fp,[sp],-0x6
8e00040c:	f4ef 2402 	mov fp,sp
8e000410:	1ddc 0400 	str r0,[fp,+0x3]
8e000414:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000418:	02c4      	ldr r0,[r0,0x5]
8e00041a:	1edc 0400 	str r0,[fp,+0x5]
8e00041e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000422:	2344      	ldr r1,[r0,0x6]
8e000424:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000428:	243a      	sub r1,r1,r0
8e00042a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00042e:	215c 0001 	str r1,[r0,+0xa]
8e000432:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000436:	23c4      	ldr r1,[r0,0x7]
8e000438:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00043c:	243a      	sub r1,r1,r0
8e00043e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000442:	21dc 0001 	str r1,[r0,+0xb]
8e000446:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00044a:	204c 0001 	ldr r1,[r0,+0x8]
8e00044e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000452:	243a      	sub r1,r1,r0
8e000454:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000458:	225c 0001 	str r1,[r0,+0xc]
8e00045c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000460:	20cc 0001 	ldr r1,[r0,+0x9]
8e000464:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000468:	243a      	sub r1,r1,r0
8e00046a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00046e:	22dc 0001 	str r1,[r0,+0xd]
8e000472:	01a2      	nop
8e000474:	f74c 2400 	ldr fp,[sp,+0x6]
8e000478:	b41b 2403 	add sp,sp,24
8e00047c:	194f 0402 	rts

8e000480 <bjk_glb_init>:
8e000480:	d77c 2700 	strd lr,[sp],-0x6
8e000484:	96fc 0400 	strd r4,[sp,+0x5]
8e000488:	f41b 2406 	add fp,sp,48
8e00048c:	a112      	movfs r5,config
8e00048e:	000b 00b2 	mov r0,0xb00
8e000492:	000b 18e2 	movt r0,0x8e00
8e000496:	9fcb 0ff2 	mov r4,0xfffe
8e00049a:	9e2b 1ff2 	movt r4,0xfff1
8e00049e:	0152      	jalr r0
8e0004a0:	070b 0262 	mov r0,0x2638
8e0004a4:	000b 18e2 	movt r0,0x8e00
8e0004a8:	9fcb 0ff2 	mov r4,0xfffe
8e0004ac:	9e2b 1ff2 	movt r4,0xfff1
8e0004b0:	0152      	jalr r0
8e0004b2:	118b 0092 	mov r0,0x98c
8e0004b6:	000b 18e2 	movt r0,0x8e00
8e0004ba:	9fcb 0ff2 	mov r4,0xfffe
8e0004be:	9e2b 1ff2 	movt r4,0xfff1
8e0004c2:	0152      	jalr r0
8e0004c4:	1ddc 0500 	str r0,[fp,-0x3]
8e0004c8:	580b 0012 	mov r2,0x1c0
8e0004cc:	2003      	mov r1,0x0
8e0004ce:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0004d2:	6b8b 0032 	mov r3,0x35c
8e0004d6:	600b 18e2 	movt r3,0x8e00
8e0004da:	9fcb 0ff2 	mov r4,0xfffe
8e0004de:	9e2b 1ff2 	movt r4,0xfff1
8e0004e2:	0d52      	jalr r3
8e0004e4:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0004e8:	2003      	mov r1,0x0
8e0004ea:	22dc 0001 	str r1,[r0,+0xd]
8e0004ee:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0004f2:	2003      	mov r1,0x0
8e0004f4:	235c 0001 	str r1,[r0,+0xe]
8e0004f8:	110b 0032 	mov r0,0x388
8e0004fc:	000b 1002 	movt r0,0x0
8e000500:	1e5c 0500 	str r0,[fp,-0x4]
8e000504:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000508:	1c5c 0501 	str r0,[fp,-0x8]
8e00050c:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000510:	2403      	mov r1,0x20
8e000512:	2034      	strh r1,[r0]
8e000514:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000518:	2103      	mov r1,0x8
8e00051a:	20b4      	strh r1,[r0,0x1]
8e00051c:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000520:	2083      	mov r1,0x4
8e000522:	2134      	strh r1,[r0,0x2]
8e000524:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000528:	2043      	mov r1,0x2
8e00052a:	2314      	strb r1,[r0,0x6]
8e00052c:	000b 0002 	mov r0,0x0
8e000530:	000b 18f2 	movt r0,0x8f00
8e000534:	2044      	ldr r1,[r0]
8e000536:	1bab 0cc2 	mov r0,0xccdd
8e00053a:	176b 1aa2 	movt r0,0xaabb
8e00053e:	443a      	sub r2,r1,r0
8e000540:	1200      	beq 8e000564 <bjk_glb_init+0xe4>
8e000542:	100b 0042 	mov r0,0x480
8e000546:	000b 18e2 	movt r0,0x8e00
8e00054a:	280b 0272 	mov r1,0x2740
8e00054e:	200b 18e2 	movt r1,0x8e00
8e000552:	588b 0092 	mov r2,0x9c4
8e000556:	400b 18e2 	movt r2,0x8e00
8e00055a:	9fcb 0ff2 	mov r4,0xfffe
8e00055e:	9e2b 1ff2 	movt r4,0xfff1
8e000562:	0952      	jalr r2
8e000564:	000b 0002 	mov r0,0x0
8e000568:	000b 18f2 	movt r0,0x8f00
8e00056c:	200b 0002 	mov r1,0x0
8e000570:	200b 18f2 	movt r1,0x8f00
8e000574:	21d4      	str r1,[r0,0x3]
8e000576:	0003      	mov r0,0x0
8e000578:	1cbc 0501 	strh r0,[fp,-0x9]
8e00057c:	051f 0032 	movfs r0,coreid
8e000580:	1cbc 0501 	strh r0,[fp,-0x9]
8e000584:	1cac 0501 	ldrh r0,[fp,-0x9]
8e000588:	1dbc 0501 	strh r0,[fp,-0xb]
8e00058c:	4103      	mov r2,0x8
8e00058e:	2003      	mov r1,0x0
8e000590:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000594:	6b8b 0032 	mov r3,0x35c
8e000598:	600b 18e2 	movt r3,0x8e00
8e00059c:	9fcb 0ff2 	mov r4,0xfffe
8e0005a0:	9e2b 1ff2 	movt r4,0xfff1
8e0005a4:	0d52      	jalr r3
8e0005a6:	5e4c 0500 	ldr r2,[fp,-0x4]
8e0005aa:	000b 0002 	mov r0,0x0
8e0005ae:	000b 18f2 	movt r0,0x8f00
8e0005b2:	01e4      	ldrd r0,[r0,0x3]
8e0005b4:	0874      	strd r0,[r2]
8e0005b6:	1dac 0501 	ldrh r0,[fp,-0xb]
8e0005ba:	00c6      	lsr r0,r0,0x6
8e0005bc:	000b 1002 	movt r0,0x0
8e0005c0:	20e2      	mov r1,r0
8e0005c2:	07e3      	mov r0,0x3f
8e0005c4:	045a      	and r0,r1,r0
8e0005c6:	310b 0032 	mov r1,0x388
8e0005ca:	200b 1002 	movt r1,0x0
8e0005ce:	2424      	ldrh r1,[r1]
8e0005d0:	00ba      	sub r0,r0,r1
8e0005d2:	40e2      	mov r2,r0
8e0005d4:	400b 1002 	movt r2,0x0
8e0005d8:	110b 0032 	mov r0,0x388
8e0005dc:	000b 1002 	movt r0,0x0
8e0005e0:	0304      	ldrb r0,[r0,0x6]
8e0005e2:	20e2      	mov r1,r0
8e0005e4:	0023      	mov r0,0x1
8e0005e6:	00aa      	lsl r0,r0,r1
8e0005e8:	20e2      	mov r1,r0
8e0005ea:	200b 1002 	movt r1,0x0
8e0005ee:	600b 0002 	mov r3,0x0
8e0005f2:	610b 1002 	movt r3,0x8
8e0005f6:	0512      	movfs r0,status
8e0005f8:	0392      	gid
8e0005fa:	811f 2002 	movfs ip,config
8e0005fe:	91ff 240a 	orr ip,ip,r3
8e000602:	810f 2002 	movts config,ip
8e000606:	0192      	gie
8e000608:	01eb 4ef2 	mov r16,0xef0f
8e00060c:	1feb 5ff2 	movt r16,0xffff
8e000610:	6512      	movfs r3,status
8e000612:	6c0a      	eor r3,r3,r0
8e000614:	6c5f 010a 	and r3,r3,r16
8e000618:	6c0a      	eor r3,r3,r0
8e00061a:	6502      	movts status,r3
8e00061c:	08a7      	fmul r0,r2,r1
8e00061e:	20e2      	mov r1,r0
8e000620:	200b 1002 	movt r1,0x0
8e000624:	5dac 0501 	ldrh r2,[fp,-0xb]
8e000628:	07e3      	mov r0,0x3f
8e00062a:	085a      	and r0,r2,r0
8e00062c:	40e2      	mov r2,r0
8e00062e:	400b 1002 	movt r2,0x0
8e000632:	110b 0032 	mov r0,0x388
8e000636:	000b 1002 	movt r0,0x0
8e00063a:	00a4      	ldrh r0,[r0,0x1]
8e00063c:	083a      	sub r0,r2,r0
8e00063e:	000b 1002 	movt r0,0x0
8e000642:	041a      	add r0,r1,r0
8e000644:	1e3c 0501 	strh r0,[fp,-0xc]
8e000648:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00064c:	3bab 0cc2 	mov r1,0xccdd
8e000650:	376b 1aa2 	movt r1,0xaabb
8e000654:	2054      	str r1,[r0]
8e000656:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00065a:	2003      	mov r1,0x0
8e00065c:	20d4      	str r1,[r0,0x1]
8e00065e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000662:	39ab 0ab2 	mov r1,0xabcd
8e000666:	312b 1672 	movt r1,0x6789
8e00066a:	225c 0001 	str r1,[r0,+0xc]
8e00066e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000672:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000676:	213c 0001 	strh r1,[r0,+0xa]
8e00067a:	1dac 0501 	ldrh r0,[fp,-0xb]
8e00067e:	00c6      	lsr r0,r0,0x6
8e000680:	20e2      	mov r1,r0
8e000682:	200b 1002 	movt r1,0x0
8e000686:	07e3      	mov r0,0x3f
8e000688:	045a      	and r0,r1,r0
8e00068a:	20e2      	mov r1,r0
8e00068c:	200b 1002 	movt r1,0x0
8e000690:	110b 0032 	mov r0,0x388
8e000694:	000b 1002 	movt r0,0x0
8e000698:	0024      	ldrh r0,[r0]
8e00069a:	043a      	sub r0,r1,r0
8e00069c:	20e2      	mov r1,r0
8e00069e:	200b 1002 	movt r1,0x0
8e0006a2:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0006a6:	223c 0001 	strh r1,[r0,+0xc]
8e0006aa:	3dac 0501 	ldrh r1,[fp,-0xb]
8e0006ae:	07e3      	mov r0,0x3f
8e0006b0:	045a      	and r0,r1,r0
8e0006b2:	20e2      	mov r1,r0
8e0006b4:	200b 1002 	movt r1,0x0
8e0006b8:	110b 0032 	mov r0,0x388
8e0006bc:	000b 1002 	movt r0,0x0
8e0006c0:	00a4      	ldrh r0,[r0,0x1]
8e0006c2:	043a      	sub r0,r1,r0
8e0006c4:	20e2      	mov r1,r0
8e0006c6:	200b 1002 	movt r1,0x0
8e0006ca:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0006ce:	22bc 0001 	strh r1,[r0,+0xd]
8e0006d2:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0006d6:	3e2c 0501 	ldrh r1,[fp,-0xc]
8e0006da:	21bc 0001 	strh r1,[r0,+0xb]
8e0006de:	1e2c 0501 	ldrh r0,[fp,-0xc]
8e0006e2:	83bb 2001 	sub ip,r0,15
8e0006e6:	0728 0001 	bgtu 8e0008f4 <bjk_glb_init+0x474>
8e0006ea:	1e2c 0501 	ldrh r0,[fp,-0xc]
8e0006ee:	0113      	add r0,r0,2
8e0006f0:	2096      	lsl r1,r0,0x4
8e0006f2:	000b 0002 	mov r0,0x0
8e0006f6:	000b 18f2 	movt r0,0x8f00
8e0006fa:	241a      	add r1,r1,r0
8e0006fc:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000700:	22dc 0001 	str r1,[r0,+0xd]
8e000704:	5e2c 0501 	ldrh r2,[fp,-0xc]
8e000708:	600b 0002 	mov r3,0x0
8e00070c:	600b 18f2 	movt r3,0x8f00
8e000710:	28e2      	mov r1,r2
8e000712:	0496      	lsl r0,r1,0x4
8e000714:	20e2      	mov r1,r0
8e000716:	0456      	lsl r0,r1,0x2
8e000718:	00ba      	sub r0,r0,r1
8e00071a:	013a      	sub r0,r0,r2
8e00071c:	0076      	lsl r0,r0,0x3
8e00071e:	0c1a      	add r0,r3,r0
8e000720:	001b 0024 	add r0,r0,288
8e000724:	2044      	ldr r1,[r0]
8e000726:	1bab 0cc2 	mov r0,0xccdd
8e00072a:	176b 1aa2 	movt r0,0xaabb
8e00072e:	043f 400a 	sub r16,r1,r0
8e000732:	2e00      	beq 8e00078e <bjk_glb_init+0x30e>
8e000734:	100b 0042 	mov r0,0x480
8e000738:	000b 18e2 	movt r0,0x8e00
8e00073c:	2b0b 0272 	mov r1,0x2758
8e000740:	200b 18e2 	movt r1,0x8e00
8e000744:	788b 0092 	mov r3,0x9c4
8e000748:	600b 18e2 	movt r3,0x8e00
8e00074c:	9fcb 0ff2 	mov r4,0xfffe
8e000750:	9e2b 1ff2 	movt r4,0xfff1
8e000754:	4512      	movfs r2,status
8e000756:	0392      	gid
8e000758:	811f 2002 	movfs ip,config
8e00075c:	928f 240a 	eor ip,ip,r5
8e000760:	925f 240a 	and ip,ip,r4
8e000764:	928f 240a 	eor ip,ip,r5
8e000768:	810f 2002 	movts config,ip
8e00076c:	0192      	gie
8e00076e:	01eb 4ef2 	mov r16,0xef0f
8e000772:	1feb 5ff2 	movt r16,0xffff
8e000776:	851f 2002 	movfs ip,status
8e00077a:	910f 240a 	eor ip,ip,r2
8e00077e:	905f 250a 	and ip,ip,r16
8e000782:	910f 240a 	eor ip,ip,r2
8e000786:	850f 2002 	movts status,ip
8e00078a:	0d52      	jalr r3
8e00078c:	17e0      	b 8e0007ba <bjk_glb_init+0x33a>
8e00078e:	0512      	movfs r0,status
8e000790:	0392      	gid
8e000792:	011f 4002 	movfs r16,config
8e000796:	028f 480a 	eor r16,r16,r5
8e00079a:	025f 480a 	and r16,r16,r4
8e00079e:	028f 480a 	eor r16,r16,r5
8e0007a2:	010f 4002 	movts config,r16
8e0007a6:	0192      	gie
8e0007a8:	21eb 0ef2 	mov r1,0xef0f
8e0007ac:	3feb 1ff2 	movt r1,0xffff
8e0007b0:	4512      	movfs r2,status
8e0007b2:	480a      	eor r2,r2,r0
8e0007b4:	48da      	and r2,r2,r1
8e0007b6:	480a      	eor r2,r2,r0
8e0007b8:	4502      	movts status,r2
8e0007ba:	5e2c 0501 	ldrh r2,[fp,-0xc]
8e0007be:	28e2      	mov r1,r2
8e0007c0:	0496      	lsl r0,r1,0x4
8e0007c2:	20e2      	mov r1,r0
8e0007c4:	0456      	lsl r0,r1,0x2
8e0007c6:	00ba      	sub r0,r0,r1
8e0007c8:	013a      	sub r0,r0,r2
8e0007ca:	0076      	lsl r0,r0,0x3
8e0007cc:	201b 0024 	add r1,r0,288
8e0007d0:	000b 0002 	mov r0,0x0
8e0007d4:	000b 18f2 	movt r0,0x8f00
8e0007d8:	041a      	add r0,r1,r0
8e0007da:	1fdc 0500 	str r0,[fp,-0x7]
8e0007de:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0007e2:	201b 0001 	add r1,r0,8
8e0007e6:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0007ea:	235c 0001 	str r1,[r0,+0xe]
8e0007ee:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0007f2:	834c 2001 	ldr ip,[r0,+0xe]
8e0007f6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0007fa:	001b 0009 	add r0,r0,72
8e0007fe:	6003      	mov r3,0x0
8e000800:	40e2      	mov r2,r0
8e000802:	258b 0012 	mov r1,0x12c
8e000806:	10ef 0402 	mov r0,ip
8e00080a:	988b 20b2 	mov ip,0xbc4
8e00080e:	800b 38e2 	movt ip,0x8e00
8e000812:	9fcb 0ff2 	mov r4,0xfffe
8e000816:	9e2b 1ff2 	movt r4,0xfff1
8e00081a:	115f 0402 	jalr ip
8e00081e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000822:	02cc 0001 	ldr r0,[r0,+0xd]
8e000826:	2044      	ldr r1,[r0]
8e000828:	1bab 0cc2 	mov r0,0xccdd
8e00082c:	176b 1aa2 	movt r0,0xaabb
8e000830:	643a      	sub r3,r1,r0
8e000832:	1200      	beq 8e000856 <bjk_glb_init+0x3d6>
8e000834:	100b 0042 	mov r0,0x480
8e000838:	000b 18e2 	movt r0,0x8e00
8e00083c:	2e0b 0272 	mov r1,0x2770
8e000840:	200b 18e2 	movt r1,0x8e00
8e000844:	588b 0092 	mov r2,0x9c4
8e000848:	400b 18e2 	movt r2,0x8e00
8e00084c:	9fcb 0ff2 	mov r4,0xfffe
8e000850:	9e2b 1ff2 	movt r4,0xfff1
8e000854:	0952      	jalr r2
8e000856:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00085a:	02cc 0001 	ldr r0,[r0,+0xd]
8e00085e:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000862:	2134      	strh r1,[r0,0x2]
8e000864:	01a2      	nop
8e000866:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00086a:	02cc 0001 	ldr r0,[r0,+0xd]
8e00086e:	0124      	ldrh r0,[r0,0x2]
8e000870:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000874:	843f 200a 	sub ip,r1,r0
8e000878:	f710      	bne 8e000866 <bjk_glb_init+0x3e6>
8e00087a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00087e:	02cc 0001 	ldr r0,[r0,+0xd]
8e000882:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000886:	2154      	str r1,[r0,0x2]
8e000888:	01a2      	nop
8e00088a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00088e:	02cc 0001 	ldr r0,[r0,+0xd]
8e000892:	2144      	ldr r1,[r0,0x2]
8e000894:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000898:	043f 400a 	sub r16,r1,r0
8e00089c:	f710      	bne 8e00088a <bjk_glb_init+0x40a>
8e00089e:	0423      	mov r0,0x21
8e0008a0:	1d9c 0502 	strb r0,[fp,-0x13]
8e0008a4:	108b 0032 	mov r0,0x384
8e0008a8:	000b 1002 	movt r0,0x0
8e0008ac:	0044      	ldr r0,[r0]
8e0008ae:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008b2:	1cdc 0501 	str r0,[fp,-0x9]
8e0008b6:	1ccc 0501 	ldr r0,[fp,-0x9]
8e0008ba:	2033      	sub r1,r0,0
8e0008bc:	0d00      	beq 8e0008d6 <bjk_glb_init+0x456>
8e0008be:	1ccc 0501 	ldr r0,[fp,-0x9]
8e0008c2:	3d8c 0502 	ldrb r1,[fp,-0x13]
8e0008c6:	2314      	strb r1,[r0,0x6]
8e0008c8:	1ccc 0501 	ldr r0,[fp,-0x9]
8e0008cc:	0304      	ldrb r0,[r0,0x6]
8e0008ce:	3d8c 0502 	ldrb r1,[fp,-0x13]
8e0008d2:	443a      	sub r2,r1,r0
8e0008d4:	fa10      	bne 8e0008c8 <bjk_glb_init+0x448>
8e0008d6:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0008da:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008de:	2003      	mov r1,0x0
8e0008e0:	2394      	strb r1,[r0,0x7]
8e0008e2:	01a2      	nop
8e0008e4:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0008e8:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008ec:	0384      	ldrb r0,[r0,0x7]
8e0008ee:	6033      	sub r3,r0,0
8e0008f0:	fa10      	bne 8e0008e4 <bjk_glb_init+0x464>
8e0008f2:	18e0      	b 8e000922 <bjk_glb_init+0x4a2>
8e0008f4:	0512      	movfs r0,status
8e0008f6:	0392      	gid
8e0008f8:	811f 2002 	movfs ip,config
8e0008fc:	928f 240a 	eor ip,ip,r5
8e000900:	925f 240a 	and ip,ip,r4
8e000904:	928f 240a 	eor ip,ip,r5
8e000908:	810f 2002 	movts config,ip
8e00090c:	0192      	gie
8e00090e:	01eb 4ef2 	mov r16,0xef0f
8e000912:	1feb 5ff2 	movt r16,0xffff
8e000916:	2512      	movfs r1,status
8e000918:	240a      	eor r1,r1,r0
8e00091a:	245f 010a 	and r1,r1,r16
8e00091e:	240a      	eor r1,r1,r0
8e000920:	2502      	movts status,r1
8e000922:	01a2      	nop
8e000924:	9fcb 0ff2 	mov r4,0xfffe
8e000928:	9e2b 1ff2 	movt r4,0xfff1
8e00092c:	d76c 2400 	ldrd lr,[sp,+0x6]
8e000930:	96ec 0400 	ldrd r4,[sp,+0x5]
8e000934:	b41b 2406 	add sp,sp,48
8e000938:	194f 0402 	rts

8e00093c <bjk_glb_finish>:
8e00093c:	f65c 2700 	str fp,[sp],-0x4
8e000940:	f4ef 2402 	mov fp,sp
8e000944:	1e2b 0ff2 	mov r0,0xfff1
8e000948:	1f9c 0401 	strb r0,[fp,+0xf]
8e00094c:	108b 0032 	mov r0,0x384
8e000950:	000b 1002 	movt r0,0x0
8e000954:	0044      	ldr r0,[r0]
8e000956:	02cc 0001 	ldr r0,[r0,+0xd]
8e00095a:	1d5c 0400 	str r0,[fp,+0x2]
8e00095e:	1d4c 0400 	ldr r0,[fp,+0x2]
8e000962:	2033      	sub r1,r0,0
8e000964:	0d00      	beq 8e00097e <bjk_glb_finish+0x42>
8e000966:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00096a:	3f8c 0401 	ldrb r1,[fp,+0xf]
8e00096e:	2314      	strb r1,[r0,0x6]
8e000970:	1d4c 0400 	ldr r0,[fp,+0x2]
8e000974:	0304      	ldrb r0,[r0,0x6]
8e000976:	3f8c 0401 	ldrb r1,[fp,+0xf]
8e00097a:	443a      	sub r2,r1,r0
8e00097c:	fa10      	bne 8e000970 <bjk_glb_finish+0x34>
8e00097e:	01a2      	nop
8e000980:	f64c 2400 	ldr fp,[sp,+0x4]
8e000984:	b41b 2402 	add sp,sp,16
8e000988:	194f 0402 	rts

8e00098c <bjk_get_first_glb_sys>:
8e00098c:	d4fc 2700 	strd lr,[sp],-0x1
8e000990:	f41b 2401 	add fp,sp,8
8e000994:	180b 0012 	mov r0,0x1c0
8e000998:	3f8b 01f2 	mov r1,0x1ffc
8e00099c:	200b 18e2 	movt r1,0x8e00
8e0009a0:	0552      	jalr r1
8e0009a2:	20e2      	mov r1,r0
8e0009a4:	108b 0032 	mov r0,0x384
8e0009a8:	000b 1002 	movt r0,0x0
8e0009ac:	2054      	str r1,[r0]
8e0009ae:	108b 0032 	mov r0,0x384
8e0009b2:	000b 1002 	movt r0,0x0
8e0009b6:	0044      	ldr r0,[r0]
8e0009b8:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0009bc:	b41b 2401 	add sp,sp,8
8e0009c0:	194f 0402 	rts

8e0009c4 <bjk_abort>:
8e0009c4:	d67c 2700 	strd lr,[sp],-0x4
8e0009c8:	f41b 2404 	add fp,sp,32
8e0009cc:	1edc 0500 	str r0,[fp,-0x5]
8e0009d0:	3f5c 0500 	str r1,[fp,-0x6]
8e0009d4:	1feb 0ff2 	mov r0,0xffff
8e0009d8:	1feb 1ff2 	movt r0,0xffff
8e0009dc:	1cbc 0500 	strh r0,[fp,-0x1]
8e0009e0:	0003      	mov r0,0x0
8e0009e2:	1d5c 0500 	str r0,[fp,-0x2]
8e0009e6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0009ea:	2033      	sub r1,r0,0
8e0009ec:	0d00      	beq 8e000a06 <bjk_abort+0x42>
8e0009ee:	0283      	mov r0,0x14
8e0009f0:	1cbc 0500 	strh r0,[fp,-0x1]
8e0009f4:	108b 0032 	mov r0,0x384
8e0009f8:	000b 1002 	movt r0,0x0
8e0009fc:	0044      	ldr r0,[r0]
8e0009fe:	001b 002d 	add r0,r0,360
8e000a02:	1d5c 0500 	str r0,[fp,-0x2]
8e000a06:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000a0a:	4033      	sub r2,r0,0
8e000a0c:	1200      	beq 8e000a30 <bjk_abort+0x6c>
8e000a0e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000a12:	0216      	lsl r0,r0,0x10
8e000a14:	020e      	asr r0,r0,0x10
8e000a16:	2033      	sub r1,r0,0
8e000a18:	0c90      	blte 8e000a30 <bjk_abort+0x6c>
8e000a1a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000a1e:	0216      	lsl r0,r0,0x10
8e000a20:	020e      	asr r0,r0,0x10
8e000a22:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000a26:	4d8b 0142 	mov r2,0x146c
8e000a2a:	400b 18e2 	movt r2,0x8e00
8e000a2e:	0952      	jalr r2
8e000a30:	108b 0032 	mov r0,0x384
8e000a34:	000b 1002 	movt r0,0x0
8e000a38:	0044      	ldr r0,[r0]
8e000a3a:	1ddc 0500 	str r0,[fp,-0x3]
8e000a3e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000a42:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000a46:	21d4      	str r1,[r0,0x3]
8e000a48:	108b 0032 	mov r0,0x384
8e000a4c:	000b 1002 	movt r0,0x0
8e000a50:	0044      	ldr r0,[r0]
8e000a52:	02cc 0001 	ldr r0,[r0,+0xd]
8e000a56:	1e5c 0500 	str r0,[fp,-0x4]
8e000a5a:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a5e:	4033      	sub r2,r0,0
8e000a60:	1600      	beq 8e000a8c <bjk_abort+0xc8>
8e000a62:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a66:	2044      	ldr r1,[r0]
8e000a68:	1bab 0cc2 	mov r0,0xccdd
8e000a6c:	176b 1aa2 	movt r0,0xaabb
8e000a70:	443a      	sub r2,r1,r0
8e000a72:	0d10      	bne 8e000a8c <bjk_abort+0xc8>
8e000a74:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a78:	3e2b 0ff2 	mov r1,0xfff1
8e000a7c:	2314      	strb r1,[r0,0x6]
8e000a7e:	01a2      	nop
8e000a80:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a84:	0304      	ldrb r0,[r0,0x6]
8e000a86:	20bb 001e 	sub r1,r0,241
8e000a8a:	fb10      	bne 8e000a80 <bjk_abort+0xbc>
8e000a8c:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000a90:	c0ef e002 	mov r62,r0
8e000a94:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000a98:	e0ef e002 	mov r63,r0
8e000a9c:	0392      	gid
8e000a9e:	0fe2      	trap 0x3
8e000aa0:	0912      	movfs r0,pc
8e000aa2:	0152      	jalr r0
8e000aa4:	01a2      	nop
8e000aa6:	d66c 2400 	ldrd lr,[sp,+0x4]
8e000aaa:	b41b 2404 	add sp,sp,32
8e000aae:	194f 0402 	rts
8e000ab2:	01a2      	nop

8e000ab4 <abort>:
8e000ab4:	d57c 2700 	strd lr,[sp],-0x2
8e000ab8:	f41b 2402 	add fp,sp,16

8e000abc <ck2_abort>:
8e000abc:	b78b e0a2 	mov r61,0xabc
8e000ac0:	a00b f8e2 	movt r61,0x8e00
8e000ac4:	14ef 1c02 	mov r0,r61
8e000ac8:	1cdc 0500 	str r0,[fp,-0x1]
8e000acc:	380b 0272 	mov r1,0x27c0
8e000ad0:	200b 18e2 	movt r1,0x8e00
8e000ad4:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ad8:	588b 0092 	mov r2,0x9c4
8e000adc:	400b 18e2 	movt r2,0x8e00
8e000ae0:	0952      	jalr r2
8e000ae2:	168b 00a2 	mov r0,0xab4
8e000ae6:	000b 18e2 	movt r0,0x8e00
8e000aea:	260b 0272 	mov r1,0x2730
8e000aee:	200b 18e2 	movt r1,0x8e00
8e000af2:	588b 0092 	mov r2,0x9c4
8e000af6:	400b 18e2 	movt r2,0x8e00
8e000afa:	0952      	jalr r2
8e000afc:	00e0      	b 8e000afc <ck2_abort+0x40>
8e000afe:	01a2      	nop

8e000b00 <bjk_set_irq0_handler>:
8e000b00:	f65c 2700 	str fp,[sp],-0x4
8e000b04:	f4ef 2402 	mov fp,sp
8e000b08:	0003      	mov r0,0x0
8e000b0a:	1ddc 0400 	str r0,[fp,+0x3]
8e000b0e:	008b 0022 	mov r0,0x204
8e000b12:	000b 1002 	movt r0,0x0
8e000b16:	0026      	lsr r0,r0,0x1
8e000b18:	2116      	lsl r1,r0,0x8
8e000b1a:	1d03      	mov r0,0xe8
8e000b1c:	247a      	orr r1,r1,r0
8e000b1e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000b22:	2054      	str r1,[r0]
8e000b24:	01a2      	nop
8e000b26:	f64c 2400 	ldr fp,[sp,+0x4]
8e000b2a:	b41b 2402 	add sp,sp,16
8e000b2e:	194f 0402 	rts
8e000b32:	01a2      	nop

8e000b34 <bj_host_init>:
8e000b34:	d4fc 2700 	strd lr,[sp],-0x1
8e000b38:	f41b 2401 	add fp,sp,8
8e000b3c:	068b 00b2 	mov r0,0xb34
8e000b40:	000b 18e2 	movt r0,0x8e00
8e000b44:	3d0b 0262 	mov r1,0x26e8
8e000b48:	200b 18e2 	movt r1,0x8e00
8e000b4c:	588b 0092 	mov r2,0x9c4
8e000b50:	400b 18e2 	movt r2,0x8e00
8e000b54:	0952      	jalr r2
8e000b56:	01a2      	nop
8e000b58:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b5c:	b41b 2401 	add sp,sp,8
8e000b60:	194f 0402 	rts

8e000b64 <bj_host_run>:
8e000b64:	d4fc 2700 	strd lr,[sp],-0x1
8e000b68:	f41b 2401 	add fp,sp,8
8e000b6c:	0c8b 00b2 	mov r0,0xb64
8e000b70:	000b 18e2 	movt r0,0x8e00
8e000b74:	200b 0272 	mov r1,0x2700
8e000b78:	200b 18e2 	movt r1,0x8e00
8e000b7c:	588b 0092 	mov r2,0x9c4
8e000b80:	400b 18e2 	movt r2,0x8e00
8e000b84:	0952      	jalr r2
8e000b86:	01a2      	nop
8e000b88:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b8c:	b41b 2401 	add sp,sp,8
8e000b90:	194f 0402 	rts

8e000b94 <bj_host_finish>:
8e000b94:	d4fc 2700 	strd lr,[sp],-0x1
8e000b98:	f41b 2401 	add fp,sp,8
8e000b9c:	128b 00b2 	mov r0,0xb94
8e000ba0:	000b 18e2 	movt r0,0x8e00
8e000ba4:	230b 0272 	mov r1,0x2718
8e000ba8:	200b 18e2 	movt r1,0x8e00
8e000bac:	588b 0092 	mov r2,0x9c4
8e000bb0:	400b 18e2 	movt r2,0x8e00
8e000bb4:	0952      	jalr r2
8e000bb6:	01a2      	nop
8e000bb8:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000bbc:	b41b 2401 	add sp,sp,8
8e000bc0:	194f 0402 	rts

8e000bc4 <bj_rr_init>:
8e000bc4:	d5fc 2700 	strd lr,[sp],-0x3
8e000bc8:	f41b 2403 	add fp,sp,24
8e000bcc:	1cdc 0500 	str r0,[fp,-0x1]
8e000bd0:	04e2      	mov r0,r1
8e000bd2:	5ddc 0500 	str r2,[fp,-0x3]
8e000bd6:	2ce2      	mov r1,r3
8e000bd8:	1e3c 0500 	strh r0,[fp,-0x4]
8e000bdc:	04e2      	mov r0,r1
8e000bde:	1c1c 0502 	strb r0,[fp,-0x10]
8e000be2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000be6:	2033      	sub r1,r0,0
8e000be8:	8408 0000 	beq 8e000cf0 <bj_rr_init+0x12c>
8e000bec:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000bf0:	3bab 0cc2 	mov r1,0xccdd
8e000bf4:	376b 1aa2 	movt r1,0xaabb
8e000bf8:	2054      	str r1,[r0]
8e000bfa:	01a2      	nop
8e000bfc:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c00:	2044      	ldr r1,[r0]
8e000c02:	1bab 0cc2 	mov r0,0xccdd
8e000c06:	176b 1aa2 	movt r0,0xaabb
8e000c0a:	443a      	sub r2,r1,r0
8e000c0c:	f810      	bne 8e000bfc <bj_rr_init+0x38>
8e000c0e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c12:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000c16:	20d4      	str r1,[r0,0x1]
8e000c18:	01a2      	nop
8e000c1a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c1e:	20c4      	ldr r1,[r0,0x1]
8e000c20:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000c24:	443a      	sub r2,r1,r0
8e000c26:	fa10      	bne 8e000c1a <bj_rr_init+0x56>
8e000c28:	1c0c 0502 	ldrb r0,[fp,-0x10]
8e000c2c:	2033      	sub r1,r0,0
8e000c2e:	0d00      	beq 8e000c48 <bj_rr_init+0x84>
8e000c30:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c34:	00c4      	ldr r0,[r0,0x1]
8e000c36:	3e2c 0500 	ldrh r1,[fp,-0x4]
8e000c3a:	44e2      	mov r2,r1
8e000c3c:	2003      	mov r1,0x0
8e000c3e:	6b8b 0032 	mov r3,0x35c
8e000c42:	600b 18e2 	movt r3,0x8e00
8e000c46:	0d52      	jalr r3
8e000c48:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000c4c:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000c50:	241a      	add r1,r1,r0
8e000c52:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c56:	2154      	str r1,[r0,0x2]
8e000c58:	01a2      	nop
8e000c5a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c5e:	2144      	ldr r1,[r0,0x2]
8e000c60:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000c64:	5dcc 0500 	ldr r2,[fp,-0x3]
8e000c68:	081a      	add r0,r2,r0
8e000c6a:	443a      	sub r2,r1,r0
8e000c6c:	f710      	bne 8e000c5a <bj_rr_init+0x96>
8e000c6e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c72:	20c4      	ldr r1,[r0,0x1]
8e000c74:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c78:	21d4      	str r1,[r0,0x3]
8e000c7a:	01a2      	nop
8e000c7c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c80:	21c4      	ldr r1,[r0,0x3]
8e000c82:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c86:	00c4      	ldr r0,[r0,0x1]
8e000c88:	443a      	sub r2,r1,r0
8e000c8a:	f910      	bne 8e000c7c <bj_rr_init+0xb8>
8e000c8c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c90:	20c4      	ldr r1,[r0,0x1]
8e000c92:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c96:	2254      	str r1,[r0,0x4]
8e000c98:	01a2      	nop
8e000c9a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c9e:	2244      	ldr r1,[r0,0x4]
8e000ca0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ca4:	00c4      	ldr r0,[r0,0x1]
8e000ca6:	443a      	sub r2,r1,r0
8e000ca8:	f910      	bne 8e000c9a <bj_rr_init+0xd6>
8e000caa:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cae:	2003      	mov r1,0x0
8e000cb0:	22d4      	str r1,[r0,0x5]
8e000cb2:	01a2      	nop
8e000cb4:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cb8:	02c4      	ldr r0,[r0,0x5]
8e000cba:	2033      	sub r1,r0,0
8e000cbc:	fc10      	bne 8e000cb4 <bj_rr_init+0xf0>
8e000cbe:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cc2:	2003      	mov r1,0x0
8e000cc4:	201c 0003 	strb r1,[r0,+0x18]
8e000cc8:	01a2      	nop
8e000cca:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cce:	000c 0003 	ldrb r0,[r0,+0x18]
8e000cd2:	4033      	sub r2,r0,0
8e000cd4:	fb10      	bne 8e000cca <bj_rr_init+0x106>
8e000cd6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cda:	2003      	mov r1,0x0
8e000cdc:	209c 0003 	strb r1,[r0,+0x19]
8e000ce0:	01a2      	nop
8e000ce2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ce6:	008c 0003 	ldrb r0,[r0,+0x19]
8e000cea:	2033      	sub r1,r0,0
8e000cec:	fb10      	bne 8e000ce2 <bj_rr_init+0x11e>
8e000cee:	02e0      	b 8e000cf2 <bj_rr_init+0x12e>
8e000cf0:	01a2      	nop
8e000cf2:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e000cf6:	b41b 2403 	add sp,sp,24
8e000cfa:	194f 0402 	rts
8e000cfe:	01a2      	nop

8e000d00 <bj_rr_read_obj>:
8e000d00:	d77c 2700 	strd lr,[sp],-0x6
8e000d04:	f41b 2406 	add fp,sp,48
8e000d08:	1fdc 0500 	str r0,[fp,-0x7]
8e000d0c:	04e2      	mov r0,r1
8e000d0e:	5cdc 0501 	str r2,[fp,-0x9]
8e000d12:	1c3c 0502 	strh r0,[fp,-0x10]
8e000d16:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d1a:	2033      	sub r1,r0,0
8e000d1c:	0410      	bne 8e000d24 <bj_rr_read_obj+0x24>
8e000d1e:	0003      	mov r0,0x0
8e000d20:	e7e8 0000 	b 8e000eee <bj_rr_read_obj+0x1ee>
8e000d24:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d28:	0244      	ldr r0,[r0,0x4]
8e000d2a:	1edc 0500 	str r0,[fp,-0x5]
8e000d2e:	1e1b 04fd 	add r0,fp,-20
8e000d32:	20e2      	mov r1,r0
8e000d34:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d38:	448b 0132 	mov r2,0x1324
8e000d3c:	400b 18e2 	movt r2,0x8e00
8e000d40:	0952      	jalr r2
8e000d42:	1ebc 0500 	strh r0,[fp,-0x5]
8e000d46:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000d4a:	4033      	sub r2,r0,0
8e000d4c:	1310      	bne 8e000d72 <bj_rr_read_obj+0x72>
8e000d4e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d52:	3feb 0ff2 	mov r1,0xffff
8e000d56:	209c 0003 	strb r1,[r0,+0x19]
8e000d5a:	01a2      	nop
8e000d5c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d60:	008c 0003 	ldrb r0,[r0,+0x19]
8e000d64:	0316      	lsl r0,r0,0x18
8e000d66:	030e      	asr r0,r0,0x18
8e000d68:	23b3      	sub r1,r0,-1
8e000d6a:	f910      	bne 8e000d5c <bj_rr_read_obj+0x5c>
8e000d6c:	0003      	mov r0,0x0
8e000d6e:	c0e8 0000 	b 8e000eee <bj_rr_read_obj+0x1ee>
8e000d72:	3eac 0500 	ldrh r1,[fp,-0x5]
8e000d76:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000d7a:	443a      	sub r2,r1,r0
8e000d7c:	1340      	blteu 8e000da2 <bj_rr_read_obj+0xa2>
8e000d7e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d82:	3fcb 0ff2 	mov r1,0xfffe
8e000d86:	209c 0003 	strb r1,[r0,+0x19]
8e000d8a:	01a2      	nop
8e000d8c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d90:	008c 0003 	ldrb r0,[r0,+0x19]
8e000d94:	0316      	lsl r0,r0,0x18
8e000d96:	030e      	asr r0,r0,0x18
8e000d98:	2333      	sub r1,r0,-2
8e000d9a:	f910      	bne 8e000d8c <bj_rr_read_obj+0x8c>
8e000d9c:	0003      	mov r0,0x0
8e000d9e:	a8e8 0000 	b 8e000eee <bj_rr_read_obj+0x1ee>
8e000da2:	3eac 0500 	ldrh r1,[fp,-0x5]
8e000da6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000daa:	0144      	ldr r0,[r0,0x2]
8e000dac:	40e2      	mov r2,r0
8e000dae:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000db2:	00c4      	ldr r0,[r0,0x1]
8e000db4:	083a      	sub r0,r2,r0
8e000db6:	443a      	sub r2,r1,r0
8e000db8:	1390      	blte 8e000dde <bj_rr_read_obj+0xde>
8e000dba:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dbe:	3fab 0ff2 	mov r1,0xfffd
8e000dc2:	209c 0003 	strb r1,[r0,+0x19]
8e000dc6:	01a2      	nop
8e000dc8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dcc:	008c 0003 	ldrb r0,[r0,+0x19]
8e000dd0:	0316      	lsl r0,r0,0x18
8e000dd2:	030e      	asr r0,r0,0x18
8e000dd4:	22b3      	sub r1,r0,-3
8e000dd6:	f910      	bne 8e000dc8 <bj_rr_read_obj+0xc8>
8e000dd8:	0003      	mov r0,0x0
8e000dda:	8ae8 0000 	b 8e000eee <bj_rr_read_obj+0x1ee>
8e000dde:	0003      	mov r0,0x0
8e000de0:	1cbc 0500 	strh r0,[fp,-0x1]
8e000de4:	20e0      	b 8e000e24 <bj_rr_read_obj+0x124>
8e000de6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dea:	2144      	ldr r1,[r0,0x2]
8e000dec:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000df0:	443a      	sub r2,r1,r0
8e000df2:	0610      	bne 8e000dfe <bj_rr_read_obj+0xfe>
8e000df4:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000df8:	00c4      	ldr r0,[r0,0x1]
8e000dfa:	1edc 0500 	str r0,[fp,-0x5]
8e000dfe:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000e02:	3ccc 0501 	ldr r1,[fp,-0x9]
8e000e06:	041a      	add r0,r1,r0
8e000e08:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000e0c:	2404      	ldrb r1,[r1]
8e000e0e:	2014      	strb r1,[r0]
8e000e10:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000e14:	0093      	add r0,r0,1
8e000e16:	1edc 0500 	str r0,[fp,-0x5]
8e000e1a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000e1e:	0093      	add r0,r0,1
8e000e20:	1cbc 0500 	strh r0,[fp,-0x1]
8e000e24:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000e28:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000e2c:	443a      	sub r2,r1,r0
8e000e2e:	dc50      	bltu 8e000de6 <bj_rr_read_obj+0xe6>
8e000e30:	1e1b 04fd 	add r0,fp,-20
8e000e34:	20e2      	mov r1,r0
8e000e36:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e3a:	448b 0132 	mov r2,0x1324
8e000e3e:	400b 18e2 	movt r2,0x8e00
8e000e42:	0952      	jalr r2
8e000e44:	1f3c 0500 	strh r0,[fp,-0x6]
8e000e48:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000e4c:	20e2      	mov r1,r0
8e000e4e:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000e52:	4c8b 0112 	mov r2,0x1164
8e000e56:	400b 18e2 	movt r2,0x8e00
8e000e5a:	0952      	jalr r2
8e000e5c:	1fbc 0500 	strh r0,[fp,-0x7]
8e000e60:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000e64:	1fac 0500 	ldrh r0,[fp,-0x7]
8e000e68:	443a      	sub r2,r1,r0
8e000e6a:	1200      	beq 8e000e8e <bj_rr_read_obj+0x18e>
8e000e6c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e70:	3f8b 0ff2 	mov r1,0xfffc
8e000e74:	209c 0003 	strb r1,[r0,+0x19]
8e000e78:	01a2      	nop
8e000e7a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e7e:	008c 0003 	ldrb r0,[r0,+0x19]
8e000e82:	0316      	lsl r0,r0,0x18
8e000e84:	030e      	asr r0,r0,0x18
8e000e86:	2233      	sub r1,r0,-4
8e000e88:	f910      	bne 8e000e7a <bj_rr_read_obj+0x17a>
8e000e8a:	0003      	mov r0,0x0
8e000e8c:	31e0      	b 8e000eee <bj_rr_read_obj+0x1ee>
8e000e8e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e92:	0244      	ldr r0,[r0,0x4]
8e000e94:	1d5c 0500 	str r0,[fp,-0x2]
8e000e98:	16e0      	b 8e000ec4 <bj_rr_read_obj+0x1c4>
8e000e9a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e9e:	2144      	ldr r1,[r0,0x2]
8e000ea0:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ea4:	443a      	sub r2,r1,r0
8e000ea6:	0610      	bne 8e000eb2 <bj_rr_read_obj+0x1b2>
8e000ea8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000eac:	00c4      	ldr r0,[r0,0x1]
8e000eae:	1d5c 0500 	str r0,[fp,-0x2]
8e000eb2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000eb6:	2003      	mov r1,0x0
8e000eb8:	2014      	strb r1,[r0]
8e000eba:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ebe:	0093      	add r0,r0,1
8e000ec0:	1d5c 0500 	str r0,[fp,-0x2]
8e000ec4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000ec8:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000ecc:	443a      	sub r2,r1,r0
8e000ece:	e610      	bne 8e000e9a <bj_rr_read_obj+0x19a>
8e000ed0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ed4:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000ed8:	2254      	str r1,[r0,0x4]
8e000eda:	01a2      	nop
8e000edc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ee0:	2244      	ldr r1,[r0,0x4]
8e000ee2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ee6:	443a      	sub r2,r1,r0
8e000ee8:	fa10      	bne 8e000edc <bj_rr_read_obj+0x1dc>
8e000eea:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000eee:	d76c 2400 	ldrd lr,[sp,+0x6]
8e000ef2:	b41b 2406 	add sp,sp,48
8e000ef6:	194f 0402 	rts
8e000efa:	01a2      	nop

8e000efc <bj_rr_write_obj>:
8e000efc:	d77c 2700 	strd lr,[sp],-0x6
8e000f00:	f41b 2406 	add fp,sp,48
8e000f04:	1fdc 0500 	str r0,[fp,-0x7]
8e000f08:	04e2      	mov r0,r1
8e000f0a:	5cdc 0501 	str r2,[fp,-0x9]
8e000f0e:	1c3c 0502 	strh r0,[fp,-0x10]
8e000f12:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f16:	2033      	sub r1,r0,0
8e000f18:	0410      	bne 8e000f20 <bj_rr_write_obj+0x24>
8e000f1a:	0003      	mov r0,0x0
8e000f1c:	1de8 0001 	b 8e001156 <bj_rr_write_obj+0x25a>
8e000f20:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f24:	02c4      	ldr r0,[r0,0x5]
8e000f26:	1e5c 0500 	str r0,[fp,-0x4]
8e000f2a:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000f2e:	1cbc 0501 	strh r0,[fp,-0x9]
8e000f32:	3cac 0501 	ldrh r1,[fp,-0x9]
8e000f36:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f3a:	0144      	ldr r0,[r0,0x2]
8e000f3c:	40e2      	mov r2,r0
8e000f3e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f42:	00c4      	ldr r0,[r0,0x1]
8e000f44:	083a      	sub r0,r2,r0
8e000f46:	0213      	add r0,r0,-4
8e000f48:	443a      	sub r2,r1,r0
8e000f4a:	2540      	blteu 8e000f94 <bj_rr_write_obj+0x98>
8e000f4c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f50:	3feb 0ff2 	mov r1,0xffff
8e000f54:	201c 0003 	strb r1,[r0,+0x18]
8e000f58:	01a2      	nop
8e000f5a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f5e:	000c 0003 	ldrb r0,[r0,+0x18]
8e000f62:	0316      	lsl r0,r0,0x18
8e000f64:	030e      	asr r0,r0,0x18
8e000f66:	23b3      	sub r1,r0,-1
8e000f68:	f910      	bne 8e000f5a <bj_rr_write_obj+0x5e>
8e000f6a:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f6e:	0093      	add r0,r0,1
8e000f70:	1e5c 0500 	str r0,[fp,-0x4]
8e000f74:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f78:	3e4c 0500 	ldr r1,[fp,-0x4]
8e000f7c:	22d4      	str r1,[r0,0x5]
8e000f7e:	01a2      	nop
8e000f80:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f84:	22c4      	ldr r1,[r0,0x5]
8e000f86:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f8a:	443a      	sub r2,r1,r0
8e000f8c:	fa10      	bne 8e000f80 <bj_rr_write_obj+0x84>
8e000f8e:	0003      	mov r0,0x0
8e000f90:	e3e8 0000 	b 8e001156 <bj_rr_write_obj+0x25a>
8e000f94:	1cac 0501 	ldrh r0,[fp,-0x9]
8e000f98:	2033      	sub r1,r0,0
8e000f9a:	2510      	bne 8e000fe4 <bj_rr_write_obj+0xe8>
8e000f9c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fa0:	3fcb 0ff2 	mov r1,0xfffe
8e000fa4:	201c 0003 	strb r1,[r0,+0x18]
8e000fa8:	01a2      	nop
8e000faa:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fae:	000c 0003 	ldrb r0,[r0,+0x18]
8e000fb2:	0316      	lsl r0,r0,0x18
8e000fb4:	030e      	asr r0,r0,0x18
8e000fb6:	4333      	sub r2,r0,-2
8e000fb8:	f910      	bne 8e000faa <bj_rr_write_obj+0xae>
8e000fba:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000fbe:	0093      	add r0,r0,1
8e000fc0:	1e5c 0500 	str r0,[fp,-0x4]
8e000fc4:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fc8:	3e4c 0500 	ldr r1,[fp,-0x4]
8e000fcc:	22d4      	str r1,[r0,0x5]
8e000fce:	01a2      	nop
8e000fd0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fd4:	22c4      	ldr r1,[r0,0x5]
8e000fd6:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000fda:	443a      	sub r2,r1,r0
8e000fdc:	fa10      	bne 8e000fd0 <bj_rr_write_obj+0xd4>
8e000fde:	0003      	mov r0,0x0
8e000fe0:	bbe8 0000 	b 8e001156 <bj_rr_write_obj+0x25a>
8e000fe4:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000fe8:	031b 0000 	add r0,r0,6
8e000fec:	1cbc 0500 	strh r0,[fp,-0x1]
8e000ff0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ff4:	01c4      	ldr r0,[r0,0x3]
8e000ff6:	1d5c 0500 	str r0,[fp,-0x2]
8e000ffa:	20e0      	b 8e00103a <bj_rr_write_obj+0x13e>
8e000ffc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001000:	2144      	ldr r1,[r0,0x2]
8e001002:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001006:	443a      	sub r2,r1,r0
8e001008:	0610      	bne 8e001014 <bj_rr_write_obj+0x118>
8e00100a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00100e:	00c4      	ldr r0,[r0,0x1]
8e001010:	1d5c 0500 	str r0,[fp,-0x2]
8e001014:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001018:	0004      	ldrb r0,[r0]
8e00101a:	2033      	sub r1,r0,0
8e00101c:	0500      	beq 8e001026 <bj_rr_write_obj+0x12a>
8e00101e:	0003      	mov r0,0x0
8e001020:	1d5c 0500 	str r0,[fp,-0x2]
8e001024:	0fe0      	b 8e001042 <bj_rr_write_obj+0x146>
8e001026:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00102a:	0093      	add r0,r0,1
8e00102c:	1d5c 0500 	str r0,[fp,-0x2]
8e001030:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001034:	0393      	add r0,r0,-1
8e001036:	1cbc 0500 	strh r0,[fp,-0x1]
8e00103a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00103e:	4033      	sub r2,r0,0
8e001040:	de10      	bne 8e000ffc <bj_rr_write_obj+0x100>
8e001042:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001046:	2033      	sub r1,r0,0
8e001048:	2410      	bne 8e001090 <bj_rr_write_obj+0x194>
8e00104a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00104e:	3fab 0ff2 	mov r1,0xfffd
8e001052:	201c 0003 	strb r1,[r0,+0x18]
8e001056:	01a2      	nop
8e001058:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00105c:	000c 0003 	ldrb r0,[r0,+0x18]
8e001060:	0316      	lsl r0,r0,0x18
8e001062:	030e      	asr r0,r0,0x18
8e001064:	42b3      	sub r2,r0,-3
8e001066:	f910      	bne 8e001058 <bj_rr_write_obj+0x15c>
8e001068:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00106c:	0093      	add r0,r0,1
8e00106e:	1e5c 0500 	str r0,[fp,-0x4]
8e001072:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001076:	3e4c 0500 	ldr r1,[fp,-0x4]
8e00107a:	22d4      	str r1,[r0,0x5]
8e00107c:	01a2      	nop
8e00107e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001082:	22c4      	ldr r1,[r0,0x5]
8e001084:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001088:	443a      	sub r2,r1,r0
8e00108a:	fa10      	bne 8e00107e <bj_rr_write_obj+0x182>
8e00108c:	0003      	mov r0,0x0
8e00108e:	64e0      	b 8e001156 <bj_rr_write_obj+0x25a>
8e001090:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001094:	01c4      	ldr r0,[r0,0x3]
8e001096:	1f5c 0500 	str r0,[fp,-0x6]
8e00109a:	3c2c 0502 	ldrh r1,[fp,-0x10]
8e00109e:	1c1b 04fd 	add r0,fp,-24
8e0010a2:	44e2      	mov r2,r1
8e0010a4:	20e2      	mov r1,r0
8e0010a6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010aa:	790b 0132 	mov r3,0x13c8
8e0010ae:	600b 18e2 	movt r3,0x8e00
8e0010b2:	0d52      	jalr r3
8e0010b4:	0003      	mov r0,0x0
8e0010b6:	1ebc 0500 	strh r0,[fp,-0x5]
8e0010ba:	20e0      	b 8e0010fa <bj_rr_write_obj+0x1fe>
8e0010bc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010c0:	2144      	ldr r1,[r0,0x2]
8e0010c2:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010c6:	443a      	sub r2,r1,r0
8e0010c8:	0610      	bne 8e0010d4 <bj_rr_write_obj+0x1d8>
8e0010ca:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010ce:	00c4      	ldr r0,[r0,0x1]
8e0010d0:	1f5c 0500 	str r0,[fp,-0x6]
8e0010d4:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010d8:	3eac 0500 	ldrh r1,[fp,-0x5]
8e0010dc:	5ccc 0501 	ldr r2,[fp,-0x9]
8e0010e0:	289a      	add r1,r2,r1
8e0010e2:	2404      	ldrb r1,[r1]
8e0010e4:	2014      	strb r1,[r0]
8e0010e6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010ea:	0093      	add r0,r0,1
8e0010ec:	1f5c 0500 	str r0,[fp,-0x6]
8e0010f0:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0010f4:	0093      	add r0,r0,1
8e0010f6:	1ebc 0500 	strh r0,[fp,-0x5]
8e0010fa:	3eac 0500 	ldrh r1,[fp,-0x5]
8e0010fe:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001102:	443a      	sub r2,r1,r0
8e001104:	dc50      	bltu 8e0010bc <bj_rr_write_obj+0x1c0>
8e001106:	1cac 0501 	ldrh r0,[fp,-0x9]
8e00110a:	20e2      	mov r1,r0
8e00110c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e001110:	4c8b 0112 	mov r2,0x1164
8e001114:	400b 18e2 	movt r2,0x8e00
8e001118:	0952      	jalr r2
8e00111a:	1d3c 0501 	strh r0,[fp,-0xa]
8e00111e:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e001122:	1c1b 04fd 	add r0,fp,-24
8e001126:	44e2      	mov r2,r1
8e001128:	20e2      	mov r1,r0
8e00112a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00112e:	790b 0132 	mov r3,0x13c8
8e001132:	600b 18e2 	movt r3,0x8e00
8e001136:	0d52      	jalr r3
8e001138:	3f4c 0500 	ldr r1,[fp,-0x6]
8e00113c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001140:	21d4      	str r1,[r0,0x3]
8e001142:	01a2      	nop
8e001144:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001148:	21c4      	ldr r1,[r0,0x3]
8e00114a:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00114e:	443a      	sub r2,r1,r0
8e001150:	fa10      	bne 8e001144 <bj_rr_write_obj+0x248>
8e001152:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001156:	d76c 2400 	ldrd lr,[sp,+0x6]
8e00115a:	b41b 2406 	add sp,sp,48
8e00115e:	194f 0402 	rts
8e001162:	01a2      	nop

8e001164 <bj_crc16>:
8e001164:	f75c 2700 	str fp,[sp],-0x6
8e001168:	f4ef 2402 	mov fp,sp
8e00116c:	1ddc 0400 	str r0,[fp,+0x3]
8e001170:	04e2      	mov r0,r1
8e001172:	1e3c 0400 	strh r0,[fp,+0x4]
8e001176:	1feb 0ff2 	mov r0,0xffff
8e00117a:	1feb 1ff2 	movt r0,0xffff
8e00117e:	1cbc 0401 	strh r0,[fp,+0x9]
8e001182:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001186:	2033      	sub r1,r0,0
8e001188:	0b10      	bne 8e00119e <bj_crc16+0x3a>
8e00118a:	3cac 0401 	ldrh r1,[fp,+0x9]
8e00118e:	1feb 0ff2 	mov r0,0xffff
8e001192:	1feb 1ff2 	movt r0,0xffff
8e001196:	040a      	eor r0,r1,r0
8e001198:	000b 1002 	movt r0,0x0
8e00119c:	65e0      	b 8e001266 <bj_crc16+0x102>
8e00119e:	0003      	mov r0,0x0
8e0011a0:	1f9c 0402 	strb r0,[fp,+0x17]
8e0011a4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0011a8:	2093      	add r1,r0,1
8e0011aa:	3ddc 0400 	str r1,[fp,+0x3]
8e0011ae:	0004      	ldrb r0,[r0]
8e0011b0:	1d3c 0401 	strh r0,[fp,+0xa]
8e0011b4:	2ae0      	b 8e001208 <bj_crc16+0xa4>
8e0011b6:	3cac 0401 	ldrh r1,[fp,+0x9]
8e0011ba:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0011be:	040a      	eor r0,r1,r0
8e0011c0:	000b 1002 	movt r0,0x0
8e0011c4:	20e2      	mov r1,r0
8e0011c6:	0023      	mov r0,0x1
8e0011c8:	045a      	and r0,r1,r0
8e0011ca:	2033      	sub r1,r0,0
8e0011cc:	0f00      	beq 8e0011ea <bj_crc16+0x86>
8e0011ce:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0011d2:	0026      	lsr r0,r0,0x1
8e0011d4:	20e2      	mov r1,r0
8e0011d6:	200b 1002 	movt r1,0x0
8e0011da:	010b 0842 	mov r0,0x8408
8e0011de:	1feb 1ff2 	movt r0,0xffff
8e0011e2:	040a      	eor r0,r1,r0
8e0011e4:	1cbc 0401 	strh r0,[fp,+0x9]
8e0011e8:	06e0      	b 8e0011f4 <bj_crc16+0x90>
8e0011ea:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0011ee:	0026      	lsr r0,r0,0x1
8e0011f0:	1cbc 0401 	strh r0,[fp,+0x9]
8e0011f4:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e0011f8:	0093      	add r0,r0,1
8e0011fa:	1f9c 0402 	strb r0,[fp,+0x17]
8e0011fe:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e001202:	0026      	lsr r0,r0,0x1
8e001204:	1d3c 0401 	strh r0,[fp,+0xa]
8e001208:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e00120c:	23bb 0000 	sub r1,r0,7
8e001210:	d340      	blteu 8e0011b6 <bj_crc16+0x52>
8e001212:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001216:	0393      	add r0,r0,-1
8e001218:	1e3c 0400 	strh r0,[fp,+0x4]
8e00121c:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001220:	2033      	sub r1,r0,0
8e001222:	be10      	bne 8e00119e <bj_crc16+0x3a>
8e001224:	3cac 0401 	ldrh r1,[fp,+0x9]
8e001228:	1feb 0ff2 	mov r0,0xffff
8e00122c:	1feb 1ff2 	movt r0,0xffff
8e001230:	040a      	eor r0,r1,r0
8e001232:	1cbc 0401 	strh r0,[fp,+0x9]
8e001236:	1cac 0401 	ldrh r0,[fp,+0x9]
8e00123a:	1d3c 0401 	strh r0,[fp,+0xa]
8e00123e:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001242:	0116      	lsl r0,r0,0x8
8e001244:	20e2      	mov r1,r0
8e001246:	200b 1002 	movt r1,0x0
8e00124a:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e00124e:	0106      	lsr r0,r0,0x8
8e001250:	000b 1002 	movt r0,0x0
8e001254:	000b 1002 	movt r0,0x0
8e001258:	047a      	orr r0,r1,r0
8e00125a:	000b 1002 	movt r0,0x0
8e00125e:	1cbc 0401 	strh r0,[fp,+0x9]
8e001262:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001266:	f74c 2400 	ldr fp,[sp,+0x6]
8e00126a:	b41b 2403 	add sp,sp,24
8e00126e:	194f 0402 	rts
8e001272:	01a2      	nop

8e001274 <bj_get_v16_of_p8>:
8e001274:	f75c 2700 	str fp,[sp],-0x6
8e001278:	f4ef 2402 	mov fp,sp
8e00127c:	1ddc 0400 	str r0,[fp,+0x3]
8e001280:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001284:	0093      	add r0,r0,1
8e001286:	0004      	ldrb r0,[r0]
8e001288:	1dbc 0401 	strh r0,[fp,+0xb]
8e00128c:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001290:	0116      	lsl r0,r0,0x8
8e001292:	1dbc 0401 	strh r0,[fp,+0xb]
8e001296:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00129a:	0004      	ldrb r0,[r0]
8e00129c:	20e2      	mov r1,r0
8e00129e:	200b 1002 	movt r1,0x0
8e0012a2:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0012a6:	047a      	orr r0,r1,r0
8e0012a8:	1dbc 0401 	strh r0,[fp,+0xb]
8e0012ac:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0012b0:	f74c 2400 	ldr fp,[sp,+0x6]
8e0012b4:	b41b 2403 	add sp,sp,24
8e0012b8:	194f 0402 	rts

8e0012bc <bj_set_v16_of_p8>:
8e0012bc:	f75c 2700 	str fp,[sp],-0x6
8e0012c0:	f4ef 2402 	mov fp,sp
8e0012c4:	1ddc 0400 	str r0,[fp,+0x3]
8e0012c8:	04e2      	mov r0,r1
8e0012ca:	1e3c 0400 	strh r0,[fp,+0x4]
8e0012ce:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e0012d2:	1fe3      	mov r0,0xff
8e0012d4:	045a      	and r0,r1,r0
8e0012d6:	1dbc 0401 	strh r0,[fp,+0xb]
8e0012da:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e0012de:	000b 0ff2 	mov r0,0xff00
8e0012e2:	1feb 1ff2 	movt r0,0xffff
8e0012e6:	045a      	and r0,r1,r0
8e0012e8:	1d3c 0401 	strh r0,[fp,+0xa]
8e0012ec:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0012f0:	0106      	lsr r0,r0,0x8
8e0012f2:	1d3c 0401 	strh r0,[fp,+0xa]
8e0012f6:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0012fa:	0093      	add r0,r0,1
8e0012fc:	3d2c 0401 	ldrh r1,[fp,+0xa]
8e001300:	2716      	lsl r1,r1,0x18
8e001302:	2706      	lsr r1,r1,0x18
8e001304:	2014      	strb r1,[r0]
8e001306:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00130a:	2316      	lsl r1,r0,0x18
8e00130c:	2706      	lsr r1,r1,0x18
8e00130e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001312:	2014      	strb r1,[r0]
8e001314:	01a2      	nop
8e001316:	f74c 2400 	ldr fp,[sp,+0x6]
8e00131a:	b41b 2403 	add sp,sp,24
8e00131e:	194f 0402 	rts
8e001322:	01a2      	nop

8e001324 <bj_rr_get_v16>:
8e001324:	d67c 2700 	strd lr,[sp],-0x4
8e001328:	f41b 2404 	add fp,sp,32
8e00132c:	1edc 0500 	str r0,[fp,-0x5]
8e001330:	3f5c 0500 	str r1,[fp,-0x6]
8e001334:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001338:	2033      	sub r1,r0,0
8e00133a:	0310      	bne 8e001340 <bj_rr_get_v16+0x1c>
8e00133c:	0003      	mov r0,0x0
8e00133e:	3ee0      	b 8e0013ba <bj_rr_get_v16+0x96>
8e001340:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001344:	0044      	ldr r0,[r0]
8e001346:	1cdc 0500 	str r0,[fp,-0x1]
8e00134a:	0003      	mov r0,0x0
8e00134c:	1d5c 0500 	str r0,[fp,-0x2]
8e001350:	21e0      	b 8e001392 <bj_rr_get_v16+0x6e>
8e001352:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001356:	2144      	ldr r1,[r0,0x2]
8e001358:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00135c:	443a      	sub r2,r1,r0
8e00135e:	0610      	bne 8e00136a <bj_rr_get_v16+0x46>
8e001360:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001364:	00c4      	ldr r0,[r0,0x1]
8e001366:	1cdc 0500 	str r0,[fp,-0x1]
8e00136a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00136e:	4004      	ldrb r2,[r0]
8e001370:	3e1b 04fe 	add r1,fp,-12
8e001374:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001378:	041a      	add r0,r1,r0
8e00137a:	28e2      	mov r1,r2
8e00137c:	2014      	strb r1,[r0]
8e00137e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001382:	0093      	add r0,r0,1
8e001384:	1cdc 0500 	str r0,[fp,-0x1]
8e001388:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00138c:	0093      	add r0,r0,1
8e00138e:	1d5c 0500 	str r0,[fp,-0x2]
8e001392:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001396:	20b3      	sub r1,r0,1
8e001398:	dd90      	blte 8e001352 <bj_rr_get_v16+0x2e>
8e00139a:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00139e:	3ccc 0500 	ldr r1,[fp,-0x1]
8e0013a2:	2054      	str r1,[r0]
8e0013a4:	1e1b 04fe 	add r0,fp,-12
8e0013a8:	2e8b 0122 	mov r1,0x1274
8e0013ac:	200b 18e2 	movt r1,0x8e00
8e0013b0:	0552      	jalr r1
8e0013b2:	1ebc 0500 	strh r0,[fp,-0x5]
8e0013b6:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0013ba:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0013be:	b41b 2404 	add sp,sp,32
8e0013c2:	194f 0402 	rts
8e0013c6:	01a2      	nop

8e0013c8 <bj_rr_set_v16>:
8e0013c8:	d6fc 2700 	strd lr,[sp],-0x5
8e0013cc:	f41b 2405 	add fp,sp,40
8e0013d0:	1edc 0500 	str r0,[fp,-0x5]
8e0013d4:	3f5c 0500 	str r1,[fp,-0x6]
8e0013d8:	08e2      	mov r0,r2
8e0013da:	1f3c 0501 	strh r0,[fp,-0xe]
8e0013de:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0013e2:	2033      	sub r1,r0,0
8e0013e4:	3c00      	beq 8e00145c <bj_rr_set_v16+0x94>
8e0013e6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0013ea:	0044      	ldr r0,[r0]
8e0013ec:	1cdc 0500 	str r0,[fp,-0x1]
8e0013f0:	3f2c 0501 	ldrh r1,[fp,-0xe]
8e0013f4:	1f1b 04fe 	add r0,fp,-10
8e0013f8:	578b 0122 	mov r2,0x12bc
8e0013fc:	400b 18e2 	movt r2,0x8e00
8e001400:	0952      	jalr r2
8e001402:	0003      	mov r0,0x0
8e001404:	1d5c 0500 	str r0,[fp,-0x2]
8e001408:	20e0      	b 8e001448 <bj_rr_set_v16+0x80>
8e00140a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00140e:	2144      	ldr r1,[r0,0x2]
8e001410:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001414:	443a      	sub r2,r1,r0
8e001416:	0610      	bne 8e001422 <bj_rr_set_v16+0x5a>
8e001418:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00141c:	00c4      	ldr r0,[r0,0x1]
8e00141e:	1cdc 0500 	str r0,[fp,-0x1]
8e001422:	3f1b 04fe 	add r1,fp,-10
8e001426:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00142a:	041a      	add r0,r1,r0
8e00142c:	2004      	ldrb r1,[r0]
8e00142e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001432:	2014      	strb r1,[r0]
8e001434:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001438:	0093      	add r0,r0,1
8e00143a:	1cdc 0500 	str r0,[fp,-0x1]
8e00143e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001442:	0093      	add r0,r0,1
8e001444:	1d5c 0500 	str r0,[fp,-0x2]
8e001448:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00144c:	20b3      	sub r1,r0,1
8e00144e:	de90      	blte 8e00140a <bj_rr_set_v16+0x42>
8e001450:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001454:	3ccc 0500 	ldr r1,[fp,-0x1]
8e001458:	2054      	str r1,[r0]
8e00145a:	02e0      	b 8e00145e <bj_rr_set_v16+0x96>
8e00145c:	01a2      	nop
8e00145e:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e001462:	b41b 2405 	add sp,sp,40
8e001466:	194f 0402 	rts
8e00146a:	01a2      	nop

8e00146c <bjk_get_call_stack_trace>:
8e00146c:	d57c 2701 	strd lr,[sp],-0xa
8e001470:	f41b 240a 	add fp,sp,80
8e001474:	3d5c 0502 	str r1,[fp,-0x12]
8e001478:	1d3c 0504 	strh r0,[fp,-0x22]
8e00147c:	1d4c 0502 	ldr r0,[fp,-0x12]
8e001480:	2033      	sub r1,r0,0
8e001482:	0410      	bne 8e00148a <bjk_get_call_stack_trace+0x1e>
8e001484:	0003      	mov r0,0x0
8e001486:	3be8 0001 	b 8e0016fc <bjk_get_call_stack_trace+0x290>
8e00148a:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e00148e:	0216      	lsl r0,r0,0x10
8e001490:	020e      	asr r0,r0,0x10
8e001492:	4033      	sub r2,r0,0
8e001494:	0460      	bgt 8e00149c <bjk_get_call_stack_trace+0x30>
8e001496:	0003      	mov r0,0x0
8e001498:	32e8 0001 	b 8e0016fc <bjk_get_call_stack_trace+0x290>
8e00149c:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e0014a0:	0216      	lsl r0,r0,0x10
8e0014a2:	020e      	asr r0,r0,0x10
8e0014a4:	0056      	lsl r0,r0,0x2
8e0014a6:	40e2      	mov r2,r0
8e0014a8:	2003      	mov r1,0x0
8e0014aa:	1d4c 0502 	ldr r0,[fp,-0x12]
8e0014ae:	6b8b 0032 	mov r3,0x35c
8e0014b2:	600b 18e2 	movt r3,0x8e00
8e0014b6:	0d52      	jalr r3
8e0014b8:	108b 0032 	mov r0,0x384
8e0014bc:	000b 1002 	movt r0,0x0
8e0014c0:	0044      	ldr r0,[r0]
8e0014c2:	3d4c 0502 	ldr r1,[fp,-0x12]
8e0014c6:	20d4      	str r1,[r0,0x1]
8e0014c8:	0003      	mov r0,0x0
8e0014ca:	1cdc 0500 	str r0,[fp,-0x1]
8e0014ce:	0003      	mov r0,0x0
8e0014d0:	1d5c 0500 	str r0,[fp,-0x2]
8e0014d4:	0003      	mov r0,0x0
8e0014d6:	1ddc 0500 	str r0,[fp,-0x3]
8e0014da:	0003      	mov r0,0x0
8e0014dc:	1fbc 0500 	strh r0,[fp,-0x7]
8e0014e0:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e0014e4:	0216      	lsl r0,r0,0x10
8e0014e6:	020e      	asr r0,r0,0x10
8e0014e8:	2033      	sub r1,r0,0
8e0014ea:	0460      	bgt 8e0014f2 <bjk_get_call_stack_trace+0x86>
8e0014ec:	0003      	mov r0,0x0
8e0014ee:	07e8 0001 	b 8e0016fc <bjk_get_call_stack_trace+0x290>
8e0014f2:	0912      	movfs r0,pc
8e0014f4:	00e2      	mov r0,r0
8e0014f6:	1cdc 0500 	str r0,[fp,-0x1]
8e0014fa:	14ef 0402 	mov r0,sp
8e0014fe:	1d5c 0500 	str r0,[fp,-0x2]
8e001502:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001506:	340b 01a2 	mov r1,0x1aa0
8e00150a:	200b 18e2 	movt r1,0x8e00
8e00150e:	0552      	jalr r1
8e001510:	1ddc 0500 	str r0,[fp,-0x3]
8e001514:	c5e8 0000 	b 8e00169e <bjk_get_call_stack_trace+0x232>
8e001518:	3fac 0500 	ldrh r1,[fp,-0x7]
8e00151c:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e001520:	0216      	lsl r0,r0,0x10
8e001522:	020e      	asr r0,r0,0x10
8e001524:	443a      	sub r2,r1,r0
8e001526:	c208 0000 	beq 8e0016aa <bjk_get_call_stack_trace+0x23e>
8e00152a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00152e:	390b 01b2 	mov r1,0x1bc8
8e001532:	200b 18e2 	movt r1,0x8e00
8e001536:	0552      	jalr r1
8e001538:	1c3c 0501 	strh r0,[fp,-0x8]
8e00153c:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001540:	2033      	sub r1,r0,0
8e001542:	b608 0000 	beq 8e0016ae <bjk_get_call_stack_trace+0x242>
8e001546:	3c2c 0501 	ldrh r1,[fp,-0x8]
8e00154a:	0023      	mov r0,0x1
8e00154c:	045a      	and r0,r1,r0
8e00154e:	000b 1002 	movt r0,0x0
8e001552:	4033      	sub r2,r0,0
8e001554:	0b00      	beq 8e00156a <bjk_get_call_stack_trace+0xfe>
8e001556:	0d8b 0142 	mov r0,0x146c
8e00155a:	000b 18e2 	movt r0,0x8e00
8e00155e:	2003      	mov r1,0x0
8e001560:	588b 0092 	mov r2,0x9c4
8e001564:	400b 18e2 	movt r2,0x8e00
8e001568:	0952      	jalr r2
8e00156a:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00156e:	1edc 0500 	str r0,[fp,-0x5]
8e001572:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001576:	3ecc 0500 	ldr r1,[fp,-0x5]
8e00157a:	041a      	add r0,r1,r0
8e00157c:	1edc 0500 	str r0,[fp,-0x5]
8e001580:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001584:	1d5c 0500 	str r0,[fp,-0x2]
8e001588:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e00158c:	0066      	lsr r0,r0,0x3
8e00158e:	1dbc 0501 	strh r0,[fp,-0xb]
8e001592:	1dac 0501 	ldrh r0,[fp,-0xb]
8e001596:	0216      	lsl r0,r0,0x10
8e001598:	020e      	asr r0,r0,0x10
8e00159a:	3f1b 04f8 	add r1,fp,-58
8e00159e:	3c5c 0501 	str r1,[fp,-0x8]
8e0015a2:	1dbc 0503 	strh r0,[fp,-0x1b]
8e0015a6:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015aa:	2f8b 0d42 	mov r1,0xd47c
8e0015ae:	3feb 1ff2 	movt r1,0xffff
8e0015b2:	2034      	strh r1,[r0]
8e0015b4:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015b8:	0113      	add r0,r0,2
8e0015ba:	200b 0272 	mov r1,0x2700
8e0015be:	2034      	strh r1,[r0]
8e0015c0:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015c4:	0024      	ldrh r0,[r0]
8e0015c6:	20e2      	mov r1,r0
8e0015c8:	200b 1002 	movt r1,0x0
8e0015cc:	1dac 0503 	ldrh r0,[fp,-0x1b]
8e0015d0:	40e2      	mov r2,r0
8e0015d2:	00e3      	mov r0,0x7
8e0015d4:	085a      	and r0,r2,r0
8e0015d6:	00f6      	lsl r0,r0,0x7
8e0015d8:	000b 1002 	movt r0,0x0
8e0015dc:	047a      	orr r0,r1,r0
8e0015de:	000b 1002 	movt r0,0x0
8e0015e2:	20e2      	mov r1,r0
8e0015e4:	200b 1002 	movt r1,0x0
8e0015e8:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015ec:	2034      	strh r1,[r0]
8e0015ee:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015f2:	2113      	add r1,r0,2
8e0015f4:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015f8:	0113      	add r0,r0,2
8e0015fa:	0024      	ldrh r0,[r0]
8e0015fc:	40e2      	mov r2,r0
8e0015fe:	400b 1002 	movt r2,0x0
8e001602:	1dac 0503 	ldrh r0,[fp,-0x1b]
8e001606:	0216      	lsl r0,r0,0x10
8e001608:	020e      	asr r0,r0,0x10
8e00160a:	006e      	asr r0,r0,0x3
8e00160c:	000b 1002 	movt r0,0x0
8e001610:	087a      	orr r0,r2,r0
8e001612:	000b 1002 	movt r0,0x0
8e001616:	000b 1002 	movt r0,0x0
8e00161a:	0434      	strh r0,[r1]
8e00161c:	1f1b 04f8 	add r0,fp,-58
8e001620:	20e2      	mov r1,r0
8e001622:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001626:	418b 0192 	mov r2,0x190c
8e00162a:	400b 18e2 	movt r2,0x8e00
8e00162e:	0952      	jalr r2
8e001630:	1fdc 0500 	str r0,[fp,-0x7]
8e001634:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001638:	1e5c 0501 	str r0,[fp,-0xc]
8e00163c:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001640:	0113      	add r0,r0,2
8e001642:	0024      	ldrh r0,[r0]
8e001644:	1edc 0501 	str r0,[fp,-0xd]
8e001648:	1ecc 0501 	ldr r0,[fp,-0xd]
8e00164c:	0216      	lsl r0,r0,0x10
8e00164e:	1edc 0501 	str r0,[fp,-0xd]
8e001652:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001656:	0024      	ldrh r0,[r0]
8e001658:	20e2      	mov r1,r0
8e00165a:	1ecc 0501 	ldr r0,[fp,-0xd]
8e00165e:	00fa      	orr r0,r0,r1
8e001660:	1edc 0501 	str r0,[fp,-0xd]
8e001664:	1ecc 0501 	ldr r0,[fp,-0xd]
8e001668:	1cdc 0501 	str r0,[fp,-0x9]
8e00166c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e001670:	1cdc 0500 	str r0,[fp,-0x1]
8e001674:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001678:	2093      	add r1,r0,1
8e00167a:	3fbc 0500 	strh r1,[fp,-0x7]
8e00167e:	0056      	lsl r0,r0,0x2
8e001680:	3d4c 0502 	ldr r1,[fp,-0x12]
8e001684:	041a      	add r0,r1,r0
8e001686:	3fcc 0500 	ldr r1,[fp,-0x7]
8e00168a:	2054      	str r1,[r0]
8e00168c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001690:	340b 01a2 	mov r1,0x1aa0
8e001694:	200b 18e2 	movt r1,0x8e00
8e001698:	0552      	jalr r1
8e00169a:	1ddc 0500 	str r0,[fp,-0x3]
8e00169e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0016a2:	2033      	sub r1,r0,0
8e0016a4:	3a18 ffff 	bne 8e001518 <bjk_get_call_stack_trace+0xac>
8e0016a8:	04e0      	b 8e0016b0 <bjk_get_call_stack_trace+0x244>
8e0016aa:	01a2      	nop
8e0016ac:	02e0      	b 8e0016b0 <bjk_get_call_stack_trace+0x244>
8e0016ae:	01a2      	nop
8e0016b0:	108b 0032 	mov r0,0x384
8e0016b4:	000b 1002 	movt r0,0x0
8e0016b8:	0044      	ldr r0,[r0]
8e0016ba:	001b 0037 	add r0,r0,440
8e0016be:	1d5c 0501 	str r0,[fp,-0xa]
8e0016c2:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0016c6:	0024      	ldrh r0,[r0]
8e0016c8:	40bb 0008 	sub r2,r0,65
8e0016cc:	1610      	bne 8e0016f8 <bjk_get_call_stack_trace+0x28c>
8e0016ce:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0016d2:	380b 0192 	mov r1,0x19c0
8e0016d6:	200b 18e2 	movt r1,0x8e00
8e0016da:	0552      	jalr r1
8e0016dc:	1ddc 0501 	str r0,[fp,-0xb]
8e0016e0:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0016e4:	2093      	add r1,r0,1
8e0016e6:	3fbc 0500 	strh r1,[fp,-0x7]
8e0016ea:	0056      	lsl r0,r0,0x2
8e0016ec:	3d4c 0502 	ldr r1,[fp,-0x12]
8e0016f0:	041a      	add r0,r1,r0
8e0016f2:	3dcc 0501 	ldr r1,[fp,-0xb]
8e0016f6:	2054      	str r1,[r0]
8e0016f8:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0016fc:	d56c 2401 	ldrd lr,[sp,+0xa]
8e001700:	b41b 240a 	add sp,sp,80
8e001704:	194f 0402 	rts

8e001708 <bjk_wait_sync>:
8e001708:	d67c 2700 	strd lr,[sp],-0x4
8e00170c:	f41b 2404 	add fp,sp,32
8e001710:	1ddc 0500 	str r0,[fp,-0x3]
8e001714:	04e2      	mov r0,r1
8e001716:	5edc 0500 	str r2,[fp,-0x5]
8e00171a:	1c3c 0501 	strh r0,[fp,-0x8]
8e00171e:	108b 0032 	mov r0,0x384
8e001722:	000b 1002 	movt r0,0x0
8e001726:	0044      	ldr r0,[r0]
8e001728:	02cc 0001 	ldr r0,[r0,+0xd]
8e00172c:	1cdc 0500 	str r0,[fp,-0x1]
8e001730:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001734:	2033      	sub r1,r0,0
8e001736:	4c00      	beq 8e0017ce <bjk_wait_sync+0xc6>
8e001738:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e00173c:	0216      	lsl r0,r0,0x10
8e00173e:	020e      	asr r0,r0,0x10
8e001740:	4033      	sub r2,r0,0
8e001742:	1090      	blte 8e001762 <bjk_wait_sync+0x5a>
8e001744:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001748:	2033      	sub r1,r0,0
8e00174a:	0c00      	beq 8e001762 <bjk_wait_sync+0x5a>
8e00174c:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001750:	0216      	lsl r0,r0,0x10
8e001752:	020e      	asr r0,r0,0x10
8e001754:	3ecc 0500 	ldr r1,[fp,-0x5]
8e001758:	4d8b 0142 	mov r2,0x146c
8e00175c:	400b 18e2 	movt r2,0x8e00
8e001760:	0952      	jalr r2
8e001762:	0003      	mov r0,0x0
8e001764:	1dbc 0500 	strh r0,[fp,-0x3]
8e001768:	0392      	gid
8e00176a:	051f 0402 	movfs r0,imask
8e00176e:	1dbc 0500 	strh r0,[fp,-0x3]
8e001772:	1fcb 0032 	mov r0,0x3fe
8e001776:	050f 0402 	movts imask,r0
8e00177a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00177e:	4033      	sub r2,r0,0
8e001780:	0410      	bne 8e001788 <bjk_wait_sync+0x80>
8e001782:	1543      	mov r0,0xaa
8e001784:	1ddc 0500 	str r0,[fp,-0x3]
8e001788:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00178c:	2316      	lsl r1,r0,0x18
8e00178e:	2706      	lsr r1,r1,0x18
8e001790:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001794:	2394      	strb r1,[r0,0x7]
8e001796:	01a2      	nop
8e001798:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00179c:	0384      	ldrb r0,[r0,0x7]
8e00179e:	20e2      	mov r1,r0
8e0017a0:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0017a4:	443a      	sub r2,r1,r0
8e0017a6:	f910      	bne 8e001798 <bjk_wait_sync+0x90>
8e0017a8:	0192      	gie
8e0017aa:	01b2      	idle
8e0017ac:	0392      	gid
8e0017ae:	1dac 0500 	ldrh r0,[fp,-0x3]
8e0017b2:	050f 0402 	movts imask,r0
8e0017b6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017ba:	2003      	mov r1,0x0
8e0017bc:	2394      	strb r1,[r0,0x7]
8e0017be:	01a2      	nop
8e0017c0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017c4:	0384      	ldrb r0,[r0,0x7]
8e0017c6:	2033      	sub r1,r0,0
8e0017c8:	fc10      	bne 8e0017c0 <bjk_wait_sync+0xb8>
8e0017ca:	0192      	gie
8e0017cc:	02e0      	b 8e0017d0 <bjk_wait_sync+0xc8>
8e0017ce:	01a2      	nop
8e0017d0:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0017d4:	b41b 2404 	add sp,sp,32
8e0017d8:	194f 0402 	rts

8e0017dc <get_add_simm11>:
8e0017dc:	f75c 2700 	str fp,[sp],-0x6
8e0017e0:	f4ef 2402 	mov fp,sp
8e0017e4:	1ddc 0400 	str r0,[fp,+0x3]
8e0017e8:	0003      	mov r0,0x0
8e0017ea:	1dbc 0401 	strh r0,[fp,+0xb]
8e0017ee:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0017f2:	0113      	add r0,r0,2
8e0017f4:	0024      	ldrh r0,[r0]
8e0017f6:	20e2      	mov r1,r0
8e0017f8:	1fe3      	mov r0,0xff
8e0017fa:	045a      	and r0,r1,r0
8e0017fc:	0076      	lsl r0,r0,0x3
8e0017fe:	20e2      	mov r1,r0
8e001800:	200b 1002 	movt r1,0x0
8e001804:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001808:	0024      	ldrh r0,[r0]
8e00180a:	40e2      	mov r2,r0
8e00180c:	100b 0032 	mov r0,0x380
8e001810:	085a      	and r0,r2,r0
8e001812:	00ee      	asr r0,r0,0x7
8e001814:	000b 1002 	movt r0,0x0
8e001818:	047a      	orr r0,r1,r0
8e00181a:	000b 1002 	movt r0,0x0
8e00181e:	1dbc 0401 	strh r0,[fp,+0xb]
8e001822:	1f1b 0402 	add r0,fp,22
8e001826:	0093      	add r0,r0,1
8e001828:	0004      	ldrb r0,[r0]
8e00182a:	0046      	lsr r0,r0,0x2
8e00182c:	0316      	lsl r0,r0,0x18
8e00182e:	0306      	lsr r0,r0,0x18
8e001830:	20e2      	mov r1,r0
8e001832:	0023      	mov r0,0x1
8e001834:	045a      	and r0,r1,r0
8e001836:	2033      	sub r1,r0,0
8e001838:	1000      	beq 8e001858 <get_add_simm11+0x7c>
8e00183a:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00183e:	20e2      	mov r1,r0
8e001840:	200b 1002 	movt r1,0x0
8e001844:	000b 0f82 	mov r0,0xf800
8e001848:	1feb 1ff2 	movt r0,0xffff
8e00184c:	040a      	eor r0,r1,r0
8e00184e:	000b 1002 	movt r0,0x0
8e001852:	000b 1002 	movt r0,0x0
8e001856:	03e0      	b 8e00185c <get_add_simm11+0x80>
8e001858:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00185c:	1dbc 0401 	strh r0,[fp,+0xb]
8e001860:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001864:	0216      	lsl r0,r0,0x10
8e001866:	020e      	asr r0,r0,0x10
8e001868:	f74c 2400 	ldr fp,[sp,+0x6]
8e00186c:	b41b 2403 	add sp,sp,24
8e001870:	194f 0402 	rts

8e001874 <get_call_opcode>:
8e001874:	f65c 2700 	str fp,[sp],-0x4
8e001878:	f4ef 2402 	mov fp,sp
8e00187c:	1ddc 0400 	str r0,[fp,+0x3]
8e001880:	04e2      	mov r0,r1
8e001882:	1e3c 0400 	strh r0,[fp,+0x4]
8e001886:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00188a:	2f8b 0d42 	mov r1,0xd47c
8e00188e:	3feb 1ff2 	movt r1,0xffff
8e001892:	2034      	strh r1,[r0]
8e001894:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001898:	0113      	add r0,r0,2
8e00189a:	200b 0272 	mov r1,0x2700
8e00189e:	2034      	strh r1,[r0]
8e0018a0:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018a4:	0024      	ldrh r0,[r0]
8e0018a6:	20e2      	mov r1,r0
8e0018a8:	200b 1002 	movt r1,0x0
8e0018ac:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0018b0:	40e2      	mov r2,r0
8e0018b2:	00e3      	mov r0,0x7
8e0018b4:	085a      	and r0,r2,r0
8e0018b6:	00f6      	lsl r0,r0,0x7
8e0018b8:	000b 1002 	movt r0,0x0
8e0018bc:	047a      	orr r0,r1,r0
8e0018be:	000b 1002 	movt r0,0x0
8e0018c2:	20e2      	mov r1,r0
8e0018c4:	200b 1002 	movt r1,0x0
8e0018c8:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018cc:	2034      	strh r1,[r0]
8e0018ce:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018d2:	2113      	add r1,r0,2
8e0018d4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018d8:	0113      	add r0,r0,2
8e0018da:	0024      	ldrh r0,[r0]
8e0018dc:	40e2      	mov r2,r0
8e0018de:	400b 1002 	movt r2,0x0
8e0018e2:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0018e6:	0216      	lsl r0,r0,0x10
8e0018e8:	020e      	asr r0,r0,0x10
8e0018ea:	006e      	asr r0,r0,0x3
8e0018ec:	000b 1002 	movt r0,0x0
8e0018f0:	087a      	orr r0,r2,r0
8e0018f2:	000b 1002 	movt r0,0x0
8e0018f6:	000b 1002 	movt r0,0x0
8e0018fa:	0434      	strh r0,[r1]
8e0018fc:	01a2      	nop
8e0018fe:	f64c 2400 	ldr fp,[sp,+0x4]
8e001902:	b41b 2402 	add sp,sp,16
8e001906:	194f 0402 	rts
8e00190a:	01a2      	nop

8e00190c <find_call>:
8e00190c:	f75c 2700 	str fp,[sp],-0x6
8e001910:	f4ef 2402 	mov fp,sp
8e001914:	1ddc 0400 	str r0,[fp,+0x3]
8e001918:	3d5c 0400 	str r1,[fp,+0x2]
8e00191c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001920:	1edc 0400 	str r0,[fp,+0x5]
8e001924:	108b 0032 	mov r0,0x384
8e001928:	000b 1002 	movt r0,0x0
8e00192c:	0044      	ldr r0,[r0]
8e00192e:	001b 0037 	add r0,r0,440
8e001932:	1e5c 0400 	str r0,[fp,+0x4]
8e001936:	1e4c 0400 	ldr r0,[fp,+0x4]
8e00193a:	2003      	mov r1,0x0
8e00193c:	2034      	strh r1,[r0]
8e00193e:	35e0      	b 8e0019a8 <find_call+0x9c>
8e001940:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001944:	2024      	ldrh r1,[r0]
8e001946:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00194a:	0024      	ldrh r0,[r0]
8e00194c:	443a      	sub r2,r1,r0
8e00194e:	1110      	bne 8e001970 <find_call+0x64>
8e001950:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001954:	0113      	add r0,r0,2
8e001956:	2024      	ldrh r1,[r0]
8e001958:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00195c:	0113      	add r0,r0,2
8e00195e:	0024      	ldrh r0,[r0]
8e001960:	443a      	sub r2,r1,r0
8e001962:	0710      	bne 8e001970 <find_call+0x64>
8e001964:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001968:	3dcb 01e2 	mov r1,0x1eee
8e00196c:	2034      	strh r1,[r0]
8e00196e:	21e0      	b 8e0019b0 <find_call+0xa4>
8e001970:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001974:	2024      	ldrh r1,[r0]
8e001976:	09eb 0192 	mov r0,0x194f
8e00197a:	443a      	sub r2,r1,r0
8e00197c:	1110      	bne 8e00199e <find_call+0x92>
8e00197e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001982:	0113      	add r0,r0,2
8e001984:	2024      	ldrh r1,[r0]
8e001986:	004b 0042 	mov r0,0x402
8e00198a:	443a      	sub r2,r1,r0
8e00198c:	0910      	bne 8e00199e <find_call+0x92>
8e00198e:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001992:	2223      	mov r1,0x11
8e001994:	2034      	strh r1,[r0]
8e001996:	0003      	mov r0,0x0
8e001998:	1edc 0400 	str r0,[fp,+0x5]
8e00199c:	0ae0      	b 8e0019b0 <find_call+0xa4>
8e00199e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019a2:	0313      	add r0,r0,-2
8e0019a4:	1edc 0400 	str r0,[fp,+0x5]
8e0019a8:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019ac:	2033      	sub r1,r0,0
8e0019ae:	c910      	bne 8e001940 <find_call+0x34>
8e0019b0:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019b4:	f74c 2400 	ldr fp,[sp,+0x6]
8e0019b8:	b41b 2403 	add sp,sp,24
8e0019bc:	194f 0402 	rts

8e0019c0 <find_interrupt_call>:
8e0019c0:	f75c 2700 	str fp,[sp],-0x6
8e0019c4:	f4ef 2402 	mov fp,sp
8e0019c8:	1ddc 0400 	str r0,[fp,+0x3]
8e0019cc:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0019d0:	1edc 0400 	str r0,[fp,+0x5]
8e0019d4:	108b 0032 	mov r0,0x384
8e0019d8:	000b 1002 	movt r0,0x0
8e0019dc:	0044      	ldr r0,[r0]
8e0019de:	001b 0037 	add r0,r0,440
8e0019e2:	1e5c 0400 	str r0,[fp,+0x4]
8e0019e6:	1e4c 0400 	ldr r0,[fp,+0x4]
8e0019ea:	2003      	mov r1,0x0
8e0019ec:	2034      	strh r1,[r0]
8e0019ee:	4de0      	b 8e001a88 <find_interrupt_call+0xc8>
8e0019f0:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019f4:	2024      	ldrh r1,[r0]
8e0019f6:	1f8b 0142 	mov r0,0x14fc
8e0019fa:	443a      	sub r2,r1,r0
8e0019fc:	2a10      	bne 8e001a50 <find_interrupt_call+0x90>
8e0019fe:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a02:	0113      	add r0,r0,2
8e001a04:	2024      	ldrh r1,[r0]
8e001a06:	000b 0052 	mov r0,0x500
8e001a0a:	443a      	sub r2,r1,r0
8e001a0c:	2210      	bne 8e001a50 <find_interrupt_call+0x90>
8e001a0e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a12:	021b 0000 	add r0,r0,4
8e001a16:	2024      	ldrh r1,[r0]
8e001a18:	024b 0052 	mov r0,0x512
8e001a1c:	443a      	sub r2,r1,r0
8e001a1e:	1910      	bne 8e001a50 <find_interrupt_call+0x90>
8e001a20:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a24:	031b 0000 	add r0,r0,6
8e001a28:	2024      	ldrh r1,[r0]
8e001a2a:	03eb 0212 	mov r0,0x211f
8e001a2e:	443a      	sub r2,r1,r0
8e001a30:	1010      	bne 8e001a50 <find_interrupt_call+0x90>
8e001a32:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a36:	001b 0001 	add r0,r0,8
8e001a3a:	2024      	ldrh r1,[r0]
8e001a3c:	004b 0042 	mov r0,0x402
8e001a40:	443a      	sub r2,r1,r0
8e001a42:	0710      	bne 8e001a50 <find_interrupt_call+0x90>
8e001a44:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001a48:	3dcb 02e2 	mov r1,0x2eee
8e001a4c:	2034      	strh r1,[r0]
8e001a4e:	21e0      	b 8e001a90 <find_interrupt_call+0xd0>
8e001a50:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a54:	2024      	ldrh r1,[r0]
8e001a56:	09eb 0192 	mov r0,0x194f
8e001a5a:	443a      	sub r2,r1,r0
8e001a5c:	1110      	bne 8e001a7e <find_interrupt_call+0xbe>
8e001a5e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a62:	0113      	add r0,r0,2
8e001a64:	2024      	ldrh r1,[r0]
8e001a66:	004b 0042 	mov r0,0x402
8e001a6a:	443a      	sub r2,r1,r0
8e001a6c:	0910      	bne 8e001a7e <find_interrupt_call+0xbe>
8e001a6e:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001a72:	2423      	mov r1,0x21
8e001a74:	2034      	strh r1,[r0]
8e001a76:	0003      	mov r0,0x0
8e001a78:	1edc 0400 	str r0,[fp,+0x5]
8e001a7c:	0ae0      	b 8e001a90 <find_interrupt_call+0xd0>
8e001a7e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a82:	0313      	add r0,r0,-2
8e001a84:	1edc 0400 	str r0,[fp,+0x5]
8e001a88:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a8c:	2033      	sub r1,r0,0
8e001a8e:	b110      	bne 8e0019f0 <find_interrupt_call+0x30>
8e001a90:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a94:	f74c 2400 	ldr fp,[sp,+0x6]
8e001a98:	b41b 2403 	add sp,sp,24
8e001a9c:	194f 0402 	rts

8e001aa0 <find_rts>:
8e001aa0:	f45c 2701 	str fp,[sp],-0x8
8e001aa4:	f4ef 2402 	mov fp,sp
8e001aa8:	1ddc 0400 	str r0,[fp,+0x3]
8e001aac:	3dcc 0400 	ldr r1,[fp,+0x3]
8e001ab0:	000b 0802 	mov r0,0x8000
8e001ab4:	041a      	add r0,r1,r0
8e001ab6:	1f5c 0400 	str r0,[fp,+0x6]
8e001aba:	108b 0032 	mov r0,0x384
8e001abe:	000b 1002 	movt r0,0x0
8e001ac2:	0044      	ldr r0,[r0]
8e001ac4:	001b 0037 	add r0,r0,440
8e001ac8:	1edc 0400 	str r0,[fp,+0x5]
8e001acc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001ad0:	2003      	mov r1,0x0
8e001ad2:	2034      	strh r1,[r0]
8e001ad4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001ad8:	1fdc 0400 	str r0,[fp,+0x7]
8e001adc:	45e0      	b 8e001b66 <find_rts+0xc6>
8e001ade:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001ae2:	2024      	ldrh r1,[r0]
8e001ae4:	09eb 0192 	mov r0,0x194f
8e001ae8:	443a      	sub r2,r1,r0
8e001aea:	0f10      	bne 8e001b08 <find_rts+0x68>
8e001aec:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001af0:	0113      	add r0,r0,2
8e001af2:	2024      	ldrh r1,[r0]
8e001af4:	004b 0042 	mov r0,0x402
8e001af8:	443a      	sub r2,r1,r0
8e001afa:	0710      	bne 8e001b08 <find_rts+0x68>
8e001afc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b00:	3dcb 04e2 	mov r1,0x4eee
8e001b04:	2034      	strh r1,[r0]
8e001b06:	36e0      	b 8e001b72 <find_rts+0xd2>
8e001b08:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b0c:	0024      	ldrh r0,[r0]
8e001b0e:	213b 003a 	sub r1,r0,466
8e001b12:	2510      	bne 8e001b5c <find_rts+0xbc>
8e001b14:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b18:	031b 00fe 	add r0,r0,-10
8e001b1c:	2024      	ldrh r1,[r0]
8e001b1e:	004b 0052 	mov r0,0x502
8e001b22:	443a      	sub r2,r1,r0
8e001b24:	1c10      	bne 8e001b5c <find_rts+0xbc>
8e001b26:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b2a:	001b 00ff 	add r0,r0,-8
8e001b2e:	2024      	ldrh r1,[r0]
8e001b30:	01eb 0212 	mov r0,0x210f
8e001b34:	443a      	sub r2,r1,r0
8e001b36:	1310      	bne 8e001b5c <find_rts+0xbc>
8e001b38:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b3c:	011b 00ff 	add r0,r0,-6
8e001b40:	2024      	ldrh r1,[r0]
8e001b42:	004b 0042 	mov r0,0x402
8e001b46:	443a      	sub r2,r1,r0
8e001b48:	0a10      	bne 8e001b5c <find_rts+0xbc>
8e001b4a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b4e:	2823      	mov r1,0x41
8e001b50:	2034      	strh r1,[r0]
8e001b52:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001b56:	1fdc 0400 	str r0,[fp,+0x7]
8e001b5a:	0ce0      	b 8e001b72 <find_rts+0xd2>
8e001b5c:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b60:	0113      	add r0,r0,2
8e001b62:	1fdc 0400 	str r0,[fp,+0x7]
8e001b66:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b6a:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001b6e:	443a      	sub r2,r1,r0
8e001b70:	b750      	bltu 8e001ade <find_rts+0x3e>
8e001b72:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b76:	0024      	ldrh r0,[r0]
8e001b78:	20bb 0008 	sub r1,r0,65
8e001b7c:	0310      	bne 8e001b82 <find_rts+0xe2>
8e001b7e:	0003      	mov r0,0x0
8e001b80:	1de0      	b 8e001bba <find_rts+0x11a>
8e001b82:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b86:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001b8a:	443a      	sub r2,r1,r0
8e001b8c:	0710      	bne 8e001b9a <find_rts+0xfa>
8e001b8e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b92:	2843      	mov r1,0x42
8e001b94:	2034      	strh r1,[r0]
8e001b96:	0003      	mov r0,0x0
8e001b98:	11e0      	b 8e001bba <find_rts+0x11a>
8e001b9a:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b9e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001ba2:	043a      	sub r0,r1,r0
8e001ba4:	002e      	asr r0,r0,0x1
8e001ba6:	20b3      	sub r1,r0,1
8e001ba8:	0720      	bgtu 8e001bb6 <find_rts+0x116>
8e001baa:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001bae:	2863      	mov r1,0x43
8e001bb0:	2034      	strh r1,[r0]
8e001bb2:	0003      	mov r0,0x0
8e001bb4:	03e0      	b 8e001bba <find_rts+0x11a>
8e001bb6:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001bba:	f44c 2401 	ldr fp,[sp,+0x8]
8e001bbe:	b41b 2404 	add sp,sp,32
8e001bc2:	194f 0402 	rts
8e001bc6:	01a2      	nop

8e001bc8 <get_sp_disp>:
8e001bc8:	f65c 2701 	str fp,[sp],-0xc
8e001bcc:	f4ef 2402 	mov fp,sp
8e001bd0:	1ddc 0400 	str r0,[fp,+0x3]
8e001bd4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001bd8:	1ddc 0401 	str r0,[fp,+0xb]
8e001bdc:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001be0:	0213      	add r0,r0,-4
8e001be2:	1ddc 0401 	str r0,[fp,+0xb]
8e001be6:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001bea:	0024      	ldrh r0,[r0]
8e001bec:	1ebc 0402 	strh r0,[fp,+0x15]
8e001bf0:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001bf4:	00a4      	ldrh r0,[r0,0x1]
8e001bf6:	1e3c 0402 	strh r0,[fp,+0x14]
8e001bfa:	108b 0032 	mov r0,0x384
8e001bfe:	000b 1002 	movt r0,0x0
8e001c02:	0044      	ldr r0,[r0]
8e001c04:	001b 0037 	add r0,r0,440
8e001c08:	1cdc 0401 	str r0,[fp,+0x9]
8e001c0c:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c10:	2003      	mov r1,0x0
8e001c12:	2034      	strh r1,[r0]
8e001c14:	3eac 0402 	ldrh r1,[fp,+0x15]
8e001c18:	01eb 0f02 	mov r0,0xf00f
8e001c1c:	245a      	and r1,r1,r0
8e001c1e:	016b 0b02 	mov r0,0xb00b
8e001c22:	443a      	sub r2,r1,r0
8e001c24:	0800      	beq 8e001c34 <get_sp_disp+0x6c>
8e001c26:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c2a:	2623      	mov r1,0x31
8e001c2c:	2034      	strh r1,[r0]
8e001c2e:	0003      	mov r0,0x0
8e001c30:	8fe8 0000 	b 8e001d4e <get_sp_disp+0x186>
8e001c34:	3e2c 0402 	ldrh r1,[fp,+0x14]
8e001c38:	000b 0ff2 	mov r0,0xff00
8e001c3c:	245a      	and r1,r1,r0
8e001c3e:	000b 0242 	mov r0,0x2400
8e001c42:	443a      	sub r2,r1,r0
8e001c44:	0700      	beq 8e001c52 <get_sp_disp+0x8a>
8e001c46:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c4a:	2643      	mov r1,0x32
8e001c4c:	2034      	strh r1,[r0]
8e001c4e:	0003      	mov r0,0x0
8e001c50:	7fe0      	b 8e001d4e <get_sp_disp+0x186>
8e001c52:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c56:	1c5c 0401 	str r0,[fp,+0x8]
8e001c5a:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c5e:	0213      	add r0,r0,-4
8e001c60:	1ddc 0401 	str r0,[fp,+0xb]
8e001c64:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c68:	0024      	ldrh r0,[r0]
8e001c6a:	1ebc 0402 	strh r0,[fp,+0x15]
8e001c6e:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c72:	00a4      	ldrh r0,[r0,0x1]
8e001c74:	1e3c 0402 	strh r0,[fp,+0x14]
8e001c78:	3eac 0402 	ldrh r1,[fp,+0x15]
8e001c7c:	01eb 0f02 	mov r0,0xf00f
8e001c80:	245a      	and r1,r1,r0
8e001c82:	018b 0d02 	mov r0,0xd00c
8e001c86:	443a      	sub r2,r1,r0
8e001c88:	0700      	beq 8e001c96 <get_sp_disp+0xce>
8e001c8a:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c8e:	2663      	mov r1,0x33
8e001c90:	2034      	strh r1,[r0]
8e001c92:	0003      	mov r0,0x0
8e001c94:	5de0      	b 8e001d4e <get_sp_disp+0x186>
8e001c96:	3e2c 0402 	ldrh r1,[fp,+0x14]
8e001c9a:	000b 0f02 	mov r0,0xf000
8e001c9e:	245a      	and r1,r1,r0
8e001ca0:	000b 0202 	mov r0,0x2000
8e001ca4:	443a      	sub r2,r1,r0
8e001ca6:	0700      	beq 8e001cb4 <get_sp_disp+0xec>
8e001ca8:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001cac:	2683      	mov r1,0x34
8e001cae:	2034      	strh r1,[r0]
8e001cb0:	0003      	mov r0,0x0
8e001cb2:	4ee0      	b 8e001d4e <get_sp_disp+0x186>
8e001cb4:	1c4c 0401 	ldr r0,[fp,+0x8]
8e001cb8:	1f5c 0400 	str r0,[fp,+0x6]
8e001cbc:	0003      	mov r0,0x0
8e001cbe:	1dbc 0401 	strh r0,[fp,+0xb]
8e001cc2:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001cc6:	0113      	add r0,r0,2
8e001cc8:	0024      	ldrh r0,[r0]
8e001cca:	20e2      	mov r1,r0
8e001ccc:	1fe3      	mov r0,0xff
8e001cce:	045a      	and r0,r1,r0
8e001cd0:	0076      	lsl r0,r0,0x3
8e001cd2:	20e2      	mov r1,r0
8e001cd4:	200b 1002 	movt r1,0x0
8e001cd8:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001cdc:	0024      	ldrh r0,[r0]
8e001cde:	40e2      	mov r2,r0
8e001ce0:	100b 0032 	mov r0,0x380
8e001ce4:	085a      	and r0,r2,r0
8e001ce6:	00ee      	asr r0,r0,0x7
8e001ce8:	000b 1002 	movt r0,0x0
8e001cec:	047a      	orr r0,r1,r0
8e001cee:	000b 1002 	movt r0,0x0
8e001cf2:	1dbc 0401 	strh r0,[fp,+0xb]
8e001cf6:	1f1b 0402 	add r0,fp,22
8e001cfa:	0093      	add r0,r0,1
8e001cfc:	0004      	ldrb r0,[r0]
8e001cfe:	0046      	lsr r0,r0,0x2
8e001d00:	0316      	lsl r0,r0,0x18
8e001d02:	0306      	lsr r0,r0,0x18
8e001d04:	20e2      	mov r1,r0
8e001d06:	0023      	mov r0,0x1
8e001d08:	045a      	and r0,r1,r0
8e001d0a:	2033      	sub r1,r0,0
8e001d0c:	1000      	beq 8e001d2c <get_sp_disp+0x164>
8e001d0e:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001d12:	20e2      	mov r1,r0
8e001d14:	200b 1002 	movt r1,0x0
8e001d18:	000b 0f82 	mov r0,0xf800
8e001d1c:	1feb 1ff2 	movt r0,0xffff
8e001d20:	040a      	eor r0,r1,r0
8e001d22:	000b 1002 	movt r0,0x0
8e001d26:	000b 1002 	movt r0,0x0
8e001d2a:	03e0      	b 8e001d30 <get_sp_disp+0x168>
8e001d2c:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001d30:	1dbc 0401 	strh r0,[fp,+0xb]
8e001d34:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001d38:	000b 1002 	movt r0,0x0
8e001d3c:	1fbc 0401 	strh r0,[fp,+0xf]
8e001d40:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001d44:	3dcb 03e2 	mov r1,0x3eee
8e001d48:	2034      	strh r1,[r0]
8e001d4a:	1fac 0401 	ldrh r0,[fp,+0xf]
8e001d4e:	0216      	lsl r0,r0,0x10
8e001d50:	020e      	asr r0,r0,0x10
8e001d52:	f64c 2401 	ldr fp,[sp,+0xc]
8e001d56:	b41b 2406 	add sp,sp,48
8e001d5a:	194f 0402 	rts
8e001d5e:	01a2      	nop

8e001d60 <umm_info>:
8e001d60:	d6fc 2700 	strd lr,[sp],-0x5
8e001d64:	f41b 2405 	add fp,sp,40
8e001d68:	1edc 0500 	str r0,[fp,-0x5]
8e001d6c:	3f5c 0500 	str r1,[fp,-0x6]
8e001d70:	5fdc 0500 	str r2,[fp,-0x7]
8e001d74:	0003      	mov r0,0x0
8e001d76:	1cbc 0500 	strh r0,[fp,-0x1]
8e001d7a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001d7e:	1d5c 0500 	str r0,[fp,-0x2]
8e001d82:	0003      	mov r0,0x0
8e001d84:	1c9c 0501 	strb r0,[fp,-0x9]
8e001d88:	0203      	mov r0,0x10
8e001d8a:	1e5c 0500 	str r0,[fp,-0x4]
8e001d8e:	1c8c 0501 	ldrb r0,[fp,-0x9]
8e001d92:	5e4c 0500 	ldr r2,[fp,-0x4]
8e001d96:	20e2      	mov r1,r0
8e001d98:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001d9c:	6b8b 0032 	mov r3,0x35c
8e001da0:	600b 18e2 	movt r3,0x8e00
8e001da4:	0d52      	jalr r3
8e001da6:	070b 0032 	mov r0,0x338
8e001daa:	000b 1002 	movt r0,0x0
8e001dae:	2044      	ldr r1,[r0]
8e001db0:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001db4:	0076      	lsl r0,r0,0x3
8e001db6:	041a      	add r0,r1,r0
8e001db8:	2004      	ldrb r1,[r0]
8e001dba:	0084      	ldrb r0,[r0,0x1]
8e001dbc:	0116      	lsl r0,r0,0x8
8e001dbe:	00fa      	orr r0,r0,r1
8e001dc0:	20e2      	mov r1,r0
8e001dc2:	200b 1002 	movt r1,0x0
8e001dc6:	1feb 07f2 	mov r0,0x7fff
8e001dca:	045a      	and r0,r1,r0
8e001dcc:	1cbc 0500 	strh r0,[fp,-0x1]
8e001dd0:	cae8 0000 	b 8e001f64 <umm_info+0x204>
8e001dd4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001dd8:	0024      	ldrh r0,[r0]
8e001dda:	0093      	add r0,r0,1
8e001ddc:	20e2      	mov r1,r0
8e001dde:	200b 1002 	movt r1,0x0
8e001de2:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001de6:	2034      	strh r1,[r0]
8e001de8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001dec:	21a4      	ldrh r1,[r0,0x3]
8e001dee:	070b 0032 	mov r0,0x338
8e001df2:	000b 1002 	movt r0,0x0
8e001df6:	4044      	ldr r2,[r0]
8e001df8:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001dfc:	0076      	lsl r0,r0,0x3
8e001dfe:	081a      	add r0,r2,r0
8e001e00:	4004      	ldrb r2,[r0]
8e001e02:	0084      	ldrb r0,[r0,0x1]
8e001e04:	0116      	lsl r0,r0,0x8
8e001e06:	017a      	orr r0,r0,r2
8e001e08:	40e2      	mov r2,r0
8e001e0a:	400b 1002 	movt r2,0x0
8e001e0e:	1feb 07f2 	mov r0,0x7fff
8e001e12:	085a      	and r0,r2,r0
8e001e14:	40e2      	mov r2,r0
8e001e16:	400b 1002 	movt r2,0x0
8e001e1a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e1e:	083a      	sub r0,r2,r0
8e001e20:	000b 1002 	movt r0,0x0
8e001e24:	041a      	add r0,r1,r0
8e001e26:	20e2      	mov r1,r0
8e001e28:	200b 1002 	movt r1,0x0
8e001e2c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e30:	21b4      	strh r1,[r0,0x3]
8e001e32:	070b 0032 	mov r0,0x338
8e001e36:	000b 1002 	movt r0,0x0
8e001e3a:	2044      	ldr r1,[r0]
8e001e3c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e40:	0076      	lsl r0,r0,0x3
8e001e42:	041a      	add r0,r1,r0
8e001e44:	2004      	ldrb r1,[r0]
8e001e46:	0084      	ldrb r0,[r0,0x1]
8e001e48:	0116      	lsl r0,r0,0x8
8e001e4a:	00fa      	orr r0,r0,r1
8e001e4c:	000b 1002 	movt r0,0x0
8e001e50:	000b 1002 	movt r0,0x0
8e001e54:	0216      	lsl r0,r0,0x10
8e001e56:	020e      	asr r0,r0,0x10
8e001e58:	2033      	sub r1,r0,0
8e001e5a:	4170      	bgte 8e001edc <umm_info+0x17c>
8e001e5c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e60:	0124      	ldrh r0,[r0,0x2]
8e001e62:	0093      	add r0,r0,1
8e001e64:	20e2      	mov r1,r0
8e001e66:	200b 1002 	movt r1,0x0
8e001e6a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e6e:	2134      	strh r1,[r0,0x2]
8e001e70:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e74:	22a4      	ldrh r1,[r0,0x5]
8e001e76:	070b 0032 	mov r0,0x338
8e001e7a:	000b 1002 	movt r0,0x0
8e001e7e:	4044      	ldr r2,[r0]
8e001e80:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e84:	0076      	lsl r0,r0,0x3
8e001e86:	081a      	add r0,r2,r0
8e001e88:	4004      	ldrb r2,[r0]
8e001e8a:	0084      	ldrb r0,[r0,0x1]
8e001e8c:	0116      	lsl r0,r0,0x8
8e001e8e:	017a      	orr r0,r0,r2
8e001e90:	40e2      	mov r2,r0
8e001e92:	400b 1002 	movt r2,0x0
8e001e96:	1feb 07f2 	mov r0,0x7fff
8e001e9a:	085a      	and r0,r2,r0
8e001e9c:	40e2      	mov r2,r0
8e001e9e:	400b 1002 	movt r2,0x0
8e001ea2:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001ea6:	083a      	sub r0,r2,r0
8e001ea8:	000b 1002 	movt r0,0x0
8e001eac:	041a      	add r0,r1,r0
8e001eae:	20e2      	mov r1,r0
8e001eb0:	200b 1002 	movt r1,0x0
8e001eb4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001eb8:	22b4      	strh r1,[r0,0x5]
8e001eba:	070b 0032 	mov r0,0x338
8e001ebe:	000b 1002 	movt r0,0x0
8e001ec2:	2044      	ldr r1,[r0]
8e001ec4:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001ec8:	0076      	lsl r0,r0,0x3
8e001eca:	241a      	add r1,r1,r0
8e001ecc:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001ed0:	443a      	sub r2,r1,r0
8e001ed2:	3410      	bne 8e001f3a <umm_info+0x1da>
8e001ed4:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001ed8:	8be8 0000 	b 8e001fee <umm_info+0x28e>
8e001edc:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ee0:	00a4      	ldrh r0,[r0,0x1]
8e001ee2:	0093      	add r0,r0,1
8e001ee4:	20e2      	mov r1,r0
8e001ee6:	200b 1002 	movt r1,0x0
8e001eea:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001eee:	20b4      	strh r1,[r0,0x1]
8e001ef0:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ef4:	2224      	ldrh r1,[r0,0x4]
8e001ef6:	070b 0032 	mov r0,0x338
8e001efa:	000b 1002 	movt r0,0x0
8e001efe:	4044      	ldr r2,[r0]
8e001f00:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f04:	0076      	lsl r0,r0,0x3
8e001f06:	081a      	add r0,r2,r0
8e001f08:	4004      	ldrb r2,[r0]
8e001f0a:	0084      	ldrb r0,[r0,0x1]
8e001f0c:	0116      	lsl r0,r0,0x8
8e001f0e:	017a      	orr r0,r0,r2
8e001f10:	40e2      	mov r2,r0
8e001f12:	400b 1002 	movt r2,0x0
8e001f16:	1feb 07f2 	mov r0,0x7fff
8e001f1a:	085a      	and r0,r2,r0
8e001f1c:	40e2      	mov r2,r0
8e001f1e:	400b 1002 	movt r2,0x0
8e001f22:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f26:	083a      	sub r0,r2,r0
8e001f28:	000b 1002 	movt r0,0x0
8e001f2c:	041a      	add r0,r1,r0
8e001f2e:	20e2      	mov r1,r0
8e001f30:	200b 1002 	movt r1,0x0
8e001f34:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f38:	2234      	strh r1,[r0,0x4]
8e001f3a:	070b 0032 	mov r0,0x338
8e001f3e:	000b 1002 	movt r0,0x0
8e001f42:	2044      	ldr r1,[r0]
8e001f44:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f48:	0076      	lsl r0,r0,0x3
8e001f4a:	041a      	add r0,r1,r0
8e001f4c:	2004      	ldrb r1,[r0]
8e001f4e:	0084      	ldrb r0,[r0,0x1]
8e001f50:	0116      	lsl r0,r0,0x8
8e001f52:	00fa      	orr r0,r0,r1
8e001f54:	20e2      	mov r1,r0
8e001f56:	200b 1002 	movt r1,0x0
8e001f5a:	1feb 07f2 	mov r0,0x7fff
8e001f5e:	045a      	and r0,r1,r0
8e001f60:	1cbc 0500 	strh r0,[fp,-0x1]
8e001f64:	070b 0032 	mov r0,0x338
8e001f68:	000b 1002 	movt r0,0x0
8e001f6c:	2044      	ldr r1,[r0]
8e001f6e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f72:	0076      	lsl r0,r0,0x3
8e001f74:	041a      	add r0,r1,r0
8e001f76:	2004      	ldrb r1,[r0]
8e001f78:	0084      	ldrb r0,[r0,0x1]
8e001f7a:	0116      	lsl r0,r0,0x8
8e001f7c:	00fa      	orr r0,r0,r1
8e001f7e:	000b 1002 	movt r0,0x0
8e001f82:	20e2      	mov r1,r0
8e001f84:	1feb 07f2 	mov r0,0x7fff
8e001f88:	045a      	and r0,r1,r0
8e001f8a:	2033      	sub r1,r0,0
8e001f8c:	2418 ffff 	bne 8e001dd4 <umm_info+0x74>
8e001f90:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f94:	22a4      	ldrh r1,[r0,0x5]
8e001f96:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f9a:	043a      	sub r0,r1,r0
8e001f9c:	20e2      	mov r1,r0
8e001f9e:	200b 1002 	movt r1,0x0
8e001fa2:	000b 0302 	mov r0,0x3000
8e001fa6:	000b 1002 	movt r0,0x0
8e001faa:	0066      	lsr r0,r0,0x3
8e001fac:	000b 1002 	movt r0,0x0
8e001fb0:	041a      	add r0,r1,r0
8e001fb2:	20e2      	mov r1,r0
8e001fb4:	200b 1002 	movt r1,0x0
8e001fb8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001fbc:	22b4      	strh r1,[r0,0x5]
8e001fbe:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001fc2:	21a4      	ldrh r1,[r0,0x3]
8e001fc4:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001fc8:	043a      	sub r0,r1,r0
8e001fca:	20e2      	mov r1,r0
8e001fcc:	200b 1002 	movt r1,0x0
8e001fd0:	000b 0302 	mov r0,0x3000
8e001fd4:	000b 1002 	movt r0,0x0
8e001fd8:	0066      	lsr r0,r0,0x3
8e001fda:	000b 1002 	movt r0,0x0
8e001fde:	041a      	add r0,r1,r0
8e001fe0:	20e2      	mov r1,r0
8e001fe2:	200b 1002 	movt r1,0x0
8e001fe6:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001fea:	21b4      	strh r1,[r0,0x3]
8e001fec:	0003      	mov r0,0x0
8e001fee:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e001ff2:	b41b 2405 	add sp,sp,40
8e001ff6:	194f 0402 	rts
8e001ffa:	01a2      	nop

8e001ffc <umm_malloc>:
8e001ffc:	967c 0700 	strd r4,[sp],-0x4
8e002000:	d5fc 0400 	strd r6,[sp,+0x3]
8e002004:	157c 2400 	strd r8,[sp,+0x2]
8e002008:	d4fc 2400 	strd lr,[sp,+0x1]
8e00200c:	2033      	sub r1,r0,0
8e00200e:	ac08 0000 	beq 8e002166 <umm_malloc+0x16a>
8e002012:	200b 0242 	mov r1,0x2400
8e002016:	200b 18e2 	movt r1,0x8e00
8e00201a:	0552      	jalr r1
8e00201c:	c70b 0032 	mov r6,0x338
8e002020:	c00b 1002 	movt r6,0x0
8e002024:	984c 2000 	ldr ip,[r6,+0x0]
8e002028:	1feb 47f2 	mov r16,0x7fff
8e00202c:	328c 0400 	ldrb r1,[ip,+0x5]
8e002030:	2516      	lsl r1,r1,0x8
8e002032:	720c 0400 	ldrb r3,[ip,+0x4]
8e002036:	65fa      	orr r3,r1,r3
8e002038:	8ce2      	mov r4,r3
8e00203a:	2003      	mov r1,0x0
8e00203c:	7feb 47f2 	mov r19,0x7fff
8e002040:	5076      	lsl r2,r4,0x3
8e002042:	511f 040a 	add r2,ip,r2
8e002046:	4a8c 4000 	ldrb r18,[r2,+0x5]
8e00204a:	2a0c 4000 	ldrb r17,[r2,+0x4]
8e00204e:	491f 4806 	lsl r18,r18,0x8
8e002052:	28ff 490a 	orr r17,r18,r17
8e002056:	1500      	beq 8e002080 <umm_malloc+0x84>
8e002058:	2804      	ldrb r1,[r2]
8e00205a:	4884      	ldrb r2,[r2,0x1]
8e00205c:	4916      	lsl r2,r2,0x8
8e00205e:	28fa      	orr r1,r2,r1
8e002060:	25df 010a 	and r1,r1,r19
8e002064:	263a      	sub r1,r1,r4
8e002066:	200b 1002 	movt r1,0x0
8e00206a:	40ba      	sub r2,r0,r1
8e00206c:	0720      	bgtu 8e00207a <umm_malloc+0x7e>
8e00206e:	40bf 080a 	sub r2,r16,r1
8e002072:	0440      	blteu 8e00207a <umm_malloc+0x7e>
8e002074:	70e2      	mov r3,r4
8e002076:	04ef 4002 	mov r16,r1
8e00207a:	84ef 0802 	mov r4,r17
8e00207e:	e1e0      	b 8e002040 <umm_malloc+0x44>
8e002080:	5feb 07f2 	mov r2,0x7fff
8e002084:	213f 480a 	sub r17,r16,r2
8e002088:	8c12      	movne r4,r3
8e00208a:	201f 0802 	movne r1,r16
8e00208e:	7076      	lsl r3,r4,0x3
8e002090:	719f 040a 	add r3,ip,r3
8e002094:	4c84      	ldrb r2,[r3,0x1]
8e002096:	0c0c 4000 	ldrb r16,[r3,+0x0]
8e00209a:	4916      	lsl r2,r2,0x8
8e00209c:	487f 010a 	orr r2,r2,r16
8e0020a0:	7feb 07f2 	mov r3,0x7fff
8e0020a4:	49da      	and r2,r2,r3
8e0020a6:	1a00      	beq 8e0020da <umm_malloc+0xde>
8e0020a8:	443a      	sub r2,r1,r0
8e0020aa:	0810      	bne 8e0020ba <umm_malloc+0xbe>
8e0020ac:	368b 0242 	mov r1,0x24b4
8e0020b0:	10e2      	mov r0,r4
8e0020b2:	200b 18e2 	movt r1,0x8e00
8e0020b6:	0552      	jalr r1
8e0020b8:	51e0      	b 8e00215a <umm_malloc+0x15e>
8e0020ba:	a43a      	sub r5,r1,r0
8e0020bc:	a00b 1002 	movt r5,0x0
8e0020c0:	638b 0242 	mov r3,0x241c
8e0020c4:	10e2      	mov r0,r4
8e0020c6:	400b 0802 	mov r2,0x8000
8e0020ca:	34e2      	mov r1,r5
8e0020cc:	600b 18e2 	movt r3,0x8e00
8e0020d0:	929a      	add r4,r4,r5
8e0020d2:	0d52      	jalr r3
8e0020d4:	800b 1002 	movt r4,0x0
8e0020d8:	41e0      	b 8e00215a <umm_malloc+0x15e>
8e0020da:	200b 0302 	mov r1,0x3000
8e0020de:	501a      	add r2,r4,r0
8e0020e0:	200b 1002 	movt r1,0x0
8e0020e4:	4893      	add r2,r2,1
8e0020e6:	2466      	lsr r1,r1,0x3
8e0020e8:	68ba      	sub r3,r2,r1
8e0020ea:	3e30      	bgteu 8e002166 <umm_malloc+0x16a>
8e0020ec:	303b 4000 	sub r17,r4,0
8e0020f0:	0a10      	bne 8e002104 <umm_malloc+0x108>
8e0020f2:	4023      	mov r2,0x1
8e0020f4:	909c 0400 	strb r4,[ip,+0x1]
8e0020f8:	501c 0400 	strb r2,[ip]
8e0020fc:	3844      	ldr r1,[r6]
8e0020fe:	8694      	strb r4,[r1,0x5]
8e002100:	8023      	mov r4,0x1
8e002102:	4614      	strb r2,[r1,0x4]
8e002104:	7844      	ldr r3,[r6]
8e002106:	f076      	lsl r7,r4,0x3
8e002108:	2f9a      	add r1,r3,r7
8e00210a:	4784      	ldrb r2,[r1,0x7]
8e00210c:	b01a      	add r5,r4,r0
8e00210e:	4916      	lsl r2,r2,0x8
8e002110:	0704      	ldrb r0,[r1,0x6]
8e002112:	14ef 2002 	mov r8,r5
8e002116:	487a      	orr r2,r2,r0
8e002118:	000b 3002 	movt r8,0x0
8e00211c:	b476      	lsl r5,r5,0x3
8e00211e:	4876      	lsl r2,r2,0x3
8e002120:	3feb 2002 	mov r9,0xff
8e002124:	4d1a      	add r2,r3,r2
8e002126:	20df 248a 	and r9,r8,r9
8e00212a:	0e9a      	add r0,r3,r5
8e00212c:	010f 2406 	lsr r8,r8,0x8
8e002130:	6e8b 0032 	mov r3,0x374
8e002134:	2a1c 2000 	strb r9,[r2,+0x4]
8e002138:	0a9c 2000 	strb r8,[r2,+0x5]
8e00213c:	600b 18e2 	movt r3,0x8e00
8e002140:	4103      	mov r2,0x8
8e002142:	0d52      	jalr r3
8e002144:	1844      	ldr r0,[r6]
8e002146:	2399 2000 	strb r9,[r0,+r7]
8e00214a:	e39a      	add r7,r0,r7
8e00214c:	1c9c 2000 	strb r8,[r7,+0x1]
8e002150:	1844      	ldr r0,[r6]
8e002152:	a29a      	add r5,r0,r5
8e002154:	1106      	lsr r0,r4,0x8
8e002156:	9514      	strb r4,[r5,0x2]
8e002158:	1594      	strb r0,[r5,0x3]
8e00215a:	1844      	ldr r0,[r6]
8e00215c:	9076      	lsl r4,r4,0x3
8e00215e:	021a      	add r0,r0,r4
8e002160:	021b 0000 	add r0,r0,4
8e002164:	02e0      	b 8e002168 <umm_malloc+0x16c>
8e002166:	0003      	mov r0,0x0
8e002168:	d5ec 0400 	ldrd r6,[sp,+0x3]
8e00216c:	156c 2400 	ldrd r8,[sp,+0x2]
8e002170:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002174:	b41b 2404 	add sp,sp,32
8e002178:	946c 0400 	ldrd r4,[sp,+0x0]
8e00217c:	194f 0402 	rts

8e002180 <umm_realloc>:
8e002180:	96fc 0700 	strd r4,[sp],-0x5
8e002184:	d67c 0400 	strd r6,[sp,+0x4]
8e002188:	15fc 2400 	strd r8,[sp,+0x3]
8e00218c:	557c 2400 	strd r10,[sp,+0x2]
8e002190:	d4fc 2400 	strd lr,[sp,+0x1]
8e002194:	c05a      	and r6,r0,r0
8e002196:	e4e2      	mov r7,r1
8e002198:	1310      	bne 8e0021be <umm_realloc+0x3e>
8e00219a:	d66c 0400 	ldrd r6,[sp,+0x4]
8e00219e:	15ec 2400 	ldrd r8,[sp,+0x3]
8e0021a2:	556c 2400 	ldrd r10,[sp,+0x2]
8e0021a6:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0021aa:	b41b 2405 	add sp,sp,40
8e0021ae:	04e2      	mov r0,r1
8e0021b0:	946c 0400 	ldrd r4,[sp,+0x0]
8e0021b4:	3f8b 01f2 	mov r1,0x1ffc
8e0021b8:	200b 18e2 	movt r1,0x8e00
8e0021bc:	0542      	jr r1
8e0021be:	3c33      	sub r1,r7,0
8e0021c0:	0910      	bne 8e0021d2 <umm_realloc+0x52>
8e0021c2:	278b 0232 	mov r1,0x233c
8e0021c6:	200b 18e2 	movt r1,0x8e00
8e0021ca:	0552      	jalr r1
8e0021cc:	0003      	mov r0,0x0
8e0021ce:	a9e8 0000 	b 8e002320 <umm_realloc+0x1a0>
8e0021d2:	200b 0242 	mov r1,0x2400
8e0021d6:	200b 18e2 	movt r1,0x8e00
8e0021da:	1ce2      	mov r0,r7
8e0021dc:	0552      	jalr r1
8e0021de:	670b 2032 	mov r11,0x338
8e0021e2:	600b 3002 	movt r11,0x0
8e0021e6:	a0e2      	mov r5,r0
8e0021e8:	0c4c 0400 	ldr r0,[r11,+0x0]
8e0021ec:	183f 200a 	sub r8,r6,r0
8e0021f0:	006f 2406 	lsr r8,r8,0x3
8e0021f4:	40ef 2402 	mov r10,r8
8e0021f8:	400b 3002 	movt r10,0x0
8e0021fc:	287f 2406 	lsl r9,r10,0x3
8e002200:	2089 0080 	ldrb r1,[r0,+r9]
8e002204:	009f 008a 	add r0,r0,r9
8e002208:	8084      	ldrb r4,[r0,0x1]
8e00220a:	9116      	lsl r4,r4,0x8
8e00220c:	90fa      	orr r4,r4,r1
8e00220e:	913f 008a 	sub r4,r4,r10
8e002212:	800b 1002 	movt r4,0x0
8e002216:	563a      	sub r2,r5,r4
8e002218:	8308 0000 	beq 8e00231e <umm_realloc+0x19e>
8e00221c:	238b 0252 	mov r1,0x251c
8e002220:	08ef 0402 	mov r0,r10
8e002224:	200b 18e2 	movt r1,0x8e00
8e002228:	0552      	jalr r1
8e00222a:	6c4c 0400 	ldr r3,[r11,+0x0]
8e00222e:	9076      	lsl r4,r4,0x3
8e002230:	2c9f 008a 	add r1,r3,r9
8e002234:	0584      	ldrb r0,[r1,0x3]
8e002236:	4504      	ldrb r2,[r1,0x2]
8e002238:	0116      	lsl r0,r0,0x8
8e00223a:	017a      	orr r0,r0,r2
8e00223c:	4076      	lsl r2,r0,0x3
8e00223e:	4d1a      	add r2,r3,r2
8e002240:	4884      	ldrb r2,[r2,0x1]
8e002242:	9213      	add r4,r4,-4
8e002244:	48e6      	lsr r2,r2,0x7
8e002246:	6833      	sub r3,r2,0
8e002248:	2c00      	beq 8e0022a0 <umm_realloc+0x120>
8e00224a:	4404      	ldrb r2,[r1]
8e00224c:	2484      	ldrb r1,[r1,0x1]
8e00224e:	2516      	lsl r1,r1,0x8
8e002250:	257a      	orr r1,r1,r2
8e002252:	243a      	sub r1,r1,r0
8e002254:	54ba      	sub r2,r5,r1
8e002256:	2560      	bgt 8e0022a0 <umm_realloc+0x120>
8e002258:	368b 0242 	mov r1,0x24b4
8e00225c:	200b 18e2 	movt r1,0x8e00
8e002260:	0552      	jalr r1
8e002262:	570b 0252 	mov r2,0x25b8
8e002266:	2003      	mov r1,0x0
8e002268:	08ef 0402 	mov r0,r10
8e00226c:	400b 18e2 	movt r2,0x8e00
8e002270:	0952      	jalr r2
8e002272:	007f 2006 	lsl r8,r0,0x3
8e002276:	40ef 2002 	mov r10,r0
8e00227a:	0c4c 0400 	ldr r0,[r11,+0x0]
8e00227e:	718b 0032 	mov r3,0x38c
8e002282:	001f 008a 	add r0,r0,r8
8e002286:	38e2      	mov r1,r6
8e002288:	50e2      	mov r2,r4
8e00228a:	021b 0000 	add r0,r0,4
8e00228e:	600b 18e2 	movt r3,0x8e00
8e002292:	0d52      	jalr r3
8e002294:	0c4c 0400 	ldr r0,[r11,+0x0]
8e002298:	001f 008a 	add r0,r0,r8
8e00229c:	c21b 0000 	add r6,r0,4
8e0022a0:	2c4c 0400 	ldr r1,[r11,+0x0]
8e0022a4:	087f 0406 	lsl r0,r10,0x3
8e0022a8:	241a      	add r1,r1,r0
8e0022aa:	0484      	ldrb r0,[r1,0x1]
8e0022ac:	4404      	ldrb r2,[r1]
8e0022ae:	0116      	lsl r0,r0,0x8
8e0022b0:	017a      	orr r0,r0,r2
8e0022b2:	013f 008a 	sub r0,r0,r10
8e0022b6:	000b 1002 	movt r0,0x0
8e0022ba:	743a      	sub r3,r5,r0
8e0022bc:	3100      	beq 8e00231e <umm_realloc+0x19e>
8e0022be:	078b 2232 	mov r8,0x233c
8e0022c2:	000b 38e2 	movt r8,0x8e00
8e0022c6:	1830      	bgteu 8e0022f6 <umm_realloc+0x176>
8e0022c8:	638b 0242 	mov r3,0x241c
8e0022cc:	34e2      	mov r1,r5
8e0022ce:	08ef 0402 	mov r0,r10
8e0022d2:	4003      	mov r2,0x0
8e0022d4:	600b 18e2 	movt r3,0x8e00
8e0022d8:	0d52      	jalr r3
8e0022da:	070b 0032 	mov r0,0x338
8e0022de:	000b 1002 	movt r0,0x0
8e0022e2:	aa9f 040a 	add r5,r10,r5
8e0022e6:	0044      	ldr r0,[r0]
8e0022e8:	b476      	lsl r5,r5,0x3
8e0022ea:	029a      	add r0,r0,r5
8e0022ec:	021b 0000 	add r0,r0,4
8e0022f0:	015f 0402 	jalr r8
8e0022f4:	15e0      	b 8e00231e <umm_realloc+0x19e>
8e0022f6:	3f8b 01f2 	mov r1,0x1ffc
8e0022fa:	1ce2      	mov r0,r7
8e0022fc:	200b 18e2 	movt r1,0x8e00
8e002300:	0552      	jalr r1
8e002302:	a05a      	and r5,r0,r0
8e002304:	0800      	beq 8e002314 <umm_realloc+0x194>
8e002306:	6e8b 0032 	mov r3,0x374
8e00230a:	50e2      	mov r2,r4
8e00230c:	38e2      	mov r1,r6
8e00230e:	600b 18e2 	movt r3,0x8e00
8e002312:	0d52      	jalr r3
8e002314:	18e2      	mov r0,r6
8e002316:	015f 0402 	jalr r8
8e00231a:	14e2      	mov r0,r5
8e00231c:	02e0      	b 8e002320 <umm_realloc+0x1a0>
8e00231e:	18e2      	mov r0,r6
8e002320:	d66c 0400 	ldrd r6,[sp,+0x4]
8e002324:	15ec 2400 	ldrd r8,[sp,+0x3]
8e002328:	556c 2400 	ldrd r10,[sp,+0x2]
8e00232c:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002330:	b41b 2405 	add sp,sp,40
8e002334:	946c 0400 	ldrd r4,[sp,+0x0]
8e002338:	194f 0402 	rts

8e00233c <umm_free>:
8e00233c:	95fc 0700 	strd r4,[sp],-0x3
8e002340:	d6dc 0400 	str r6,[sp,+0x5]
8e002344:	d4fc 2400 	strd lr,[sp,+0x1]
8e002348:	005a      	and r0,r0,r0
8e00234a:	5100      	beq 8e0023ec <umm_free+0xb0>
8e00234c:	c70b 0032 	mov r6,0x338
8e002350:	c00b 1002 	movt r6,0x0
8e002354:	9844      	ldr r4,[r6]
8e002356:	238b 0252 	mov r1,0x251c
8e00235a:	823a      	sub r4,r0,r4
8e00235c:	9066      	lsr r4,r4,0x3
8e00235e:	b0e2      	mov r5,r4
8e002360:	a00b 1002 	movt r5,0x0
8e002364:	14e2      	mov r0,r5
8e002366:	200b 18e2 	movt r1,0x8e00
8e00236a:	0552      	jalr r1
8e00236c:	5844      	ldr r2,[r6]
8e00236e:	3476      	lsl r1,r5,0x3
8e002370:	289a      	add r1,r2,r1
8e002372:	0584      	ldrb r0,[r1,0x3]
8e002374:	6504      	ldrb r3,[r1,0x2]
8e002376:	0116      	lsl r0,r0,0x8
8e002378:	01fa      	orr r0,r0,r3
8e00237a:	0076      	lsl r0,r0,0x3
8e00237c:	081a      	add r0,r2,r0
8e00237e:	0084      	ldrb r0,[r0,0x1]
8e002380:	00e6      	lsr r0,r0,0x7
8e002382:	6033      	sub r3,r0,0
8e002384:	1100      	beq 8e0023a6 <umm_free+0x6a>
8e002386:	d6cc 0400 	ldr r6,[sp,+0x5]
8e00238a:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e00238e:	b41b 2403 	add sp,sp,24
8e002392:	14e2      	mov r0,r5
8e002394:	570b 0252 	mov r2,0x25b8
8e002398:	946c 0400 	ldrd r4,[sp,+0x0]
8e00239c:	200b 0802 	mov r1,0x8000
8e0023a0:	400b 18e2 	movt r2,0x8e00
8e0023a4:	0942      	jr r2
8e0023a6:	0a84      	ldrb r0,[r2,0x5]
8e0023a8:	6a04      	ldrb r3,[r2,0x4]
8e0023aa:	0116      	lsl r0,r0,0x8
8e0023ac:	01fa      	orr r0,r0,r3
8e0023ae:	0076      	lsl r0,r0,0x3
8e0023b0:	7fe3      	mov r3,0xff
8e0023b2:	081a      	add r0,r2,r0
8e0023b4:	75da      	and r3,r5,r3
8e0023b6:	b506      	lsr r5,r5,0x8
8e0023b8:	6314      	strb r3,[r0,0x6]
8e0023ba:	a394      	strb r5,[r0,0x7]
8e0023bc:	0a84      	ldrb r0,[r2,0x5]
8e0023be:	8a0c 2000 	ldrb ip,[r2,+0x4]
8e0023c2:	0116      	lsl r0,r0,0x8
8e0023c4:	027f 008a 	orr r0,r0,ip
8e0023c8:	0614      	strb r0,[r1,0x4]
8e0023ca:	0106      	lsr r0,r0,0x8
8e0023cc:	0694      	strb r0,[r1,0x5]
8e0023ce:	0003      	mov r0,0x0
8e0023d0:	0714      	strb r0,[r1,0x6]
8e0023d2:	0794      	strb r0,[r1,0x7]
8e0023d4:	6a14      	strb r3,[r2,0x4]
8e0023d6:	aa94      	strb r5,[r2,0x5]
8e0023d8:	0484      	ldrb r0,[r1,0x1]
8e0023da:	4404      	ldrb r2,[r1]
8e0023dc:	0116      	lsl r0,r0,0x8
8e0023de:	017a      	orr r0,r0,r2
8e0023e0:	400b 0802 	mov r2,0x8000
8e0023e4:	017a      	orr r0,r0,r2
8e0023e6:	0414      	strb r0,[r1]
8e0023e8:	0106      	lsr r0,r0,0x8
8e0023ea:	0494      	strb r0,[r1,0x1]
8e0023ec:	d6cc 0400 	ldr r6,[sp,+0x5]
8e0023f0:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0023f4:	b41b 2403 	add sp,sp,24
8e0023f8:	946c 0400 	ldrd r4,[sp,+0x0]
8e0023fc:	194f 0402 	rts

8e002400 <umm_blocks>:
8e002400:	223b 0000 	sub r1,r0,4
8e002404:	0840      	blteu 8e002414 <umm_blocks+0x14>
8e002406:	019b 00ff 	add r0,r0,-5
8e00240a:	0066      	lsr r0,r0,0x3
8e00240c:	0113      	add r0,r0,2
8e00240e:	000b 1002 	movt r0,0x0
8e002412:	02e0      	b 8e002416 <umm_blocks+0x16>
8e002414:	0023      	mov r0,0x1
8e002416:	194f 0402 	rts
8e00241a:	01a2      	nop

8e00241c <umm_make_new_block>:
8e00241c:	470b 4032 	mov r18,0x338
8e002420:	400b 5002 	movt r18,0x0
8e002424:	284c 4800 	ldr r17,[r18,+0x0]
8e002428:	000b 1002 	movt r0,0x0
8e00242c:	807f 2006 	lsl ip,r0,0x3
8e002430:	661f 088a 	add r3,r17,ip
8e002434:	6c84      	ldrb r3,[r3,0x1]
8e002436:	6609 4880 	ldrb r19,[r17,+ip]
8e00243a:	200b 1002 	movt r1,0x0
8e00243e:	6d16      	lsl r3,r3,0x8
8e002440:	209a      	add r1,r0,r1
8e002442:	6dff 010a 	orr r3,r3,r19
8e002446:	7feb 47f2 	mov r19,0x7fff
8e00244a:	047f 4006 	lsl r16,r1,0x3
8e00244e:	6ddf 010a 	and r3,r3,r19
8e002452:	6419 0900 	strb r3,[r17,+r16]
8e002456:	6d06      	lsr r3,r3,0x8
8e002458:	241f 490a 	add r17,r17,r16
8e00245c:	649c 0800 	strb r3,[r17,+0x1]
8e002460:	684c 0800 	ldr r3,[r18,+0x0]
8e002464:	200b 1002 	movt r1,0x0
8e002468:	0c1f 410a 	add r16,r3,r16
8e00246c:	6106      	lsr r3,r0,0x8
8e00246e:	619c 0800 	strb r3,[r16,+0x3]
8e002472:	011c 0800 	strb r0,[r16,+0x2]
8e002476:	084c 4800 	ldr r16,[r18,+0x0]
8e00247a:	400b 1002 	movt r2,0x0
8e00247e:	621f 088a 	add r3,r16,ip
8e002482:	6c84      	ldrb r3,[r3,0x1]
8e002484:	0209 0880 	ldrb r0,[r16,+ip]
8e002488:	6d16      	lsl r3,r3,0x8
8e00248a:	6c7a      	orr r3,r3,r0
8e00248c:	0ddf 010a 	and r0,r3,r19
8e002490:	0076      	lsl r0,r0,0x3
8e002492:	001f 080a 	add r0,r16,r0
8e002496:	6506      	lsr r3,r1,0x8
8e002498:	2114      	strb r1,[r0,0x2]
8e00249a:	6194      	strb r3,[r0,0x3]
8e00249c:	084c 0800 	ldr r0,[r18,+0x0]
8e0024a0:	257a      	orr r1,r1,r2
8e0024a2:	2219 0080 	strb r1,[r0,+ip]
8e0024a6:	2506      	lsr r1,r1,0x8
8e0024a8:	821f 208a 	add ip,r0,ip
8e0024ac:	309c 0400 	strb r1,[ip,+0x1]
8e0024b0:	194f 0402 	rts

8e0024b4 <umm_disconnect_from_free_list>:
8e0024b4:	270b 0032 	mov r1,0x338
8e0024b8:	200b 1002 	movt r1,0x0
8e0024bc:	844c 2000 	ldr ip,[r1,+0x0]
8e0024c0:	000b 1002 	movt r0,0x0
8e0024c4:	0076      	lsl r0,r0,0x3
8e0024c6:	101f 040a 	add r0,ip,r0
8e0024ca:	4284      	ldrb r2,[r0,0x5]
8e0024cc:	6204      	ldrb r3,[r0,0x4]
8e0024ce:	4916      	lsl r2,r2,0x8
8e0024d0:	69fa      	orr r3,r2,r3
8e0024d2:	4384      	ldrb r2,[r0,0x7]
8e0024d4:	2304      	ldrb r1,[r0,0x6]
8e0024d6:	4916      	lsl r2,r2,0x8
8e0024d8:	48fa      	orr r2,r2,r1
8e0024da:	4876      	lsl r2,r2,0x3
8e0024dc:	511f 040a 	add r2,ip,r2
8e0024e0:	6a14      	strb r3,[r2,0x4]
8e0024e2:	6d06      	lsr r3,r3,0x8
8e0024e4:	6a94      	strb r3,[r2,0x5]
8e0024e6:	4384      	ldrb r2,[r0,0x7]
8e0024e8:	6304      	ldrb r3,[r0,0x6]
8e0024ea:	4916      	lsl r2,r2,0x8
8e0024ec:	69fa      	orr r3,r2,r3
8e0024ee:	4284      	ldrb r2,[r0,0x5]
8e0024f0:	2204      	ldrb r1,[r0,0x4]
8e0024f2:	4916      	lsl r2,r2,0x8
8e0024f4:	28fa      	orr r1,r2,r1
8e0024f6:	2476      	lsl r1,r1,0x3
8e0024f8:	309f 040a 	add r1,ip,r1
8e0024fc:	6714      	strb r3,[r1,0x6]
8e0024fe:	6d06      	lsr r3,r3,0x8
8e002500:	6794      	strb r3,[r1,0x7]
8e002502:	2084      	ldrb r1,[r0,0x1]
8e002504:	4004      	ldrb r2,[r0]
8e002506:	2516      	lsl r1,r1,0x8
8e002508:	257a      	orr r1,r1,r2
8e00250a:	5feb 07f2 	mov r2,0x7fff
8e00250e:	255a      	and r1,r1,r2
8e002510:	2014      	strb r1,[r0]
8e002512:	2506      	lsr r1,r1,0x8
8e002514:	2094      	strb r1,[r0,0x1]
8e002516:	194f 0402 	rts
8e00251a:	01a2      	nop

8e00251c <umm_assimilate_up>:
8e00251c:	95fc 0700 	strd r4,[sp],-0x3
8e002520:	d6dc 0400 	str r6,[sp,+0x5]
8e002524:	c70b 0032 	mov r6,0x338
8e002528:	d4fc 2400 	strd lr,[sp,+0x1]
8e00252c:	a0e2      	mov r5,r0
8e00252e:	c00b 1002 	movt r6,0x0
8e002532:	5844      	ldr r2,[r6]
8e002534:	a00b 1002 	movt r5,0x0
8e002538:	9476      	lsl r4,r5,0x3
8e00253a:	0a1a      	add r0,r2,r4
8e00253c:	0084      	ldrb r0,[r0,0x1]
8e00253e:	2a01      	ldrb r1,[r2,r4]
8e002540:	0116      	lsl r0,r0,0x8
8e002542:	00fa      	orr r0,r0,r1
8e002544:	2076      	lsl r1,r0,0x3
8e002546:	289a      	add r1,r2,r1
8e002548:	2484      	ldrb r1,[r1,0x1]
8e00254a:	24e6      	lsr r1,r1,0x7
8e00254c:	4433      	sub r2,r1,0
8e00254e:	2a00      	beq 8e0025a2 <umm_assimilate_up+0x86>
8e002550:	368b 0242 	mov r1,0x24b4
8e002554:	200b 18e2 	movt r1,0x8e00
8e002558:	0552      	jalr r1
8e00255a:	3844      	ldr r1,[r6]
8e00255c:	461a      	add r2,r1,r4
8e00255e:	4884      	ldrb r2,[r2,0x1]
8e002560:	0601      	ldrb r0,[r1,r4]
8e002562:	4916      	lsl r2,r2,0x8
8e002564:	487a      	orr r2,r2,r0
8e002566:	4876      	lsl r2,r2,0x3
8e002568:	451a      	add r2,r1,r2
8e00256a:	0884      	ldrb r0,[r2,0x1]
8e00256c:	6804      	ldrb r3,[r2]
8e00256e:	0116      	lsl r0,r0,0x8
8e002570:	01fa      	orr r0,r0,r3
8e002572:	7feb 07f2 	mov r3,0x7fff
8e002576:	01da      	and r0,r0,r3
8e002578:	0076      	lsl r0,r0,0x3
8e00257a:	241a      	add r1,r1,r0
8e00257c:	a514      	strb r5,[r1,0x2]
8e00257e:	b506      	lsr r5,r5,0x8
8e002580:	a594      	strb r5,[r1,0x3]
8e002582:	1844      	ldr r0,[r6]
8e002584:	821a      	add r4,r0,r4
8e002586:	5084      	ldrb r2,[r4,0x1]
8e002588:	3004      	ldrb r1,[r4]
8e00258a:	4916      	lsl r2,r2,0x8
8e00258c:	28fa      	orr r1,r2,r1
8e00258e:	2476      	lsl r1,r1,0x3
8e002590:	209a      	add r1,r0,r1
8e002592:	0404      	ldrb r0,[r1]
8e002594:	2484      	ldrb r1,[r1,0x1]
8e002596:	2516      	lsl r1,r1,0x8
8e002598:	047a      	orr r0,r1,r0
8e00259a:	01da      	and r0,r0,r3
8e00259c:	1014      	strb r0,[r4]
8e00259e:	0106      	lsr r0,r0,0x8
8e0025a0:	1094      	strb r0,[r4,0x1]
8e0025a2:	d6cc 0400 	ldr r6,[sp,+0x5]
8e0025a6:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0025aa:	b41b 2403 	add sp,sp,24
8e0025ae:	946c 0400 	ldrd r4,[sp,+0x0]
8e0025b2:	194f 0402 	rts
8e0025b6:	01a2      	nop

8e0025b8 <umm_assimilate_down>:
8e0025b8:	070b 4032 	mov r16,0x338
8e0025bc:	000b 5002 	movt r16,0x0
8e0025c0:	204c 4800 	ldr r17,[r16,+0x0]
8e0025c4:	000b 1002 	movt r0,0x0
8e0025c8:	0076      	lsl r0,r0,0x3
8e0025ca:	841f 280a 	add ip,r17,r0
8e0025ce:	718c 0400 	ldrb r3,[ip,+0x3]
8e0025d2:	510c 0400 	ldrb r2,[ip,+0x2]
8e0025d6:	6d16      	lsl r3,r3,0x8
8e0025d8:	4d7a      	orr r2,r3,r2
8e0025da:	4876      	lsl r2,r2,0x3
8e0025dc:	708c 0400 	ldrb r3,[ip,+0x1]
8e0025e0:	451f 080a 	add r2,r17,r2
8e0025e4:	6d16      	lsl r3,r3,0x8
8e0025e6:	300c 4400 	ldrb r17,[ip,+0x0]
8e0025ea:	6cff 010a 	orr r3,r3,r17
8e0025ee:	200b 1002 	movt r1,0x0
8e0025f2:	25fa      	orr r1,r1,r3
8e0025f4:	2814      	strb r1,[r2]
8e0025f6:	2506      	lsr r1,r1,0x8
8e0025f8:	2894      	strb r1,[r2,0x1]
8e0025fa:	204c 4800 	ldr r17,[r16,+0x0]
8e0025fe:	841f 280a 	add ip,r17,r0
8e002602:	518c 0400 	ldrb r2,[ip,+0x3]
8e002606:	710c 0400 	ldrb r3,[ip,+0x2]
8e00260a:	4916      	lsl r2,r2,0x8
8e00260c:	69fa      	orr r3,r2,r3
8e00260e:	508c 0400 	ldrb r2,[ip,+0x1]
8e002612:	300c 0400 	ldrb r1,[ip,+0x0]
8e002616:	4916      	lsl r2,r2,0x8
8e002618:	28fa      	orr r1,r2,r1
8e00261a:	2476      	lsl r1,r1,0x3
8e00261c:	249f 080a 	add r1,r17,r1
8e002620:	6514      	strb r3,[r1,0x2]
8e002622:	6d06      	lsr r3,r3,0x8
8e002624:	6594      	strb r3,[r1,0x3]
8e002626:	204c 0800 	ldr r1,[r16,+0x0]
8e00262a:	041a      	add r0,r1,r0
8e00262c:	2104      	ldrb r1,[r0,0x2]
8e00262e:	0184      	ldrb r0,[r0,0x3]
8e002630:	0116      	lsl r0,r0,0x8
8e002632:	00fa      	orr r0,r0,r1
8e002634:	194f 0402 	rts

8e002638 <bj_add_lk_syms>:
8e002638:	d4fc 2700 	strd lr,[sp],-0x1
8e00263c:	f41b 2401 	add fp,sp,8
8e002640:	000b 0002 	mov r0,0x0
8e002644:	000b 18e2 	movt r0,0x8e00
8e002648:	210b 0042 	mov r1,0x408
8e00264c:	200b 18e2 	movt r1,0x8e00
8e002650:	0552      	jalr r1
8e002652:	000b 0002 	mov r0,0x0
8e002656:	000b 18e2 	movt r0,0x8e00
8e00265a:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e00265e:	b41b 2401 	add sp,sp,8
8e002662:	194f 0402 	rts
8e002666:	01a2      	nop

8e002668 <bj_host_addr_to_core_addr>:
8e002668:	d57c 2700 	strd lr,[sp],-0x2
8e00266c:	f41b 2402 	add fp,sp,16
8e002670:	1cdc 0500 	str r0,[fp,-0x1]
8e002674:	0d0b 0262 	mov r0,0x2668
8e002678:	000b 18e2 	movt r0,0x8e00
8e00267c:	3a0b 0272 	mov r1,0x27d0
8e002680:	200b 18e2 	movt r1,0x8e00
8e002684:	588b 0092 	mov r2,0x9c4
8e002688:	400b 18e2 	movt r2,0x8e00
8e00268c:	0952      	jalr r2
8e00268e:	0003      	mov r0,0x0
8e002690:	d56c 2400 	ldrd lr,[sp,+0x2]
8e002694:	b41b 2402 	add sp,sp,16
8e002698:	194f 0402 	rts

8e00269c <bj_core_addr_to_host_addr>:
8e00269c:	d57c 2700 	strd lr,[sp],-0x2
8e0026a0:	f41b 2402 	add fp,sp,16
8e0026a4:	1cdc 0500 	str r0,[fp,-0x1]
8e0026a8:	138b 0262 	mov r0,0x269c
8e0026ac:	000b 18e2 	movt r0,0x8e00
8e0026b0:	3f0b 0272 	mov r1,0x27f8
8e0026b4:	200b 18e2 	movt r1,0x8e00
8e0026b8:	588b 0092 	mov r2,0x9c4
8e0026bc:	400b 18e2 	movt r2,0x8e00
8e0026c0:	0952      	jalr r2
8e0026c2:	0003      	mov r0,0x0
8e0026c4:	d56c 2400 	ldrd lr,[sp,+0x2]
8e0026c8:	b41b 2402 	add sp,sp,16
8e0026cc:	194f 0402 	rts

8e0026d0 <err_1>:
8e0026d0:	6361      	ldrd r3,[r0,r6]
8e0026d2:	7571      	strd r3,[r5,r2]
8e0026d4:	7269 5f65 	*unknown*
8e0026d8:	6c61      	ldrd r3,[r3,r0]
8e0026da:	6f6c 2063 	ldrd r11,[r3,+0x31e]
8e0026de:	6261      	ldrd r3,[r0,r4]
8e0026e0:	726f 0a74 	*unknown*
8e0026e4:	0000      	beq 8e0026e4 <err_1+0x14>
	...

8e0026e8 <err_2>:
8e0026e8:	6a62 685f 	*unknown*
8e0026ec:	736f 5f74 	*unknown*
8e0026f0:	6e69 7469 	*unknown*
8e0026f4:	6120      	bgtu 8e0027b6 <err_10+0xe>
8e0026f6:	6f62 7472 	*unknown*
8e0026fa:	000a      	eor r0,r0,r0
8e0026fc:	0000      	beq 8e0026fc <err_2+0x14>
	...

8e002700 <err_3>:
8e002700:	6a62 685f 	*unknown*
8e002704:	736f 5f74 	*unknown*
8e002708:	7572 206e 	*unknown*
8e00270c:	6261      	ldrd r3,[r0,r4]
8e00270e:	726f 0a74 	*unknown*
8e002712:	0000      	beq 8e002712 <err_3+0x12>
8e002714:	0000      	beq 8e002714 <err_3+0x14>
	...

8e002718 <err_4>:
8e002718:	6a62 685f 	*unknown*
8e00271c:	736f 5f74 	*unknown*
8e002720:	6966      	lsr r3,r2,0xb
8e002722:	696e      	asr r3,r2,0xb
8e002724:	6873 6120 	*unknown*
8e002728:	6f62 7472 	*unknown*
8e00272c:	000a      	eor r0,r0,r0
	...

8e002730 <err_5>:
8e002730:	6261      	ldrd r3,[r0,r4]
8e002732:	726f 2874 	*unknown*
8e002736:	2029 6261 	*unknown*
8e00273a:	726f 0a74 	*unknown*
	...

8e002740 <err_6>:
8e002740:	6a62 5f6b 	*unknown*
8e002744:	6c67      	fix r3,r3
8e002746:	5f62 6e69 	*unknown*
8e00274a:	7469 6120 	*unknown*
8e00274e:	6f62 7472 	*unknown*
8e002752:	315f 0a2e 	*unknown*
	...

8e002758 <err_7>:
8e002758:	6a62 5f6b 	*unknown*
8e00275c:	6c67      	fix r3,r3
8e00275e:	5f62 6e69 	*unknown*
8e002762:	7469 6120 	*unknown*
8e002766:	6f62 7472 	*unknown*
8e00276a:	325f 0a2e 	*unknown*
	...

8e002770 <err_8>:
8e002770:	6a62 5f6b 	*unknown*
8e002774:	6c67      	fix r3,r3
8e002776:	5f62 6e69 	*unknown*
8e00277a:	7469 6120 	*unknown*
8e00277e:	6f62 7472 	*unknown*
8e002782:	335f 0a2e 	*unknown*
	...

8e002788 <err_9>:
8e002788:	6761      	ldrd r3,[r1,r6]
8e00278a:	6e65      	ldrd r3,[r3],r4
8e00278c:	3a74      	strd r1,[r6,0x4]
8e00278e:	673a      	sub r3,r1,r6
8e002790:	7465      	ldrd r3,[r5],r0
8e002792:	615f 6176 	*unknown*
8e002796:	6c69 6261 	*unknown*
8e00279a:	656c 6120 	ldrd r27,[r1,-0x102]
8e00279e:	6f62 7472 	*unknown*
8e0027a2:	000a      	eor r0,r0,r0
8e0027a4:	0000      	beq 8e0027a4 <err_9+0x1c>
	...

8e0027a8 <err_10>:
8e0027a8:	6761      	ldrd r3,[r1,r6]
8e0027aa:	6e65      	ldrd r3,[r3],r4
8e0027ac:	3a74      	strd r1,[r6,0x4]
8e0027ae:	693a      	sub r3,r2,r2
8e0027b0:	696e      	asr r3,r2,0xb
8e0027b2:	5f74      	strd r2,[r7,0x6]
8e0027b4:	656d 6120 	*unknown*
8e0027b8:	6f62 7472 	*unknown*
8e0027bc:	000a      	eor r0,r0,r0
	...

8e0027c0 <err_11>:
8e0027c0:	7361      	ldrd r3,[r4,r6]
8e0027c2:	6573 7472 	*unknown*
8e0027c6:	6120      	bgtu 8e002888 <err_13+0x90>
8e0027c8:	6f62 7472 	*unknown*
8e0027cc:	000a      	eor r0,r0,r0
	...

8e0027d0 <err_12>:
8e0027d0:	6a62 685f 	*unknown*
8e0027d4:	736f 5f74 	*unknown*
8e0027d8:	6461      	ldrd r3,[r1,r0]
8e0027da:	7264      	ldrd r3,[r4,0x4]
8e0027dc:	745f 5f6f 	*unknown*
8e0027e0:	6f63      	mov r3,0x7b
8e0027e2:	6572 615f 	*unknown*
8e0027e6:	6464      	ldrd r3,[r1]
8e0027e8:	2072      	movgte r1,r0
8e0027ea:	6261      	ldrd r3,[r0,r4]
8e0027ec:	726f 0a74 	*unknown*
	...

8e0027f8 <err_13>:
8e0027f8:	6a62 635f 	*unknown*
8e0027fc:	726f 5f65 	*unknown*
8e002800:	6461      	ldrd r3,[r1,r0]
8e002802:	7264      	ldrd r3,[r4,0x4]
8e002804:	745f 5f6f 	*unknown*
8e002808:	6f68 7473 	bgt 8ee90ee6 <LD_EXTERNAL_LOAD_ORIG+0x690ee6>
8e00280c:	615f 6464 	*unknown*
8e002810:	2072      	movgte r1,r0
8e002812:	6261      	ldrd r3,[r0,r4]
8e002814:	726f 0a74 	*unknown*
	...

Disassembly of section external_data_ram:

8f000000 <bjk_external_data_obj>:
	...

Disassembly of section .text:

00000100 <_Z6func_1i>:
 100:	d57c 2700 	strd lr,[sp],-0x2
 104:	f41b 2402 	add fp,sp,16
 108:	1cdc 0500 	str r0,[fp,-0x1]
 10c:	000b 0012 	mov r0,0x100
 110:	000b 1002 	movt r0,0x0
 114:	2c0b 0032 	mov r1,0x360
 118:	200b 1002 	movt r1,0x0
 11c:	588b 0092 	mov r2,0x9c4
 120:	400b 18e2 	movt r2,0x8e00
 124:	0952      	jalr r2
 126:	01a2      	nop
 128:	d56c 2400 	ldrd lr,[sp,+0x2]
 12c:	b41b 2402 	add sp,sp,16
 130:	194f 0402 	rts

00000134 <_Z6func_2ci>:
 134:	d57c 2700 	strd lr,[sp],-0x2
 138:	f41b 2402 	add fp,sp,16
 13c:	3d5c 0500 	str r1,[fp,-0x2]
 140:	1e1c 0500 	strb r0,[fp,-0x4]
 144:	1d4c 0500 	ldr r0,[fp,-0x2]
 148:	029b 0000 	add r0,r0,5
 14c:	200b 0012 	mov r1,0x100
 150:	200b 1002 	movt r1,0x0
 154:	0552      	jalr r1
 156:	01a2      	nop
 158:	d56c 2400 	ldrd lr,[sp,+0x2]
 15c:	b41b 2402 	add sp,sp,16
 160:	194f 0402 	rts

00000164 <_Z6func_3Pci>:
 164:	d57c 2700 	strd lr,[sp],-0x2
 168:	f41b 2402 	add fp,sp,16
 16c:	1cdc 0500 	str r0,[fp,-0x1]
 170:	3d5c 0500 	str r1,[fp,-0x2]
 174:	3d4c 0500 	ldr r1,[fp,-0x2]
 178:	04e2      	mov r0,r1
 17a:	0076      	lsl r0,r0,0x3
 17c:	00ba      	sub r0,r0,r1
 17e:	20e2      	mov r1,r0
 180:	0f03      	mov r0,0x78
 182:	468b 0012 	mov r2,0x134
 186:	400b 1002 	movt r2,0x0
 18a:	0952      	jalr r2
 18c:	01a2      	nop
 18e:	d56c 2400 	ldrd lr,[sp,+0x2]
 192:	b41b 2402 	add sp,sp,16
 196:	194f 0402 	rts
 19a:	01a2      	nop

0000019c <normal_start>:
 19c:	bf0b 21f2 	mov sp,0x1ff8
 1a0:	a00b 3002 	movt sp,0x0
 1a4:	e00b 2002 	mov fp,0x0
 1a8:	1feb 0032 	mov r0,0x3ff
 1ac:	050f 0402 	movts imask,r0
 1b0:	180b 0012 	mov r0,0x1c0
 1b4:	000b 1002 	movt r0,0x0
 1b8:	010f 0402 	movts iret,r0
 1bc:	01d2      	rti
 1be:	01a2      	nop

000001c0 <main_caller>:
 1c0:	1c8b 0012 	mov r0,0x1e4
 1c4:	000b 1002 	movt r0,0x0
 1c8:	0152      	jalr r0
 1ca:	01a2      	nop
 1cc:	1feb 0032 	mov r0,0x3ff
 1d0:	050f 0402 	movts imask,r0
 1d4:	0392      	gid
 1d6:	0fe2      	trap 0x3
 1d8:	01a2      	nop

000001da <infn_loop>:
 1da:	00e0      	b 1da <infn_loop>
 1dc:	01a2      	nop
 1de:	194f 0402 	rts
 1e2:	01d2      	rti

000001e4 <main>:
 1e4:	d4fc 2700 	strd lr,[sp],-0x1
 1e8:	f41b 2401 	add fp,sp,8
 1ec:	070b 0002 	mov r0,0x38
 1f0:	000b 18e2 	movt r0,0x8e00
 1f4:	0152      	jalr r0
 1f6:	0003      	mov r0,0x0
 1f8:	d4ec 2400 	ldrd lr,[sp,+0x1]
 1fc:	b41b 2401 	add sp,sp,8
 200:	194f 0402 	rts

00000204 <bjk_sync_handler>:
 204:	14fc 0500 	strd r0,[sp,-0x1]
 208:	0512      	movfs r0,status
 20a:	211f 0402 	movfs r1,iret
 20e:	b41b 24fe 	add sp,sp,-16
 212:	0192      	gie
 214:	0392      	gid
 216:	b41b 2402 	add sp,sp,16
 21a:	0502      	movts status,r0
 21c:	210f 0402 	movts iret,r1
 220:	14ec 0500 	ldrd r0,[sp,-0x1]
 224:	01d2      	rti
 226:	01a2      	nop

00000228 <bjk_software_exception_handler>:
 228:	14fc 0500 	strd r0,[sp,-0x1]
 22c:	0512      	movfs r0,status
 22e:	211f 0402 	movfs r1,iret
 232:	b41b 24fc 	add sp,sp,-32
 236:	0192      	gie
 238:	157c 0400 	strd r0,[sp,+0x2]
 23c:	108b 0032 	mov r0,0x384
 240:	54fc 0400 	strd r2,[sp,+0x1]
 244:	000b 1002 	movt r0,0x0
 248:	0044      	ldr r0,[r0]
 24a:	2023      	mov r1,0x1
 24c:	229c 0003 	strb r1,[r0,+0x1d]
 250:	250b 0022 	mov r1,0x228
 254:	200b 1002 	movt r1,0x0
 258:	21d4      	str r1,[r0,0x3]
 25a:	02cc 0001 	ldr r0,[r0,+0xd]
 25e:	2033      	sub r1,r0,0
 260:	0b00      	beq 276 <bjk_software_exception_handler+0x4e>
 262:	4044      	ldr r2,[r0]
 264:	3bab 0cc2 	mov r1,0xccdd
 268:	376b 1aa2 	movt r1,0xaabb
 26c:	68ba      	sub r3,r2,r1
 26e:	0410      	bne 276 <bjk_software_exception_handler+0x4e>
 270:	3e2b 0ff2 	mov r1,0xfff1
 274:	2314      	strb r1,[r0,0x6]
 276:	0fe2      	trap 0x3
 278:	156c 0400 	ldrd r0,[sp,+0x2]
 27c:	54ec 0400 	ldrd r2,[sp,+0x1]
 280:	0392      	gid
 282:	b41b 2404 	add sp,sp,32
 286:	0502      	movts status,r0
 288:	210f 0402 	movts iret,r1
 28c:	14ec 0500 	ldrd r0,[sp,-0x1]
 290:	01d2      	rti
 292:	01a2      	nop

00000294 <bjk_page_miss_handler>:
 294:	14fc 0500 	strd r0,[sp,-0x1]
 298:	0512      	movfs r0,status
 29a:	211f 0402 	movfs r1,iret
 29e:	b41b 24fc 	add sp,sp,-32
 2a2:	0192      	gie
 2a4:	157c 0400 	strd r0,[sp,+0x2]
 2a8:	108b 0032 	mov r0,0x384
 2ac:	54fc 0400 	strd r2,[sp,+0x1]
 2b0:	000b 1002 	movt r0,0x0
 2b4:	0044      	ldr r0,[r0]
 2b6:	2043      	mov r1,0x2
 2b8:	229c 0003 	strb r1,[r0,+0x1d]
 2bc:	328b 0022 	mov r1,0x294
 2c0:	200b 1002 	movt r1,0x0
 2c4:	21d4      	str r1,[r0,0x3]
 2c6:	02cc 0001 	ldr r0,[r0,+0xd]
 2ca:	2033      	sub r1,r0,0
 2cc:	0b00      	beq 2e2 <bjk_page_miss_handler+0x4e>
 2ce:	4044      	ldr r2,[r0]
 2d0:	3bab 0cc2 	mov r1,0xccdd
 2d4:	376b 1aa2 	movt r1,0xaabb
 2d8:	68ba      	sub r3,r2,r1
 2da:	0410      	bne 2e2 <bjk_page_miss_handler+0x4e>
 2dc:	3e2b 0ff2 	mov r1,0xfff1
 2e0:	2314      	strb r1,[r0,0x6]
 2e2:	0fe2      	trap 0x3
 2e4:	156c 0400 	ldrd r0,[sp,+0x2]
 2e8:	54ec 0400 	ldrd r2,[sp,+0x1]
 2ec:	0392      	gid
 2ee:	b41b 2404 	add sp,sp,32
 2f2:	0502      	movts status,r0
 2f4:	210f 0402 	movts iret,r1
 2f8:	14ec 0500 	ldrd r0,[sp,-0x1]
 2fc:	01d2      	rti
 2fe:	01a2      	nop

00000300 <bjk_timer0_handler>:
 300:	14fc 0500 	strd r0,[sp,-0x1]
 304:	0512      	movfs r0,status
 306:	211f 0402 	movfs r1,iret
 30a:	b41b 24fd 	add sp,sp,-24
 30e:	0192      	gie
 310:	14fc 0400 	strd r0,[sp,+0x1]
 314:	300b 0032 	mov r1,0x380
 318:	200b 1002 	movt r1,0x0
 31c:	0444      	ldr r0,[r1]
 31e:	0093      	add r0,r0,1
 320:	0454      	str r0,[r1]
 322:	14ec 0400 	ldrd r0,[sp,+0x1]
 326:	0392      	gid
 328:	b41b 2403 	add sp,sp,24
 32c:	0502      	movts status,r0
 32e:	210f 0402 	movts iret,r1
 332:	14ec 0500 	ldrd r0,[sp,-0x1]
 336:	01d2      	rti

Disassembly of section .data:

00000338 <umm_heap>:
 338:	5000      	beq 3d8 <bjk_system_sz+0x50>
	...

Disassembly of section .rodata:

00000340 <.rodata>:
 340:	4142 4b43 	*unknown*
 344:	5254      	str r2,[r4,0x4]
 346:	4341      	ldr r2,[r0,r6]
 348:	5f45      	ldr r2,[r7],r6
 34a:	4554      	str r2,[r1,0x2]
 34c:	5453 000a 	*unknown*
 350:	6163      	mov r3,0xb
 352:	6c6c 6e69 	ldrd r27,[r27],+0x348
 356:	2067      	fix r1,r0
 358:	7566      	lsr r3,r5,0xb
 35a:	636e      	asr r3,r0,0x1b
 35c:	0033      	sub r0,r0,0
 35e:	0000      	beq 35e <umm_heap+0x26>
 360:	6f46      	lsr r3,r3,0x1a
 362:	6372 6465 	*unknown*
 366:	6120      	bgtu 428 <bjk_system_sz+0xa0>
 368:	6f62 7472 	*unknown*
 36c:	6920      	bgtu 43e <bjk_system_sz+0xb6>
 36e:	206e      	asr r1,r0,0x3
 370:	6162 6b63 	*unknown*
 374:	7274      	strd r3,[r4,0x4]
 376:	6361      	ldrd r3,[r0,r6]
 378:	2065      	ldrd r1,[r0],r0
 37a:	6574      	strd r3,[r1,0x2]
 37c:	7473 0000 	*unknown*

Disassembly of section .bss:

00000380 <test_send_irq3>:
 380:	0000      	beq 380 <test_send_irq3>
	...

00000384 <bjk_glb_pt_sys_data>:
 384:	0000      	beq 384 <bjk_glb_pt_sys_data>
	...

00000388 <bjk_system_sz>:
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	4347      	fmsub r2,r0,r6
   2:	3a43      	mov r1,0xd2
   4:	2820      	bgtu 54 <irq3_entry+0x48>
   6:	7045      	ldr r3,[r4],r0
   8:	7069 6168 	*unknown*
   c:	796e      	asr r3,r6,0xb
   e:	7420      	bgtu f6 <irq3_entry+0xea>
  10:	6f6f 636c 	*unknown*
  14:	6168 6e69 	bgt dcd2d6 <LD_EXTERNAL_ALLOC_SIZE+0x5cd2d6>
  18:	3220      	bgtu 7c <irq3_entry+0x70>
  1a:	3130      	bgteu 7c <irq3_entry+0x70>
  1c:	2e36      	lsl r1,r3,0x11
  1e:	3131      	strh r1,[r4,r2]
  20:	2029 2e35 	*unknown*
  24:	2e34      	strh r1,[r3,0x4]
  26:	0030      	bgteu 26 <irq3_entry+0x1a>

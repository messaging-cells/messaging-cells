
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
8e00007a:	098b 0092 	mov r0,0x94c
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
8e00016e:	618b 00f2 	mov r3,0xf0c
8e000172:	600b 18e2 	movt r3,0x8e00
8e000176:	0d52      	jalr r3
8e000178:	1d3c 0500 	strh r0,[fp,-0x2]
8e00017c:	22e0      	b 8e0001c0 <bjk_aux_sout+0x12c>
8e00017e:	4003      	mov r2,0x0
8e000180:	2003      	mov r1,0x0
8e000182:	1763      	mov r0,0xbb
8e000184:	630b 0172 	mov r3,0x1718
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
8e0001b2:	618b 00f2 	mov r3,0xf0c
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
8e0002d8:	618b 00f2 	mov r3,0xf0c
8e0002dc:	600b 18e2 	movt r3,0x8e00
8e0002e0:	0d52      	jalr r3
8e0002e2:	1ebc 0500 	strh r0,[fp,-0x5]
8e0002e6:	18e0      	b 8e000316 <bjk_aux_iout+0x13e>
8e0002e8:	4003      	mov r2,0x0
8e0002ea:	2003      	mov r1,0x0
8e0002ec:	1763      	mov r0,0xbb
8e0002ee:	630b 0172 	mov r3,0x1718
8e0002f2:	600b 18e2 	movt r3,0x8e00
8e0002f6:	0d52      	jalr r3
8e0002f8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0002fc:	034c 0001 	ldr r0,[r0,+0xe]
8e000300:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000304:	5ecc 0500 	ldr r2,[fp,-0x5]
8e000308:	618b 00f2 	mov r3,0xf0c
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
8e00048e:	020b 00b2 	mov r0,0xb10
8e000492:	000b 18e2 	movt r0,0x8e00
8e000496:	9fcb 0ff2 	mov r4,0xfffe
8e00049a:	9e2b 1ff2 	movt r4,0xfff1
8e00049e:	0152      	jalr r0
8e0004a0:	090b 0262 	mov r0,0x2648
8e0004a4:	000b 18e2 	movt r0,0x8e00
8e0004a8:	9fcb 0ff2 	mov r4,0xfffe
8e0004ac:	9e2b 1ff2 	movt r4,0xfff1
8e0004b0:	0152      	jalr r0
8e0004b2:	138b 0092 	mov r0,0x99c
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
8e000508:	1cdc 0501 	str r0,[fp,-0x9]
8e00050c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000510:	2403      	mov r1,0x20
8e000512:	2034      	strh r1,[r0]
8e000514:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000518:	2103      	mov r1,0x8
8e00051a:	20b4      	strh r1,[r0,0x1]
8e00051c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000520:	2083      	mov r1,0x4
8e000522:	2134      	strh r1,[r0,0x2]
8e000524:	1ccc 0501 	ldr r0,[fp,-0x9]
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
8e00054a:	2a0b 0272 	mov r1,0x2750
8e00054e:	200b 18e2 	movt r1,0x8e00
8e000552:	5a8b 0092 	mov r2,0x9d4
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
8e000648:	108b 0032 	mov r0,0x384
8e00064c:	000b 1002 	movt r0,0x0
8e000650:	0044      	ldr r0,[r0]
8e000652:	1fdc 0500 	str r0,[fp,-0x7]
8e000656:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00065a:	3bab 0cc2 	mov r1,0xccdd
8e00065e:	376b 1aa2 	movt r1,0xaabb
8e000662:	2054      	str r1,[r0]
8e000664:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000668:	2003      	mov r1,0x0
8e00066a:	20d4      	str r1,[r0,0x1]
8e00066c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000670:	39ab 0ab2 	mov r1,0xabcd
8e000674:	312b 1672 	movt r1,0x6789
8e000678:	225c 0001 	str r1,[r0,+0xc]
8e00067c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000680:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000684:	213c 0001 	strh r1,[r0,+0xa]
8e000688:	1dac 0501 	ldrh r0,[fp,-0xb]
8e00068c:	00c6      	lsr r0,r0,0x6
8e00068e:	20e2      	mov r1,r0
8e000690:	200b 1002 	movt r1,0x0
8e000694:	07e3      	mov r0,0x3f
8e000696:	045a      	and r0,r1,r0
8e000698:	20e2      	mov r1,r0
8e00069a:	200b 1002 	movt r1,0x0
8e00069e:	110b 0032 	mov r0,0x388
8e0006a2:	000b 1002 	movt r0,0x0
8e0006a6:	0024      	ldrh r0,[r0]
8e0006a8:	043a      	sub r0,r1,r0
8e0006aa:	20e2      	mov r1,r0
8e0006ac:	200b 1002 	movt r1,0x0
8e0006b0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006b4:	223c 0001 	strh r1,[r0,+0xc]
8e0006b8:	3dac 0501 	ldrh r1,[fp,-0xb]
8e0006bc:	07e3      	mov r0,0x3f
8e0006be:	045a      	and r0,r1,r0
8e0006c0:	20e2      	mov r1,r0
8e0006c2:	200b 1002 	movt r1,0x0
8e0006c6:	110b 0032 	mov r0,0x388
8e0006ca:	000b 1002 	movt r0,0x0
8e0006ce:	00a4      	ldrh r0,[r0,0x1]
8e0006d0:	043a      	sub r0,r1,r0
8e0006d2:	20e2      	mov r1,r0
8e0006d4:	200b 1002 	movt r1,0x0
8e0006d8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006dc:	22bc 0001 	strh r1,[r0,+0xd]
8e0006e0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006e4:	3e2c 0501 	ldrh r1,[fp,-0xc]
8e0006e8:	21bc 0001 	strh r1,[r0,+0xb]
8e0006ec:	1e2c 0501 	ldrh r0,[fp,-0xc]
8e0006f0:	83bb 2001 	sub ip,r0,15
8e0006f4:	0728 0001 	bgtu 8e000902 <bjk_glb_init+0x482>
8e0006f8:	1e2c 0501 	ldrh r0,[fp,-0xc]
8e0006fc:	0113      	add r0,r0,2
8e0006fe:	2096      	lsl r1,r0,0x4
8e000700:	000b 0002 	mov r0,0x0
8e000704:	000b 18f2 	movt r0,0x8f00
8e000708:	241a      	add r1,r1,r0
8e00070a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00070e:	22dc 0001 	str r1,[r0,+0xd]
8e000712:	5e2c 0501 	ldrh r2,[fp,-0xc]
8e000716:	600b 0002 	mov r3,0x0
8e00071a:	600b 18f2 	movt r3,0x8f00
8e00071e:	28e2      	mov r1,r2
8e000720:	0496      	lsl r0,r1,0x4
8e000722:	20e2      	mov r1,r0
8e000724:	0456      	lsl r0,r1,0x2
8e000726:	00ba      	sub r0,r0,r1
8e000728:	013a      	sub r0,r0,r2
8e00072a:	0076      	lsl r0,r0,0x3
8e00072c:	0c1a      	add r0,r3,r0
8e00072e:	001b 0024 	add r0,r0,288
8e000732:	2044      	ldr r1,[r0]
8e000734:	1bab 0cc2 	mov r0,0xccdd
8e000738:	176b 1aa2 	movt r0,0xaabb
8e00073c:	043f 400a 	sub r16,r1,r0
8e000740:	2e00      	beq 8e00079c <bjk_glb_init+0x31c>
8e000742:	100b 0042 	mov r0,0x480
8e000746:	000b 18e2 	movt r0,0x8e00
8e00074a:	2d0b 0272 	mov r1,0x2768
8e00074e:	200b 18e2 	movt r1,0x8e00
8e000752:	7a8b 0092 	mov r3,0x9d4
8e000756:	600b 18e2 	movt r3,0x8e00
8e00075a:	9fcb 0ff2 	mov r4,0xfffe
8e00075e:	9e2b 1ff2 	movt r4,0xfff1
8e000762:	4512      	movfs r2,status
8e000764:	0392      	gid
8e000766:	811f 2002 	movfs ip,config
8e00076a:	928f 240a 	eor ip,ip,r5
8e00076e:	925f 240a 	and ip,ip,r4
8e000772:	928f 240a 	eor ip,ip,r5
8e000776:	810f 2002 	movts config,ip
8e00077a:	0192      	gie
8e00077c:	01eb 4ef2 	mov r16,0xef0f
8e000780:	1feb 5ff2 	movt r16,0xffff
8e000784:	851f 2002 	movfs ip,status
8e000788:	910f 240a 	eor ip,ip,r2
8e00078c:	905f 250a 	and ip,ip,r16
8e000790:	910f 240a 	eor ip,ip,r2
8e000794:	850f 2002 	movts status,ip
8e000798:	0d52      	jalr r3
8e00079a:	17e0      	b 8e0007c8 <bjk_glb_init+0x348>
8e00079c:	0512      	movfs r0,status
8e00079e:	0392      	gid
8e0007a0:	011f 4002 	movfs r16,config
8e0007a4:	028f 480a 	eor r16,r16,r5
8e0007a8:	025f 480a 	and r16,r16,r4
8e0007ac:	028f 480a 	eor r16,r16,r5
8e0007b0:	010f 4002 	movts config,r16
8e0007b4:	0192      	gie
8e0007b6:	21eb 0ef2 	mov r1,0xef0f
8e0007ba:	3feb 1ff2 	movt r1,0xffff
8e0007be:	4512      	movfs r2,status
8e0007c0:	480a      	eor r2,r2,r0
8e0007c2:	48da      	and r2,r2,r1
8e0007c4:	480a      	eor r2,r2,r0
8e0007c6:	4502      	movts status,r2
8e0007c8:	5e2c 0501 	ldrh r2,[fp,-0xc]
8e0007cc:	28e2      	mov r1,r2
8e0007ce:	0496      	lsl r0,r1,0x4
8e0007d0:	20e2      	mov r1,r0
8e0007d2:	0456      	lsl r0,r1,0x2
8e0007d4:	00ba      	sub r0,r0,r1
8e0007d6:	013a      	sub r0,r0,r2
8e0007d8:	0076      	lsl r0,r0,0x3
8e0007da:	201b 0024 	add r1,r0,288
8e0007de:	000b 0002 	mov r0,0x0
8e0007e2:	000b 18f2 	movt r0,0x8f00
8e0007e6:	041a      	add r0,r1,r0
8e0007e8:	1c5c 0501 	str r0,[fp,-0x8]
8e0007ec:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0007f0:	201b 0001 	add r1,r0,8
8e0007f4:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0007f8:	235c 0001 	str r1,[r0,+0xe]
8e0007fc:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000800:	834c 2001 	ldr ip,[r0,+0xe]
8e000804:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000808:	001b 0009 	add r0,r0,72
8e00080c:	6003      	mov r3,0x0
8e00080e:	40e2      	mov r2,r0
8e000810:	258b 0012 	mov r1,0x12c
8e000814:	10ef 0402 	mov r0,ip
8e000818:	9a8b 20b2 	mov ip,0xbd4
8e00081c:	800b 38e2 	movt ip,0x8e00
8e000820:	9fcb 0ff2 	mov r4,0xfffe
8e000824:	9e2b 1ff2 	movt r4,0xfff1
8e000828:	115f 0402 	jalr ip
8e00082c:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000830:	02cc 0001 	ldr r0,[r0,+0xd]
8e000834:	2044      	ldr r1,[r0]
8e000836:	1bab 0cc2 	mov r0,0xccdd
8e00083a:	176b 1aa2 	movt r0,0xaabb
8e00083e:	643a      	sub r3,r1,r0
8e000840:	1200      	beq 8e000864 <bjk_glb_init+0x3e4>
8e000842:	100b 0042 	mov r0,0x480
8e000846:	000b 18e2 	movt r0,0x8e00
8e00084a:	300b 0272 	mov r1,0x2780
8e00084e:	200b 18e2 	movt r1,0x8e00
8e000852:	5a8b 0092 	mov r2,0x9d4
8e000856:	400b 18e2 	movt r2,0x8e00
8e00085a:	9fcb 0ff2 	mov r4,0xfffe
8e00085e:	9e2b 1ff2 	movt r4,0xfff1
8e000862:	0952      	jalr r2
8e000864:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000868:	02cc 0001 	ldr r0,[r0,+0xd]
8e00086c:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000870:	2134      	strh r1,[r0,0x2]
8e000872:	01a2      	nop
8e000874:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000878:	02cc 0001 	ldr r0,[r0,+0xd]
8e00087c:	0124      	ldrh r0,[r0,0x2]
8e00087e:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000882:	843f 200a 	sub ip,r1,r0
8e000886:	f710      	bne 8e000874 <bjk_glb_init+0x3f4>
8e000888:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00088c:	02cc 0001 	ldr r0,[r0,+0xd]
8e000890:	3fcc 0500 	ldr r1,[fp,-0x7]
8e000894:	2154      	str r1,[r0,0x2]
8e000896:	01a2      	nop
8e000898:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00089c:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008a0:	2144      	ldr r1,[r0,0x2]
8e0008a2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0008a6:	043f 400a 	sub r16,r1,r0
8e0008aa:	f710      	bne 8e000898 <bjk_glb_init+0x418>
8e0008ac:	0423      	mov r0,0x21
8e0008ae:	1d9c 0502 	strb r0,[fp,-0x13]
8e0008b2:	108b 0032 	mov r0,0x384
8e0008b6:	000b 1002 	movt r0,0x0
8e0008ba:	0044      	ldr r0,[r0]
8e0008bc:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008c0:	1d5c 0501 	str r0,[fp,-0xa]
8e0008c4:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0008c8:	2033      	sub r1,r0,0
8e0008ca:	0d00      	beq 8e0008e4 <bjk_glb_init+0x464>
8e0008cc:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0008d0:	3d8c 0502 	ldrb r1,[fp,-0x13]
8e0008d4:	2314      	strb r1,[r0,0x6]
8e0008d6:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0008da:	0304      	ldrb r0,[r0,0x6]
8e0008dc:	3d8c 0502 	ldrb r1,[fp,-0x13]
8e0008e0:	443a      	sub r2,r1,r0
8e0008e2:	fa10      	bne 8e0008d6 <bjk_glb_init+0x456>
8e0008e4:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0008e8:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008ec:	2003      	mov r1,0x0
8e0008ee:	2394      	strb r1,[r0,0x7]
8e0008f0:	01a2      	nop
8e0008f2:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0008f6:	02cc 0001 	ldr r0,[r0,+0xd]
8e0008fa:	0384      	ldrb r0,[r0,0x7]
8e0008fc:	6033      	sub r3,r0,0
8e0008fe:	fa10      	bne 8e0008f2 <bjk_glb_init+0x472>
8e000900:	18e0      	b 8e000930 <bjk_glb_init+0x4b0>
8e000902:	0512      	movfs r0,status
8e000904:	0392      	gid
8e000906:	811f 2002 	movfs ip,config
8e00090a:	928f 240a 	eor ip,ip,r5
8e00090e:	925f 240a 	and ip,ip,r4
8e000912:	928f 240a 	eor ip,ip,r5
8e000916:	810f 2002 	movts config,ip
8e00091a:	0192      	gie
8e00091c:	01eb 4ef2 	mov r16,0xef0f
8e000920:	1feb 5ff2 	movt r16,0xffff
8e000924:	2512      	movfs r1,status
8e000926:	240a      	eor r1,r1,r0
8e000928:	245f 010a 	and r1,r1,r16
8e00092c:	240a      	eor r1,r1,r0
8e00092e:	2502      	movts status,r1
8e000930:	01a2      	nop
8e000932:	9fcb 0ff2 	mov r4,0xfffe
8e000936:	9e2b 1ff2 	movt r4,0xfff1
8e00093a:	d76c 2400 	ldrd lr,[sp,+0x6]
8e00093e:	96ec 0400 	ldrd r4,[sp,+0x5]
8e000942:	b41b 2406 	add sp,sp,48
8e000946:	194f 0402 	rts
8e00094a:	01a2      	nop

8e00094c <bjk_glb_finish>:
8e00094c:	f65c 2700 	str fp,[sp],-0x4
8e000950:	f4ef 2402 	mov fp,sp
8e000954:	1e2b 0ff2 	mov r0,0xfff1
8e000958:	1f9c 0401 	strb r0,[fp,+0xf]
8e00095c:	108b 0032 	mov r0,0x384
8e000960:	000b 1002 	movt r0,0x0
8e000964:	0044      	ldr r0,[r0]
8e000966:	02cc 0001 	ldr r0,[r0,+0xd]
8e00096a:	1d5c 0400 	str r0,[fp,+0x2]
8e00096e:	1d4c 0400 	ldr r0,[fp,+0x2]
8e000972:	2033      	sub r1,r0,0
8e000974:	0d00      	beq 8e00098e <bjk_glb_finish+0x42>
8e000976:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00097a:	3f8c 0401 	ldrb r1,[fp,+0xf]
8e00097e:	2314      	strb r1,[r0,0x6]
8e000980:	1d4c 0400 	ldr r0,[fp,+0x2]
8e000984:	0304      	ldrb r0,[r0,0x6]
8e000986:	3f8c 0401 	ldrb r1,[fp,+0xf]
8e00098a:	443a      	sub r2,r1,r0
8e00098c:	fa10      	bne 8e000980 <bjk_glb_finish+0x34>
8e00098e:	01a2      	nop
8e000990:	f64c 2400 	ldr fp,[sp,+0x4]
8e000994:	b41b 2402 	add sp,sp,16
8e000998:	194f 0402 	rts

8e00099c <bjk_get_first_glb_sys>:
8e00099c:	d4fc 2700 	strd lr,[sp],-0x1
8e0009a0:	f41b 2401 	add fp,sp,8
8e0009a4:	180b 0012 	mov r0,0x1c0
8e0009a8:	218b 0202 	mov r1,0x200c
8e0009ac:	200b 18e2 	movt r1,0x8e00
8e0009b0:	0552      	jalr r1
8e0009b2:	20e2      	mov r1,r0
8e0009b4:	108b 0032 	mov r0,0x384
8e0009b8:	000b 1002 	movt r0,0x0
8e0009bc:	2054      	str r1,[r0]
8e0009be:	108b 0032 	mov r0,0x384
8e0009c2:	000b 1002 	movt r0,0x0
8e0009c6:	0044      	ldr r0,[r0]
8e0009c8:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0009cc:	b41b 2401 	add sp,sp,8
8e0009d0:	194f 0402 	rts

8e0009d4 <bjk_abort>:
8e0009d4:	d67c 2700 	strd lr,[sp],-0x4
8e0009d8:	f41b 2404 	add fp,sp,32
8e0009dc:	1edc 0500 	str r0,[fp,-0x5]
8e0009e0:	3f5c 0500 	str r1,[fp,-0x6]
8e0009e4:	1feb 0ff2 	mov r0,0xffff
8e0009e8:	1feb 1ff2 	movt r0,0xffff
8e0009ec:	1cbc 0500 	strh r0,[fp,-0x1]
8e0009f0:	0003      	mov r0,0x0
8e0009f2:	1d5c 0500 	str r0,[fp,-0x2]
8e0009f6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0009fa:	2033      	sub r1,r0,0
8e0009fc:	0d00      	beq 8e000a16 <bjk_abort+0x42>
8e0009fe:	0283      	mov r0,0x14
8e000a00:	1cbc 0500 	strh r0,[fp,-0x1]
8e000a04:	108b 0032 	mov r0,0x384
8e000a08:	000b 1002 	movt r0,0x0
8e000a0c:	0044      	ldr r0,[r0]
8e000a0e:	001b 002d 	add r0,r0,360
8e000a12:	1d5c 0500 	str r0,[fp,-0x2]
8e000a16:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000a1a:	4033      	sub r2,r0,0
8e000a1c:	1200      	beq 8e000a40 <bjk_abort+0x6c>
8e000a1e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000a22:	0216      	lsl r0,r0,0x10
8e000a24:	020e      	asr r0,r0,0x10
8e000a26:	2033      	sub r1,r0,0
8e000a28:	0c90      	blte 8e000a40 <bjk_abort+0x6c>
8e000a2a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000a2e:	0216      	lsl r0,r0,0x10
8e000a30:	020e      	asr r0,r0,0x10
8e000a32:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000a36:	4f8b 0142 	mov r2,0x147c
8e000a3a:	400b 18e2 	movt r2,0x8e00
8e000a3e:	0952      	jalr r2
8e000a40:	108b 0032 	mov r0,0x384
8e000a44:	000b 1002 	movt r0,0x0
8e000a48:	0044      	ldr r0,[r0]
8e000a4a:	1ddc 0500 	str r0,[fp,-0x3]
8e000a4e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000a52:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000a56:	21d4      	str r1,[r0,0x3]
8e000a58:	108b 0032 	mov r0,0x384
8e000a5c:	000b 1002 	movt r0,0x0
8e000a60:	0044      	ldr r0,[r0]
8e000a62:	02cc 0001 	ldr r0,[r0,+0xd]
8e000a66:	1e5c 0500 	str r0,[fp,-0x4]
8e000a6a:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a6e:	4033      	sub r2,r0,0
8e000a70:	1600      	beq 8e000a9c <bjk_abort+0xc8>
8e000a72:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a76:	2044      	ldr r1,[r0]
8e000a78:	1bab 0cc2 	mov r0,0xccdd
8e000a7c:	176b 1aa2 	movt r0,0xaabb
8e000a80:	443a      	sub r2,r1,r0
8e000a82:	0d10      	bne 8e000a9c <bjk_abort+0xc8>
8e000a84:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a88:	3e2b 0ff2 	mov r1,0xfff1
8e000a8c:	2314      	strb r1,[r0,0x6]
8e000a8e:	01a2      	nop
8e000a90:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a94:	0304      	ldrb r0,[r0,0x6]
8e000a96:	20bb 001e 	sub r1,r0,241
8e000a9a:	fb10      	bne 8e000a90 <bjk_abort+0xbc>
8e000a9c:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000aa0:	c0ef e002 	mov r62,r0
8e000aa4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000aa8:	e0ef e002 	mov r63,r0
8e000aac:	0392      	gid
8e000aae:	0fe2      	trap 0x3
8e000ab0:	0912      	movfs r0,pc
8e000ab2:	0152      	jalr r0
8e000ab4:	01a2      	nop
8e000ab6:	d66c 2400 	ldrd lr,[sp,+0x4]
8e000aba:	b41b 2404 	add sp,sp,32
8e000abe:	194f 0402 	rts
8e000ac2:	01a2      	nop

8e000ac4 <abort>:
8e000ac4:	d57c 2700 	strd lr,[sp],-0x2
8e000ac8:	f41b 2402 	add fp,sp,16

8e000acc <ck2_abort>:
8e000acc:	b98b e0a2 	mov r61,0xacc
8e000ad0:	a00b f8e2 	movt r61,0x8e00
8e000ad4:	14ef 1c02 	mov r0,r61
8e000ad8:	1cdc 0500 	str r0,[fp,-0x1]
8e000adc:	3a0b 0272 	mov r1,0x27d0
8e000ae0:	200b 18e2 	movt r1,0x8e00
8e000ae4:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ae8:	5a8b 0092 	mov r2,0x9d4
8e000aec:	400b 18e2 	movt r2,0x8e00
8e000af0:	0952      	jalr r2
8e000af2:	188b 00a2 	mov r0,0xac4
8e000af6:	000b 18e2 	movt r0,0x8e00
8e000afa:	280b 0272 	mov r1,0x2740
8e000afe:	200b 18e2 	movt r1,0x8e00
8e000b02:	5a8b 0092 	mov r2,0x9d4
8e000b06:	400b 18e2 	movt r2,0x8e00
8e000b0a:	0952      	jalr r2
8e000b0c:	00e0      	b 8e000b0c <ck2_abort+0x40>
8e000b0e:	01a2      	nop

8e000b10 <bjk_set_irq0_handler>:
8e000b10:	f65c 2700 	str fp,[sp],-0x4
8e000b14:	f4ef 2402 	mov fp,sp
8e000b18:	0003      	mov r0,0x0
8e000b1a:	1ddc 0400 	str r0,[fp,+0x3]
8e000b1e:	008b 0022 	mov r0,0x204
8e000b22:	000b 1002 	movt r0,0x0
8e000b26:	0026      	lsr r0,r0,0x1
8e000b28:	2116      	lsl r1,r0,0x8
8e000b2a:	1d03      	mov r0,0xe8
8e000b2c:	247a      	orr r1,r1,r0
8e000b2e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000b32:	2054      	str r1,[r0]
8e000b34:	01a2      	nop
8e000b36:	f64c 2400 	ldr fp,[sp,+0x4]
8e000b3a:	b41b 2402 	add sp,sp,16
8e000b3e:	194f 0402 	rts
8e000b42:	01a2      	nop

8e000b44 <bj_host_init>:
8e000b44:	d4fc 2700 	strd lr,[sp],-0x1
8e000b48:	f41b 2401 	add fp,sp,8
8e000b4c:	088b 00b2 	mov r0,0xb44
8e000b50:	000b 18e2 	movt r0,0x8e00
8e000b54:	3f0b 0262 	mov r1,0x26f8
8e000b58:	200b 18e2 	movt r1,0x8e00
8e000b5c:	5a8b 0092 	mov r2,0x9d4
8e000b60:	400b 18e2 	movt r2,0x8e00
8e000b64:	0952      	jalr r2
8e000b66:	01a2      	nop
8e000b68:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b6c:	b41b 2401 	add sp,sp,8
8e000b70:	194f 0402 	rts

8e000b74 <bj_host_run>:
8e000b74:	d4fc 2700 	strd lr,[sp],-0x1
8e000b78:	f41b 2401 	add fp,sp,8
8e000b7c:	0e8b 00b2 	mov r0,0xb74
8e000b80:	000b 18e2 	movt r0,0x8e00
8e000b84:	220b 0272 	mov r1,0x2710
8e000b88:	200b 18e2 	movt r1,0x8e00
8e000b8c:	5a8b 0092 	mov r2,0x9d4
8e000b90:	400b 18e2 	movt r2,0x8e00
8e000b94:	0952      	jalr r2
8e000b96:	01a2      	nop
8e000b98:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b9c:	b41b 2401 	add sp,sp,8
8e000ba0:	194f 0402 	rts

8e000ba4 <bj_host_finish>:
8e000ba4:	d4fc 2700 	strd lr,[sp],-0x1
8e000ba8:	f41b 2401 	add fp,sp,8
8e000bac:	148b 00b2 	mov r0,0xba4
8e000bb0:	000b 18e2 	movt r0,0x8e00
8e000bb4:	250b 0272 	mov r1,0x2728
8e000bb8:	200b 18e2 	movt r1,0x8e00
8e000bbc:	5a8b 0092 	mov r2,0x9d4
8e000bc0:	400b 18e2 	movt r2,0x8e00
8e000bc4:	0952      	jalr r2
8e000bc6:	01a2      	nop
8e000bc8:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000bcc:	b41b 2401 	add sp,sp,8
8e000bd0:	194f 0402 	rts

8e000bd4 <bj_rr_init>:
8e000bd4:	d5fc 2700 	strd lr,[sp],-0x3
8e000bd8:	f41b 2403 	add fp,sp,24
8e000bdc:	1cdc 0500 	str r0,[fp,-0x1]
8e000be0:	04e2      	mov r0,r1
8e000be2:	5ddc 0500 	str r2,[fp,-0x3]
8e000be6:	2ce2      	mov r1,r3
8e000be8:	1e3c 0500 	strh r0,[fp,-0x4]
8e000bec:	04e2      	mov r0,r1
8e000bee:	1c1c 0502 	strb r0,[fp,-0x10]
8e000bf2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000bf6:	2033      	sub r1,r0,0
8e000bf8:	8408 0000 	beq 8e000d00 <bj_rr_init+0x12c>
8e000bfc:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c00:	3bab 0cc2 	mov r1,0xccdd
8e000c04:	376b 1aa2 	movt r1,0xaabb
8e000c08:	2054      	str r1,[r0]
8e000c0a:	01a2      	nop
8e000c0c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c10:	2044      	ldr r1,[r0]
8e000c12:	1bab 0cc2 	mov r0,0xccdd
8e000c16:	176b 1aa2 	movt r0,0xaabb
8e000c1a:	443a      	sub r2,r1,r0
8e000c1c:	f810      	bne 8e000c0c <bj_rr_init+0x38>
8e000c1e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c22:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000c26:	20d4      	str r1,[r0,0x1]
8e000c28:	01a2      	nop
8e000c2a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c2e:	20c4      	ldr r1,[r0,0x1]
8e000c30:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000c34:	443a      	sub r2,r1,r0
8e000c36:	fa10      	bne 8e000c2a <bj_rr_init+0x56>
8e000c38:	1c0c 0502 	ldrb r0,[fp,-0x10]
8e000c3c:	2033      	sub r1,r0,0
8e000c3e:	0d00      	beq 8e000c58 <bj_rr_init+0x84>
8e000c40:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c44:	00c4      	ldr r0,[r0,0x1]
8e000c46:	3e2c 0500 	ldrh r1,[fp,-0x4]
8e000c4a:	44e2      	mov r2,r1
8e000c4c:	2003      	mov r1,0x0
8e000c4e:	6b8b 0032 	mov r3,0x35c
8e000c52:	600b 18e2 	movt r3,0x8e00
8e000c56:	0d52      	jalr r3
8e000c58:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000c5c:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000c60:	241a      	add r1,r1,r0
8e000c62:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c66:	2154      	str r1,[r0,0x2]
8e000c68:	01a2      	nop
8e000c6a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c6e:	2144      	ldr r1,[r0,0x2]
8e000c70:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000c74:	5dcc 0500 	ldr r2,[fp,-0x3]
8e000c78:	081a      	add r0,r2,r0
8e000c7a:	443a      	sub r2,r1,r0
8e000c7c:	f710      	bne 8e000c6a <bj_rr_init+0x96>
8e000c7e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c82:	20c4      	ldr r1,[r0,0x1]
8e000c84:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c88:	21d4      	str r1,[r0,0x3]
8e000c8a:	01a2      	nop
8e000c8c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c90:	21c4      	ldr r1,[r0,0x3]
8e000c92:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c96:	00c4      	ldr r0,[r0,0x1]
8e000c98:	443a      	sub r2,r1,r0
8e000c9a:	f910      	bne 8e000c8c <bj_rr_init+0xb8>
8e000c9c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ca0:	20c4      	ldr r1,[r0,0x1]
8e000ca2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ca6:	2254      	str r1,[r0,0x4]
8e000ca8:	01a2      	nop
8e000caa:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cae:	2244      	ldr r1,[r0,0x4]
8e000cb0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cb4:	00c4      	ldr r0,[r0,0x1]
8e000cb6:	443a      	sub r2,r1,r0
8e000cb8:	f910      	bne 8e000caa <bj_rr_init+0xd6>
8e000cba:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cbe:	2003      	mov r1,0x0
8e000cc0:	22d4      	str r1,[r0,0x5]
8e000cc2:	01a2      	nop
8e000cc4:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cc8:	02c4      	ldr r0,[r0,0x5]
8e000cca:	2033      	sub r1,r0,0
8e000ccc:	fc10      	bne 8e000cc4 <bj_rr_init+0xf0>
8e000cce:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cd2:	2003      	mov r1,0x0
8e000cd4:	201c 0003 	strb r1,[r0,+0x18]
8e000cd8:	01a2      	nop
8e000cda:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cde:	000c 0003 	ldrb r0,[r0,+0x18]
8e000ce2:	4033      	sub r2,r0,0
8e000ce4:	fb10      	bne 8e000cda <bj_rr_init+0x106>
8e000ce6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cea:	2003      	mov r1,0x0
8e000cec:	209c 0003 	strb r1,[r0,+0x19]
8e000cf0:	01a2      	nop
8e000cf2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000cf6:	008c 0003 	ldrb r0,[r0,+0x19]
8e000cfa:	2033      	sub r1,r0,0
8e000cfc:	fb10      	bne 8e000cf2 <bj_rr_init+0x11e>
8e000cfe:	02e0      	b 8e000d02 <bj_rr_init+0x12e>
8e000d00:	01a2      	nop
8e000d02:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e000d06:	b41b 2403 	add sp,sp,24
8e000d0a:	194f 0402 	rts
8e000d0e:	01a2      	nop

8e000d10 <bj_rr_read_obj>:
8e000d10:	d77c 2700 	strd lr,[sp],-0x6
8e000d14:	f41b 2406 	add fp,sp,48
8e000d18:	1fdc 0500 	str r0,[fp,-0x7]
8e000d1c:	04e2      	mov r0,r1
8e000d1e:	5cdc 0501 	str r2,[fp,-0x9]
8e000d22:	1c3c 0502 	strh r0,[fp,-0x10]
8e000d26:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d2a:	2033      	sub r1,r0,0
8e000d2c:	0410      	bne 8e000d34 <bj_rr_read_obj+0x24>
8e000d2e:	0003      	mov r0,0x0
8e000d30:	e7e8 0000 	b 8e000efe <bj_rr_read_obj+0x1ee>
8e000d34:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d38:	0244      	ldr r0,[r0,0x4]
8e000d3a:	1edc 0500 	str r0,[fp,-0x5]
8e000d3e:	1e1b 04fd 	add r0,fp,-20
8e000d42:	20e2      	mov r1,r0
8e000d44:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d48:	468b 0132 	mov r2,0x1334
8e000d4c:	400b 18e2 	movt r2,0x8e00
8e000d50:	0952      	jalr r2
8e000d52:	1ebc 0500 	strh r0,[fp,-0x5]
8e000d56:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000d5a:	4033      	sub r2,r0,0
8e000d5c:	1310      	bne 8e000d82 <bj_rr_read_obj+0x72>
8e000d5e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d62:	3feb 0ff2 	mov r1,0xffff
8e000d66:	209c 0003 	strb r1,[r0,+0x19]
8e000d6a:	01a2      	nop
8e000d6c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d70:	008c 0003 	ldrb r0,[r0,+0x19]
8e000d74:	0316      	lsl r0,r0,0x18
8e000d76:	030e      	asr r0,r0,0x18
8e000d78:	23b3      	sub r1,r0,-1
8e000d7a:	f910      	bne 8e000d6c <bj_rr_read_obj+0x5c>
8e000d7c:	0003      	mov r0,0x0
8e000d7e:	c0e8 0000 	b 8e000efe <bj_rr_read_obj+0x1ee>
8e000d82:	3eac 0500 	ldrh r1,[fp,-0x5]
8e000d86:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000d8a:	443a      	sub r2,r1,r0
8e000d8c:	1340      	blteu 8e000db2 <bj_rr_read_obj+0xa2>
8e000d8e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d92:	3fcb 0ff2 	mov r1,0xfffe
8e000d96:	209c 0003 	strb r1,[r0,+0x19]
8e000d9a:	01a2      	nop
8e000d9c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000da0:	008c 0003 	ldrb r0,[r0,+0x19]
8e000da4:	0316      	lsl r0,r0,0x18
8e000da6:	030e      	asr r0,r0,0x18
8e000da8:	2333      	sub r1,r0,-2
8e000daa:	f910      	bne 8e000d9c <bj_rr_read_obj+0x8c>
8e000dac:	0003      	mov r0,0x0
8e000dae:	a8e8 0000 	b 8e000efe <bj_rr_read_obj+0x1ee>
8e000db2:	3eac 0500 	ldrh r1,[fp,-0x5]
8e000db6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dba:	0144      	ldr r0,[r0,0x2]
8e000dbc:	40e2      	mov r2,r0
8e000dbe:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dc2:	00c4      	ldr r0,[r0,0x1]
8e000dc4:	083a      	sub r0,r2,r0
8e000dc6:	443a      	sub r2,r1,r0
8e000dc8:	1390      	blte 8e000dee <bj_rr_read_obj+0xde>
8e000dca:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dce:	3fab 0ff2 	mov r1,0xfffd
8e000dd2:	209c 0003 	strb r1,[r0,+0x19]
8e000dd6:	01a2      	nop
8e000dd8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ddc:	008c 0003 	ldrb r0,[r0,+0x19]
8e000de0:	0316      	lsl r0,r0,0x18
8e000de2:	030e      	asr r0,r0,0x18
8e000de4:	22b3      	sub r1,r0,-3
8e000de6:	f910      	bne 8e000dd8 <bj_rr_read_obj+0xc8>
8e000de8:	0003      	mov r0,0x0
8e000dea:	8ae8 0000 	b 8e000efe <bj_rr_read_obj+0x1ee>
8e000dee:	0003      	mov r0,0x0
8e000df0:	1cbc 0500 	strh r0,[fp,-0x1]
8e000df4:	20e0      	b 8e000e34 <bj_rr_read_obj+0x124>
8e000df6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000dfa:	2144      	ldr r1,[r0,0x2]
8e000dfc:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000e00:	443a      	sub r2,r1,r0
8e000e02:	0610      	bne 8e000e0e <bj_rr_read_obj+0xfe>
8e000e04:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e08:	00c4      	ldr r0,[r0,0x1]
8e000e0a:	1edc 0500 	str r0,[fp,-0x5]
8e000e0e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000e12:	3ccc 0501 	ldr r1,[fp,-0x9]
8e000e16:	041a      	add r0,r1,r0
8e000e18:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000e1c:	2404      	ldrb r1,[r1]
8e000e1e:	2014      	strb r1,[r0]
8e000e20:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000e24:	0093      	add r0,r0,1
8e000e26:	1edc 0500 	str r0,[fp,-0x5]
8e000e2a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000e2e:	0093      	add r0,r0,1
8e000e30:	1cbc 0500 	strh r0,[fp,-0x1]
8e000e34:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000e38:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000e3c:	443a      	sub r2,r1,r0
8e000e3e:	dc50      	bltu 8e000df6 <bj_rr_read_obj+0xe6>
8e000e40:	1e1b 04fd 	add r0,fp,-20
8e000e44:	20e2      	mov r1,r0
8e000e46:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e4a:	468b 0132 	mov r2,0x1334
8e000e4e:	400b 18e2 	movt r2,0x8e00
8e000e52:	0952      	jalr r2
8e000e54:	1f3c 0500 	strh r0,[fp,-0x6]
8e000e58:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000e5c:	20e2      	mov r1,r0
8e000e5e:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000e62:	4e8b 0112 	mov r2,0x1174
8e000e66:	400b 18e2 	movt r2,0x8e00
8e000e6a:	0952      	jalr r2
8e000e6c:	1fbc 0500 	strh r0,[fp,-0x7]
8e000e70:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000e74:	1fac 0500 	ldrh r0,[fp,-0x7]
8e000e78:	443a      	sub r2,r1,r0
8e000e7a:	1200      	beq 8e000e9e <bj_rr_read_obj+0x18e>
8e000e7c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e80:	3f8b 0ff2 	mov r1,0xfffc
8e000e84:	209c 0003 	strb r1,[r0,+0x19]
8e000e88:	01a2      	nop
8e000e8a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e8e:	008c 0003 	ldrb r0,[r0,+0x19]
8e000e92:	0316      	lsl r0,r0,0x18
8e000e94:	030e      	asr r0,r0,0x18
8e000e96:	2233      	sub r1,r0,-4
8e000e98:	f910      	bne 8e000e8a <bj_rr_read_obj+0x17a>
8e000e9a:	0003      	mov r0,0x0
8e000e9c:	31e0      	b 8e000efe <bj_rr_read_obj+0x1ee>
8e000e9e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ea2:	0244      	ldr r0,[r0,0x4]
8e000ea4:	1d5c 0500 	str r0,[fp,-0x2]
8e000ea8:	16e0      	b 8e000ed4 <bj_rr_read_obj+0x1c4>
8e000eaa:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000eae:	2144      	ldr r1,[r0,0x2]
8e000eb0:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000eb4:	443a      	sub r2,r1,r0
8e000eb6:	0610      	bne 8e000ec2 <bj_rr_read_obj+0x1b2>
8e000eb8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ebc:	00c4      	ldr r0,[r0,0x1]
8e000ebe:	1d5c 0500 	str r0,[fp,-0x2]
8e000ec2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ec6:	2003      	mov r1,0x0
8e000ec8:	2014      	strb r1,[r0]
8e000eca:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ece:	0093      	add r0,r0,1
8e000ed0:	1d5c 0500 	str r0,[fp,-0x2]
8e000ed4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000ed8:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000edc:	443a      	sub r2,r1,r0
8e000ede:	e610      	bne 8e000eaa <bj_rr_read_obj+0x19a>
8e000ee0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ee4:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000ee8:	2254      	str r1,[r0,0x4]
8e000eea:	01a2      	nop
8e000eec:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ef0:	2244      	ldr r1,[r0,0x4]
8e000ef2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ef6:	443a      	sub r2,r1,r0
8e000ef8:	fa10      	bne 8e000eec <bj_rr_read_obj+0x1dc>
8e000efa:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000efe:	d76c 2400 	ldrd lr,[sp,+0x6]
8e000f02:	b41b 2406 	add sp,sp,48
8e000f06:	194f 0402 	rts
8e000f0a:	01a2      	nop

8e000f0c <bj_rr_write_obj>:
8e000f0c:	d77c 2700 	strd lr,[sp],-0x6
8e000f10:	f41b 2406 	add fp,sp,48
8e000f14:	1fdc 0500 	str r0,[fp,-0x7]
8e000f18:	04e2      	mov r0,r1
8e000f1a:	5cdc 0501 	str r2,[fp,-0x9]
8e000f1e:	1c3c 0502 	strh r0,[fp,-0x10]
8e000f22:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f26:	2033      	sub r1,r0,0
8e000f28:	0410      	bne 8e000f30 <bj_rr_write_obj+0x24>
8e000f2a:	0003      	mov r0,0x0
8e000f2c:	1de8 0001 	b 8e001166 <bj_rr_write_obj+0x25a>
8e000f30:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f34:	02c4      	ldr r0,[r0,0x5]
8e000f36:	1e5c 0500 	str r0,[fp,-0x4]
8e000f3a:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000f3e:	1cbc 0501 	strh r0,[fp,-0x9]
8e000f42:	3cac 0501 	ldrh r1,[fp,-0x9]
8e000f46:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f4a:	0144      	ldr r0,[r0,0x2]
8e000f4c:	40e2      	mov r2,r0
8e000f4e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f52:	00c4      	ldr r0,[r0,0x1]
8e000f54:	083a      	sub r0,r2,r0
8e000f56:	0213      	add r0,r0,-4
8e000f58:	443a      	sub r2,r1,r0
8e000f5a:	2540      	blteu 8e000fa4 <bj_rr_write_obj+0x98>
8e000f5c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f60:	3feb 0ff2 	mov r1,0xffff
8e000f64:	201c 0003 	strb r1,[r0,+0x18]
8e000f68:	01a2      	nop
8e000f6a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f6e:	000c 0003 	ldrb r0,[r0,+0x18]
8e000f72:	0316      	lsl r0,r0,0x18
8e000f74:	030e      	asr r0,r0,0x18
8e000f76:	23b3      	sub r1,r0,-1
8e000f78:	f910      	bne 8e000f6a <bj_rr_write_obj+0x5e>
8e000f7a:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f7e:	0093      	add r0,r0,1
8e000f80:	1e5c 0500 	str r0,[fp,-0x4]
8e000f84:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f88:	3e4c 0500 	ldr r1,[fp,-0x4]
8e000f8c:	22d4      	str r1,[r0,0x5]
8e000f8e:	01a2      	nop
8e000f90:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f94:	22c4      	ldr r1,[r0,0x5]
8e000f96:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f9a:	443a      	sub r2,r1,r0
8e000f9c:	fa10      	bne 8e000f90 <bj_rr_write_obj+0x84>
8e000f9e:	0003      	mov r0,0x0
8e000fa0:	e3e8 0000 	b 8e001166 <bj_rr_write_obj+0x25a>
8e000fa4:	1cac 0501 	ldrh r0,[fp,-0x9]
8e000fa8:	2033      	sub r1,r0,0
8e000faa:	2510      	bne 8e000ff4 <bj_rr_write_obj+0xe8>
8e000fac:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fb0:	3fcb 0ff2 	mov r1,0xfffe
8e000fb4:	201c 0003 	strb r1,[r0,+0x18]
8e000fb8:	01a2      	nop
8e000fba:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fbe:	000c 0003 	ldrb r0,[r0,+0x18]
8e000fc2:	0316      	lsl r0,r0,0x18
8e000fc4:	030e      	asr r0,r0,0x18
8e000fc6:	4333      	sub r2,r0,-2
8e000fc8:	f910      	bne 8e000fba <bj_rr_write_obj+0xae>
8e000fca:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000fce:	0093      	add r0,r0,1
8e000fd0:	1e5c 0500 	str r0,[fp,-0x4]
8e000fd4:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fd8:	3e4c 0500 	ldr r1,[fp,-0x4]
8e000fdc:	22d4      	str r1,[r0,0x5]
8e000fde:	01a2      	nop
8e000fe0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fe4:	22c4      	ldr r1,[r0,0x5]
8e000fe6:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000fea:	443a      	sub r2,r1,r0
8e000fec:	fa10      	bne 8e000fe0 <bj_rr_write_obj+0xd4>
8e000fee:	0003      	mov r0,0x0
8e000ff0:	bbe8 0000 	b 8e001166 <bj_rr_write_obj+0x25a>
8e000ff4:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000ff8:	031b 0000 	add r0,r0,6
8e000ffc:	1cbc 0500 	strh r0,[fp,-0x1]
8e001000:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001004:	01c4      	ldr r0,[r0,0x3]
8e001006:	1d5c 0500 	str r0,[fp,-0x2]
8e00100a:	20e0      	b 8e00104a <bj_rr_write_obj+0x13e>
8e00100c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001010:	2144      	ldr r1,[r0,0x2]
8e001012:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001016:	443a      	sub r2,r1,r0
8e001018:	0610      	bne 8e001024 <bj_rr_write_obj+0x118>
8e00101a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00101e:	00c4      	ldr r0,[r0,0x1]
8e001020:	1d5c 0500 	str r0,[fp,-0x2]
8e001024:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001028:	0004      	ldrb r0,[r0]
8e00102a:	2033      	sub r1,r0,0
8e00102c:	0500      	beq 8e001036 <bj_rr_write_obj+0x12a>
8e00102e:	0003      	mov r0,0x0
8e001030:	1d5c 0500 	str r0,[fp,-0x2]
8e001034:	0fe0      	b 8e001052 <bj_rr_write_obj+0x146>
8e001036:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00103a:	0093      	add r0,r0,1
8e00103c:	1d5c 0500 	str r0,[fp,-0x2]
8e001040:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001044:	0393      	add r0,r0,-1
8e001046:	1cbc 0500 	strh r0,[fp,-0x1]
8e00104a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00104e:	4033      	sub r2,r0,0
8e001050:	de10      	bne 8e00100c <bj_rr_write_obj+0x100>
8e001052:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001056:	2033      	sub r1,r0,0
8e001058:	2410      	bne 8e0010a0 <bj_rr_write_obj+0x194>
8e00105a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00105e:	3fab 0ff2 	mov r1,0xfffd
8e001062:	201c 0003 	strb r1,[r0,+0x18]
8e001066:	01a2      	nop
8e001068:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00106c:	000c 0003 	ldrb r0,[r0,+0x18]
8e001070:	0316      	lsl r0,r0,0x18
8e001072:	030e      	asr r0,r0,0x18
8e001074:	42b3      	sub r2,r0,-3
8e001076:	f910      	bne 8e001068 <bj_rr_write_obj+0x15c>
8e001078:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00107c:	0093      	add r0,r0,1
8e00107e:	1e5c 0500 	str r0,[fp,-0x4]
8e001082:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001086:	3e4c 0500 	ldr r1,[fp,-0x4]
8e00108a:	22d4      	str r1,[r0,0x5]
8e00108c:	01a2      	nop
8e00108e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001092:	22c4      	ldr r1,[r0,0x5]
8e001094:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001098:	443a      	sub r2,r1,r0
8e00109a:	fa10      	bne 8e00108e <bj_rr_write_obj+0x182>
8e00109c:	0003      	mov r0,0x0
8e00109e:	64e0      	b 8e001166 <bj_rr_write_obj+0x25a>
8e0010a0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010a4:	01c4      	ldr r0,[r0,0x3]
8e0010a6:	1f5c 0500 	str r0,[fp,-0x6]
8e0010aa:	3c2c 0502 	ldrh r1,[fp,-0x10]
8e0010ae:	1c1b 04fd 	add r0,fp,-24
8e0010b2:	44e2      	mov r2,r1
8e0010b4:	20e2      	mov r1,r0
8e0010b6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010ba:	7b0b 0132 	mov r3,0x13d8
8e0010be:	600b 18e2 	movt r3,0x8e00
8e0010c2:	0d52      	jalr r3
8e0010c4:	0003      	mov r0,0x0
8e0010c6:	1ebc 0500 	strh r0,[fp,-0x5]
8e0010ca:	20e0      	b 8e00110a <bj_rr_write_obj+0x1fe>
8e0010cc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010d0:	2144      	ldr r1,[r0,0x2]
8e0010d2:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010d6:	443a      	sub r2,r1,r0
8e0010d8:	0610      	bne 8e0010e4 <bj_rr_write_obj+0x1d8>
8e0010da:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010de:	00c4      	ldr r0,[r0,0x1]
8e0010e0:	1f5c 0500 	str r0,[fp,-0x6]
8e0010e4:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010e8:	3eac 0500 	ldrh r1,[fp,-0x5]
8e0010ec:	5ccc 0501 	ldr r2,[fp,-0x9]
8e0010f0:	289a      	add r1,r2,r1
8e0010f2:	2404      	ldrb r1,[r1]
8e0010f4:	2014      	strb r1,[r0]
8e0010f6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010fa:	0093      	add r0,r0,1
8e0010fc:	1f5c 0500 	str r0,[fp,-0x6]
8e001100:	1eac 0500 	ldrh r0,[fp,-0x5]
8e001104:	0093      	add r0,r0,1
8e001106:	1ebc 0500 	strh r0,[fp,-0x5]
8e00110a:	3eac 0500 	ldrh r1,[fp,-0x5]
8e00110e:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001112:	443a      	sub r2,r1,r0
8e001114:	dc50      	bltu 8e0010cc <bj_rr_write_obj+0x1c0>
8e001116:	1cac 0501 	ldrh r0,[fp,-0x9]
8e00111a:	20e2      	mov r1,r0
8e00111c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e001120:	4e8b 0112 	mov r2,0x1174
8e001124:	400b 18e2 	movt r2,0x8e00
8e001128:	0952      	jalr r2
8e00112a:	1d3c 0501 	strh r0,[fp,-0xa]
8e00112e:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e001132:	1c1b 04fd 	add r0,fp,-24
8e001136:	44e2      	mov r2,r1
8e001138:	20e2      	mov r1,r0
8e00113a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00113e:	7b0b 0132 	mov r3,0x13d8
8e001142:	600b 18e2 	movt r3,0x8e00
8e001146:	0d52      	jalr r3
8e001148:	3f4c 0500 	ldr r1,[fp,-0x6]
8e00114c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001150:	21d4      	str r1,[r0,0x3]
8e001152:	01a2      	nop
8e001154:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001158:	21c4      	ldr r1,[r0,0x3]
8e00115a:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00115e:	443a      	sub r2,r1,r0
8e001160:	fa10      	bne 8e001154 <bj_rr_write_obj+0x248>
8e001162:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001166:	d76c 2400 	ldrd lr,[sp,+0x6]
8e00116a:	b41b 2406 	add sp,sp,48
8e00116e:	194f 0402 	rts
8e001172:	01a2      	nop

8e001174 <bj_crc16>:
8e001174:	f75c 2700 	str fp,[sp],-0x6
8e001178:	f4ef 2402 	mov fp,sp
8e00117c:	1ddc 0400 	str r0,[fp,+0x3]
8e001180:	04e2      	mov r0,r1
8e001182:	1e3c 0400 	strh r0,[fp,+0x4]
8e001186:	1feb 0ff2 	mov r0,0xffff
8e00118a:	1feb 1ff2 	movt r0,0xffff
8e00118e:	1cbc 0401 	strh r0,[fp,+0x9]
8e001192:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001196:	2033      	sub r1,r0,0
8e001198:	0b10      	bne 8e0011ae <bj_crc16+0x3a>
8e00119a:	3cac 0401 	ldrh r1,[fp,+0x9]
8e00119e:	1feb 0ff2 	mov r0,0xffff
8e0011a2:	1feb 1ff2 	movt r0,0xffff
8e0011a6:	040a      	eor r0,r1,r0
8e0011a8:	000b 1002 	movt r0,0x0
8e0011ac:	65e0      	b 8e001276 <bj_crc16+0x102>
8e0011ae:	0003      	mov r0,0x0
8e0011b0:	1f9c 0402 	strb r0,[fp,+0x17]
8e0011b4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0011b8:	2093      	add r1,r0,1
8e0011ba:	3ddc 0400 	str r1,[fp,+0x3]
8e0011be:	0004      	ldrb r0,[r0]
8e0011c0:	1d3c 0401 	strh r0,[fp,+0xa]
8e0011c4:	2ae0      	b 8e001218 <bj_crc16+0xa4>
8e0011c6:	3cac 0401 	ldrh r1,[fp,+0x9]
8e0011ca:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0011ce:	040a      	eor r0,r1,r0
8e0011d0:	000b 1002 	movt r0,0x0
8e0011d4:	20e2      	mov r1,r0
8e0011d6:	0023      	mov r0,0x1
8e0011d8:	045a      	and r0,r1,r0
8e0011da:	2033      	sub r1,r0,0
8e0011dc:	0f00      	beq 8e0011fa <bj_crc16+0x86>
8e0011de:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0011e2:	0026      	lsr r0,r0,0x1
8e0011e4:	20e2      	mov r1,r0
8e0011e6:	200b 1002 	movt r1,0x0
8e0011ea:	010b 0842 	mov r0,0x8408
8e0011ee:	1feb 1ff2 	movt r0,0xffff
8e0011f2:	040a      	eor r0,r1,r0
8e0011f4:	1cbc 0401 	strh r0,[fp,+0x9]
8e0011f8:	06e0      	b 8e001204 <bj_crc16+0x90>
8e0011fa:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0011fe:	0026      	lsr r0,r0,0x1
8e001200:	1cbc 0401 	strh r0,[fp,+0x9]
8e001204:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e001208:	0093      	add r0,r0,1
8e00120a:	1f9c 0402 	strb r0,[fp,+0x17]
8e00120e:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e001212:	0026      	lsr r0,r0,0x1
8e001214:	1d3c 0401 	strh r0,[fp,+0xa]
8e001218:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e00121c:	23bb 0000 	sub r1,r0,7
8e001220:	d340      	blteu 8e0011c6 <bj_crc16+0x52>
8e001222:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001226:	0393      	add r0,r0,-1
8e001228:	1e3c 0400 	strh r0,[fp,+0x4]
8e00122c:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001230:	2033      	sub r1,r0,0
8e001232:	be10      	bne 8e0011ae <bj_crc16+0x3a>
8e001234:	3cac 0401 	ldrh r1,[fp,+0x9]
8e001238:	1feb 0ff2 	mov r0,0xffff
8e00123c:	1feb 1ff2 	movt r0,0xffff
8e001240:	040a      	eor r0,r1,r0
8e001242:	1cbc 0401 	strh r0,[fp,+0x9]
8e001246:	1cac 0401 	ldrh r0,[fp,+0x9]
8e00124a:	1d3c 0401 	strh r0,[fp,+0xa]
8e00124e:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001252:	0116      	lsl r0,r0,0x8
8e001254:	20e2      	mov r1,r0
8e001256:	200b 1002 	movt r1,0x0
8e00125a:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e00125e:	0106      	lsr r0,r0,0x8
8e001260:	000b 1002 	movt r0,0x0
8e001264:	000b 1002 	movt r0,0x0
8e001268:	047a      	orr r0,r1,r0
8e00126a:	000b 1002 	movt r0,0x0
8e00126e:	1cbc 0401 	strh r0,[fp,+0x9]
8e001272:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001276:	f74c 2400 	ldr fp,[sp,+0x6]
8e00127a:	b41b 2403 	add sp,sp,24
8e00127e:	194f 0402 	rts
8e001282:	01a2      	nop

8e001284 <bj_get_v16_of_p8>:
8e001284:	f75c 2700 	str fp,[sp],-0x6
8e001288:	f4ef 2402 	mov fp,sp
8e00128c:	1ddc 0400 	str r0,[fp,+0x3]
8e001290:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001294:	0093      	add r0,r0,1
8e001296:	0004      	ldrb r0,[r0]
8e001298:	1dbc 0401 	strh r0,[fp,+0xb]
8e00129c:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0012a0:	0116      	lsl r0,r0,0x8
8e0012a2:	1dbc 0401 	strh r0,[fp,+0xb]
8e0012a6:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0012aa:	0004      	ldrb r0,[r0]
8e0012ac:	20e2      	mov r1,r0
8e0012ae:	200b 1002 	movt r1,0x0
8e0012b2:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0012b6:	047a      	orr r0,r1,r0
8e0012b8:	1dbc 0401 	strh r0,[fp,+0xb]
8e0012bc:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0012c0:	f74c 2400 	ldr fp,[sp,+0x6]
8e0012c4:	b41b 2403 	add sp,sp,24
8e0012c8:	194f 0402 	rts

8e0012cc <bj_set_v16_of_p8>:
8e0012cc:	f75c 2700 	str fp,[sp],-0x6
8e0012d0:	f4ef 2402 	mov fp,sp
8e0012d4:	1ddc 0400 	str r0,[fp,+0x3]
8e0012d8:	04e2      	mov r0,r1
8e0012da:	1e3c 0400 	strh r0,[fp,+0x4]
8e0012de:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e0012e2:	1fe3      	mov r0,0xff
8e0012e4:	045a      	and r0,r1,r0
8e0012e6:	1dbc 0401 	strh r0,[fp,+0xb]
8e0012ea:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e0012ee:	000b 0ff2 	mov r0,0xff00
8e0012f2:	1feb 1ff2 	movt r0,0xffff
8e0012f6:	045a      	and r0,r1,r0
8e0012f8:	1d3c 0401 	strh r0,[fp,+0xa]
8e0012fc:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e001300:	0106      	lsr r0,r0,0x8
8e001302:	1d3c 0401 	strh r0,[fp,+0xa]
8e001306:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00130a:	0093      	add r0,r0,1
8e00130c:	3d2c 0401 	ldrh r1,[fp,+0xa]
8e001310:	2716      	lsl r1,r1,0x18
8e001312:	2706      	lsr r1,r1,0x18
8e001314:	2014      	strb r1,[r0]
8e001316:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00131a:	2316      	lsl r1,r0,0x18
8e00131c:	2706      	lsr r1,r1,0x18
8e00131e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001322:	2014      	strb r1,[r0]
8e001324:	01a2      	nop
8e001326:	f74c 2400 	ldr fp,[sp,+0x6]
8e00132a:	b41b 2403 	add sp,sp,24
8e00132e:	194f 0402 	rts
8e001332:	01a2      	nop

8e001334 <bj_rr_get_v16>:
8e001334:	d67c 2700 	strd lr,[sp],-0x4
8e001338:	f41b 2404 	add fp,sp,32
8e00133c:	1edc 0500 	str r0,[fp,-0x5]
8e001340:	3f5c 0500 	str r1,[fp,-0x6]
8e001344:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001348:	2033      	sub r1,r0,0
8e00134a:	0310      	bne 8e001350 <bj_rr_get_v16+0x1c>
8e00134c:	0003      	mov r0,0x0
8e00134e:	3ee0      	b 8e0013ca <bj_rr_get_v16+0x96>
8e001350:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001354:	0044      	ldr r0,[r0]
8e001356:	1cdc 0500 	str r0,[fp,-0x1]
8e00135a:	0003      	mov r0,0x0
8e00135c:	1d5c 0500 	str r0,[fp,-0x2]
8e001360:	21e0      	b 8e0013a2 <bj_rr_get_v16+0x6e>
8e001362:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001366:	2144      	ldr r1,[r0,0x2]
8e001368:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00136c:	443a      	sub r2,r1,r0
8e00136e:	0610      	bne 8e00137a <bj_rr_get_v16+0x46>
8e001370:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001374:	00c4      	ldr r0,[r0,0x1]
8e001376:	1cdc 0500 	str r0,[fp,-0x1]
8e00137a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00137e:	4004      	ldrb r2,[r0]
8e001380:	3e1b 04fe 	add r1,fp,-12
8e001384:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001388:	041a      	add r0,r1,r0
8e00138a:	28e2      	mov r1,r2
8e00138c:	2014      	strb r1,[r0]
8e00138e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001392:	0093      	add r0,r0,1
8e001394:	1cdc 0500 	str r0,[fp,-0x1]
8e001398:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00139c:	0093      	add r0,r0,1
8e00139e:	1d5c 0500 	str r0,[fp,-0x2]
8e0013a2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0013a6:	20b3      	sub r1,r0,1
8e0013a8:	dd90      	blte 8e001362 <bj_rr_get_v16+0x2e>
8e0013aa:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0013ae:	3ccc 0500 	ldr r1,[fp,-0x1]
8e0013b2:	2054      	str r1,[r0]
8e0013b4:	1e1b 04fe 	add r0,fp,-12
8e0013b8:	308b 0122 	mov r1,0x1284
8e0013bc:	200b 18e2 	movt r1,0x8e00
8e0013c0:	0552      	jalr r1
8e0013c2:	1ebc 0500 	strh r0,[fp,-0x5]
8e0013c6:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0013ca:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0013ce:	b41b 2404 	add sp,sp,32
8e0013d2:	194f 0402 	rts
8e0013d6:	01a2      	nop

8e0013d8 <bj_rr_set_v16>:
8e0013d8:	d6fc 2700 	strd lr,[sp],-0x5
8e0013dc:	f41b 2405 	add fp,sp,40
8e0013e0:	1edc 0500 	str r0,[fp,-0x5]
8e0013e4:	3f5c 0500 	str r1,[fp,-0x6]
8e0013e8:	08e2      	mov r0,r2
8e0013ea:	1f3c 0501 	strh r0,[fp,-0xe]
8e0013ee:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0013f2:	2033      	sub r1,r0,0
8e0013f4:	3c00      	beq 8e00146c <bj_rr_set_v16+0x94>
8e0013f6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0013fa:	0044      	ldr r0,[r0]
8e0013fc:	1cdc 0500 	str r0,[fp,-0x1]
8e001400:	3f2c 0501 	ldrh r1,[fp,-0xe]
8e001404:	1f1b 04fe 	add r0,fp,-10
8e001408:	598b 0122 	mov r2,0x12cc
8e00140c:	400b 18e2 	movt r2,0x8e00
8e001410:	0952      	jalr r2
8e001412:	0003      	mov r0,0x0
8e001414:	1d5c 0500 	str r0,[fp,-0x2]
8e001418:	20e0      	b 8e001458 <bj_rr_set_v16+0x80>
8e00141a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00141e:	2144      	ldr r1,[r0,0x2]
8e001420:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001424:	443a      	sub r2,r1,r0
8e001426:	0610      	bne 8e001432 <bj_rr_set_v16+0x5a>
8e001428:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00142c:	00c4      	ldr r0,[r0,0x1]
8e00142e:	1cdc 0500 	str r0,[fp,-0x1]
8e001432:	3f1b 04fe 	add r1,fp,-10
8e001436:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00143a:	041a      	add r0,r1,r0
8e00143c:	2004      	ldrb r1,[r0]
8e00143e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001442:	2014      	strb r1,[r0]
8e001444:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001448:	0093      	add r0,r0,1
8e00144a:	1cdc 0500 	str r0,[fp,-0x1]
8e00144e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001452:	0093      	add r0,r0,1
8e001454:	1d5c 0500 	str r0,[fp,-0x2]
8e001458:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00145c:	20b3      	sub r1,r0,1
8e00145e:	de90      	blte 8e00141a <bj_rr_set_v16+0x42>
8e001460:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001464:	3ccc 0500 	ldr r1,[fp,-0x1]
8e001468:	2054      	str r1,[r0]
8e00146a:	02e0      	b 8e00146e <bj_rr_set_v16+0x96>
8e00146c:	01a2      	nop
8e00146e:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e001472:	b41b 2405 	add sp,sp,40
8e001476:	194f 0402 	rts
8e00147a:	01a2      	nop

8e00147c <bjk_get_call_stack_trace>:
8e00147c:	d57c 2701 	strd lr,[sp],-0xa
8e001480:	f41b 240a 	add fp,sp,80
8e001484:	3d5c 0502 	str r1,[fp,-0x12]
8e001488:	1d3c 0504 	strh r0,[fp,-0x22]
8e00148c:	1d4c 0502 	ldr r0,[fp,-0x12]
8e001490:	2033      	sub r1,r0,0
8e001492:	0410      	bne 8e00149a <bjk_get_call_stack_trace+0x1e>
8e001494:	0003      	mov r0,0x0
8e001496:	3be8 0001 	b 8e00170c <bjk_get_call_stack_trace+0x290>
8e00149a:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e00149e:	0216      	lsl r0,r0,0x10
8e0014a0:	020e      	asr r0,r0,0x10
8e0014a2:	4033      	sub r2,r0,0
8e0014a4:	0460      	bgt 8e0014ac <bjk_get_call_stack_trace+0x30>
8e0014a6:	0003      	mov r0,0x0
8e0014a8:	32e8 0001 	b 8e00170c <bjk_get_call_stack_trace+0x290>
8e0014ac:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e0014b0:	0216      	lsl r0,r0,0x10
8e0014b2:	020e      	asr r0,r0,0x10
8e0014b4:	0056      	lsl r0,r0,0x2
8e0014b6:	40e2      	mov r2,r0
8e0014b8:	2003      	mov r1,0x0
8e0014ba:	1d4c 0502 	ldr r0,[fp,-0x12]
8e0014be:	6b8b 0032 	mov r3,0x35c
8e0014c2:	600b 18e2 	movt r3,0x8e00
8e0014c6:	0d52      	jalr r3
8e0014c8:	108b 0032 	mov r0,0x384
8e0014cc:	000b 1002 	movt r0,0x0
8e0014d0:	0044      	ldr r0,[r0]
8e0014d2:	3d4c 0502 	ldr r1,[fp,-0x12]
8e0014d6:	20d4      	str r1,[r0,0x1]
8e0014d8:	0003      	mov r0,0x0
8e0014da:	1cdc 0500 	str r0,[fp,-0x1]
8e0014de:	0003      	mov r0,0x0
8e0014e0:	1d5c 0500 	str r0,[fp,-0x2]
8e0014e4:	0003      	mov r0,0x0
8e0014e6:	1ddc 0500 	str r0,[fp,-0x3]
8e0014ea:	0003      	mov r0,0x0
8e0014ec:	1fbc 0500 	strh r0,[fp,-0x7]
8e0014f0:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e0014f4:	0216      	lsl r0,r0,0x10
8e0014f6:	020e      	asr r0,r0,0x10
8e0014f8:	2033      	sub r1,r0,0
8e0014fa:	0460      	bgt 8e001502 <bjk_get_call_stack_trace+0x86>
8e0014fc:	0003      	mov r0,0x0
8e0014fe:	07e8 0001 	b 8e00170c <bjk_get_call_stack_trace+0x290>
8e001502:	0912      	movfs r0,pc
8e001504:	00e2      	mov r0,r0
8e001506:	1cdc 0500 	str r0,[fp,-0x1]
8e00150a:	14ef 0402 	mov r0,sp
8e00150e:	1d5c 0500 	str r0,[fp,-0x2]
8e001512:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001516:	360b 01a2 	mov r1,0x1ab0
8e00151a:	200b 18e2 	movt r1,0x8e00
8e00151e:	0552      	jalr r1
8e001520:	1ddc 0500 	str r0,[fp,-0x3]
8e001524:	c5e8 0000 	b 8e0016ae <bjk_get_call_stack_trace+0x232>
8e001528:	3fac 0500 	ldrh r1,[fp,-0x7]
8e00152c:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e001530:	0216      	lsl r0,r0,0x10
8e001532:	020e      	asr r0,r0,0x10
8e001534:	443a      	sub r2,r1,r0
8e001536:	c208 0000 	beq 8e0016ba <bjk_get_call_stack_trace+0x23e>
8e00153a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00153e:	3b0b 01b2 	mov r1,0x1bd8
8e001542:	200b 18e2 	movt r1,0x8e00
8e001546:	0552      	jalr r1
8e001548:	1c3c 0501 	strh r0,[fp,-0x8]
8e00154c:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001550:	2033      	sub r1,r0,0
8e001552:	b608 0000 	beq 8e0016be <bjk_get_call_stack_trace+0x242>
8e001556:	3c2c 0501 	ldrh r1,[fp,-0x8]
8e00155a:	0023      	mov r0,0x1
8e00155c:	045a      	and r0,r1,r0
8e00155e:	000b 1002 	movt r0,0x0
8e001562:	4033      	sub r2,r0,0
8e001564:	0b00      	beq 8e00157a <bjk_get_call_stack_trace+0xfe>
8e001566:	0f8b 0142 	mov r0,0x147c
8e00156a:	000b 18e2 	movt r0,0x8e00
8e00156e:	2003      	mov r1,0x0
8e001570:	5a8b 0092 	mov r2,0x9d4
8e001574:	400b 18e2 	movt r2,0x8e00
8e001578:	0952      	jalr r2
8e00157a:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00157e:	1edc 0500 	str r0,[fp,-0x5]
8e001582:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001586:	3ecc 0500 	ldr r1,[fp,-0x5]
8e00158a:	041a      	add r0,r1,r0
8e00158c:	1edc 0500 	str r0,[fp,-0x5]
8e001590:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001594:	1d5c 0500 	str r0,[fp,-0x2]
8e001598:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e00159c:	0066      	lsr r0,r0,0x3
8e00159e:	1dbc 0501 	strh r0,[fp,-0xb]
8e0015a2:	1dac 0501 	ldrh r0,[fp,-0xb]
8e0015a6:	0216      	lsl r0,r0,0x10
8e0015a8:	020e      	asr r0,r0,0x10
8e0015aa:	3f1b 04f8 	add r1,fp,-58
8e0015ae:	3c5c 0501 	str r1,[fp,-0x8]
8e0015b2:	1dbc 0503 	strh r0,[fp,-0x1b]
8e0015b6:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015ba:	2f8b 0d42 	mov r1,0xd47c
8e0015be:	3feb 1ff2 	movt r1,0xffff
8e0015c2:	2034      	strh r1,[r0]
8e0015c4:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015c8:	0113      	add r0,r0,2
8e0015ca:	200b 0272 	mov r1,0x2700
8e0015ce:	2034      	strh r1,[r0]
8e0015d0:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015d4:	0024      	ldrh r0,[r0]
8e0015d6:	20e2      	mov r1,r0
8e0015d8:	200b 1002 	movt r1,0x0
8e0015dc:	1dac 0503 	ldrh r0,[fp,-0x1b]
8e0015e0:	40e2      	mov r2,r0
8e0015e2:	00e3      	mov r0,0x7
8e0015e4:	085a      	and r0,r2,r0
8e0015e6:	00f6      	lsl r0,r0,0x7
8e0015e8:	000b 1002 	movt r0,0x0
8e0015ec:	047a      	orr r0,r1,r0
8e0015ee:	000b 1002 	movt r0,0x0
8e0015f2:	20e2      	mov r1,r0
8e0015f4:	200b 1002 	movt r1,0x0
8e0015f8:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015fc:	2034      	strh r1,[r0]
8e0015fe:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001602:	2113      	add r1,r0,2
8e001604:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001608:	0113      	add r0,r0,2
8e00160a:	0024      	ldrh r0,[r0]
8e00160c:	40e2      	mov r2,r0
8e00160e:	400b 1002 	movt r2,0x0
8e001612:	1dac 0503 	ldrh r0,[fp,-0x1b]
8e001616:	0216      	lsl r0,r0,0x10
8e001618:	020e      	asr r0,r0,0x10
8e00161a:	006e      	asr r0,r0,0x3
8e00161c:	000b 1002 	movt r0,0x0
8e001620:	087a      	orr r0,r2,r0
8e001622:	000b 1002 	movt r0,0x0
8e001626:	000b 1002 	movt r0,0x0
8e00162a:	0434      	strh r0,[r1]
8e00162c:	1f1b 04f8 	add r0,fp,-58
8e001630:	20e2      	mov r1,r0
8e001632:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001636:	438b 0192 	mov r2,0x191c
8e00163a:	400b 18e2 	movt r2,0x8e00
8e00163e:	0952      	jalr r2
8e001640:	1fdc 0500 	str r0,[fp,-0x7]
8e001644:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001648:	1e5c 0501 	str r0,[fp,-0xc]
8e00164c:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001650:	0113      	add r0,r0,2
8e001652:	0024      	ldrh r0,[r0]
8e001654:	1edc 0501 	str r0,[fp,-0xd]
8e001658:	1ecc 0501 	ldr r0,[fp,-0xd]
8e00165c:	0216      	lsl r0,r0,0x10
8e00165e:	1edc 0501 	str r0,[fp,-0xd]
8e001662:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001666:	0024      	ldrh r0,[r0]
8e001668:	20e2      	mov r1,r0
8e00166a:	1ecc 0501 	ldr r0,[fp,-0xd]
8e00166e:	00fa      	orr r0,r0,r1
8e001670:	1edc 0501 	str r0,[fp,-0xd]
8e001674:	1ecc 0501 	ldr r0,[fp,-0xd]
8e001678:	1cdc 0501 	str r0,[fp,-0x9]
8e00167c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e001680:	1cdc 0500 	str r0,[fp,-0x1]
8e001684:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001688:	2093      	add r1,r0,1
8e00168a:	3fbc 0500 	strh r1,[fp,-0x7]
8e00168e:	0056      	lsl r0,r0,0x2
8e001690:	3d4c 0502 	ldr r1,[fp,-0x12]
8e001694:	041a      	add r0,r1,r0
8e001696:	3fcc 0500 	ldr r1,[fp,-0x7]
8e00169a:	2054      	str r1,[r0]
8e00169c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0016a0:	360b 01a2 	mov r1,0x1ab0
8e0016a4:	200b 18e2 	movt r1,0x8e00
8e0016a8:	0552      	jalr r1
8e0016aa:	1ddc 0500 	str r0,[fp,-0x3]
8e0016ae:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0016b2:	2033      	sub r1,r0,0
8e0016b4:	3a18 ffff 	bne 8e001528 <bjk_get_call_stack_trace+0xac>
8e0016b8:	04e0      	b 8e0016c0 <bjk_get_call_stack_trace+0x244>
8e0016ba:	01a2      	nop
8e0016bc:	02e0      	b 8e0016c0 <bjk_get_call_stack_trace+0x244>
8e0016be:	01a2      	nop
8e0016c0:	108b 0032 	mov r0,0x384
8e0016c4:	000b 1002 	movt r0,0x0
8e0016c8:	0044      	ldr r0,[r0]
8e0016ca:	001b 0037 	add r0,r0,440
8e0016ce:	1d5c 0501 	str r0,[fp,-0xa]
8e0016d2:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0016d6:	0024      	ldrh r0,[r0]
8e0016d8:	40bb 0008 	sub r2,r0,65
8e0016dc:	1610      	bne 8e001708 <bjk_get_call_stack_trace+0x28c>
8e0016de:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0016e2:	3a0b 0192 	mov r1,0x19d0
8e0016e6:	200b 18e2 	movt r1,0x8e00
8e0016ea:	0552      	jalr r1
8e0016ec:	1ddc 0501 	str r0,[fp,-0xb]
8e0016f0:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0016f4:	2093      	add r1,r0,1
8e0016f6:	3fbc 0500 	strh r1,[fp,-0x7]
8e0016fa:	0056      	lsl r0,r0,0x2
8e0016fc:	3d4c 0502 	ldr r1,[fp,-0x12]
8e001700:	041a      	add r0,r1,r0
8e001702:	3dcc 0501 	ldr r1,[fp,-0xb]
8e001706:	2054      	str r1,[r0]
8e001708:	1fac 0500 	ldrh r0,[fp,-0x7]
8e00170c:	d56c 2401 	ldrd lr,[sp,+0xa]
8e001710:	b41b 240a 	add sp,sp,80
8e001714:	194f 0402 	rts

8e001718 <bjk_wait_sync>:
8e001718:	d67c 2700 	strd lr,[sp],-0x4
8e00171c:	f41b 2404 	add fp,sp,32
8e001720:	1ddc 0500 	str r0,[fp,-0x3]
8e001724:	04e2      	mov r0,r1
8e001726:	5edc 0500 	str r2,[fp,-0x5]
8e00172a:	1c3c 0501 	strh r0,[fp,-0x8]
8e00172e:	108b 0032 	mov r0,0x384
8e001732:	000b 1002 	movt r0,0x0
8e001736:	0044      	ldr r0,[r0]
8e001738:	02cc 0001 	ldr r0,[r0,+0xd]
8e00173c:	1cdc 0500 	str r0,[fp,-0x1]
8e001740:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001744:	2033      	sub r1,r0,0
8e001746:	4c00      	beq 8e0017de <bjk_wait_sync+0xc6>
8e001748:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e00174c:	0216      	lsl r0,r0,0x10
8e00174e:	020e      	asr r0,r0,0x10
8e001750:	4033      	sub r2,r0,0
8e001752:	1090      	blte 8e001772 <bjk_wait_sync+0x5a>
8e001754:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001758:	2033      	sub r1,r0,0
8e00175a:	0c00      	beq 8e001772 <bjk_wait_sync+0x5a>
8e00175c:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001760:	0216      	lsl r0,r0,0x10
8e001762:	020e      	asr r0,r0,0x10
8e001764:	3ecc 0500 	ldr r1,[fp,-0x5]
8e001768:	4f8b 0142 	mov r2,0x147c
8e00176c:	400b 18e2 	movt r2,0x8e00
8e001770:	0952      	jalr r2
8e001772:	0003      	mov r0,0x0
8e001774:	1dbc 0500 	strh r0,[fp,-0x3]
8e001778:	0392      	gid
8e00177a:	051f 0402 	movfs r0,imask
8e00177e:	1dbc 0500 	strh r0,[fp,-0x3]
8e001782:	1fcb 0032 	mov r0,0x3fe
8e001786:	050f 0402 	movts imask,r0
8e00178a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00178e:	4033      	sub r2,r0,0
8e001790:	0410      	bne 8e001798 <bjk_wait_sync+0x80>
8e001792:	1543      	mov r0,0xaa
8e001794:	1ddc 0500 	str r0,[fp,-0x3]
8e001798:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00179c:	2316      	lsl r1,r0,0x18
8e00179e:	2706      	lsr r1,r1,0x18
8e0017a0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017a4:	2394      	strb r1,[r0,0x7]
8e0017a6:	01a2      	nop
8e0017a8:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017ac:	0384      	ldrb r0,[r0,0x7]
8e0017ae:	20e2      	mov r1,r0
8e0017b0:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0017b4:	443a      	sub r2,r1,r0
8e0017b6:	f910      	bne 8e0017a8 <bjk_wait_sync+0x90>
8e0017b8:	0192      	gie
8e0017ba:	01b2      	idle
8e0017bc:	0392      	gid
8e0017be:	1dac 0500 	ldrh r0,[fp,-0x3]
8e0017c2:	050f 0402 	movts imask,r0
8e0017c6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017ca:	2003      	mov r1,0x0
8e0017cc:	2394      	strb r1,[r0,0x7]
8e0017ce:	01a2      	nop
8e0017d0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017d4:	0384      	ldrb r0,[r0,0x7]
8e0017d6:	2033      	sub r1,r0,0
8e0017d8:	fc10      	bne 8e0017d0 <bjk_wait_sync+0xb8>
8e0017da:	0192      	gie
8e0017dc:	02e0      	b 8e0017e0 <bjk_wait_sync+0xc8>
8e0017de:	01a2      	nop
8e0017e0:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0017e4:	b41b 2404 	add sp,sp,32
8e0017e8:	194f 0402 	rts

8e0017ec <get_add_simm11>:
8e0017ec:	f75c 2700 	str fp,[sp],-0x6
8e0017f0:	f4ef 2402 	mov fp,sp
8e0017f4:	1ddc 0400 	str r0,[fp,+0x3]
8e0017f8:	0003      	mov r0,0x0
8e0017fa:	1dbc 0401 	strh r0,[fp,+0xb]
8e0017fe:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001802:	0113      	add r0,r0,2
8e001804:	0024      	ldrh r0,[r0]
8e001806:	20e2      	mov r1,r0
8e001808:	1fe3      	mov r0,0xff
8e00180a:	045a      	and r0,r1,r0
8e00180c:	0076      	lsl r0,r0,0x3
8e00180e:	20e2      	mov r1,r0
8e001810:	200b 1002 	movt r1,0x0
8e001814:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001818:	0024      	ldrh r0,[r0]
8e00181a:	40e2      	mov r2,r0
8e00181c:	100b 0032 	mov r0,0x380
8e001820:	085a      	and r0,r2,r0
8e001822:	00ee      	asr r0,r0,0x7
8e001824:	000b 1002 	movt r0,0x0
8e001828:	047a      	orr r0,r1,r0
8e00182a:	000b 1002 	movt r0,0x0
8e00182e:	1dbc 0401 	strh r0,[fp,+0xb]
8e001832:	1f1b 0402 	add r0,fp,22
8e001836:	0093      	add r0,r0,1
8e001838:	0004      	ldrb r0,[r0]
8e00183a:	0046      	lsr r0,r0,0x2
8e00183c:	0316      	lsl r0,r0,0x18
8e00183e:	0306      	lsr r0,r0,0x18
8e001840:	20e2      	mov r1,r0
8e001842:	0023      	mov r0,0x1
8e001844:	045a      	and r0,r1,r0
8e001846:	2033      	sub r1,r0,0
8e001848:	1000      	beq 8e001868 <get_add_simm11+0x7c>
8e00184a:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00184e:	20e2      	mov r1,r0
8e001850:	200b 1002 	movt r1,0x0
8e001854:	000b 0f82 	mov r0,0xf800
8e001858:	1feb 1ff2 	movt r0,0xffff
8e00185c:	040a      	eor r0,r1,r0
8e00185e:	000b 1002 	movt r0,0x0
8e001862:	000b 1002 	movt r0,0x0
8e001866:	03e0      	b 8e00186c <get_add_simm11+0x80>
8e001868:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00186c:	1dbc 0401 	strh r0,[fp,+0xb]
8e001870:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001874:	0216      	lsl r0,r0,0x10
8e001876:	020e      	asr r0,r0,0x10
8e001878:	f74c 2400 	ldr fp,[sp,+0x6]
8e00187c:	b41b 2403 	add sp,sp,24
8e001880:	194f 0402 	rts

8e001884 <get_call_opcode>:
8e001884:	f65c 2700 	str fp,[sp],-0x4
8e001888:	f4ef 2402 	mov fp,sp
8e00188c:	1ddc 0400 	str r0,[fp,+0x3]
8e001890:	04e2      	mov r0,r1
8e001892:	1e3c 0400 	strh r0,[fp,+0x4]
8e001896:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00189a:	2f8b 0d42 	mov r1,0xd47c
8e00189e:	3feb 1ff2 	movt r1,0xffff
8e0018a2:	2034      	strh r1,[r0]
8e0018a4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018a8:	0113      	add r0,r0,2
8e0018aa:	200b 0272 	mov r1,0x2700
8e0018ae:	2034      	strh r1,[r0]
8e0018b0:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018b4:	0024      	ldrh r0,[r0]
8e0018b6:	20e2      	mov r1,r0
8e0018b8:	200b 1002 	movt r1,0x0
8e0018bc:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0018c0:	40e2      	mov r2,r0
8e0018c2:	00e3      	mov r0,0x7
8e0018c4:	085a      	and r0,r2,r0
8e0018c6:	00f6      	lsl r0,r0,0x7
8e0018c8:	000b 1002 	movt r0,0x0
8e0018cc:	047a      	orr r0,r1,r0
8e0018ce:	000b 1002 	movt r0,0x0
8e0018d2:	20e2      	mov r1,r0
8e0018d4:	200b 1002 	movt r1,0x0
8e0018d8:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018dc:	2034      	strh r1,[r0]
8e0018de:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018e2:	2113      	add r1,r0,2
8e0018e4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018e8:	0113      	add r0,r0,2
8e0018ea:	0024      	ldrh r0,[r0]
8e0018ec:	40e2      	mov r2,r0
8e0018ee:	400b 1002 	movt r2,0x0
8e0018f2:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0018f6:	0216      	lsl r0,r0,0x10
8e0018f8:	020e      	asr r0,r0,0x10
8e0018fa:	006e      	asr r0,r0,0x3
8e0018fc:	000b 1002 	movt r0,0x0
8e001900:	087a      	orr r0,r2,r0
8e001902:	000b 1002 	movt r0,0x0
8e001906:	000b 1002 	movt r0,0x0
8e00190a:	0434      	strh r0,[r1]
8e00190c:	01a2      	nop
8e00190e:	f64c 2400 	ldr fp,[sp,+0x4]
8e001912:	b41b 2402 	add sp,sp,16
8e001916:	194f 0402 	rts
8e00191a:	01a2      	nop

8e00191c <find_call>:
8e00191c:	f75c 2700 	str fp,[sp],-0x6
8e001920:	f4ef 2402 	mov fp,sp
8e001924:	1ddc 0400 	str r0,[fp,+0x3]
8e001928:	3d5c 0400 	str r1,[fp,+0x2]
8e00192c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001930:	1edc 0400 	str r0,[fp,+0x5]
8e001934:	108b 0032 	mov r0,0x384
8e001938:	000b 1002 	movt r0,0x0
8e00193c:	0044      	ldr r0,[r0]
8e00193e:	001b 0037 	add r0,r0,440
8e001942:	1e5c 0400 	str r0,[fp,+0x4]
8e001946:	1e4c 0400 	ldr r0,[fp,+0x4]
8e00194a:	2003      	mov r1,0x0
8e00194c:	2034      	strh r1,[r0]
8e00194e:	35e0      	b 8e0019b8 <find_call+0x9c>
8e001950:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001954:	2024      	ldrh r1,[r0]
8e001956:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00195a:	0024      	ldrh r0,[r0]
8e00195c:	443a      	sub r2,r1,r0
8e00195e:	1110      	bne 8e001980 <find_call+0x64>
8e001960:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001964:	0113      	add r0,r0,2
8e001966:	2024      	ldrh r1,[r0]
8e001968:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00196c:	0113      	add r0,r0,2
8e00196e:	0024      	ldrh r0,[r0]
8e001970:	443a      	sub r2,r1,r0
8e001972:	0710      	bne 8e001980 <find_call+0x64>
8e001974:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001978:	3dcb 01e2 	mov r1,0x1eee
8e00197c:	2034      	strh r1,[r0]
8e00197e:	21e0      	b 8e0019c0 <find_call+0xa4>
8e001980:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001984:	2024      	ldrh r1,[r0]
8e001986:	09eb 0192 	mov r0,0x194f
8e00198a:	443a      	sub r2,r1,r0
8e00198c:	1110      	bne 8e0019ae <find_call+0x92>
8e00198e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001992:	0113      	add r0,r0,2
8e001994:	2024      	ldrh r1,[r0]
8e001996:	004b 0042 	mov r0,0x402
8e00199a:	443a      	sub r2,r1,r0
8e00199c:	0910      	bne 8e0019ae <find_call+0x92>
8e00199e:	1e4c 0400 	ldr r0,[fp,+0x4]
8e0019a2:	2223      	mov r1,0x11
8e0019a4:	2034      	strh r1,[r0]
8e0019a6:	0003      	mov r0,0x0
8e0019a8:	1edc 0400 	str r0,[fp,+0x5]
8e0019ac:	0ae0      	b 8e0019c0 <find_call+0xa4>
8e0019ae:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019b2:	0313      	add r0,r0,-2
8e0019b4:	1edc 0400 	str r0,[fp,+0x5]
8e0019b8:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019bc:	2033      	sub r1,r0,0
8e0019be:	c910      	bne 8e001950 <find_call+0x34>
8e0019c0:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019c4:	f74c 2400 	ldr fp,[sp,+0x6]
8e0019c8:	b41b 2403 	add sp,sp,24
8e0019cc:	194f 0402 	rts

8e0019d0 <find_interrupt_call>:
8e0019d0:	f75c 2700 	str fp,[sp],-0x6
8e0019d4:	f4ef 2402 	mov fp,sp
8e0019d8:	1ddc 0400 	str r0,[fp,+0x3]
8e0019dc:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0019e0:	1edc 0400 	str r0,[fp,+0x5]
8e0019e4:	108b 0032 	mov r0,0x384
8e0019e8:	000b 1002 	movt r0,0x0
8e0019ec:	0044      	ldr r0,[r0]
8e0019ee:	001b 0037 	add r0,r0,440
8e0019f2:	1e5c 0400 	str r0,[fp,+0x4]
8e0019f6:	1e4c 0400 	ldr r0,[fp,+0x4]
8e0019fa:	2003      	mov r1,0x0
8e0019fc:	2034      	strh r1,[r0]
8e0019fe:	4de0      	b 8e001a98 <find_interrupt_call+0xc8>
8e001a00:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a04:	2024      	ldrh r1,[r0]
8e001a06:	1f8b 0142 	mov r0,0x14fc
8e001a0a:	443a      	sub r2,r1,r0
8e001a0c:	2a10      	bne 8e001a60 <find_interrupt_call+0x90>
8e001a0e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a12:	0113      	add r0,r0,2
8e001a14:	2024      	ldrh r1,[r0]
8e001a16:	000b 0052 	mov r0,0x500
8e001a1a:	443a      	sub r2,r1,r0
8e001a1c:	2210      	bne 8e001a60 <find_interrupt_call+0x90>
8e001a1e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a22:	021b 0000 	add r0,r0,4
8e001a26:	2024      	ldrh r1,[r0]
8e001a28:	024b 0052 	mov r0,0x512
8e001a2c:	443a      	sub r2,r1,r0
8e001a2e:	1910      	bne 8e001a60 <find_interrupt_call+0x90>
8e001a30:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a34:	031b 0000 	add r0,r0,6
8e001a38:	2024      	ldrh r1,[r0]
8e001a3a:	03eb 0212 	mov r0,0x211f
8e001a3e:	443a      	sub r2,r1,r0
8e001a40:	1010      	bne 8e001a60 <find_interrupt_call+0x90>
8e001a42:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a46:	001b 0001 	add r0,r0,8
8e001a4a:	2024      	ldrh r1,[r0]
8e001a4c:	004b 0042 	mov r0,0x402
8e001a50:	443a      	sub r2,r1,r0
8e001a52:	0710      	bne 8e001a60 <find_interrupt_call+0x90>
8e001a54:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001a58:	3dcb 02e2 	mov r1,0x2eee
8e001a5c:	2034      	strh r1,[r0]
8e001a5e:	21e0      	b 8e001aa0 <find_interrupt_call+0xd0>
8e001a60:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a64:	2024      	ldrh r1,[r0]
8e001a66:	09eb 0192 	mov r0,0x194f
8e001a6a:	443a      	sub r2,r1,r0
8e001a6c:	1110      	bne 8e001a8e <find_interrupt_call+0xbe>
8e001a6e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a72:	0113      	add r0,r0,2
8e001a74:	2024      	ldrh r1,[r0]
8e001a76:	004b 0042 	mov r0,0x402
8e001a7a:	443a      	sub r2,r1,r0
8e001a7c:	0910      	bne 8e001a8e <find_interrupt_call+0xbe>
8e001a7e:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001a82:	2423      	mov r1,0x21
8e001a84:	2034      	strh r1,[r0]
8e001a86:	0003      	mov r0,0x0
8e001a88:	1edc 0400 	str r0,[fp,+0x5]
8e001a8c:	0ae0      	b 8e001aa0 <find_interrupt_call+0xd0>
8e001a8e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a92:	0313      	add r0,r0,-2
8e001a94:	1edc 0400 	str r0,[fp,+0x5]
8e001a98:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a9c:	2033      	sub r1,r0,0
8e001a9e:	b110      	bne 8e001a00 <find_interrupt_call+0x30>
8e001aa0:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001aa4:	f74c 2400 	ldr fp,[sp,+0x6]
8e001aa8:	b41b 2403 	add sp,sp,24
8e001aac:	194f 0402 	rts

8e001ab0 <find_rts>:
8e001ab0:	f45c 2701 	str fp,[sp],-0x8
8e001ab4:	f4ef 2402 	mov fp,sp
8e001ab8:	1ddc 0400 	str r0,[fp,+0x3]
8e001abc:	3dcc 0400 	ldr r1,[fp,+0x3]
8e001ac0:	000b 0802 	mov r0,0x8000
8e001ac4:	041a      	add r0,r1,r0
8e001ac6:	1f5c 0400 	str r0,[fp,+0x6]
8e001aca:	108b 0032 	mov r0,0x384
8e001ace:	000b 1002 	movt r0,0x0
8e001ad2:	0044      	ldr r0,[r0]
8e001ad4:	001b 0037 	add r0,r0,440
8e001ad8:	1edc 0400 	str r0,[fp,+0x5]
8e001adc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001ae0:	2003      	mov r1,0x0
8e001ae2:	2034      	strh r1,[r0]
8e001ae4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001ae8:	1fdc 0400 	str r0,[fp,+0x7]
8e001aec:	45e0      	b 8e001b76 <find_rts+0xc6>
8e001aee:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001af2:	2024      	ldrh r1,[r0]
8e001af4:	09eb 0192 	mov r0,0x194f
8e001af8:	443a      	sub r2,r1,r0
8e001afa:	0f10      	bne 8e001b18 <find_rts+0x68>
8e001afc:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b00:	0113      	add r0,r0,2
8e001b02:	2024      	ldrh r1,[r0]
8e001b04:	004b 0042 	mov r0,0x402
8e001b08:	443a      	sub r2,r1,r0
8e001b0a:	0710      	bne 8e001b18 <find_rts+0x68>
8e001b0c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b10:	3dcb 04e2 	mov r1,0x4eee
8e001b14:	2034      	strh r1,[r0]
8e001b16:	36e0      	b 8e001b82 <find_rts+0xd2>
8e001b18:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b1c:	0024      	ldrh r0,[r0]
8e001b1e:	213b 003a 	sub r1,r0,466
8e001b22:	2510      	bne 8e001b6c <find_rts+0xbc>
8e001b24:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b28:	031b 00fe 	add r0,r0,-10
8e001b2c:	2024      	ldrh r1,[r0]
8e001b2e:	004b 0052 	mov r0,0x502
8e001b32:	443a      	sub r2,r1,r0
8e001b34:	1c10      	bne 8e001b6c <find_rts+0xbc>
8e001b36:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b3a:	001b 00ff 	add r0,r0,-8
8e001b3e:	2024      	ldrh r1,[r0]
8e001b40:	01eb 0212 	mov r0,0x210f
8e001b44:	443a      	sub r2,r1,r0
8e001b46:	1310      	bne 8e001b6c <find_rts+0xbc>
8e001b48:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b4c:	011b 00ff 	add r0,r0,-6
8e001b50:	2024      	ldrh r1,[r0]
8e001b52:	004b 0042 	mov r0,0x402
8e001b56:	443a      	sub r2,r1,r0
8e001b58:	0a10      	bne 8e001b6c <find_rts+0xbc>
8e001b5a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b5e:	2823      	mov r1,0x41
8e001b60:	2034      	strh r1,[r0]
8e001b62:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001b66:	1fdc 0400 	str r0,[fp,+0x7]
8e001b6a:	0ce0      	b 8e001b82 <find_rts+0xd2>
8e001b6c:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b70:	0113      	add r0,r0,2
8e001b72:	1fdc 0400 	str r0,[fp,+0x7]
8e001b76:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b7a:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001b7e:	443a      	sub r2,r1,r0
8e001b80:	b750      	bltu 8e001aee <find_rts+0x3e>
8e001b82:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b86:	0024      	ldrh r0,[r0]
8e001b88:	20bb 0008 	sub r1,r0,65
8e001b8c:	0310      	bne 8e001b92 <find_rts+0xe2>
8e001b8e:	0003      	mov r0,0x0
8e001b90:	1de0      	b 8e001bca <find_rts+0x11a>
8e001b92:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b96:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001b9a:	443a      	sub r2,r1,r0
8e001b9c:	0710      	bne 8e001baa <find_rts+0xfa>
8e001b9e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001ba2:	2843      	mov r1,0x42
8e001ba4:	2034      	strh r1,[r0]
8e001ba6:	0003      	mov r0,0x0
8e001ba8:	11e0      	b 8e001bca <find_rts+0x11a>
8e001baa:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001bae:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001bb2:	043a      	sub r0,r1,r0
8e001bb4:	002e      	asr r0,r0,0x1
8e001bb6:	20b3      	sub r1,r0,1
8e001bb8:	0720      	bgtu 8e001bc6 <find_rts+0x116>
8e001bba:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001bbe:	2863      	mov r1,0x43
8e001bc0:	2034      	strh r1,[r0]
8e001bc2:	0003      	mov r0,0x0
8e001bc4:	03e0      	b 8e001bca <find_rts+0x11a>
8e001bc6:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001bca:	f44c 2401 	ldr fp,[sp,+0x8]
8e001bce:	b41b 2404 	add sp,sp,32
8e001bd2:	194f 0402 	rts
8e001bd6:	01a2      	nop

8e001bd8 <get_sp_disp>:
8e001bd8:	f65c 2701 	str fp,[sp],-0xc
8e001bdc:	f4ef 2402 	mov fp,sp
8e001be0:	1ddc 0400 	str r0,[fp,+0x3]
8e001be4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001be8:	1ddc 0401 	str r0,[fp,+0xb]
8e001bec:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001bf0:	0213      	add r0,r0,-4
8e001bf2:	1ddc 0401 	str r0,[fp,+0xb]
8e001bf6:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001bfa:	0024      	ldrh r0,[r0]
8e001bfc:	1ebc 0402 	strh r0,[fp,+0x15]
8e001c00:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c04:	00a4      	ldrh r0,[r0,0x1]
8e001c06:	1e3c 0402 	strh r0,[fp,+0x14]
8e001c0a:	108b 0032 	mov r0,0x384
8e001c0e:	000b 1002 	movt r0,0x0
8e001c12:	0044      	ldr r0,[r0]
8e001c14:	001b 0037 	add r0,r0,440
8e001c18:	1cdc 0401 	str r0,[fp,+0x9]
8e001c1c:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c20:	2003      	mov r1,0x0
8e001c22:	2034      	strh r1,[r0]
8e001c24:	3eac 0402 	ldrh r1,[fp,+0x15]
8e001c28:	01eb 0f02 	mov r0,0xf00f
8e001c2c:	245a      	and r1,r1,r0
8e001c2e:	016b 0b02 	mov r0,0xb00b
8e001c32:	443a      	sub r2,r1,r0
8e001c34:	0800      	beq 8e001c44 <get_sp_disp+0x6c>
8e001c36:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c3a:	2623      	mov r1,0x31
8e001c3c:	2034      	strh r1,[r0]
8e001c3e:	0003      	mov r0,0x0
8e001c40:	8fe8 0000 	b 8e001d5e <get_sp_disp+0x186>
8e001c44:	3e2c 0402 	ldrh r1,[fp,+0x14]
8e001c48:	000b 0ff2 	mov r0,0xff00
8e001c4c:	245a      	and r1,r1,r0
8e001c4e:	000b 0242 	mov r0,0x2400
8e001c52:	443a      	sub r2,r1,r0
8e001c54:	0700      	beq 8e001c62 <get_sp_disp+0x8a>
8e001c56:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c5a:	2643      	mov r1,0x32
8e001c5c:	2034      	strh r1,[r0]
8e001c5e:	0003      	mov r0,0x0
8e001c60:	7fe0      	b 8e001d5e <get_sp_disp+0x186>
8e001c62:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c66:	1c5c 0401 	str r0,[fp,+0x8]
8e001c6a:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c6e:	0213      	add r0,r0,-4
8e001c70:	1ddc 0401 	str r0,[fp,+0xb]
8e001c74:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c78:	0024      	ldrh r0,[r0]
8e001c7a:	1ebc 0402 	strh r0,[fp,+0x15]
8e001c7e:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c82:	00a4      	ldrh r0,[r0,0x1]
8e001c84:	1e3c 0402 	strh r0,[fp,+0x14]
8e001c88:	3eac 0402 	ldrh r1,[fp,+0x15]
8e001c8c:	01eb 0f02 	mov r0,0xf00f
8e001c90:	245a      	and r1,r1,r0
8e001c92:	018b 0d02 	mov r0,0xd00c
8e001c96:	443a      	sub r2,r1,r0
8e001c98:	0700      	beq 8e001ca6 <get_sp_disp+0xce>
8e001c9a:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c9e:	2663      	mov r1,0x33
8e001ca0:	2034      	strh r1,[r0]
8e001ca2:	0003      	mov r0,0x0
8e001ca4:	5de0      	b 8e001d5e <get_sp_disp+0x186>
8e001ca6:	3e2c 0402 	ldrh r1,[fp,+0x14]
8e001caa:	000b 0f02 	mov r0,0xf000
8e001cae:	245a      	and r1,r1,r0
8e001cb0:	000b 0202 	mov r0,0x2000
8e001cb4:	443a      	sub r2,r1,r0
8e001cb6:	0700      	beq 8e001cc4 <get_sp_disp+0xec>
8e001cb8:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001cbc:	2683      	mov r1,0x34
8e001cbe:	2034      	strh r1,[r0]
8e001cc0:	0003      	mov r0,0x0
8e001cc2:	4ee0      	b 8e001d5e <get_sp_disp+0x186>
8e001cc4:	1c4c 0401 	ldr r0,[fp,+0x8]
8e001cc8:	1f5c 0400 	str r0,[fp,+0x6]
8e001ccc:	0003      	mov r0,0x0
8e001cce:	1dbc 0401 	strh r0,[fp,+0xb]
8e001cd2:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001cd6:	0113      	add r0,r0,2
8e001cd8:	0024      	ldrh r0,[r0]
8e001cda:	20e2      	mov r1,r0
8e001cdc:	1fe3      	mov r0,0xff
8e001cde:	045a      	and r0,r1,r0
8e001ce0:	0076      	lsl r0,r0,0x3
8e001ce2:	20e2      	mov r1,r0
8e001ce4:	200b 1002 	movt r1,0x0
8e001ce8:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001cec:	0024      	ldrh r0,[r0]
8e001cee:	40e2      	mov r2,r0
8e001cf0:	100b 0032 	mov r0,0x380
8e001cf4:	085a      	and r0,r2,r0
8e001cf6:	00ee      	asr r0,r0,0x7
8e001cf8:	000b 1002 	movt r0,0x0
8e001cfc:	047a      	orr r0,r1,r0
8e001cfe:	000b 1002 	movt r0,0x0
8e001d02:	1dbc 0401 	strh r0,[fp,+0xb]
8e001d06:	1f1b 0402 	add r0,fp,22
8e001d0a:	0093      	add r0,r0,1
8e001d0c:	0004      	ldrb r0,[r0]
8e001d0e:	0046      	lsr r0,r0,0x2
8e001d10:	0316      	lsl r0,r0,0x18
8e001d12:	0306      	lsr r0,r0,0x18
8e001d14:	20e2      	mov r1,r0
8e001d16:	0023      	mov r0,0x1
8e001d18:	045a      	and r0,r1,r0
8e001d1a:	2033      	sub r1,r0,0
8e001d1c:	1000      	beq 8e001d3c <get_sp_disp+0x164>
8e001d1e:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001d22:	20e2      	mov r1,r0
8e001d24:	200b 1002 	movt r1,0x0
8e001d28:	000b 0f82 	mov r0,0xf800
8e001d2c:	1feb 1ff2 	movt r0,0xffff
8e001d30:	040a      	eor r0,r1,r0
8e001d32:	000b 1002 	movt r0,0x0
8e001d36:	000b 1002 	movt r0,0x0
8e001d3a:	03e0      	b 8e001d40 <get_sp_disp+0x168>
8e001d3c:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001d40:	1dbc 0401 	strh r0,[fp,+0xb]
8e001d44:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001d48:	000b 1002 	movt r0,0x0
8e001d4c:	1fbc 0401 	strh r0,[fp,+0xf]
8e001d50:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001d54:	3dcb 03e2 	mov r1,0x3eee
8e001d58:	2034      	strh r1,[r0]
8e001d5a:	1fac 0401 	ldrh r0,[fp,+0xf]
8e001d5e:	0216      	lsl r0,r0,0x10
8e001d60:	020e      	asr r0,r0,0x10
8e001d62:	f64c 2401 	ldr fp,[sp,+0xc]
8e001d66:	b41b 2406 	add sp,sp,48
8e001d6a:	194f 0402 	rts
8e001d6e:	01a2      	nop

8e001d70 <umm_info>:
8e001d70:	d6fc 2700 	strd lr,[sp],-0x5
8e001d74:	f41b 2405 	add fp,sp,40
8e001d78:	1edc 0500 	str r0,[fp,-0x5]
8e001d7c:	3f5c 0500 	str r1,[fp,-0x6]
8e001d80:	5fdc 0500 	str r2,[fp,-0x7]
8e001d84:	0003      	mov r0,0x0
8e001d86:	1cbc 0500 	strh r0,[fp,-0x1]
8e001d8a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001d8e:	1d5c 0500 	str r0,[fp,-0x2]
8e001d92:	0003      	mov r0,0x0
8e001d94:	1c9c 0501 	strb r0,[fp,-0x9]
8e001d98:	0203      	mov r0,0x10
8e001d9a:	1e5c 0500 	str r0,[fp,-0x4]
8e001d9e:	1c8c 0501 	ldrb r0,[fp,-0x9]
8e001da2:	5e4c 0500 	ldr r2,[fp,-0x4]
8e001da6:	20e2      	mov r1,r0
8e001da8:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001dac:	6b8b 0032 	mov r3,0x35c
8e001db0:	600b 18e2 	movt r3,0x8e00
8e001db4:	0d52      	jalr r3
8e001db6:	070b 0032 	mov r0,0x338
8e001dba:	000b 1002 	movt r0,0x0
8e001dbe:	2044      	ldr r1,[r0]
8e001dc0:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001dc4:	0076      	lsl r0,r0,0x3
8e001dc6:	041a      	add r0,r1,r0
8e001dc8:	2004      	ldrb r1,[r0]
8e001dca:	0084      	ldrb r0,[r0,0x1]
8e001dcc:	0116      	lsl r0,r0,0x8
8e001dce:	00fa      	orr r0,r0,r1
8e001dd0:	20e2      	mov r1,r0
8e001dd2:	200b 1002 	movt r1,0x0
8e001dd6:	1feb 07f2 	mov r0,0x7fff
8e001dda:	045a      	and r0,r1,r0
8e001ddc:	1cbc 0500 	strh r0,[fp,-0x1]
8e001de0:	cae8 0000 	b 8e001f74 <umm_info+0x204>
8e001de4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001de8:	0024      	ldrh r0,[r0]
8e001dea:	0093      	add r0,r0,1
8e001dec:	20e2      	mov r1,r0
8e001dee:	200b 1002 	movt r1,0x0
8e001df2:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001df6:	2034      	strh r1,[r0]
8e001df8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001dfc:	21a4      	ldrh r1,[r0,0x3]
8e001dfe:	070b 0032 	mov r0,0x338
8e001e02:	000b 1002 	movt r0,0x0
8e001e06:	4044      	ldr r2,[r0]
8e001e08:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e0c:	0076      	lsl r0,r0,0x3
8e001e0e:	081a      	add r0,r2,r0
8e001e10:	4004      	ldrb r2,[r0]
8e001e12:	0084      	ldrb r0,[r0,0x1]
8e001e14:	0116      	lsl r0,r0,0x8
8e001e16:	017a      	orr r0,r0,r2
8e001e18:	40e2      	mov r2,r0
8e001e1a:	400b 1002 	movt r2,0x0
8e001e1e:	1feb 07f2 	mov r0,0x7fff
8e001e22:	085a      	and r0,r2,r0
8e001e24:	40e2      	mov r2,r0
8e001e26:	400b 1002 	movt r2,0x0
8e001e2a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e2e:	083a      	sub r0,r2,r0
8e001e30:	000b 1002 	movt r0,0x0
8e001e34:	041a      	add r0,r1,r0
8e001e36:	20e2      	mov r1,r0
8e001e38:	200b 1002 	movt r1,0x0
8e001e3c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e40:	21b4      	strh r1,[r0,0x3]
8e001e42:	070b 0032 	mov r0,0x338
8e001e46:	000b 1002 	movt r0,0x0
8e001e4a:	2044      	ldr r1,[r0]
8e001e4c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e50:	0076      	lsl r0,r0,0x3
8e001e52:	041a      	add r0,r1,r0
8e001e54:	2004      	ldrb r1,[r0]
8e001e56:	0084      	ldrb r0,[r0,0x1]
8e001e58:	0116      	lsl r0,r0,0x8
8e001e5a:	00fa      	orr r0,r0,r1
8e001e5c:	000b 1002 	movt r0,0x0
8e001e60:	000b 1002 	movt r0,0x0
8e001e64:	0216      	lsl r0,r0,0x10
8e001e66:	020e      	asr r0,r0,0x10
8e001e68:	2033      	sub r1,r0,0
8e001e6a:	4170      	bgte 8e001eec <umm_info+0x17c>
8e001e6c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e70:	0124      	ldrh r0,[r0,0x2]
8e001e72:	0093      	add r0,r0,1
8e001e74:	20e2      	mov r1,r0
8e001e76:	200b 1002 	movt r1,0x0
8e001e7a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e7e:	2134      	strh r1,[r0,0x2]
8e001e80:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e84:	22a4      	ldrh r1,[r0,0x5]
8e001e86:	070b 0032 	mov r0,0x338
8e001e8a:	000b 1002 	movt r0,0x0
8e001e8e:	4044      	ldr r2,[r0]
8e001e90:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e94:	0076      	lsl r0,r0,0x3
8e001e96:	081a      	add r0,r2,r0
8e001e98:	4004      	ldrb r2,[r0]
8e001e9a:	0084      	ldrb r0,[r0,0x1]
8e001e9c:	0116      	lsl r0,r0,0x8
8e001e9e:	017a      	orr r0,r0,r2
8e001ea0:	40e2      	mov r2,r0
8e001ea2:	400b 1002 	movt r2,0x0
8e001ea6:	1feb 07f2 	mov r0,0x7fff
8e001eaa:	085a      	and r0,r2,r0
8e001eac:	40e2      	mov r2,r0
8e001eae:	400b 1002 	movt r2,0x0
8e001eb2:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001eb6:	083a      	sub r0,r2,r0
8e001eb8:	000b 1002 	movt r0,0x0
8e001ebc:	041a      	add r0,r1,r0
8e001ebe:	20e2      	mov r1,r0
8e001ec0:	200b 1002 	movt r1,0x0
8e001ec4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ec8:	22b4      	strh r1,[r0,0x5]
8e001eca:	070b 0032 	mov r0,0x338
8e001ece:	000b 1002 	movt r0,0x0
8e001ed2:	2044      	ldr r1,[r0]
8e001ed4:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001ed8:	0076      	lsl r0,r0,0x3
8e001eda:	241a      	add r1,r1,r0
8e001edc:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001ee0:	443a      	sub r2,r1,r0
8e001ee2:	3410      	bne 8e001f4a <umm_info+0x1da>
8e001ee4:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001ee8:	8be8 0000 	b 8e001ffe <umm_info+0x28e>
8e001eec:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ef0:	00a4      	ldrh r0,[r0,0x1]
8e001ef2:	0093      	add r0,r0,1
8e001ef4:	20e2      	mov r1,r0
8e001ef6:	200b 1002 	movt r1,0x0
8e001efa:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001efe:	20b4      	strh r1,[r0,0x1]
8e001f00:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f04:	2224      	ldrh r1,[r0,0x4]
8e001f06:	070b 0032 	mov r0,0x338
8e001f0a:	000b 1002 	movt r0,0x0
8e001f0e:	4044      	ldr r2,[r0]
8e001f10:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f14:	0076      	lsl r0,r0,0x3
8e001f16:	081a      	add r0,r2,r0
8e001f18:	4004      	ldrb r2,[r0]
8e001f1a:	0084      	ldrb r0,[r0,0x1]
8e001f1c:	0116      	lsl r0,r0,0x8
8e001f1e:	017a      	orr r0,r0,r2
8e001f20:	40e2      	mov r2,r0
8e001f22:	400b 1002 	movt r2,0x0
8e001f26:	1feb 07f2 	mov r0,0x7fff
8e001f2a:	085a      	and r0,r2,r0
8e001f2c:	40e2      	mov r2,r0
8e001f2e:	400b 1002 	movt r2,0x0
8e001f32:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f36:	083a      	sub r0,r2,r0
8e001f38:	000b 1002 	movt r0,0x0
8e001f3c:	041a      	add r0,r1,r0
8e001f3e:	20e2      	mov r1,r0
8e001f40:	200b 1002 	movt r1,0x0
8e001f44:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f48:	2234      	strh r1,[r0,0x4]
8e001f4a:	070b 0032 	mov r0,0x338
8e001f4e:	000b 1002 	movt r0,0x0
8e001f52:	2044      	ldr r1,[r0]
8e001f54:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f58:	0076      	lsl r0,r0,0x3
8e001f5a:	041a      	add r0,r1,r0
8e001f5c:	2004      	ldrb r1,[r0]
8e001f5e:	0084      	ldrb r0,[r0,0x1]
8e001f60:	0116      	lsl r0,r0,0x8
8e001f62:	00fa      	orr r0,r0,r1
8e001f64:	20e2      	mov r1,r0
8e001f66:	200b 1002 	movt r1,0x0
8e001f6a:	1feb 07f2 	mov r0,0x7fff
8e001f6e:	045a      	and r0,r1,r0
8e001f70:	1cbc 0500 	strh r0,[fp,-0x1]
8e001f74:	070b 0032 	mov r0,0x338
8e001f78:	000b 1002 	movt r0,0x0
8e001f7c:	2044      	ldr r1,[r0]
8e001f7e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f82:	0076      	lsl r0,r0,0x3
8e001f84:	041a      	add r0,r1,r0
8e001f86:	2004      	ldrb r1,[r0]
8e001f88:	0084      	ldrb r0,[r0,0x1]
8e001f8a:	0116      	lsl r0,r0,0x8
8e001f8c:	00fa      	orr r0,r0,r1
8e001f8e:	000b 1002 	movt r0,0x0
8e001f92:	20e2      	mov r1,r0
8e001f94:	1feb 07f2 	mov r0,0x7fff
8e001f98:	045a      	and r0,r1,r0
8e001f9a:	2033      	sub r1,r0,0
8e001f9c:	2418 ffff 	bne 8e001de4 <umm_info+0x74>
8e001fa0:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001fa4:	22a4      	ldrh r1,[r0,0x5]
8e001fa6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001faa:	043a      	sub r0,r1,r0
8e001fac:	20e2      	mov r1,r0
8e001fae:	200b 1002 	movt r1,0x0
8e001fb2:	000b 0302 	mov r0,0x3000
8e001fb6:	000b 1002 	movt r0,0x0
8e001fba:	0066      	lsr r0,r0,0x3
8e001fbc:	000b 1002 	movt r0,0x0
8e001fc0:	041a      	add r0,r1,r0
8e001fc2:	20e2      	mov r1,r0
8e001fc4:	200b 1002 	movt r1,0x0
8e001fc8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001fcc:	22b4      	strh r1,[r0,0x5]
8e001fce:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001fd2:	21a4      	ldrh r1,[r0,0x3]
8e001fd4:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001fd8:	043a      	sub r0,r1,r0
8e001fda:	20e2      	mov r1,r0
8e001fdc:	200b 1002 	movt r1,0x0
8e001fe0:	000b 0302 	mov r0,0x3000
8e001fe4:	000b 1002 	movt r0,0x0
8e001fe8:	0066      	lsr r0,r0,0x3
8e001fea:	000b 1002 	movt r0,0x0
8e001fee:	041a      	add r0,r1,r0
8e001ff0:	20e2      	mov r1,r0
8e001ff2:	200b 1002 	movt r1,0x0
8e001ff6:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ffa:	21b4      	strh r1,[r0,0x3]
8e001ffc:	0003      	mov r0,0x0
8e001ffe:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e002002:	b41b 2405 	add sp,sp,40
8e002006:	194f 0402 	rts
8e00200a:	01a2      	nop

8e00200c <umm_malloc>:
8e00200c:	967c 0700 	strd r4,[sp],-0x4
8e002010:	d5fc 0400 	strd r6,[sp,+0x3]
8e002014:	157c 2400 	strd r8,[sp,+0x2]
8e002018:	d4fc 2400 	strd lr,[sp,+0x1]
8e00201c:	2033      	sub r1,r0,0
8e00201e:	ac08 0000 	beq 8e002176 <umm_malloc+0x16a>
8e002022:	220b 0242 	mov r1,0x2410
8e002026:	200b 18e2 	movt r1,0x8e00
8e00202a:	0552      	jalr r1
8e00202c:	c70b 0032 	mov r6,0x338
8e002030:	c00b 1002 	movt r6,0x0
8e002034:	984c 2000 	ldr ip,[r6,+0x0]
8e002038:	1feb 47f2 	mov r16,0x7fff
8e00203c:	328c 0400 	ldrb r1,[ip,+0x5]
8e002040:	2516      	lsl r1,r1,0x8
8e002042:	720c 0400 	ldrb r3,[ip,+0x4]
8e002046:	65fa      	orr r3,r1,r3
8e002048:	8ce2      	mov r4,r3
8e00204a:	2003      	mov r1,0x0
8e00204c:	7feb 47f2 	mov r19,0x7fff
8e002050:	5076      	lsl r2,r4,0x3
8e002052:	511f 040a 	add r2,ip,r2
8e002056:	4a8c 4000 	ldrb r18,[r2,+0x5]
8e00205a:	2a0c 4000 	ldrb r17,[r2,+0x4]
8e00205e:	491f 4806 	lsl r18,r18,0x8
8e002062:	28ff 490a 	orr r17,r18,r17
8e002066:	1500      	beq 8e002090 <umm_malloc+0x84>
8e002068:	2804      	ldrb r1,[r2]
8e00206a:	4884      	ldrb r2,[r2,0x1]
8e00206c:	4916      	lsl r2,r2,0x8
8e00206e:	28fa      	orr r1,r2,r1
8e002070:	25df 010a 	and r1,r1,r19
8e002074:	263a      	sub r1,r1,r4
8e002076:	200b 1002 	movt r1,0x0
8e00207a:	40ba      	sub r2,r0,r1
8e00207c:	0720      	bgtu 8e00208a <umm_malloc+0x7e>
8e00207e:	40bf 080a 	sub r2,r16,r1
8e002082:	0440      	blteu 8e00208a <umm_malloc+0x7e>
8e002084:	70e2      	mov r3,r4
8e002086:	04ef 4002 	mov r16,r1
8e00208a:	84ef 0802 	mov r4,r17
8e00208e:	e1e0      	b 8e002050 <umm_malloc+0x44>
8e002090:	5feb 07f2 	mov r2,0x7fff
8e002094:	213f 480a 	sub r17,r16,r2
8e002098:	8c12      	movne r4,r3
8e00209a:	201f 0802 	movne r1,r16
8e00209e:	7076      	lsl r3,r4,0x3
8e0020a0:	719f 040a 	add r3,ip,r3
8e0020a4:	4c84      	ldrb r2,[r3,0x1]
8e0020a6:	0c0c 4000 	ldrb r16,[r3,+0x0]
8e0020aa:	4916      	lsl r2,r2,0x8
8e0020ac:	487f 010a 	orr r2,r2,r16
8e0020b0:	7feb 07f2 	mov r3,0x7fff
8e0020b4:	49da      	and r2,r2,r3
8e0020b6:	1a00      	beq 8e0020ea <umm_malloc+0xde>
8e0020b8:	443a      	sub r2,r1,r0
8e0020ba:	0810      	bne 8e0020ca <umm_malloc+0xbe>
8e0020bc:	388b 0242 	mov r1,0x24c4
8e0020c0:	10e2      	mov r0,r4
8e0020c2:	200b 18e2 	movt r1,0x8e00
8e0020c6:	0552      	jalr r1
8e0020c8:	51e0      	b 8e00216a <umm_malloc+0x15e>
8e0020ca:	a43a      	sub r5,r1,r0
8e0020cc:	a00b 1002 	movt r5,0x0
8e0020d0:	658b 0242 	mov r3,0x242c
8e0020d4:	10e2      	mov r0,r4
8e0020d6:	400b 0802 	mov r2,0x8000
8e0020da:	34e2      	mov r1,r5
8e0020dc:	600b 18e2 	movt r3,0x8e00
8e0020e0:	929a      	add r4,r4,r5
8e0020e2:	0d52      	jalr r3
8e0020e4:	800b 1002 	movt r4,0x0
8e0020e8:	41e0      	b 8e00216a <umm_malloc+0x15e>
8e0020ea:	200b 0302 	mov r1,0x3000
8e0020ee:	501a      	add r2,r4,r0
8e0020f0:	200b 1002 	movt r1,0x0
8e0020f4:	4893      	add r2,r2,1
8e0020f6:	2466      	lsr r1,r1,0x3
8e0020f8:	68ba      	sub r3,r2,r1
8e0020fa:	3e30      	bgteu 8e002176 <umm_malloc+0x16a>
8e0020fc:	303b 4000 	sub r17,r4,0
8e002100:	0a10      	bne 8e002114 <umm_malloc+0x108>
8e002102:	4023      	mov r2,0x1
8e002104:	909c 0400 	strb r4,[ip,+0x1]
8e002108:	501c 0400 	strb r2,[ip]
8e00210c:	3844      	ldr r1,[r6]
8e00210e:	8694      	strb r4,[r1,0x5]
8e002110:	8023      	mov r4,0x1
8e002112:	4614      	strb r2,[r1,0x4]
8e002114:	7844      	ldr r3,[r6]
8e002116:	f076      	lsl r7,r4,0x3
8e002118:	2f9a      	add r1,r3,r7
8e00211a:	4784      	ldrb r2,[r1,0x7]
8e00211c:	b01a      	add r5,r4,r0
8e00211e:	4916      	lsl r2,r2,0x8
8e002120:	0704      	ldrb r0,[r1,0x6]
8e002122:	14ef 2002 	mov r8,r5
8e002126:	487a      	orr r2,r2,r0
8e002128:	000b 3002 	movt r8,0x0
8e00212c:	b476      	lsl r5,r5,0x3
8e00212e:	4876      	lsl r2,r2,0x3
8e002130:	3feb 2002 	mov r9,0xff
8e002134:	4d1a      	add r2,r3,r2
8e002136:	20df 248a 	and r9,r8,r9
8e00213a:	0e9a      	add r0,r3,r5
8e00213c:	010f 2406 	lsr r8,r8,0x8
8e002140:	6e8b 0032 	mov r3,0x374
8e002144:	2a1c 2000 	strb r9,[r2,+0x4]
8e002148:	0a9c 2000 	strb r8,[r2,+0x5]
8e00214c:	600b 18e2 	movt r3,0x8e00
8e002150:	4103      	mov r2,0x8
8e002152:	0d52      	jalr r3
8e002154:	1844      	ldr r0,[r6]
8e002156:	2399 2000 	strb r9,[r0,+r7]
8e00215a:	e39a      	add r7,r0,r7
8e00215c:	1c9c 2000 	strb r8,[r7,+0x1]
8e002160:	1844      	ldr r0,[r6]
8e002162:	a29a      	add r5,r0,r5
8e002164:	1106      	lsr r0,r4,0x8
8e002166:	9514      	strb r4,[r5,0x2]
8e002168:	1594      	strb r0,[r5,0x3]
8e00216a:	1844      	ldr r0,[r6]
8e00216c:	9076      	lsl r4,r4,0x3
8e00216e:	021a      	add r0,r0,r4
8e002170:	021b 0000 	add r0,r0,4
8e002174:	02e0      	b 8e002178 <umm_malloc+0x16c>
8e002176:	0003      	mov r0,0x0
8e002178:	d5ec 0400 	ldrd r6,[sp,+0x3]
8e00217c:	156c 2400 	ldrd r8,[sp,+0x2]
8e002180:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002184:	b41b 2404 	add sp,sp,32
8e002188:	946c 0400 	ldrd r4,[sp,+0x0]
8e00218c:	194f 0402 	rts

8e002190 <umm_realloc>:
8e002190:	96fc 0700 	strd r4,[sp],-0x5
8e002194:	d67c 0400 	strd r6,[sp,+0x4]
8e002198:	15fc 2400 	strd r8,[sp,+0x3]
8e00219c:	557c 2400 	strd r10,[sp,+0x2]
8e0021a0:	d4fc 2400 	strd lr,[sp,+0x1]
8e0021a4:	c05a      	and r6,r0,r0
8e0021a6:	e4e2      	mov r7,r1
8e0021a8:	1310      	bne 8e0021ce <umm_realloc+0x3e>
8e0021aa:	d66c 0400 	ldrd r6,[sp,+0x4]
8e0021ae:	15ec 2400 	ldrd r8,[sp,+0x3]
8e0021b2:	556c 2400 	ldrd r10,[sp,+0x2]
8e0021b6:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0021ba:	b41b 2405 	add sp,sp,40
8e0021be:	04e2      	mov r0,r1
8e0021c0:	946c 0400 	ldrd r4,[sp,+0x0]
8e0021c4:	218b 0202 	mov r1,0x200c
8e0021c8:	200b 18e2 	movt r1,0x8e00
8e0021cc:	0542      	jr r1
8e0021ce:	3c33      	sub r1,r7,0
8e0021d0:	0910      	bne 8e0021e2 <umm_realloc+0x52>
8e0021d2:	298b 0232 	mov r1,0x234c
8e0021d6:	200b 18e2 	movt r1,0x8e00
8e0021da:	0552      	jalr r1
8e0021dc:	0003      	mov r0,0x0
8e0021de:	a9e8 0000 	b 8e002330 <umm_realloc+0x1a0>
8e0021e2:	220b 0242 	mov r1,0x2410
8e0021e6:	200b 18e2 	movt r1,0x8e00
8e0021ea:	1ce2      	mov r0,r7
8e0021ec:	0552      	jalr r1
8e0021ee:	670b 2032 	mov r11,0x338
8e0021f2:	600b 3002 	movt r11,0x0
8e0021f6:	a0e2      	mov r5,r0
8e0021f8:	0c4c 0400 	ldr r0,[r11,+0x0]
8e0021fc:	183f 200a 	sub r8,r6,r0
8e002200:	006f 2406 	lsr r8,r8,0x3
8e002204:	40ef 2402 	mov r10,r8
8e002208:	400b 3002 	movt r10,0x0
8e00220c:	287f 2406 	lsl r9,r10,0x3
8e002210:	2089 0080 	ldrb r1,[r0,+r9]
8e002214:	009f 008a 	add r0,r0,r9
8e002218:	8084      	ldrb r4,[r0,0x1]
8e00221a:	9116      	lsl r4,r4,0x8
8e00221c:	90fa      	orr r4,r4,r1
8e00221e:	913f 008a 	sub r4,r4,r10
8e002222:	800b 1002 	movt r4,0x0
8e002226:	563a      	sub r2,r5,r4
8e002228:	8308 0000 	beq 8e00232e <umm_realloc+0x19e>
8e00222c:	258b 0252 	mov r1,0x252c
8e002230:	08ef 0402 	mov r0,r10
8e002234:	200b 18e2 	movt r1,0x8e00
8e002238:	0552      	jalr r1
8e00223a:	6c4c 0400 	ldr r3,[r11,+0x0]
8e00223e:	9076      	lsl r4,r4,0x3
8e002240:	2c9f 008a 	add r1,r3,r9
8e002244:	0584      	ldrb r0,[r1,0x3]
8e002246:	4504      	ldrb r2,[r1,0x2]
8e002248:	0116      	lsl r0,r0,0x8
8e00224a:	017a      	orr r0,r0,r2
8e00224c:	4076      	lsl r2,r0,0x3
8e00224e:	4d1a      	add r2,r3,r2
8e002250:	4884      	ldrb r2,[r2,0x1]
8e002252:	9213      	add r4,r4,-4
8e002254:	48e6      	lsr r2,r2,0x7
8e002256:	6833      	sub r3,r2,0
8e002258:	2c00      	beq 8e0022b0 <umm_realloc+0x120>
8e00225a:	4404      	ldrb r2,[r1]
8e00225c:	2484      	ldrb r1,[r1,0x1]
8e00225e:	2516      	lsl r1,r1,0x8
8e002260:	257a      	orr r1,r1,r2
8e002262:	243a      	sub r1,r1,r0
8e002264:	54ba      	sub r2,r5,r1
8e002266:	2560      	bgt 8e0022b0 <umm_realloc+0x120>
8e002268:	388b 0242 	mov r1,0x24c4
8e00226c:	200b 18e2 	movt r1,0x8e00
8e002270:	0552      	jalr r1
8e002272:	590b 0252 	mov r2,0x25c8
8e002276:	2003      	mov r1,0x0
8e002278:	08ef 0402 	mov r0,r10
8e00227c:	400b 18e2 	movt r2,0x8e00
8e002280:	0952      	jalr r2
8e002282:	007f 2006 	lsl r8,r0,0x3
8e002286:	40ef 2002 	mov r10,r0
8e00228a:	0c4c 0400 	ldr r0,[r11,+0x0]
8e00228e:	718b 0032 	mov r3,0x38c
8e002292:	001f 008a 	add r0,r0,r8
8e002296:	38e2      	mov r1,r6
8e002298:	50e2      	mov r2,r4
8e00229a:	021b 0000 	add r0,r0,4
8e00229e:	600b 18e2 	movt r3,0x8e00
8e0022a2:	0d52      	jalr r3
8e0022a4:	0c4c 0400 	ldr r0,[r11,+0x0]
8e0022a8:	001f 008a 	add r0,r0,r8
8e0022ac:	c21b 0000 	add r6,r0,4
8e0022b0:	2c4c 0400 	ldr r1,[r11,+0x0]
8e0022b4:	087f 0406 	lsl r0,r10,0x3
8e0022b8:	241a      	add r1,r1,r0
8e0022ba:	0484      	ldrb r0,[r1,0x1]
8e0022bc:	4404      	ldrb r2,[r1]
8e0022be:	0116      	lsl r0,r0,0x8
8e0022c0:	017a      	orr r0,r0,r2
8e0022c2:	013f 008a 	sub r0,r0,r10
8e0022c6:	000b 1002 	movt r0,0x0
8e0022ca:	743a      	sub r3,r5,r0
8e0022cc:	3100      	beq 8e00232e <umm_realloc+0x19e>
8e0022ce:	098b 2232 	mov r8,0x234c
8e0022d2:	000b 38e2 	movt r8,0x8e00
8e0022d6:	1830      	bgteu 8e002306 <umm_realloc+0x176>
8e0022d8:	658b 0242 	mov r3,0x242c
8e0022dc:	34e2      	mov r1,r5
8e0022de:	08ef 0402 	mov r0,r10
8e0022e2:	4003      	mov r2,0x0
8e0022e4:	600b 18e2 	movt r3,0x8e00
8e0022e8:	0d52      	jalr r3
8e0022ea:	070b 0032 	mov r0,0x338
8e0022ee:	000b 1002 	movt r0,0x0
8e0022f2:	aa9f 040a 	add r5,r10,r5
8e0022f6:	0044      	ldr r0,[r0]
8e0022f8:	b476      	lsl r5,r5,0x3
8e0022fa:	029a      	add r0,r0,r5
8e0022fc:	021b 0000 	add r0,r0,4
8e002300:	015f 0402 	jalr r8
8e002304:	15e0      	b 8e00232e <umm_realloc+0x19e>
8e002306:	218b 0202 	mov r1,0x200c
8e00230a:	1ce2      	mov r0,r7
8e00230c:	200b 18e2 	movt r1,0x8e00
8e002310:	0552      	jalr r1
8e002312:	a05a      	and r5,r0,r0
8e002314:	0800      	beq 8e002324 <umm_realloc+0x194>
8e002316:	6e8b 0032 	mov r3,0x374
8e00231a:	50e2      	mov r2,r4
8e00231c:	38e2      	mov r1,r6
8e00231e:	600b 18e2 	movt r3,0x8e00
8e002322:	0d52      	jalr r3
8e002324:	18e2      	mov r0,r6
8e002326:	015f 0402 	jalr r8
8e00232a:	14e2      	mov r0,r5
8e00232c:	02e0      	b 8e002330 <umm_realloc+0x1a0>
8e00232e:	18e2      	mov r0,r6
8e002330:	d66c 0400 	ldrd r6,[sp,+0x4]
8e002334:	15ec 2400 	ldrd r8,[sp,+0x3]
8e002338:	556c 2400 	ldrd r10,[sp,+0x2]
8e00233c:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002340:	b41b 2405 	add sp,sp,40
8e002344:	946c 0400 	ldrd r4,[sp,+0x0]
8e002348:	194f 0402 	rts

8e00234c <umm_free>:
8e00234c:	95fc 0700 	strd r4,[sp],-0x3
8e002350:	d6dc 0400 	str r6,[sp,+0x5]
8e002354:	d4fc 2400 	strd lr,[sp,+0x1]
8e002358:	005a      	and r0,r0,r0
8e00235a:	5100      	beq 8e0023fc <umm_free+0xb0>
8e00235c:	c70b 0032 	mov r6,0x338
8e002360:	c00b 1002 	movt r6,0x0
8e002364:	9844      	ldr r4,[r6]
8e002366:	258b 0252 	mov r1,0x252c
8e00236a:	823a      	sub r4,r0,r4
8e00236c:	9066      	lsr r4,r4,0x3
8e00236e:	b0e2      	mov r5,r4
8e002370:	a00b 1002 	movt r5,0x0
8e002374:	14e2      	mov r0,r5
8e002376:	200b 18e2 	movt r1,0x8e00
8e00237a:	0552      	jalr r1
8e00237c:	5844      	ldr r2,[r6]
8e00237e:	3476      	lsl r1,r5,0x3
8e002380:	289a      	add r1,r2,r1
8e002382:	0584      	ldrb r0,[r1,0x3]
8e002384:	6504      	ldrb r3,[r1,0x2]
8e002386:	0116      	lsl r0,r0,0x8
8e002388:	01fa      	orr r0,r0,r3
8e00238a:	0076      	lsl r0,r0,0x3
8e00238c:	081a      	add r0,r2,r0
8e00238e:	0084      	ldrb r0,[r0,0x1]
8e002390:	00e6      	lsr r0,r0,0x7
8e002392:	6033      	sub r3,r0,0
8e002394:	1100      	beq 8e0023b6 <umm_free+0x6a>
8e002396:	d6cc 0400 	ldr r6,[sp,+0x5]
8e00239a:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e00239e:	b41b 2403 	add sp,sp,24
8e0023a2:	14e2      	mov r0,r5
8e0023a4:	590b 0252 	mov r2,0x25c8
8e0023a8:	946c 0400 	ldrd r4,[sp,+0x0]
8e0023ac:	200b 0802 	mov r1,0x8000
8e0023b0:	400b 18e2 	movt r2,0x8e00
8e0023b4:	0942      	jr r2
8e0023b6:	0a84      	ldrb r0,[r2,0x5]
8e0023b8:	6a04      	ldrb r3,[r2,0x4]
8e0023ba:	0116      	lsl r0,r0,0x8
8e0023bc:	01fa      	orr r0,r0,r3
8e0023be:	0076      	lsl r0,r0,0x3
8e0023c0:	7fe3      	mov r3,0xff
8e0023c2:	081a      	add r0,r2,r0
8e0023c4:	75da      	and r3,r5,r3
8e0023c6:	b506      	lsr r5,r5,0x8
8e0023c8:	6314      	strb r3,[r0,0x6]
8e0023ca:	a394      	strb r5,[r0,0x7]
8e0023cc:	0a84      	ldrb r0,[r2,0x5]
8e0023ce:	8a0c 2000 	ldrb ip,[r2,+0x4]
8e0023d2:	0116      	lsl r0,r0,0x8
8e0023d4:	027f 008a 	orr r0,r0,ip
8e0023d8:	0614      	strb r0,[r1,0x4]
8e0023da:	0106      	lsr r0,r0,0x8
8e0023dc:	0694      	strb r0,[r1,0x5]
8e0023de:	0003      	mov r0,0x0
8e0023e0:	0714      	strb r0,[r1,0x6]
8e0023e2:	0794      	strb r0,[r1,0x7]
8e0023e4:	6a14      	strb r3,[r2,0x4]
8e0023e6:	aa94      	strb r5,[r2,0x5]
8e0023e8:	0484      	ldrb r0,[r1,0x1]
8e0023ea:	4404      	ldrb r2,[r1]
8e0023ec:	0116      	lsl r0,r0,0x8
8e0023ee:	017a      	orr r0,r0,r2
8e0023f0:	400b 0802 	mov r2,0x8000
8e0023f4:	017a      	orr r0,r0,r2
8e0023f6:	0414      	strb r0,[r1]
8e0023f8:	0106      	lsr r0,r0,0x8
8e0023fa:	0494      	strb r0,[r1,0x1]
8e0023fc:	d6cc 0400 	ldr r6,[sp,+0x5]
8e002400:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002404:	b41b 2403 	add sp,sp,24
8e002408:	946c 0400 	ldrd r4,[sp,+0x0]
8e00240c:	194f 0402 	rts

8e002410 <umm_blocks>:
8e002410:	223b 0000 	sub r1,r0,4
8e002414:	0840      	blteu 8e002424 <umm_blocks+0x14>
8e002416:	019b 00ff 	add r0,r0,-5
8e00241a:	0066      	lsr r0,r0,0x3
8e00241c:	0113      	add r0,r0,2
8e00241e:	000b 1002 	movt r0,0x0
8e002422:	02e0      	b 8e002426 <umm_blocks+0x16>
8e002424:	0023      	mov r0,0x1
8e002426:	194f 0402 	rts
8e00242a:	01a2      	nop

8e00242c <umm_make_new_block>:
8e00242c:	470b 4032 	mov r18,0x338
8e002430:	400b 5002 	movt r18,0x0
8e002434:	284c 4800 	ldr r17,[r18,+0x0]
8e002438:	000b 1002 	movt r0,0x0
8e00243c:	807f 2006 	lsl ip,r0,0x3
8e002440:	661f 088a 	add r3,r17,ip
8e002444:	6c84      	ldrb r3,[r3,0x1]
8e002446:	6609 4880 	ldrb r19,[r17,+ip]
8e00244a:	200b 1002 	movt r1,0x0
8e00244e:	6d16      	lsl r3,r3,0x8
8e002450:	209a      	add r1,r0,r1
8e002452:	6dff 010a 	orr r3,r3,r19
8e002456:	7feb 47f2 	mov r19,0x7fff
8e00245a:	047f 4006 	lsl r16,r1,0x3
8e00245e:	6ddf 010a 	and r3,r3,r19
8e002462:	6419 0900 	strb r3,[r17,+r16]
8e002466:	6d06      	lsr r3,r3,0x8
8e002468:	241f 490a 	add r17,r17,r16
8e00246c:	649c 0800 	strb r3,[r17,+0x1]
8e002470:	684c 0800 	ldr r3,[r18,+0x0]
8e002474:	200b 1002 	movt r1,0x0
8e002478:	0c1f 410a 	add r16,r3,r16
8e00247c:	6106      	lsr r3,r0,0x8
8e00247e:	619c 0800 	strb r3,[r16,+0x3]
8e002482:	011c 0800 	strb r0,[r16,+0x2]
8e002486:	084c 4800 	ldr r16,[r18,+0x0]
8e00248a:	400b 1002 	movt r2,0x0
8e00248e:	621f 088a 	add r3,r16,ip
8e002492:	6c84      	ldrb r3,[r3,0x1]
8e002494:	0209 0880 	ldrb r0,[r16,+ip]
8e002498:	6d16      	lsl r3,r3,0x8
8e00249a:	6c7a      	orr r3,r3,r0
8e00249c:	0ddf 010a 	and r0,r3,r19
8e0024a0:	0076      	lsl r0,r0,0x3
8e0024a2:	001f 080a 	add r0,r16,r0
8e0024a6:	6506      	lsr r3,r1,0x8
8e0024a8:	2114      	strb r1,[r0,0x2]
8e0024aa:	6194      	strb r3,[r0,0x3]
8e0024ac:	084c 0800 	ldr r0,[r18,+0x0]
8e0024b0:	257a      	orr r1,r1,r2
8e0024b2:	2219 0080 	strb r1,[r0,+ip]
8e0024b6:	2506      	lsr r1,r1,0x8
8e0024b8:	821f 208a 	add ip,r0,ip
8e0024bc:	309c 0400 	strb r1,[ip,+0x1]
8e0024c0:	194f 0402 	rts

8e0024c4 <umm_disconnect_from_free_list>:
8e0024c4:	270b 0032 	mov r1,0x338
8e0024c8:	200b 1002 	movt r1,0x0
8e0024cc:	844c 2000 	ldr ip,[r1,+0x0]
8e0024d0:	000b 1002 	movt r0,0x0
8e0024d4:	0076      	lsl r0,r0,0x3
8e0024d6:	101f 040a 	add r0,ip,r0
8e0024da:	4284      	ldrb r2,[r0,0x5]
8e0024dc:	6204      	ldrb r3,[r0,0x4]
8e0024de:	4916      	lsl r2,r2,0x8
8e0024e0:	69fa      	orr r3,r2,r3
8e0024e2:	4384      	ldrb r2,[r0,0x7]
8e0024e4:	2304      	ldrb r1,[r0,0x6]
8e0024e6:	4916      	lsl r2,r2,0x8
8e0024e8:	48fa      	orr r2,r2,r1
8e0024ea:	4876      	lsl r2,r2,0x3
8e0024ec:	511f 040a 	add r2,ip,r2
8e0024f0:	6a14      	strb r3,[r2,0x4]
8e0024f2:	6d06      	lsr r3,r3,0x8
8e0024f4:	6a94      	strb r3,[r2,0x5]
8e0024f6:	4384      	ldrb r2,[r0,0x7]
8e0024f8:	6304      	ldrb r3,[r0,0x6]
8e0024fa:	4916      	lsl r2,r2,0x8
8e0024fc:	69fa      	orr r3,r2,r3
8e0024fe:	4284      	ldrb r2,[r0,0x5]
8e002500:	2204      	ldrb r1,[r0,0x4]
8e002502:	4916      	lsl r2,r2,0x8
8e002504:	28fa      	orr r1,r2,r1
8e002506:	2476      	lsl r1,r1,0x3
8e002508:	309f 040a 	add r1,ip,r1
8e00250c:	6714      	strb r3,[r1,0x6]
8e00250e:	6d06      	lsr r3,r3,0x8
8e002510:	6794      	strb r3,[r1,0x7]
8e002512:	2084      	ldrb r1,[r0,0x1]
8e002514:	4004      	ldrb r2,[r0]
8e002516:	2516      	lsl r1,r1,0x8
8e002518:	257a      	orr r1,r1,r2
8e00251a:	5feb 07f2 	mov r2,0x7fff
8e00251e:	255a      	and r1,r1,r2
8e002520:	2014      	strb r1,[r0]
8e002522:	2506      	lsr r1,r1,0x8
8e002524:	2094      	strb r1,[r0,0x1]
8e002526:	194f 0402 	rts
8e00252a:	01a2      	nop

8e00252c <umm_assimilate_up>:
8e00252c:	95fc 0700 	strd r4,[sp],-0x3
8e002530:	d6dc 0400 	str r6,[sp,+0x5]
8e002534:	c70b 0032 	mov r6,0x338
8e002538:	d4fc 2400 	strd lr,[sp,+0x1]
8e00253c:	a0e2      	mov r5,r0
8e00253e:	c00b 1002 	movt r6,0x0
8e002542:	5844      	ldr r2,[r6]
8e002544:	a00b 1002 	movt r5,0x0
8e002548:	9476      	lsl r4,r5,0x3
8e00254a:	0a1a      	add r0,r2,r4
8e00254c:	0084      	ldrb r0,[r0,0x1]
8e00254e:	2a01      	ldrb r1,[r2,r4]
8e002550:	0116      	lsl r0,r0,0x8
8e002552:	00fa      	orr r0,r0,r1
8e002554:	2076      	lsl r1,r0,0x3
8e002556:	289a      	add r1,r2,r1
8e002558:	2484      	ldrb r1,[r1,0x1]
8e00255a:	24e6      	lsr r1,r1,0x7
8e00255c:	4433      	sub r2,r1,0
8e00255e:	2a00      	beq 8e0025b2 <umm_assimilate_up+0x86>
8e002560:	388b 0242 	mov r1,0x24c4
8e002564:	200b 18e2 	movt r1,0x8e00
8e002568:	0552      	jalr r1
8e00256a:	3844      	ldr r1,[r6]
8e00256c:	461a      	add r2,r1,r4
8e00256e:	4884      	ldrb r2,[r2,0x1]
8e002570:	0601      	ldrb r0,[r1,r4]
8e002572:	4916      	lsl r2,r2,0x8
8e002574:	487a      	orr r2,r2,r0
8e002576:	4876      	lsl r2,r2,0x3
8e002578:	451a      	add r2,r1,r2
8e00257a:	0884      	ldrb r0,[r2,0x1]
8e00257c:	6804      	ldrb r3,[r2]
8e00257e:	0116      	lsl r0,r0,0x8
8e002580:	01fa      	orr r0,r0,r3
8e002582:	7feb 07f2 	mov r3,0x7fff
8e002586:	01da      	and r0,r0,r3
8e002588:	0076      	lsl r0,r0,0x3
8e00258a:	241a      	add r1,r1,r0
8e00258c:	a514      	strb r5,[r1,0x2]
8e00258e:	b506      	lsr r5,r5,0x8
8e002590:	a594      	strb r5,[r1,0x3]
8e002592:	1844      	ldr r0,[r6]
8e002594:	821a      	add r4,r0,r4
8e002596:	5084      	ldrb r2,[r4,0x1]
8e002598:	3004      	ldrb r1,[r4]
8e00259a:	4916      	lsl r2,r2,0x8
8e00259c:	28fa      	orr r1,r2,r1
8e00259e:	2476      	lsl r1,r1,0x3
8e0025a0:	209a      	add r1,r0,r1
8e0025a2:	0404      	ldrb r0,[r1]
8e0025a4:	2484      	ldrb r1,[r1,0x1]
8e0025a6:	2516      	lsl r1,r1,0x8
8e0025a8:	047a      	orr r0,r1,r0
8e0025aa:	01da      	and r0,r0,r3
8e0025ac:	1014      	strb r0,[r4]
8e0025ae:	0106      	lsr r0,r0,0x8
8e0025b0:	1094      	strb r0,[r4,0x1]
8e0025b2:	d6cc 0400 	ldr r6,[sp,+0x5]
8e0025b6:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0025ba:	b41b 2403 	add sp,sp,24
8e0025be:	946c 0400 	ldrd r4,[sp,+0x0]
8e0025c2:	194f 0402 	rts
8e0025c6:	01a2      	nop

8e0025c8 <umm_assimilate_down>:
8e0025c8:	070b 4032 	mov r16,0x338
8e0025cc:	000b 5002 	movt r16,0x0
8e0025d0:	204c 4800 	ldr r17,[r16,+0x0]
8e0025d4:	000b 1002 	movt r0,0x0
8e0025d8:	0076      	lsl r0,r0,0x3
8e0025da:	841f 280a 	add ip,r17,r0
8e0025de:	718c 0400 	ldrb r3,[ip,+0x3]
8e0025e2:	510c 0400 	ldrb r2,[ip,+0x2]
8e0025e6:	6d16      	lsl r3,r3,0x8
8e0025e8:	4d7a      	orr r2,r3,r2
8e0025ea:	4876      	lsl r2,r2,0x3
8e0025ec:	708c 0400 	ldrb r3,[ip,+0x1]
8e0025f0:	451f 080a 	add r2,r17,r2
8e0025f4:	6d16      	lsl r3,r3,0x8
8e0025f6:	300c 4400 	ldrb r17,[ip,+0x0]
8e0025fa:	6cff 010a 	orr r3,r3,r17
8e0025fe:	200b 1002 	movt r1,0x0
8e002602:	25fa      	orr r1,r1,r3
8e002604:	2814      	strb r1,[r2]
8e002606:	2506      	lsr r1,r1,0x8
8e002608:	2894      	strb r1,[r2,0x1]
8e00260a:	204c 4800 	ldr r17,[r16,+0x0]
8e00260e:	841f 280a 	add ip,r17,r0
8e002612:	518c 0400 	ldrb r2,[ip,+0x3]
8e002616:	710c 0400 	ldrb r3,[ip,+0x2]
8e00261a:	4916      	lsl r2,r2,0x8
8e00261c:	69fa      	orr r3,r2,r3
8e00261e:	508c 0400 	ldrb r2,[ip,+0x1]
8e002622:	300c 0400 	ldrb r1,[ip,+0x0]
8e002626:	4916      	lsl r2,r2,0x8
8e002628:	28fa      	orr r1,r2,r1
8e00262a:	2476      	lsl r1,r1,0x3
8e00262c:	249f 080a 	add r1,r17,r1
8e002630:	6514      	strb r3,[r1,0x2]
8e002632:	6d06      	lsr r3,r3,0x8
8e002634:	6594      	strb r3,[r1,0x3]
8e002636:	204c 0800 	ldr r1,[r16,+0x0]
8e00263a:	041a      	add r0,r1,r0
8e00263c:	2104      	ldrb r1,[r0,0x2]
8e00263e:	0184      	ldrb r0,[r0,0x3]
8e002640:	0116      	lsl r0,r0,0x8
8e002642:	00fa      	orr r0,r0,r1
8e002644:	194f 0402 	rts

8e002648 <bj_add_lk_syms>:
8e002648:	d4fc 2700 	strd lr,[sp],-0x1
8e00264c:	f41b 2401 	add fp,sp,8
8e002650:	000b 0002 	mov r0,0x0
8e002654:	000b 18e2 	movt r0,0x8e00
8e002658:	210b 0042 	mov r1,0x408
8e00265c:	200b 18e2 	movt r1,0x8e00
8e002660:	0552      	jalr r1
8e002662:	000b 0002 	mov r0,0x0
8e002666:	000b 18e2 	movt r0,0x8e00
8e00266a:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e00266e:	b41b 2401 	add sp,sp,8
8e002672:	194f 0402 	rts
8e002676:	01a2      	nop

8e002678 <bj_host_addr_to_core_addr>:
8e002678:	d57c 2700 	strd lr,[sp],-0x2
8e00267c:	f41b 2402 	add fp,sp,16
8e002680:	1cdc 0500 	str r0,[fp,-0x1]
8e002684:	0f0b 0262 	mov r0,0x2678
8e002688:	000b 18e2 	movt r0,0x8e00
8e00268c:	3c0b 0272 	mov r1,0x27e0
8e002690:	200b 18e2 	movt r1,0x8e00
8e002694:	5a8b 0092 	mov r2,0x9d4
8e002698:	400b 18e2 	movt r2,0x8e00
8e00269c:	0952      	jalr r2
8e00269e:	0003      	mov r0,0x0
8e0026a0:	d56c 2400 	ldrd lr,[sp,+0x2]
8e0026a4:	b41b 2402 	add sp,sp,16
8e0026a8:	194f 0402 	rts

8e0026ac <bj_core_addr_to_host_addr>:
8e0026ac:	d57c 2700 	strd lr,[sp],-0x2
8e0026b0:	f41b 2402 	add fp,sp,16
8e0026b4:	1cdc 0500 	str r0,[fp,-0x1]
8e0026b8:	158b 0262 	mov r0,0x26ac
8e0026bc:	000b 18e2 	movt r0,0x8e00
8e0026c0:	210b 0282 	mov r1,0x2808
8e0026c4:	200b 18e2 	movt r1,0x8e00
8e0026c8:	5a8b 0092 	mov r2,0x9d4
8e0026cc:	400b 18e2 	movt r2,0x8e00
8e0026d0:	0952      	jalr r2
8e0026d2:	0003      	mov r0,0x0
8e0026d4:	d56c 2400 	ldrd lr,[sp,+0x2]
8e0026d8:	b41b 2402 	add sp,sp,16
8e0026dc:	194f 0402 	rts

8e0026e0 <err_1>:
8e0026e0:	6361      	ldrd r3,[r0,r6]
8e0026e2:	7571      	strd r3,[r5,r2]
8e0026e4:	7269 5f65 	*unknown*
8e0026e8:	6c61      	ldrd r3,[r3,r0]
8e0026ea:	6f6c 2063 	ldrd r11,[r3,+0x31e]
8e0026ee:	6261      	ldrd r3,[r0,r4]
8e0026f0:	726f 0a74 	*unknown*
8e0026f4:	0000      	beq 8e0026f4 <err_1+0x14>
	...

8e0026f8 <err_2>:
8e0026f8:	6a62 685f 	*unknown*
8e0026fc:	736f 5f74 	*unknown*
8e002700:	6e69 7469 	*unknown*
8e002704:	6120      	bgtu 8e0027c6 <err_10+0xe>
8e002706:	6f62 7472 	*unknown*
8e00270a:	000a      	eor r0,r0,r0
8e00270c:	0000      	beq 8e00270c <err_2+0x14>
	...

8e002710 <err_3>:
8e002710:	6a62 685f 	*unknown*
8e002714:	736f 5f74 	*unknown*
8e002718:	7572 206e 	*unknown*
8e00271c:	6261      	ldrd r3,[r0,r4]
8e00271e:	726f 0a74 	*unknown*
8e002722:	0000      	beq 8e002722 <err_3+0x12>
8e002724:	0000      	beq 8e002724 <err_3+0x14>
	...

8e002728 <err_4>:
8e002728:	6a62 685f 	*unknown*
8e00272c:	736f 5f74 	*unknown*
8e002730:	6966      	lsr r3,r2,0xb
8e002732:	696e      	asr r3,r2,0xb
8e002734:	6873 6120 	*unknown*
8e002738:	6f62 7472 	*unknown*
8e00273c:	000a      	eor r0,r0,r0
	...

8e002740 <err_5>:
8e002740:	6261      	ldrd r3,[r0,r4]
8e002742:	726f 2874 	*unknown*
8e002746:	2029 6261 	*unknown*
8e00274a:	726f 0a74 	*unknown*
	...

8e002750 <err_6>:
8e002750:	6a62 5f6b 	*unknown*
8e002754:	6c67      	fix r3,r3
8e002756:	5f62 6e69 	*unknown*
8e00275a:	7469 6120 	*unknown*
8e00275e:	6f62 7472 	*unknown*
8e002762:	315f 0a2e 	*unknown*
	...

8e002768 <err_7>:
8e002768:	6a62 5f6b 	*unknown*
8e00276c:	6c67      	fix r3,r3
8e00276e:	5f62 6e69 	*unknown*
8e002772:	7469 6120 	*unknown*
8e002776:	6f62 7472 	*unknown*
8e00277a:	325f 0a2e 	*unknown*
	...

8e002780 <err_8>:
8e002780:	6a62 5f6b 	*unknown*
8e002784:	6c67      	fix r3,r3
8e002786:	5f62 6e69 	*unknown*
8e00278a:	7469 6120 	*unknown*
8e00278e:	6f62 7472 	*unknown*
8e002792:	335f 0a2e 	*unknown*
	...

8e002798 <err_9>:
8e002798:	6761      	ldrd r3,[r1,r6]
8e00279a:	6e65      	ldrd r3,[r3],r4
8e00279c:	3a74      	strd r1,[r6,0x4]
8e00279e:	673a      	sub r3,r1,r6
8e0027a0:	7465      	ldrd r3,[r5],r0
8e0027a2:	615f 6176 	*unknown*
8e0027a6:	6c69 6261 	*unknown*
8e0027aa:	656c 6120 	ldrd r27,[r1,-0x102]
8e0027ae:	6f62 7472 	*unknown*
8e0027b2:	000a      	eor r0,r0,r0
8e0027b4:	0000      	beq 8e0027b4 <err_9+0x1c>
	...

8e0027b8 <err_10>:
8e0027b8:	6761      	ldrd r3,[r1,r6]
8e0027ba:	6e65      	ldrd r3,[r3],r4
8e0027bc:	3a74      	strd r1,[r6,0x4]
8e0027be:	693a      	sub r3,r2,r2
8e0027c0:	696e      	asr r3,r2,0xb
8e0027c2:	5f74      	strd r2,[r7,0x6]
8e0027c4:	656d 6120 	*unknown*
8e0027c8:	6f62 7472 	*unknown*
8e0027cc:	000a      	eor r0,r0,r0
	...

8e0027d0 <err_11>:
8e0027d0:	7361      	ldrd r3,[r4,r6]
8e0027d2:	6573 7472 	*unknown*
8e0027d6:	6120      	bgtu 8e002898 <err_13+0x90>
8e0027d8:	6f62 7472 	*unknown*
8e0027dc:	000a      	eor r0,r0,r0
	...

8e0027e0 <err_12>:
8e0027e0:	6a62 685f 	*unknown*
8e0027e4:	736f 5f74 	*unknown*
8e0027e8:	6461      	ldrd r3,[r1,r0]
8e0027ea:	7264      	ldrd r3,[r4,0x4]
8e0027ec:	745f 5f6f 	*unknown*
8e0027f0:	6f63      	mov r3,0x7b
8e0027f2:	6572 615f 	*unknown*
8e0027f6:	6464      	ldrd r3,[r1]
8e0027f8:	2072      	movgte r1,r0
8e0027fa:	6261      	ldrd r3,[r0,r4]
8e0027fc:	726f 0a74 	*unknown*
	...

8e002808 <err_13>:
8e002808:	6a62 635f 	*unknown*
8e00280c:	726f 5f65 	*unknown*
8e002810:	6461      	ldrd r3,[r1,r0]
8e002812:	7264      	ldrd r3,[r4,0x4]
8e002814:	745f 5f6f 	*unknown*
8e002818:	6f68 7473 	bgt 8ee90ef6 <LD_EXTERNAL_LOAD_ORIG+0x690ef6>
8e00281c:	615f 6464 	*unknown*
8e002820:	2072      	movgte r1,r0
8e002822:	6261      	ldrd r3,[r0,r4]
8e002824:	726f 0a74 	*unknown*
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
 11c:	5a8b 0092 	mov r2,0x9d4
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

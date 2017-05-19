
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
   8:	44e8 0001 	b 290 <bjk_page_miss_handler>

Disassembly of section ivt_timer0:

0000000c <irq3_entry>:
   c:	76e8 0001 	b 2f8 <bjk_timer0_handler>

Disassembly of section external_code_ram:

8e000038 <bj_cores_main>:
8e000038:	d57c 2700 	strd lr,[sp],-0x2
8e00003c:	f41b 2402 	add fp,sp,16
8e000040:	0e8b 0042 	mov r0,0x474
8e000044:	000b 18e2 	movt r0,0x8e00
8e000048:	0152      	jalr r0
8e00004a:	070b 0032 	mov r0,0x338
8e00004e:	000b 1002 	movt r0,0x0
8e000052:	1cdc 0500 	str r0,[fp,-0x1]
8e000056:	2003      	mov r1,0x0
8e000058:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00005c:	528b 0002 	mov r2,0x94
8e000060:	400b 18e2 	movt r2,0x8e00
8e000064:	0952      	jalr r2
8e000066:	2423      	mov r1,0x21
8e000068:	090b 0032 	mov r0,0x348
8e00006c:	000b 1002 	movt r0,0x0
8e000070:	4c8b 0012 	mov r2,0x164
8e000074:	400b 1002 	movt r2,0x0
8e000078:	0952      	jalr r2
8e00007a:	1d0b 0082 	mov r0,0x8e8
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
8e0000a4:	0f8b 0032 	mov r0,0x37c
8e0000a8:	000b 1002 	movt r0,0x0
8e0000ac:	0044      	ldr r0,[r0]
8e0000ae:	0044      	ldr r0,[r0]
8e0000b0:	2033      	sub r1,r0,0
8e0000b2:	8908 0000 	beq 8e0001c4 <bjk_aux_sout+0x130>
8e0000b6:	0043      	mov r0,0x2
8e0000b8:	1e9c 0500 	strb r0,[fp,-0x5]
8e0000bc:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0000c0:	368b 0032 	mov r1,0x3b4
8e0000c4:	200b 18e2 	movt r1,0x8e00
8e0000c8:	0552      	jalr r1
8e0000ca:	1cbc 0500 	strh r0,[fp,-0x1]
8e0000ce:	3cac 0500 	ldrh r1,[fp,-0x1]
8e0000d2:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e0000d6:	458b 0012 	mov r2,0x12c
8e0000da:	083a      	sub r0,r2,r0
8e0000dc:	443a      	sub r2,r1,r0
8e0000de:	0a90      	blte 8e0000f2 <bjk_aux_sout+0x5e>
8e0000e0:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e0000e4:	000b 1002 	movt r0,0x0
8e0000e8:	258b 0012 	mov r1,0x12c
8e0000ec:	043a      	sub r0,r1,r0
8e0000ee:	1cbc 0500 	strh r0,[fp,-0x1]
8e0000f2:	0f8b 0032 	mov r0,0x37c
8e0000f6:	000b 1002 	movt r0,0x0
8e0000fa:	0044      	ldr r0,[r0]
8e0000fc:	001b 0008 	add r0,r0,64
8e000100:	1ddc 0500 	str r0,[fp,-0x3]
8e000104:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000108:	3dcc 0500 	ldr r1,[fp,-0x3]
8e00010c:	041a      	add r0,r1,r0
8e00010e:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000112:	44e2      	mov r2,r1
8e000114:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000118:	6d0b 0032 	mov r3,0x368
8e00011c:	600b 18e2 	movt r3,0x8e00
8e000120:	0d52      	jalr r3
8e000122:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000126:	2316      	lsl r1,r0,0x18
8e000128:	2706      	lsr r1,r1,0x18
8e00012a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00012e:	2014      	strb r1,[r0]
8e000130:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000134:	0093      	add r0,r0,1
8e000136:	2003      	mov r1,0x0
8e000138:	2014      	strb r1,[r0]
8e00013a:	0f8b 0032 	mov r0,0x37c
8e00013e:	000b 1002 	movt r0,0x0
8e000142:	0044      	ldr r0,[r0]
8e000144:	1e5c 0500 	str r0,[fp,-0x4]
8e000148:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00014c:	60c4      	ldr r3,[r0,0x1]
8e00014e:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000152:	20e2      	mov r1,r0
8e000154:	200b 1002 	movt r1,0x0
8e000158:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00015c:	041a      	add r0,r1,r0
8e00015e:	000b 1002 	movt r0,0x0
8e000162:	5dcc 0500 	ldr r2,[fp,-0x3]
8e000166:	20e2      	mov r1,r0
8e000168:	0ce2      	mov r0,r3
8e00016a:	750b 00e2 	mov r3,0xea8
8e00016e:	600b 18e2 	movt r3,0x8e00
8e000172:	0d52      	jalr r3
8e000174:	1d3c 0500 	strh r0,[fp,-0x2]
8e000178:	21e0      	b 8e0001ba <bjk_aux_sout+0x126>
8e00017a:	4003      	mov r2,0x0
8e00017c:	2003      	mov r1,0x0
8e00017e:	1763      	mov r0,0xbb
8e000180:	768b 0162 	mov r3,0x16b4
8e000184:	600b 18e2 	movt r3,0x8e00
8e000188:	0d52      	jalr r3
8e00018a:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00018e:	60c4      	ldr r3,[r0,0x1]
8e000190:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000194:	20e2      	mov r1,r0
8e000196:	200b 1002 	movt r1,0x0
8e00019a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00019e:	041a      	add r0,r1,r0
8e0001a0:	000b 1002 	movt r0,0x0
8e0001a4:	5dcc 0500 	ldr r2,[fp,-0x3]
8e0001a8:	20e2      	mov r1,r0
8e0001aa:	0ce2      	mov r0,r3
8e0001ac:	750b 00e2 	mov r3,0xea8
8e0001b0:	600b 18e2 	movt r3,0x8e00
8e0001b4:	0d52      	jalr r3
8e0001b6:	1d3c 0500 	strh r0,[fp,-0x2]
8e0001ba:	1d2c 0500 	ldrh r0,[fp,-0x2]
8e0001be:	2033      	sub r1,r0,0
8e0001c0:	dd00      	beq 8e00017a <bjk_aux_sout+0xe6>
8e0001c2:	02e0      	b 8e0001c6 <bjk_aux_sout+0x132>
8e0001c4:	01a2      	nop
8e0001c6:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0001ca:	b41b 2404 	add sp,sp,32
8e0001ce:	194f 0402 	rts
8e0001d2:	01a2      	nop

8e0001d4 <bjk_aux_iout>:
8e0001d4:	d7fc 2700 	strd lr,[sp],-0x7
8e0001d8:	96dc 0401 	str r4,[sp,+0xd]
8e0001dc:	f41b 2407 	add fp,sp,56
8e0001e0:	1cdc 0501 	str r0,[fp,-0x9]
8e0001e4:	3d5c 0501 	str r1,[fp,-0xa]
8e0001e8:	5ddc 0501 	str r2,[fp,-0xb]
8e0001ec:	14ef 0402 	mov r0,sp
8e0001f0:	80e2      	mov r4,r0
8e0001f2:	0f8b 0032 	mov r0,0x37c
8e0001f6:	000b 1002 	movt r0,0x0
8e0001fa:	0044      	ldr r0,[r0]
8e0001fc:	0044      	ldr r0,[r0]
8e0001fe:	2033      	sub r1,r0,0
8e000200:	0410      	bne 8e000208 <bjk_aux_iout+0x34>
8e000202:	0003      	mov r0,0x0
8e000204:	89e8 0000 	b 8e000316 <bjk_aux_iout+0x142>
8e000208:	00c3      	mov r0,0x6
8e00020a:	1f3c 0500 	strh r0,[fp,-0x6]
8e00020e:	1f2c 0500 	ldrh r0,[fp,-0x6]
8e000212:	20e2      	mov r1,r0
8e000214:	2793      	add r1,r1,-1
8e000216:	3e5c 0500 	str r1,[fp,-0x4]
8e00021a:	40ef 4002 	mov r18,r0
8e00021e:	600b 4002 	mov r19,0x0
8e000222:	2baf 0806 	lsr r1,r18,0x1d
8e000226:	ec7f 4806 	lsl r23,r19,0x3
8e00022a:	e7ff 410a 	orr r23,r1,r23
8e00022e:	c87f 4806 	lsl r22,r18,0x3
8e000232:	00ef 4002 	mov r16,r0
8e000236:	200b 4002 	mov r17,0x0
8e00023a:	23af 0806 	lsr r1,r16,0x1d
8e00023e:	a47f 4806 	lsl r21,r17,0x3
8e000242:	a6ff 410a 	orr r21,r1,r21
8e000246:	807f 4806 	lsl r20,r16,0x3
8e00024a:	039b 0000 	add r0,r0,7
8e00024e:	0066      	lsr r0,r0,0x3
8e000250:	0076      	lsl r0,r0,0x3
8e000252:	b43f 240a 	sub sp,sp,r0
8e000256:	141b 0401 	add r0,sp,8
8e00025a:	0013      	add r0,r0,0
8e00025c:	1edc 0500 	str r0,[fp,-0x5]
8e000260:	1d4c 0501 	ldr r0,[fp,-0xa]
8e000264:	2316      	lsl r1,r0,0x18
8e000266:	2706      	lsr r1,r1,0x18
8e000268:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00026c:	2014      	strb r1,[r0]
8e00026e:	1dcc 0501 	ldr r0,[fp,-0xb]
8e000272:	2316      	lsl r1,r0,0x18
8e000274:	2706      	lsr r1,r1,0x18
8e000276:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00027a:	2094      	strb r1,[r0,0x1]
8e00027c:	1e1b 04fb 	add r0,fp,-36
8e000280:	1f5c 0500 	str r0,[fp,-0x6]
8e000284:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000288:	2004      	ldrb r1,[r0]
8e00028a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00028e:	2114      	strb r1,[r0,0x2]
8e000290:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000294:	2084      	ldrb r1,[r0,0x1]
8e000296:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00029a:	2194      	strb r1,[r0,0x3]
8e00029c:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0002a0:	2104      	ldrb r1,[r0,0x2]
8e0002a2:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0002a6:	2214      	strb r1,[r0,0x4]
8e0002a8:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0002ac:	2184      	ldrb r1,[r0,0x3]
8e0002ae:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0002b2:	2294      	strb r1,[r0,0x5]
8e0002b4:	0f8b 0032 	mov r0,0x37c
8e0002b8:	000b 1002 	movt r0,0x0
8e0002bc:	0044      	ldr r0,[r0]
8e0002be:	1fdc 0500 	str r0,[fp,-0x7]
8e0002c2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0002c6:	00c4      	ldr r0,[r0,0x1]
8e0002c8:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e0002cc:	5ecc 0500 	ldr r2,[fp,-0x5]
8e0002d0:	750b 00e2 	mov r3,0xea8
8e0002d4:	600b 18e2 	movt r3,0x8e00
8e0002d8:	0d52      	jalr r3
8e0002da:	1ebc 0500 	strh r0,[fp,-0x5]
8e0002de:	17e0      	b 8e00030c <bjk_aux_iout+0x138>
8e0002e0:	4003      	mov r2,0x0
8e0002e2:	2003      	mov r1,0x0
8e0002e4:	1763      	mov r0,0xbb
8e0002e6:	768b 0162 	mov r3,0x16b4
8e0002ea:	600b 18e2 	movt r3,0x8e00
8e0002ee:	0d52      	jalr r3
8e0002f0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0002f4:	00c4      	ldr r0,[r0,0x1]
8e0002f6:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e0002fa:	5ecc 0500 	ldr r2,[fp,-0x5]
8e0002fe:	750b 00e2 	mov r3,0xea8
8e000302:	600b 18e2 	movt r3,0x8e00
8e000306:	0d52      	jalr r3
8e000308:	1ebc 0500 	strh r0,[fp,-0x5]
8e00030c:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000310:	2033      	sub r1,r0,0
8e000312:	e700      	beq 8e0002e0 <bjk_aux_iout+0x10c>
8e000314:	0023      	mov r0,0x1
8e000316:	b0ef 2002 	mov sp,r4
8e00031a:	20b3      	sub r1,r0,1
8e00031c:	bc1b 24f9 	add sp,fp,-56
8e000320:	d7ec 2400 	ldrd lr,[sp,+0x7]
8e000324:	96cc 0401 	ldr r4,[sp,+0xd]
8e000328:	b41b 2407 	add sp,sp,56
8e00032c:	194f 0402 	rts

8e000330 <bj_get_aligment>:
8e000330:	20e3      	mov r1,0x7
8e000332:	20da      	and r1,r0,r1
8e000334:	0900      	beq 8e000346 <bj_get_aligment+0x16>
8e000336:	2063      	mov r1,0x3
8e000338:	20da      	and r1,r0,r1
8e00033a:	0800      	beq 8e00034a <bj_get_aligment+0x1a>
8e00033c:	03f6      	lsl r0,r0,0x1f
8e00033e:	0103      	mov r0,0x8
8e000340:	2203      	mov r1,0x10
8e000342:	0472      	movgte r0,r1
8e000344:	04e0      	b 8e00034c <bj_get_aligment+0x1c>
8e000346:	0803      	mov r0,0x40
8e000348:	02e0      	b 8e00034c <bj_get_aligment+0x1c>
8e00034a:	0403      	mov r0,0x20
8e00034c:	194f 0402 	rts

8e000350 <bj_memset>:
8e000350:	2716      	lsl r1,r1,0x18
8e000352:	2706      	lsr r1,r1,0x18
8e000354:	6003      	mov r3,0x0
8e000356:	8d3f 200a 	sub ip,r3,r2
8e00035a:	0400      	beq 8e000362 <bj_memset+0x12>
8e00035c:	2191      	strb r1,[r0,r3]
8e00035e:	6c93      	add r3,r3,1
8e000360:	fbe0      	b 8e000356 <bj_memset+0x6>
8e000362:	194f 0402 	rts
8e000366:	01a2      	nop

8e000368 <bj_memcpy>:
8e000368:	6003      	mov r3,0x0
8e00036a:	8d3f 200a 	sub ip,r3,r2
8e00036e:	0700      	beq 8e00037c <bj_memcpy+0x14>
8e000370:	8589 2000 	ldrb ip,[r1,+r3]
8e000374:	8199 2000 	strb ip,[r0,+r3]
8e000378:	6c93      	add r3,r3,1
8e00037a:	f8e0      	b 8e00036a <bj_memcpy+0x2>
8e00037c:	194f 0402 	rts

8e000380 <bj_memmove>:
8e000380:	20bf 400a 	sub r17,r0,r1
8e000384:	04ef 4002 	mov r16,r1
8e000388:	88ef 2002 	mov ip,r2
8e00038c:	0620      	bgtu 8e000398 <bj_memmove+0x18>
8e00038e:	6d0b 0032 	mov r3,0x368
8e000392:	600b 18e2 	movt r3,0x8e00
8e000396:	0d42      	jr r3
8e000398:	011a      	add r0,r0,r2
8e00039a:	28e2      	mov r1,r2
8e00039c:	413a      	sub r2,r0,r2
8e00039e:	2793      	add r1,r1,-1
8e0003a0:	67b3      	sub r3,r1,-1
8e0003a2:	0500      	beq 8e0003ac <bj_memmove+0x2c>
8e0003a4:	6089 0800 	ldrb r3,[r16,+r1]
8e0003a8:	6891      	strb r3,[r2,r1]
8e0003aa:	fae0      	b 8e00039e <bj_memmove+0x1e>
8e0003ac:	023f 008a 	sub r0,r0,ip
8e0003b0:	194f 0402 	rts

8e0003b4 <bj_strlen>:
8e0003b4:	f75c 2700 	str fp,[sp],-0x6
8e0003b8:	f4ef 2402 	mov fp,sp
8e0003bc:	1ddc 0400 	str r0,[fp,+0x3]
8e0003c0:	0003      	mov r0,0x0
8e0003c2:	1dbc 0401 	strh r0,[fp,+0xb]
8e0003c6:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0003ca:	2033      	sub r1,r0,0
8e0003cc:	0810      	bne 8e0003dc <bj_strlen+0x28>
8e0003ce:	0003      	mov r0,0x0
8e0003d0:	10e0      	b 8e0003f0 <bj_strlen+0x3c>
8e0003d2:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0003d6:	0093      	add r0,r0,1
8e0003d8:	1dbc 0401 	strh r0,[fp,+0xb]
8e0003dc:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0003e0:	3dcc 0400 	ldr r1,[fp,+0x3]
8e0003e4:	041a      	add r0,r1,r0
8e0003e6:	0004      	ldrb r0,[r0]
8e0003e8:	2033      	sub r1,r0,0
8e0003ea:	f410      	bne 8e0003d2 <bj_strlen+0x1e>
8e0003ec:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0003f0:	f74c 2400 	ldr fp,[sp,+0x6]
8e0003f4:	b41b 2403 	add sp,sp,24
8e0003f8:	194f 0402 	rts

8e0003fc <bj_extnl_ram_load_data_fill>:
8e0003fc:	f75c 2700 	str fp,[sp],-0x6
8e000400:	f4ef 2402 	mov fp,sp
8e000404:	1ddc 0400 	str r0,[fp,+0x3]
8e000408:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00040c:	02c4      	ldr r0,[r0,0x5]
8e00040e:	1edc 0400 	str r0,[fp,+0x5]
8e000412:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000416:	2344      	ldr r1,[r0,0x6]
8e000418:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00041c:	243a      	sub r1,r1,r0
8e00041e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000422:	215c 0001 	str r1,[r0,+0xa]
8e000426:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00042a:	23c4      	ldr r1,[r0,0x7]
8e00042c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000430:	243a      	sub r1,r1,r0
8e000432:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000436:	21dc 0001 	str r1,[r0,+0xb]
8e00043a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00043e:	204c 0001 	ldr r1,[r0,+0x8]
8e000442:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000446:	243a      	sub r1,r1,r0
8e000448:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00044c:	225c 0001 	str r1,[r0,+0xc]
8e000450:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000454:	20cc 0001 	ldr r1,[r0,+0x9]
8e000458:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00045c:	243a      	sub r1,r1,r0
8e00045e:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000462:	22dc 0001 	str r1,[r0,+0xd]
8e000466:	01a2      	nop
8e000468:	f74c 2400 	ldr fp,[sp,+0x6]
8e00046c:	b41b 2403 	add sp,sp,24
8e000470:	194f 0402 	rts

8e000474 <bjk_glb_init>:
8e000474:	d77c 2700 	strd lr,[sp],-0x6
8e000478:	95dc 0401 	str r4,[sp,+0xb]
8e00047c:	f41b 2406 	add fp,sp,48
8e000480:	8112      	movfs r4,config
8e000482:	158b 00a2 	mov r0,0xaac
8e000486:	000b 18e2 	movt r0,0x8e00
8e00048a:	9fcb 2ff2 	mov ip,0xfffe
8e00048e:	9e2b 3ff2 	movt ip,0xfff1
8e000492:	0152      	jalr r0
8e000494:	1c8b 0252 	mov r0,0x25e4
8e000498:	000b 18e2 	movt r0,0x8e00
8e00049c:	9fcb 2ff2 	mov ip,0xfffe
8e0004a0:	9e2b 3ff2 	movt ip,0xfff1
8e0004a4:	0152      	jalr r0
8e0004a6:	070b 0092 	mov r0,0x938
8e0004aa:	000b 18e2 	movt r0,0x8e00
8e0004ae:	9fcb 2ff2 	mov ip,0xfffe
8e0004b2:	9e2b 3ff2 	movt ip,0xfff1
8e0004b6:	0152      	jalr r0
8e0004b8:	1ddc 0500 	str r0,[fp,-0x3]
8e0004bc:	590b 0012 	mov r2,0x1c8
8e0004c0:	2003      	mov r1,0x0
8e0004c2:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0004c6:	6a0b 0032 	mov r3,0x350
8e0004ca:	600b 18e2 	movt r3,0x8e00
8e0004ce:	9fcb 2ff2 	mov ip,0xfffe
8e0004d2:	9e2b 3ff2 	movt ip,0xfff1
8e0004d6:	0d52      	jalr r3
8e0004d8:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0004dc:	2003      	mov r1,0x0
8e0004de:	2054      	str r1,[r0]
8e0004e0:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0004e4:	2003      	mov r1,0x0
8e0004e6:	20d4      	str r1,[r0,0x1]
8e0004e8:	100b 0032 	mov r0,0x380
8e0004ec:	000b 1002 	movt r0,0x0
8e0004f0:	1e5c 0500 	str r0,[fp,-0x4]
8e0004f4:	1e4c 0500 	ldr r0,[fp,-0x4]
8e0004f8:	1cdc 0501 	str r0,[fp,-0x9]
8e0004fc:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000500:	2403      	mov r1,0x20
8e000502:	2034      	strh r1,[r0]
8e000504:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000508:	2103      	mov r1,0x8
8e00050a:	20b4      	strh r1,[r0,0x1]
8e00050c:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000510:	2083      	mov r1,0x4
8e000512:	2134      	strh r1,[r0,0x2]
8e000514:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000518:	2043      	mov r1,0x2
8e00051a:	2314      	strb r1,[r0,0x6]
8e00051c:	000b 0002 	mov r0,0x0
8e000520:	000b 18f2 	movt r0,0x8f00
8e000524:	2044      	ldr r1,[r0]
8e000526:	1bab 0cc2 	mov r0,0xccdd
8e00052a:	176b 1aa2 	movt r0,0xaabb
8e00052e:	443a      	sub r2,r1,r0
8e000530:	1200      	beq 8e000554 <bjk_glb_init+0xe0>
8e000532:	0e8b 0042 	mov r0,0x474
8e000536:	000b 18e2 	movt r0,0x8e00
8e00053a:	3e0b 0262 	mov r1,0x26f0
8e00053e:	200b 18e2 	movt r1,0x8e00
8e000542:	4e0b 0092 	mov r2,0x970
8e000546:	400b 18e2 	movt r2,0x8e00
8e00054a:	9fcb 2ff2 	mov ip,0xfffe
8e00054e:	9e2b 3ff2 	movt ip,0xfff1
8e000552:	0952      	jalr r2
8e000554:	000b 0002 	mov r0,0x0
8e000558:	000b 18f2 	movt r0,0x8f00
8e00055c:	200b 0002 	mov r1,0x0
8e000560:	200b 18f2 	movt r1,0x8f00
8e000564:	21d4      	str r1,[r0,0x3]
8e000566:	0003      	mov r0,0x0
8e000568:	1cbc 0501 	strh r0,[fp,-0x9]
8e00056c:	051f 0032 	movfs r0,coreid
8e000570:	1cbc 0501 	strh r0,[fp,-0x9]
8e000574:	1cac 0501 	ldrh r0,[fp,-0x9]
8e000578:	1dbc 0501 	strh r0,[fp,-0xb]
8e00057c:	4103      	mov r2,0x8
8e00057e:	2003      	mov r1,0x0
8e000580:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000584:	6a0b 0032 	mov r3,0x350
8e000588:	600b 18e2 	movt r3,0x8e00
8e00058c:	9fcb 2ff2 	mov ip,0xfffe
8e000590:	9e2b 3ff2 	movt ip,0xfff1
8e000594:	0d52      	jalr r3
8e000596:	5e4c 0500 	ldr r2,[fp,-0x4]
8e00059a:	000b 0002 	mov r0,0x0
8e00059e:	000b 18f2 	movt r0,0x8f00
8e0005a2:	01e4      	ldrd r0,[r0,0x3]
8e0005a4:	0874      	strd r0,[r2]
8e0005a6:	1dac 0501 	ldrh r0,[fp,-0xb]
8e0005aa:	00c6      	lsr r0,r0,0x6
8e0005ac:	000b 1002 	movt r0,0x0
8e0005b0:	20e2      	mov r1,r0
8e0005b2:	07e3      	mov r0,0x3f
8e0005b4:	045a      	and r0,r1,r0
8e0005b6:	300b 0032 	mov r1,0x380
8e0005ba:	200b 1002 	movt r1,0x0
8e0005be:	2424      	ldrh r1,[r1]
8e0005c0:	00ba      	sub r0,r0,r1
8e0005c2:	40e2      	mov r2,r0
8e0005c4:	400b 1002 	movt r2,0x0
8e0005c8:	100b 0032 	mov r0,0x380
8e0005cc:	000b 1002 	movt r0,0x0
8e0005d0:	0304      	ldrb r0,[r0,0x6]
8e0005d2:	20e2      	mov r1,r0
8e0005d4:	0023      	mov r0,0x1
8e0005d6:	00aa      	lsl r0,r0,r1
8e0005d8:	20e2      	mov r1,r0
8e0005da:	200b 1002 	movt r1,0x0
8e0005de:	600b 0002 	mov r3,0x0
8e0005e2:	610b 1002 	movt r3,0x8
8e0005e6:	0512      	movfs r0,status
8e0005e8:	0392      	gid
8e0005ea:	811f 2002 	movfs ip,config
8e0005ee:	91ff 240a 	orr ip,ip,r3
8e0005f2:	810f 2002 	movts config,ip
8e0005f6:	0192      	gie
8e0005f8:	21eb 4ef2 	mov r17,0xef0f
8e0005fc:	3feb 5ff2 	movt r17,0xffff
8e000600:	6512      	movfs r3,status
8e000602:	6c0a      	eor r3,r3,r0
8e000604:	6cdf 010a 	and r3,r3,r17
8e000608:	6c0a      	eor r3,r3,r0
8e00060a:	6502      	movts status,r3
8e00060c:	08a7      	fmul r0,r2,r1
8e00060e:	20e2      	mov r1,r0
8e000610:	200b 1002 	movt r1,0x0
8e000614:	5dac 0501 	ldrh r2,[fp,-0xb]
8e000618:	07e3      	mov r0,0x3f
8e00061a:	085a      	and r0,r2,r0
8e00061c:	40e2      	mov r2,r0
8e00061e:	400b 1002 	movt r2,0x0
8e000622:	100b 0032 	mov r0,0x380
8e000626:	000b 1002 	movt r0,0x0
8e00062a:	00a4      	ldrh r0,[r0,0x1]
8e00062c:	083a      	sub r0,r2,r0
8e00062e:	000b 1002 	movt r0,0x0
8e000632:	041a      	add r0,r1,r0
8e000634:	1e3c 0501 	strh r0,[fp,-0xc]
8e000638:	0f8b 0032 	mov r0,0x37c
8e00063c:	000b 1002 	movt r0,0x0
8e000640:	0044      	ldr r0,[r0]
8e000642:	001b 0001 	add r0,r0,8
8e000646:	1fdc 0500 	str r0,[fp,-0x7]
8e00064a:	4703      	mov r2,0x38
8e00064c:	2003      	mov r1,0x0
8e00064e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000652:	0a0b 4032 	mov r16,0x350
8e000656:	000b 58e2 	movt r16,0x8e00
8e00065a:	9fcb 2ff2 	mov ip,0xfffe
8e00065e:	9e2b 3ff2 	movt ip,0xfff1
8e000662:	6512      	movfs r3,status
8e000664:	0392      	gid
8e000666:	211f 4002 	movfs r17,config
8e00066a:	260f 480a 	eor r17,r17,r4
8e00066e:	265f 488a 	and r17,r17,ip
8e000672:	260f 480a 	eor r17,r17,r4
8e000676:	210f 4002 	movts config,r17
8e00067a:	0192      	gie
8e00067c:	81eb 2ef2 	mov ip,0xef0f
8e000680:	9feb 3ff2 	movt ip,0xffff
8e000684:	251f 4002 	movfs r17,status
8e000688:	258f 480a 	eor r17,r17,r3
8e00068c:	265f 488a 	and r17,r17,ip
8e000690:	258f 480a 	eor r17,r17,r3
8e000694:	250f 4002 	movts status,r17
8e000698:	015f 0802 	jalr r16
8e00069c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006a0:	3bab 0cc2 	mov r1,0xccdd
8e0006a4:	376b 1aa2 	movt r1,0xaabb
8e0006a8:	2054      	str r1,[r0]
8e0006aa:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006ae:	2003      	mov r1,0x0
8e0006b0:	20d4      	str r1,[r0,0x1]
8e0006b2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006b6:	39ab 0ab2 	mov r1,0xabcd
8e0006ba:	312b 1672 	movt r1,0x6789
8e0006be:	225c 0001 	str r1,[r0,+0xc]
8e0006c2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006c6:	3dac 0501 	ldrh r1,[fp,-0xb]
8e0006ca:	213c 0001 	strh r1,[r0,+0xa]
8e0006ce:	1dac 0501 	ldrh r0,[fp,-0xb]
8e0006d2:	00c6      	lsr r0,r0,0x6
8e0006d4:	20e2      	mov r1,r0
8e0006d6:	200b 1002 	movt r1,0x0
8e0006da:	07e3      	mov r0,0x3f
8e0006dc:	045a      	and r0,r1,r0
8e0006de:	20e2      	mov r1,r0
8e0006e0:	200b 1002 	movt r1,0x0
8e0006e4:	100b 0032 	mov r0,0x380
8e0006e8:	000b 1002 	movt r0,0x0
8e0006ec:	0024      	ldrh r0,[r0]
8e0006ee:	043a      	sub r0,r1,r0
8e0006f0:	20e2      	mov r1,r0
8e0006f2:	200b 1002 	movt r1,0x0
8e0006f6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0006fa:	223c 0001 	strh r1,[r0,+0xc]
8e0006fe:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000702:	07e3      	mov r0,0x3f
8e000704:	045a      	and r0,r1,r0
8e000706:	20e2      	mov r1,r0
8e000708:	200b 1002 	movt r1,0x0
8e00070c:	100b 0032 	mov r0,0x380
8e000710:	000b 1002 	movt r0,0x0
8e000714:	00a4      	ldrh r0,[r0,0x1]
8e000716:	043a      	sub r0,r1,r0
8e000718:	20e2      	mov r1,r0
8e00071a:	200b 1002 	movt r1,0x0
8e00071e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000722:	22bc 0001 	strh r1,[r0,+0xd]
8e000726:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00072a:	3e2c 0501 	ldrh r1,[fp,-0xc]
8e00072e:	21bc 0001 	strh r1,[r0,+0xb]
8e000732:	1e2c 0501 	ldrh r0,[fp,-0xc]
8e000736:	23bb 0001 	sub r1,r0,15
8e00073a:	c928 0000 	bgtu 8e0008cc <bjk_glb_init+0x458>
8e00073e:	1e2c 0501 	ldrh r0,[fp,-0xc]
8e000742:	0113      	add r0,r0,2
8e000744:	2096      	lsl r1,r0,0x4
8e000746:	000b 0002 	mov r0,0x0
8e00074a:	000b 18f2 	movt r0,0x8f00
8e00074e:	241a      	add r1,r1,r0
8e000750:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000754:	2054      	str r1,[r0]
8e000756:	5e2c 0501 	ldrh r2,[fp,-0xc]
8e00075a:	600b 0002 	mov r3,0x0
8e00075e:	600b 18f2 	movt r3,0x8f00
8e000762:	28e2      	mov r1,r2
8e000764:	0496      	lsl r0,r1,0x4
8e000766:	20e2      	mov r1,r0
8e000768:	0456      	lsl r0,r1,0x2
8e00076a:	00ba      	sub r0,r0,r1
8e00076c:	013a      	sub r0,r0,r2
8e00076e:	0076      	lsl r0,r0,0x3
8e000770:	0c1a      	add r0,r3,r0
8e000772:	001b 0024 	add r0,r0,288
8e000776:	2044      	ldr r1,[r0]
8e000778:	1bab 0cc2 	mov r0,0xccdd
8e00077c:	176b 1aa2 	movt r0,0xaabb
8e000780:	443a      	sub r2,r1,r0
8e000782:	1200      	beq 8e0007a6 <bjk_glb_init+0x332>
8e000784:	0e8b 0042 	mov r0,0x474
8e000788:	000b 18e2 	movt r0,0x8e00
8e00078c:	210b 0272 	mov r1,0x2708
8e000790:	200b 18e2 	movt r1,0x8e00
8e000794:	4e0b 0092 	mov r2,0x970
8e000798:	400b 18e2 	movt r2,0x8e00
8e00079c:	9fcb 2ff2 	mov ip,0xfffe
8e0007a0:	9e2b 3ff2 	movt ip,0xfff1
8e0007a4:	0952      	jalr r2
8e0007a6:	5e2c 0501 	ldrh r2,[fp,-0xc]
8e0007aa:	28e2      	mov r1,r2
8e0007ac:	0496      	lsl r0,r1,0x4
8e0007ae:	20e2      	mov r1,r0
8e0007b0:	0456      	lsl r0,r1,0x2
8e0007b2:	00ba      	sub r0,r0,r1
8e0007b4:	013a      	sub r0,r0,r2
8e0007b6:	0076      	lsl r0,r0,0x3
8e0007b8:	201b 0024 	add r1,r0,288
8e0007bc:	000b 0002 	mov r0,0x0
8e0007c0:	000b 18f2 	movt r0,0x8f00
8e0007c4:	041a      	add r0,r1,r0
8e0007c6:	1c5c 0501 	str r0,[fp,-0x8]
8e0007ca:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0007ce:	201b 0001 	add r1,r0,8
8e0007d2:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0007d6:	20d4      	str r1,[r0,0x1]
8e0007d8:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0007dc:	80cc 2000 	ldr ip,[r0,+0x1]
8e0007e0:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0007e4:	001b 0009 	add r0,r0,72
8e0007e8:	6003      	mov r3,0x0
8e0007ea:	40e2      	mov r2,r0
8e0007ec:	258b 0012 	mov r1,0x12c
8e0007f0:	10ef 0402 	mov r0,ip
8e0007f4:	0e0b 40b2 	mov r16,0xb70
8e0007f8:	000b 58e2 	movt r16,0x8e00
8e0007fc:	9fcb 2ff2 	mov ip,0xfffe
8e000800:	9e2b 3ff2 	movt ip,0xfff1
8e000804:	015f 0802 	jalr r16
8e000808:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00080c:	0044      	ldr r0,[r0]
8e00080e:	2044      	ldr r1,[r0]
8e000810:	1bab 0cc2 	mov r0,0xccdd
8e000814:	176b 1aa2 	movt r0,0xaabb
8e000818:	643a      	sub r3,r1,r0
8e00081a:	1200      	beq 8e00083e <bjk_glb_init+0x3ca>
8e00081c:	0e8b 0042 	mov r0,0x474
8e000820:	000b 18e2 	movt r0,0x8e00
8e000824:	240b 0272 	mov r1,0x2720
8e000828:	200b 18e2 	movt r1,0x8e00
8e00082c:	4e0b 0092 	mov r2,0x970
8e000830:	400b 18e2 	movt r2,0x8e00
8e000834:	9fcb 2ff2 	mov ip,0xfffe
8e000838:	9e2b 3ff2 	movt ip,0xfff1
8e00083c:	0952      	jalr r2
8e00083e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000842:	0044      	ldr r0,[r0]
8e000844:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000848:	2134      	strh r1,[r0,0x2]
8e00084a:	01a2      	nop
8e00084c:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000850:	0044      	ldr r0,[r0]
8e000852:	0124      	ldrh r0,[r0,0x2]
8e000854:	3dac 0501 	ldrh r1,[fp,-0xb]
8e000858:	843f 200a 	sub ip,r1,r0
8e00085c:	f810      	bne 8e00084c <bjk_glb_init+0x3d8>
8e00085e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000862:	0044      	ldr r0,[r0]
8e000864:	3fcc 0500 	ldr r1,[fp,-0x7]
8e000868:	2154      	str r1,[r0,0x2]
8e00086a:	01a2      	nop
8e00086c:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000870:	0044      	ldr r0,[r0]
8e000872:	2144      	ldr r1,[r0,0x2]
8e000874:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000878:	243f 400a 	sub r17,r1,r0
8e00087c:	f810      	bne 8e00086c <bjk_glb_init+0x3f8>
8e00087e:	0423      	mov r0,0x21
8e000880:	1d9c 0502 	strb r0,[fp,-0x13]
8e000884:	0f8b 0032 	mov r0,0x37c
8e000888:	000b 1002 	movt r0,0x0
8e00088c:	0044      	ldr r0,[r0]
8e00088e:	0044      	ldr r0,[r0]
8e000890:	1d5c 0501 	str r0,[fp,-0xa]
8e000894:	1d4c 0501 	ldr r0,[fp,-0xa]
8e000898:	2033      	sub r1,r0,0
8e00089a:	0d00      	beq 8e0008b4 <bjk_glb_init+0x440>
8e00089c:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0008a0:	3d8c 0502 	ldrb r1,[fp,-0x13]
8e0008a4:	2314      	strb r1,[r0,0x6]
8e0008a6:	1d4c 0501 	ldr r0,[fp,-0xa]
8e0008aa:	0304      	ldrb r0,[r0,0x6]
8e0008ac:	3d8c 0502 	ldrb r1,[fp,-0x13]
8e0008b0:	443a      	sub r2,r1,r0
8e0008b2:	fa10      	bne 8e0008a6 <bjk_glb_init+0x432>
8e0008b4:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0008b8:	0044      	ldr r0,[r0]
8e0008ba:	2003      	mov r1,0x0
8e0008bc:	2394      	strb r1,[r0,0x7]
8e0008be:	01a2      	nop
8e0008c0:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0008c4:	0044      	ldr r0,[r0]
8e0008c6:	0384      	ldrb r0,[r0,0x7]
8e0008c8:	6033      	sub r3,r0,0
8e0008ca:	fb10      	bne 8e0008c0 <bjk_glb_init+0x44c>
8e0008cc:	01a2      	nop
8e0008ce:	9fcb 2ff2 	mov ip,0xfffe
8e0008d2:	9e2b 3ff2 	movt ip,0xfff1
8e0008d6:	d76c 2400 	ldrd lr,[sp,+0x6]
8e0008da:	95cc 0401 	ldr r4,[sp,+0xb]
8e0008de:	b41b 2406 	add sp,sp,48
8e0008e2:	194f 0402 	rts
8e0008e6:	01a2      	nop

8e0008e8 <bjk_glb_finish>:
8e0008e8:	f65c 2700 	str fp,[sp],-0x4
8e0008ec:	f4ef 2402 	mov fp,sp
8e0008f0:	1e2b 0ff2 	mov r0,0xfff1
8e0008f4:	1f9c 0401 	strb r0,[fp,+0xf]
8e0008f8:	0f8b 0032 	mov r0,0x37c
8e0008fc:	000b 1002 	movt r0,0x0
8e000900:	0044      	ldr r0,[r0]
8e000902:	0044      	ldr r0,[r0]
8e000904:	1d5c 0400 	str r0,[fp,+0x2]
8e000908:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00090c:	2033      	sub r1,r0,0
8e00090e:	0d00      	beq 8e000928 <bjk_glb_finish+0x40>
8e000910:	1d4c 0400 	ldr r0,[fp,+0x2]
8e000914:	3f8c 0401 	ldrb r1,[fp,+0xf]
8e000918:	2314      	strb r1,[r0,0x6]
8e00091a:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00091e:	0304      	ldrb r0,[r0,0x6]
8e000920:	3f8c 0401 	ldrb r1,[fp,+0xf]
8e000924:	443a      	sub r2,r1,r0
8e000926:	fa10      	bne 8e00091a <bjk_glb_finish+0x32>
8e000928:	01a2      	nop
8e00092a:	f64c 2400 	ldr fp,[sp,+0x4]
8e00092e:	b41b 2402 	add sp,sp,16
8e000932:	194f 0402 	rts
8e000936:	01a2      	nop

8e000938 <bjk_get_first_glb_sys>:
8e000938:	d4fc 2700 	strd lr,[sp],-0x1
8e00093c:	f41b 2401 	add fp,sp,8
8e000940:	190b 0012 	mov r0,0x1c8
8e000944:	350b 01f2 	mov r1,0x1fa8
8e000948:	200b 18e2 	movt r1,0x8e00
8e00094c:	0552      	jalr r1
8e00094e:	20e2      	mov r1,r0
8e000950:	0f8b 0032 	mov r0,0x37c
8e000954:	000b 1002 	movt r0,0x0
8e000958:	2054      	str r1,[r0]
8e00095a:	0f8b 0032 	mov r0,0x37c
8e00095e:	000b 1002 	movt r0,0x0
8e000962:	0044      	ldr r0,[r0]
8e000964:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000968:	b41b 2401 	add sp,sp,8
8e00096c:	194f 0402 	rts

8e000970 <bjk_abort>:
8e000970:	d67c 2700 	strd lr,[sp],-0x4
8e000974:	f41b 2404 	add fp,sp,32
8e000978:	1edc 0500 	str r0,[fp,-0x5]
8e00097c:	3f5c 0500 	str r1,[fp,-0x6]
8e000980:	1feb 0ff2 	mov r0,0xffff
8e000984:	1feb 1ff2 	movt r0,0xffff
8e000988:	1cbc 0500 	strh r0,[fp,-0x1]
8e00098c:	0003      	mov r0,0x0
8e00098e:	1d5c 0500 	str r0,[fp,-0x2]
8e000992:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000996:	2033      	sub r1,r0,0
8e000998:	0d00      	beq 8e0009b2 <bjk_abort+0x42>
8e00099a:	0283      	mov r0,0x14
8e00099c:	1cbc 0500 	strh r0,[fp,-0x1]
8e0009a0:	0f8b 0032 	mov r0,0x37c
8e0009a4:	000b 1002 	movt r0,0x0
8e0009a8:	0044      	ldr r0,[r0]
8e0009aa:	001b 002e 	add r0,r0,368
8e0009ae:	1d5c 0500 	str r0,[fp,-0x2]
8e0009b2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0009b6:	4033      	sub r2,r0,0
8e0009b8:	1200      	beq 8e0009dc <bjk_abort+0x6c>
8e0009ba:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0009be:	0216      	lsl r0,r0,0x10
8e0009c0:	020e      	asr r0,r0,0x10
8e0009c2:	2033      	sub r1,r0,0
8e0009c4:	0c90      	blte 8e0009dc <bjk_abort+0x6c>
8e0009c6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0009ca:	0216      	lsl r0,r0,0x10
8e0009cc:	020e      	asr r0,r0,0x10
8e0009ce:	3d4c 0500 	ldr r1,[fp,-0x2]
8e0009d2:	430b 0142 	mov r2,0x1418
8e0009d6:	400b 18e2 	movt r2,0x8e00
8e0009da:	0952      	jalr r2
8e0009dc:	0f8b 0032 	mov r0,0x37c
8e0009e0:	000b 1002 	movt r0,0x0
8e0009e4:	0044      	ldr r0,[r0]
8e0009e6:	001b 0001 	add r0,r0,8
8e0009ea:	1ddc 0500 	str r0,[fp,-0x3]
8e0009ee:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0009f2:	3ecc 0500 	ldr r1,[fp,-0x5]
8e0009f6:	21d4      	str r1,[r0,0x3]
8e0009f8:	0f8b 0032 	mov r0,0x37c
8e0009fc:	000b 1002 	movt r0,0x0
8e000a00:	0044      	ldr r0,[r0]
8e000a02:	0044      	ldr r0,[r0]
8e000a04:	1e5c 0500 	str r0,[fp,-0x4]
8e000a08:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a0c:	4033      	sub r2,r0,0
8e000a0e:	1600      	beq 8e000a3a <bjk_abort+0xca>
8e000a10:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a14:	2044      	ldr r1,[r0]
8e000a16:	1bab 0cc2 	mov r0,0xccdd
8e000a1a:	176b 1aa2 	movt r0,0xaabb
8e000a1e:	443a      	sub r2,r1,r0
8e000a20:	0d10      	bne 8e000a3a <bjk_abort+0xca>
8e000a22:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a26:	3e2b 0ff2 	mov r1,0xfff1
8e000a2a:	2314      	strb r1,[r0,0x6]
8e000a2c:	01a2      	nop
8e000a2e:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000a32:	0304      	ldrb r0,[r0,0x6]
8e000a34:	20bb 001e 	sub r1,r0,241
8e000a38:	fb10      	bne 8e000a2e <bjk_abort+0xbe>
8e000a3a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000a3e:	c0ef e002 	mov r62,r0
8e000a42:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000a46:	e0ef e002 	mov r63,r0
8e000a4a:	0392      	gid
8e000a4c:	0fe2      	trap 0x3
8e000a4e:	0912      	movfs r0,pc
8e000a50:	0152      	jalr r0
8e000a52:	01a2      	nop
8e000a54:	d66c 2400 	ldrd lr,[sp,+0x4]
8e000a58:	b41b 2404 	add sp,sp,32
8e000a5c:	194f 0402 	rts

8e000a60 <abort>:
8e000a60:	d57c 2700 	strd lr,[sp],-0x2
8e000a64:	f41b 2402 	add fp,sp,16

8e000a68 <ck2_abort>:
8e000a68:	ad0b e0a2 	mov r61,0xa68
8e000a6c:	a00b f8e2 	movt r61,0x8e00
8e000a70:	14ef 1c02 	mov r0,r61
8e000a74:	1cdc 0500 	str r0,[fp,-0x1]
8e000a78:	2e0b 0272 	mov r1,0x2770
8e000a7c:	200b 18e2 	movt r1,0x8e00
8e000a80:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000a84:	4e0b 0092 	mov r2,0x970
8e000a88:	400b 18e2 	movt r2,0x8e00
8e000a8c:	0952      	jalr r2
8e000a8e:	0c0b 00a2 	mov r0,0xa60
8e000a92:	000b 18e2 	movt r0,0x8e00
8e000a96:	3c0b 0262 	mov r1,0x26e0
8e000a9a:	200b 18e2 	movt r1,0x8e00
8e000a9e:	4e0b 0092 	mov r2,0x970
8e000aa2:	400b 18e2 	movt r2,0x8e00
8e000aa6:	0952      	jalr r2
8e000aa8:	00e0      	b 8e000aa8 <ck2_abort+0x40>
8e000aaa:	01a2      	nop

8e000aac <bjk_set_irq0_handler>:
8e000aac:	f65c 2700 	str fp,[sp],-0x4
8e000ab0:	f4ef 2402 	mov fp,sp
8e000ab4:	0003      	mov r0,0x0
8e000ab6:	1ddc 0400 	str r0,[fp,+0x3]
8e000aba:	008b 0022 	mov r0,0x204
8e000abe:	000b 1002 	movt r0,0x0
8e000ac2:	0026      	lsr r0,r0,0x1
8e000ac4:	2116      	lsl r1,r0,0x8
8e000ac6:	1d03      	mov r0,0xe8
8e000ac8:	247a      	orr r1,r1,r0
8e000aca:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000ace:	2054      	str r1,[r0]
8e000ad0:	01a2      	nop
8e000ad2:	f64c 2400 	ldr fp,[sp,+0x4]
8e000ad6:	b41b 2402 	add sp,sp,16
8e000ada:	194f 0402 	rts
8e000ade:	01a2      	nop

8e000ae0 <bj_host_init>:
8e000ae0:	d4fc 2700 	strd lr,[sp],-0x1
8e000ae4:	f41b 2401 	add fp,sp,8
8e000ae8:	1c0b 00a2 	mov r0,0xae0
8e000aec:	000b 18e2 	movt r0,0x8e00
8e000af0:	330b 0262 	mov r1,0x2698
8e000af4:	200b 18e2 	movt r1,0x8e00
8e000af8:	4e0b 0092 	mov r2,0x970
8e000afc:	400b 18e2 	movt r2,0x8e00
8e000b00:	0952      	jalr r2
8e000b02:	01a2      	nop
8e000b04:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b08:	b41b 2401 	add sp,sp,8
8e000b0c:	194f 0402 	rts

8e000b10 <bj_host_run>:
8e000b10:	d4fc 2700 	strd lr,[sp],-0x1
8e000b14:	f41b 2401 	add fp,sp,8
8e000b18:	020b 00b2 	mov r0,0xb10
8e000b1c:	000b 18e2 	movt r0,0x8e00
8e000b20:	360b 0262 	mov r1,0x26b0
8e000b24:	200b 18e2 	movt r1,0x8e00
8e000b28:	4e0b 0092 	mov r2,0x970
8e000b2c:	400b 18e2 	movt r2,0x8e00
8e000b30:	0952      	jalr r2
8e000b32:	01a2      	nop
8e000b34:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b38:	b41b 2401 	add sp,sp,8
8e000b3c:	194f 0402 	rts

8e000b40 <bj_host_finish>:
8e000b40:	d4fc 2700 	strd lr,[sp],-0x1
8e000b44:	f41b 2401 	add fp,sp,8
8e000b48:	080b 00b2 	mov r0,0xb40
8e000b4c:	000b 18e2 	movt r0,0x8e00
8e000b50:	390b 0262 	mov r1,0x26c8
8e000b54:	200b 18e2 	movt r1,0x8e00
8e000b58:	4e0b 0092 	mov r2,0x970
8e000b5c:	400b 18e2 	movt r2,0x8e00
8e000b60:	0952      	jalr r2
8e000b62:	01a2      	nop
8e000b64:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000b68:	b41b 2401 	add sp,sp,8
8e000b6c:	194f 0402 	rts

8e000b70 <bj_rr_init>:
8e000b70:	d5fc 2700 	strd lr,[sp],-0x3
8e000b74:	f41b 2403 	add fp,sp,24
8e000b78:	1cdc 0500 	str r0,[fp,-0x1]
8e000b7c:	04e2      	mov r0,r1
8e000b7e:	5ddc 0500 	str r2,[fp,-0x3]
8e000b82:	2ce2      	mov r1,r3
8e000b84:	1e3c 0500 	strh r0,[fp,-0x4]
8e000b88:	04e2      	mov r0,r1
8e000b8a:	1c1c 0502 	strb r0,[fp,-0x10]
8e000b8e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000b92:	2033      	sub r1,r0,0
8e000b94:	8408 0000 	beq 8e000c9c <bj_rr_init+0x12c>
8e000b98:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000b9c:	3bab 0cc2 	mov r1,0xccdd
8e000ba0:	376b 1aa2 	movt r1,0xaabb
8e000ba4:	2054      	str r1,[r0]
8e000ba6:	01a2      	nop
8e000ba8:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000bac:	2044      	ldr r1,[r0]
8e000bae:	1bab 0cc2 	mov r0,0xccdd
8e000bb2:	176b 1aa2 	movt r0,0xaabb
8e000bb6:	443a      	sub r2,r1,r0
8e000bb8:	f810      	bne 8e000ba8 <bj_rr_init+0x38>
8e000bba:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000bbe:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000bc2:	20d4      	str r1,[r0,0x1]
8e000bc4:	01a2      	nop
8e000bc6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000bca:	20c4      	ldr r1,[r0,0x1]
8e000bcc:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000bd0:	443a      	sub r2,r1,r0
8e000bd2:	fa10      	bne 8e000bc6 <bj_rr_init+0x56>
8e000bd4:	1c0c 0502 	ldrb r0,[fp,-0x10]
8e000bd8:	2033      	sub r1,r0,0
8e000bda:	0d00      	beq 8e000bf4 <bj_rr_init+0x84>
8e000bdc:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000be0:	00c4      	ldr r0,[r0,0x1]
8e000be2:	3e2c 0500 	ldrh r1,[fp,-0x4]
8e000be6:	44e2      	mov r2,r1
8e000be8:	2003      	mov r1,0x0
8e000bea:	6a0b 0032 	mov r3,0x350
8e000bee:	600b 18e2 	movt r3,0x8e00
8e000bf2:	0d52      	jalr r3
8e000bf4:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000bf8:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000bfc:	241a      	add r1,r1,r0
8e000bfe:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c02:	2154      	str r1,[r0,0x2]
8e000c04:	01a2      	nop
8e000c06:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c0a:	2144      	ldr r1,[r0,0x2]
8e000c0c:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000c10:	5dcc 0500 	ldr r2,[fp,-0x3]
8e000c14:	081a      	add r0,r2,r0
8e000c16:	443a      	sub r2,r1,r0
8e000c18:	f710      	bne 8e000c06 <bj_rr_init+0x96>
8e000c1a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c1e:	20c4      	ldr r1,[r0,0x1]
8e000c20:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c24:	21d4      	str r1,[r0,0x3]
8e000c26:	01a2      	nop
8e000c28:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c2c:	21c4      	ldr r1,[r0,0x3]
8e000c2e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c32:	00c4      	ldr r0,[r0,0x1]
8e000c34:	443a      	sub r2,r1,r0
8e000c36:	f910      	bne 8e000c28 <bj_rr_init+0xb8>
8e000c38:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c3c:	20c4      	ldr r1,[r0,0x1]
8e000c3e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c42:	2254      	str r1,[r0,0x4]
8e000c44:	01a2      	nop
8e000c46:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c4a:	2244      	ldr r1,[r0,0x4]
8e000c4c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c50:	00c4      	ldr r0,[r0,0x1]
8e000c52:	443a      	sub r2,r1,r0
8e000c54:	f910      	bne 8e000c46 <bj_rr_init+0xd6>
8e000c56:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c5a:	2003      	mov r1,0x0
8e000c5c:	22d4      	str r1,[r0,0x5]
8e000c5e:	01a2      	nop
8e000c60:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c64:	02c4      	ldr r0,[r0,0x5]
8e000c66:	2033      	sub r1,r0,0
8e000c68:	fc10      	bne 8e000c60 <bj_rr_init+0xf0>
8e000c6a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c6e:	2003      	mov r1,0x0
8e000c70:	201c 0003 	strb r1,[r0,+0x18]
8e000c74:	01a2      	nop
8e000c76:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c7a:	000c 0003 	ldrb r0,[r0,+0x18]
8e000c7e:	4033      	sub r2,r0,0
8e000c80:	fb10      	bne 8e000c76 <bj_rr_init+0x106>
8e000c82:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c86:	2003      	mov r1,0x0
8e000c88:	209c 0003 	strb r1,[r0,+0x19]
8e000c8c:	01a2      	nop
8e000c8e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000c92:	008c 0003 	ldrb r0,[r0,+0x19]
8e000c96:	2033      	sub r1,r0,0
8e000c98:	fb10      	bne 8e000c8e <bj_rr_init+0x11e>
8e000c9a:	02e0      	b 8e000c9e <bj_rr_init+0x12e>
8e000c9c:	01a2      	nop
8e000c9e:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e000ca2:	b41b 2403 	add sp,sp,24
8e000ca6:	194f 0402 	rts
8e000caa:	01a2      	nop

8e000cac <bj_rr_read_obj>:
8e000cac:	d77c 2700 	strd lr,[sp],-0x6
8e000cb0:	f41b 2406 	add fp,sp,48
8e000cb4:	1fdc 0500 	str r0,[fp,-0x7]
8e000cb8:	04e2      	mov r0,r1
8e000cba:	5cdc 0501 	str r2,[fp,-0x9]
8e000cbe:	1c3c 0502 	strh r0,[fp,-0x10]
8e000cc2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000cc6:	2033      	sub r1,r0,0
8e000cc8:	0410      	bne 8e000cd0 <bj_rr_read_obj+0x24>
8e000cca:	0003      	mov r0,0x0
8e000ccc:	e7e8 0000 	b 8e000e9a <bj_rr_read_obj+0x1ee>
8e000cd0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000cd4:	0244      	ldr r0,[r0,0x4]
8e000cd6:	1edc 0500 	str r0,[fp,-0x5]
8e000cda:	1e1b 04fd 	add r0,fp,-20
8e000cde:	20e2      	mov r1,r0
8e000ce0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ce4:	5a0b 0122 	mov r2,0x12d0
8e000ce8:	400b 18e2 	movt r2,0x8e00
8e000cec:	0952      	jalr r2
8e000cee:	1ebc 0500 	strh r0,[fp,-0x5]
8e000cf2:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000cf6:	4033      	sub r2,r0,0
8e000cf8:	1310      	bne 8e000d1e <bj_rr_read_obj+0x72>
8e000cfa:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000cfe:	3feb 0ff2 	mov r1,0xffff
8e000d02:	209c 0003 	strb r1,[r0,+0x19]
8e000d06:	01a2      	nop
8e000d08:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d0c:	008c 0003 	ldrb r0,[r0,+0x19]
8e000d10:	0316      	lsl r0,r0,0x18
8e000d12:	030e      	asr r0,r0,0x18
8e000d14:	23b3      	sub r1,r0,-1
8e000d16:	f910      	bne 8e000d08 <bj_rr_read_obj+0x5c>
8e000d18:	0003      	mov r0,0x0
8e000d1a:	c0e8 0000 	b 8e000e9a <bj_rr_read_obj+0x1ee>
8e000d1e:	3eac 0500 	ldrh r1,[fp,-0x5]
8e000d22:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000d26:	443a      	sub r2,r1,r0
8e000d28:	1340      	blteu 8e000d4e <bj_rr_read_obj+0xa2>
8e000d2a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d2e:	3fcb 0ff2 	mov r1,0xfffe
8e000d32:	209c 0003 	strb r1,[r0,+0x19]
8e000d36:	01a2      	nop
8e000d38:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d3c:	008c 0003 	ldrb r0,[r0,+0x19]
8e000d40:	0316      	lsl r0,r0,0x18
8e000d42:	030e      	asr r0,r0,0x18
8e000d44:	2333      	sub r1,r0,-2
8e000d46:	f910      	bne 8e000d38 <bj_rr_read_obj+0x8c>
8e000d48:	0003      	mov r0,0x0
8e000d4a:	a8e8 0000 	b 8e000e9a <bj_rr_read_obj+0x1ee>
8e000d4e:	3eac 0500 	ldrh r1,[fp,-0x5]
8e000d52:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d56:	0144      	ldr r0,[r0,0x2]
8e000d58:	40e2      	mov r2,r0
8e000d5a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d5e:	00c4      	ldr r0,[r0,0x1]
8e000d60:	083a      	sub r0,r2,r0
8e000d62:	443a      	sub r2,r1,r0
8e000d64:	1390      	blte 8e000d8a <bj_rr_read_obj+0xde>
8e000d66:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d6a:	3fab 0ff2 	mov r1,0xfffd
8e000d6e:	209c 0003 	strb r1,[r0,+0x19]
8e000d72:	01a2      	nop
8e000d74:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d78:	008c 0003 	ldrb r0,[r0,+0x19]
8e000d7c:	0316      	lsl r0,r0,0x18
8e000d7e:	030e      	asr r0,r0,0x18
8e000d80:	22b3      	sub r1,r0,-3
8e000d82:	f910      	bne 8e000d74 <bj_rr_read_obj+0xc8>
8e000d84:	0003      	mov r0,0x0
8e000d86:	8ae8 0000 	b 8e000e9a <bj_rr_read_obj+0x1ee>
8e000d8a:	0003      	mov r0,0x0
8e000d8c:	1cbc 0500 	strh r0,[fp,-0x1]
8e000d90:	20e0      	b 8e000dd0 <bj_rr_read_obj+0x124>
8e000d92:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000d96:	2144      	ldr r1,[r0,0x2]
8e000d98:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000d9c:	443a      	sub r2,r1,r0
8e000d9e:	0610      	bne 8e000daa <bj_rr_read_obj+0xfe>
8e000da0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000da4:	00c4      	ldr r0,[r0,0x1]
8e000da6:	1edc 0500 	str r0,[fp,-0x5]
8e000daa:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000dae:	3ccc 0501 	ldr r1,[fp,-0x9]
8e000db2:	041a      	add r0,r1,r0
8e000db4:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000db8:	2404      	ldrb r1,[r1]
8e000dba:	2014      	strb r1,[r0]
8e000dbc:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000dc0:	0093      	add r0,r0,1
8e000dc2:	1edc 0500 	str r0,[fp,-0x5]
8e000dc6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000dca:	0093      	add r0,r0,1
8e000dcc:	1cbc 0500 	strh r0,[fp,-0x1]
8e000dd0:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000dd4:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000dd8:	443a      	sub r2,r1,r0
8e000dda:	dc50      	bltu 8e000d92 <bj_rr_read_obj+0xe6>
8e000ddc:	1e1b 04fd 	add r0,fp,-20
8e000de0:	20e2      	mov r1,r0
8e000de2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000de6:	5a0b 0122 	mov r2,0x12d0
8e000dea:	400b 18e2 	movt r2,0x8e00
8e000dee:	0952      	jalr r2
8e000df0:	1f3c 0500 	strh r0,[fp,-0x6]
8e000df4:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000df8:	20e2      	mov r1,r0
8e000dfa:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000dfe:	420b 0112 	mov r2,0x1110
8e000e02:	400b 18e2 	movt r2,0x8e00
8e000e06:	0952      	jalr r2
8e000e08:	1fbc 0500 	strh r0,[fp,-0x7]
8e000e0c:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000e10:	1fac 0500 	ldrh r0,[fp,-0x7]
8e000e14:	443a      	sub r2,r1,r0
8e000e16:	1200      	beq 8e000e3a <bj_rr_read_obj+0x18e>
8e000e18:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e1c:	3f8b 0ff2 	mov r1,0xfffc
8e000e20:	209c 0003 	strb r1,[r0,+0x19]
8e000e24:	01a2      	nop
8e000e26:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e2a:	008c 0003 	ldrb r0,[r0,+0x19]
8e000e2e:	0316      	lsl r0,r0,0x18
8e000e30:	030e      	asr r0,r0,0x18
8e000e32:	2233      	sub r1,r0,-4
8e000e34:	f910      	bne 8e000e26 <bj_rr_read_obj+0x17a>
8e000e36:	0003      	mov r0,0x0
8e000e38:	31e0      	b 8e000e9a <bj_rr_read_obj+0x1ee>
8e000e3a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e3e:	0244      	ldr r0,[r0,0x4]
8e000e40:	1d5c 0500 	str r0,[fp,-0x2]
8e000e44:	16e0      	b 8e000e70 <bj_rr_read_obj+0x1c4>
8e000e46:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e4a:	2144      	ldr r1,[r0,0x2]
8e000e4c:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000e50:	443a      	sub r2,r1,r0
8e000e52:	0610      	bne 8e000e5e <bj_rr_read_obj+0x1b2>
8e000e54:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e58:	00c4      	ldr r0,[r0,0x1]
8e000e5a:	1d5c 0500 	str r0,[fp,-0x2]
8e000e5e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000e62:	2003      	mov r1,0x0
8e000e64:	2014      	strb r1,[r0]
8e000e66:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000e6a:	0093      	add r0,r0,1
8e000e6c:	1d5c 0500 	str r0,[fp,-0x2]
8e000e70:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000e74:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000e78:	443a      	sub r2,r1,r0
8e000e7a:	e610      	bne 8e000e46 <bj_rr_read_obj+0x19a>
8e000e7c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e80:	3d4c 0500 	ldr r1,[fp,-0x2]
8e000e84:	2254      	str r1,[r0,0x4]
8e000e86:	01a2      	nop
8e000e88:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000e8c:	2244      	ldr r1,[r0,0x4]
8e000e8e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000e92:	443a      	sub r2,r1,r0
8e000e94:	fa10      	bne 8e000e88 <bj_rr_read_obj+0x1dc>
8e000e96:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000e9a:	d76c 2400 	ldrd lr,[sp,+0x6]
8e000e9e:	b41b 2406 	add sp,sp,48
8e000ea2:	194f 0402 	rts
8e000ea6:	01a2      	nop

8e000ea8 <bj_rr_write_obj>:
8e000ea8:	d77c 2700 	strd lr,[sp],-0x6
8e000eac:	f41b 2406 	add fp,sp,48
8e000eb0:	1fdc 0500 	str r0,[fp,-0x7]
8e000eb4:	04e2      	mov r0,r1
8e000eb6:	5cdc 0501 	str r2,[fp,-0x9]
8e000eba:	1c3c 0502 	strh r0,[fp,-0x10]
8e000ebe:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ec2:	2033      	sub r1,r0,0
8e000ec4:	0410      	bne 8e000ecc <bj_rr_write_obj+0x24>
8e000ec6:	0003      	mov r0,0x0
8e000ec8:	1de8 0001 	b 8e001102 <bj_rr_write_obj+0x25a>
8e000ecc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ed0:	02c4      	ldr r0,[r0,0x5]
8e000ed2:	1e5c 0500 	str r0,[fp,-0x4]
8e000ed6:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000eda:	1cbc 0501 	strh r0,[fp,-0x9]
8e000ede:	3cac 0501 	ldrh r1,[fp,-0x9]
8e000ee2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ee6:	0144      	ldr r0,[r0,0x2]
8e000ee8:	40e2      	mov r2,r0
8e000eea:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000eee:	00c4      	ldr r0,[r0,0x1]
8e000ef0:	083a      	sub r0,r2,r0
8e000ef2:	0213      	add r0,r0,-4
8e000ef4:	443a      	sub r2,r1,r0
8e000ef6:	2540      	blteu 8e000f40 <bj_rr_write_obj+0x98>
8e000ef8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000efc:	3feb 0ff2 	mov r1,0xffff
8e000f00:	201c 0003 	strb r1,[r0,+0x18]
8e000f04:	01a2      	nop
8e000f06:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f0a:	000c 0003 	ldrb r0,[r0,+0x18]
8e000f0e:	0316      	lsl r0,r0,0x18
8e000f10:	030e      	asr r0,r0,0x18
8e000f12:	23b3      	sub r1,r0,-1
8e000f14:	f910      	bne 8e000f06 <bj_rr_write_obj+0x5e>
8e000f16:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f1a:	0093      	add r0,r0,1
8e000f1c:	1e5c 0500 	str r0,[fp,-0x4]
8e000f20:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f24:	3e4c 0500 	ldr r1,[fp,-0x4]
8e000f28:	22d4      	str r1,[r0,0x5]
8e000f2a:	01a2      	nop
8e000f2c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f30:	22c4      	ldr r1,[r0,0x5]
8e000f32:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f36:	443a      	sub r2,r1,r0
8e000f38:	fa10      	bne 8e000f2c <bj_rr_write_obj+0x84>
8e000f3a:	0003      	mov r0,0x0
8e000f3c:	e3e8 0000 	b 8e001102 <bj_rr_write_obj+0x25a>
8e000f40:	1cac 0501 	ldrh r0,[fp,-0x9]
8e000f44:	2033      	sub r1,r0,0
8e000f46:	2510      	bne 8e000f90 <bj_rr_write_obj+0xe8>
8e000f48:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f4c:	3fcb 0ff2 	mov r1,0xfffe
8e000f50:	201c 0003 	strb r1,[r0,+0x18]
8e000f54:	01a2      	nop
8e000f56:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f5a:	000c 0003 	ldrb r0,[r0,+0x18]
8e000f5e:	0316      	lsl r0,r0,0x18
8e000f60:	030e      	asr r0,r0,0x18
8e000f62:	4333      	sub r2,r0,-2
8e000f64:	f910      	bne 8e000f56 <bj_rr_write_obj+0xae>
8e000f66:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f6a:	0093      	add r0,r0,1
8e000f6c:	1e5c 0500 	str r0,[fp,-0x4]
8e000f70:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f74:	3e4c 0500 	ldr r1,[fp,-0x4]
8e000f78:	22d4      	str r1,[r0,0x5]
8e000f7a:	01a2      	nop
8e000f7c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000f80:	22c4      	ldr r1,[r0,0x5]
8e000f82:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000f86:	443a      	sub r2,r1,r0
8e000f88:	fa10      	bne 8e000f7c <bj_rr_write_obj+0xd4>
8e000f8a:	0003      	mov r0,0x0
8e000f8c:	bbe8 0000 	b 8e001102 <bj_rr_write_obj+0x25a>
8e000f90:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e000f94:	031b 0000 	add r0,r0,6
8e000f98:	1cbc 0500 	strh r0,[fp,-0x1]
8e000f9c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fa0:	01c4      	ldr r0,[r0,0x3]
8e000fa2:	1d5c 0500 	str r0,[fp,-0x2]
8e000fa6:	20e0      	b 8e000fe6 <bj_rr_write_obj+0x13e>
8e000fa8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fac:	2144      	ldr r1,[r0,0x2]
8e000fae:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000fb2:	443a      	sub r2,r1,r0
8e000fb4:	0610      	bne 8e000fc0 <bj_rr_write_obj+0x118>
8e000fb6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000fba:	00c4      	ldr r0,[r0,0x1]
8e000fbc:	1d5c 0500 	str r0,[fp,-0x2]
8e000fc0:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000fc4:	0004      	ldrb r0,[r0]
8e000fc6:	2033      	sub r1,r0,0
8e000fc8:	0500      	beq 8e000fd2 <bj_rr_write_obj+0x12a>
8e000fca:	0003      	mov r0,0x0
8e000fcc:	1d5c 0500 	str r0,[fp,-0x2]
8e000fd0:	0fe0      	b 8e000fee <bj_rr_write_obj+0x146>
8e000fd2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000fd6:	0093      	add r0,r0,1
8e000fd8:	1d5c 0500 	str r0,[fp,-0x2]
8e000fdc:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000fe0:	0393      	add r0,r0,-1
8e000fe2:	1cbc 0500 	strh r0,[fp,-0x1]
8e000fe6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000fea:	4033      	sub r2,r0,0
8e000fec:	de10      	bne 8e000fa8 <bj_rr_write_obj+0x100>
8e000fee:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000ff2:	2033      	sub r1,r0,0
8e000ff4:	2410      	bne 8e00103c <bj_rr_write_obj+0x194>
8e000ff6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e000ffa:	3fab 0ff2 	mov r1,0xfffd
8e000ffe:	201c 0003 	strb r1,[r0,+0x18]
8e001002:	01a2      	nop
8e001004:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001008:	000c 0003 	ldrb r0,[r0,+0x18]
8e00100c:	0316      	lsl r0,r0,0x18
8e00100e:	030e      	asr r0,r0,0x18
8e001010:	42b3      	sub r2,r0,-3
8e001012:	f910      	bne 8e001004 <bj_rr_write_obj+0x15c>
8e001014:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001018:	0093      	add r0,r0,1
8e00101a:	1e5c 0500 	str r0,[fp,-0x4]
8e00101e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001022:	3e4c 0500 	ldr r1,[fp,-0x4]
8e001026:	22d4      	str r1,[r0,0x5]
8e001028:	01a2      	nop
8e00102a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00102e:	22c4      	ldr r1,[r0,0x5]
8e001030:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001034:	443a      	sub r2,r1,r0
8e001036:	fa10      	bne 8e00102a <bj_rr_write_obj+0x182>
8e001038:	0003      	mov r0,0x0
8e00103a:	64e0      	b 8e001102 <bj_rr_write_obj+0x25a>
8e00103c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001040:	01c4      	ldr r0,[r0,0x3]
8e001042:	1f5c 0500 	str r0,[fp,-0x6]
8e001046:	3c2c 0502 	ldrh r1,[fp,-0x10]
8e00104a:	1c1b 04fd 	add r0,fp,-24
8e00104e:	44e2      	mov r2,r1
8e001050:	20e2      	mov r1,r0
8e001052:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001056:	6e8b 0132 	mov r3,0x1374
8e00105a:	600b 18e2 	movt r3,0x8e00
8e00105e:	0d52      	jalr r3
8e001060:	0003      	mov r0,0x0
8e001062:	1ebc 0500 	strh r0,[fp,-0x5]
8e001066:	20e0      	b 8e0010a6 <bj_rr_write_obj+0x1fe>
8e001068:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00106c:	2144      	ldr r1,[r0,0x2]
8e00106e:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001072:	443a      	sub r2,r1,r0
8e001074:	0610      	bne 8e001080 <bj_rr_write_obj+0x1d8>
8e001076:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00107a:	00c4      	ldr r0,[r0,0x1]
8e00107c:	1f5c 0500 	str r0,[fp,-0x6]
8e001080:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001084:	3eac 0500 	ldrh r1,[fp,-0x5]
8e001088:	5ccc 0501 	ldr r2,[fp,-0x9]
8e00108c:	289a      	add r1,r2,r1
8e00108e:	2404      	ldrb r1,[r1]
8e001090:	2014      	strb r1,[r0]
8e001092:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001096:	0093      	add r0,r0,1
8e001098:	1f5c 0500 	str r0,[fp,-0x6]
8e00109c:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0010a0:	0093      	add r0,r0,1
8e0010a2:	1ebc 0500 	strh r0,[fp,-0x5]
8e0010a6:	3eac 0500 	ldrh r1,[fp,-0x5]
8e0010aa:	1cac 0501 	ldrh r0,[fp,-0x9]
8e0010ae:	443a      	sub r2,r1,r0
8e0010b0:	dc50      	bltu 8e001068 <bj_rr_write_obj+0x1c0>
8e0010b2:	1cac 0501 	ldrh r0,[fp,-0x9]
8e0010b6:	20e2      	mov r1,r0
8e0010b8:	1ccc 0501 	ldr r0,[fp,-0x9]
8e0010bc:	420b 0112 	mov r2,0x1110
8e0010c0:	400b 18e2 	movt r2,0x8e00
8e0010c4:	0952      	jalr r2
8e0010c6:	1d3c 0501 	strh r0,[fp,-0xa]
8e0010ca:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e0010ce:	1c1b 04fd 	add r0,fp,-24
8e0010d2:	44e2      	mov r2,r1
8e0010d4:	20e2      	mov r1,r0
8e0010d6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010da:	6e8b 0132 	mov r3,0x1374
8e0010de:	600b 18e2 	movt r3,0x8e00
8e0010e2:	0d52      	jalr r3
8e0010e4:	3f4c 0500 	ldr r1,[fp,-0x6]
8e0010e8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010ec:	21d4      	str r1,[r0,0x3]
8e0010ee:	01a2      	nop
8e0010f0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010f4:	21c4      	ldr r1,[r0,0x3]
8e0010f6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0010fa:	443a      	sub r2,r1,r0
8e0010fc:	fa10      	bne 8e0010f0 <bj_rr_write_obj+0x248>
8e0010fe:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001102:	d76c 2400 	ldrd lr,[sp,+0x6]
8e001106:	b41b 2406 	add sp,sp,48
8e00110a:	194f 0402 	rts
8e00110e:	01a2      	nop

8e001110 <bj_crc16>:
8e001110:	f75c 2700 	str fp,[sp],-0x6
8e001114:	f4ef 2402 	mov fp,sp
8e001118:	1ddc 0400 	str r0,[fp,+0x3]
8e00111c:	04e2      	mov r0,r1
8e00111e:	1e3c 0400 	strh r0,[fp,+0x4]
8e001122:	1feb 0ff2 	mov r0,0xffff
8e001126:	1feb 1ff2 	movt r0,0xffff
8e00112a:	1cbc 0401 	strh r0,[fp,+0x9]
8e00112e:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001132:	2033      	sub r1,r0,0
8e001134:	0b10      	bne 8e00114a <bj_crc16+0x3a>
8e001136:	3cac 0401 	ldrh r1,[fp,+0x9]
8e00113a:	1feb 0ff2 	mov r0,0xffff
8e00113e:	1feb 1ff2 	movt r0,0xffff
8e001142:	040a      	eor r0,r1,r0
8e001144:	000b 1002 	movt r0,0x0
8e001148:	65e0      	b 8e001212 <bj_crc16+0x102>
8e00114a:	0003      	mov r0,0x0
8e00114c:	1f9c 0402 	strb r0,[fp,+0x17]
8e001150:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001154:	2093      	add r1,r0,1
8e001156:	3ddc 0400 	str r1,[fp,+0x3]
8e00115a:	0004      	ldrb r0,[r0]
8e00115c:	1d3c 0401 	strh r0,[fp,+0xa]
8e001160:	2ae0      	b 8e0011b4 <bj_crc16+0xa4>
8e001162:	3cac 0401 	ldrh r1,[fp,+0x9]
8e001166:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e00116a:	040a      	eor r0,r1,r0
8e00116c:	000b 1002 	movt r0,0x0
8e001170:	20e2      	mov r1,r0
8e001172:	0023      	mov r0,0x1
8e001174:	045a      	and r0,r1,r0
8e001176:	2033      	sub r1,r0,0
8e001178:	0f00      	beq 8e001196 <bj_crc16+0x86>
8e00117a:	1cac 0401 	ldrh r0,[fp,+0x9]
8e00117e:	0026      	lsr r0,r0,0x1
8e001180:	20e2      	mov r1,r0
8e001182:	200b 1002 	movt r1,0x0
8e001186:	010b 0842 	mov r0,0x8408
8e00118a:	1feb 1ff2 	movt r0,0xffff
8e00118e:	040a      	eor r0,r1,r0
8e001190:	1cbc 0401 	strh r0,[fp,+0x9]
8e001194:	06e0      	b 8e0011a0 <bj_crc16+0x90>
8e001196:	1cac 0401 	ldrh r0,[fp,+0x9]
8e00119a:	0026      	lsr r0,r0,0x1
8e00119c:	1cbc 0401 	strh r0,[fp,+0x9]
8e0011a0:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e0011a4:	0093      	add r0,r0,1
8e0011a6:	1f9c 0402 	strb r0,[fp,+0x17]
8e0011aa:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0011ae:	0026      	lsr r0,r0,0x1
8e0011b0:	1d3c 0401 	strh r0,[fp,+0xa]
8e0011b4:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e0011b8:	23bb 0000 	sub r1,r0,7
8e0011bc:	d340      	blteu 8e001162 <bj_crc16+0x52>
8e0011be:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0011c2:	0393      	add r0,r0,-1
8e0011c4:	1e3c 0400 	strh r0,[fp,+0x4]
8e0011c8:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0011cc:	2033      	sub r1,r0,0
8e0011ce:	be10      	bne 8e00114a <bj_crc16+0x3a>
8e0011d0:	3cac 0401 	ldrh r1,[fp,+0x9]
8e0011d4:	1feb 0ff2 	mov r0,0xffff
8e0011d8:	1feb 1ff2 	movt r0,0xffff
8e0011dc:	040a      	eor r0,r1,r0
8e0011de:	1cbc 0401 	strh r0,[fp,+0x9]
8e0011e2:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0011e6:	1d3c 0401 	strh r0,[fp,+0xa]
8e0011ea:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0011ee:	0116      	lsl r0,r0,0x8
8e0011f0:	20e2      	mov r1,r0
8e0011f2:	200b 1002 	movt r1,0x0
8e0011f6:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0011fa:	0106      	lsr r0,r0,0x8
8e0011fc:	000b 1002 	movt r0,0x0
8e001200:	000b 1002 	movt r0,0x0
8e001204:	047a      	orr r0,r1,r0
8e001206:	000b 1002 	movt r0,0x0
8e00120a:	1cbc 0401 	strh r0,[fp,+0x9]
8e00120e:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001212:	f74c 2400 	ldr fp,[sp,+0x6]
8e001216:	b41b 2403 	add sp,sp,24
8e00121a:	194f 0402 	rts
8e00121e:	01a2      	nop

8e001220 <bj_get_v16_of_p8>:
8e001220:	f75c 2700 	str fp,[sp],-0x6
8e001224:	f4ef 2402 	mov fp,sp
8e001228:	1ddc 0400 	str r0,[fp,+0x3]
8e00122c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001230:	0093      	add r0,r0,1
8e001232:	0004      	ldrb r0,[r0]
8e001234:	1dbc 0401 	strh r0,[fp,+0xb]
8e001238:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00123c:	0116      	lsl r0,r0,0x8
8e00123e:	1dbc 0401 	strh r0,[fp,+0xb]
8e001242:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001246:	0004      	ldrb r0,[r0]
8e001248:	20e2      	mov r1,r0
8e00124a:	200b 1002 	movt r1,0x0
8e00124e:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001252:	047a      	orr r0,r1,r0
8e001254:	1dbc 0401 	strh r0,[fp,+0xb]
8e001258:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00125c:	f74c 2400 	ldr fp,[sp,+0x6]
8e001260:	b41b 2403 	add sp,sp,24
8e001264:	194f 0402 	rts

8e001268 <bj_set_v16_of_p8>:
8e001268:	f75c 2700 	str fp,[sp],-0x6
8e00126c:	f4ef 2402 	mov fp,sp
8e001270:	1ddc 0400 	str r0,[fp,+0x3]
8e001274:	04e2      	mov r0,r1
8e001276:	1e3c 0400 	strh r0,[fp,+0x4]
8e00127a:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e00127e:	1fe3      	mov r0,0xff
8e001280:	045a      	and r0,r1,r0
8e001282:	1dbc 0401 	strh r0,[fp,+0xb]
8e001286:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e00128a:	000b 0ff2 	mov r0,0xff00
8e00128e:	1feb 1ff2 	movt r0,0xffff
8e001292:	045a      	and r0,r1,r0
8e001294:	1d3c 0401 	strh r0,[fp,+0xa]
8e001298:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e00129c:	0106      	lsr r0,r0,0x8
8e00129e:	1d3c 0401 	strh r0,[fp,+0xa]
8e0012a2:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0012a6:	0093      	add r0,r0,1
8e0012a8:	3d2c 0401 	ldrh r1,[fp,+0xa]
8e0012ac:	2716      	lsl r1,r1,0x18
8e0012ae:	2706      	lsr r1,r1,0x18
8e0012b0:	2014      	strb r1,[r0]
8e0012b2:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0012b6:	2316      	lsl r1,r0,0x18
8e0012b8:	2706      	lsr r1,r1,0x18
8e0012ba:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0012be:	2014      	strb r1,[r0]
8e0012c0:	01a2      	nop
8e0012c2:	f74c 2400 	ldr fp,[sp,+0x6]
8e0012c6:	b41b 2403 	add sp,sp,24
8e0012ca:	194f 0402 	rts
8e0012ce:	01a2      	nop

8e0012d0 <bj_rr_get_v16>:
8e0012d0:	d67c 2700 	strd lr,[sp],-0x4
8e0012d4:	f41b 2404 	add fp,sp,32
8e0012d8:	1edc 0500 	str r0,[fp,-0x5]
8e0012dc:	3f5c 0500 	str r1,[fp,-0x6]
8e0012e0:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0012e4:	2033      	sub r1,r0,0
8e0012e6:	0310      	bne 8e0012ec <bj_rr_get_v16+0x1c>
8e0012e8:	0003      	mov r0,0x0
8e0012ea:	3ee0      	b 8e001366 <bj_rr_get_v16+0x96>
8e0012ec:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0012f0:	0044      	ldr r0,[r0]
8e0012f2:	1cdc 0500 	str r0,[fp,-0x1]
8e0012f6:	0003      	mov r0,0x0
8e0012f8:	1d5c 0500 	str r0,[fp,-0x2]
8e0012fc:	21e0      	b 8e00133e <bj_rr_get_v16+0x6e>
8e0012fe:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001302:	2144      	ldr r1,[r0,0x2]
8e001304:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001308:	443a      	sub r2,r1,r0
8e00130a:	0610      	bne 8e001316 <bj_rr_get_v16+0x46>
8e00130c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001310:	00c4      	ldr r0,[r0,0x1]
8e001312:	1cdc 0500 	str r0,[fp,-0x1]
8e001316:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00131a:	4004      	ldrb r2,[r0]
8e00131c:	3e1b 04fe 	add r1,fp,-12
8e001320:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001324:	041a      	add r0,r1,r0
8e001326:	28e2      	mov r1,r2
8e001328:	2014      	strb r1,[r0]
8e00132a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00132e:	0093      	add r0,r0,1
8e001330:	1cdc 0500 	str r0,[fp,-0x1]
8e001334:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001338:	0093      	add r0,r0,1
8e00133a:	1d5c 0500 	str r0,[fp,-0x2]
8e00133e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001342:	20b3      	sub r1,r0,1
8e001344:	dd90      	blte 8e0012fe <bj_rr_get_v16+0x2e>
8e001346:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00134a:	3ccc 0500 	ldr r1,[fp,-0x1]
8e00134e:	2054      	str r1,[r0]
8e001350:	1e1b 04fe 	add r0,fp,-12
8e001354:	240b 0122 	mov r1,0x1220
8e001358:	200b 18e2 	movt r1,0x8e00
8e00135c:	0552      	jalr r1
8e00135e:	1ebc 0500 	strh r0,[fp,-0x5]
8e001362:	1eac 0500 	ldrh r0,[fp,-0x5]
8e001366:	d66c 2400 	ldrd lr,[sp,+0x4]
8e00136a:	b41b 2404 	add sp,sp,32
8e00136e:	194f 0402 	rts
8e001372:	01a2      	nop

8e001374 <bj_rr_set_v16>:
8e001374:	d6fc 2700 	strd lr,[sp],-0x5
8e001378:	f41b 2405 	add fp,sp,40
8e00137c:	1edc 0500 	str r0,[fp,-0x5]
8e001380:	3f5c 0500 	str r1,[fp,-0x6]
8e001384:	08e2      	mov r0,r2
8e001386:	1f3c 0501 	strh r0,[fp,-0xe]
8e00138a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00138e:	2033      	sub r1,r0,0
8e001390:	3c00      	beq 8e001408 <bj_rr_set_v16+0x94>
8e001392:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001396:	0044      	ldr r0,[r0]
8e001398:	1cdc 0500 	str r0,[fp,-0x1]
8e00139c:	3f2c 0501 	ldrh r1,[fp,-0xe]
8e0013a0:	1f1b 04fe 	add r0,fp,-10
8e0013a4:	4d0b 0122 	mov r2,0x1268
8e0013a8:	400b 18e2 	movt r2,0x8e00
8e0013ac:	0952      	jalr r2
8e0013ae:	0003      	mov r0,0x0
8e0013b0:	1d5c 0500 	str r0,[fp,-0x2]
8e0013b4:	20e0      	b 8e0013f4 <bj_rr_set_v16+0x80>
8e0013b6:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0013ba:	2144      	ldr r1,[r0,0x2]
8e0013bc:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0013c0:	443a      	sub r2,r1,r0
8e0013c2:	0610      	bne 8e0013ce <bj_rr_set_v16+0x5a>
8e0013c4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0013c8:	00c4      	ldr r0,[r0,0x1]
8e0013ca:	1cdc 0500 	str r0,[fp,-0x1]
8e0013ce:	3f1b 04fe 	add r1,fp,-10
8e0013d2:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0013d6:	041a      	add r0,r1,r0
8e0013d8:	2004      	ldrb r1,[r0]
8e0013da:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0013de:	2014      	strb r1,[r0]
8e0013e0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0013e4:	0093      	add r0,r0,1
8e0013e6:	1cdc 0500 	str r0,[fp,-0x1]
8e0013ea:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0013ee:	0093      	add r0,r0,1
8e0013f0:	1d5c 0500 	str r0,[fp,-0x2]
8e0013f4:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0013f8:	20b3      	sub r1,r0,1
8e0013fa:	de90      	blte 8e0013b6 <bj_rr_set_v16+0x42>
8e0013fc:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001400:	3ccc 0500 	ldr r1,[fp,-0x1]
8e001404:	2054      	str r1,[r0]
8e001406:	02e0      	b 8e00140a <bj_rr_set_v16+0x96>
8e001408:	01a2      	nop
8e00140a:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e00140e:	b41b 2405 	add sp,sp,40
8e001412:	194f 0402 	rts
8e001416:	01a2      	nop

8e001418 <bjk_get_call_stack_trace>:
8e001418:	d57c 2701 	strd lr,[sp],-0xa
8e00141c:	f41b 240a 	add fp,sp,80
8e001420:	3d5c 0502 	str r1,[fp,-0x12]
8e001424:	1d3c 0504 	strh r0,[fp,-0x22]
8e001428:	1d4c 0502 	ldr r0,[fp,-0x12]
8e00142c:	2033      	sub r1,r0,0
8e00142e:	0410      	bne 8e001436 <bjk_get_call_stack_trace+0x1e>
8e001430:	0003      	mov r0,0x0
8e001432:	3be8 0001 	b 8e0016a8 <bjk_get_call_stack_trace+0x290>
8e001436:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e00143a:	0216      	lsl r0,r0,0x10
8e00143c:	020e      	asr r0,r0,0x10
8e00143e:	4033      	sub r2,r0,0
8e001440:	0460      	bgt 8e001448 <bjk_get_call_stack_trace+0x30>
8e001442:	0003      	mov r0,0x0
8e001444:	32e8 0001 	b 8e0016a8 <bjk_get_call_stack_trace+0x290>
8e001448:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e00144c:	0216      	lsl r0,r0,0x10
8e00144e:	020e      	asr r0,r0,0x10
8e001450:	0056      	lsl r0,r0,0x2
8e001452:	40e2      	mov r2,r0
8e001454:	2003      	mov r1,0x0
8e001456:	1d4c 0502 	ldr r0,[fp,-0x12]
8e00145a:	6a0b 0032 	mov r3,0x350
8e00145e:	600b 18e2 	movt r3,0x8e00
8e001462:	0d52      	jalr r3
8e001464:	0f8b 0032 	mov r0,0x37c
8e001468:	000b 1002 	movt r0,0x0
8e00146c:	0044      	ldr r0,[r0]
8e00146e:	3d4c 0502 	ldr r1,[fp,-0x12]
8e001472:	21d4      	str r1,[r0,0x3]
8e001474:	0003      	mov r0,0x0
8e001476:	1cdc 0500 	str r0,[fp,-0x1]
8e00147a:	0003      	mov r0,0x0
8e00147c:	1d5c 0500 	str r0,[fp,-0x2]
8e001480:	0003      	mov r0,0x0
8e001482:	1ddc 0500 	str r0,[fp,-0x3]
8e001486:	0003      	mov r0,0x0
8e001488:	1fbc 0500 	strh r0,[fp,-0x7]
8e00148c:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e001490:	0216      	lsl r0,r0,0x10
8e001492:	020e      	asr r0,r0,0x10
8e001494:	2033      	sub r1,r0,0
8e001496:	0460      	bgt 8e00149e <bjk_get_call_stack_trace+0x86>
8e001498:	0003      	mov r0,0x0
8e00149a:	07e8 0001 	b 8e0016a8 <bjk_get_call_stack_trace+0x290>
8e00149e:	0912      	movfs r0,pc
8e0014a0:	00e2      	mov r0,r0
8e0014a2:	1cdc 0500 	str r0,[fp,-0x1]
8e0014a6:	14ef 0402 	mov r0,sp
8e0014aa:	1d5c 0500 	str r0,[fp,-0x2]
8e0014ae:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0014b2:	298b 01a2 	mov r1,0x1a4c
8e0014b6:	200b 18e2 	movt r1,0x8e00
8e0014ba:	0552      	jalr r1
8e0014bc:	1ddc 0500 	str r0,[fp,-0x3]
8e0014c0:	c5e8 0000 	b 8e00164a <bjk_get_call_stack_trace+0x232>
8e0014c4:	3fac 0500 	ldrh r1,[fp,-0x7]
8e0014c8:	1d2c 0504 	ldrh r0,[fp,-0x22]
8e0014cc:	0216      	lsl r0,r0,0x10
8e0014ce:	020e      	asr r0,r0,0x10
8e0014d0:	443a      	sub r2,r1,r0
8e0014d2:	c208 0000 	beq 8e001656 <bjk_get_call_stack_trace+0x23e>
8e0014d6:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0014da:	2e8b 01b2 	mov r1,0x1b74
8e0014de:	200b 18e2 	movt r1,0x8e00
8e0014e2:	0552      	jalr r1
8e0014e4:	1c3c 0501 	strh r0,[fp,-0x8]
8e0014e8:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e0014ec:	2033      	sub r1,r0,0
8e0014ee:	b608 0000 	beq 8e00165a <bjk_get_call_stack_trace+0x242>
8e0014f2:	3c2c 0501 	ldrh r1,[fp,-0x8]
8e0014f6:	0023      	mov r0,0x1
8e0014f8:	045a      	and r0,r1,r0
8e0014fa:	000b 1002 	movt r0,0x0
8e0014fe:	4033      	sub r2,r0,0
8e001500:	0b00      	beq 8e001516 <bjk_get_call_stack_trace+0xfe>
8e001502:	030b 0142 	mov r0,0x1418
8e001506:	000b 18e2 	movt r0,0x8e00
8e00150a:	2003      	mov r1,0x0
8e00150c:	4e0b 0092 	mov r2,0x970
8e001510:	400b 18e2 	movt r2,0x8e00
8e001514:	0952      	jalr r2
8e001516:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00151a:	1edc 0500 	str r0,[fp,-0x5]
8e00151e:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001522:	3ecc 0500 	ldr r1,[fp,-0x5]
8e001526:	041a      	add r0,r1,r0
8e001528:	1edc 0500 	str r0,[fp,-0x5]
8e00152c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001530:	1d5c 0500 	str r0,[fp,-0x2]
8e001534:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001538:	0066      	lsr r0,r0,0x3
8e00153a:	1dbc 0501 	strh r0,[fp,-0xb]
8e00153e:	1dac 0501 	ldrh r0,[fp,-0xb]
8e001542:	0216      	lsl r0,r0,0x10
8e001544:	020e      	asr r0,r0,0x10
8e001546:	3f1b 04f8 	add r1,fp,-58
8e00154a:	3c5c 0501 	str r1,[fp,-0x8]
8e00154e:	1dbc 0503 	strh r0,[fp,-0x1b]
8e001552:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001556:	2f8b 0d42 	mov r1,0xd47c
8e00155a:	3feb 1ff2 	movt r1,0xffff
8e00155e:	2034      	strh r1,[r0]
8e001560:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001564:	0113      	add r0,r0,2
8e001566:	200b 0272 	mov r1,0x2700
8e00156a:	2034      	strh r1,[r0]
8e00156c:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001570:	0024      	ldrh r0,[r0]
8e001572:	20e2      	mov r1,r0
8e001574:	200b 1002 	movt r1,0x0
8e001578:	1dac 0503 	ldrh r0,[fp,-0x1b]
8e00157c:	40e2      	mov r2,r0
8e00157e:	00e3      	mov r0,0x7
8e001580:	085a      	and r0,r2,r0
8e001582:	00f6      	lsl r0,r0,0x7
8e001584:	000b 1002 	movt r0,0x0
8e001588:	047a      	orr r0,r1,r0
8e00158a:	000b 1002 	movt r0,0x0
8e00158e:	20e2      	mov r1,r0
8e001590:	200b 1002 	movt r1,0x0
8e001594:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001598:	2034      	strh r1,[r0]
8e00159a:	1c4c 0501 	ldr r0,[fp,-0x8]
8e00159e:	2113      	add r1,r0,2
8e0015a0:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0015a4:	0113      	add r0,r0,2
8e0015a6:	0024      	ldrh r0,[r0]
8e0015a8:	40e2      	mov r2,r0
8e0015aa:	400b 1002 	movt r2,0x0
8e0015ae:	1dac 0503 	ldrh r0,[fp,-0x1b]
8e0015b2:	0216      	lsl r0,r0,0x10
8e0015b4:	020e      	asr r0,r0,0x10
8e0015b6:	006e      	asr r0,r0,0x3
8e0015b8:	000b 1002 	movt r0,0x0
8e0015bc:	087a      	orr r0,r2,r0
8e0015be:	000b 1002 	movt r0,0x0
8e0015c2:	000b 1002 	movt r0,0x0
8e0015c6:	0434      	strh r0,[r1]
8e0015c8:	1f1b 04f8 	add r0,fp,-58
8e0015cc:	20e2      	mov r1,r0
8e0015ce:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0015d2:	570b 0182 	mov r2,0x18b8
8e0015d6:	400b 18e2 	movt r2,0x8e00
8e0015da:	0952      	jalr r2
8e0015dc:	1fdc 0500 	str r0,[fp,-0x7]
8e0015e0:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0015e4:	1e5c 0501 	str r0,[fp,-0xc]
8e0015e8:	1e4c 0501 	ldr r0,[fp,-0xc]
8e0015ec:	0113      	add r0,r0,2
8e0015ee:	0024      	ldrh r0,[r0]
8e0015f0:	1edc 0501 	str r0,[fp,-0xd]
8e0015f4:	1ecc 0501 	ldr r0,[fp,-0xd]
8e0015f8:	0216      	lsl r0,r0,0x10
8e0015fa:	1edc 0501 	str r0,[fp,-0xd]
8e0015fe:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001602:	0024      	ldrh r0,[r0]
8e001604:	20e2      	mov r1,r0
8e001606:	1ecc 0501 	ldr r0,[fp,-0xd]
8e00160a:	00fa      	orr r0,r0,r1
8e00160c:	1edc 0501 	str r0,[fp,-0xd]
8e001610:	1ecc 0501 	ldr r0,[fp,-0xd]
8e001614:	1cdc 0501 	str r0,[fp,-0x9]
8e001618:	1ccc 0501 	ldr r0,[fp,-0x9]
8e00161c:	1cdc 0500 	str r0,[fp,-0x1]
8e001620:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001624:	2093      	add r1,r0,1
8e001626:	3fbc 0500 	strh r1,[fp,-0x7]
8e00162a:	0056      	lsl r0,r0,0x2
8e00162c:	3d4c 0502 	ldr r1,[fp,-0x12]
8e001630:	041a      	add r0,r1,r0
8e001632:	3fcc 0500 	ldr r1,[fp,-0x7]
8e001636:	2054      	str r1,[r0]
8e001638:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00163c:	298b 01a2 	mov r1,0x1a4c
8e001640:	200b 18e2 	movt r1,0x8e00
8e001644:	0552      	jalr r1
8e001646:	1ddc 0500 	str r0,[fp,-0x3]
8e00164a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00164e:	2033      	sub r1,r0,0
8e001650:	3a18 ffff 	bne 8e0014c4 <bjk_get_call_stack_trace+0xac>
8e001654:	04e0      	b 8e00165c <bjk_get_call_stack_trace+0x244>
8e001656:	01a2      	nop
8e001658:	02e0      	b 8e00165c <bjk_get_call_stack_trace+0x244>
8e00165a:	01a2      	nop
8e00165c:	0f8b 0032 	mov r0,0x37c
8e001660:	000b 1002 	movt r0,0x0
8e001664:	0044      	ldr r0,[r0]
8e001666:	001b 0038 	add r0,r0,448
8e00166a:	1d5c 0501 	str r0,[fp,-0xa]
8e00166e:	1d4c 0501 	ldr r0,[fp,-0xa]
8e001672:	0024      	ldrh r0,[r0]
8e001674:	40bb 0008 	sub r2,r0,65
8e001678:	1610      	bne 8e0016a4 <bjk_get_call_stack_trace+0x28c>
8e00167a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00167e:	2d8b 0192 	mov r1,0x196c
8e001682:	200b 18e2 	movt r1,0x8e00
8e001686:	0552      	jalr r1
8e001688:	1ddc 0501 	str r0,[fp,-0xb]
8e00168c:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001690:	2093      	add r1,r0,1
8e001692:	3fbc 0500 	strh r1,[fp,-0x7]
8e001696:	0056      	lsl r0,r0,0x2
8e001698:	3d4c 0502 	ldr r1,[fp,-0x12]
8e00169c:	041a      	add r0,r1,r0
8e00169e:	3dcc 0501 	ldr r1,[fp,-0xb]
8e0016a2:	2054      	str r1,[r0]
8e0016a4:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0016a8:	d56c 2401 	ldrd lr,[sp,+0xa]
8e0016ac:	b41b 240a 	add sp,sp,80
8e0016b0:	194f 0402 	rts

8e0016b4 <bjk_wait_sync>:
8e0016b4:	d67c 2700 	strd lr,[sp],-0x4
8e0016b8:	f41b 2404 	add fp,sp,32
8e0016bc:	1ddc 0500 	str r0,[fp,-0x3]
8e0016c0:	04e2      	mov r0,r1
8e0016c2:	5edc 0500 	str r2,[fp,-0x5]
8e0016c6:	1c3c 0501 	strh r0,[fp,-0x8]
8e0016ca:	0f8b 0032 	mov r0,0x37c
8e0016ce:	000b 1002 	movt r0,0x0
8e0016d2:	0044      	ldr r0,[r0]
8e0016d4:	0044      	ldr r0,[r0]
8e0016d6:	1cdc 0500 	str r0,[fp,-0x1]
8e0016da:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0016de:	2033      	sub r1,r0,0
8e0016e0:	4c00      	beq 8e001778 <bjk_wait_sync+0xc4>
8e0016e2:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e0016e6:	0216      	lsl r0,r0,0x10
8e0016e8:	020e      	asr r0,r0,0x10
8e0016ea:	4033      	sub r2,r0,0
8e0016ec:	1090      	blte 8e00170c <bjk_wait_sync+0x58>
8e0016ee:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0016f2:	2033      	sub r1,r0,0
8e0016f4:	0c00      	beq 8e00170c <bjk_wait_sync+0x58>
8e0016f6:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e0016fa:	0216      	lsl r0,r0,0x10
8e0016fc:	020e      	asr r0,r0,0x10
8e0016fe:	3ecc 0500 	ldr r1,[fp,-0x5]
8e001702:	430b 0142 	mov r2,0x1418
8e001706:	400b 18e2 	movt r2,0x8e00
8e00170a:	0952      	jalr r2
8e00170c:	0003      	mov r0,0x0
8e00170e:	1dbc 0500 	strh r0,[fp,-0x3]
8e001712:	0392      	gid
8e001714:	051f 0402 	movfs r0,imask
8e001718:	1dbc 0500 	strh r0,[fp,-0x3]
8e00171c:	1fcb 0032 	mov r0,0x3fe
8e001720:	050f 0402 	movts imask,r0
8e001724:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001728:	4033      	sub r2,r0,0
8e00172a:	0410      	bne 8e001732 <bjk_wait_sync+0x7e>
8e00172c:	1543      	mov r0,0xaa
8e00172e:	1ddc 0500 	str r0,[fp,-0x3]
8e001732:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001736:	2316      	lsl r1,r0,0x18
8e001738:	2706      	lsr r1,r1,0x18
8e00173a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00173e:	2394      	strb r1,[r0,0x7]
8e001740:	01a2      	nop
8e001742:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001746:	0384      	ldrb r0,[r0,0x7]
8e001748:	20e2      	mov r1,r0
8e00174a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00174e:	443a      	sub r2,r1,r0
8e001750:	f910      	bne 8e001742 <bjk_wait_sync+0x8e>
8e001752:	0192      	gie
8e001754:	01b2      	idle
8e001756:	0392      	gid
8e001758:	1dac 0500 	ldrh r0,[fp,-0x3]
8e00175c:	050f 0402 	movts imask,r0
8e001760:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001764:	2003      	mov r1,0x0
8e001766:	2394      	strb r1,[r0,0x7]
8e001768:	01a2      	nop
8e00176a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00176e:	0384      	ldrb r0,[r0,0x7]
8e001770:	2033      	sub r1,r0,0
8e001772:	fc10      	bne 8e00176a <bjk_wait_sync+0xb6>
8e001774:	0192      	gie
8e001776:	02e0      	b 8e00177a <bjk_wait_sync+0xc6>
8e001778:	01a2      	nop
8e00177a:	d66c 2400 	ldrd lr,[sp,+0x4]
8e00177e:	b41b 2404 	add sp,sp,32
8e001782:	194f 0402 	rts
8e001786:	01a2      	nop

8e001788 <get_add_simm11>:
8e001788:	f75c 2700 	str fp,[sp],-0x6
8e00178c:	f4ef 2402 	mov fp,sp
8e001790:	1ddc 0400 	str r0,[fp,+0x3]
8e001794:	0003      	mov r0,0x0
8e001796:	1dbc 0401 	strh r0,[fp,+0xb]
8e00179a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00179e:	0113      	add r0,r0,2
8e0017a0:	0024      	ldrh r0,[r0]
8e0017a2:	20e2      	mov r1,r0
8e0017a4:	1fe3      	mov r0,0xff
8e0017a6:	045a      	and r0,r1,r0
8e0017a8:	0076      	lsl r0,r0,0x3
8e0017aa:	20e2      	mov r1,r0
8e0017ac:	200b 1002 	movt r1,0x0
8e0017b0:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0017b4:	0024      	ldrh r0,[r0]
8e0017b6:	40e2      	mov r2,r0
8e0017b8:	100b 0032 	mov r0,0x380
8e0017bc:	085a      	and r0,r2,r0
8e0017be:	00ee      	asr r0,r0,0x7
8e0017c0:	000b 1002 	movt r0,0x0
8e0017c4:	047a      	orr r0,r1,r0
8e0017c6:	000b 1002 	movt r0,0x0
8e0017ca:	1dbc 0401 	strh r0,[fp,+0xb]
8e0017ce:	1f1b 0402 	add r0,fp,22
8e0017d2:	0093      	add r0,r0,1
8e0017d4:	0004      	ldrb r0,[r0]
8e0017d6:	0046      	lsr r0,r0,0x2
8e0017d8:	0316      	lsl r0,r0,0x18
8e0017da:	0306      	lsr r0,r0,0x18
8e0017dc:	20e2      	mov r1,r0
8e0017de:	0023      	mov r0,0x1
8e0017e0:	045a      	and r0,r1,r0
8e0017e2:	2033      	sub r1,r0,0
8e0017e4:	1000      	beq 8e001804 <get_add_simm11+0x7c>
8e0017e6:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0017ea:	20e2      	mov r1,r0
8e0017ec:	200b 1002 	movt r1,0x0
8e0017f0:	000b 0f82 	mov r0,0xf800
8e0017f4:	1feb 1ff2 	movt r0,0xffff
8e0017f8:	040a      	eor r0,r1,r0
8e0017fa:	000b 1002 	movt r0,0x0
8e0017fe:	000b 1002 	movt r0,0x0
8e001802:	03e0      	b 8e001808 <get_add_simm11+0x80>
8e001804:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001808:	1dbc 0401 	strh r0,[fp,+0xb]
8e00180c:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001810:	0216      	lsl r0,r0,0x10
8e001812:	020e      	asr r0,r0,0x10
8e001814:	f74c 2400 	ldr fp,[sp,+0x6]
8e001818:	b41b 2403 	add sp,sp,24
8e00181c:	194f 0402 	rts

8e001820 <get_call_opcode>:
8e001820:	f65c 2700 	str fp,[sp],-0x4
8e001824:	f4ef 2402 	mov fp,sp
8e001828:	1ddc 0400 	str r0,[fp,+0x3]
8e00182c:	04e2      	mov r0,r1
8e00182e:	1e3c 0400 	strh r0,[fp,+0x4]
8e001832:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001836:	2f8b 0d42 	mov r1,0xd47c
8e00183a:	3feb 1ff2 	movt r1,0xffff
8e00183e:	2034      	strh r1,[r0]
8e001840:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001844:	0113      	add r0,r0,2
8e001846:	200b 0272 	mov r1,0x2700
8e00184a:	2034      	strh r1,[r0]
8e00184c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001850:	0024      	ldrh r0,[r0]
8e001852:	20e2      	mov r1,r0
8e001854:	200b 1002 	movt r1,0x0
8e001858:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e00185c:	40e2      	mov r2,r0
8e00185e:	00e3      	mov r0,0x7
8e001860:	085a      	and r0,r2,r0
8e001862:	00f6      	lsl r0,r0,0x7
8e001864:	000b 1002 	movt r0,0x0
8e001868:	047a      	orr r0,r1,r0
8e00186a:	000b 1002 	movt r0,0x0
8e00186e:	20e2      	mov r1,r0
8e001870:	200b 1002 	movt r1,0x0
8e001874:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001878:	2034      	strh r1,[r0]
8e00187a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00187e:	2113      	add r1,r0,2
8e001880:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001884:	0113      	add r0,r0,2
8e001886:	0024      	ldrh r0,[r0]
8e001888:	40e2      	mov r2,r0
8e00188a:	400b 1002 	movt r2,0x0
8e00188e:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001892:	0216      	lsl r0,r0,0x10
8e001894:	020e      	asr r0,r0,0x10
8e001896:	006e      	asr r0,r0,0x3
8e001898:	000b 1002 	movt r0,0x0
8e00189c:	087a      	orr r0,r2,r0
8e00189e:	000b 1002 	movt r0,0x0
8e0018a2:	000b 1002 	movt r0,0x0
8e0018a6:	0434      	strh r0,[r1]
8e0018a8:	01a2      	nop
8e0018aa:	f64c 2400 	ldr fp,[sp,+0x4]
8e0018ae:	b41b 2402 	add sp,sp,16
8e0018b2:	194f 0402 	rts
8e0018b6:	01a2      	nop

8e0018b8 <find_call>:
8e0018b8:	f75c 2700 	str fp,[sp],-0x6
8e0018bc:	f4ef 2402 	mov fp,sp
8e0018c0:	1ddc 0400 	str r0,[fp,+0x3]
8e0018c4:	3d5c 0400 	str r1,[fp,+0x2]
8e0018c8:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0018cc:	1edc 0400 	str r0,[fp,+0x5]
8e0018d0:	0f8b 0032 	mov r0,0x37c
8e0018d4:	000b 1002 	movt r0,0x0
8e0018d8:	0044      	ldr r0,[r0]
8e0018da:	001b 0038 	add r0,r0,448
8e0018de:	1e5c 0400 	str r0,[fp,+0x4]
8e0018e2:	1e4c 0400 	ldr r0,[fp,+0x4]
8e0018e6:	2003      	mov r1,0x0
8e0018e8:	2034      	strh r1,[r0]
8e0018ea:	35e0      	b 8e001954 <find_call+0x9c>
8e0018ec:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0018f0:	2024      	ldrh r1,[r0]
8e0018f2:	1d4c 0400 	ldr r0,[fp,+0x2]
8e0018f6:	0024      	ldrh r0,[r0]
8e0018f8:	443a      	sub r2,r1,r0
8e0018fa:	1110      	bne 8e00191c <find_call+0x64>
8e0018fc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001900:	0113      	add r0,r0,2
8e001902:	2024      	ldrh r1,[r0]
8e001904:	1d4c 0400 	ldr r0,[fp,+0x2]
8e001908:	0113      	add r0,r0,2
8e00190a:	0024      	ldrh r0,[r0]
8e00190c:	443a      	sub r2,r1,r0
8e00190e:	0710      	bne 8e00191c <find_call+0x64>
8e001910:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001914:	3dcb 01e2 	mov r1,0x1eee
8e001918:	2034      	strh r1,[r0]
8e00191a:	21e0      	b 8e00195c <find_call+0xa4>
8e00191c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001920:	2024      	ldrh r1,[r0]
8e001922:	09eb 0192 	mov r0,0x194f
8e001926:	443a      	sub r2,r1,r0
8e001928:	1110      	bne 8e00194a <find_call+0x92>
8e00192a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00192e:	0113      	add r0,r0,2
8e001930:	2024      	ldrh r1,[r0]
8e001932:	004b 0042 	mov r0,0x402
8e001936:	443a      	sub r2,r1,r0
8e001938:	0910      	bne 8e00194a <find_call+0x92>
8e00193a:	1e4c 0400 	ldr r0,[fp,+0x4]
8e00193e:	2223      	mov r1,0x11
8e001940:	2034      	strh r1,[r0]
8e001942:	0003      	mov r0,0x0
8e001944:	1edc 0400 	str r0,[fp,+0x5]
8e001948:	0ae0      	b 8e00195c <find_call+0xa4>
8e00194a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00194e:	0313      	add r0,r0,-2
8e001950:	1edc 0400 	str r0,[fp,+0x5]
8e001954:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001958:	2033      	sub r1,r0,0
8e00195a:	c910      	bne 8e0018ec <find_call+0x34>
8e00195c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001960:	f74c 2400 	ldr fp,[sp,+0x6]
8e001964:	b41b 2403 	add sp,sp,24
8e001968:	194f 0402 	rts

8e00196c <find_interrupt_call>:
8e00196c:	f75c 2700 	str fp,[sp],-0x6
8e001970:	f4ef 2402 	mov fp,sp
8e001974:	1ddc 0400 	str r0,[fp,+0x3]
8e001978:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00197c:	1edc 0400 	str r0,[fp,+0x5]
8e001980:	0f8b 0032 	mov r0,0x37c
8e001984:	000b 1002 	movt r0,0x0
8e001988:	0044      	ldr r0,[r0]
8e00198a:	001b 0038 	add r0,r0,448
8e00198e:	1e5c 0400 	str r0,[fp,+0x4]
8e001992:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001996:	2003      	mov r1,0x0
8e001998:	2034      	strh r1,[r0]
8e00199a:	4de0      	b 8e001a34 <find_interrupt_call+0xc8>
8e00199c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019a0:	2024      	ldrh r1,[r0]
8e0019a2:	1f8b 0142 	mov r0,0x14fc
8e0019a6:	443a      	sub r2,r1,r0
8e0019a8:	2a10      	bne 8e0019fc <find_interrupt_call+0x90>
8e0019aa:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019ae:	0113      	add r0,r0,2
8e0019b0:	2024      	ldrh r1,[r0]
8e0019b2:	000b 0052 	mov r0,0x500
8e0019b6:	443a      	sub r2,r1,r0
8e0019b8:	2210      	bne 8e0019fc <find_interrupt_call+0x90>
8e0019ba:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019be:	021b 0000 	add r0,r0,4
8e0019c2:	2024      	ldrh r1,[r0]
8e0019c4:	024b 0052 	mov r0,0x512
8e0019c8:	443a      	sub r2,r1,r0
8e0019ca:	1910      	bne 8e0019fc <find_interrupt_call+0x90>
8e0019cc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019d0:	031b 0000 	add r0,r0,6
8e0019d4:	2024      	ldrh r1,[r0]
8e0019d6:	03eb 0212 	mov r0,0x211f
8e0019da:	443a      	sub r2,r1,r0
8e0019dc:	1010      	bne 8e0019fc <find_interrupt_call+0x90>
8e0019de:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0019e2:	001b 0001 	add r0,r0,8
8e0019e6:	2024      	ldrh r1,[r0]
8e0019e8:	004b 0042 	mov r0,0x402
8e0019ec:	443a      	sub r2,r1,r0
8e0019ee:	0710      	bne 8e0019fc <find_interrupt_call+0x90>
8e0019f0:	1e4c 0400 	ldr r0,[fp,+0x4]
8e0019f4:	3dcb 02e2 	mov r1,0x2eee
8e0019f8:	2034      	strh r1,[r0]
8e0019fa:	21e0      	b 8e001a3c <find_interrupt_call+0xd0>
8e0019fc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a00:	2024      	ldrh r1,[r0]
8e001a02:	09eb 0192 	mov r0,0x194f
8e001a06:	443a      	sub r2,r1,r0
8e001a08:	1110      	bne 8e001a2a <find_interrupt_call+0xbe>
8e001a0a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a0e:	0113      	add r0,r0,2
8e001a10:	2024      	ldrh r1,[r0]
8e001a12:	004b 0042 	mov r0,0x402
8e001a16:	443a      	sub r2,r1,r0
8e001a18:	0910      	bne 8e001a2a <find_interrupt_call+0xbe>
8e001a1a:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001a1e:	2423      	mov r1,0x21
8e001a20:	2034      	strh r1,[r0]
8e001a22:	0003      	mov r0,0x0
8e001a24:	1edc 0400 	str r0,[fp,+0x5]
8e001a28:	0ae0      	b 8e001a3c <find_interrupt_call+0xd0>
8e001a2a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a2e:	0313      	add r0,r0,-2
8e001a30:	1edc 0400 	str r0,[fp,+0x5]
8e001a34:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a38:	2033      	sub r1,r0,0
8e001a3a:	b110      	bne 8e00199c <find_interrupt_call+0x30>
8e001a3c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a40:	f74c 2400 	ldr fp,[sp,+0x6]
8e001a44:	b41b 2403 	add sp,sp,24
8e001a48:	194f 0402 	rts

8e001a4c <find_rts>:
8e001a4c:	f45c 2701 	str fp,[sp],-0x8
8e001a50:	f4ef 2402 	mov fp,sp
8e001a54:	1ddc 0400 	str r0,[fp,+0x3]
8e001a58:	3dcc 0400 	ldr r1,[fp,+0x3]
8e001a5c:	000b 0802 	mov r0,0x8000
8e001a60:	041a      	add r0,r1,r0
8e001a62:	1f5c 0400 	str r0,[fp,+0x6]
8e001a66:	0f8b 0032 	mov r0,0x37c
8e001a6a:	000b 1002 	movt r0,0x0
8e001a6e:	0044      	ldr r0,[r0]
8e001a70:	001b 0038 	add r0,r0,448
8e001a74:	1edc 0400 	str r0,[fp,+0x5]
8e001a78:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001a7c:	2003      	mov r1,0x0
8e001a7e:	2034      	strh r1,[r0]
8e001a80:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001a84:	1fdc 0400 	str r0,[fp,+0x7]
8e001a88:	45e0      	b 8e001b12 <find_rts+0xc6>
8e001a8a:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001a8e:	2024      	ldrh r1,[r0]
8e001a90:	09eb 0192 	mov r0,0x194f
8e001a94:	443a      	sub r2,r1,r0
8e001a96:	0f10      	bne 8e001ab4 <find_rts+0x68>
8e001a98:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001a9c:	0113      	add r0,r0,2
8e001a9e:	2024      	ldrh r1,[r0]
8e001aa0:	004b 0042 	mov r0,0x402
8e001aa4:	443a      	sub r2,r1,r0
8e001aa6:	0710      	bne 8e001ab4 <find_rts+0x68>
8e001aa8:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001aac:	3dcb 04e2 	mov r1,0x4eee
8e001ab0:	2034      	strh r1,[r0]
8e001ab2:	36e0      	b 8e001b1e <find_rts+0xd2>
8e001ab4:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001ab8:	0024      	ldrh r0,[r0]
8e001aba:	213b 003a 	sub r1,r0,466
8e001abe:	2510      	bne 8e001b08 <find_rts+0xbc>
8e001ac0:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001ac4:	031b 00fe 	add r0,r0,-10
8e001ac8:	2024      	ldrh r1,[r0]
8e001aca:	004b 0052 	mov r0,0x502
8e001ace:	443a      	sub r2,r1,r0
8e001ad0:	1c10      	bne 8e001b08 <find_rts+0xbc>
8e001ad2:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001ad6:	001b 00ff 	add r0,r0,-8
8e001ada:	2024      	ldrh r1,[r0]
8e001adc:	01eb 0212 	mov r0,0x210f
8e001ae0:	443a      	sub r2,r1,r0
8e001ae2:	1310      	bne 8e001b08 <find_rts+0xbc>
8e001ae4:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001ae8:	011b 00ff 	add r0,r0,-6
8e001aec:	2024      	ldrh r1,[r0]
8e001aee:	004b 0042 	mov r0,0x402
8e001af2:	443a      	sub r2,r1,r0
8e001af4:	0a10      	bne 8e001b08 <find_rts+0xbc>
8e001af6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001afa:	2823      	mov r1,0x41
8e001afc:	2034      	strh r1,[r0]
8e001afe:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001b02:	1fdc 0400 	str r0,[fp,+0x7]
8e001b06:	0ce0      	b 8e001b1e <find_rts+0xd2>
8e001b08:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b0c:	0113      	add r0,r0,2
8e001b0e:	1fdc 0400 	str r0,[fp,+0x7]
8e001b12:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b16:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001b1a:	443a      	sub r2,r1,r0
8e001b1c:	b750      	bltu 8e001a8a <find_rts+0x3e>
8e001b1e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b22:	0024      	ldrh r0,[r0]
8e001b24:	20bb 0008 	sub r1,r0,65
8e001b28:	0310      	bne 8e001b2e <find_rts+0xe2>
8e001b2a:	0003      	mov r0,0x0
8e001b2c:	1de0      	b 8e001b66 <find_rts+0x11a>
8e001b2e:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b32:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001b36:	443a      	sub r2,r1,r0
8e001b38:	0710      	bne 8e001b46 <find_rts+0xfa>
8e001b3a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b3e:	2843      	mov r1,0x42
8e001b40:	2034      	strh r1,[r0]
8e001b42:	0003      	mov r0,0x0
8e001b44:	11e0      	b 8e001b66 <find_rts+0x11a>
8e001b46:	3fcc 0400 	ldr r1,[fp,+0x7]
8e001b4a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001b4e:	043a      	sub r0,r1,r0
8e001b50:	002e      	asr r0,r0,0x1
8e001b52:	20b3      	sub r1,r0,1
8e001b54:	0720      	bgtu 8e001b62 <find_rts+0x116>
8e001b56:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001b5a:	2863      	mov r1,0x43
8e001b5c:	2034      	strh r1,[r0]
8e001b5e:	0003      	mov r0,0x0
8e001b60:	03e0      	b 8e001b66 <find_rts+0x11a>
8e001b62:	1fcc 0400 	ldr r0,[fp,+0x7]
8e001b66:	f44c 2401 	ldr fp,[sp,+0x8]
8e001b6a:	b41b 2404 	add sp,sp,32
8e001b6e:	194f 0402 	rts
8e001b72:	01a2      	nop

8e001b74 <get_sp_disp>:
8e001b74:	f65c 2701 	str fp,[sp],-0xc
8e001b78:	f4ef 2402 	mov fp,sp
8e001b7c:	1ddc 0400 	str r0,[fp,+0x3]
8e001b80:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001b84:	1ddc 0401 	str r0,[fp,+0xb]
8e001b88:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001b8c:	0213      	add r0,r0,-4
8e001b8e:	1ddc 0401 	str r0,[fp,+0xb]
8e001b92:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001b96:	0024      	ldrh r0,[r0]
8e001b98:	1ebc 0402 	strh r0,[fp,+0x15]
8e001b9c:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001ba0:	00a4      	ldrh r0,[r0,0x1]
8e001ba2:	1e3c 0402 	strh r0,[fp,+0x14]
8e001ba6:	0f8b 0032 	mov r0,0x37c
8e001baa:	000b 1002 	movt r0,0x0
8e001bae:	0044      	ldr r0,[r0]
8e001bb0:	001b 0038 	add r0,r0,448
8e001bb4:	1cdc 0401 	str r0,[fp,+0x9]
8e001bb8:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001bbc:	2003      	mov r1,0x0
8e001bbe:	2034      	strh r1,[r0]
8e001bc0:	3eac 0402 	ldrh r1,[fp,+0x15]
8e001bc4:	01eb 0f02 	mov r0,0xf00f
8e001bc8:	245a      	and r1,r1,r0
8e001bca:	016b 0b02 	mov r0,0xb00b
8e001bce:	443a      	sub r2,r1,r0
8e001bd0:	0800      	beq 8e001be0 <get_sp_disp+0x6c>
8e001bd2:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001bd6:	2623      	mov r1,0x31
8e001bd8:	2034      	strh r1,[r0]
8e001bda:	0003      	mov r0,0x0
8e001bdc:	8fe8 0000 	b 8e001cfa <get_sp_disp+0x186>
8e001be0:	3e2c 0402 	ldrh r1,[fp,+0x14]
8e001be4:	000b 0ff2 	mov r0,0xff00
8e001be8:	245a      	and r1,r1,r0
8e001bea:	000b 0242 	mov r0,0x2400
8e001bee:	443a      	sub r2,r1,r0
8e001bf0:	0700      	beq 8e001bfe <get_sp_disp+0x8a>
8e001bf2:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001bf6:	2643      	mov r1,0x32
8e001bf8:	2034      	strh r1,[r0]
8e001bfa:	0003      	mov r0,0x0
8e001bfc:	7fe0      	b 8e001cfa <get_sp_disp+0x186>
8e001bfe:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c02:	1c5c 0401 	str r0,[fp,+0x8]
8e001c06:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c0a:	0213      	add r0,r0,-4
8e001c0c:	1ddc 0401 	str r0,[fp,+0xb]
8e001c10:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c14:	0024      	ldrh r0,[r0]
8e001c16:	1ebc 0402 	strh r0,[fp,+0x15]
8e001c1a:	1dcc 0401 	ldr r0,[fp,+0xb]
8e001c1e:	00a4      	ldrh r0,[r0,0x1]
8e001c20:	1e3c 0402 	strh r0,[fp,+0x14]
8e001c24:	3eac 0402 	ldrh r1,[fp,+0x15]
8e001c28:	01eb 0f02 	mov r0,0xf00f
8e001c2c:	245a      	and r1,r1,r0
8e001c2e:	018b 0d02 	mov r0,0xd00c
8e001c32:	443a      	sub r2,r1,r0
8e001c34:	0700      	beq 8e001c42 <get_sp_disp+0xce>
8e001c36:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c3a:	2663      	mov r1,0x33
8e001c3c:	2034      	strh r1,[r0]
8e001c3e:	0003      	mov r0,0x0
8e001c40:	5de0      	b 8e001cfa <get_sp_disp+0x186>
8e001c42:	3e2c 0402 	ldrh r1,[fp,+0x14]
8e001c46:	000b 0f02 	mov r0,0xf000
8e001c4a:	245a      	and r1,r1,r0
8e001c4c:	000b 0202 	mov r0,0x2000
8e001c50:	443a      	sub r2,r1,r0
8e001c52:	0700      	beq 8e001c60 <get_sp_disp+0xec>
8e001c54:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001c58:	2683      	mov r1,0x34
8e001c5a:	2034      	strh r1,[r0]
8e001c5c:	0003      	mov r0,0x0
8e001c5e:	4ee0      	b 8e001cfa <get_sp_disp+0x186>
8e001c60:	1c4c 0401 	ldr r0,[fp,+0x8]
8e001c64:	1f5c 0400 	str r0,[fp,+0x6]
8e001c68:	0003      	mov r0,0x0
8e001c6a:	1dbc 0401 	strh r0,[fp,+0xb]
8e001c6e:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001c72:	0113      	add r0,r0,2
8e001c74:	0024      	ldrh r0,[r0]
8e001c76:	20e2      	mov r1,r0
8e001c78:	1fe3      	mov r0,0xff
8e001c7a:	045a      	and r0,r1,r0
8e001c7c:	0076      	lsl r0,r0,0x3
8e001c7e:	20e2      	mov r1,r0
8e001c80:	200b 1002 	movt r1,0x0
8e001c84:	1f4c 0400 	ldr r0,[fp,+0x6]
8e001c88:	0024      	ldrh r0,[r0]
8e001c8a:	40e2      	mov r2,r0
8e001c8c:	100b 0032 	mov r0,0x380
8e001c90:	085a      	and r0,r2,r0
8e001c92:	00ee      	asr r0,r0,0x7
8e001c94:	000b 1002 	movt r0,0x0
8e001c98:	047a      	orr r0,r1,r0
8e001c9a:	000b 1002 	movt r0,0x0
8e001c9e:	1dbc 0401 	strh r0,[fp,+0xb]
8e001ca2:	1f1b 0402 	add r0,fp,22
8e001ca6:	0093      	add r0,r0,1
8e001ca8:	0004      	ldrb r0,[r0]
8e001caa:	0046      	lsr r0,r0,0x2
8e001cac:	0316      	lsl r0,r0,0x18
8e001cae:	0306      	lsr r0,r0,0x18
8e001cb0:	20e2      	mov r1,r0
8e001cb2:	0023      	mov r0,0x1
8e001cb4:	045a      	and r0,r1,r0
8e001cb6:	2033      	sub r1,r0,0
8e001cb8:	1000      	beq 8e001cd8 <get_sp_disp+0x164>
8e001cba:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001cbe:	20e2      	mov r1,r0
8e001cc0:	200b 1002 	movt r1,0x0
8e001cc4:	000b 0f82 	mov r0,0xf800
8e001cc8:	1feb 1ff2 	movt r0,0xffff
8e001ccc:	040a      	eor r0,r1,r0
8e001cce:	000b 1002 	movt r0,0x0
8e001cd2:	000b 1002 	movt r0,0x0
8e001cd6:	03e0      	b 8e001cdc <get_sp_disp+0x168>
8e001cd8:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001cdc:	1dbc 0401 	strh r0,[fp,+0xb]
8e001ce0:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001ce4:	000b 1002 	movt r0,0x0
8e001ce8:	1fbc 0401 	strh r0,[fp,+0xf]
8e001cec:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001cf0:	3dcb 03e2 	mov r1,0x3eee
8e001cf4:	2034      	strh r1,[r0]
8e001cf6:	1fac 0401 	ldrh r0,[fp,+0xf]
8e001cfa:	0216      	lsl r0,r0,0x10
8e001cfc:	020e      	asr r0,r0,0x10
8e001cfe:	f64c 2401 	ldr fp,[sp,+0xc]
8e001d02:	b41b 2406 	add sp,sp,48
8e001d06:	194f 0402 	rts
8e001d0a:	01a2      	nop

8e001d0c <umm_info>:
8e001d0c:	d6fc 2700 	strd lr,[sp],-0x5
8e001d10:	f41b 2405 	add fp,sp,40
8e001d14:	1edc 0500 	str r0,[fp,-0x5]
8e001d18:	3f5c 0500 	str r1,[fp,-0x6]
8e001d1c:	5fdc 0500 	str r2,[fp,-0x7]
8e001d20:	0003      	mov r0,0x0
8e001d22:	1cbc 0500 	strh r0,[fp,-0x1]
8e001d26:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001d2a:	1d5c 0500 	str r0,[fp,-0x2]
8e001d2e:	0003      	mov r0,0x0
8e001d30:	1c9c 0501 	strb r0,[fp,-0x9]
8e001d34:	0203      	mov r0,0x10
8e001d36:	1e5c 0500 	str r0,[fp,-0x4]
8e001d3a:	1c8c 0501 	ldrb r0,[fp,-0x9]
8e001d3e:	5e4c 0500 	ldr r2,[fp,-0x4]
8e001d42:	20e2      	mov r1,r0
8e001d44:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001d48:	6a0b 0032 	mov r3,0x350
8e001d4c:	600b 18e2 	movt r3,0x8e00
8e001d50:	0d52      	jalr r3
8e001d52:	060b 0032 	mov r0,0x330
8e001d56:	000b 1002 	movt r0,0x0
8e001d5a:	2044      	ldr r1,[r0]
8e001d5c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001d60:	0076      	lsl r0,r0,0x3
8e001d62:	041a      	add r0,r1,r0
8e001d64:	2004      	ldrb r1,[r0]
8e001d66:	0084      	ldrb r0,[r0,0x1]
8e001d68:	0116      	lsl r0,r0,0x8
8e001d6a:	00fa      	orr r0,r0,r1
8e001d6c:	20e2      	mov r1,r0
8e001d6e:	200b 1002 	movt r1,0x0
8e001d72:	1feb 07f2 	mov r0,0x7fff
8e001d76:	045a      	and r0,r1,r0
8e001d78:	1cbc 0500 	strh r0,[fp,-0x1]
8e001d7c:	cae8 0000 	b 8e001f10 <umm_info+0x204>
8e001d80:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001d84:	0024      	ldrh r0,[r0]
8e001d86:	0093      	add r0,r0,1
8e001d88:	20e2      	mov r1,r0
8e001d8a:	200b 1002 	movt r1,0x0
8e001d8e:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001d92:	2034      	strh r1,[r0]
8e001d94:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001d98:	21a4      	ldrh r1,[r0,0x3]
8e001d9a:	060b 0032 	mov r0,0x330
8e001d9e:	000b 1002 	movt r0,0x0
8e001da2:	4044      	ldr r2,[r0]
8e001da4:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001da8:	0076      	lsl r0,r0,0x3
8e001daa:	081a      	add r0,r2,r0
8e001dac:	4004      	ldrb r2,[r0]
8e001dae:	0084      	ldrb r0,[r0,0x1]
8e001db0:	0116      	lsl r0,r0,0x8
8e001db2:	017a      	orr r0,r0,r2
8e001db4:	40e2      	mov r2,r0
8e001db6:	400b 1002 	movt r2,0x0
8e001dba:	1feb 07f2 	mov r0,0x7fff
8e001dbe:	085a      	and r0,r2,r0
8e001dc0:	40e2      	mov r2,r0
8e001dc2:	400b 1002 	movt r2,0x0
8e001dc6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001dca:	083a      	sub r0,r2,r0
8e001dcc:	000b 1002 	movt r0,0x0
8e001dd0:	041a      	add r0,r1,r0
8e001dd2:	20e2      	mov r1,r0
8e001dd4:	200b 1002 	movt r1,0x0
8e001dd8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ddc:	21b4      	strh r1,[r0,0x3]
8e001dde:	060b 0032 	mov r0,0x330
8e001de2:	000b 1002 	movt r0,0x0
8e001de6:	2044      	ldr r1,[r0]
8e001de8:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001dec:	0076      	lsl r0,r0,0x3
8e001dee:	041a      	add r0,r1,r0
8e001df0:	2004      	ldrb r1,[r0]
8e001df2:	0084      	ldrb r0,[r0,0x1]
8e001df4:	0116      	lsl r0,r0,0x8
8e001df6:	00fa      	orr r0,r0,r1
8e001df8:	000b 1002 	movt r0,0x0
8e001dfc:	000b 1002 	movt r0,0x0
8e001e00:	0216      	lsl r0,r0,0x10
8e001e02:	020e      	asr r0,r0,0x10
8e001e04:	2033      	sub r1,r0,0
8e001e06:	4170      	bgte 8e001e88 <umm_info+0x17c>
8e001e08:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e0c:	0124      	ldrh r0,[r0,0x2]
8e001e0e:	0093      	add r0,r0,1
8e001e10:	20e2      	mov r1,r0
8e001e12:	200b 1002 	movt r1,0x0
8e001e16:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e1a:	2134      	strh r1,[r0,0x2]
8e001e1c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e20:	22a4      	ldrh r1,[r0,0x5]
8e001e22:	060b 0032 	mov r0,0x330
8e001e26:	000b 1002 	movt r0,0x0
8e001e2a:	4044      	ldr r2,[r0]
8e001e2c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e30:	0076      	lsl r0,r0,0x3
8e001e32:	081a      	add r0,r2,r0
8e001e34:	4004      	ldrb r2,[r0]
8e001e36:	0084      	ldrb r0,[r0,0x1]
8e001e38:	0116      	lsl r0,r0,0x8
8e001e3a:	017a      	orr r0,r0,r2
8e001e3c:	40e2      	mov r2,r0
8e001e3e:	400b 1002 	movt r2,0x0
8e001e42:	1feb 07f2 	mov r0,0x7fff
8e001e46:	085a      	and r0,r2,r0
8e001e48:	40e2      	mov r2,r0
8e001e4a:	400b 1002 	movt r2,0x0
8e001e4e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e52:	083a      	sub r0,r2,r0
8e001e54:	000b 1002 	movt r0,0x0
8e001e58:	041a      	add r0,r1,r0
8e001e5a:	20e2      	mov r1,r0
8e001e5c:	200b 1002 	movt r1,0x0
8e001e60:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e64:	22b4      	strh r1,[r0,0x5]
8e001e66:	060b 0032 	mov r0,0x330
8e001e6a:	000b 1002 	movt r0,0x0
8e001e6e:	2044      	ldr r1,[r0]
8e001e70:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001e74:	0076      	lsl r0,r0,0x3
8e001e76:	241a      	add r1,r1,r0
8e001e78:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001e7c:	443a      	sub r2,r1,r0
8e001e7e:	3410      	bne 8e001ee6 <umm_info+0x1da>
8e001e80:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001e84:	8be8 0000 	b 8e001f9a <umm_info+0x28e>
8e001e88:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e8c:	00a4      	ldrh r0,[r0,0x1]
8e001e8e:	0093      	add r0,r0,1
8e001e90:	20e2      	mov r1,r0
8e001e92:	200b 1002 	movt r1,0x0
8e001e96:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001e9a:	20b4      	strh r1,[r0,0x1]
8e001e9c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ea0:	2224      	ldrh r1,[r0,0x4]
8e001ea2:	060b 0032 	mov r0,0x330
8e001ea6:	000b 1002 	movt r0,0x0
8e001eaa:	4044      	ldr r2,[r0]
8e001eac:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001eb0:	0076      	lsl r0,r0,0x3
8e001eb2:	081a      	add r0,r2,r0
8e001eb4:	4004      	ldrb r2,[r0]
8e001eb6:	0084      	ldrb r0,[r0,0x1]
8e001eb8:	0116      	lsl r0,r0,0x8
8e001eba:	017a      	orr r0,r0,r2
8e001ebc:	40e2      	mov r2,r0
8e001ebe:	400b 1002 	movt r2,0x0
8e001ec2:	1feb 07f2 	mov r0,0x7fff
8e001ec6:	085a      	and r0,r2,r0
8e001ec8:	40e2      	mov r2,r0
8e001eca:	400b 1002 	movt r2,0x0
8e001ece:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001ed2:	083a      	sub r0,r2,r0
8e001ed4:	000b 1002 	movt r0,0x0
8e001ed8:	041a      	add r0,r1,r0
8e001eda:	20e2      	mov r1,r0
8e001edc:	200b 1002 	movt r1,0x0
8e001ee0:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001ee4:	2234      	strh r1,[r0,0x4]
8e001ee6:	060b 0032 	mov r0,0x330
8e001eea:	000b 1002 	movt r0,0x0
8e001eee:	2044      	ldr r1,[r0]
8e001ef0:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001ef4:	0076      	lsl r0,r0,0x3
8e001ef6:	041a      	add r0,r1,r0
8e001ef8:	2004      	ldrb r1,[r0]
8e001efa:	0084      	ldrb r0,[r0,0x1]
8e001efc:	0116      	lsl r0,r0,0x8
8e001efe:	00fa      	orr r0,r0,r1
8e001f00:	20e2      	mov r1,r0
8e001f02:	200b 1002 	movt r1,0x0
8e001f06:	1feb 07f2 	mov r0,0x7fff
8e001f0a:	045a      	and r0,r1,r0
8e001f0c:	1cbc 0500 	strh r0,[fp,-0x1]
8e001f10:	060b 0032 	mov r0,0x330
8e001f14:	000b 1002 	movt r0,0x0
8e001f18:	2044      	ldr r1,[r0]
8e001f1a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f1e:	0076      	lsl r0,r0,0x3
8e001f20:	041a      	add r0,r1,r0
8e001f22:	2004      	ldrb r1,[r0]
8e001f24:	0084      	ldrb r0,[r0,0x1]
8e001f26:	0116      	lsl r0,r0,0x8
8e001f28:	00fa      	orr r0,r0,r1
8e001f2a:	000b 1002 	movt r0,0x0
8e001f2e:	20e2      	mov r1,r0
8e001f30:	1feb 07f2 	mov r0,0x7fff
8e001f34:	045a      	and r0,r1,r0
8e001f36:	2033      	sub r1,r0,0
8e001f38:	2418 ffff 	bne 8e001d80 <umm_info+0x74>
8e001f3c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f40:	22a4      	ldrh r1,[r0,0x5]
8e001f42:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f46:	043a      	sub r0,r1,r0
8e001f48:	20e2      	mov r1,r0
8e001f4a:	200b 1002 	movt r1,0x0
8e001f4e:	000b 0302 	mov r0,0x3000
8e001f52:	000b 1002 	movt r0,0x0
8e001f56:	0066      	lsr r0,r0,0x3
8e001f58:	000b 1002 	movt r0,0x0
8e001f5c:	041a      	add r0,r1,r0
8e001f5e:	20e2      	mov r1,r0
8e001f60:	200b 1002 	movt r1,0x0
8e001f64:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f68:	22b4      	strh r1,[r0,0x5]
8e001f6a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f6e:	21a4      	ldrh r1,[r0,0x3]
8e001f70:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001f74:	043a      	sub r0,r1,r0
8e001f76:	20e2      	mov r1,r0
8e001f78:	200b 1002 	movt r1,0x0
8e001f7c:	000b 0302 	mov r0,0x3000
8e001f80:	000b 1002 	movt r0,0x0
8e001f84:	0066      	lsr r0,r0,0x3
8e001f86:	000b 1002 	movt r0,0x0
8e001f8a:	041a      	add r0,r1,r0
8e001f8c:	20e2      	mov r1,r0
8e001f8e:	200b 1002 	movt r1,0x0
8e001f92:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001f96:	21b4      	strh r1,[r0,0x3]
8e001f98:	0003      	mov r0,0x0
8e001f9a:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e001f9e:	b41b 2405 	add sp,sp,40
8e001fa2:	194f 0402 	rts
8e001fa6:	01a2      	nop

8e001fa8 <umm_malloc>:
8e001fa8:	967c 0700 	strd r4,[sp],-0x4
8e001fac:	d5fc 0400 	strd r6,[sp,+0x3]
8e001fb0:	157c 2400 	strd r8,[sp,+0x2]
8e001fb4:	d4fc 2400 	strd lr,[sp,+0x1]
8e001fb8:	2033      	sub r1,r0,0
8e001fba:	ac08 0000 	beq 8e002112 <umm_malloc+0x16a>
8e001fbe:	358b 0232 	mov r1,0x23ac
8e001fc2:	200b 18e2 	movt r1,0x8e00
8e001fc6:	0552      	jalr r1
8e001fc8:	c60b 0032 	mov r6,0x330
8e001fcc:	c00b 1002 	movt r6,0x0
8e001fd0:	984c 2000 	ldr ip,[r6,+0x0]
8e001fd4:	1feb 47f2 	mov r16,0x7fff
8e001fd8:	328c 0400 	ldrb r1,[ip,+0x5]
8e001fdc:	2516      	lsl r1,r1,0x8
8e001fde:	720c 0400 	ldrb r3,[ip,+0x4]
8e001fe2:	65fa      	orr r3,r1,r3
8e001fe4:	8ce2      	mov r4,r3
8e001fe6:	2003      	mov r1,0x0
8e001fe8:	7feb 47f2 	mov r19,0x7fff
8e001fec:	5076      	lsl r2,r4,0x3
8e001fee:	511f 040a 	add r2,ip,r2
8e001ff2:	4a8c 4000 	ldrb r18,[r2,+0x5]
8e001ff6:	2a0c 4000 	ldrb r17,[r2,+0x4]
8e001ffa:	491f 4806 	lsl r18,r18,0x8
8e001ffe:	28ff 490a 	orr r17,r18,r17
8e002002:	1500      	beq 8e00202c <umm_malloc+0x84>
8e002004:	2804      	ldrb r1,[r2]
8e002006:	4884      	ldrb r2,[r2,0x1]
8e002008:	4916      	lsl r2,r2,0x8
8e00200a:	28fa      	orr r1,r2,r1
8e00200c:	25df 010a 	and r1,r1,r19
8e002010:	263a      	sub r1,r1,r4
8e002012:	200b 1002 	movt r1,0x0
8e002016:	40ba      	sub r2,r0,r1
8e002018:	0720      	bgtu 8e002026 <umm_malloc+0x7e>
8e00201a:	40bf 080a 	sub r2,r16,r1
8e00201e:	0440      	blteu 8e002026 <umm_malloc+0x7e>
8e002020:	70e2      	mov r3,r4
8e002022:	04ef 4002 	mov r16,r1
8e002026:	84ef 0802 	mov r4,r17
8e00202a:	e1e0      	b 8e001fec <umm_malloc+0x44>
8e00202c:	5feb 07f2 	mov r2,0x7fff
8e002030:	213f 480a 	sub r17,r16,r2
8e002034:	8c12      	movne r4,r3
8e002036:	201f 0802 	movne r1,r16
8e00203a:	7076      	lsl r3,r4,0x3
8e00203c:	719f 040a 	add r3,ip,r3
8e002040:	4c84      	ldrb r2,[r3,0x1]
8e002042:	0c0c 4000 	ldrb r16,[r3,+0x0]
8e002046:	4916      	lsl r2,r2,0x8
8e002048:	487f 010a 	orr r2,r2,r16
8e00204c:	7feb 07f2 	mov r3,0x7fff
8e002050:	49da      	and r2,r2,r3
8e002052:	1a00      	beq 8e002086 <umm_malloc+0xde>
8e002054:	443a      	sub r2,r1,r0
8e002056:	0810      	bne 8e002066 <umm_malloc+0xbe>
8e002058:	2c0b 0242 	mov r1,0x2460
8e00205c:	10e2      	mov r0,r4
8e00205e:	200b 18e2 	movt r1,0x8e00
8e002062:	0552      	jalr r1
8e002064:	51e0      	b 8e002106 <umm_malloc+0x15e>
8e002066:	a43a      	sub r5,r1,r0
8e002068:	a00b 1002 	movt r5,0x0
8e00206c:	790b 0232 	mov r3,0x23c8
8e002070:	10e2      	mov r0,r4
8e002072:	400b 0802 	mov r2,0x8000
8e002076:	34e2      	mov r1,r5
8e002078:	600b 18e2 	movt r3,0x8e00
8e00207c:	929a      	add r4,r4,r5
8e00207e:	0d52      	jalr r3
8e002080:	800b 1002 	movt r4,0x0
8e002084:	41e0      	b 8e002106 <umm_malloc+0x15e>
8e002086:	200b 0302 	mov r1,0x3000
8e00208a:	501a      	add r2,r4,r0
8e00208c:	200b 1002 	movt r1,0x0
8e002090:	4893      	add r2,r2,1
8e002092:	2466      	lsr r1,r1,0x3
8e002094:	68ba      	sub r3,r2,r1
8e002096:	3e30      	bgteu 8e002112 <umm_malloc+0x16a>
8e002098:	303b 4000 	sub r17,r4,0
8e00209c:	0a10      	bne 8e0020b0 <umm_malloc+0x108>
8e00209e:	4023      	mov r2,0x1
8e0020a0:	909c 0400 	strb r4,[ip,+0x1]
8e0020a4:	501c 0400 	strb r2,[ip]
8e0020a8:	3844      	ldr r1,[r6]
8e0020aa:	8694      	strb r4,[r1,0x5]
8e0020ac:	8023      	mov r4,0x1
8e0020ae:	4614      	strb r2,[r1,0x4]
8e0020b0:	7844      	ldr r3,[r6]
8e0020b2:	f076      	lsl r7,r4,0x3
8e0020b4:	2f9a      	add r1,r3,r7
8e0020b6:	4784      	ldrb r2,[r1,0x7]
8e0020b8:	b01a      	add r5,r4,r0
8e0020ba:	4916      	lsl r2,r2,0x8
8e0020bc:	0704      	ldrb r0,[r1,0x6]
8e0020be:	14ef 2002 	mov r8,r5
8e0020c2:	487a      	orr r2,r2,r0
8e0020c4:	000b 3002 	movt r8,0x0
8e0020c8:	b476      	lsl r5,r5,0x3
8e0020ca:	4876      	lsl r2,r2,0x3
8e0020cc:	3feb 2002 	mov r9,0xff
8e0020d0:	4d1a      	add r2,r3,r2
8e0020d2:	20df 248a 	and r9,r8,r9
8e0020d6:	0e9a      	add r0,r3,r5
8e0020d8:	010f 2406 	lsr r8,r8,0x8
8e0020dc:	6d0b 0032 	mov r3,0x368
8e0020e0:	2a1c 2000 	strb r9,[r2,+0x4]
8e0020e4:	0a9c 2000 	strb r8,[r2,+0x5]
8e0020e8:	600b 18e2 	movt r3,0x8e00
8e0020ec:	4103      	mov r2,0x8
8e0020ee:	0d52      	jalr r3
8e0020f0:	1844      	ldr r0,[r6]
8e0020f2:	2399 2000 	strb r9,[r0,+r7]
8e0020f6:	e39a      	add r7,r0,r7
8e0020f8:	1c9c 2000 	strb r8,[r7,+0x1]
8e0020fc:	1844      	ldr r0,[r6]
8e0020fe:	a29a      	add r5,r0,r5
8e002100:	1106      	lsr r0,r4,0x8
8e002102:	9514      	strb r4,[r5,0x2]
8e002104:	1594      	strb r0,[r5,0x3]
8e002106:	1844      	ldr r0,[r6]
8e002108:	9076      	lsl r4,r4,0x3
8e00210a:	021a      	add r0,r0,r4
8e00210c:	021b 0000 	add r0,r0,4
8e002110:	02e0      	b 8e002114 <umm_malloc+0x16c>
8e002112:	0003      	mov r0,0x0
8e002114:	d5ec 0400 	ldrd r6,[sp,+0x3]
8e002118:	156c 2400 	ldrd r8,[sp,+0x2]
8e00211c:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002120:	b41b 2404 	add sp,sp,32
8e002124:	946c 0400 	ldrd r4,[sp,+0x0]
8e002128:	194f 0402 	rts

8e00212c <umm_realloc>:
8e00212c:	96fc 0700 	strd r4,[sp],-0x5
8e002130:	d67c 0400 	strd r6,[sp,+0x4]
8e002134:	15fc 2400 	strd r8,[sp,+0x3]
8e002138:	557c 2400 	strd r10,[sp,+0x2]
8e00213c:	d4fc 2400 	strd lr,[sp,+0x1]
8e002140:	c05a      	and r6,r0,r0
8e002142:	e4e2      	mov r7,r1
8e002144:	1310      	bne 8e00216a <umm_realloc+0x3e>
8e002146:	d66c 0400 	ldrd r6,[sp,+0x4]
8e00214a:	15ec 2400 	ldrd r8,[sp,+0x3]
8e00214e:	556c 2400 	ldrd r10,[sp,+0x2]
8e002152:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002156:	b41b 2405 	add sp,sp,40
8e00215a:	04e2      	mov r0,r1
8e00215c:	946c 0400 	ldrd r4,[sp,+0x0]
8e002160:	350b 01f2 	mov r1,0x1fa8
8e002164:	200b 18e2 	movt r1,0x8e00
8e002168:	0542      	jr r1
8e00216a:	3c33      	sub r1,r7,0
8e00216c:	0910      	bne 8e00217e <umm_realloc+0x52>
8e00216e:	3d0b 0222 	mov r1,0x22e8
8e002172:	200b 18e2 	movt r1,0x8e00
8e002176:	0552      	jalr r1
8e002178:	0003      	mov r0,0x0
8e00217a:	a9e8 0000 	b 8e0022cc <umm_realloc+0x1a0>
8e00217e:	358b 0232 	mov r1,0x23ac
8e002182:	200b 18e2 	movt r1,0x8e00
8e002186:	1ce2      	mov r0,r7
8e002188:	0552      	jalr r1
8e00218a:	660b 2032 	mov r11,0x330
8e00218e:	600b 3002 	movt r11,0x0
8e002192:	a0e2      	mov r5,r0
8e002194:	0c4c 0400 	ldr r0,[r11,+0x0]
8e002198:	183f 200a 	sub r8,r6,r0
8e00219c:	006f 2406 	lsr r8,r8,0x3
8e0021a0:	40ef 2402 	mov r10,r8
8e0021a4:	400b 3002 	movt r10,0x0
8e0021a8:	287f 2406 	lsl r9,r10,0x3
8e0021ac:	2089 0080 	ldrb r1,[r0,+r9]
8e0021b0:	009f 008a 	add r0,r0,r9
8e0021b4:	8084      	ldrb r4,[r0,0x1]
8e0021b6:	9116      	lsl r4,r4,0x8
8e0021b8:	90fa      	orr r4,r4,r1
8e0021ba:	913f 008a 	sub r4,r4,r10
8e0021be:	800b 1002 	movt r4,0x0
8e0021c2:	563a      	sub r2,r5,r4
8e0021c4:	8308 0000 	beq 8e0022ca <umm_realloc+0x19e>
8e0021c8:	390b 0242 	mov r1,0x24c8
8e0021cc:	08ef 0402 	mov r0,r10
8e0021d0:	200b 18e2 	movt r1,0x8e00
8e0021d4:	0552      	jalr r1
8e0021d6:	6c4c 0400 	ldr r3,[r11,+0x0]
8e0021da:	9076      	lsl r4,r4,0x3
8e0021dc:	2c9f 008a 	add r1,r3,r9
8e0021e0:	0584      	ldrb r0,[r1,0x3]
8e0021e2:	4504      	ldrb r2,[r1,0x2]
8e0021e4:	0116      	lsl r0,r0,0x8
8e0021e6:	017a      	orr r0,r0,r2
8e0021e8:	4076      	lsl r2,r0,0x3
8e0021ea:	4d1a      	add r2,r3,r2
8e0021ec:	4884      	ldrb r2,[r2,0x1]
8e0021ee:	9213      	add r4,r4,-4
8e0021f0:	48e6      	lsr r2,r2,0x7
8e0021f2:	6833      	sub r3,r2,0
8e0021f4:	2c00      	beq 8e00224c <umm_realloc+0x120>
8e0021f6:	4404      	ldrb r2,[r1]
8e0021f8:	2484      	ldrb r1,[r1,0x1]
8e0021fa:	2516      	lsl r1,r1,0x8
8e0021fc:	257a      	orr r1,r1,r2
8e0021fe:	243a      	sub r1,r1,r0
8e002200:	54ba      	sub r2,r5,r1
8e002202:	2560      	bgt 8e00224c <umm_realloc+0x120>
8e002204:	2c0b 0242 	mov r1,0x2460
8e002208:	200b 18e2 	movt r1,0x8e00
8e00220c:	0552      	jalr r1
8e00220e:	4c8b 0252 	mov r2,0x2564
8e002212:	2003      	mov r1,0x0
8e002214:	08ef 0402 	mov r0,r10
8e002218:	400b 18e2 	movt r2,0x8e00
8e00221c:	0952      	jalr r2
8e00221e:	007f 2006 	lsl r8,r0,0x3
8e002222:	40ef 2002 	mov r10,r0
8e002226:	0c4c 0400 	ldr r0,[r11,+0x0]
8e00222a:	700b 0032 	mov r3,0x380
8e00222e:	001f 008a 	add r0,r0,r8
8e002232:	38e2      	mov r1,r6
8e002234:	50e2      	mov r2,r4
8e002236:	021b 0000 	add r0,r0,4
8e00223a:	600b 18e2 	movt r3,0x8e00
8e00223e:	0d52      	jalr r3
8e002240:	0c4c 0400 	ldr r0,[r11,+0x0]
8e002244:	001f 008a 	add r0,r0,r8
8e002248:	c21b 0000 	add r6,r0,4
8e00224c:	2c4c 0400 	ldr r1,[r11,+0x0]
8e002250:	087f 0406 	lsl r0,r10,0x3
8e002254:	241a      	add r1,r1,r0
8e002256:	0484      	ldrb r0,[r1,0x1]
8e002258:	4404      	ldrb r2,[r1]
8e00225a:	0116      	lsl r0,r0,0x8
8e00225c:	017a      	orr r0,r0,r2
8e00225e:	013f 008a 	sub r0,r0,r10
8e002262:	000b 1002 	movt r0,0x0
8e002266:	743a      	sub r3,r5,r0
8e002268:	3100      	beq 8e0022ca <umm_realloc+0x19e>
8e00226a:	1d0b 2222 	mov r8,0x22e8
8e00226e:	000b 38e2 	movt r8,0x8e00
8e002272:	1830      	bgteu 8e0022a2 <umm_realloc+0x176>
8e002274:	790b 0232 	mov r3,0x23c8
8e002278:	34e2      	mov r1,r5
8e00227a:	08ef 0402 	mov r0,r10
8e00227e:	4003      	mov r2,0x0
8e002280:	600b 18e2 	movt r3,0x8e00
8e002284:	0d52      	jalr r3
8e002286:	060b 0032 	mov r0,0x330
8e00228a:	000b 1002 	movt r0,0x0
8e00228e:	aa9f 040a 	add r5,r10,r5
8e002292:	0044      	ldr r0,[r0]
8e002294:	b476      	lsl r5,r5,0x3
8e002296:	029a      	add r0,r0,r5
8e002298:	021b 0000 	add r0,r0,4
8e00229c:	015f 0402 	jalr r8
8e0022a0:	15e0      	b 8e0022ca <umm_realloc+0x19e>
8e0022a2:	350b 01f2 	mov r1,0x1fa8
8e0022a6:	1ce2      	mov r0,r7
8e0022a8:	200b 18e2 	movt r1,0x8e00
8e0022ac:	0552      	jalr r1
8e0022ae:	a05a      	and r5,r0,r0
8e0022b0:	0800      	beq 8e0022c0 <umm_realloc+0x194>
8e0022b2:	6d0b 0032 	mov r3,0x368
8e0022b6:	50e2      	mov r2,r4
8e0022b8:	38e2      	mov r1,r6
8e0022ba:	600b 18e2 	movt r3,0x8e00
8e0022be:	0d52      	jalr r3
8e0022c0:	18e2      	mov r0,r6
8e0022c2:	015f 0402 	jalr r8
8e0022c6:	14e2      	mov r0,r5
8e0022c8:	02e0      	b 8e0022cc <umm_realloc+0x1a0>
8e0022ca:	18e2      	mov r0,r6
8e0022cc:	d66c 0400 	ldrd r6,[sp,+0x4]
8e0022d0:	15ec 2400 	ldrd r8,[sp,+0x3]
8e0022d4:	556c 2400 	ldrd r10,[sp,+0x2]
8e0022d8:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0022dc:	b41b 2405 	add sp,sp,40
8e0022e0:	946c 0400 	ldrd r4,[sp,+0x0]
8e0022e4:	194f 0402 	rts

8e0022e8 <umm_free>:
8e0022e8:	95fc 0700 	strd r4,[sp],-0x3
8e0022ec:	d6dc 0400 	str r6,[sp,+0x5]
8e0022f0:	d4fc 2400 	strd lr,[sp,+0x1]
8e0022f4:	005a      	and r0,r0,r0
8e0022f6:	5100      	beq 8e002398 <umm_free+0xb0>
8e0022f8:	c60b 0032 	mov r6,0x330
8e0022fc:	c00b 1002 	movt r6,0x0
8e002300:	9844      	ldr r4,[r6]
8e002302:	390b 0242 	mov r1,0x24c8
8e002306:	823a      	sub r4,r0,r4
8e002308:	9066      	lsr r4,r4,0x3
8e00230a:	b0e2      	mov r5,r4
8e00230c:	a00b 1002 	movt r5,0x0
8e002310:	14e2      	mov r0,r5
8e002312:	200b 18e2 	movt r1,0x8e00
8e002316:	0552      	jalr r1
8e002318:	5844      	ldr r2,[r6]
8e00231a:	3476      	lsl r1,r5,0x3
8e00231c:	289a      	add r1,r2,r1
8e00231e:	0584      	ldrb r0,[r1,0x3]
8e002320:	6504      	ldrb r3,[r1,0x2]
8e002322:	0116      	lsl r0,r0,0x8
8e002324:	01fa      	orr r0,r0,r3
8e002326:	0076      	lsl r0,r0,0x3
8e002328:	081a      	add r0,r2,r0
8e00232a:	0084      	ldrb r0,[r0,0x1]
8e00232c:	00e6      	lsr r0,r0,0x7
8e00232e:	6033      	sub r3,r0,0
8e002330:	1100      	beq 8e002352 <umm_free+0x6a>
8e002332:	d6cc 0400 	ldr r6,[sp,+0x5]
8e002336:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e00233a:	b41b 2403 	add sp,sp,24
8e00233e:	14e2      	mov r0,r5
8e002340:	4c8b 0252 	mov r2,0x2564
8e002344:	946c 0400 	ldrd r4,[sp,+0x0]
8e002348:	200b 0802 	mov r1,0x8000
8e00234c:	400b 18e2 	movt r2,0x8e00
8e002350:	0942      	jr r2
8e002352:	0a84      	ldrb r0,[r2,0x5]
8e002354:	6a04      	ldrb r3,[r2,0x4]
8e002356:	0116      	lsl r0,r0,0x8
8e002358:	01fa      	orr r0,r0,r3
8e00235a:	0076      	lsl r0,r0,0x3
8e00235c:	7fe3      	mov r3,0xff
8e00235e:	081a      	add r0,r2,r0
8e002360:	75da      	and r3,r5,r3
8e002362:	b506      	lsr r5,r5,0x8
8e002364:	6314      	strb r3,[r0,0x6]
8e002366:	a394      	strb r5,[r0,0x7]
8e002368:	0a84      	ldrb r0,[r2,0x5]
8e00236a:	8a0c 2000 	ldrb ip,[r2,+0x4]
8e00236e:	0116      	lsl r0,r0,0x8
8e002370:	027f 008a 	orr r0,r0,ip
8e002374:	0614      	strb r0,[r1,0x4]
8e002376:	0106      	lsr r0,r0,0x8
8e002378:	0694      	strb r0,[r1,0x5]
8e00237a:	0003      	mov r0,0x0
8e00237c:	0714      	strb r0,[r1,0x6]
8e00237e:	0794      	strb r0,[r1,0x7]
8e002380:	6a14      	strb r3,[r2,0x4]
8e002382:	aa94      	strb r5,[r2,0x5]
8e002384:	0484      	ldrb r0,[r1,0x1]
8e002386:	4404      	ldrb r2,[r1]
8e002388:	0116      	lsl r0,r0,0x8
8e00238a:	017a      	orr r0,r0,r2
8e00238c:	400b 0802 	mov r2,0x8000
8e002390:	017a      	orr r0,r0,r2
8e002392:	0414      	strb r0,[r1]
8e002394:	0106      	lsr r0,r0,0x8
8e002396:	0494      	strb r0,[r1,0x1]
8e002398:	d6cc 0400 	ldr r6,[sp,+0x5]
8e00239c:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0023a0:	b41b 2403 	add sp,sp,24
8e0023a4:	946c 0400 	ldrd r4,[sp,+0x0]
8e0023a8:	194f 0402 	rts

8e0023ac <umm_blocks>:
8e0023ac:	223b 0000 	sub r1,r0,4
8e0023b0:	0840      	blteu 8e0023c0 <umm_blocks+0x14>
8e0023b2:	019b 00ff 	add r0,r0,-5
8e0023b6:	0066      	lsr r0,r0,0x3
8e0023b8:	0113      	add r0,r0,2
8e0023ba:	000b 1002 	movt r0,0x0
8e0023be:	02e0      	b 8e0023c2 <umm_blocks+0x16>
8e0023c0:	0023      	mov r0,0x1
8e0023c2:	194f 0402 	rts
8e0023c6:	01a2      	nop

8e0023c8 <umm_make_new_block>:
8e0023c8:	460b 4032 	mov r18,0x330
8e0023cc:	400b 5002 	movt r18,0x0
8e0023d0:	284c 4800 	ldr r17,[r18,+0x0]
8e0023d4:	000b 1002 	movt r0,0x0
8e0023d8:	807f 2006 	lsl ip,r0,0x3
8e0023dc:	661f 088a 	add r3,r17,ip
8e0023e0:	6c84      	ldrb r3,[r3,0x1]
8e0023e2:	6609 4880 	ldrb r19,[r17,+ip]
8e0023e6:	200b 1002 	movt r1,0x0
8e0023ea:	6d16      	lsl r3,r3,0x8
8e0023ec:	209a      	add r1,r0,r1
8e0023ee:	6dff 010a 	orr r3,r3,r19
8e0023f2:	7feb 47f2 	mov r19,0x7fff
8e0023f6:	047f 4006 	lsl r16,r1,0x3
8e0023fa:	6ddf 010a 	and r3,r3,r19
8e0023fe:	6419 0900 	strb r3,[r17,+r16]
8e002402:	6d06      	lsr r3,r3,0x8
8e002404:	241f 490a 	add r17,r17,r16
8e002408:	649c 0800 	strb r3,[r17,+0x1]
8e00240c:	684c 0800 	ldr r3,[r18,+0x0]
8e002410:	200b 1002 	movt r1,0x0
8e002414:	0c1f 410a 	add r16,r3,r16
8e002418:	6106      	lsr r3,r0,0x8
8e00241a:	619c 0800 	strb r3,[r16,+0x3]
8e00241e:	011c 0800 	strb r0,[r16,+0x2]
8e002422:	084c 4800 	ldr r16,[r18,+0x0]
8e002426:	400b 1002 	movt r2,0x0
8e00242a:	621f 088a 	add r3,r16,ip
8e00242e:	6c84      	ldrb r3,[r3,0x1]
8e002430:	0209 0880 	ldrb r0,[r16,+ip]
8e002434:	6d16      	lsl r3,r3,0x8
8e002436:	6c7a      	orr r3,r3,r0
8e002438:	0ddf 010a 	and r0,r3,r19
8e00243c:	0076      	lsl r0,r0,0x3
8e00243e:	001f 080a 	add r0,r16,r0
8e002442:	6506      	lsr r3,r1,0x8
8e002444:	2114      	strb r1,[r0,0x2]
8e002446:	6194      	strb r3,[r0,0x3]
8e002448:	084c 0800 	ldr r0,[r18,+0x0]
8e00244c:	257a      	orr r1,r1,r2
8e00244e:	2219 0080 	strb r1,[r0,+ip]
8e002452:	2506      	lsr r1,r1,0x8
8e002454:	821f 208a 	add ip,r0,ip
8e002458:	309c 0400 	strb r1,[ip,+0x1]
8e00245c:	194f 0402 	rts

8e002460 <umm_disconnect_from_free_list>:
8e002460:	260b 0032 	mov r1,0x330
8e002464:	200b 1002 	movt r1,0x0
8e002468:	844c 2000 	ldr ip,[r1,+0x0]
8e00246c:	000b 1002 	movt r0,0x0
8e002470:	0076      	lsl r0,r0,0x3
8e002472:	101f 040a 	add r0,ip,r0
8e002476:	4284      	ldrb r2,[r0,0x5]
8e002478:	6204      	ldrb r3,[r0,0x4]
8e00247a:	4916      	lsl r2,r2,0x8
8e00247c:	69fa      	orr r3,r2,r3
8e00247e:	4384      	ldrb r2,[r0,0x7]
8e002480:	2304      	ldrb r1,[r0,0x6]
8e002482:	4916      	lsl r2,r2,0x8
8e002484:	48fa      	orr r2,r2,r1
8e002486:	4876      	lsl r2,r2,0x3
8e002488:	511f 040a 	add r2,ip,r2
8e00248c:	6a14      	strb r3,[r2,0x4]
8e00248e:	6d06      	lsr r3,r3,0x8
8e002490:	6a94      	strb r3,[r2,0x5]
8e002492:	4384      	ldrb r2,[r0,0x7]
8e002494:	6304      	ldrb r3,[r0,0x6]
8e002496:	4916      	lsl r2,r2,0x8
8e002498:	69fa      	orr r3,r2,r3
8e00249a:	4284      	ldrb r2,[r0,0x5]
8e00249c:	2204      	ldrb r1,[r0,0x4]
8e00249e:	4916      	lsl r2,r2,0x8
8e0024a0:	28fa      	orr r1,r2,r1
8e0024a2:	2476      	lsl r1,r1,0x3
8e0024a4:	309f 040a 	add r1,ip,r1
8e0024a8:	6714      	strb r3,[r1,0x6]
8e0024aa:	6d06      	lsr r3,r3,0x8
8e0024ac:	6794      	strb r3,[r1,0x7]
8e0024ae:	2084      	ldrb r1,[r0,0x1]
8e0024b0:	4004      	ldrb r2,[r0]
8e0024b2:	2516      	lsl r1,r1,0x8
8e0024b4:	257a      	orr r1,r1,r2
8e0024b6:	5feb 07f2 	mov r2,0x7fff
8e0024ba:	255a      	and r1,r1,r2
8e0024bc:	2014      	strb r1,[r0]
8e0024be:	2506      	lsr r1,r1,0x8
8e0024c0:	2094      	strb r1,[r0,0x1]
8e0024c2:	194f 0402 	rts
8e0024c6:	01a2      	nop

8e0024c8 <umm_assimilate_up>:
8e0024c8:	95fc 0700 	strd r4,[sp],-0x3
8e0024cc:	d6dc 0400 	str r6,[sp,+0x5]
8e0024d0:	c60b 0032 	mov r6,0x330
8e0024d4:	d4fc 2400 	strd lr,[sp,+0x1]
8e0024d8:	a0e2      	mov r5,r0
8e0024da:	c00b 1002 	movt r6,0x0
8e0024de:	5844      	ldr r2,[r6]
8e0024e0:	a00b 1002 	movt r5,0x0
8e0024e4:	9476      	lsl r4,r5,0x3
8e0024e6:	0a1a      	add r0,r2,r4
8e0024e8:	0084      	ldrb r0,[r0,0x1]
8e0024ea:	2a01      	ldrb r1,[r2,r4]
8e0024ec:	0116      	lsl r0,r0,0x8
8e0024ee:	00fa      	orr r0,r0,r1
8e0024f0:	2076      	lsl r1,r0,0x3
8e0024f2:	289a      	add r1,r2,r1
8e0024f4:	2484      	ldrb r1,[r1,0x1]
8e0024f6:	24e6      	lsr r1,r1,0x7
8e0024f8:	4433      	sub r2,r1,0
8e0024fa:	2a00      	beq 8e00254e <umm_assimilate_up+0x86>
8e0024fc:	2c0b 0242 	mov r1,0x2460
8e002500:	200b 18e2 	movt r1,0x8e00
8e002504:	0552      	jalr r1
8e002506:	3844      	ldr r1,[r6]
8e002508:	461a      	add r2,r1,r4
8e00250a:	4884      	ldrb r2,[r2,0x1]
8e00250c:	0601      	ldrb r0,[r1,r4]
8e00250e:	4916      	lsl r2,r2,0x8
8e002510:	487a      	orr r2,r2,r0
8e002512:	4876      	lsl r2,r2,0x3
8e002514:	451a      	add r2,r1,r2
8e002516:	0884      	ldrb r0,[r2,0x1]
8e002518:	6804      	ldrb r3,[r2]
8e00251a:	0116      	lsl r0,r0,0x8
8e00251c:	01fa      	orr r0,r0,r3
8e00251e:	7feb 07f2 	mov r3,0x7fff
8e002522:	01da      	and r0,r0,r3
8e002524:	0076      	lsl r0,r0,0x3
8e002526:	241a      	add r1,r1,r0
8e002528:	a514      	strb r5,[r1,0x2]
8e00252a:	b506      	lsr r5,r5,0x8
8e00252c:	a594      	strb r5,[r1,0x3]
8e00252e:	1844      	ldr r0,[r6]
8e002530:	821a      	add r4,r0,r4
8e002532:	5084      	ldrb r2,[r4,0x1]
8e002534:	3004      	ldrb r1,[r4]
8e002536:	4916      	lsl r2,r2,0x8
8e002538:	28fa      	orr r1,r2,r1
8e00253a:	2476      	lsl r1,r1,0x3
8e00253c:	209a      	add r1,r0,r1
8e00253e:	0404      	ldrb r0,[r1]
8e002540:	2484      	ldrb r1,[r1,0x1]
8e002542:	2516      	lsl r1,r1,0x8
8e002544:	047a      	orr r0,r1,r0
8e002546:	01da      	and r0,r0,r3
8e002548:	1014      	strb r0,[r4]
8e00254a:	0106      	lsr r0,r0,0x8
8e00254c:	1094      	strb r0,[r4,0x1]
8e00254e:	d6cc 0400 	ldr r6,[sp,+0x5]
8e002552:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002556:	b41b 2403 	add sp,sp,24
8e00255a:	946c 0400 	ldrd r4,[sp,+0x0]
8e00255e:	194f 0402 	rts
8e002562:	01a2      	nop

8e002564 <umm_assimilate_down>:
8e002564:	060b 4032 	mov r16,0x330
8e002568:	000b 5002 	movt r16,0x0
8e00256c:	204c 4800 	ldr r17,[r16,+0x0]
8e002570:	000b 1002 	movt r0,0x0
8e002574:	0076      	lsl r0,r0,0x3
8e002576:	841f 280a 	add ip,r17,r0
8e00257a:	718c 0400 	ldrb r3,[ip,+0x3]
8e00257e:	510c 0400 	ldrb r2,[ip,+0x2]
8e002582:	6d16      	lsl r3,r3,0x8
8e002584:	4d7a      	orr r2,r3,r2
8e002586:	4876      	lsl r2,r2,0x3
8e002588:	708c 0400 	ldrb r3,[ip,+0x1]
8e00258c:	451f 080a 	add r2,r17,r2
8e002590:	6d16      	lsl r3,r3,0x8
8e002592:	300c 4400 	ldrb r17,[ip,+0x0]
8e002596:	6cff 010a 	orr r3,r3,r17
8e00259a:	200b 1002 	movt r1,0x0
8e00259e:	25fa      	orr r1,r1,r3
8e0025a0:	2814      	strb r1,[r2]
8e0025a2:	2506      	lsr r1,r1,0x8
8e0025a4:	2894      	strb r1,[r2,0x1]
8e0025a6:	204c 4800 	ldr r17,[r16,+0x0]
8e0025aa:	841f 280a 	add ip,r17,r0
8e0025ae:	518c 0400 	ldrb r2,[ip,+0x3]
8e0025b2:	710c 0400 	ldrb r3,[ip,+0x2]
8e0025b6:	4916      	lsl r2,r2,0x8
8e0025b8:	69fa      	orr r3,r2,r3
8e0025ba:	508c 0400 	ldrb r2,[ip,+0x1]
8e0025be:	300c 0400 	ldrb r1,[ip,+0x0]
8e0025c2:	4916      	lsl r2,r2,0x8
8e0025c4:	28fa      	orr r1,r2,r1
8e0025c6:	2476      	lsl r1,r1,0x3
8e0025c8:	249f 080a 	add r1,r17,r1
8e0025cc:	6514      	strb r3,[r1,0x2]
8e0025ce:	6d06      	lsr r3,r3,0x8
8e0025d0:	6594      	strb r3,[r1,0x3]
8e0025d2:	204c 0800 	ldr r1,[r16,+0x0]
8e0025d6:	041a      	add r0,r1,r0
8e0025d8:	2104      	ldrb r1,[r0,0x2]
8e0025da:	0184      	ldrb r0,[r0,0x3]
8e0025dc:	0116      	lsl r0,r0,0x8
8e0025de:	00fa      	orr r0,r0,r1
8e0025e0:	194f 0402 	rts

8e0025e4 <bj_add_lk_syms>:
8e0025e4:	d4fc 2700 	strd lr,[sp],-0x1
8e0025e8:	f41b 2401 	add fp,sp,8
8e0025ec:	000b 0002 	mov r0,0x0
8e0025f0:	000b 18e2 	movt r0,0x8e00
8e0025f4:	3f8b 0032 	mov r1,0x3fc
8e0025f8:	200b 18e2 	movt r1,0x8e00
8e0025fc:	0552      	jalr r1
8e0025fe:	000b 0002 	mov r0,0x0
8e002602:	000b 18e2 	movt r0,0x8e00
8e002606:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e00260a:	b41b 2401 	add sp,sp,8
8e00260e:	194f 0402 	rts
8e002612:	01a2      	nop

8e002614 <bj_host_addr_to_core_addr>:
8e002614:	d57c 2700 	strd lr,[sp],-0x2
8e002618:	f41b 2402 	add fp,sp,16
8e00261c:	1cdc 0500 	str r0,[fp,-0x1]
8e002620:	028b 0262 	mov r0,0x2614
8e002624:	000b 18e2 	movt r0,0x8e00
8e002628:	300b 0272 	mov r1,0x2780
8e00262c:	200b 18e2 	movt r1,0x8e00
8e002630:	4e0b 0092 	mov r2,0x970
8e002634:	400b 18e2 	movt r2,0x8e00
8e002638:	0952      	jalr r2
8e00263a:	0003      	mov r0,0x0
8e00263c:	d56c 2400 	ldrd lr,[sp,+0x2]
8e002640:	b41b 2402 	add sp,sp,16
8e002644:	194f 0402 	rts

8e002648 <bj_core_addr_to_host_addr>:
8e002648:	d57c 2700 	strd lr,[sp],-0x2
8e00264c:	f41b 2402 	add fp,sp,16
8e002650:	1cdc 0500 	str r0,[fp,-0x1]
8e002654:	090b 0262 	mov r0,0x2648
8e002658:	000b 18e2 	movt r0,0x8e00
8e00265c:	350b 0272 	mov r1,0x27a8
8e002660:	200b 18e2 	movt r1,0x8e00
8e002664:	4e0b 0092 	mov r2,0x970
8e002668:	400b 18e2 	movt r2,0x8e00
8e00266c:	0952      	jalr r2
8e00266e:	0003      	mov r0,0x0
8e002670:	d56c 2400 	ldrd lr,[sp,+0x2]
8e002674:	b41b 2402 	add sp,sp,16
8e002678:	194f 0402 	rts
8e00267c:	0000      	beq 8e00267c <bj_core_addr_to_host_addr+0x34>
	...

8e002680 <err_1>:
8e002680:	6361      	ldrd r3,[r0,r6]
8e002682:	7571      	strd r3,[r5,r2]
8e002684:	7269 5f65 	*unknown*
8e002688:	6c61      	ldrd r3,[r3,r0]
8e00268a:	6f6c 2063 	ldrd r11,[r3,+0x31e]
8e00268e:	6261      	ldrd r3,[r0,r4]
8e002690:	726f 0a74 	*unknown*
8e002694:	0000      	beq 8e002694 <err_1+0x14>
	...

8e002698 <err_2>:
8e002698:	6a62 685f 	*unknown*
8e00269c:	736f 5f74 	*unknown*
8e0026a0:	6e69 7469 	*unknown*
8e0026a4:	6120      	bgtu 8e002766 <err_10+0xe>
8e0026a6:	6f62 7472 	*unknown*
8e0026aa:	000a      	eor r0,r0,r0
8e0026ac:	0000      	beq 8e0026ac <err_2+0x14>
	...

8e0026b0 <err_3>:
8e0026b0:	6a62 685f 	*unknown*
8e0026b4:	736f 5f74 	*unknown*
8e0026b8:	7572 206e 	*unknown*
8e0026bc:	6261      	ldrd r3,[r0,r4]
8e0026be:	726f 0a74 	*unknown*
8e0026c2:	0000      	beq 8e0026c2 <err_3+0x12>
8e0026c4:	0000      	beq 8e0026c4 <err_3+0x14>
	...

8e0026c8 <err_4>:
8e0026c8:	6a62 685f 	*unknown*
8e0026cc:	736f 5f74 	*unknown*
8e0026d0:	6966      	lsr r3,r2,0xb
8e0026d2:	696e      	asr r3,r2,0xb
8e0026d4:	6873 6120 	*unknown*
8e0026d8:	6f62 7472 	*unknown*
8e0026dc:	000a      	eor r0,r0,r0
	...

8e0026e0 <err_5>:
8e0026e0:	6261      	ldrd r3,[r0,r4]
8e0026e2:	726f 2874 	*unknown*
8e0026e6:	2029 6261 	*unknown*
8e0026ea:	726f 0a74 	*unknown*
	...

8e0026f0 <err_6>:
8e0026f0:	6a62 5f6b 	*unknown*
8e0026f4:	6c67      	fix r3,r3
8e0026f6:	5f62 6e69 	*unknown*
8e0026fa:	7469 6120 	*unknown*
8e0026fe:	6f62 7472 	*unknown*
8e002702:	315f 0a2e 	*unknown*
	...

8e002708 <err_7>:
8e002708:	6a62 5f6b 	*unknown*
8e00270c:	6c67      	fix r3,r3
8e00270e:	5f62 6e69 	*unknown*
8e002712:	7469 6120 	*unknown*
8e002716:	6f62 7472 	*unknown*
8e00271a:	325f 0a2e 	*unknown*
	...

8e002720 <err_8>:
8e002720:	6a62 5f6b 	*unknown*
8e002724:	6c67      	fix r3,r3
8e002726:	5f62 6e69 	*unknown*
8e00272a:	7469 6120 	*unknown*
8e00272e:	6f62 7472 	*unknown*
8e002732:	335f 0a2e 	*unknown*
	...

8e002738 <err_9>:
8e002738:	6761      	ldrd r3,[r1,r6]
8e00273a:	6e65      	ldrd r3,[r3],r4
8e00273c:	3a74      	strd r1,[r6,0x4]
8e00273e:	673a      	sub r3,r1,r6
8e002740:	7465      	ldrd r3,[r5],r0
8e002742:	615f 6176 	*unknown*
8e002746:	6c69 6261 	*unknown*
8e00274a:	656c 6120 	ldrd r27,[r1,-0x102]
8e00274e:	6f62 7472 	*unknown*
8e002752:	000a      	eor r0,r0,r0
8e002754:	0000      	beq 8e002754 <err_9+0x1c>
	...

8e002758 <err_10>:
8e002758:	6761      	ldrd r3,[r1,r6]
8e00275a:	6e65      	ldrd r3,[r3],r4
8e00275c:	3a74      	strd r1,[r6,0x4]
8e00275e:	693a      	sub r3,r2,r2
8e002760:	696e      	asr r3,r2,0xb
8e002762:	5f74      	strd r2,[r7,0x6]
8e002764:	656d 6120 	*unknown*
8e002768:	6f62 7472 	*unknown*
8e00276c:	000a      	eor r0,r0,r0
	...

8e002770 <err_11>:
8e002770:	7361      	ldrd r3,[r4,r6]
8e002772:	6573 7472 	*unknown*
8e002776:	6120      	bgtu 8e002838 <err_13+0x90>
8e002778:	6f62 7472 	*unknown*
8e00277c:	000a      	eor r0,r0,r0
	...

8e002780 <err_12>:
8e002780:	6a62 685f 	*unknown*
8e002784:	736f 5f74 	*unknown*
8e002788:	6461      	ldrd r3,[r1,r0]
8e00278a:	7264      	ldrd r3,[r4,0x4]
8e00278c:	745f 5f6f 	*unknown*
8e002790:	6f63      	mov r3,0x7b
8e002792:	6572 615f 	*unknown*
8e002796:	6464      	ldrd r3,[r1]
8e002798:	2072      	movgte r1,r0
8e00279a:	6261      	ldrd r3,[r0,r4]
8e00279c:	726f 0a74 	*unknown*
	...

8e0027a8 <err_13>:
8e0027a8:	6a62 635f 	*unknown*
8e0027ac:	726f 5f65 	*unknown*
8e0027b0:	6461      	ldrd r3,[r1,r0]
8e0027b2:	7264      	ldrd r3,[r4,0x4]
8e0027b4:	745f 5f6f 	*unknown*
8e0027b8:	6f68 7473 	bgt 8ee90e96 <LD_EXTERNAL_LOAD_ORIG+0x690e96>
8e0027bc:	615f 6464 	*unknown*
8e0027c0:	2072      	movgte r1,r0
8e0027c2:	6261      	ldrd r3,[r0,r4]
8e0027c4:	726f 0a74 	*unknown*
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
 114:	2b0b 0032 	mov r1,0x358
 118:	200b 1002 	movt r1,0x0
 11c:	4e0b 0092 	mov r2,0x970
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
 23c:	0f8b 0032 	mov r0,0x37c
 240:	54fc 0400 	strd r2,[sp,+0x1]
 244:	000b 1002 	movt r0,0x0
 248:	0044      	ldr r0,[r0]
 24a:	2023      	mov r1,0x1
 24c:	229c 0004 	strb r1,[r0,+0x25]
 250:	250b 0022 	mov r1,0x228
 254:	200b 1002 	movt r1,0x0
 258:	22d4      	str r1,[r0,0x5]
 25a:	0044      	ldr r0,[r0]
 25c:	2033      	sub r1,r0,0
 25e:	0b00      	beq 274 <bjk_software_exception_handler+0x4c>
 260:	4044      	ldr r2,[r0]
 262:	3bab 0cc2 	mov r1,0xccdd
 266:	376b 1aa2 	movt r1,0xaabb
 26a:	68ba      	sub r3,r2,r1
 26c:	0410      	bne 274 <bjk_software_exception_handler+0x4c>
 26e:	3e2b 0ff2 	mov r1,0xfff1
 272:	2314      	strb r1,[r0,0x6]
 274:	0fe2      	trap 0x3
 276:	156c 0400 	ldrd r0,[sp,+0x2]
 27a:	54ec 0400 	ldrd r2,[sp,+0x1]
 27e:	0392      	gid
 280:	b41b 2404 	add sp,sp,32
 284:	0502      	movts status,r0
 286:	210f 0402 	movts iret,r1
 28a:	14ec 0500 	ldrd r0,[sp,-0x1]
 28e:	01d2      	rti

00000290 <bjk_page_miss_handler>:
 290:	14fc 0500 	strd r0,[sp,-0x1]
 294:	0512      	movfs r0,status
 296:	211f 0402 	movfs r1,iret
 29a:	b41b 24fc 	add sp,sp,-32
 29e:	0192      	gie
 2a0:	157c 0400 	strd r0,[sp,+0x2]
 2a4:	0f8b 0032 	mov r0,0x37c
 2a8:	54fc 0400 	strd r2,[sp,+0x1]
 2ac:	000b 1002 	movt r0,0x0
 2b0:	0044      	ldr r0,[r0]
 2b2:	2043      	mov r1,0x2
 2b4:	229c 0004 	strb r1,[r0,+0x25]
 2b8:	320b 0022 	mov r1,0x290
 2bc:	200b 1002 	movt r1,0x0
 2c0:	22d4      	str r1,[r0,0x5]
 2c2:	0044      	ldr r0,[r0]
 2c4:	2033      	sub r1,r0,0
 2c6:	0b00      	beq 2dc <bjk_page_miss_handler+0x4c>
 2c8:	4044      	ldr r2,[r0]
 2ca:	3bab 0cc2 	mov r1,0xccdd
 2ce:	376b 1aa2 	movt r1,0xaabb
 2d2:	68ba      	sub r3,r2,r1
 2d4:	0410      	bne 2dc <bjk_page_miss_handler+0x4c>
 2d6:	3e2b 0ff2 	mov r1,0xfff1
 2da:	2314      	strb r1,[r0,0x6]
 2dc:	0fe2      	trap 0x3
 2de:	156c 0400 	ldrd r0,[sp,+0x2]
 2e2:	54ec 0400 	ldrd r2,[sp,+0x1]
 2e6:	0392      	gid
 2e8:	b41b 2404 	add sp,sp,32
 2ec:	0502      	movts status,r0
 2ee:	210f 0402 	movts iret,r1
 2f2:	14ec 0500 	ldrd r0,[sp,-0x1]
 2f6:	01d2      	rti

000002f8 <bjk_timer0_handler>:
 2f8:	14fc 0500 	strd r0,[sp,-0x1]
 2fc:	0512      	movfs r0,status
 2fe:	211f 0402 	movfs r1,iret
 302:	b41b 24fd 	add sp,sp,-24
 306:	0192      	gie
 308:	14fc 0400 	strd r0,[sp,+0x1]
 30c:	2f0b 0032 	mov r1,0x378
 310:	200b 1002 	movt r1,0x0
 314:	0444      	ldr r0,[r1]
 316:	0093      	add r0,r0,1
 318:	0454      	str r0,[r1]
 31a:	14ec 0400 	ldrd r0,[sp,+0x1]
 31e:	0392      	gid
 320:	b41b 2403 	add sp,sp,24
 324:	0502      	movts status,r0
 326:	210f 0402 	movts iret,r1
 32a:	14ec 0500 	ldrd r0,[sp,-0x1]
 32e:	01d2      	rti

Disassembly of section .data:

00000330 <umm_heap>:
 330:	5000      	beq 3d0 <bjk_system_sz+0x50>
	...

Disassembly of section .rodata:

00000338 <.rodata>:
 338:	4142 4b43 	*unknown*
 33c:	5254      	str r2,[r4,0x4]
 33e:	4341      	ldr r2,[r0,r6]
 340:	5f45      	ldr r2,[r7],r6
 342:	4554      	str r2,[r1,0x2]
 344:	5453 000a 	*unknown*
 348:	6163      	mov r3,0xb
 34a:	6c6c 6e69 	ldrd r27,[r27],+0x348
 34e:	2067      	fix r1,r0
 350:	7566      	lsr r3,r5,0xb
 352:	636e      	asr r3,r0,0x1b
 354:	0033      	sub r0,r0,0
 356:	0000      	beq 356 <umm_heap+0x26>
 358:	6f46      	lsr r3,r3,0x1a
 35a:	6372 6465 	*unknown*
 35e:	6120      	bgtu 420 <bjk_system_sz+0xa0>
 360:	6f62 7472 	*unknown*
 364:	6920      	bgtu 436 <bjk_system_sz+0xb6>
 366:	206e      	asr r1,r0,0x3
 368:	6162 6b63 	*unknown*
 36c:	7274      	strd r3,[r4,0x4]
 36e:	6361      	ldrd r3,[r0,r6]
 370:	2065      	ldrd r1,[r0],r0
 372:	6574      	strd r3,[r1,0x2]
 374:	7473 0000 	*unknown*

Disassembly of section .bss:

00000378 <test_send_irq3>:
 378:	0000      	beq 378 <test_send_irq3>
	...

0000037c <bjk_glb_pt_sys_data>:
 37c:	0000      	beq 37c <bjk_glb_pt_sys_data>
	...

00000380 <bjk_system_sz>:
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

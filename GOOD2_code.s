
bin/bj-core-actor.elf:     file format elf32-epiphany


Disassembly of section ivt_reset:

00000000 <_start>:
   0:	e4e8 0002 	b 5c8 <normal_start>

Disassembly of section ivt_software_exception:

00000004 <irq1_entry>:
   4:	b4e8 0000 	b 16c <bjk_irq1_handler>

Disassembly of section ivt_page_miss:

00000008 <irq2_entry>:
   8:	4ae8 0001 	b 29c <bjk_irq2_handler>

Disassembly of section ivt_timer0:

0000000c <irq3_entry>:
   c:	66e8 0001 	b 2d8 <bjk_irq3_handler>

Disassembly of section ivt_timer1:

00000010 <irq4_entry>:
  10:	90e8 0001 	b 330 <bjk_irq4_handler>

Disassembly of section ivt_message:

00000014 <irq5_entry>:
  14:	bae8 0001 	b 388 <bjk_irq5_handler>

Disassembly of section ivt_dma0:

00000018 <irq6_entry>:
  18:	e4e8 0001 	b 3e0 <bjk_irq6_handler>

Disassembly of section ivt_dma1:

0000001c <irq7_entry>:
  1c:	0ee8 0002 	b 438 <bjk_irq7_handler>

Disassembly of section ivt_wand:

00000020 <irq8_entry>:
  20:	38e8 0002 	b 490 <bjk_irq8_handler>

Disassembly of section ivt_user:

00000024 <irq9_entry>:
  24:	64e8 0002 	b 4ec <bjk_irq9_handler>

Disassembly of section workgroup_cfg:

00000028 <workgroup_cfg>:
	...

Disassembly of section ext_mem_cfg:

00000050 <ext_mem_cfg>:
	...

Disassembly of section loader_cfg:

00000058 <loader_cfg>:
	...

Disassembly of section .data_bank2:

00004000 <umm_heap>:
	...

Disassembly of section .code_dram:

8e000000 <umm_info>:
8e000000:	d67c 2700 	strd lr,[sp],-0x4
8e000004:	f41b 2404 	add fp,sp,32
8e000008:	1edc 0500 	str r0,[fp,-0x5]
8e00000c:	3f5c 0500 	str r1,[fp,-0x6]
8e000010:	0003      	mov r0,0x0
8e000012:	1cbc 0500 	strh r0,[fp,-0x1]
8e000016:	0e0b 0192 	mov r0,0x1970
8e00001a:	000b 1002 	movt r0,0x0
8e00001e:	1d5c 0500 	str r0,[fp,-0x2]
8e000022:	0003      	mov r0,0x0
8e000024:	1c9c 0501 	strb r0,[fp,-0x9]
8e000028:	0203      	mov r0,0x10
8e00002a:	1f3c 0500 	strh r0,[fp,-0x6]
8e00002e:	1c8c 0501 	ldrb r0,[fp,-0x9]
8e000032:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000036:	44e2      	mov r2,r1
8e000038:	20e2      	mov r1,r0
8e00003a:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00003e:	620b 0072 	mov r3,0x710
8e000042:	600b 18e2 	movt r3,0x8e00
8e000046:	0d52      	jalr r3
8e000048:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00004c:	200b 0402 	mov r1,0x4000
8e000050:	200b 1002 	movt r1,0x0
8e000054:	0076      	lsl r0,r0,0x3
8e000056:	041a      	add r0,r1,r0
8e000058:	2024      	ldrh r1,[r0]
8e00005a:	1feb 07f2 	mov r0,0x7fff
8e00005e:	045a      	and r0,r1,r0
8e000060:	1cbc 0500 	strh r0,[fp,-0x1]
8e000064:	bfe8 0000 	b 8e0001e2 <umm_info+0x1e2>
8e000068:	0e0b 0192 	mov r0,0x1970
8e00006c:	000b 1002 	movt r0,0x0
8e000070:	0024      	ldrh r0,[r0]
8e000072:	0093      	add r0,r0,1
8e000074:	20e2      	mov r1,r0
8e000076:	200b 1002 	movt r1,0x0
8e00007a:	0e0b 0192 	mov r0,0x1970
8e00007e:	000b 1002 	movt r0,0x0
8e000082:	2034      	strh r1,[r0]
8e000084:	0e0b 0192 	mov r0,0x1970
8e000088:	000b 1002 	movt r0,0x0
8e00008c:	21a4      	ldrh r1,[r0,0x3]
8e00008e:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000092:	400b 0402 	mov r2,0x4000
8e000096:	400b 1002 	movt r2,0x0
8e00009a:	0076      	lsl r0,r0,0x3
8e00009c:	081a      	add r0,r2,r0
8e00009e:	4024      	ldrh r2,[r0]
8e0000a0:	1feb 07f2 	mov r0,0x7fff
8e0000a4:	085a      	and r0,r2,r0
8e0000a6:	40e2      	mov r2,r0
8e0000a8:	400b 1002 	movt r2,0x0
8e0000ac:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0000b0:	083a      	sub r0,r2,r0
8e0000b2:	000b 1002 	movt r0,0x0
8e0000b6:	041a      	add r0,r1,r0
8e0000b8:	20e2      	mov r1,r0
8e0000ba:	200b 1002 	movt r1,0x0
8e0000be:	0e0b 0192 	mov r0,0x1970
8e0000c2:	000b 1002 	movt r0,0x0
8e0000c6:	21b4      	strh r1,[r0,0x3]
8e0000c8:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0000cc:	200b 0402 	mov r1,0x4000
8e0000d0:	200b 1002 	movt r1,0x0
8e0000d4:	0076      	lsl r0,r0,0x3
8e0000d6:	041a      	add r0,r1,r0
8e0000d8:	0024      	ldrh r0,[r0]
8e0000da:	000b 1002 	movt r0,0x0
8e0000de:	0216      	lsl r0,r0,0x10
8e0000e0:	020e      	asr r0,r0,0x10
8e0000e2:	2033      	sub r1,r0,0
8e0000e4:	4170      	bgte 8e000166 <umm_info+0x166>
8e0000e6:	0e0b 0192 	mov r0,0x1970
8e0000ea:	000b 1002 	movt r0,0x0
8e0000ee:	0124      	ldrh r0,[r0,0x2]
8e0000f0:	0093      	add r0,r0,1
8e0000f2:	20e2      	mov r1,r0
8e0000f4:	200b 1002 	movt r1,0x0
8e0000f8:	0e0b 0192 	mov r0,0x1970
8e0000fc:	000b 1002 	movt r0,0x0
8e000100:	2134      	strh r1,[r0,0x2]
8e000102:	0e0b 0192 	mov r0,0x1970
8e000106:	000b 1002 	movt r0,0x0
8e00010a:	22a4      	ldrh r1,[r0,0x5]
8e00010c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000110:	400b 0402 	mov r2,0x4000
8e000114:	400b 1002 	movt r2,0x0
8e000118:	0076      	lsl r0,r0,0x3
8e00011a:	081a      	add r0,r2,r0
8e00011c:	4024      	ldrh r2,[r0]
8e00011e:	1feb 07f2 	mov r0,0x7fff
8e000122:	085a      	and r0,r2,r0
8e000124:	40e2      	mov r2,r0
8e000126:	400b 1002 	movt r2,0x0
8e00012a:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00012e:	083a      	sub r0,r2,r0
8e000130:	000b 1002 	movt r0,0x0
8e000134:	041a      	add r0,r1,r0
8e000136:	20e2      	mov r1,r0
8e000138:	200b 1002 	movt r1,0x0
8e00013c:	0e0b 0192 	mov r0,0x1970
8e000140:	000b 1002 	movt r0,0x0
8e000144:	22b4      	strh r1,[r0,0x5]
8e000146:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00014a:	2076      	lsl r1,r0,0x3
8e00014c:	000b 0402 	mov r0,0x4000
8e000150:	000b 1002 	movt r0,0x0
8e000154:	241a      	add r1,r1,r0
8e000156:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00015a:	443a      	sub r2,r1,r0
8e00015c:	3510      	bne 8e0001c6 <umm_info+0x1c6>
8e00015e:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000162:	81e8 0000 	b 8e000264 <umm_info+0x264>
8e000166:	0e0b 0192 	mov r0,0x1970
8e00016a:	000b 1002 	movt r0,0x0
8e00016e:	00a4      	ldrh r0,[r0,0x1]
8e000170:	0093      	add r0,r0,1
8e000172:	20e2      	mov r1,r0
8e000174:	200b 1002 	movt r1,0x0
8e000178:	0e0b 0192 	mov r0,0x1970
8e00017c:	000b 1002 	movt r0,0x0
8e000180:	20b4      	strh r1,[r0,0x1]
8e000182:	0e0b 0192 	mov r0,0x1970
8e000186:	000b 1002 	movt r0,0x0
8e00018a:	2224      	ldrh r1,[r0,0x4]
8e00018c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000190:	400b 0402 	mov r2,0x4000
8e000194:	400b 1002 	movt r2,0x0
8e000198:	0076      	lsl r0,r0,0x3
8e00019a:	081a      	add r0,r2,r0
8e00019c:	4024      	ldrh r2,[r0]
8e00019e:	1feb 07f2 	mov r0,0x7fff
8e0001a2:	085a      	and r0,r2,r0
8e0001a4:	40e2      	mov r2,r0
8e0001a6:	400b 1002 	movt r2,0x0
8e0001aa:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0001ae:	083a      	sub r0,r2,r0
8e0001b0:	000b 1002 	movt r0,0x0
8e0001b4:	041a      	add r0,r1,r0
8e0001b6:	20e2      	mov r1,r0
8e0001b8:	200b 1002 	movt r1,0x0
8e0001bc:	0e0b 0192 	mov r0,0x1970
8e0001c0:	000b 1002 	movt r0,0x0
8e0001c4:	2234      	strh r1,[r0,0x4]
8e0001c6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0001ca:	200b 0402 	mov r1,0x4000
8e0001ce:	200b 1002 	movt r1,0x0
8e0001d2:	0076      	lsl r0,r0,0x3
8e0001d4:	041a      	add r0,r1,r0
8e0001d6:	2024      	ldrh r1,[r0]
8e0001d8:	1feb 07f2 	mov r0,0x7fff
8e0001dc:	045a      	and r0,r1,r0
8e0001de:	1cbc 0500 	strh r0,[fp,-0x1]
8e0001e2:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0001e6:	200b 0402 	mov r1,0x4000
8e0001ea:	200b 1002 	movt r1,0x0
8e0001ee:	0076      	lsl r0,r0,0x3
8e0001f0:	041a      	add r0,r1,r0
8e0001f2:	0024      	ldrh r0,[r0]
8e0001f4:	20e2      	mov r1,r0
8e0001f6:	1feb 07f2 	mov r0,0x7fff
8e0001fa:	045a      	and r0,r1,r0
8e0001fc:	2033      	sub r1,r0,0
8e0001fe:	3518 ffff 	bne 8e000068 <umm_info+0x68>
8e000202:	0e0b 0192 	mov r0,0x1970
8e000206:	000b 1002 	movt r0,0x0
8e00020a:	22a4      	ldrh r1,[r0,0x5]
8e00020c:	130b 0172 	mov r0,0x1798
8e000210:	000b 1002 	movt r0,0x0
8e000214:	4024      	ldrh r2,[r0]
8e000216:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00021a:	083a      	sub r0,r2,r0
8e00021c:	000b 1002 	movt r0,0x0
8e000220:	041a      	add r0,r1,r0
8e000222:	20e2      	mov r1,r0
8e000224:	200b 1002 	movt r1,0x0
8e000228:	0e0b 0192 	mov r0,0x1970
8e00022c:	000b 1002 	movt r0,0x0
8e000230:	22b4      	strh r1,[r0,0x5]
8e000232:	0e0b 0192 	mov r0,0x1970
8e000236:	000b 1002 	movt r0,0x0
8e00023a:	21a4      	ldrh r1,[r0,0x3]
8e00023c:	130b 0172 	mov r0,0x1798
8e000240:	000b 1002 	movt r0,0x0
8e000244:	4024      	ldrh r2,[r0]
8e000246:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00024a:	083a      	sub r0,r2,r0
8e00024c:	000b 1002 	movt r0,0x0
8e000250:	041a      	add r0,r1,r0
8e000252:	20e2      	mov r1,r0
8e000254:	200b 1002 	movt r1,0x0
8e000258:	0e0b 0192 	mov r0,0x1970
8e00025c:	000b 1002 	movt r0,0x0
8e000260:	21b4      	strh r1,[r0,0x3]
8e000262:	0003      	mov r0,0x0
8e000264:	d66c 2400 	ldrd lr,[sp,+0x4]
8e000268:	b41b 2404 	add sp,sp,32
8e00026c:	194f 0402 	rts

8e000270 <umm_malloc>:
8e000270:	967c 0700 	strd r4,[sp],-0x4
8e000274:	000b 1002 	movt r0,0x0
8e000278:	d5fc 0400 	strd r6,[sp,+0x3]
8e00027c:	16dc 2400 	str r8,[sp,+0x5]
8e000280:	d4fc 2400 	strd lr,[sp,+0x1]
8e000284:	2033      	sub r1,r0,0
8e000286:	8608 0000 	beq 8e000392 <umm_malloc+0x122>
8e00028a:	3a0b 0052 	mov r1,0x5d0
8e00028e:	200b 18e2 	movt r1,0x8e00
8e000292:	0552      	jalr r1
8e000294:	c00b 0402 	mov r6,0x4000
8e000298:	c00b 1002 	movt r6,0x0
8e00029c:	992c 2000 	ldrh ip,[r6,+0x2]
8e0002a0:	90ef 0402 	mov r4,ip
8e0002a4:	5feb 07f2 	mov r2,0x7fff
8e0002a8:	2003      	mov r1,0x0
8e0002aa:	3feb 47f2 	mov r17,0x7fff
8e0002ae:	7076      	lsl r3,r4,0x3
8e0002b0:	799a      	add r3,r6,r3
8e0002b2:	0d2c 4000 	ldrh r16,[r3,+0x2]
8e0002b6:	403b 4800 	sub r18,r16,0
8e0002ba:	1200      	beq 8e0002de <umm_malloc+0x6e>
8e0002bc:	2c24      	ldrh r1,[r3]
8e0002be:	24df 010a 	and r1,r1,r17
8e0002c2:	263a      	sub r1,r1,r4
8e0002c4:	200b 1002 	movt r1,0x0
8e0002c8:	60ba      	sub r3,r0,r1
8e0002ca:	0720      	bgtu 8e0002d8 <umm_malloc+0x68>
8e0002cc:	48bf 400a 	sub r18,r2,r1
8e0002d0:	0440      	blteu 8e0002d8 <umm_malloc+0x68>
8e0002d2:	90ef 2002 	mov ip,r4
8e0002d6:	44e2      	mov r2,r1
8e0002d8:	80ef 0802 	mov r4,r16
8e0002dc:	e9e0      	b 8e0002ae <umm_malloc+0x3e>
8e0002de:	7feb 07f2 	mov r3,0x7fff
8e0002e2:	09bf 400a 	sub r16,r2,r3
8e0002e6:	901f 0402 	movne r4,ip
8e0002ea:	2812      	movne r1,r2
8e0002ec:	5076      	lsl r2,r4,0x3
8e0002ee:	5921      	ldrh r2,[r6,r2]
8e0002f0:	9feb 27f2 	mov ip,0x7fff
8e0002f4:	600b 0402 	mov r3,0x4000
8e0002f8:	4a5f 008a 	and r2,r2,ip
8e0002fc:	600b 1002 	movt r3,0x0
8e000300:	1b00      	beq 8e000336 <umm_malloc+0xc6>
8e000302:	043f 400a 	sub r16,r1,r0
8e000306:	0810      	bne 8e000316 <umm_malloc+0xa6>
8e000308:	268b 0062 	mov r1,0x634
8e00030c:	10e2      	mov r0,r4
8e00030e:	200b 18e2 	movt r1,0x8e00
8e000312:	0552      	jalr r1
8e000314:	3ae0      	b 8e000388 <umm_malloc+0x118>
8e000316:	a43a      	sub r5,r1,r0
8e000318:	a00b 1002 	movt r5,0x0
8e00031c:	7d8b 0052 	mov r3,0x5ec
8e000320:	10e2      	mov r0,r4
8e000322:	400b 0802 	mov r2,0x8000
8e000326:	34e2      	mov r1,r5
8e000328:	600b 18e2 	movt r3,0x8e00
8e00032c:	929a      	add r4,r4,r5
8e00032e:	0d52      	jalr r3
8e000330:	800b 1002 	movt r4,0x0
8e000334:	2ae0      	b 8e000388 <umm_malloc+0x118>
8e000336:	330b 0172 	mov r1,0x1798
8e00033a:	200b 1002 	movt r1,0x0
8e00033e:	4424      	ldrh r2,[r1]
8e000340:	301a      	add r1,r4,r0
8e000342:	2493      	add r1,r1,1
8e000344:	48bf 400a 	sub r18,r2,r1
8e000348:	2590      	blte 8e000392 <umm_malloc+0x122>
8e00034a:	3033      	sub r1,r4,0
8e00034c:	0510      	bne 8e000356 <umm_malloc+0xe6>
8e00034e:	2023      	mov r1,0x1
8e000350:	8023      	mov r4,0x1
8e000352:	2c34      	strh r1,[r3]
8e000354:	2d34      	strh r1,[r3,0x2]
8e000356:	f076      	lsl r7,r4,0x3
8e000358:	fb9a      	add r7,r6,r7
8e00035a:	b01a      	add r5,r4,r0
8e00035c:	1da4      	ldrh r0,[r7,0x3]
8e00035e:	14ef 2002 	mov r8,r5
8e000362:	0076      	lsl r0,r0,0x3
8e000364:	b476      	lsl r5,r5,0x3
8e000366:	000b 3002 	movt r8,0x0
8e00036a:	181a      	add r0,r6,r0
8e00036c:	ba9a      	add r5,r6,r5
8e00036e:	668b 0072 	mov r3,0x734
8e000372:	013c 2000 	strh r8,[r0,+0x2]
8e000376:	4103      	mov r2,0x8
8e000378:	3ce2      	mov r1,r7
8e00037a:	14e2      	mov r0,r5
8e00037c:	600b 18e2 	movt r3,0x8e00
8e000380:	0d52      	jalr r3
8e000382:	1c3c 2000 	strh r8,[r7]
8e000386:	94b4      	strh r4,[r5,0x1]
8e000388:	1076      	lsl r0,r4,0x3
8e00038a:	181a      	add r0,r6,r0
8e00038c:	021b 0000 	add r0,r0,4
8e000390:	02e0      	b 8e000394 <umm_malloc+0x124>
8e000392:	0003      	mov r0,0x0
8e000394:	d5ec 0400 	ldrd r6,[sp,+0x3]
8e000398:	16cc 2400 	ldr r8,[sp,+0x5]
8e00039c:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0003a0:	b41b 2404 	add sp,sp,32
8e0003a4:	946c 0400 	ldrd r4,[sp,+0x0]
8e0003a8:	194f 0402 	rts

8e0003ac <umm_realloc>:
8e0003ac:	96fc 0700 	strd r4,[sp],-0x5
8e0003b0:	d67c 0400 	strd r6,[sp,+0x4]
8e0003b4:	15fc 2400 	strd r8,[sp,+0x3]
8e0003b8:	e4e2      	mov r7,r1
8e0003ba:	557c 2400 	strd r10,[sp,+0x2]
8e0003be:	d4fc 2400 	strd lr,[sp,+0x1]
8e0003c2:	805a      	and r4,r0,r0
8e0003c4:	e00b 1002 	movt r7,0x0
8e0003c8:	1310      	bne 8e0003ee <umm_realloc+0x42>
8e0003ca:	1ce2      	mov r0,r7
8e0003cc:	15ec 2400 	ldrd r8,[sp,+0x3]
8e0003d0:	d66c 0400 	ldrd r6,[sp,+0x4]
8e0003d4:	556c 2400 	ldrd r10,[sp,+0x2]
8e0003d8:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0003dc:	b41b 2405 	add sp,sp,40
8e0003e0:	2e0b 0022 	mov r1,0x270
8e0003e4:	946c 0400 	ldrd r4,[sp,+0x0]
8e0003e8:	200b 18e2 	movt r1,0x8e00
8e0003ec:	0542      	jr r1
8e0003ee:	3c33      	sub r1,r7,0
8e0003f0:	0910      	bne 8e000402 <umm_realloc+0x56>
8e0003f2:	280b 0052 	mov r1,0x540
8e0003f6:	200b 18e2 	movt r1,0x8e00
8e0003fa:	0552      	jalr r1
8e0003fc:	0003      	mov r0,0x0
8e0003fe:	92e8 0000 	b 8e000522 <umm_realloc+0x176>
8e000402:	000b 2402 	mov r8,0x4000
8e000406:	000b 3002 	movt r8,0x0
8e00040a:	3a0b 0052 	mov r1,0x5d0
8e00040e:	303f 208a 	sub r9,r4,r8
8e000412:	1ce2      	mov r0,r7
8e000414:	200b 18e2 	movt r1,0x8e00
8e000418:	0552      	jalr r1
8e00041a:	246f 2406 	lsr r9,r9,0x3
8e00041e:	44ef 2402 	mov r10,r9
8e000422:	400b 3002 	movt r10,0x0
8e000426:	687f 2406 	lsl r11,r10,0x3
8e00042a:	619f 248a 	add r11,r8,r11
8e00042e:	ac2c 0400 	ldrh r5,[r11,+0x0]
8e000432:	b53f 008a 	sub r5,r5,r10
8e000436:	a00b 1002 	movt r5,0x0
8e00043a:	42ba      	sub r2,r0,r5
8e00043c:	c0e2      	mov r6,r0
8e00043e:	7100      	beq 8e000520 <umm_realloc+0x174>
8e000440:	2c8b 0062 	mov r1,0x664
8e000444:	08ef 0402 	mov r0,r10
8e000448:	200b 18e2 	movt r1,0x8e00
8e00044c:	0552      	jalr r1
8e00044e:	0cac 0400 	ldrh r0,[r11,+0x1]
8e000452:	b476      	lsl r5,r5,0x3
8e000454:	2076      	lsl r1,r0,0x3
8e000456:	b613      	add r5,r5,-4
8e000458:	20a9 0400 	ldrh r1,[r8,+r1]
8e00045c:	2616      	lsl r1,r1,0x10
8e00045e:	a00b 1002 	movt r5,0x0
8e000462:	2670      	bgte 8e0004ae <umm_realloc+0x102>
8e000464:	2c2c 0400 	ldrh r1,[r11,+0x0]
8e000468:	243a      	sub r1,r1,r0
8e00046a:	58ba      	sub r2,r6,r1
8e00046c:	2160      	bgt 8e0004ae <umm_realloc+0x102>
8e00046e:	268b 0062 	mov r1,0x634
8e000472:	200b 18e2 	movt r1,0x8e00
8e000476:	0552      	jalr r1
8e000478:	588b 0062 	mov r2,0x6c4
8e00047c:	2003      	mov r1,0x0
8e00047e:	08ef 0402 	mov r0,r10
8e000482:	400b 18e2 	movt r2,0x8e00
8e000486:	0952      	jalr r2
8e000488:	207f 2006 	lsl r9,r0,0x3
8e00048c:	209f 248a 	add r9,r8,r9
8e000490:	261b 2400 	add r9,r9,4
8e000494:	6b0b 0072 	mov r3,0x758
8e000498:	30e2      	mov r1,r4
8e00049a:	40ef 2002 	mov r10,r0
8e00049e:	54e2      	mov r2,r5
8e0004a0:	04ef 0402 	mov r0,r9
8e0004a4:	600b 18e2 	movt r3,0x8e00
8e0004a8:	0d52      	jalr r3
8e0004aa:	84ef 0402 	mov r4,r9
8e0004ae:	087f 0406 	lsl r0,r10,0x3
8e0004b2:	0029 0400 	ldrh r0,[r8,+r0]
8e0004b6:	013f 008a 	sub r0,r0,r10
8e0004ba:	000b 1002 	movt r0,0x0
8e0004be:	383a      	sub r1,r6,r0
8e0004c0:	3000      	beq 8e000520 <umm_realloc+0x174>
8e0004c2:	080b 2052 	mov r8,0x540
8e0004c6:	000b 38e2 	movt r8,0x8e00
8e0004ca:	1730      	bgteu 8e0004f8 <umm_realloc+0x14c>
8e0004cc:	7d8b 0052 	mov r3,0x5ec
8e0004d0:	38e2      	mov r1,r6
8e0004d2:	08ef 0402 	mov r0,r10
8e0004d6:	4003      	mov r2,0x0
8e0004d8:	600b 18e2 	movt r3,0x8e00
8e0004dc:	0d52      	jalr r3
8e0004de:	cb1f 040a 	add r6,r10,r6
8e0004e2:	000b 0402 	mov r0,0x4000
8e0004e6:	d876      	lsl r6,r6,0x3
8e0004e8:	000b 1002 	movt r0,0x0
8e0004ec:	031a      	add r0,r0,r6
8e0004ee:	021b 0000 	add r0,r0,4
8e0004f2:	015f 0402 	jalr r8
8e0004f6:	15e0      	b 8e000520 <umm_realloc+0x174>
8e0004f8:	2e0b 0022 	mov r1,0x270
8e0004fc:	1ce2      	mov r0,r7
8e0004fe:	200b 18e2 	movt r1,0x8e00
8e000502:	0552      	jalr r1
8e000504:	c05a      	and r6,r0,r0
8e000506:	0800      	beq 8e000516 <umm_realloc+0x16a>
8e000508:	668b 0072 	mov r3,0x734
8e00050c:	54e2      	mov r2,r5
8e00050e:	30e2      	mov r1,r4
8e000510:	600b 18e2 	movt r3,0x8e00
8e000514:	0d52      	jalr r3
8e000516:	10e2      	mov r0,r4
8e000518:	015f 0402 	jalr r8
8e00051c:	18e2      	mov r0,r6
8e00051e:	02e0      	b 8e000522 <umm_realloc+0x176>
8e000520:	10e2      	mov r0,r4
8e000522:	d66c 0400 	ldrd r6,[sp,+0x4]
8e000526:	15ec 2400 	ldrd r8,[sp,+0x3]
8e00052a:	556c 2400 	ldrd r10,[sp,+0x2]
8e00052e:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000532:	b41b 2405 	add sp,sp,40
8e000536:	946c 0400 	ldrd r4,[sp,+0x0]
8e00053a:	194f 0402 	rts
8e00053e:	01a2      	nop

8e000540 <umm_free>:
8e000540:	95fc 0700 	strd r4,[sp],-0x3
8e000544:	d6dc 0400 	str r6,[sp,+0x5]
8e000548:	d4fc 2400 	strd lr,[sp,+0x1]
8e00054c:	005a      	and r0,r0,r0
8e00054e:	3600      	beq 8e0005ba <umm_free+0x7a>
8e000550:	a00b 0402 	mov r5,0x4000
8e000554:	a00b 1002 	movt r5,0x0
8e000558:	82ba      	sub r4,r0,r5
8e00055a:	9066      	lsr r4,r4,0x3
8e00055c:	d0e2      	mov r6,r4
8e00055e:	c00b 1002 	movt r6,0x0
8e000562:	2c8b 0062 	mov r1,0x664
8e000566:	18e2      	mov r0,r6
8e000568:	200b 18e2 	movt r1,0x8e00
8e00056c:	0552      	jalr r1
8e00056e:	1876      	lsl r0,r6,0x3
8e000570:	141a      	add r0,r5,r0
8e000572:	20a4      	ldrh r1,[r0,0x1]
8e000574:	2476      	lsl r1,r1,0x3
8e000576:	34a1      	ldrh r1,[r5,r1]
8e000578:	2616      	lsl r1,r1,0x10
8e00057a:	1170      	bgte 8e00059c <umm_free+0x5c>
8e00057c:	18e2      	mov r0,r6
8e00057e:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e000582:	d6cc 0400 	ldr r6,[sp,+0x5]
8e000586:	b41b 2403 	add sp,sp,24
8e00058a:	588b 0062 	mov r2,0x6c4
8e00058e:	946c 0400 	ldrd r4,[sp,+0x0]
8e000592:	200b 0802 	mov r1,0x8000
8e000596:	400b 18e2 	movt r2,0x8e00
8e00059a:	0942      	jr r2
8e00059c:	5524      	ldrh r2,[r5,0x2]
8e00059e:	2876      	lsl r1,r2,0x3
8e0005a0:	349a      	add r1,r5,r1
8e0005a2:	c5b4      	strh r6,[r1,0x3]
8e0005a4:	4134      	strh r2,[r0,0x2]
8e0005a6:	2003      	mov r1,0x0
8e0005a8:	d534      	strh r6,[r5,0x2]
8e0005aa:	400b 0802 	mov r2,0x8000
8e0005ae:	21b4      	strh r1,[r0,0x3]
8e0005b0:	5feb 1ff2 	movt r2,0xffff
8e0005b4:	2024      	ldrh r1,[r0]
8e0005b6:	257a      	orr r1,r1,r2
8e0005b8:	2034      	strh r1,[r0]
8e0005ba:	d6cc 0400 	ldr r6,[sp,+0x5]
8e0005be:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0005c2:	b41b 2403 	add sp,sp,24
8e0005c6:	946c 0400 	ldrd r4,[sp,+0x0]
8e0005ca:	194f 0402 	rts
8e0005ce:	01a2      	nop

8e0005d0 <umm_blocks>:
8e0005d0:	223b 0000 	sub r1,r0,4
8e0005d4:	0840      	blteu 8e0005e4 <umm_blocks+0x14>
8e0005d6:	019b 00ff 	add r0,r0,-5
8e0005da:	000b 1002 	movt r0,0x0
8e0005de:	0066      	lsr r0,r0,0x3
8e0005e0:	0113      	add r0,r0,2
8e0005e2:	02e0      	b 8e0005e6 <umm_blocks+0x16>
8e0005e4:	0023      	mov r0,0x1
8e0005e6:	194f 0402 	rts
8e0005ea:	01a2      	nop

8e0005ec <umm_make_new_block>:
8e0005ec:	000b 4402 	mov r16,0x4000
8e0005f0:	000b 5002 	movt r16,0x0
8e0005f4:	807f 2006 	lsl ip,r0,0x3
8e0005f8:	241a      	add r1,r1,r0
8e0005fa:	821f 288a 	add ip,r16,ip
8e0005fe:	302c 4400 	ldrh r17,[ip,+0x0]
8e000602:	6476      	lsl r3,r1,0x3
8e000604:	5feb 47f2 	mov r18,0x7fff
8e000608:	619f 080a 	add r3,r16,r3
8e00060c:	255f 490a 	and r17,r17,r18
8e000610:	0cb4      	strh r0,[r3,0x1]
8e000612:	2c3c 4000 	strh r17,[r3]
8e000616:	702c 0400 	ldrh r3,[ip,+0x0]
8e00061a:	0d5f 010a 	and r0,r3,r18
8e00061e:	0076      	lsl r0,r0,0x3
8e000620:	200b 1002 	movt r1,0x0
8e000624:	001f 080a 	add r0,r16,r0
8e000628:	20b4      	strh r1,[r0,0x1]
8e00062a:	457a      	orr r2,r1,r2
8e00062c:	503c 0400 	strh r2,[ip]
8e000630:	194f 0402 	rts

8e000634 <umm_disconnect_from_free_list>:
8e000634:	600b 0402 	mov r3,0x4000
8e000638:	600b 1002 	movt r3,0x0
8e00063c:	0076      	lsl r0,r0,0x3
8e00063e:	0c1a      	add r0,r3,r0
8e000640:	41a4      	ldrh r2,[r0,0x3]
8e000642:	4876      	lsl r2,r2,0x3
8e000644:	2124      	ldrh r1,[r0,0x2]
8e000646:	4d1a      	add r2,r3,r2
8e000648:	2934      	strh r1,[r2,0x2]
8e00064a:	2124      	ldrh r1,[r0,0x2]
8e00064c:	2476      	lsl r1,r1,0x3
8e00064e:	41a4      	ldrh r2,[r0,0x3]
8e000650:	2c9a      	add r1,r3,r1
8e000652:	45b4      	strh r2,[r1,0x3]
8e000654:	2024      	ldrh r1,[r0]
8e000656:	5feb 07f2 	mov r2,0x7fff
8e00065a:	255a      	and r1,r1,r2
8e00065c:	2034      	strh r1,[r0]
8e00065e:	194f 0402 	rts
8e000662:	01a2      	nop

8e000664 <umm_assimilate_up>:
8e000664:	95fc 0700 	strd r4,[sp],-0x3
8e000668:	a00b 0402 	mov r5,0x4000
8e00066c:	8076      	lsl r4,r0,0x3
8e00066e:	a00b 1002 	movt r5,0x0
8e000672:	d6dc 0400 	str r6,[sp,+0x5]
8e000676:	d4fc 2400 	strd lr,[sp,+0x1]
8e00067a:	961a      	add r4,r5,r4
8e00067c:	c0e2      	mov r6,r0
8e00067e:	1024      	ldrh r0,[r4]
8e000680:	2076      	lsl r1,r0,0x3
8e000682:	34a1      	ldrh r1,[r5,r1]
8e000684:	2616      	lsl r1,r1,0x10
8e000686:	1470      	bgte 8e0006ae <umm_assimilate_up+0x4a>
8e000688:	268b 0062 	mov r1,0x634
8e00068c:	200b 18e2 	movt r1,0x8e00
8e000690:	0552      	jalr r1
8e000692:	3024      	ldrh r1,[r4]
8e000694:	2476      	lsl r1,r1,0x3
8e000696:	14a1      	ldrh r0,[r5,r1]
8e000698:	5feb 07f2 	mov r2,0x7fff
8e00069c:	015a      	and r0,r0,r2
8e00069e:	0076      	lsl r0,r0,0x3
8e0006a0:	141a      	add r0,r5,r0
8e0006a2:	c0b4      	strh r6,[r0,0x1]
8e0006a4:	3024      	ldrh r1,[r4]
8e0006a6:	2476      	lsl r1,r1,0x3
8e0006a8:	14a1      	ldrh r0,[r5,r1]
8e0006aa:	015a      	and r0,r0,r2
8e0006ac:	1034      	strh r0,[r4]
8e0006ae:	d6cc 0400 	ldr r6,[sp,+0x5]
8e0006b2:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e0006b6:	b41b 2403 	add sp,sp,24
8e0006ba:	946c 0400 	ldrd r4,[sp,+0x0]
8e0006be:	194f 0402 	rts
8e0006c2:	01a2      	nop

8e0006c4 <umm_assimilate_down>:
8e0006c4:	400b 0402 	mov r2,0x4000
8e0006c8:	400b 1002 	movt r2,0x0
8e0006cc:	0076      	lsl r0,r0,0x3
8e0006ce:	081a      	add r0,r2,r0
8e0006d0:	60a4      	ldrh r3,[r0,0x1]
8e0006d2:	802c 2000 	ldrh ip,[r0,+0x0]
8e0006d6:	6c76      	lsl r3,r3,0x3
8e0006d8:	267f 008a 	orr r1,r1,ip
8e0006dc:	29b1      	strh r1,[r2,r3]
8e0006de:	2024      	ldrh r1,[r0]
8e0006e0:	2476      	lsl r1,r1,0x3
8e0006e2:	60a4      	ldrh r3,[r0,0x1]
8e0006e4:	289a      	add r1,r2,r1
8e0006e6:	64b4      	strh r3,[r1,0x1]
8e0006e8:	00a4      	ldrh r0,[r0,0x1]
8e0006ea:	194f 0402 	rts
8e0006ee:	01a2      	nop

8e0006f0 <bj_get_aligment>:
8e0006f0:	20e3      	mov r1,0x7
8e0006f2:	20da      	and r1,r0,r1
8e0006f4:	0900      	beq 8e000706 <bj_get_aligment+0x16>
8e0006f6:	2063      	mov r1,0x3
8e0006f8:	20da      	and r1,r0,r1
8e0006fa:	0800      	beq 8e00070a <bj_get_aligment+0x1a>
8e0006fc:	03f6      	lsl r0,r0,0x1f
8e0006fe:	0103      	mov r0,0x8
8e000700:	2203      	mov r1,0x10
8e000702:	0472      	movgte r0,r1
8e000704:	04e0      	b 8e00070c <bj_get_aligment+0x1c>
8e000706:	0803      	mov r0,0x40
8e000708:	02e0      	b 8e00070c <bj_get_aligment+0x1c>
8e00070a:	0403      	mov r0,0x20
8e00070c:	194f 0402 	rts

8e000710 <bj_memset>:
8e000710:	2716      	lsl r1,r1,0x18
8e000712:	2706      	lsr r1,r1,0x18
8e000714:	400b 1002 	movt r2,0x0
8e000718:	6003      	mov r3,0x0
8e00071a:	8cef 2002 	mov ip,r3
8e00071e:	800b 3002 	movt ip,0x0
8e000722:	0a3f 408a 	sub r16,r2,ip
8e000726:	0440      	blteu 8e00072e <bj_memset+0x1e>
8e000728:	2191      	strb r1,[r0,r3]
8e00072a:	6c93      	add r3,r3,1
8e00072c:	f7e0      	b 8e00071a <bj_memset+0xa>
8e00072e:	194f 0402 	rts
8e000732:	01a2      	nop

8e000734 <bj_memcpy>:
8e000734:	400b 1002 	movt r2,0x0
8e000738:	6003      	mov r3,0x0
8e00073a:	8cef 2002 	mov ip,r3
8e00073e:	800b 3002 	movt ip,0x0
8e000742:	0a3f 408a 	sub r16,r2,ip
8e000746:	0740      	blteu 8e000754 <bj_memcpy+0x20>
8e000748:	8589 2000 	ldrb ip,[r1,+r3]
8e00074c:	8199 2000 	strb ip,[r0,+r3]
8e000750:	6c93      	add r3,r3,1
8e000752:	f4e0      	b 8e00073a <bj_memcpy+0x6>
8e000754:	194f 0402 	rts

8e000758 <bj_memmove>:
8e000758:	00bf 400a 	sub r16,r0,r1
8e00075c:	80ef 2002 	mov ip,r0
8e000760:	400b 1002 	movt r2,0x0
8e000764:	0620      	bgtu 8e000770 <bj_memmove+0x18>
8e000766:	668b 0072 	mov r3,0x734
8e00076a:	600b 18e2 	movt r3,0x8e00
8e00076e:	0d42      	jr r3
8e000770:	911f 240a 	add ip,ip,r2
8e000774:	08e2      	mov r0,r2
8e000776:	251a      	add r1,r1,r2
8e000778:	70ef 0402 	mov r3,ip
8e00077c:	1feb 4ff2 	mov r16,0xffff
8e000780:	4b93      	add r2,r2,-1
8e000782:	400b 1002 	movt r2,0x0
8e000786:	283f 410a 	sub r17,r2,r16
8e00078a:	0800      	beq 8e00079a <bj_memmove+0x42>
8e00078c:	2793      	add r1,r1,-1
8e00078e:	6f93      	add r3,r3,-1
8e000790:	240c 4000 	ldrb r17,[r1,+0x0]
8e000794:	2c1c 4000 	strb r17,[r3]
8e000798:	f4e0      	b 8e000780 <bj_memmove+0x28>
8e00079a:	103f 040a 	sub r0,ip,r0
8e00079e:	194f 0402 	rts
8e0007a2:	01a2      	nop

8e0007a4 <bj_strlen>:
8e0007a4:	f75c 2700 	str fp,[sp],-0x6
8e0007a8:	f4ef 2402 	mov fp,sp
8e0007ac:	1ddc 0400 	str r0,[fp,+0x3]
8e0007b0:	0003      	mov r0,0x0
8e0007b2:	1dbc 0401 	strh r0,[fp,+0xb]
8e0007b6:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0007ba:	2033      	sub r1,r0,0
8e0007bc:	0810      	bne 8e0007cc <bj_strlen+0x28>
8e0007be:	0003      	mov r0,0x0
8e0007c0:	10e0      	b 8e0007e0 <bj_strlen+0x3c>
8e0007c2:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0007c6:	0093      	add r0,r0,1
8e0007c8:	1dbc 0401 	strh r0,[fp,+0xb]
8e0007cc:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0007d0:	3dcc 0400 	ldr r1,[fp,+0x3]
8e0007d4:	041a      	add r0,r1,r0
8e0007d6:	0004      	ldrb r0,[r0]
8e0007d8:	2033      	sub r1,r0,0
8e0007da:	f410      	bne 8e0007c2 <bj_strlen+0x1e>
8e0007dc:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0007e0:	f74c 2400 	ldr fp,[sp,+0x6]
8e0007e4:	b41b 2403 	add sp,sp,24
8e0007e8:	194f 0402 	rts

8e0007ec <bjk_init_global>:
8e0007ec:	d67c 2700 	strd lr,[sp],-0x4
8e0007f0:	95fc 0400 	strd r4,[sp,+0x3]
8e0007f4:	f41b 2404 	add fp,sp,32
8e0007f8:	a112      	movfs r5,config
8e0007fa:	0003      	mov r0,0x0
8e0007fc:	1ddc 0500 	str r0,[fp,-0x3]
8e000800:	0fe0      	b 8e00081e <bjk_init_global+0x32>
8e000802:	300b 0192 	mov r1,0x1980
8e000806:	200b 1002 	movt r1,0x0
8e00080a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e00080e:	041a      	add r0,r1,r0
8e000810:	2003      	mov r1,0x0
8e000812:	2014      	strb r1,[r0]
8e000814:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000818:	0093      	add r0,r0,1
8e00081a:	1ddc 0500 	str r0,[fp,-0x3]
8e00081e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000822:	20bb 0001 	sub r1,r0,9
8e000826:	ee90      	blte 8e000802 <bjk_init_global+0x16>
8e000828:	080b 01c2 	mov r0,0x1c40
8e00082c:	000b 1002 	movt r0,0x0
8e000830:	2003      	mov r1,0x0
8e000832:	2014      	strb r1,[r0]
8e000834:	0d8b 00f2 	mov r0,0xf6c
8e000838:	000b 18e2 	movt r0,0x8e00
8e00083c:	9fcb 0ff2 	mov r4,0xfffe
8e000840:	9e2b 1ff2 	movt r4,0xfff1
8e000844:	0152      	jalr r0
8e000846:	060b 01c2 	mov r0,0x1c30
8e00084a:	000b 1002 	movt r0,0x0
8e00084e:	2003      	mov r1,0x0
8e000850:	2054      	str r1,[r0]
8e000852:	068b 01c2 	mov r0,0x1c34
8e000856:	000b 1002 	movt r0,0x0
8e00085a:	2003      	mov r1,0x0
8e00085c:	2054      	str r1,[r0]
8e00085e:	070b 01c2 	mov r0,0x1c38
8e000862:	000b 1002 	movt r0,0x0
8e000866:	2403      	mov r1,0x20
8e000868:	2034      	strh r1,[r0]
8e00086a:	070b 01c2 	mov r0,0x1c38
8e00086e:	000b 1002 	movt r0,0x0
8e000872:	2103      	mov r1,0x8
8e000874:	20b4      	strh r1,[r0,0x1]
8e000876:	070b 01c2 	mov r0,0x1c38
8e00087a:	000b 1002 	movt r0,0x0
8e00087e:	2083      	mov r1,0x4
8e000880:	2134      	strh r1,[r0,0x2]
8e000882:	070b 01c2 	mov r0,0x1c38
8e000886:	000b 1002 	movt r0,0x0
8e00088a:	2083      	mov r1,0x4
8e00088c:	21b4      	strh r1,[r0,0x3]
8e00088e:	000b 0002 	mov r0,0x0
8e000892:	000b 18f2 	movt r0,0x8f00
8e000896:	2044      	ldr r1,[r0]
8e000898:	1bab 0cc2 	mov r0,0xccdd
8e00089c:	176b 1aa2 	movt r0,0xaabb
8e0008a0:	443a      	sub r2,r1,r0
8e0008a2:	1000      	beq 8e0008c2 <bjk_init_global+0xd6>
8e0008a4:	1d8b 0072 	mov r0,0x7ec
8e0008a8:	000b 18e2 	movt r0,0x8e00
8e0008ac:	4003      	mov r2,0x0
8e0008ae:	2003      	mov r1,0x0
8e0008b0:	768b 01a2 	mov r3,0x1ab4
8e0008b4:	600b 18e2 	movt r3,0x8e00
8e0008b8:	9fcb 0ff2 	mov r4,0xfffe
8e0008bc:	9e2b 1ff2 	movt r4,0xfff1
8e0008c0:	0d52      	jalr r3
8e0008c2:	0003      	mov r0,0x0
8e0008c4:	1fbc 0500 	strh r0,[fp,-0x7]
8e0008c8:	051f 0032 	movfs r0,coreid
8e0008cc:	1fbc 0500 	strh r0,[fp,-0x7]
8e0008d0:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0008d4:	1cbc 0501 	strh r0,[fp,-0x9]
8e0008d8:	4103      	mov r2,0x8
8e0008da:	2003      	mov r1,0x0
8e0008dc:	070b 01c2 	mov r0,0x1c38
8e0008e0:	000b 1002 	movt r0,0x0
8e0008e4:	620b 0072 	mov r3,0x710
8e0008e8:	600b 18e2 	movt r3,0x8e00
8e0008ec:	9fcb 0ff2 	mov r4,0xfffe
8e0008f0:	9e2b 1ff2 	movt r4,0xfff1
8e0008f4:	0d52      	jalr r3
8e0008f6:	470b 01c2 	mov r2,0x1c38
8e0008fa:	400b 1002 	movt r2,0x0
8e0008fe:	000b 0002 	mov r0,0x0
8e000902:	000b 18f2 	movt r0,0x8f00
8e000906:	00e4      	ldrd r0,[r0,0x1]
8e000908:	0874      	strd r0,[r2]
8e00090a:	1cac 0501 	ldrh r0,[fp,-0x9]
8e00090e:	00c6      	lsr r0,r0,0x6
8e000910:	000b 1002 	movt r0,0x0
8e000914:	20e2      	mov r1,r0
8e000916:	07e3      	mov r0,0x3f
8e000918:	045a      	and r0,r1,r0
8e00091a:	270b 01c2 	mov r1,0x1c38
8e00091e:	200b 1002 	movt r1,0x0
8e000922:	2424      	ldrh r1,[r1]
8e000924:	00ba      	sub r0,r0,r1
8e000926:	40e2      	mov r2,r0
8e000928:	400b 1002 	movt r2,0x0
8e00092c:	070b 01c2 	mov r0,0x1c38
8e000930:	000b 1002 	movt r0,0x0
8e000934:	21a4      	ldrh r1,[r0,0x3]
8e000936:	600b 0002 	mov r3,0x0
8e00093a:	610b 1002 	movt r3,0x8
8e00093e:	0512      	movfs r0,status
8e000940:	0392      	gid
8e000942:	811f 2002 	movfs ip,config
8e000946:	91ff 240a 	orr ip,ip,r3
8e00094a:	810f 2002 	movts config,ip
8e00094e:	0192      	gie
8e000950:	01eb 4ef2 	mov r16,0xef0f
8e000954:	1feb 5ff2 	movt r16,0xffff
8e000958:	251f 4002 	movfs r17,status
8e00095c:	240f 480a 	eor r17,r17,r0
8e000960:	245f 490a 	and r17,r17,r16
8e000964:	240f 480a 	eor r17,r17,r0
8e000968:	250f 4002 	movts status,r17
8e00096c:	08a7      	fmul r0,r2,r1
8e00096e:	20e2      	mov r1,r0
8e000970:	200b 1002 	movt r1,0x0
8e000974:	5cac 0501 	ldrh r2,[fp,-0x9]
8e000978:	07e3      	mov r0,0x3f
8e00097a:	085a      	and r0,r2,r0
8e00097c:	40e2      	mov r2,r0
8e00097e:	400b 1002 	movt r2,0x0
8e000982:	070b 01c2 	mov r0,0x1c38
8e000986:	000b 1002 	movt r0,0x0
8e00098a:	00a4      	ldrh r0,[r0,0x1]
8e00098c:	083a      	sub r0,r2,r0
8e00098e:	000b 1002 	movt r0,0x0
8e000992:	041a      	add r0,r1,r0
8e000994:	1d3c 0501 	strh r0,[fp,-0xa]
8e000998:	1d2c 0501 	ldrh r0,[fp,-0xa]
8e00099c:	0093      	add r0,r0,1
8e00099e:	2096      	lsl r1,r0,0x4
8e0009a0:	000b 0002 	mov r0,0x0
8e0009a4:	000b 18f2 	movt r0,0x8f00
8e0009a8:	241a      	add r1,r1,r0
8e0009aa:	060b 01c2 	mov r0,0x1c30
8e0009ae:	000b 1002 	movt r0,0x0
8e0009b2:	2054      	str r1,[r0]
8e0009b4:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e0009b8:	400b 0002 	mov r2,0x0
8e0009bc:	400b 18f2 	movt r2,0x8f00
8e0009c0:	04e2      	mov r0,r1
8e0009c2:	0076      	lsl r0,r0,0x3
8e0009c4:	6116      	lsl r3,r0,0x8
8e0009c6:	019a      	add r0,r0,r3
8e0009c8:	009a      	add r0,r0,r1
8e0009ca:	0076      	lsl r0,r0,0x3
8e0009cc:	081a      	add r0,r2,r0
8e0009ce:	001b 0022 	add r0,r0,272
8e0009d2:	2044      	ldr r1,[r0]
8e0009d4:	1bab 0cc2 	mov r0,0xccdd
8e0009d8:	176b 1aa2 	movt r0,0xaabb
8e0009dc:	443a      	sub r2,r1,r0
8e0009de:	2d00      	beq 8e000a38 <bjk_init_global+0x24c>
8e0009e0:	1d8b 0072 	mov r0,0x7ec
8e0009e4:	000b 18e2 	movt r0,0x8e00
8e0009e8:	4003      	mov r2,0x0
8e0009ea:	2003      	mov r1,0x0
8e0009ec:	968b 21a2 	mov ip,0x1ab4
8e0009f0:	800b 38e2 	movt ip,0x8e00
8e0009f4:	9fcb 0ff2 	mov r4,0xfffe
8e0009f8:	9e2b 1ff2 	movt r4,0xfff1
8e0009fc:	6512      	movfs r3,status
8e0009fe:	0392      	gid
8e000a00:	011f 4002 	movfs r16,config
8e000a04:	028f 480a 	eor r16,r16,r5
8e000a08:	025f 480a 	and r16,r16,r4
8e000a0c:	028f 480a 	eor r16,r16,r5
8e000a10:	010f 4002 	movts config,r16
8e000a14:	0192      	gie
8e000a16:	21eb 4ef2 	mov r17,0xef0f
8e000a1a:	3feb 5ff2 	movt r17,0xffff
8e000a1e:	051f 4002 	movfs r16,status
8e000a22:	018f 480a 	eor r16,r16,r3
8e000a26:	00df 490a 	and r16,r16,r17
8e000a2a:	018f 480a 	eor r16,r16,r3
8e000a2e:	050f 4002 	movts status,r16
8e000a32:	115f 0402 	jalr ip
8e000a36:	17e0      	b 8e000a64 <bjk_init_global+0x278>
8e000a38:	0512      	movfs r0,status
8e000a3a:	0392      	gid
8e000a3c:	211f 4002 	movfs r17,config
8e000a40:	268f 480a 	eor r17,r17,r5
8e000a44:	265f 480a 	and r17,r17,r4
8e000a48:	268f 480a 	eor r17,r17,r5
8e000a4c:	210f 4002 	movts config,r17
8e000a50:	0192      	gie
8e000a52:	21eb 0ef2 	mov r1,0xef0f
8e000a56:	3feb 1ff2 	movt r1,0xffff
8e000a5a:	4512      	movfs r2,status
8e000a5c:	480a      	eor r2,r2,r0
8e000a5e:	48da      	and r2,r2,r1
8e000a60:	480a      	eor r2,r2,r0
8e000a62:	4502      	movts status,r2
8e000a64:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e000a68:	04e2      	mov r0,r1
8e000a6a:	0076      	lsl r0,r0,0x3
8e000a6c:	4116      	lsl r2,r0,0x8
8e000a6e:	011a      	add r0,r0,r2
8e000a70:	009a      	add r0,r0,r1
8e000a72:	0076      	lsl r0,r0,0x3
8e000a74:	201b 0022 	add r1,r0,272
8e000a78:	000b 0002 	mov r0,0x0
8e000a7c:	000b 18f2 	movt r0,0x8f00
8e000a80:	041a      	add r0,r1,r0
8e000a82:	1f5c 0500 	str r0,[fp,-0x6]
8e000a86:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000a8a:	201b 0001 	add r1,r0,8
8e000a8e:	068b 01c2 	mov r0,0x1c34
8e000a92:	000b 1002 	movt r0,0x0
8e000a96:	2054      	str r1,[r0]
8e000a98:	068b 01c2 	mov r0,0x1c34
8e000a9c:	000b 1002 	movt r0,0x0
8e000aa0:	804c 2000 	ldr ip,[r0,+0x0]
8e000aa4:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000aa8:	001b 0009 	add r0,r0,72
8e000aac:	6003      	mov r3,0x0
8e000aae:	40e2      	mov r2,r0
8e000ab0:	200b 0402 	mov r1,0x4000
8e000ab4:	10ef 0402 	mov r0,ip
8e000ab8:	940b 20f2 	mov ip,0xfa0
8e000abc:	800b 38e2 	movt ip,0x8e00
8e000ac0:	9fcb 0ff2 	mov r4,0xfffe
8e000ac4:	9e2b 1ff2 	movt r4,0xfff1
8e000ac8:	115f 0402 	jalr ip
8e000acc:	060b 01c2 	mov r0,0x1c30
8e000ad0:	000b 1002 	movt r0,0x0
8e000ad4:	0044      	ldr r0,[r0]
8e000ad6:	2044      	ldr r1,[r0]
8e000ad8:	1bab 0cc2 	mov r0,0xccdd
8e000adc:	176b 1aa2 	movt r0,0xaabb
8e000ae0:	643a      	sub r3,r1,r0
8e000ae2:	1000      	beq 8e000b02 <bjk_init_global+0x316>
8e000ae4:	1d8b 0072 	mov r0,0x7ec
8e000ae8:	000b 18e2 	movt r0,0x8e00
8e000aec:	4003      	mov r2,0x0
8e000aee:	2003      	mov r1,0x0
8e000af0:	768b 01a2 	mov r3,0x1ab4
8e000af4:	600b 18e2 	movt r3,0x8e00
8e000af8:	9fcb 0ff2 	mov r4,0xfffe
8e000afc:	9e2b 1ff2 	movt r4,0xfff1
8e000b00:	0d52      	jalr r3
8e000b02:	4a03      	mov r2,0x50
8e000b04:	2003      	mov r1,0x0
8e000b06:	1c0b 01b2 	mov r0,0x1be0
8e000b0a:	000b 1002 	movt r0,0x0
8e000b0e:	620b 0072 	mov r3,0x710
8e000b12:	600b 18e2 	movt r3,0x8e00
8e000b16:	9fcb 0ff2 	mov r4,0xfffe
8e000b1a:	9e2b 1ff2 	movt r4,0xfff1
8e000b1e:	0d52      	jalr r3
8e000b20:	4a03      	mov r2,0x50
8e000b22:	2003      	mov r1,0x0
8e000b24:	110b 01b2 	mov r0,0x1b88
8e000b28:	000b 1002 	movt r0,0x0
8e000b2c:	620b 0072 	mov r3,0x710
8e000b30:	600b 18e2 	movt r3,0x8e00
8e000b34:	9fcb 0ff2 	mov r4,0xfffe
8e000b38:	9e2b 1ff2 	movt r4,0xfff1
8e000b3c:	0d52      	jalr r3
8e000b3e:	1c0b 01b2 	mov r0,0x1be0
8e000b42:	000b 1002 	movt r0,0x0
8e000b46:	3bab 0cc2 	mov r1,0xccdd
8e000b4a:	376b 1aa2 	movt r1,0xaabb
8e000b4e:	2054      	str r1,[r0]
8e000b50:	1c0b 01b2 	mov r0,0x1be0
8e000b54:	000b 1002 	movt r0,0x0
8e000b58:	310b 01b2 	mov r1,0x1b88
8e000b5c:	200b 1002 	movt r1,0x0
8e000b60:	20d4      	str r1,[r0,0x1]
8e000b62:	1c0b 01b2 	mov r0,0x1be0
8e000b66:	000b 1002 	movt r0,0x0
8e000b6a:	39ab 0ab2 	mov r1,0xabcd
8e000b6e:	312b 1672 	movt r1,0x6789
8e000b72:	21dc 0002 	str r1,[r0,+0x13]
8e000b76:	1c0b 01b2 	mov r0,0x1be0
8e000b7a:	000b 1002 	movt r0,0x0
8e000b7e:	3cac 0501 	ldrh r1,[fp,-0x9]
8e000b82:	203c 0001 	strh r1,[r0,+0x8]
8e000b86:	1cac 0501 	ldrh r0,[fp,-0x9]
8e000b8a:	00c6      	lsr r0,r0,0x6
8e000b8c:	20e2      	mov r1,r0
8e000b8e:	200b 1002 	movt r1,0x0
8e000b92:	07e3      	mov r0,0x3f
8e000b94:	045a      	and r0,r1,r0
8e000b96:	20e2      	mov r1,r0
8e000b98:	200b 1002 	movt r1,0x0
8e000b9c:	070b 01c2 	mov r0,0x1c38
8e000ba0:	000b 1002 	movt r0,0x0
8e000ba4:	0024      	ldrh r0,[r0]
8e000ba6:	043a      	sub r0,r1,r0
8e000ba8:	20e2      	mov r1,r0
8e000baa:	200b 1002 	movt r1,0x0
8e000bae:	1c0b 01b2 	mov r0,0x1be0
8e000bb2:	000b 1002 	movt r0,0x0
8e000bb6:	213c 0001 	strh r1,[r0,+0xa]
8e000bba:	3cac 0501 	ldrh r1,[fp,-0x9]
8e000bbe:	07e3      	mov r0,0x3f
8e000bc0:	045a      	and r0,r1,r0
8e000bc2:	20e2      	mov r1,r0
8e000bc4:	200b 1002 	movt r1,0x0
8e000bc8:	070b 01c2 	mov r0,0x1c38
8e000bcc:	000b 1002 	movt r0,0x0
8e000bd0:	00a4      	ldrh r0,[r0,0x1]
8e000bd2:	043a      	sub r0,r1,r0
8e000bd4:	20e2      	mov r1,r0
8e000bd6:	200b 1002 	movt r1,0x0
8e000bda:	1c0b 01b2 	mov r0,0x1be0
8e000bde:	000b 1002 	movt r0,0x0
8e000be2:	21bc 0001 	strh r1,[r0,+0xb]
8e000be6:	1c0b 01b2 	mov r0,0x1be0
8e000bea:	000b 1002 	movt r0,0x0
8e000bee:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e000bf2:	20bc 0001 	strh r1,[r0,+0x9]
8e000bf6:	060b 01c2 	mov r0,0x1c30
8e000bfa:	000b 1002 	movt r0,0x0
8e000bfe:	0044      	ldr r0,[r0]
8e000c00:	3c0b 01b2 	mov r1,0x1be0
8e000c04:	200b 1002 	movt r1,0x0
8e000c08:	242c 0001 	ldrh r1,[r1,+0x8]
8e000c0c:	2134      	strh r1,[r0,0x2]
8e000c0e:	01a2      	nop
8e000c10:	060b 01c2 	mov r0,0x1c30
8e000c14:	000b 1002 	movt r0,0x0
8e000c18:	0044      	ldr r0,[r0]
8e000c1a:	2124      	ldrh r1,[r0,0x2]
8e000c1c:	1c0b 01b2 	mov r0,0x1be0
8e000c20:	000b 1002 	movt r0,0x0
8e000c24:	002c 0001 	ldrh r0,[r0,+0x8]
8e000c28:	843f 200a 	sub ip,r1,r0
8e000c2c:	f210      	bne 8e000c10 <bjk_init_global+0x424>
8e000c2e:	060b 01c2 	mov r0,0x1c30
8e000c32:	000b 1002 	movt r0,0x0
8e000c36:	0044      	ldr r0,[r0]
8e000c38:	3c0b 01b2 	mov r1,0x1be0
8e000c3c:	200b 1002 	movt r1,0x0
8e000c40:	2154      	str r1,[r0,0x2]
8e000c42:	01a2      	nop
8e000c44:	060b 01c2 	mov r0,0x1c30
8e000c48:	000b 1002 	movt r0,0x0
8e000c4c:	0044      	ldr r0,[r0]
8e000c4e:	2144      	ldr r1,[r0,0x2]
8e000c50:	1c0b 01b2 	mov r0,0x1be0
8e000c54:	000b 1002 	movt r0,0x0
8e000c58:	043f 400a 	sub r16,r1,r0
8e000c5c:	f410      	bne 8e000c44 <bjk_init_global+0x458>
8e000c5e:	0423      	mov r0,0x21
8e000c60:	1f9c 0501 	strb r0,[fp,-0xf]
8e000c64:	060b 01c2 	mov r0,0x1c30
8e000c68:	000b 1002 	movt r0,0x0
8e000c6c:	0044      	ldr r0,[r0]
8e000c6e:	3f8c 0501 	ldrb r1,[fp,-0xf]
8e000c72:	2314      	strb r1,[r0,0x6]
8e000c74:	060b 01c2 	mov r0,0x1c30
8e000c78:	000b 1002 	movt r0,0x0
8e000c7c:	0044      	ldr r0,[r0]
8e000c7e:	0304      	ldrb r0,[r0,0x6]
8e000c80:	3f8c 0501 	ldrb r1,[fp,-0xf]
8e000c84:	243f 400a 	sub r17,r1,r0
8e000c88:	f610      	bne 8e000c74 <bjk_init_global+0x488>
8e000c8a:	060b 01c2 	mov r0,0x1c30
8e000c8e:	000b 1002 	movt r0,0x0
8e000c92:	0044      	ldr r0,[r0]
8e000c94:	2003      	mov r1,0x0
8e000c96:	2394      	strb r1,[r0,0x7]
8e000c98:	01a2      	nop
8e000c9a:	060b 01c2 	mov r0,0x1c30
8e000c9e:	000b 1002 	movt r0,0x0
8e000ca2:	0044      	ldr r0,[r0]
8e000ca4:	0384      	ldrb r0,[r0,0x7]
8e000ca6:	2033      	sub r1,r0,0
8e000ca8:	f910      	bne 8e000c9a <bjk_init_global+0x4ae>
8e000caa:	01a2      	nop
8e000cac:	9fcb 0ff2 	mov r4,0xfffe
8e000cb0:	9e2b 1ff2 	movt r4,0xfff1
8e000cb4:	d66c 2400 	ldrd lr,[sp,+0x4]
8e000cb8:	95ec 0400 	ldrd r4,[sp,+0x3]
8e000cbc:	b41b 2404 	add sp,sp,32
8e000cc0:	194f 0402 	rts

8e000cc4 <abort>:
8e000cc4:	d57c 2700 	strd lr,[sp],-0x2
8e000cc8:	f41b 2402 	add fp,sp,16

8e000ccc <ck2_abort>:
8e000ccc:	b98b e0c2 	mov r61,0xccc
8e000cd0:	a00b f8e2 	movt r61,0x8e00
8e000cd4:	14ef 1c02 	mov r0,r61
8e000cd8:	1cdc 0500 	str r0,[fp,-0x1]
8e000cdc:	4003      	mov r2,0x0
8e000cde:	2003      	mov r1,0x0
8e000ce0:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ce4:	768b 01a2 	mov r3,0x1ab4
8e000ce8:	600b 18e2 	movt r3,0x8e00
8e000cec:	0d52      	jalr r3
8e000cee:	188b 00c2 	mov r0,0xcc4
8e000cf2:	000b 18e2 	movt r0,0x8e00
8e000cf6:	4003      	mov r2,0x0
8e000cf8:	2003      	mov r1,0x0
8e000cfa:	768b 01a2 	mov r3,0x1ab4
8e000cfe:	600b 18e2 	movt r3,0x8e00
8e000d02:	0d52      	jalr r3
8e000d04:	00e0      	b 8e000d04 <ck2_abort+0x38>
8e000d06:	01a2      	nop

8e000d08 <bjk_aux_sout>:
8e000d08:	d5fc 2700 	strd lr,[sp],-0x3
8e000d0c:	f41b 2403 	add fp,sp,24
8e000d10:	1ddc 0500 	str r0,[fp,-0x3]
8e000d14:	3e5c 0500 	str r1,[fp,-0x4]
8e000d18:	0043      	mov r0,0x2
8e000d1a:	1e9c 0500 	strb r0,[fp,-0x5]
8e000d1e:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000d22:	348b 0072 	mov r1,0x7a4
8e000d26:	200b 18e2 	movt r1,0x8e00
8e000d2a:	0552      	jalr r1
8e000d2c:	1cbc 0500 	strh r0,[fp,-0x1]
8e000d30:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000d34:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000d38:	5e8b 0012 	mov r2,0x1f4
8e000d3c:	083a      	sub r0,r2,r0
8e000d3e:	443a      	sub r2,r1,r0
8e000d40:	0a90      	blte 8e000d54 <bjk_aux_sout+0x4c>
8e000d42:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000d46:	000b 1002 	movt r0,0x0
8e000d4a:	3e8b 0012 	mov r1,0x1f4
8e000d4e:	043a      	sub r0,r1,r0
8e000d50:	1cbc 0500 	strh r0,[fp,-0x1]
8e000d54:	3e8c 0500 	ldrb r1,[fp,-0x5]
8e000d58:	120b 0192 	mov r0,0x1990
8e000d5c:	000b 1002 	movt r0,0x0
8e000d60:	041a      	add r0,r1,r0
8e000d62:	3cac 0500 	ldrh r1,[fp,-0x1]
8e000d66:	44e2      	mov r2,r1
8e000d68:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000d6c:	668b 0072 	mov r3,0x734
8e000d70:	600b 18e2 	movt r3,0x8e00
8e000d74:	0d52      	jalr r3
8e000d76:	1e4c 0500 	ldr r0,[fp,-0x4]
8e000d7a:	2316      	lsl r1,r0,0x18
8e000d7c:	2706      	lsr r1,r1,0x18
8e000d7e:	120b 0192 	mov r0,0x1990
8e000d82:	000b 1002 	movt r0,0x0
8e000d86:	2014      	strb r1,[r0]
8e000d88:	120b 0192 	mov r0,0x1990
8e000d8c:	000b 1002 	movt r0,0x0
8e000d90:	2003      	mov r1,0x0
8e000d92:	2094      	strb r1,[r0,0x1]
8e000d94:	068b 01c2 	mov r0,0x1c34
8e000d98:	000b 1002 	movt r0,0x0
8e000d9c:	6044      	ldr r3,[r0]
8e000d9e:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000da2:	20e2      	mov r1,r0
8e000da4:	200b 1002 	movt r1,0x0
8e000da8:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000dac:	041a      	add r0,r1,r0
8e000dae:	000b 1002 	movt r0,0x0
8e000db2:	520b 0192 	mov r2,0x1990
8e000db6:	400b 1002 	movt r2,0x0
8e000dba:	20e2      	mov r1,r0
8e000dbc:	0ce2      	mov r0,r3
8e000dbe:	7b0b 0122 	mov r3,0x12d8
8e000dc2:	600b 18e2 	movt r3,0x8e00
8e000dc6:	0d52      	jalr r3
8e000dc8:	1d3c 0500 	strh r0,[fp,-0x2]
8e000dcc:	25e0      	b 8e000e16 <bjk_aux_sout+0x10e>
8e000dce:	4003      	mov r2,0x0
8e000dd0:	2003      	mov r1,0x0
8e000dd2:	1763      	mov r0,0xbb
8e000dd4:	738b 01b2 	mov r3,0x1b9c
8e000dd8:	600b 18e2 	movt r3,0x8e00
8e000ddc:	0d52      	jalr r3
8e000dde:	068b 01c2 	mov r0,0x1c34
8e000de2:	000b 1002 	movt r0,0x0
8e000de6:	6044      	ldr r3,[r0]
8e000de8:	1e8c 0500 	ldrb r0,[fp,-0x5]
8e000dec:	20e2      	mov r1,r0
8e000dee:	200b 1002 	movt r1,0x0
8e000df2:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000df6:	041a      	add r0,r1,r0
8e000df8:	000b 1002 	movt r0,0x0
8e000dfc:	520b 0192 	mov r2,0x1990
8e000e00:	400b 1002 	movt r2,0x0
8e000e04:	20e2      	mov r1,r0
8e000e06:	0ce2      	mov r0,r3
8e000e08:	7b0b 0122 	mov r3,0x12d8
8e000e0c:	600b 18e2 	movt r3,0x8e00
8e000e10:	0d52      	jalr r3
8e000e12:	1d3c 0500 	strh r0,[fp,-0x2]
8e000e16:	1d2c 0500 	ldrh r0,[fp,-0x2]
8e000e1a:	2033      	sub r1,r0,0
8e000e1c:	d900      	beq 8e000dce <bjk_aux_sout+0xc6>
8e000e1e:	01a2      	nop
8e000e20:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e000e24:	b41b 2403 	add sp,sp,24
8e000e28:	194f 0402 	rts

8e000e2c <bjk_aux_iout>:
8e000e2c:	d77c 2700 	strd lr,[sp],-0x6
8e000e30:	95dc 0401 	str r4,[sp,+0xb]
8e000e34:	f41b 2406 	add fp,sp,48
8e000e38:	1fdc 0500 	str r0,[fp,-0x7]
8e000e3c:	3c5c 0501 	str r1,[fp,-0x8]
8e000e40:	5cdc 0501 	str r2,[fp,-0x9]
8e000e44:	14ef 0402 	mov r0,sp
8e000e48:	80e2      	mov r4,r0
8e000e4a:	00c3      	mov r0,0x6
8e000e4c:	1f3c 0500 	strh r0,[fp,-0x6]
8e000e50:	1f2c 0500 	ldrh r0,[fp,-0x6]
8e000e54:	20e2      	mov r1,r0
8e000e56:	2793      	add r1,r1,-1
8e000e58:	3e5c 0500 	str r1,[fp,-0x4]
8e000e5c:	40ef 4002 	mov r18,r0
8e000e60:	600b 4002 	mov r19,0x0
8e000e64:	2baf 0806 	lsr r1,r18,0x1d
8e000e68:	ec7f 4806 	lsl r23,r19,0x3
8e000e6c:	e7ff 410a 	orr r23,r1,r23
8e000e70:	c87f 4806 	lsl r22,r18,0x3
8e000e74:	00ef 4002 	mov r16,r0
8e000e78:	200b 4002 	mov r17,0x0
8e000e7c:	23af 0806 	lsr r1,r16,0x1d
8e000e80:	a47f 4806 	lsl r21,r17,0x3
8e000e84:	a6ff 410a 	orr r21,r1,r21
8e000e88:	807f 4806 	lsl r20,r16,0x3
8e000e8c:	039b 0000 	add r0,r0,7
8e000e90:	0066      	lsr r0,r0,0x3
8e000e92:	0076      	lsl r0,r0,0x3
8e000e94:	b43f 240a 	sub sp,sp,r0
8e000e98:	141b 0401 	add r0,sp,8
8e000e9c:	0013      	add r0,r0,0
8e000e9e:	1edc 0500 	str r0,[fp,-0x5]
8e000ea2:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000ea6:	2316      	lsl r1,r0,0x18
8e000ea8:	2706      	lsr r1,r1,0x18
8e000eaa:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000eae:	2014      	strb r1,[r0]
8e000eb0:	1ccc 0501 	ldr r0,[fp,-0x9]
8e000eb4:	2316      	lsl r1,r0,0x18
8e000eb6:	2706      	lsr r1,r1,0x18
8e000eb8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000ebc:	2094      	strb r1,[r0,0x1]
8e000ebe:	1e1b 04fc 	add r0,fp,-28
8e000ec2:	1f5c 0500 	str r0,[fp,-0x6]
8e000ec6:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000eca:	2004      	ldrb r1,[r0]
8e000ecc:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000ed0:	2114      	strb r1,[r0,0x2]
8e000ed2:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000ed6:	2084      	ldrb r1,[r0,0x1]
8e000ed8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000edc:	2194      	strb r1,[r0,0x3]
8e000ede:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000ee2:	2104      	ldrb r1,[r0,0x2]
8e000ee4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000ee8:	2214      	strb r1,[r0,0x4]
8e000eea:	1f4c 0500 	ldr r0,[fp,-0x6]
8e000eee:	2184      	ldrb r1,[r0,0x3]
8e000ef0:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000ef4:	2294      	strb r1,[r0,0x5]
8e000ef6:	068b 01c2 	mov r0,0x1c34
8e000efa:	000b 1002 	movt r0,0x0
8e000efe:	0044      	ldr r0,[r0]
8e000f00:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000f04:	5ecc 0500 	ldr r2,[fp,-0x5]
8e000f08:	7b0b 0122 	mov r3,0x12d8
8e000f0c:	600b 18e2 	movt r3,0x8e00
8e000f10:	0d52      	jalr r3
8e000f12:	1ebc 0500 	strh r0,[fp,-0x5]
8e000f16:	19e0      	b 8e000f48 <bjk_aux_iout+0x11c>
8e000f18:	4003      	mov r2,0x0
8e000f1a:	2003      	mov r1,0x0
8e000f1c:	1763      	mov r0,0xbb
8e000f1e:	738b 01b2 	mov r3,0x1b9c
8e000f22:	600b 18e2 	movt r3,0x8e00
8e000f26:	0d52      	jalr r3
8e000f28:	068b 01c2 	mov r0,0x1c34
8e000f2c:	000b 1002 	movt r0,0x0
8e000f30:	0044      	ldr r0,[r0]
8e000f32:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e000f36:	5ecc 0500 	ldr r2,[fp,-0x5]
8e000f3a:	7b0b 0122 	mov r3,0x12d8
8e000f3e:	600b 18e2 	movt r3,0x8e00
8e000f42:	0d52      	jalr r3
8e000f44:	1ebc 0500 	strh r0,[fp,-0x5]
8e000f48:	1eac 0500 	ldrh r0,[fp,-0x5]
8e000f4c:	2033      	sub r1,r0,0
8e000f4e:	e500      	beq 8e000f18 <bjk_aux_iout+0xec>
8e000f50:	b0ef 2002 	mov sp,r4
8e000f54:	01a2      	nop
8e000f56:	bc1b 24fa 	add sp,fp,-48
8e000f5a:	d76c 2400 	ldrd lr,[sp,+0x6]
8e000f5e:	95cc 0401 	ldr r4,[sp,+0xb]
8e000f62:	b41b 2406 	add sp,sp,48
8e000f66:	194f 0402 	rts
8e000f6a:	01a2      	nop

8e000f6c <bjk_set_irq0_handler>:
8e000f6c:	f65c 2700 	str fp,[sp],-0x4
8e000f70:	f4ef 2402 	mov fp,sp
8e000f74:	0003      	mov r0,0x0
8e000f76:	1ddc 0400 	str r0,[fp,+0x3]
8e000f7a:	000b 0012 	mov r0,0x100
8e000f7e:	000b 1002 	movt r0,0x0
8e000f82:	0026      	lsr r0,r0,0x1
8e000f84:	2116      	lsl r1,r0,0x8
8e000f86:	1d03      	mov r0,0xe8
8e000f88:	247a      	orr r1,r1,r0
8e000f8a:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000f8e:	2054      	str r1,[r0]
8e000f90:	01a2      	nop
8e000f92:	f64c 2400 	ldr fp,[sp,+0x4]
8e000f96:	b41b 2402 	add sp,sp,16
8e000f9a:	194f 0402 	rts
8e000f9e:	01a2      	nop

8e000fa0 <bj_rr_init>:
8e000fa0:	d5fc 2700 	strd lr,[sp],-0x3
8e000fa4:	f41b 2403 	add fp,sp,24
8e000fa8:	1cdc 0500 	str r0,[fp,-0x1]
8e000fac:	04e2      	mov r0,r1
8e000fae:	5ddc 0500 	str r2,[fp,-0x3]
8e000fb2:	2ce2      	mov r1,r3
8e000fb4:	1e3c 0500 	strh r0,[fp,-0x4]
8e000fb8:	04e2      	mov r0,r1
8e000fba:	1c1c 0502 	strb r0,[fp,-0x10]
8e000fbe:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000fc2:	2033      	sub r1,r0,0
8e000fc4:	8408 0000 	beq 8e0010cc <bj_rr_init+0x12c>
8e000fc8:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000fcc:	3bab 0cc2 	mov r1,0xccdd
8e000fd0:	376b 1aa2 	movt r1,0xaabb
8e000fd4:	2054      	str r1,[r0]
8e000fd6:	01a2      	nop
8e000fd8:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000fdc:	2044      	ldr r1,[r0]
8e000fde:	1bab 0cc2 	mov r0,0xccdd
8e000fe2:	176b 1aa2 	movt r0,0xaabb
8e000fe6:	443a      	sub r2,r1,r0
8e000fe8:	f810      	bne 8e000fd8 <bj_rr_init+0x38>
8e000fea:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000fee:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000ff2:	20d4      	str r1,[r0,0x1]
8e000ff4:	01a2      	nop
8e000ff6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000ffa:	20c4      	ldr r1,[r0,0x1]
8e000ffc:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001000:	443a      	sub r2,r1,r0
8e001002:	fa10      	bne 8e000ff6 <bj_rr_init+0x56>
8e001004:	1c0c 0502 	ldrb r0,[fp,-0x10]
8e001008:	2033      	sub r1,r0,0
8e00100a:	0d00      	beq 8e001024 <bj_rr_init+0x84>
8e00100c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001010:	00c4      	ldr r0,[r0,0x1]
8e001012:	3e2c 0500 	ldrh r1,[fp,-0x4]
8e001016:	44e2      	mov r2,r1
8e001018:	2003      	mov r1,0x0
8e00101a:	620b 0072 	mov r3,0x710
8e00101e:	600b 18e2 	movt r3,0x8e00
8e001022:	0d52      	jalr r3
8e001024:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e001028:	3dcc 0500 	ldr r1,[fp,-0x3]
8e00102c:	241a      	add r1,r1,r0
8e00102e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001032:	2154      	str r1,[r0,0x2]
8e001034:	01a2      	nop
8e001036:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00103a:	2144      	ldr r1,[r0,0x2]
8e00103c:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e001040:	5dcc 0500 	ldr r2,[fp,-0x3]
8e001044:	081a      	add r0,r2,r0
8e001046:	443a      	sub r2,r1,r0
8e001048:	f710      	bne 8e001036 <bj_rr_init+0x96>
8e00104a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00104e:	20c4      	ldr r1,[r0,0x1]
8e001050:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001054:	21d4      	str r1,[r0,0x3]
8e001056:	01a2      	nop
8e001058:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00105c:	21c4      	ldr r1,[r0,0x3]
8e00105e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001062:	00c4      	ldr r0,[r0,0x1]
8e001064:	443a      	sub r2,r1,r0
8e001066:	f910      	bne 8e001058 <bj_rr_init+0xb8>
8e001068:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00106c:	20c4      	ldr r1,[r0,0x1]
8e00106e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001072:	2254      	str r1,[r0,0x4]
8e001074:	01a2      	nop
8e001076:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00107a:	2244      	ldr r1,[r0,0x4]
8e00107c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001080:	00c4      	ldr r0,[r0,0x1]
8e001082:	443a      	sub r2,r1,r0
8e001084:	f910      	bne 8e001076 <bj_rr_init+0xd6>
8e001086:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00108a:	2003      	mov r1,0x0
8e00108c:	22d4      	str r1,[r0,0x5]
8e00108e:	01a2      	nop
8e001090:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001094:	02c4      	ldr r0,[r0,0x5]
8e001096:	2033      	sub r1,r0,0
8e001098:	fc10      	bne 8e001090 <bj_rr_init+0xf0>
8e00109a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00109e:	2003      	mov r1,0x0
8e0010a0:	201c 0003 	strb r1,[r0,+0x18]
8e0010a4:	01a2      	nop
8e0010a6:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0010aa:	000c 0003 	ldrb r0,[r0,+0x18]
8e0010ae:	4033      	sub r2,r0,0
8e0010b0:	fb10      	bne 8e0010a6 <bj_rr_init+0x106>
8e0010b2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0010b6:	2003      	mov r1,0x0
8e0010b8:	209c 0003 	strb r1,[r0,+0x19]
8e0010bc:	01a2      	nop
8e0010be:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0010c2:	008c 0003 	ldrb r0,[r0,+0x19]
8e0010c6:	2033      	sub r1,r0,0
8e0010c8:	fb10      	bne 8e0010be <bj_rr_init+0x11e>
8e0010ca:	02e0      	b 8e0010ce <bj_rr_init+0x12e>
8e0010cc:	01a2      	nop
8e0010ce:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e0010d2:	b41b 2403 	add sp,sp,24
8e0010d6:	194f 0402 	rts
8e0010da:	01a2      	nop

8e0010dc <bj_rr_read_obj>:
8e0010dc:	d77c 2700 	strd lr,[sp],-0x6
8e0010e0:	f41b 2406 	add fp,sp,48
8e0010e4:	1fdc 0500 	str r0,[fp,-0x7]
8e0010e8:	04e2      	mov r0,r1
8e0010ea:	5cdc 0501 	str r2,[fp,-0x9]
8e0010ee:	1c3c 0502 	strh r0,[fp,-0x10]
8e0010f2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0010f6:	2033      	sub r1,r0,0
8e0010f8:	0410      	bne 8e001100 <bj_rr_read_obj+0x24>
8e0010fa:	0003      	mov r0,0x0
8e0010fc:	e7e8 0000 	b 8e0012ca <bj_rr_read_obj+0x1ee>
8e001100:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001104:	0244      	ldr r0,[r0,0x4]
8e001106:	1edc 0500 	str r0,[fp,-0x5]
8e00110a:	1e1b 04fd 	add r0,fp,-20
8e00110e:	20e2      	mov r1,r0
8e001110:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001114:	400b 0172 	mov r2,0x1700
8e001118:	400b 18e2 	movt r2,0x8e00
8e00111c:	0952      	jalr r2
8e00111e:	1ebc 0500 	strh r0,[fp,-0x5]
8e001122:	1eac 0500 	ldrh r0,[fp,-0x5]
8e001126:	4033      	sub r2,r0,0
8e001128:	1310      	bne 8e00114e <bj_rr_read_obj+0x72>
8e00112a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00112e:	3feb 0ff2 	mov r1,0xffff
8e001132:	209c 0003 	strb r1,[r0,+0x19]
8e001136:	01a2      	nop
8e001138:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00113c:	008c 0003 	ldrb r0,[r0,+0x19]
8e001140:	0316      	lsl r0,r0,0x18
8e001142:	030e      	asr r0,r0,0x18
8e001144:	23b3      	sub r1,r0,-1
8e001146:	f910      	bne 8e001138 <bj_rr_read_obj+0x5c>
8e001148:	0003      	mov r0,0x0
8e00114a:	c0e8 0000 	b 8e0012ca <bj_rr_read_obj+0x1ee>
8e00114e:	3eac 0500 	ldrh r1,[fp,-0x5]
8e001152:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e001156:	443a      	sub r2,r1,r0
8e001158:	1340      	blteu 8e00117e <bj_rr_read_obj+0xa2>
8e00115a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00115e:	3fcb 0ff2 	mov r1,0xfffe
8e001162:	209c 0003 	strb r1,[r0,+0x19]
8e001166:	01a2      	nop
8e001168:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00116c:	008c 0003 	ldrb r0,[r0,+0x19]
8e001170:	0316      	lsl r0,r0,0x18
8e001172:	030e      	asr r0,r0,0x18
8e001174:	2333      	sub r1,r0,-2
8e001176:	f910      	bne 8e001168 <bj_rr_read_obj+0x8c>
8e001178:	0003      	mov r0,0x0
8e00117a:	a8e8 0000 	b 8e0012ca <bj_rr_read_obj+0x1ee>
8e00117e:	3eac 0500 	ldrh r1,[fp,-0x5]
8e001182:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001186:	0144      	ldr r0,[r0,0x2]
8e001188:	40e2      	mov r2,r0
8e00118a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00118e:	00c4      	ldr r0,[r0,0x1]
8e001190:	083a      	sub r0,r2,r0
8e001192:	443a      	sub r2,r1,r0
8e001194:	1390      	blte 8e0011ba <bj_rr_read_obj+0xde>
8e001196:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00119a:	3fab 0ff2 	mov r1,0xfffd
8e00119e:	209c 0003 	strb r1,[r0,+0x19]
8e0011a2:	01a2      	nop
8e0011a4:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0011a8:	008c 0003 	ldrb r0,[r0,+0x19]
8e0011ac:	0316      	lsl r0,r0,0x18
8e0011ae:	030e      	asr r0,r0,0x18
8e0011b0:	22b3      	sub r1,r0,-3
8e0011b2:	f910      	bne 8e0011a4 <bj_rr_read_obj+0xc8>
8e0011b4:	0003      	mov r0,0x0
8e0011b6:	8ae8 0000 	b 8e0012ca <bj_rr_read_obj+0x1ee>
8e0011ba:	0003      	mov r0,0x0
8e0011bc:	1cbc 0500 	strh r0,[fp,-0x1]
8e0011c0:	20e0      	b 8e001200 <bj_rr_read_obj+0x124>
8e0011c2:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0011c6:	2144      	ldr r1,[r0,0x2]
8e0011c8:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0011cc:	443a      	sub r2,r1,r0
8e0011ce:	0610      	bne 8e0011da <bj_rr_read_obj+0xfe>
8e0011d0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0011d4:	00c4      	ldr r0,[r0,0x1]
8e0011d6:	1edc 0500 	str r0,[fp,-0x5]
8e0011da:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0011de:	3ccc 0501 	ldr r1,[fp,-0x9]
8e0011e2:	041a      	add r0,r1,r0
8e0011e4:	3ecc 0500 	ldr r1,[fp,-0x5]
8e0011e8:	2404      	ldrb r1,[r1]
8e0011ea:	2014      	strb r1,[r0]
8e0011ec:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0011f0:	0093      	add r0,r0,1
8e0011f2:	1edc 0500 	str r0,[fp,-0x5]
8e0011f6:	1cac 0500 	ldrh r0,[fp,-0x1]
8e0011fa:	0093      	add r0,r0,1
8e0011fc:	1cbc 0500 	strh r0,[fp,-0x1]
8e001200:	3cac 0500 	ldrh r1,[fp,-0x1]
8e001204:	1eac 0500 	ldrh r0,[fp,-0x5]
8e001208:	443a      	sub r2,r1,r0
8e00120a:	dc50      	bltu 8e0011c2 <bj_rr_read_obj+0xe6>
8e00120c:	1e1b 04fd 	add r0,fp,-20
8e001210:	20e2      	mov r1,r0
8e001212:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001216:	400b 0172 	mov r2,0x1700
8e00121a:	400b 18e2 	movt r2,0x8e00
8e00121e:	0952      	jalr r2
8e001220:	1f3c 0500 	strh r0,[fp,-0x6]
8e001224:	1eac 0500 	ldrh r0,[fp,-0x5]
8e001228:	20e2      	mov r1,r0
8e00122a:	1ccc 0501 	ldr r0,[fp,-0x9]
8e00122e:	480b 0152 	mov r2,0x1540
8e001232:	400b 18e2 	movt r2,0x8e00
8e001236:	0952      	jalr r2
8e001238:	1fbc 0500 	strh r0,[fp,-0x7]
8e00123c:	3f2c 0500 	ldrh r1,[fp,-0x6]
8e001240:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001244:	443a      	sub r2,r1,r0
8e001246:	1200      	beq 8e00126a <bj_rr_read_obj+0x18e>
8e001248:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00124c:	3f8b 0ff2 	mov r1,0xfffc
8e001250:	209c 0003 	strb r1,[r0,+0x19]
8e001254:	01a2      	nop
8e001256:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00125a:	008c 0003 	ldrb r0,[r0,+0x19]
8e00125e:	0316      	lsl r0,r0,0x18
8e001260:	030e      	asr r0,r0,0x18
8e001262:	2233      	sub r1,r0,-4
8e001264:	f910      	bne 8e001256 <bj_rr_read_obj+0x17a>
8e001266:	0003      	mov r0,0x0
8e001268:	31e0      	b 8e0012ca <bj_rr_read_obj+0x1ee>
8e00126a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00126e:	0244      	ldr r0,[r0,0x4]
8e001270:	1d5c 0500 	str r0,[fp,-0x2]
8e001274:	16e0      	b 8e0012a0 <bj_rr_read_obj+0x1c4>
8e001276:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00127a:	2144      	ldr r1,[r0,0x2]
8e00127c:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001280:	443a      	sub r2,r1,r0
8e001282:	0610      	bne 8e00128e <bj_rr_read_obj+0x1b2>
8e001284:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001288:	00c4      	ldr r0,[r0,0x1]
8e00128a:	1d5c 0500 	str r0,[fp,-0x2]
8e00128e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001292:	2003      	mov r1,0x0
8e001294:	2014      	strb r1,[r0]
8e001296:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00129a:	0093      	add r0,r0,1
8e00129c:	1d5c 0500 	str r0,[fp,-0x2]
8e0012a0:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0012a4:	3d4c 0500 	ldr r1,[fp,-0x2]
8e0012a8:	443a      	sub r2,r1,r0
8e0012aa:	e610      	bne 8e001276 <bj_rr_read_obj+0x19a>
8e0012ac:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0012b0:	3d4c 0500 	ldr r1,[fp,-0x2]
8e0012b4:	2254      	str r1,[r0,0x4]
8e0012b6:	01a2      	nop
8e0012b8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0012bc:	2244      	ldr r1,[r0,0x4]
8e0012be:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0012c2:	443a      	sub r2,r1,r0
8e0012c4:	fa10      	bne 8e0012b8 <bj_rr_read_obj+0x1dc>
8e0012c6:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0012ca:	d76c 2400 	ldrd lr,[sp,+0x6]
8e0012ce:	b41b 2406 	add sp,sp,48
8e0012d2:	194f 0402 	rts
8e0012d6:	01a2      	nop

8e0012d8 <bj_rr_write_obj>:
8e0012d8:	d77c 2700 	strd lr,[sp],-0x6
8e0012dc:	f41b 2406 	add fp,sp,48
8e0012e0:	1fdc 0500 	str r0,[fp,-0x7]
8e0012e4:	04e2      	mov r0,r1
8e0012e6:	5cdc 0501 	str r2,[fp,-0x9]
8e0012ea:	1c3c 0502 	strh r0,[fp,-0x10]
8e0012ee:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0012f2:	2033      	sub r1,r0,0
8e0012f4:	0410      	bne 8e0012fc <bj_rr_write_obj+0x24>
8e0012f6:	0003      	mov r0,0x0
8e0012f8:	1de8 0001 	b 8e001532 <bj_rr_write_obj+0x25a>
8e0012fc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001300:	02c4      	ldr r0,[r0,0x5]
8e001302:	1e5c 0500 	str r0,[fp,-0x4]
8e001306:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e00130a:	1cbc 0501 	strh r0,[fp,-0x9]
8e00130e:	3cac 0501 	ldrh r1,[fp,-0x9]
8e001312:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001316:	0144      	ldr r0,[r0,0x2]
8e001318:	40e2      	mov r2,r0
8e00131a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00131e:	00c4      	ldr r0,[r0,0x1]
8e001320:	083a      	sub r0,r2,r0
8e001322:	0213      	add r0,r0,-4
8e001324:	443a      	sub r2,r1,r0
8e001326:	2540      	blteu 8e001370 <bj_rr_write_obj+0x98>
8e001328:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00132c:	3feb 0ff2 	mov r1,0xffff
8e001330:	201c 0003 	strb r1,[r0,+0x18]
8e001334:	01a2      	nop
8e001336:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00133a:	000c 0003 	ldrb r0,[r0,+0x18]
8e00133e:	0316      	lsl r0,r0,0x18
8e001340:	030e      	asr r0,r0,0x18
8e001342:	23b3      	sub r1,r0,-1
8e001344:	f910      	bne 8e001336 <bj_rr_write_obj+0x5e>
8e001346:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00134a:	0093      	add r0,r0,1
8e00134c:	1e5c 0500 	str r0,[fp,-0x4]
8e001350:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001354:	3e4c 0500 	ldr r1,[fp,-0x4]
8e001358:	22d4      	str r1,[r0,0x5]
8e00135a:	01a2      	nop
8e00135c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001360:	22c4      	ldr r1,[r0,0x5]
8e001362:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001366:	443a      	sub r2,r1,r0
8e001368:	fa10      	bne 8e00135c <bj_rr_write_obj+0x84>
8e00136a:	0003      	mov r0,0x0
8e00136c:	e3e8 0000 	b 8e001532 <bj_rr_write_obj+0x25a>
8e001370:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001374:	2033      	sub r1,r0,0
8e001376:	2510      	bne 8e0013c0 <bj_rr_write_obj+0xe8>
8e001378:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00137c:	3fcb 0ff2 	mov r1,0xfffe
8e001380:	201c 0003 	strb r1,[r0,+0x18]
8e001384:	01a2      	nop
8e001386:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00138a:	000c 0003 	ldrb r0,[r0,+0x18]
8e00138e:	0316      	lsl r0,r0,0x18
8e001390:	030e      	asr r0,r0,0x18
8e001392:	4333      	sub r2,r0,-2
8e001394:	f910      	bne 8e001386 <bj_rr_write_obj+0xae>
8e001396:	1e4c 0500 	ldr r0,[fp,-0x4]
8e00139a:	0093      	add r0,r0,1
8e00139c:	1e5c 0500 	str r0,[fp,-0x4]
8e0013a0:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0013a4:	3e4c 0500 	ldr r1,[fp,-0x4]
8e0013a8:	22d4      	str r1,[r0,0x5]
8e0013aa:	01a2      	nop
8e0013ac:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0013b0:	22c4      	ldr r1,[r0,0x5]
8e0013b2:	1e4c 0500 	ldr r0,[fp,-0x4]
8e0013b6:	443a      	sub r2,r1,r0
8e0013b8:	fa10      	bne 8e0013ac <bj_rr_write_obj+0xd4>
8e0013ba:	0003      	mov r0,0x0
8e0013bc:	bbe8 0000 	b 8e001532 <bj_rr_write_obj+0x25a>
8e0013c0:	1c2c 0502 	ldrh r0,[fp,-0x10]
8e0013c4:	031b 0000 	add r0,r0,6
8e0013c8:	1cbc 0500 	strh r0,[fp,-0x1]
8e0013cc:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0013d0:	01c4      	ldr r0,[r0,0x3]
8e0013d2:	1d5c 0500 	str r0,[fp,-0x2]
8e0013d6:	20e0      	b 8e001416 <bj_rr_write_obj+0x13e>
8e0013d8:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0013dc:	2144      	ldr r1,[r0,0x2]
8e0013de:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0013e2:	443a      	sub r2,r1,r0
8e0013e4:	0610      	bne 8e0013f0 <bj_rr_write_obj+0x118>
8e0013e6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0013ea:	00c4      	ldr r0,[r0,0x1]
8e0013ec:	1d5c 0500 	str r0,[fp,-0x2]
8e0013f0:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0013f4:	0004      	ldrb r0,[r0]
8e0013f6:	2033      	sub r1,r0,0
8e0013f8:	0500      	beq 8e001402 <bj_rr_write_obj+0x12a>
8e0013fa:	0003      	mov r0,0x0
8e0013fc:	1d5c 0500 	str r0,[fp,-0x2]
8e001400:	0fe0      	b 8e00141e <bj_rr_write_obj+0x146>
8e001402:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001406:	0093      	add r0,r0,1
8e001408:	1d5c 0500 	str r0,[fp,-0x2]
8e00140c:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001410:	0393      	add r0,r0,-1
8e001412:	1cbc 0500 	strh r0,[fp,-0x1]
8e001416:	1cac 0500 	ldrh r0,[fp,-0x1]
8e00141a:	4033      	sub r2,r0,0
8e00141c:	de10      	bne 8e0013d8 <bj_rr_write_obj+0x100>
8e00141e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001422:	2033      	sub r1,r0,0
8e001424:	2410      	bne 8e00146c <bj_rr_write_obj+0x194>
8e001426:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00142a:	3fab 0ff2 	mov r1,0xfffd
8e00142e:	201c 0003 	strb r1,[r0,+0x18]
8e001432:	01a2      	nop
8e001434:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001438:	000c 0003 	ldrb r0,[r0,+0x18]
8e00143c:	0316      	lsl r0,r0,0x18
8e00143e:	030e      	asr r0,r0,0x18
8e001440:	42b3      	sub r2,r0,-3
8e001442:	f910      	bne 8e001434 <bj_rr_write_obj+0x15c>
8e001444:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001448:	0093      	add r0,r0,1
8e00144a:	1e5c 0500 	str r0,[fp,-0x4]
8e00144e:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001452:	3e4c 0500 	ldr r1,[fp,-0x4]
8e001456:	22d4      	str r1,[r0,0x5]
8e001458:	01a2      	nop
8e00145a:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00145e:	22c4      	ldr r1,[r0,0x5]
8e001460:	1e4c 0500 	ldr r0,[fp,-0x4]
8e001464:	443a      	sub r2,r1,r0
8e001466:	fa10      	bne 8e00145a <bj_rr_write_obj+0x182>
8e001468:	0003      	mov r0,0x0
8e00146a:	64e0      	b 8e001532 <bj_rr_write_obj+0x25a>
8e00146c:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001470:	01c4      	ldr r0,[r0,0x3]
8e001472:	1f5c 0500 	str r0,[fp,-0x6]
8e001476:	3c2c 0502 	ldrh r1,[fp,-0x10]
8e00147a:	1c1b 04fd 	add r0,fp,-24
8e00147e:	44e2      	mov r2,r1
8e001480:	20e2      	mov r1,r0
8e001482:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001486:	748b 0172 	mov r3,0x17a4
8e00148a:	600b 18e2 	movt r3,0x8e00
8e00148e:	0d52      	jalr r3
8e001490:	0003      	mov r0,0x0
8e001492:	1ebc 0500 	strh r0,[fp,-0x5]
8e001496:	20e0      	b 8e0014d6 <bj_rr_write_obj+0x1fe>
8e001498:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00149c:	2144      	ldr r1,[r0,0x2]
8e00149e:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0014a2:	443a      	sub r2,r1,r0
8e0014a4:	0610      	bne 8e0014b0 <bj_rr_write_obj+0x1d8>
8e0014a6:	1fcc 0500 	ldr r0,[fp,-0x7]
8e0014aa:	00c4      	ldr r0,[r0,0x1]
8e0014ac:	1f5c 0500 	str r0,[fp,-0x6]
8e0014b0:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0014b4:	3eac 0500 	ldrh r1,[fp,-0x5]
8e0014b8:	5ccc 0501 	ldr r2,[fp,-0x9]
8e0014bc:	289a      	add r1,r2,r1
8e0014be:	2404      	ldrb r1,[r1]
8e0014c0:	2014      	strb r1,[r0]
8e0014c2:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0014c6:	0093      	add r0,r0,1
8e0014c8:	1f5c 0500 	str r0,[fp,-0x6]
8e0014cc:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0014d0:	0093      	add r0,r0,1
8e0014d2:	1ebc 0500 	strh r0,[fp,-0x5]
8e0014d6:	3eac 0500 	ldrh r1,[fp,-0x5]
8e0014da:	1cac 0501 	ldrh r0,[fp,-0x9]
8e0014de:	443a      	sub r2,r1,r0
8e0014e0:	dc50      	bltu 8e001498 <bj_rr_write_obj+0x1c0>
8e0014e2:	1cac 0501 	ldrh r0,[fp,-0x9]
8e0014e6:	20e2      	mov r1,r0
8e0014e8:	1ccc 0501 	ldr r0,[fp,-0x9]
8e0014ec:	480b 0152 	mov r2,0x1540
8e0014f0:	400b 18e2 	movt r2,0x8e00
8e0014f4:	0952      	jalr r2
8e0014f6:	1d3c 0501 	strh r0,[fp,-0xa]
8e0014fa:	3d2c 0501 	ldrh r1,[fp,-0xa]
8e0014fe:	1c1b 04fd 	add r0,fp,-24
8e001502:	44e2      	mov r2,r1
8e001504:	20e2      	mov r1,r0
8e001506:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00150a:	748b 0172 	mov r3,0x17a4
8e00150e:	600b 18e2 	movt r3,0x8e00
8e001512:	0d52      	jalr r3
8e001514:	3f4c 0500 	ldr r1,[fp,-0x6]
8e001518:	1fcc 0500 	ldr r0,[fp,-0x7]
8e00151c:	21d4      	str r1,[r0,0x3]
8e00151e:	01a2      	nop
8e001520:	1fcc 0500 	ldr r0,[fp,-0x7]
8e001524:	21c4      	ldr r1,[r0,0x3]
8e001526:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00152a:	443a      	sub r2,r1,r0
8e00152c:	fa10      	bne 8e001520 <bj_rr_write_obj+0x248>
8e00152e:	1cac 0501 	ldrh r0,[fp,-0x9]
8e001532:	d76c 2400 	ldrd lr,[sp,+0x6]
8e001536:	b41b 2406 	add sp,sp,48
8e00153a:	194f 0402 	rts
8e00153e:	01a2      	nop

8e001540 <bj_crc16>:
8e001540:	f75c 2700 	str fp,[sp],-0x6
8e001544:	f4ef 2402 	mov fp,sp
8e001548:	1ddc 0400 	str r0,[fp,+0x3]
8e00154c:	04e2      	mov r0,r1
8e00154e:	1e3c 0400 	strh r0,[fp,+0x4]
8e001552:	1feb 0ff2 	mov r0,0xffff
8e001556:	1feb 1ff2 	movt r0,0xffff
8e00155a:	1cbc 0401 	strh r0,[fp,+0x9]
8e00155e:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e001562:	2033      	sub r1,r0,0
8e001564:	0b10      	bne 8e00157a <bj_crc16+0x3a>
8e001566:	3cac 0401 	ldrh r1,[fp,+0x9]
8e00156a:	1feb 0ff2 	mov r0,0xffff
8e00156e:	1feb 1ff2 	movt r0,0xffff
8e001572:	040a      	eor r0,r1,r0
8e001574:	000b 1002 	movt r0,0x0
8e001578:	65e0      	b 8e001642 <bj_crc16+0x102>
8e00157a:	0003      	mov r0,0x0
8e00157c:	1f9c 0402 	strb r0,[fp,+0x17]
8e001580:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001584:	2093      	add r1,r0,1
8e001586:	3ddc 0400 	str r1,[fp,+0x3]
8e00158a:	0004      	ldrb r0,[r0]
8e00158c:	1d3c 0401 	strh r0,[fp,+0xa]
8e001590:	2ae0      	b 8e0015e4 <bj_crc16+0xa4>
8e001592:	3cac 0401 	ldrh r1,[fp,+0x9]
8e001596:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e00159a:	040a      	eor r0,r1,r0
8e00159c:	000b 1002 	movt r0,0x0
8e0015a0:	20e2      	mov r1,r0
8e0015a2:	0023      	mov r0,0x1
8e0015a4:	045a      	and r0,r1,r0
8e0015a6:	2033      	sub r1,r0,0
8e0015a8:	0f00      	beq 8e0015c6 <bj_crc16+0x86>
8e0015aa:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0015ae:	0026      	lsr r0,r0,0x1
8e0015b0:	20e2      	mov r1,r0
8e0015b2:	200b 1002 	movt r1,0x0
8e0015b6:	010b 0842 	mov r0,0x8408
8e0015ba:	1feb 1ff2 	movt r0,0xffff
8e0015be:	040a      	eor r0,r1,r0
8e0015c0:	1cbc 0401 	strh r0,[fp,+0x9]
8e0015c4:	06e0      	b 8e0015d0 <bj_crc16+0x90>
8e0015c6:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0015ca:	0026      	lsr r0,r0,0x1
8e0015cc:	1cbc 0401 	strh r0,[fp,+0x9]
8e0015d0:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e0015d4:	0093      	add r0,r0,1
8e0015d6:	1f9c 0402 	strb r0,[fp,+0x17]
8e0015da:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0015de:	0026      	lsr r0,r0,0x1
8e0015e0:	1d3c 0401 	strh r0,[fp,+0xa]
8e0015e4:	1f8c 0402 	ldrb r0,[fp,+0x17]
8e0015e8:	23bb 0000 	sub r1,r0,7
8e0015ec:	d340      	blteu 8e001592 <bj_crc16+0x52>
8e0015ee:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0015f2:	0393      	add r0,r0,-1
8e0015f4:	1e3c 0400 	strh r0,[fp,+0x4]
8e0015f8:	1e2c 0400 	ldrh r0,[fp,+0x4]
8e0015fc:	2033      	sub r1,r0,0
8e0015fe:	be10      	bne 8e00157a <bj_crc16+0x3a>
8e001600:	3cac 0401 	ldrh r1,[fp,+0x9]
8e001604:	1feb 0ff2 	mov r0,0xffff
8e001608:	1feb 1ff2 	movt r0,0xffff
8e00160c:	040a      	eor r0,r1,r0
8e00160e:	1cbc 0401 	strh r0,[fp,+0x9]
8e001612:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001616:	1d3c 0401 	strh r0,[fp,+0xa]
8e00161a:	1cac 0401 	ldrh r0,[fp,+0x9]
8e00161e:	0116      	lsl r0,r0,0x8
8e001620:	20e2      	mov r1,r0
8e001622:	200b 1002 	movt r1,0x0
8e001626:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e00162a:	0106      	lsr r0,r0,0x8
8e00162c:	000b 1002 	movt r0,0x0
8e001630:	000b 1002 	movt r0,0x0
8e001634:	047a      	orr r0,r1,r0
8e001636:	000b 1002 	movt r0,0x0
8e00163a:	1cbc 0401 	strh r0,[fp,+0x9]
8e00163e:	1cac 0401 	ldrh r0,[fp,+0x9]
8e001642:	f74c 2400 	ldr fp,[sp,+0x6]
8e001646:	b41b 2403 	add sp,sp,24
8e00164a:	194f 0402 	rts
8e00164e:	01a2      	nop

8e001650 <bj_get_v16_of_p8>:
8e001650:	f75c 2700 	str fp,[sp],-0x6
8e001654:	f4ef 2402 	mov fp,sp
8e001658:	1ddc 0400 	str r0,[fp,+0x3]
8e00165c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001660:	0093      	add r0,r0,1
8e001662:	0004      	ldrb r0,[r0]
8e001664:	1dbc 0401 	strh r0,[fp,+0xb]
8e001668:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00166c:	0116      	lsl r0,r0,0x8
8e00166e:	1dbc 0401 	strh r0,[fp,+0xb]
8e001672:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001676:	0004      	ldrb r0,[r0]
8e001678:	20e2      	mov r1,r0
8e00167a:	200b 1002 	movt r1,0x0
8e00167e:	1dac 0401 	ldrh r0,[fp,+0xb]
8e001682:	047a      	orr r0,r1,r0
8e001684:	1dbc 0401 	strh r0,[fp,+0xb]
8e001688:	1dac 0401 	ldrh r0,[fp,+0xb]
8e00168c:	f74c 2400 	ldr fp,[sp,+0x6]
8e001690:	b41b 2403 	add sp,sp,24
8e001694:	194f 0402 	rts

8e001698 <bj_set_v16_of_p8>:
8e001698:	f75c 2700 	str fp,[sp],-0x6
8e00169c:	f4ef 2402 	mov fp,sp
8e0016a0:	1ddc 0400 	str r0,[fp,+0x3]
8e0016a4:	04e2      	mov r0,r1
8e0016a6:	1e3c 0400 	strh r0,[fp,+0x4]
8e0016aa:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e0016ae:	1fe3      	mov r0,0xff
8e0016b0:	045a      	and r0,r1,r0
8e0016b2:	1dbc 0401 	strh r0,[fp,+0xb]
8e0016b6:	3e2c 0400 	ldrh r1,[fp,+0x4]
8e0016ba:	000b 0ff2 	mov r0,0xff00
8e0016be:	1feb 1ff2 	movt r0,0xffff
8e0016c2:	045a      	and r0,r1,r0
8e0016c4:	1d3c 0401 	strh r0,[fp,+0xa]
8e0016c8:	1d2c 0401 	ldrh r0,[fp,+0xa]
8e0016cc:	0106      	lsr r0,r0,0x8
8e0016ce:	1d3c 0401 	strh r0,[fp,+0xa]
8e0016d2:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0016d6:	0093      	add r0,r0,1
8e0016d8:	3d2c 0401 	ldrh r1,[fp,+0xa]
8e0016dc:	2716      	lsl r1,r1,0x18
8e0016de:	2706      	lsr r1,r1,0x18
8e0016e0:	2014      	strb r1,[r0]
8e0016e2:	1dac 0401 	ldrh r0,[fp,+0xb]
8e0016e6:	2316      	lsl r1,r0,0x18
8e0016e8:	2706      	lsr r1,r1,0x18
8e0016ea:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0016ee:	2014      	strb r1,[r0]
8e0016f0:	01a2      	nop
8e0016f2:	f74c 2400 	ldr fp,[sp,+0x6]
8e0016f6:	b41b 2403 	add sp,sp,24
8e0016fa:	194f 0402 	rts
8e0016fe:	01a2      	nop

8e001700 <bj_rr_get_v16>:
8e001700:	d67c 2700 	strd lr,[sp],-0x4
8e001704:	f41b 2404 	add fp,sp,32
8e001708:	1edc 0500 	str r0,[fp,-0x5]
8e00170c:	3f5c 0500 	str r1,[fp,-0x6]
8e001710:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001714:	2033      	sub r1,r0,0
8e001716:	0310      	bne 8e00171c <bj_rr_get_v16+0x1c>
8e001718:	0003      	mov r0,0x0
8e00171a:	3ee0      	b 8e001796 <bj_rr_get_v16+0x96>
8e00171c:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001720:	0044      	ldr r0,[r0]
8e001722:	1cdc 0500 	str r0,[fp,-0x1]
8e001726:	0003      	mov r0,0x0
8e001728:	1d5c 0500 	str r0,[fp,-0x2]
8e00172c:	21e0      	b 8e00176e <bj_rr_get_v16+0x6e>
8e00172e:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001732:	2144      	ldr r1,[r0,0x2]
8e001734:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001738:	443a      	sub r2,r1,r0
8e00173a:	0610      	bne 8e001746 <bj_rr_get_v16+0x46>
8e00173c:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001740:	00c4      	ldr r0,[r0,0x1]
8e001742:	1cdc 0500 	str r0,[fp,-0x1]
8e001746:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00174a:	4004      	ldrb r2,[r0]
8e00174c:	3e1b 04fe 	add r1,fp,-12
8e001750:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001754:	041a      	add r0,r1,r0
8e001756:	28e2      	mov r1,r2
8e001758:	2014      	strb r1,[r0]
8e00175a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00175e:	0093      	add r0,r0,1
8e001760:	1cdc 0500 	str r0,[fp,-0x1]
8e001764:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001768:	0093      	add r0,r0,1
8e00176a:	1d5c 0500 	str r0,[fp,-0x2]
8e00176e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001772:	20b3      	sub r1,r0,1
8e001774:	dd90      	blte 8e00172e <bj_rr_get_v16+0x2e>
8e001776:	1f4c 0500 	ldr r0,[fp,-0x6]
8e00177a:	3ccc 0500 	ldr r1,[fp,-0x1]
8e00177e:	2054      	str r1,[r0]
8e001780:	1e1b 04fe 	add r0,fp,-12
8e001784:	2a0b 0162 	mov r1,0x1650
8e001788:	200b 18e2 	movt r1,0x8e00
8e00178c:	0552      	jalr r1
8e00178e:	1ebc 0500 	strh r0,[fp,-0x5]
8e001792:	1eac 0500 	ldrh r0,[fp,-0x5]
8e001796:	d66c 2400 	ldrd lr,[sp,+0x4]
8e00179a:	b41b 2404 	add sp,sp,32
8e00179e:	194f 0402 	rts
8e0017a2:	01a2      	nop

8e0017a4 <bj_rr_set_v16>:
8e0017a4:	d6fc 2700 	strd lr,[sp],-0x5
8e0017a8:	f41b 2405 	add fp,sp,40
8e0017ac:	1edc 0500 	str r0,[fp,-0x5]
8e0017b0:	3f5c 0500 	str r1,[fp,-0x6]
8e0017b4:	08e2      	mov r0,r2
8e0017b6:	1f3c 0501 	strh r0,[fp,-0xe]
8e0017ba:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0017be:	2033      	sub r1,r0,0
8e0017c0:	3c00      	beq 8e001838 <bj_rr_set_v16+0x94>
8e0017c2:	1f4c 0500 	ldr r0,[fp,-0x6]
8e0017c6:	0044      	ldr r0,[r0]
8e0017c8:	1cdc 0500 	str r0,[fp,-0x1]
8e0017cc:	3f2c 0501 	ldrh r1,[fp,-0xe]
8e0017d0:	1f1b 04fe 	add r0,fp,-10
8e0017d4:	530b 0162 	mov r2,0x1698
8e0017d8:	400b 18e2 	movt r2,0x8e00
8e0017dc:	0952      	jalr r2
8e0017de:	0003      	mov r0,0x0
8e0017e0:	1d5c 0500 	str r0,[fp,-0x2]
8e0017e4:	20e0      	b 8e001824 <bj_rr_set_v16+0x80>
8e0017e6:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0017ea:	2144      	ldr r1,[r0,0x2]
8e0017ec:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0017f0:	443a      	sub r2,r1,r0
8e0017f2:	0610      	bne 8e0017fe <bj_rr_set_v16+0x5a>
8e0017f4:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0017f8:	00c4      	ldr r0,[r0,0x1]
8e0017fa:	1cdc 0500 	str r0,[fp,-0x1]
8e0017fe:	3f1b 04fe 	add r1,fp,-10
8e001802:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001806:	041a      	add r0,r1,r0
8e001808:	2004      	ldrb r1,[r0]
8e00180a:	1ccc 0500 	ldr r0,[fp,-0x1]
8e00180e:	2014      	strb r1,[r0]
8e001810:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001814:	0093      	add r0,r0,1
8e001816:	1cdc 0500 	str r0,[fp,-0x1]
8e00181a:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00181e:	0093      	add r0,r0,1
8e001820:	1d5c 0500 	str r0,[fp,-0x2]
8e001824:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001828:	20b3      	sub r1,r0,1
8e00182a:	de90      	blte 8e0017e6 <bj_rr_set_v16+0x42>
8e00182c:	1f4c 0500 	ldr r0,[fp,-0x6]
8e001830:	3ccc 0500 	ldr r1,[fp,-0x1]
8e001834:	2054      	str r1,[r0]
8e001836:	02e0      	b 8e00183a <bj_rr_set_v16+0x96>
8e001838:	01a2      	nop
8e00183a:	d6ec 2400 	ldrd lr,[sp,+0x5]
8e00183e:	b41b 2405 	add sp,sp,40
8e001842:	194f 0402 	rts
8e001846:	01a2      	nop

8e001848 <bjk_get_call_stack_trace>:
8e001848:	d4fc 2701 	strd lr,[sp],-0x9
8e00184c:	f41b 2409 	add fp,sp,72
8e001850:	3c5c 0502 	str r1,[fp,-0x10]
8e001854:	1f3c 0503 	strh r0,[fp,-0x1e]
8e001858:	1c4c 0502 	ldr r0,[fp,-0x10]
8e00185c:	2033      	sub r1,r0,0
8e00185e:	0410      	bne 8e001866 <bjk_get_call_stack_trace+0x1e>
8e001860:	0003      	mov r0,0x0
8e001862:	22e8 0001 	b 8e001aa6 <bjk_get_call_stack_trace+0x25e>
8e001866:	1f2c 0503 	ldrh r0,[fp,-0x1e]
8e00186a:	0216      	lsl r0,r0,0x10
8e00186c:	020e      	asr r0,r0,0x10
8e00186e:	4033      	sub r2,r0,0
8e001870:	0460      	bgt 8e001878 <bjk_get_call_stack_trace+0x30>
8e001872:	0003      	mov r0,0x0
8e001874:	19e8 0001 	b 8e001aa6 <bjk_get_call_stack_trace+0x25e>
8e001878:	0003      	mov r0,0x0
8e00187a:	1cdc 0500 	str r0,[fp,-0x1]
8e00187e:	0003      	mov r0,0x0
8e001880:	1d5c 0500 	str r0,[fp,-0x2]
8e001884:	0003      	mov r0,0x0
8e001886:	1ddc 0500 	str r0,[fp,-0x3]
8e00188a:	0003      	mov r0,0x0
8e00188c:	1fbc 0500 	strh r0,[fp,-0x7]
8e001890:	1f2c 0503 	ldrh r0,[fp,-0x1e]
8e001894:	0216      	lsl r0,r0,0x10
8e001896:	020e      	asr r0,r0,0x10
8e001898:	2033      	sub r1,r0,0
8e00189a:	0460      	bgt 8e0018a2 <bjk_get_call_stack_trace+0x5a>
8e00189c:	0003      	mov r0,0x0
8e00189e:	04e8 0001 	b 8e001aa6 <bjk_get_call_stack_trace+0x25e>
8e0018a2:	0912      	movfs r0,pc
8e0018a4:	00e2      	mov r0,r0
8e0018a6:	1cdc 0500 	str r0,[fp,-0x1]
8e0018aa:	14ef 0402 	mov r0,sp
8e0018ae:	1d5c 0500 	str r0,[fp,-0x2]
8e0018b2:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0018b6:	278b 01e2 	mov r1,0x1e3c
8e0018ba:	200b 18e2 	movt r1,0x8e00
8e0018be:	0552      	jalr r1
8e0018c0:	1ddc 0500 	str r0,[fp,-0x3]
8e0018c4:	c9e8 0000 	b 8e001a56 <bjk_get_call_stack_trace+0x20e>
8e0018c8:	3fac 0500 	ldrh r1,[fp,-0x7]
8e0018cc:	1f2c 0503 	ldrh r0,[fp,-0x1e]
8e0018d0:	0216      	lsl r0,r0,0x10
8e0018d2:	020e      	asr r0,r0,0x10
8e0018d4:	443a      	sub r2,r1,r0
8e0018d6:	c608 0000 	beq 8e001a62 <bjk_get_call_stack_trace+0x21a>
8e0018da:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0018de:	2d0b 01f2 	mov r1,0x1f68
8e0018e2:	200b 18e2 	movt r1,0x8e00
8e0018e6:	0552      	jalr r1
8e0018e8:	1c3c 0501 	strh r0,[fp,-0x8]
8e0018ec:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e0018f0:	2033      	sub r1,r0,0
8e0018f2:	ba08 0000 	beq 8e001a66 <bjk_get_call_stack_trace+0x21e>
8e0018f6:	3c2c 0501 	ldrh r1,[fp,-0x8]
8e0018fa:	0023      	mov r0,0x1
8e0018fc:	045a      	and r0,r1,r0
8e0018fe:	000b 1002 	movt r0,0x0
8e001902:	4033      	sub r2,r0,0
8e001904:	0f00      	beq 8e001922 <bjk_get_call_stack_trace+0xda>
8e001906:	090b 0182 	mov r0,0x1848
8e00190a:	000b 18e2 	movt r0,0x8e00
8e00190e:	4003      	mov r2,0x0
8e001910:	3feb 0ff2 	mov r1,0xffff
8e001914:	3feb 1ff2 	movt r1,0xffff
8e001918:	768b 01a2 	mov r3,0x1ab4
8e00191c:	600b 18e2 	movt r3,0x8e00
8e001920:	0d52      	jalr r3
8e001922:	1d4c 0500 	ldr r0,[fp,-0x2]
8e001926:	1edc 0500 	str r0,[fp,-0x5]
8e00192a:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e00192e:	3ecc 0500 	ldr r1,[fp,-0x5]
8e001932:	041a      	add r0,r1,r0
8e001934:	1edc 0500 	str r0,[fp,-0x5]
8e001938:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00193c:	1d5c 0500 	str r0,[fp,-0x2]
8e001940:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001944:	0066      	lsr r0,r0,0x3
8e001946:	1dbc 0501 	strh r0,[fp,-0xb]
8e00194a:	1dac 0501 	ldrh r0,[fp,-0xb]
8e00194e:	0216      	lsl r0,r0,0x10
8e001950:	020e      	asr r0,r0,0x10
8e001952:	3d1b 04f9 	add r1,fp,-54
8e001956:	3c5c 0501 	str r1,[fp,-0x8]
8e00195a:	1cbc 0503 	strh r0,[fp,-0x19]
8e00195e:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001962:	2f8b 0d42 	mov r1,0xd47c
8e001966:	3feb 1ff2 	movt r1,0xffff
8e00196a:	2034      	strh r1,[r0]
8e00196c:	1c4c 0501 	ldr r0,[fp,-0x8]
8e001970:	0113      	add r0,r0,2
8e001972:	200b 0272 	mov r1,0x2700
8e001976:	2034      	strh r1,[r0]
8e001978:	1c4c 0501 	ldr r0,[fp,-0x8]
8e00197c:	0024      	ldrh r0,[r0]
8e00197e:	20e2      	mov r1,r0
8e001980:	200b 1002 	movt r1,0x0
8e001984:	1cac 0503 	ldrh r0,[fp,-0x19]
8e001988:	40e2      	mov r2,r0
8e00198a:	00e3      	mov r0,0x7
8e00198c:	085a      	and r0,r2,r0
8e00198e:	00f6      	lsl r0,r0,0x7
8e001990:	000b 1002 	movt r0,0x0
8e001994:	047a      	orr r0,r1,r0
8e001996:	000b 1002 	movt r0,0x0
8e00199a:	20e2      	mov r1,r0
8e00199c:	200b 1002 	movt r1,0x0
8e0019a0:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0019a4:	2034      	strh r1,[r0]
8e0019a6:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0019aa:	2113      	add r1,r0,2
8e0019ac:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0019b0:	0113      	add r0,r0,2
8e0019b2:	0024      	ldrh r0,[r0]
8e0019b4:	40e2      	mov r2,r0
8e0019b6:	400b 1002 	movt r2,0x0
8e0019ba:	1cac 0503 	ldrh r0,[fp,-0x19]
8e0019be:	0216      	lsl r0,r0,0x10
8e0019c0:	020e      	asr r0,r0,0x10
8e0019c2:	006e      	asr r0,r0,0x3
8e0019c4:	000b 1002 	movt r0,0x0
8e0019c8:	087a      	orr r0,r2,r0
8e0019ca:	000b 1002 	movt r0,0x0
8e0019ce:	000b 1002 	movt r0,0x0
8e0019d2:	0434      	strh r0,[r1]
8e0019d4:	1d1b 04f9 	add r0,fp,-54
8e0019d8:	20e2      	mov r1,r0
8e0019da:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0019de:	560b 01c2 	mov r2,0x1cb0
8e0019e2:	400b 18e2 	movt r2,0x8e00
8e0019e6:	0952      	jalr r2
8e0019e8:	1fdc 0500 	str r0,[fp,-0x7]
8e0019ec:	1d4c 0500 	ldr r0,[fp,-0x2]
8e0019f0:	1ddc 0501 	str r0,[fp,-0xb]
8e0019f4:	1dcc 0501 	ldr r0,[fp,-0xb]
8e0019f8:	0113      	add r0,r0,2
8e0019fa:	0024      	ldrh r0,[r0]
8e0019fc:	1e5c 0501 	str r0,[fp,-0xc]
8e001a00:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001a04:	0216      	lsl r0,r0,0x10
8e001a06:	1e5c 0501 	str r0,[fp,-0xc]
8e001a0a:	1dcc 0501 	ldr r0,[fp,-0xb]
8e001a0e:	0024      	ldrh r0,[r0]
8e001a10:	20e2      	mov r1,r0
8e001a12:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001a16:	00fa      	orr r0,r0,r1
8e001a18:	1e5c 0501 	str r0,[fp,-0xc]
8e001a1c:	1e4c 0501 	ldr r0,[fp,-0xc]
8e001a20:	1cdc 0501 	str r0,[fp,-0x9]
8e001a24:	1ccc 0501 	ldr r0,[fp,-0x9]
8e001a28:	1cdc 0500 	str r0,[fp,-0x1]
8e001a2c:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001a30:	2093      	add r1,r0,1
8e001a32:	3fbc 0500 	strh r1,[fp,-0x7]
8e001a36:	0056      	lsl r0,r0,0x2
8e001a38:	3c4c 0502 	ldr r1,[fp,-0x10]
8e001a3c:	041a      	add r0,r1,r0
8e001a3e:	3fcc 0500 	ldr r1,[fp,-0x7]
8e001a42:	2054      	str r1,[r0]
8e001a44:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001a48:	278b 01e2 	mov r1,0x1e3c
8e001a4c:	200b 18e2 	movt r1,0x8e00
8e001a50:	0552      	jalr r1
8e001a52:	1ddc 0500 	str r0,[fp,-0x3]
8e001a56:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001a5a:	2033      	sub r1,r0,0
8e001a5c:	3618 ffff 	bne 8e0018c8 <bjk_get_call_stack_trace+0x80>
8e001a60:	04e0      	b 8e001a68 <bjk_get_call_stack_trace+0x220>
8e001a62:	01a2      	nop
8e001a64:	02e0      	b 8e001a68 <bjk_get_call_stack_trace+0x220>
8e001a66:	01a2      	nop
8e001a68:	1b0b 01b2 	mov r0,0x1bd8
8e001a6c:	000b 1002 	movt r0,0x0
8e001a70:	0024      	ldrh r0,[r0]
8e001a72:	40bb 0008 	sub r2,r0,65
8e001a76:	1610      	bne 8e001aa2 <bjk_get_call_stack_trace+0x25a>
8e001a78:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001a7c:	2c0b 01d2 	mov r1,0x1d60
8e001a80:	200b 18e2 	movt r1,0x8e00
8e001a84:	0552      	jalr r1
8e001a86:	1d5c 0501 	str r0,[fp,-0xa]
8e001a8a:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001a8e:	2093      	add r1,r0,1
8e001a90:	3fbc 0500 	strh r1,[fp,-0x7]
8e001a94:	0056      	lsl r0,r0,0x2
8e001a96:	3c4c 0502 	ldr r1,[fp,-0x10]
8e001a9a:	041a      	add r0,r1,r0
8e001a9c:	3d4c 0501 	ldr r1,[fp,-0xa]
8e001aa0:	2054      	str r1,[r0]
8e001aa2:	1fac 0500 	ldrh r0,[fp,-0x7]
8e001aa6:	d4ec 2401 	ldrd lr,[sp,+0x9]
8e001aaa:	b41b 2409 	add sp,sp,72
8e001aae:	194f 0402 	rts
8e001ab2:	01a2      	nop

8e001ab4 <bjk_abort>:
8e001ab4:	d5fc 2700 	strd lr,[sp],-0x3
8e001ab8:	f41b 2403 	add fp,sp,24
8e001abc:	1cdc 0500 	str r0,[fp,-0x1]
8e001ac0:	04e2      	mov r0,r1
8e001ac2:	5ddc 0500 	str r2,[fp,-0x3]
8e001ac6:	1e3c 0500 	strh r0,[fp,-0x4]
8e001aca:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001ace:	2033      	sub r1,r0,0
8e001ad0:	1010      	bne 8e001af0 <bjk_abort+0x3c>
8e001ad2:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e001ad6:	0216      	lsl r0,r0,0x10
8e001ad8:	020e      	asr r0,r0,0x10
8e001ada:	4033      	sub r2,r0,0
8e001adc:	0a80      	blt 8e001af0 <bjk_abort+0x3c>
8e001ade:	0283      	mov r0,0x14
8e001ae0:	1e3c 0500 	strh r0,[fp,-0x4]
8e001ae4:	110b 01b2 	mov r0,0x1b88
8e001ae8:	000b 1002 	movt r0,0x0
8e001aec:	1ddc 0500 	str r0,[fp,-0x3]
8e001af0:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001af4:	2033      	sub r1,r0,0
8e001af6:	1200      	beq 8e001b1a <bjk_abort+0x66>
8e001af8:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e001afc:	0216      	lsl r0,r0,0x10
8e001afe:	020e      	asr r0,r0,0x10
8e001b00:	4033      	sub r2,r0,0
8e001b02:	0c90      	blte 8e001b1a <bjk_abort+0x66>
8e001b04:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e001b08:	0216      	lsl r0,r0,0x10
8e001b0a:	020e      	asr r0,r0,0x10
8e001b0c:	3dcc 0500 	ldr r1,[fp,-0x3]
8e001b10:	490b 0182 	mov r2,0x1848
8e001b14:	400b 18e2 	movt r2,0x8e00
8e001b18:	0952      	jalr r2
8e001b1a:	1c0b 01b2 	mov r0,0x1be0
8e001b1e:	000b 1002 	movt r0,0x0
8e001b22:	3ccc 0500 	ldr r1,[fp,-0x1]
8e001b26:	2154      	str r1,[r0,0x2]
8e001b28:	060b 01c2 	mov r0,0x1c30
8e001b2c:	000b 1002 	movt r0,0x0
8e001b30:	0044      	ldr r0,[r0]
8e001b32:	2033      	sub r1,r0,0
8e001b34:	1f00      	beq 8e001b72 <bjk_abort+0xbe>
8e001b36:	060b 01c2 	mov r0,0x1c30
8e001b3a:	000b 1002 	movt r0,0x0
8e001b3e:	0044      	ldr r0,[r0]
8e001b40:	2044      	ldr r1,[r0]
8e001b42:	1bab 0cc2 	mov r0,0xccdd
8e001b46:	176b 1aa2 	movt r0,0xaabb
8e001b4a:	443a      	sub r2,r1,r0
8e001b4c:	1310      	bne 8e001b72 <bjk_abort+0xbe>
8e001b4e:	060b 01c2 	mov r0,0x1c30
8e001b52:	000b 1002 	movt r0,0x0
8e001b56:	0044      	ldr r0,[r0]
8e001b58:	3e2b 0ff2 	mov r1,0xfff1
8e001b5c:	2314      	strb r1,[r0,0x6]
8e001b5e:	01a2      	nop
8e001b60:	060b 01c2 	mov r0,0x1c30
8e001b64:	000b 1002 	movt r0,0x0
8e001b68:	0044      	ldr r0,[r0]
8e001b6a:	0304      	ldrb r0,[r0,0x6]
8e001b6c:	20bb 001e 	sub r1,r0,241
8e001b70:	f810      	bne 8e001b60 <bjk_abort+0xac>
8e001b72:	1c0b 01b2 	mov r0,0x1be0
8e001b76:	000b 1002 	movt r0,0x0
8e001b7a:	c0ef e002 	mov r62,r0
8e001b7e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e001b82:	e0ef e002 	mov r63,r0
8e001b86:	0392      	gid
8e001b88:	0fe2      	trap 0x3
8e001b8a:	0912      	movfs r0,pc
8e001b8c:	0152      	jalr r0
8e001b8e:	01a2      	nop
8e001b90:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e001b94:	b41b 2403 	add sp,sp,24
8e001b98:	194f 0402 	rts

8e001b9c <bjk_wait_sync>:
8e001b9c:	d67c 2700 	strd lr,[sp],-0x4
8e001ba0:	f41b 2404 	add fp,sp,32
8e001ba4:	1ddc 0500 	str r0,[fp,-0x3]
8e001ba8:	04e2      	mov r0,r1
8e001baa:	5edc 0500 	str r2,[fp,-0x5]
8e001bae:	1c3c 0501 	strh r0,[fp,-0x8]
8e001bb2:	060b 01c2 	mov r0,0x1c30
8e001bb6:	000b 1002 	movt r0,0x0
8e001bba:	0044      	ldr r0,[r0]
8e001bbc:	2033      	sub r1,r0,0
8e001bbe:	0c10      	bne 8e001bd6 <bjk_wait_sync+0x3a>
8e001bc0:	138b 01b2 	mov r0,0x1b9c
8e001bc4:	000b 18e2 	movt r0,0x8e00
8e001bc8:	4003      	mov r2,0x0
8e001bca:	2003      	mov r1,0x0
8e001bcc:	768b 01a2 	mov r3,0x1ab4
8e001bd0:	600b 18e2 	movt r3,0x8e00
8e001bd4:	0d52      	jalr r3
8e001bd6:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001bda:	0216      	lsl r0,r0,0x10
8e001bdc:	020e      	asr r0,r0,0x10
8e001bde:	4033      	sub r2,r0,0
8e001be0:	1090      	blte 8e001c00 <bjk_wait_sync+0x64>
8e001be2:	1ecc 0500 	ldr r0,[fp,-0x5]
8e001be6:	2033      	sub r1,r0,0
8e001be8:	0c00      	beq 8e001c00 <bjk_wait_sync+0x64>
8e001bea:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e001bee:	0216      	lsl r0,r0,0x10
8e001bf0:	020e      	asr r0,r0,0x10
8e001bf2:	3ecc 0500 	ldr r1,[fp,-0x5]
8e001bf6:	490b 0182 	mov r2,0x1848
8e001bfa:	400b 18e2 	movt r2,0x8e00
8e001bfe:	0952      	jalr r2
8e001c00:	0003      	mov r0,0x0
8e001c02:	1cbc 0500 	strh r0,[fp,-0x1]
8e001c06:	0392      	gid
8e001c08:	051f 0402 	movfs r0,imask
8e001c0c:	1cbc 0500 	strh r0,[fp,-0x1]
8e001c10:	1fcb 0032 	mov r0,0x3fe
8e001c14:	050f 0402 	movts imask,r0
8e001c18:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001c1c:	4033      	sub r2,r0,0
8e001c1e:	0410      	bne 8e001c26 <bjk_wait_sync+0x8a>
8e001c20:	1543      	mov r0,0xaa
8e001c22:	1ddc 0500 	str r0,[fp,-0x3]
8e001c26:	060b 01c2 	mov r0,0x1c30
8e001c2a:	000b 1002 	movt r0,0x0
8e001c2e:	0044      	ldr r0,[r0]
8e001c30:	3dcc 0500 	ldr r1,[fp,-0x3]
8e001c34:	2716      	lsl r1,r1,0x18
8e001c36:	2706      	lsr r1,r1,0x18
8e001c38:	2394      	strb r1,[r0,0x7]
8e001c3a:	01a2      	nop
8e001c3c:	060b 01c2 	mov r0,0x1c30
8e001c40:	000b 1002 	movt r0,0x0
8e001c44:	0044      	ldr r0,[r0]
8e001c46:	0384      	ldrb r0,[r0,0x7]
8e001c48:	20e2      	mov r1,r0
8e001c4a:	1dcc 0500 	ldr r0,[fp,-0x3]
8e001c4e:	443a      	sub r2,r1,r0
8e001c50:	f610      	bne 8e001c3c <bjk_wait_sync+0xa0>
8e001c52:	0192      	gie
8e001c54:	080b 01c2 	mov r0,0x1c40
8e001c58:	000b 1002 	movt r0,0x0
8e001c5c:	3feb 0ff2 	mov r1,0xffff
8e001c60:	2014      	strb r1,[r0]
8e001c62:	02e0      	b 8e001c66 <bjk_wait_sync+0xca>
8e001c64:	01b2      	idle
8e001c66:	080b 01c2 	mov r0,0x1c40
8e001c6a:	000b 1002 	movt r0,0x0
8e001c6e:	0004      	ldrb r0,[r0]
8e001c70:	2033      	sub r1,r0,0
8e001c72:	f910      	bne 8e001c64 <bjk_wait_sync+0xc8>
8e001c74:	0392      	gid
8e001c76:	1cac 0500 	ldrh r0,[fp,-0x1]
8e001c7a:	050f 0402 	movts imask,r0
8e001c7e:	060b 01c2 	mov r0,0x1c30
8e001c82:	000b 1002 	movt r0,0x0
8e001c86:	0044      	ldr r0,[r0]
8e001c88:	2003      	mov r1,0x0
8e001c8a:	2394      	strb r1,[r0,0x7]
8e001c8c:	01a2      	nop
8e001c8e:	060b 01c2 	mov r0,0x1c30
8e001c92:	000b 1002 	movt r0,0x0
8e001c96:	0044      	ldr r0,[r0]
8e001c98:	0384      	ldrb r0,[r0,0x7]
8e001c9a:	4033      	sub r2,r0,0
8e001c9c:	f910      	bne 8e001c8e <bjk_wait_sync+0xf2>
8e001c9e:	0192      	gie
8e001ca0:	01a2      	nop
8e001ca2:	d66c 2400 	ldrd lr,[sp,+0x4]
8e001ca6:	b41b 2404 	add sp,sp,32
8e001caa:	194f 0402 	rts
8e001cae:	01a2      	nop

8e001cb0 <find_call>:
8e001cb0:	f75c 2700 	str fp,[sp],-0x6
8e001cb4:	f4ef 2402 	mov fp,sp
8e001cb8:	1ddc 0400 	str r0,[fp,+0x3]
8e001cbc:	3d5c 0400 	str r1,[fp,+0x2]
8e001cc0:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001cc4:	1edc 0400 	str r0,[fp,+0x5]
8e001cc8:	1b0b 01b2 	mov r0,0x1bd8
8e001ccc:	000b 1002 	movt r0,0x0
8e001cd0:	2003      	mov r1,0x0
8e001cd2:	2034      	strh r1,[r0]
8e001cd4:	39e0      	b 8e001d46 <find_call+0x96>
8e001cd6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001cda:	2024      	ldrh r1,[r0]
8e001cdc:	1d4c 0400 	ldr r0,[fp,+0x2]
8e001ce0:	0024      	ldrh r0,[r0]
8e001ce2:	443a      	sub r2,r1,r0
8e001ce4:	1310      	bne 8e001d0a <find_call+0x5a>
8e001ce6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001cea:	0113      	add r0,r0,2
8e001cec:	2024      	ldrh r1,[r0]
8e001cee:	1d4c 0400 	ldr r0,[fp,+0x2]
8e001cf2:	0113      	add r0,r0,2
8e001cf4:	0024      	ldrh r0,[r0]
8e001cf6:	443a      	sub r2,r1,r0
8e001cf8:	0910      	bne 8e001d0a <find_call+0x5a>
8e001cfa:	1b0b 01b2 	mov r0,0x1bd8
8e001cfe:	000b 1002 	movt r0,0x0
8e001d02:	3dcb 01e2 	mov r1,0x1eee
8e001d06:	2034      	strh r1,[r0]
8e001d08:	23e0      	b 8e001d4e <find_call+0x9e>
8e001d0a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d0e:	2024      	ldrh r1,[r0]
8e001d10:	09eb 0192 	mov r0,0x194f
8e001d14:	443a      	sub r2,r1,r0
8e001d16:	1310      	bne 8e001d3c <find_call+0x8c>
8e001d18:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d1c:	0113      	add r0,r0,2
8e001d1e:	2024      	ldrh r1,[r0]
8e001d20:	004b 0042 	mov r0,0x402
8e001d24:	443a      	sub r2,r1,r0
8e001d26:	0b10      	bne 8e001d3c <find_call+0x8c>
8e001d28:	1b0b 01b2 	mov r0,0x1bd8
8e001d2c:	000b 1002 	movt r0,0x0
8e001d30:	2223      	mov r1,0x11
8e001d32:	2034      	strh r1,[r0]
8e001d34:	0003      	mov r0,0x0
8e001d36:	1edc 0400 	str r0,[fp,+0x5]
8e001d3a:	0ae0      	b 8e001d4e <find_call+0x9e>
8e001d3c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d40:	0313      	add r0,r0,-2
8e001d42:	1edc 0400 	str r0,[fp,+0x5]
8e001d46:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d4a:	2033      	sub r1,r0,0
8e001d4c:	c510      	bne 8e001cd6 <find_call+0x26>
8e001d4e:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d52:	f74c 2400 	ldr fp,[sp,+0x6]
8e001d56:	b41b 2403 	add sp,sp,24
8e001d5a:	194f 0402 	rts
8e001d5e:	01a2      	nop

8e001d60 <find_interrupt_call>:
8e001d60:	f75c 2700 	str fp,[sp],-0x6
8e001d64:	f4ef 2402 	mov fp,sp
8e001d68:	1ddc 0400 	str r0,[fp,+0x3]
8e001d6c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001d70:	1edc 0400 	str r0,[fp,+0x5]
8e001d74:	1b0b 01b2 	mov r0,0x1bd8
8e001d78:	000b 1002 	movt r0,0x0
8e001d7c:	2003      	mov r1,0x0
8e001d7e:	2034      	strh r1,[r0]
8e001d80:	51e0      	b 8e001e22 <find_interrupt_call+0xc2>
8e001d82:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d86:	2024      	ldrh r1,[r0]
8e001d88:	1f8b 0142 	mov r0,0x14fc
8e001d8c:	443a      	sub r2,r1,r0
8e001d8e:	2c10      	bne 8e001de6 <find_interrupt_call+0x86>
8e001d90:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001d94:	0113      	add r0,r0,2
8e001d96:	2024      	ldrh r1,[r0]
8e001d98:	000b 0052 	mov r0,0x500
8e001d9c:	443a      	sub r2,r1,r0
8e001d9e:	2410      	bne 8e001de6 <find_interrupt_call+0x86>
8e001da0:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001da4:	021b 0000 	add r0,r0,4
8e001da8:	2024      	ldrh r1,[r0]
8e001daa:	024b 0052 	mov r0,0x512
8e001dae:	443a      	sub r2,r1,r0
8e001db0:	1b10      	bne 8e001de6 <find_interrupt_call+0x86>
8e001db2:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001db6:	031b 0000 	add r0,r0,6
8e001dba:	2024      	ldrh r1,[r0]
8e001dbc:	03eb 0212 	mov r0,0x211f
8e001dc0:	443a      	sub r2,r1,r0
8e001dc2:	1210      	bne 8e001de6 <find_interrupt_call+0x86>
8e001dc4:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001dc8:	001b 0001 	add r0,r0,8
8e001dcc:	2024      	ldrh r1,[r0]
8e001dce:	004b 0042 	mov r0,0x402
8e001dd2:	443a      	sub r2,r1,r0
8e001dd4:	0910      	bne 8e001de6 <find_interrupt_call+0x86>
8e001dd6:	1b0b 01b2 	mov r0,0x1bd8
8e001dda:	000b 1002 	movt r0,0x0
8e001dde:	3dcb 02e2 	mov r1,0x2eee
8e001de2:	2034      	strh r1,[r0]
8e001de4:	23e0      	b 8e001e2a <find_interrupt_call+0xca>
8e001de6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001dea:	2024      	ldrh r1,[r0]
8e001dec:	09eb 0192 	mov r0,0x194f
8e001df0:	443a      	sub r2,r1,r0
8e001df2:	1310      	bne 8e001e18 <find_interrupt_call+0xb8>
8e001df4:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001df8:	0113      	add r0,r0,2
8e001dfa:	2024      	ldrh r1,[r0]
8e001dfc:	004b 0042 	mov r0,0x402
8e001e00:	443a      	sub r2,r1,r0
8e001e02:	0b10      	bne 8e001e18 <find_interrupt_call+0xb8>
8e001e04:	1b0b 01b2 	mov r0,0x1bd8
8e001e08:	000b 1002 	movt r0,0x0
8e001e0c:	2423      	mov r1,0x21
8e001e0e:	2034      	strh r1,[r0]
8e001e10:	0003      	mov r0,0x0
8e001e12:	1edc 0400 	str r0,[fp,+0x5]
8e001e16:	0ae0      	b 8e001e2a <find_interrupt_call+0xca>
8e001e18:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001e1c:	0313      	add r0,r0,-2
8e001e1e:	1edc 0400 	str r0,[fp,+0x5]
8e001e22:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001e26:	2033      	sub r1,r0,0
8e001e28:	ad10      	bne 8e001d82 <find_interrupt_call+0x22>
8e001e2a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001e2e:	f74c 2400 	ldr fp,[sp,+0x6]
8e001e32:	b41b 2403 	add sp,sp,24
8e001e36:	194f 0402 	rts
8e001e3a:	01a2      	nop

8e001e3c <find_rts>:
8e001e3c:	f75c 2700 	str fp,[sp],-0x6
8e001e40:	f4ef 2402 	mov fp,sp
8e001e44:	1ddc 0400 	str r0,[fp,+0x3]
8e001e48:	3dcc 0400 	ldr r1,[fp,+0x3]
8e001e4c:	000b 0802 	mov r0,0x8000
8e001e50:	041a      	add r0,r1,r0
8e001e52:	1e5c 0400 	str r0,[fp,+0x4]
8e001e56:	1b0b 01b2 	mov r0,0x1bd8
8e001e5a:	000b 1002 	movt r0,0x0
8e001e5e:	2003      	mov r1,0x0
8e001e60:	2034      	strh r1,[r0]
8e001e62:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001e66:	1edc 0400 	str r0,[fp,+0x5]
8e001e6a:	49e0      	b 8e001efc <find_rts+0xc0>
8e001e6c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001e70:	2024      	ldrh r1,[r0]
8e001e72:	09eb 0192 	mov r0,0x194f
8e001e76:	443a      	sub r2,r1,r0
8e001e78:	1110      	bne 8e001e9a <find_rts+0x5e>
8e001e7a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001e7e:	0113      	add r0,r0,2
8e001e80:	2024      	ldrh r1,[r0]
8e001e82:	004b 0042 	mov r0,0x402
8e001e86:	443a      	sub r2,r1,r0
8e001e88:	0910      	bne 8e001e9a <find_rts+0x5e>
8e001e8a:	1b0b 01b2 	mov r0,0x1bd8
8e001e8e:	000b 1002 	movt r0,0x0
8e001e92:	3dcb 04e2 	mov r1,0x4eee
8e001e96:	2034      	strh r1,[r0]
8e001e98:	38e0      	b 8e001f08 <find_rts+0xcc>
8e001e9a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001e9e:	0024      	ldrh r0,[r0]
8e001ea0:	213b 003a 	sub r1,r0,466
8e001ea4:	2710      	bne 8e001ef2 <find_rts+0xb6>
8e001ea6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001eaa:	031b 00fe 	add r0,r0,-10
8e001eae:	2024      	ldrh r1,[r0]
8e001eb0:	004b 0052 	mov r0,0x502
8e001eb4:	443a      	sub r2,r1,r0
8e001eb6:	1e10      	bne 8e001ef2 <find_rts+0xb6>
8e001eb8:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001ebc:	001b 00ff 	add r0,r0,-8
8e001ec0:	2024      	ldrh r1,[r0]
8e001ec2:	01eb 0212 	mov r0,0x210f
8e001ec6:	443a      	sub r2,r1,r0
8e001ec8:	1510      	bne 8e001ef2 <find_rts+0xb6>
8e001eca:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001ece:	011b 00ff 	add r0,r0,-6
8e001ed2:	2024      	ldrh r1,[r0]
8e001ed4:	004b 0042 	mov r0,0x402
8e001ed8:	443a      	sub r2,r1,r0
8e001eda:	0c10      	bne 8e001ef2 <find_rts+0xb6>
8e001edc:	1b0b 01b2 	mov r0,0x1bd8
8e001ee0:	000b 1002 	movt r0,0x0
8e001ee4:	2823      	mov r1,0x41
8e001ee6:	2034      	strh r1,[r0]
8e001ee8:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001eec:	1edc 0400 	str r0,[fp,+0x5]
8e001ef0:	0ce0      	b 8e001f08 <find_rts+0xcc>
8e001ef2:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001ef6:	0113      	add r0,r0,2
8e001ef8:	1edc 0400 	str r0,[fp,+0x5]
8e001efc:	3ecc 0400 	ldr r1,[fp,+0x5]
8e001f00:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001f04:	443a      	sub r2,r1,r0
8e001f06:	b350      	bltu 8e001e6c <find_rts+0x30>
8e001f08:	1b0b 01b2 	mov r0,0x1bd8
8e001f0c:	000b 1002 	movt r0,0x0
8e001f10:	0024      	ldrh r0,[r0]
8e001f12:	20bb 0008 	sub r1,r0,65
8e001f16:	0310      	bne 8e001f1c <find_rts+0xe0>
8e001f18:	0003      	mov r0,0x0
8e001f1a:	21e0      	b 8e001f5c <find_rts+0x120>
8e001f1c:	3ecc 0400 	ldr r1,[fp,+0x5]
8e001f20:	1e4c 0400 	ldr r0,[fp,+0x4]
8e001f24:	443a      	sub r2,r1,r0
8e001f26:	0910      	bne 8e001f38 <find_rts+0xfc>
8e001f28:	1b0b 01b2 	mov r0,0x1bd8
8e001f2c:	000b 1002 	movt r0,0x0
8e001f30:	2843      	mov r1,0x42
8e001f32:	2034      	strh r1,[r0]
8e001f34:	0003      	mov r0,0x0
8e001f36:	13e0      	b 8e001f5c <find_rts+0x120>
8e001f38:	3ecc 0400 	ldr r1,[fp,+0x5]
8e001f3c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001f40:	043a      	sub r0,r1,r0
8e001f42:	002e      	asr r0,r0,0x1
8e001f44:	20b3      	sub r1,r0,1
8e001f46:	0920      	bgtu 8e001f58 <find_rts+0x11c>
8e001f48:	1b0b 01b2 	mov r0,0x1bd8
8e001f4c:	000b 1002 	movt r0,0x0
8e001f50:	2863      	mov r1,0x43
8e001f52:	2034      	strh r1,[r0]
8e001f54:	0003      	mov r0,0x0
8e001f56:	03e0      	b 8e001f5c <find_rts+0x120>
8e001f58:	1ecc 0400 	ldr r0,[fp,+0x5]
8e001f5c:	f74c 2400 	ldr fp,[sp,+0x6]
8e001f60:	b41b 2403 	add sp,sp,24
8e001f64:	194f 0402 	rts

8e001f68 <get_sp_disp>:
8e001f68:	f55c 2701 	str fp,[sp],-0xa
8e001f6c:	f4ef 2402 	mov fp,sp
8e001f70:	1ddc 0400 	str r0,[fp,+0x3]
8e001f74:	1dcc 0400 	ldr r0,[fp,+0x3]
8e001f78:	1cdc 0401 	str r0,[fp,+0x9]
8e001f7c:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001f80:	0213      	add r0,r0,-4
8e001f82:	1cdc 0401 	str r0,[fp,+0x9]
8e001f86:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001f8a:	0024      	ldrh r0,[r0]
8e001f8c:	1cbc 0402 	strh r0,[fp,+0x11]
8e001f90:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001f94:	00a4      	ldrh r0,[r0,0x1]
8e001f96:	1c3c 0402 	strh r0,[fp,+0x10]
8e001f9a:	1b0b 01b2 	mov r0,0x1bd8
8e001f9e:	000b 1002 	movt r0,0x0
8e001fa2:	2003      	mov r1,0x0
8e001fa4:	2034      	strh r1,[r0]
8e001fa6:	3cac 0402 	ldrh r1,[fp,+0x11]
8e001faa:	01eb 0f02 	mov r0,0xf00f
8e001fae:	245a      	and r1,r1,r0
8e001fb0:	016b 0b02 	mov r0,0xb00b
8e001fb4:	443a      	sub r2,r1,r0
8e001fb6:	0a00      	beq 8e001fca <get_sp_disp+0x62>
8e001fb8:	1b0b 01b2 	mov r0,0x1bd8
8e001fbc:	000b 1002 	movt r0,0x0
8e001fc0:	2623      	mov r1,0x31
8e001fc2:	2034      	strh r1,[r0]
8e001fc4:	0003      	mov r0,0x0
8e001fc6:	98e8 0000 	b 8e0020f6 <get_sp_disp+0x18e>
8e001fca:	3c2c 0402 	ldrh r1,[fp,+0x10]
8e001fce:	000b 0ff2 	mov r0,0xff00
8e001fd2:	245a      	and r1,r1,r0
8e001fd4:	000b 0242 	mov r0,0x2400
8e001fd8:	443a      	sub r2,r1,r0
8e001fda:	0a00      	beq 8e001fee <get_sp_disp+0x86>
8e001fdc:	1b0b 01b2 	mov r0,0x1bd8
8e001fe0:	000b 1002 	movt r0,0x0
8e001fe4:	2643      	mov r1,0x32
8e001fe6:	2034      	strh r1,[r0]
8e001fe8:	0003      	mov r0,0x0
8e001fea:	86e8 0000 	b 8e0020f6 <get_sp_disp+0x18e>
8e001fee:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001ff2:	1fdc 0400 	str r0,[fp,+0x7]
8e001ff6:	1ccc 0401 	ldr r0,[fp,+0x9]
8e001ffa:	0213      	add r0,r0,-4
8e001ffc:	1cdc 0401 	str r0,[fp,+0x9]
8e002000:	1ccc 0401 	ldr r0,[fp,+0x9]
8e002004:	0024      	ldrh r0,[r0]
8e002006:	1cbc 0402 	strh r0,[fp,+0x11]
8e00200a:	1ccc 0401 	ldr r0,[fp,+0x9]
8e00200e:	00a4      	ldrh r0,[r0,0x1]
8e002010:	1c3c 0402 	strh r0,[fp,+0x10]
8e002014:	3cac 0402 	ldrh r1,[fp,+0x11]
8e002018:	01eb 0f02 	mov r0,0xf00f
8e00201c:	245a      	and r1,r1,r0
8e00201e:	018b 0d02 	mov r0,0xd00c
8e002022:	443a      	sub r2,r1,r0
8e002024:	0900      	beq 8e002036 <get_sp_disp+0xce>
8e002026:	1b0b 01b2 	mov r0,0x1bd8
8e00202a:	000b 1002 	movt r0,0x0
8e00202e:	2663      	mov r1,0x33
8e002030:	2034      	strh r1,[r0]
8e002032:	0003      	mov r0,0x0
8e002034:	61e0      	b 8e0020f6 <get_sp_disp+0x18e>
8e002036:	3c2c 0402 	ldrh r1,[fp,+0x10]
8e00203a:	000b 0f02 	mov r0,0xf000
8e00203e:	245a      	and r1,r1,r0
8e002040:	000b 0202 	mov r0,0x2000
8e002044:	443a      	sub r2,r1,r0
8e002046:	0900      	beq 8e002058 <get_sp_disp+0xf0>
8e002048:	1b0b 01b2 	mov r0,0x1bd8
8e00204c:	000b 1002 	movt r0,0x0
8e002050:	2683      	mov r1,0x34
8e002052:	2034      	strh r1,[r0]
8e002054:	0003      	mov r0,0x0
8e002056:	50e0      	b 8e0020f6 <get_sp_disp+0x18e>
8e002058:	1fcc 0400 	ldr r0,[fp,+0x7]
8e00205c:	1edc 0400 	str r0,[fp,+0x5]
8e002060:	0003      	mov r0,0x0
8e002062:	1cbc 0401 	strh r0,[fp,+0x9]
8e002066:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00206a:	0113      	add r0,r0,2
8e00206c:	0024      	ldrh r0,[r0]
8e00206e:	20e2      	mov r1,r0
8e002070:	1fe3      	mov r0,0xff
8e002072:	045a      	and r0,r1,r0
8e002074:	0076      	lsl r0,r0,0x3
8e002076:	20e2      	mov r1,r0
8e002078:	200b 1002 	movt r1,0x0
8e00207c:	1ecc 0400 	ldr r0,[fp,+0x5]
8e002080:	0024      	ldrh r0,[r0]
8e002082:	40e2      	mov r2,r0
8e002084:	100b 0032 	mov r0,0x380
8e002088:	085a      	and r0,r2,r0
8e00208a:	00ee      	asr r0,r0,0x7
8e00208c:	000b 1002 	movt r0,0x0
8e002090:	047a      	orr r0,r1,r0
8e002092:	000b 1002 	movt r0,0x0
8e002096:	1cbc 0401 	strh r0,[fp,+0x9]
8e00209a:	1d1b 0402 	add r0,fp,18
8e00209e:	0093      	add r0,r0,1
8e0020a0:	0004      	ldrb r0,[r0]
8e0020a2:	0046      	lsr r0,r0,0x2
8e0020a4:	0316      	lsl r0,r0,0x18
8e0020a6:	0306      	lsr r0,r0,0x18
8e0020a8:	20e2      	mov r1,r0
8e0020aa:	0023      	mov r0,0x1
8e0020ac:	045a      	and r0,r1,r0
8e0020ae:	2033      	sub r1,r0,0
8e0020b0:	1000      	beq 8e0020d0 <get_sp_disp+0x168>
8e0020b2:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0020b6:	20e2      	mov r1,r0
8e0020b8:	200b 1002 	movt r1,0x0
8e0020bc:	000b 0f82 	mov r0,0xf800
8e0020c0:	1feb 1ff2 	movt r0,0xffff
8e0020c4:	040a      	eor r0,r1,r0
8e0020c6:	000b 1002 	movt r0,0x0
8e0020ca:	000b 1002 	movt r0,0x0
8e0020ce:	03e0      	b 8e0020d4 <get_sp_disp+0x16c>
8e0020d0:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0020d4:	1cbc 0401 	strh r0,[fp,+0x9]
8e0020d8:	1cac 0401 	ldrh r0,[fp,+0x9]
8e0020dc:	000b 1002 	movt r0,0x0
8e0020e0:	1ebc 0401 	strh r0,[fp,+0xd]
8e0020e4:	1b0b 01b2 	mov r0,0x1bd8
8e0020e8:	000b 1002 	movt r0,0x0
8e0020ec:	3dcb 03e2 	mov r1,0x3eee
8e0020f0:	2034      	strh r1,[r0]
8e0020f2:	1eac 0401 	ldrh r0,[fp,+0xd]
8e0020f6:	0216      	lsl r0,r0,0x10
8e0020f8:	020e      	asr r0,r0,0x10
8e0020fa:	f54c 2401 	ldr fp,[sp,+0xa]
8e0020fe:	b41b 2405 	add sp,sp,40
8e002102:	194f 0402 	rts
8e002106:	01a2      	nop

8e002108 <a64_malloc>:
8e002108:	000b 1002 	movt r0,0x0
8e00210c:	20e3      	mov r1,0x7
8e00210e:	d4fc 2700 	strd lr,[sp],-0x1
8e002112:	20da      	and r1,r0,r1
8e002114:	0a00      	beq 8e002128 <a64_malloc+0x20>
8e002116:	3f0b 0ff2 	mov r1,0xfff8
8e00211a:	3feb 1ff2 	movt r1,0xffff
8e00211e:	00da      	and r0,r0,r1
8e002120:	001b 0001 	add r0,r0,8
8e002124:	000b 1002 	movt r0,0x0
8e002128:	2e0b 0022 	mov r1,0x270
8e00212c:	200b 18e2 	movt r1,0x8e00
8e002130:	0552      	jalr r1
8e002132:	221b 0000 	add r1,r0,4
8e002136:	4033      	sub r2,r0,0
8e002138:	0412      	movne r0,r1
8e00213a:	b41b 2401 	add sp,sp,8
8e00213e:	d46c 2400 	ldrd lr,[sp,+0x0]
8e002142:	194f 0402 	rts
8e002146:	01a2      	nop

8e002148 <a64_realloc>:
8e002148:	200b 1002 	movt r1,0x0
8e00214c:	40e3      	mov r2,0x7
8e00214e:	d4fc 2700 	strd lr,[sp],-0x1
8e002152:	455a      	and r2,r1,r2
8e002154:	0a00      	beq 8e002168 <a64_realloc+0x20>
8e002156:	5f0b 0ff2 	mov r2,0xfff8
8e00215a:	5feb 1ff2 	movt r2,0xffff
8e00215e:	255a      	and r1,r1,r2
8e002160:	241b 0001 	add r1,r1,8
8e002164:	200b 1002 	movt r1,0x0
8e002168:	4033      	sub r2,r0,0
8e00216a:	0300      	beq 8e002170 <a64_realloc+0x28>
8e00216c:	0213      	add r0,r0,-4
8e00216e:	02e0      	b 8e002172 <a64_realloc+0x2a>
8e002170:	0003      	mov r0,0x0
8e002172:	558b 0032 	mov r2,0x3ac
8e002176:	400b 18e2 	movt r2,0x8e00
8e00217a:	0952      	jalr r2
8e00217c:	221b 0000 	add r1,r0,4
8e002180:	6033      	sub r3,r0,0
8e002182:	0412      	movne r0,r1
8e002184:	b41b 2401 	add sp,sp,8
8e002188:	d46c 2400 	ldrd lr,[sp,+0x0]
8e00218c:	194f 0402 	rts

8e002190 <a64_free>:
8e002190:	965c 0700 	str r4,[sp],-0x4
8e002194:	d6dc 2400 	str lr,[sp,+0x5]
8e002198:	f5dc 2400 	str fp,[sp,+0x3]
8e00219c:	80e2      	mov r4,r0
8e00219e:	0044      	ldr r0,[r0]
8e0021a0:	2033      	sub r1,r0,0
8e0021a2:	0900      	beq 8e0021b4 <a64_free+0x24>
8e0021a4:	280b 0052 	mov r1,0x540
8e0021a8:	0213      	add r0,r0,-4
8e0021aa:	200b 18e2 	movt r1,0x8e00
8e0021ae:	0552      	jalr r1
8e0021b0:	0003      	mov r0,0x0
8e0021b2:	1054      	str r0,[r4]
8e0021b4:	d6cc 2400 	ldr lr,[sp,+0x5]
8e0021b8:	964c 0400 	ldr r4,[sp,+0x4]
8e0021bc:	f5cc 2400 	ldr fp,[sp,+0x3]
8e0021c0:	b41b 2402 	add sp,sp,16
8e0021c4:	194f 0402 	rts

8e0021c8 <init_cpp_main>:
8e0021c8:	d67c 2700 	strd lr,[sp],-0x4
8e0021cc:	f41b 2404 	add fp,sp,32
8e0021d0:	1b8b 0182 	mov r0,0x18dc
8e0021d4:	000b 1002 	movt r0,0x0
8e0021d8:	20e2      	mov r1,r0
8e0021da:	0083      	mov r0,0x4
8e0021dc:	4d8b 0122 	mov r2,0x126c
8e0021e0:	400b 1002 	movt r2,0x0
8e0021e4:	0952      	jalr r2
8e0021e6:	2033      	sub r1,r0,0
8e0021e8:	0600      	beq 8e0021f4 <init_cpp_main+0x2c>
8e0021ea:	318b 0122 	mov r1,0x128c
8e0021ee:	200b 1002 	movt r1,0x0
8e0021f2:	0552      	jalr r1
8e0021f4:	1c0b 0182 	mov r0,0x18e0
8e0021f8:	000b 1002 	movt r0,0x0
8e0021fc:	20e2      	mov r1,r0
8e0021fe:	0083      	mov r0,0x4
8e002200:	4d8b 0122 	mov r2,0x126c
8e002204:	400b 1002 	movt r2,0x0
8e002208:	0952      	jalr r2
8e00220a:	2033      	sub r1,r0,0
8e00220c:	0600      	beq 8e002218 <init_cpp_main+0x50>
8e00220e:	318b 0122 	mov r1,0x128c
8e002212:	200b 1002 	movt r1,0x0
8e002216:	0552      	jalr r1
8e002218:	1c8b 0182 	mov r0,0x18e4
8e00221c:	000b 1002 	movt r0,0x0
8e002220:	20e2      	mov r1,r0
8e002222:	0083      	mov r0,0x4
8e002224:	4d8b 0122 	mov r2,0x126c
8e002228:	400b 1002 	movt r2,0x0
8e00222c:	0952      	jalr r2
8e00222e:	2033      	sub r1,r0,0
8e002230:	0600      	beq 8e00223c <init_cpp_main+0x74>
8e002232:	318b 0122 	mov r1,0x128c
8e002236:	200b 1002 	movt r1,0x0
8e00223a:	0552      	jalr r1
8e00223c:	0003      	mov r0,0x0
8e00223e:	1cdc 0500 	str r0,[fp,-0x1]
8e002242:	1ccc 0500 	ldr r0,[fp,-0x1]
8e002246:	223b 0000 	sub r1,r0,4
8e00224a:	1160      	bgt 8e00226c <init_cpp_main+0xa4>
8e00224c:	3e0b 0182 	mov r1,0x18f0
8e002250:	200b 1002 	movt r1,0x0
8e002254:	1ccc 0500 	ldr r0,[fp,-0x1]
8e002258:	0056      	lsl r0,r0,0x2
8e00225a:	041a      	add r0,r1,r0
8e00225c:	2003      	mov r1,0x0
8e00225e:	2054      	str r1,[r0]
8e002260:	1ccc 0500 	ldr r0,[fp,-0x1]
8e002264:	0093      	add r0,r0,1
8e002266:	1cdc 0500 	str r0,[fp,-0x1]
8e00226a:	ece0      	b 8e002242 <init_cpp_main+0x7a>
8e00226c:	0003      	mov r0,0x0
8e00226e:	1d5c 0500 	str r0,[fp,-0x2]
8e002272:	1d4c 0500 	ldr r0,[fp,-0x2]
8e002276:	20b3      	sub r1,r0,1
8e002278:	1160      	bgt 8e00229a <init_cpp_main+0xd2>
8e00227a:	210b 0192 	mov r1,0x1908
8e00227e:	200b 1002 	movt r1,0x0
8e002282:	1d4c 0500 	ldr r0,[fp,-0x2]
8e002286:	0056      	lsl r0,r0,0x2
8e002288:	041a      	add r0,r1,r0
8e00228a:	2003      	mov r1,0x0
8e00228c:	2054      	str r1,[r0]
8e00228e:	1d4c 0500 	ldr r0,[fp,-0x2]
8e002292:	0093      	add r0,r0,1
8e002294:	1d5c 0500 	str r0,[fp,-0x2]
8e002298:	ede0      	b 8e002272 <init_cpp_main+0xaa>
8e00229a:	0003      	mov r0,0x0
8e00229c:	1ddc 0500 	str r0,[fp,-0x3]
8e0022a0:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0022a4:	23bb 0001 	sub r1,r0,15
8e0022a8:	1160      	bgt 8e0022ca <init_cpp_main+0x102>
8e0022aa:	220b 0192 	mov r1,0x1910
8e0022ae:	200b 1002 	movt r1,0x0
8e0022b2:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0022b6:	0056      	lsl r0,r0,0x2
8e0022b8:	041a      	add r0,r1,r0
8e0022ba:	2003      	mov r1,0x0
8e0022bc:	2054      	str r1,[r0]
8e0022be:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0022c2:	0093      	add r0,r0,1
8e0022c4:	1ddc 0500 	str r0,[fp,-0x3]
8e0022c8:	ece0      	b 8e0022a0 <init_cpp_main+0xd8>
8e0022ca:	0003      	mov r0,0x0
8e0022cc:	1e5c 0500 	str r0,[fp,-0x4]
8e0022d0:	1e4c 0500 	ldr r0,[fp,-0x4]
8e0022d4:	23bb 0001 	sub r1,r0,15
8e0022d8:	1960      	bgt 8e00230a <init_cpp_main+0x142>
8e0022da:	3e4c 0500 	ldr r1,[fp,-0x4]
8e0022de:	0a0b 0192 	mov r0,0x1950
8e0022e2:	000b 1002 	movt r0,0x0
8e0022e6:	041a      	add r0,r1,r0
8e0022e8:	20e2      	mov r1,r0
8e0022ea:	0023      	mov r0,0x1
8e0022ec:	4d8b 0122 	mov r2,0x126c
8e0022f0:	400b 1002 	movt r2,0x0
8e0022f4:	0952      	jalr r2
8e0022f6:	2033      	sub r1,r0,0
8e0022f8:	0300      	beq 8e0022fe <init_cpp_main+0x136>
8e0022fa:	2003      	mov r1,0x0
8e0022fc:	2014      	strb r1,[r0]
8e0022fe:	1e4c 0500 	ldr r0,[fp,-0x4]
8e002302:	0093      	add r0,r0,1
8e002304:	1e5c 0500 	str r0,[fp,-0x4]
8e002308:	e4e0      	b 8e0022d0 <init_cpp_main+0x108>
8e00230a:	0c0b 0192 	mov r0,0x1960
8e00230e:	000b 1002 	movt r0,0x0
8e002312:	20e2      	mov r1,r0
8e002314:	0083      	mov r0,0x4
8e002316:	4d8b 0122 	mov r2,0x126c
8e00231a:	400b 1002 	movt r2,0x0
8e00231e:	0952      	jalr r2
8e002320:	2033      	sub r1,r0,0
8e002322:	0600      	beq 8e00232e <init_cpp_main+0x166>
8e002324:	318b 0122 	mov r1,0x128c
8e002328:	200b 1002 	movt r1,0x0
8e00232c:	0552      	jalr r1
8e00232e:	0c8b 0192 	mov r0,0x1964
8e002332:	000b 1002 	movt r0,0x0
8e002336:	20e2      	mov r1,r0
8e002338:	0083      	mov r0,0x4
8e00233a:	4d8b 0122 	mov r2,0x126c
8e00233e:	400b 1002 	movt r2,0x0
8e002342:	0952      	jalr r2
8e002344:	2033      	sub r1,r0,0
8e002346:	0600      	beq 8e002352 <init_cpp_main+0x18a>
8e002348:	318b 0122 	mov r1,0x128c
8e00234c:	200b 1002 	movt r1,0x0
8e002350:	0552      	jalr r1
8e002352:	0d0b 0192 	mov r0,0x1968
8e002356:	000b 1002 	movt r0,0x0
8e00235a:	20e2      	mov r1,r0
8e00235c:	0083      	mov r0,0x4
8e00235e:	4d8b 0122 	mov r2,0x126c
8e002362:	400b 1002 	movt r2,0x0
8e002366:	0952      	jalr r2
8e002368:	2033      	sub r1,r0,0
8e00236a:	0600      	beq 8e002376 <init_cpp_main+0x1ae>
8e00236c:	318b 0122 	mov r1,0x128c
8e002370:	200b 1002 	movt r1,0x0
8e002374:	0552      	jalr r1
8e002376:	0d8b 0192 	mov r0,0x196c
8e00237a:	000b 1002 	movt r0,0x0
8e00237e:	20e2      	mov r1,r0
8e002380:	0083      	mov r0,0x4
8e002382:	4d8b 0122 	mov r2,0x126c
8e002386:	400b 1002 	movt r2,0x0
8e00238a:	0952      	jalr r2
8e00238c:	2033      	sub r1,r0,0
8e00238e:	0600      	beq 8e00239a <init_cpp_main+0x1d2>
8e002390:	318b 0122 	mov r1,0x128c
8e002394:	200b 1002 	movt r1,0x0
8e002398:	0552      	jalr r1
8e00239a:	2083      	mov r1,0x4
8e00239c:	1c0b 01b2 	mov r0,0x1be0
8e0023a0:	000b 1002 	movt r0,0x0
8e0023a4:	209c 0003 	strb r1,[r0,+0x19]
8e0023a8:	2103      	mov r1,0x8
8e0023aa:	1c0b 01b2 	mov r0,0x1be0
8e0023ae:	000b 1002 	movt r0,0x0
8e0023b2:	211c 0003 	strb r1,[r0,+0x1a]
8e0023b6:	2203      	mov r1,0x10
8e0023b8:	1c0b 01b2 	mov r0,0x1be0
8e0023bc:	000b 1002 	movt r0,0x0
8e0023c0:	219c 0003 	strb r1,[r0,+0x1b]
8e0023c4:	2303      	mov r1,0x18
8e0023c6:	1c0b 01b2 	mov r0,0x1be0
8e0023ca:	000b 1002 	movt r0,0x0
8e0023ce:	221c 0003 	strb r1,[r0,+0x1c]
8e0023d2:	2303      	mov r1,0x18
8e0023d4:	1c0b 01b2 	mov r0,0x1be0
8e0023d8:	000b 1002 	movt r0,0x0
8e0023dc:	229c 0003 	strb r1,[r0,+0x1d]
8e0023e0:	1e0b 0252 	mov r0,0x25f0
8e0023e4:	000b 18e2 	movt r0,0x8e00
8e0023e8:	0152      	jalr r0
8e0023ea:	0203      	mov r0,0x10
8e0023ec:	370b 00a2 	mov r1,0xab8
8e0023f0:	200b 1002 	movt r1,0x0
8e0023f4:	0552      	jalr r1
8e0023f6:	1f5c 0500 	str r0,[fp,-0x6]
8e0023fa:	0003      	mov r0,0x0
8e0023fc:	1edc 0500 	str r0,[fp,-0x5]
8e002400:	1ecc 0500 	ldr r0,[fp,-0x5]
8e002404:	23bb 0001 	sub r1,r0,15
8e002408:	2a60      	bgt 8e00245c <init_cpp_main+0x294>
8e00240a:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00240e:	0076      	lsl r0,r0,0x3
8e002410:	2056      	lsl r1,r0,0x2
8e002412:	043a      	sub r0,r1,r0
8e002414:	3f4c 0500 	ldr r1,[fp,-0x6]
8e002418:	041a      	add r0,r1,r0
8e00241a:	021b 0000 	add r0,r0,4
8e00241e:	358b 0132 	mov r1,0x13ac
8e002422:	200b 1002 	movt r1,0x0
8e002426:	0552      	jalr r1
8e002428:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00242c:	0076      	lsl r0,r0,0x3
8e00242e:	2056      	lsl r1,r0,0x2
8e002430:	043a      	sub r0,r1,r0
8e002432:	3f4c 0500 	ldr r1,[fp,-0x6]
8e002436:	041a      	add r0,r1,r0
8e002438:	021b 0000 	add r0,r0,4
8e00243c:	20e2      	mov r1,r0
8e00243e:	1d0b 0182 	mov r0,0x18e8
8e002442:	000b 1002 	movt r0,0x0
8e002446:	488b 0142 	mov r2,0x1444
8e00244a:	400b 1002 	movt r2,0x0
8e00244e:	0952      	jalr r2
8e002450:	1ecc 0500 	ldr r0,[fp,-0x5]
8e002454:	0093      	add r0,r0,1
8e002456:	1edc 0500 	str r0,[fp,-0x5]
8e00245a:	d3e0      	b 8e002400 <init_cpp_main+0x238>
8e00245c:	0003      	mov r0,0x0
8e00245e:	050f 0402 	movts imask,r0
8e002462:	0192      	gie
8e002464:	01a2      	nop
8e002466:	d66c 2400 	ldrd lr,[sp,+0x4]
8e00246a:	b41b 2404 	add sp,sp,32
8e00246e:	194f 0402 	rts
8e002472:	01a2      	nop

8e002474 <cpp_main>:
8e002474:	957c 0700 	strd r4,[sp],-0x2
8e002478:	190b 0212 	mov r0,0x21c8
8e00247c:	d4fc 2400 	strd lr,[sp,+0x1]
8e002480:	000b 18e2 	movt r0,0x8e00
8e002484:	0152      	jalr r0
8e002486:	078b 0262 	mov r0,0x263c
8e00248a:	000b 18e2 	movt r0,0x8e00
8e00248e:	0152      	jalr r0
8e002490:	1c0b 01b2 	mov r0,0x1be0
8e002494:	000b 1002 	movt r0,0x0
8e002498:	2023      	mov r1,0x1
8e00249a:	201c 0003 	strb r1,[r0,+0x18]
8e00249e:	22c4      	ldr r1,[r0,0x5]
8e0024a0:	80e2      	mov r4,r0
8e0024a2:	4433      	sub r2,r1,0
8e0024a4:	3a10      	bne 8e002518 <cpp_main+0xa4>
8e0024a6:	160b 0172 	mov r0,0x17b0
8e0024aa:	a10b 00d2 	mov r5,0xd08
8e0024ae:	a00b 18e2 	movt r5,0x8e00
8e0024b2:	000b 1002 	movt r0,0x0
8e0024b6:	1552      	jalr r5
8e0024b8:	470b 01c2 	mov r2,0x1c38
8e0024bc:	400b 1002 	movt r2,0x0
8e0024c0:	0824      	ldrh r0,[r2]
8e0024c2:	20d6      	lsl r1,r0,0x6
8e0024c4:	08a4      	ldrh r0,[r2,0x1]
8e0024c6:	0093      	add r0,r0,1
8e0024c8:	041a      	add r0,r1,r0
8e0024ca:	340b 0252 	mov r1,0x25a0
8e0024ce:	000b 1002 	movt r0,0x0
8e0024d2:	200b 18e2 	movt r1,0x8e00
8e0024d6:	0552      	jalr r1
8e0024d8:	190b 0172 	mov r0,0x17c8
8e0024dc:	2003      	mov r1,0x0
8e0024de:	000b 1002 	movt r0,0x0
8e0024e2:	1552      	jalr r5
8e0024e4:	178b 00f2 	mov r0,0xfbc
8e0024e8:	000b 1002 	movt r0,0x0
8e0024ec:	0152      	jalr r0
8e0024ee:	1e0b 0172 	mov r0,0x17f0
8e0024f2:	2003      	mov r1,0x0
8e0024f4:	000b 1002 	movt r0,0x0
8e0024f8:	1552      	jalr r5
8e0024fa:	11cc 0001 	ldr r0,[r4,+0xb]
8e0024fe:	658b 00e2 	mov r3,0xe2c
8e002502:	2003      	mov r1,0x0
8e002504:	4063      	mov r2,0x3
8e002506:	600b 18e2 	movt r3,0x8e00
8e00250a:	0d52      	jalr r3
8e00250c:	070b 0182 	mov r0,0x1838
8e002510:	2003      	mov r1,0x0
8e002512:	000b 1002 	movt r0,0x0
8e002516:	1552      	jalr r5
8e002518:	32c4      	ldr r1,[r4,0x5]
8e00251a:	000b 0002 	mov r0,0x0
8e00251e:	002b 1002 	movt r0,0x1
8e002522:	443a      	sub r2,r1,r0
8e002524:	3510      	bne 8e00258e <cpp_main+0x11a>
8e002526:	000b 0182 	mov r0,0x1800
8e00252a:	a10b 00d2 	mov r5,0xd08
8e00252e:	a00b 18e2 	movt r5,0x8e00
8e002532:	2003      	mov r1,0x0
8e002534:	000b 1002 	movt r0,0x0
8e002538:	1552      	jalr r5
8e00253a:	070b 01c2 	mov r0,0x1c38
8e00253e:	000b 1002 	movt r0,0x0
8e002542:	8024      	ldrh r4,[r0]
8e002544:	90d6      	lsl r4,r4,0x6
8e002546:	00a4      	ldrh r0,[r0,0x1]
8e002548:	901a      	add r4,r4,r0
8e00254a:	800b 1002 	movt r4,0x0
8e00254e:	340b 0252 	mov r1,0x25a0
8e002552:	10e2      	mov r0,r4
8e002554:	200b 18e2 	movt r1,0x8e00
8e002558:	0552      	jalr r1
8e00255a:	030b 0182 	mov r0,0x1818
8e00255e:	2003      	mov r1,0x0
8e002560:	000b 1002 	movt r0,0x0
8e002564:	1552      	jalr r5
8e002566:	5c8b 00f2 	mov r2,0xfe4
8e00256a:	10e2      	mov r0,r4
8e00256c:	2043      	mov r1,0x2
8e00256e:	400b 1002 	movt r2,0x0
8e002572:	0952      	jalr r2
8e002574:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002578:	b41b 2402 	add sp,sp,16
8e00257c:	080b 0182 	mov r0,0x1840
8e002580:	54e2      	mov r2,r5
8e002582:	946c 0400 	ldrd r4,[sp,+0x0]
8e002586:	2003      	mov r1,0x0
8e002588:	000b 1002 	movt r0,0x0
8e00258c:	0942      	jr r2
8e00258e:	d4ec 2400 	ldrd lr,[sp,+0x1]
8e002592:	b41b 2402 	add sp,sp,16
8e002596:	946c 0400 	ldrd r4,[sp,+0x0]
8e00259a:	194f 0402 	rts
8e00259e:	01a2      	nop

8e0025a0 <wait_inited_state>:
8e0025a0:	f75c 2700 	str fp,[sp],-0x6
8e0025a4:	f4ef 2402 	mov fp,sp
8e0025a8:	1f3c 0400 	strh r0,[fp,+0x6]
8e0025ac:	1f0b 01b2 	mov r0,0x1bf8
8e0025b0:	000b 1002 	movt r0,0x0
8e0025b4:	1e5c 0400 	str r0,[fp,+0x4]
8e0025b8:	1f2c 0400 	ldrh r0,[fp,+0x6]
8e0025bc:	2296      	lsl r1,r0,0x14
8e0025be:	1e4c 0400 	ldr r0,[fp,+0x4]
8e0025c2:	40e2      	mov r2,r0
8e0025c4:	1feb 0ff2 	mov r0,0xffff
8e0025c8:	01eb 1002 	movt r0,0xf
8e0025cc:	085a      	and r0,r2,r0
8e0025ce:	047a      	orr r0,r1,r0
8e0025d0:	1edc 0400 	str r0,[fp,+0x5]
8e0025d4:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0025d8:	0004      	ldrb r0,[r0]
8e0025da:	20b3      	sub r1,r0,1
8e0025dc:	0200      	beq 8e0025e0 <wait_inited_state+0x40>
8e0025de:	fbe0      	b 8e0025d4 <wait_inited_state+0x34>
8e0025e0:	01a2      	nop
8e0025e2:	f74c 2400 	ldr fp,[sp,+0x6]
8e0025e6:	b41b 2403 	add sp,sp,24
8e0025ea:	194f 0402 	rts
8e0025ee:	01a2      	nop

8e0025f0 <init_class_names>:
8e0025f0:	f55c 2700 	str fp,[sp],-0x2
8e0025f4:	f4ef 2402 	mov fp,sp
8e0025f8:	1e0b 0182 	mov r0,0x18f0
8e0025fc:	000b 1002 	movt r0,0x0
8e002600:	2b0b 0182 	mov r1,0x1858
8e002604:	200b 1002 	movt r1,0x0
8e002608:	20d4      	str r1,[r0,0x1]
8e00260a:	1e0b 0182 	mov r0,0x18f0
8e00260e:	000b 1002 	movt r0,0x0
8e002612:	2c0b 0182 	mov r1,0x1860
8e002616:	200b 1002 	movt r1,0x0
8e00261a:	2154      	str r1,[r0,0x2]
8e00261c:	1e0b 0182 	mov r0,0x18f0
8e002620:	000b 1002 	movt r0,0x0
8e002624:	2e0b 0182 	mov r1,0x1870
8e002628:	200b 1002 	movt r1,0x0
8e00262c:	21d4      	str r1,[r0,0x3]
8e00262e:	01a2      	nop
8e002630:	f54c 2400 	ldr fp,[sp,+0x2]
8e002634:	b41b 2401 	add sp,sp,8
8e002638:	194f 0402 	rts

8e00263c <ck_sizes>:
8e00263c:	f55c 2700 	str fp,[sp],-0x2
8e002640:	f4ef 2402 	mov fp,sp
8e002644:	01a2      	nop
8e002646:	f54c 2400 	ldr fp,[sp,+0x2]
8e00264a:	b41b 2401 	add sp,sp,8
8e00264e:	194f 0402 	rts
8e002652:	01a2      	nop

8e002654 <__cxa_atexit>:
8e002654:	f75c 2700 	str fp,[sp],-0x6
8e002658:	f4ef 2402 	mov fp,sp
8e00265c:	1edc 0400 	str r0,[fp,+0x5]
8e002660:	3e5c 0400 	str r1,[fp,+0x4]
8e002664:	5ddc 0400 	str r2,[fp,+0x3]
8e002668:	0003      	mov r0,0x0
8e00266a:	f74c 2400 	ldr fp,[sp,+0x6]
8e00266e:	b41b 2403 	add sp,sp,24
8e002672:	194f 0402 	rts
8e002676:	01a2      	nop

Disassembly of section .shared_dram:

8f000000 <BJK_OFF_CHIP_SHARED_MEM>:
	...

Disassembly of section .text:

00000100 <bjk_irq0_handler>:
     100:	14fc 0500 	strd r0,[sp,-0x1]
     104:	0512      	movfs r0,status
     106:	211f 0402 	movfs r1,iret
     10a:	b41b 24fc 	add sp,sp,-32
     10e:	0192      	gie
     110:	157c 0400 	strd r0,[sp,+0x2]
     114:	300b 0192 	mov r1,0x1980
     118:	55dc 0400 	str r2,[sp,+0x3]
     11c:	200b 1002 	movt r1,0x0
     120:	4404      	ldrb r2,[r1]
     122:	0833      	sub r0,r2,0
     124:	1c0b 01b2 	mov r0,0x1be0
     128:	000b 1002 	movt r0,0x0
     12c:	0900      	beq 13e <bjk_irq0_handler+0x3e>
     12e:	4003      	mov r2,0x0
     130:	4414      	strb r2,[r1]
     132:	20cc 0001 	ldr r1,[r0,+0x9]
     136:	2493      	add r1,r1,1
     138:	20dc 0001 	str r1,[r0,+0x9]
     13c:	0be0      	b 152 <bjk_irq0_handler+0x52>
     13e:	204c 0001 	ldr r1,[r0,+0x8]
     142:	2493      	add r1,r1,1
     144:	205c 0001 	str r1,[r0,+0x8]
     148:	080b 01c2 	mov r0,0x1c40
     14c:	000b 1002 	movt r0,0x0
     150:	4014      	strb r2,[r0]
     152:	156c 0400 	ldrd r0,[sp,+0x2]
     156:	55cc 0400 	ldr r2,[sp,+0x3]
     15a:	0392      	gid
     15c:	b41b 2404 	add sp,sp,32
     160:	0502      	movts status,r0
     162:	210f 0402 	movts iret,r1
     166:	14ec 0500 	ldrd r0,[sp,-0x1]
     16a:	01d2      	rti

0000016c <bjk_irq1_handler>:
     16c:	14fc 0500 	strd r0,[sp,-0x1]
     170:	0512      	movfs r0,status
     172:	211f 0402 	movfs r1,iret
     176:	b41b 24e4 	add sp,sp,-224
     17a:	0192      	gie
     17c:	157c 0403 	strd r0,[sp,+0x1a]
     180:	100b 0192 	mov r0,0x1980
     184:	54fc 0403 	strd r2,[sp,+0x19]
     188:	94dc 2406 	str ip,[sp,+0x31]
     18c:	d7fc 2402 	strd lr,[sp,+0x17]
     190:	177c 4402 	strd r16,[sp,+0x16]
     194:	56fc 4402 	strd r18,[sp,+0x15]
     198:	967c 4402 	strd r20,[sp,+0x14]
     19c:	d5fc 4402 	strd r22,[sp,+0x13]
     1a0:	157c 6402 	strd r24,[sp,+0x12]
     1a4:	54fc 6402 	strd r26,[sp,+0x11]
     1a8:	147c 8402 	strd r32,[sp,+0x10]
     1ac:	57fc 8401 	strd r34,[sp,+0xf]
     1b0:	977c 8401 	strd r36,[sp,+0xe]
     1b4:	d6fc 8401 	strd r38,[sp,+0xd]
     1b8:	167c a401 	strd r40,[sp,+0xc]
     1bc:	55fc a401 	strd r42,[sp,+0xb]
     1c0:	957c a401 	strd r44,[sp,+0xa]
     1c4:	d4fc a401 	strd r46,[sp,+0x9]
     1c8:	147c c401 	strd r48,[sp,+0x8]
     1cc:	57fc c400 	strd r50,[sp,+0x7]
     1d0:	977c c400 	strd r52,[sp,+0x6]
     1d4:	d6fc c400 	strd r54,[sp,+0x5]
     1d8:	167c e400 	strd r56,[sp,+0x4]
     1dc:	55fc e400 	strd r58,[sp,+0x3]
     1e0:	957c e400 	strd r60,[sp,+0x2]
     1e4:	d4fc e400 	strd r62,[sp,+0x1]
     1e8:	000b 1002 	movt r0,0x0
     1ec:	2084      	ldrb r1,[r0,0x1]
     1ee:	4433      	sub r2,r1,0
     1f0:	0d00      	beq 20a <bjk_irq1_handler+0x9e>
     1f2:	2003      	mov r1,0x0
     1f4:	2094      	strb r1,[r0,0x1]
     1f6:	3c0b 01b2 	mov r1,0x1be0
     1fa:	200b 1002 	movt r1,0x0
     1fe:	054c 0001 	ldr r0,[r1,+0xa]
     202:	0093      	add r0,r0,1
     204:	055c 0001 	str r0,[r1,+0xa]
     208:	0ce0      	b 220 <bjk_irq1_handler+0xb4>
     20a:	0d8b 0012 	mov r0,0x16c
     20e:	768b 01a2 	mov r3,0x1ab4
     212:	4003      	mov r2,0x0
     214:	2003      	mov r1,0x0
     216:	000b 1002 	movt r0,0x0
     21a:	600b 18e2 	movt r3,0x8e00
     21e:	0d52      	jalr r3
     220:	156c 0403 	ldrd r0,[sp,+0x1a]
     224:	54ec 0403 	ldrd r2,[sp,+0x19]
     228:	94cc 2406 	ldr ip,[sp,+0x31]
     22c:	d7ec 2402 	ldrd lr,[sp,+0x17]
     230:	176c 4402 	ldrd r16,[sp,+0x16]
     234:	56ec 4402 	ldrd r18,[sp,+0x15]
     238:	966c 4402 	ldrd r20,[sp,+0x14]
     23c:	d5ec 4402 	ldrd r22,[sp,+0x13]
     240:	156c 6402 	ldrd r24,[sp,+0x12]
     244:	54ec 6402 	ldrd r26,[sp,+0x11]
     248:	146c 8402 	ldrd r32,[sp,+0x10]
     24c:	57ec 8401 	ldrd r34,[sp,+0xf]
     250:	976c 8401 	ldrd r36,[sp,+0xe]
     254:	d6ec 8401 	ldrd r38,[sp,+0xd]
     258:	166c a401 	ldrd r40,[sp,+0xc]
     25c:	55ec a401 	ldrd r42,[sp,+0xb]
     260:	956c a401 	ldrd r44,[sp,+0xa]
     264:	d4ec a401 	ldrd r46,[sp,+0x9]
     268:	146c c401 	ldrd r48,[sp,+0x8]
     26c:	57ec c400 	ldrd r50,[sp,+0x7]
     270:	976c c400 	ldrd r52,[sp,+0x6]
     274:	d6ec c400 	ldrd r54,[sp,+0x5]
     278:	166c e400 	ldrd r56,[sp,+0x4]
     27c:	55ec e400 	ldrd r58,[sp,+0x3]
     280:	956c e400 	ldrd r60,[sp,+0x2]
     284:	d4ec e400 	ldrd r62,[sp,+0x1]
     288:	0392      	gid
     28a:	b41b 241c 	add sp,sp,224
     28e:	0502      	movts status,r0
     290:	210f 0402 	movts iret,r1
     294:	14ec 0500 	ldrd r0,[sp,-0x1]
     298:	01d2      	rti
     29a:	01a2      	nop

0000029c <bjk_irq2_handler>:
     29c:	14fc 0500 	strd r0,[sp,-0x1]
     2a0:	0512      	movfs r0,status
     2a2:	211f 0402 	movfs r1,iret
     2a6:	b41b 24fd 	add sp,sp,-24
     2aa:	0192      	gie
     2ac:	14fc 0400 	strd r0,[sp,+0x1]
     2b0:	3c0b 01b2 	mov r1,0x1be0
     2b4:	200b 1002 	movt r1,0x0
     2b8:	05cc 0001 	ldr r0,[r1,+0xb]
     2bc:	0093      	add r0,r0,1
     2be:	05dc 0001 	str r0,[r1,+0xb]
     2c2:	14ec 0400 	ldrd r0,[sp,+0x1]
     2c6:	0392      	gid
     2c8:	b41b 2403 	add sp,sp,24
     2cc:	0502      	movts status,r0
     2ce:	210f 0402 	movts iret,r1
     2d2:	14ec 0500 	ldrd r0,[sp,-0x1]
     2d6:	01d2      	rti

000002d8 <bjk_irq3_handler>:
     2d8:	14fc 0500 	strd r0,[sp,-0x1]
     2dc:	0512      	movfs r0,status
     2de:	211f 0402 	movfs r1,iret
     2e2:	b41b 24fc 	add sp,sp,-32
     2e6:	0192      	gie
     2e8:	157c 0400 	strd r0,[sp,+0x2]
     2ec:	100b 0192 	mov r0,0x1980
     2f0:	55dc 0400 	str r2,[sp,+0x3]
     2f4:	000b 1002 	movt r0,0x0
     2f8:	2184      	ldrb r1,[r0,0x3]
     2fa:	4433      	sub r2,r1,0
     2fc:	0c00      	beq 314 <bjk_irq3_handler+0x3c>
     2fe:	2003      	mov r1,0x0
     300:	2194      	strb r1,[r0,0x3]
     302:	3c0b 01b2 	mov r1,0x1be0
     306:	200b 1002 	movt r1,0x0
     30a:	064c 0001 	ldr r0,[r1,+0xc]
     30e:	0093      	add r0,r0,1
     310:	065c 0001 	str r0,[r1,+0xc]
     314:	156c 0400 	ldrd r0,[sp,+0x2]
     318:	55cc 0400 	ldr r2,[sp,+0x3]
     31c:	0392      	gid
     31e:	b41b 2404 	add sp,sp,32
     322:	0502      	movts status,r0
     324:	210f 0402 	movts iret,r1
     328:	14ec 0500 	ldrd r0,[sp,-0x1]
     32c:	01d2      	rti
     32e:	01a2      	nop

00000330 <bjk_irq4_handler>:
     330:	14fc 0500 	strd r0,[sp,-0x1]
     334:	0512      	movfs r0,status
     336:	211f 0402 	movfs r1,iret
     33a:	b41b 24fc 	add sp,sp,-32
     33e:	0192      	gie
     340:	157c 0400 	strd r0,[sp,+0x2]
     344:	100b 0192 	mov r0,0x1980
     348:	55dc 0400 	str r2,[sp,+0x3]
     34c:	000b 1002 	movt r0,0x0
     350:	2204      	ldrb r1,[r0,0x4]
     352:	4433      	sub r2,r1,0
     354:	0c00      	beq 36c <bjk_irq4_handler+0x3c>
     356:	2003      	mov r1,0x0
     358:	2214      	strb r1,[r0,0x4]
     35a:	3c0b 01b2 	mov r1,0x1be0
     35e:	200b 1002 	movt r1,0x0
     362:	06cc 0001 	ldr r0,[r1,+0xd]
     366:	0093      	add r0,r0,1
     368:	06dc 0001 	str r0,[r1,+0xd]
     36c:	156c 0400 	ldrd r0,[sp,+0x2]
     370:	55cc 0400 	ldr r2,[sp,+0x3]
     374:	0392      	gid
     376:	b41b 2404 	add sp,sp,32
     37a:	0502      	movts status,r0
     37c:	210f 0402 	movts iret,r1
     380:	14ec 0500 	ldrd r0,[sp,-0x1]
     384:	01d2      	rti
     386:	01a2      	nop

00000388 <bjk_irq5_handler>:
     388:	14fc 0500 	strd r0,[sp,-0x1]
     38c:	0512      	movfs r0,status
     38e:	211f 0402 	movfs r1,iret
     392:	b41b 24fc 	add sp,sp,-32
     396:	0192      	gie
     398:	157c 0400 	strd r0,[sp,+0x2]
     39c:	100b 0192 	mov r0,0x1980
     3a0:	55dc 0400 	str r2,[sp,+0x3]
     3a4:	000b 1002 	movt r0,0x0
     3a8:	2284      	ldrb r1,[r0,0x5]
     3aa:	4433      	sub r2,r1,0
     3ac:	0c00      	beq 3c4 <bjk_irq5_handler+0x3c>
     3ae:	2003      	mov r1,0x0
     3b0:	2294      	strb r1,[r0,0x5]
     3b2:	3c0b 01b2 	mov r1,0x1be0
     3b6:	200b 1002 	movt r1,0x0
     3ba:	074c 0001 	ldr r0,[r1,+0xe]
     3be:	0093      	add r0,r0,1
     3c0:	075c 0001 	str r0,[r1,+0xe]
     3c4:	156c 0400 	ldrd r0,[sp,+0x2]
     3c8:	55cc 0400 	ldr r2,[sp,+0x3]
     3cc:	0392      	gid
     3ce:	b41b 2404 	add sp,sp,32
     3d2:	0502      	movts status,r0
     3d4:	210f 0402 	movts iret,r1
     3d8:	14ec 0500 	ldrd r0,[sp,-0x1]
     3dc:	01d2      	rti
     3de:	01a2      	nop

000003e0 <bjk_irq6_handler>:
     3e0:	14fc 0500 	strd r0,[sp,-0x1]
     3e4:	0512      	movfs r0,status
     3e6:	211f 0402 	movfs r1,iret
     3ea:	b41b 24fc 	add sp,sp,-32
     3ee:	0192      	gie
     3f0:	157c 0400 	strd r0,[sp,+0x2]
     3f4:	100b 0192 	mov r0,0x1980
     3f8:	55dc 0400 	str r2,[sp,+0x3]
     3fc:	000b 1002 	movt r0,0x0
     400:	2304      	ldrb r1,[r0,0x6]
     402:	4433      	sub r2,r1,0
     404:	0c00      	beq 41c <bjk_irq6_handler+0x3c>
     406:	2003      	mov r1,0x0
     408:	2314      	strb r1,[r0,0x6]
     40a:	3c0b 01b2 	mov r1,0x1be0
     40e:	200b 1002 	movt r1,0x0
     412:	07cc 0001 	ldr r0,[r1,+0xf]
     416:	0093      	add r0,r0,1
     418:	07dc 0001 	str r0,[r1,+0xf]
     41c:	156c 0400 	ldrd r0,[sp,+0x2]
     420:	55cc 0400 	ldr r2,[sp,+0x3]
     424:	0392      	gid
     426:	b41b 2404 	add sp,sp,32
     42a:	0502      	movts status,r0
     42c:	210f 0402 	movts iret,r1
     430:	14ec 0500 	ldrd r0,[sp,-0x1]
     434:	01d2      	rti
     436:	01a2      	nop

00000438 <bjk_irq7_handler>:
     438:	14fc 0500 	strd r0,[sp,-0x1]
     43c:	0512      	movfs r0,status
     43e:	211f 0402 	movfs r1,iret
     442:	b41b 24fc 	add sp,sp,-32
     446:	0192      	gie
     448:	157c 0400 	strd r0,[sp,+0x2]
     44c:	100b 0192 	mov r0,0x1980
     450:	55dc 0400 	str r2,[sp,+0x3]
     454:	000b 1002 	movt r0,0x0
     458:	2384      	ldrb r1,[r0,0x7]
     45a:	4433      	sub r2,r1,0
     45c:	0c00      	beq 474 <bjk_irq7_handler+0x3c>
     45e:	2003      	mov r1,0x0
     460:	2394      	strb r1,[r0,0x7]
     462:	3c0b 01b2 	mov r1,0x1be0
     466:	200b 1002 	movt r1,0x0
     46a:	044c 0002 	ldr r0,[r1,+0x10]
     46e:	0093      	add r0,r0,1
     470:	045c 0002 	str r0,[r1,+0x10]
     474:	156c 0400 	ldrd r0,[sp,+0x2]
     478:	55cc 0400 	ldr r2,[sp,+0x3]
     47c:	0392      	gid
     47e:	b41b 2404 	add sp,sp,32
     482:	0502      	movts status,r0
     484:	210f 0402 	movts iret,r1
     488:	14ec 0500 	ldrd r0,[sp,-0x1]
     48c:	01d2      	rti
     48e:	01a2      	nop

00000490 <bjk_irq8_handler>:
     490:	14fc 0500 	strd r0,[sp,-0x1]
     494:	0512      	movfs r0,status
     496:	211f 0402 	movfs r1,iret
     49a:	b41b 24fc 	add sp,sp,-32
     49e:	0192      	gie
     4a0:	157c 0400 	strd r0,[sp,+0x2]
     4a4:	100b 0192 	mov r0,0x1980
     4a8:	55dc 0400 	str r2,[sp,+0x3]
     4ac:	000b 1002 	movt r0,0x0
     4b0:	200c 0001 	ldrb r1,[r0,+0x8]
     4b4:	4433      	sub r2,r1,0
     4b6:	0d00      	beq 4d0 <bjk_irq8_handler+0x40>
     4b8:	2003      	mov r1,0x0
     4ba:	201c 0001 	strb r1,[r0,+0x8]
     4be:	3c0b 01b2 	mov r1,0x1be0
     4c2:	200b 1002 	movt r1,0x0
     4c6:	04cc 0002 	ldr r0,[r1,+0x11]
     4ca:	0093      	add r0,r0,1
     4cc:	04dc 0002 	str r0,[r1,+0x11]
     4d0:	156c 0400 	ldrd r0,[sp,+0x2]
     4d4:	55cc 0400 	ldr r2,[sp,+0x3]
     4d8:	0392      	gid
     4da:	b41b 2404 	add sp,sp,32
     4de:	0502      	movts status,r0
     4e0:	210f 0402 	movts iret,r1
     4e4:	14ec 0500 	ldrd r0,[sp,-0x1]
     4e8:	01d2      	rti
     4ea:	01a2      	nop

000004ec <bjk_irq9_handler>:
     4ec:	14fc 0500 	strd r0,[sp,-0x1]
     4f0:	0512      	movfs r0,status
     4f2:	211f 0402 	movfs r1,iret
     4f6:	b41b 24fc 	add sp,sp,-32
     4fa:	0192      	gie
     4fc:	157c 0400 	strd r0,[sp,+0x2]
     500:	100b 0192 	mov r0,0x1980
     504:	55dc 0400 	str r2,[sp,+0x3]
     508:	000b 1002 	movt r0,0x0
     50c:	208c 0001 	ldrb r1,[r0,+0x9]
     510:	4433      	sub r2,r1,0
     512:	0d00      	beq 52c <bjk_irq9_handler+0x40>
     514:	2003      	mov r1,0x0
     516:	209c 0001 	strb r1,[r0,+0x9]
     51a:	3c0b 01b2 	mov r1,0x1be0
     51e:	200b 1002 	movt r1,0x0
     522:	054c 0002 	ldr r0,[r1,+0x12]
     526:	0093      	add r0,r0,1
     528:	055c 0002 	str r0,[r1,+0x12]
     52c:	156c 0400 	ldrd r0,[sp,+0x2]
     530:	55cc 0400 	ldr r2,[sp,+0x3]
     534:	0392      	gid
     536:	b41b 2404 	add sp,sp,32
     53a:	0502      	movts status,r0
     53c:	210f 0402 	movts iret,r1
     540:	14ec 0500 	ldrd r0,[sp,-0x1]
     544:	01d2      	rti
     546:	01a2      	nop

00000548 <main>:
     548:	d57c 2700 	strd lr,[sp],-0x2
     54c:	f41b 2402 	add fp,sp,16
     550:	1d8b 0072 	mov r0,0x7ec
     554:	000b 18e2 	movt r0,0x8e00
     558:	0152      	jalr r0
     55a:	0e8b 0242 	mov r0,0x2474
     55e:	000b 18e2 	movt r0,0x8e00
     562:	0152      	jalr r0
     564:	140b 0172 	mov r0,0x17a0
     568:	000b 1002 	movt r0,0x0
     56c:	1cdc 0500 	str r0,[fp,-0x1]
     570:	2003      	mov r1,0x0
     572:	1ccc 0500 	ldr r0,[fp,-0x1]
     576:	410b 00d2 	mov r2,0xd08
     57a:	400b 18e2 	movt r2,0x8e00
     57e:	0952      	jalr r2
     580:	1c0b 01b2 	mov r0,0x1be0
     584:	000b 1002 	movt r0,0x0
     588:	3dcb 00e2 	mov r1,0xeee
     58c:	21d4      	str r1,[r0,0x3]
     58e:	1e2b 0ff2 	mov r0,0xfff1
     592:	1e9c 0500 	strb r0,[fp,-0x5]
     596:	060b 01c2 	mov r0,0x1c30
     59a:	000b 1002 	movt r0,0x0
     59e:	0044      	ldr r0,[r0]
     5a0:	3e8c 0500 	ldrb r1,[fp,-0x5]
     5a4:	2314      	strb r1,[r0,0x6]
     5a6:	060b 01c2 	mov r0,0x1c30
     5aa:	000b 1002 	movt r0,0x0
     5ae:	0044      	ldr r0,[r0]
     5b0:	0304      	ldrb r0,[r0,0x6]
     5b2:	3e8c 0500 	ldrb r1,[fp,-0x5]
     5b6:	443a      	sub r2,r1,r0
     5b8:	f710      	bne 5a6 <main+0x5e>
     5ba:	0003      	mov r0,0x0
     5bc:	d56c 2400 	ldrd lr,[sp,+0x2]
     5c0:	b41b 2402 	add sp,sp,16
     5c4:	194f 0402 	rts

000005c8 <normal_start>:
     5c8:	be0b 27f2 	mov sp,0x7ff0
     5cc:	a00b 3002 	movt sp,0x0
     5d0:	e00b 2002 	mov fp,0x0
     5d4:	1feb 0032 	mov r0,0x3ff
     5d8:	050f 0402 	movts imask,r0
     5dc:	1d8b 0052 	mov r0,0x5ec
     5e0:	000b 1002 	movt r0,0x0
     5e4:	010f 0402 	movts iret,r0
     5e8:	01d2      	rti
     5ea:	01a2      	nop

000005ec <main_caller>:
     5ec:	090b 0052 	mov r0,0x548
     5f0:	000b 1002 	movt r0,0x0
     5f4:	0152      	jalr r0
     5f6:	01a2      	nop
     5f8:	1feb 0032 	mov r0,0x3ff
     5fc:	050f 0402 	movts imask,r0
     600:	0392      	gid
     602:	0fe2      	trap 0x3
     604:	01a2      	nop

00000606 <infn_loop>:
     606:	00e0      	b 606 <infn_loop>
     608:	01a2      	nop
     60a:	194f 0402 	rts
     60e:	01d2      	rti

00000610 <_ZN5actor7acquireEt>:
     610:	d6fc 2700 	strd lr,[sp],-0x5
     614:	94dc 0401 	str r4,[sp,+0x9]
     618:	f41b 2405 	add fp,sp,40
     61c:	8112      	movfs r4,config
     61e:	8112      	movfs r4,config
     620:	1f3c 0501 	strh r0,[fp,-0xe]
     624:	1f2c 0501 	ldrh r0,[fp,-0xe]
     628:	20b3      	sub r1,r0,1
     62a:	3910      	bne 69c <_ZN5actor7acquireEt+0x8c>
     62c:	1b8b 0182 	mov r0,0x18dc
     630:	000b 1002 	movt r0,0x0
     634:	2e8b 0132 	mov r1,0x1374
     638:	200b 1002 	movt r1,0x0
     63c:	5fcb 0ff2 	mov r2,0xfffe
     640:	5e2b 1ff2 	movt r2,0xfff1
     644:	0552      	jalr r1
     646:	20e2      	mov r1,r0
     648:	0023      	mov r0,0x1
     64a:	040a      	eor r0,r1,r0
     64c:	0316      	lsl r0,r0,0x18
     64e:	0306      	lsr r0,r0,0x18
     650:	4033      	sub r2,r0,0
     652:	2500      	beq 69c <_ZN5actor7acquireEt+0x8c>
     654:	1bcb 0182 	mov r0,0x18de
     658:	000b 1002 	movt r0,0x0
     65c:	2d8b 0172 	mov r1,0x176c
     660:	200b 1002 	movt r1,0x0
     664:	5fcb 0ff2 	mov r2,0xfffe
     668:	5e2b 1ff2 	movt r2,0xfff1
     66c:	0552      	jalr r1
     66e:	1e5c 0500 	str r0,[fp,-0x4]
     672:	1e4c 0500 	ldr r0,[fp,-0x4]
     676:	358b 0132 	mov r1,0x13ac
     67a:	200b 1002 	movt r1,0x0
     67e:	5fcb 0ff2 	mov r2,0xfffe
     682:	5e2b 1ff2 	movt r2,0xfff1
     686:	0552      	jalr r1
     688:	1e4c 0500 	ldr r0,[fp,-0x4]
     68c:	6033      	sub r3,r0,0
     68e:	0500      	beq 698 <_ZN5actor7acquireEt+0x88>
     690:	1e4c 0500 	ldr r0,[fp,-0x4]
     694:	0213      	add r0,r0,-4
     696:	77e0      	b 784 <_ZN5actor7acquireEt+0x174>
     698:	0003      	mov r0,0x0
     69a:	75e0      	b 784 <_ZN5actor7acquireEt+0x174>
     69c:	4203      	mov r2,0x10
     69e:	3f2c 0501 	ldrh r1,[fp,-0xe]
     6a2:	600b 0002 	mov r3,0x0
     6a6:	610b 1002 	movt r3,0x8
     6aa:	0512      	movfs r0,status
     6ac:	0392      	gid
     6ae:	811f 2002 	movfs ip,config
     6b2:	91ff 240a 	orr ip,ip,r3
     6b6:	810f 2002 	movts config,ip
     6ba:	0192      	gie
     6bc:	61eb 0ef2 	mov r3,0xef0f
     6c0:	7feb 1ff2 	movt r3,0xffff
     6c4:	851f 2002 	movfs ip,status
     6c8:	900f 240a 	eor ip,ip,r0
     6cc:	91df 240a 	and ip,ip,r3
     6d0:	900f 240a 	eor ip,ip,r0
     6d4:	850f 2002 	movts status,ip
     6d8:	08a7      	fmul r0,r2,r1
     6da:	000b 1002 	movt r0,0x0
     6de:	6e0b 0022 	mov r3,0x270
     6e2:	600b 18e2 	movt r3,0x8e00
     6e6:	5fcb 0ff2 	mov r2,0xfffe
     6ea:	5e2b 1ff2 	movt r2,0xfff1
     6ee:	2512      	movfs r1,status
     6f0:	0392      	gid
     6f2:	811f 2002 	movfs ip,config
     6f6:	920f 240a 	eor ip,ip,r4
     6fa:	915f 240a 	and ip,ip,r2
     6fe:	920f 240a 	eor ip,ip,r4
     702:	810f 2002 	movts config,ip
     706:	0192      	gie
     708:	41eb 0ef2 	mov r2,0xef0f
     70c:	5feb 1ff2 	movt r2,0xffff
     710:	851f 2002 	movfs ip,status
     714:	908f 240a 	eor ip,ip,r1
     718:	915f 240a 	and ip,ip,r2
     71c:	908f 240a 	eor ip,ip,r1
     720:	850f 2002 	movts status,ip
     724:	0d52      	jalr r3
     726:	1edc 0500 	str r0,[fp,-0x5]
     72a:	0003      	mov r0,0x0
     72c:	1ddc 0500 	str r0,[fp,-0x3]
     730:	3f2c 0501 	ldrh r1,[fp,-0xe]
     734:	1dcc 0500 	ldr r0,[fp,-0x3]
     738:	443a      	sub r2,r1,r0
     73a:	2390      	blte 780 <_ZN5actor7acquireEt+0x170>
     73c:	1dcc 0500 	ldr r0,[fp,-0x3]
     740:	0096      	lsl r0,r0,0x4
     742:	3ecc 0500 	ldr r1,[fp,-0x5]
     746:	041a      	add r0,r1,r0
     748:	20e2      	mov r1,r0
     74a:	0203      	mov r0,0x10
     74c:	6d8b 0122 	mov r3,0x126c
     750:	600b 1002 	movt r3,0x0
     754:	5fcb 0ff2 	mov r2,0xfffe
     758:	5e2b 1ff2 	movt r2,0xfff1
     75c:	0d52      	jalr r3
     75e:	6033      	sub r3,r0,0
     760:	0a00      	beq 774 <_ZN5actor7acquireEt+0x164>
     762:	3d0b 0142 	mov r1,0x14e8
     766:	200b 1002 	movt r1,0x0
     76a:	5fcb 0ff2 	mov r2,0xfffe
     76e:	5e2b 1ff2 	movt r2,0xfff1
     772:	0552      	jalr r1
     774:	1dcc 0500 	ldr r0,[fp,-0x3]
     778:	0093      	add r0,r0,1
     77a:	1ddc 0500 	str r0,[fp,-0x3]
     77e:	d9e0      	b 730 <_ZN5actor7acquireEt+0x120>
     780:	1ecc 0500 	ldr r0,[fp,-0x5]
     784:	5fcb 0ff2 	mov r2,0xfffe
     788:	5e2b 1ff2 	movt r2,0xfff1
     78c:	d6ec 2400 	ldrd lr,[sp,+0x5]
     790:	94cc 0401 	ldr r4,[sp,+0x9]
     794:	b41b 2405 	add sp,sp,40
     798:	194f 0402 	rts

0000079c <_ZN7missive7acquireEt>:
     79c:	d6fc 2700 	strd lr,[sp],-0x5
     7a0:	94dc 0401 	str r4,[sp,+0x9]
     7a4:	f41b 2405 	add fp,sp,40
     7a8:	8112      	movfs r4,config
     7aa:	8112      	movfs r4,config
     7ac:	1f3c 0501 	strh r0,[fp,-0xe]
     7b0:	1f2c 0501 	ldrh r0,[fp,-0xe]
     7b4:	20b3      	sub r1,r0,1
     7b6:	3910      	bne 828 <_ZN7missive7acquireEt+0x8c>
     7b8:	1c0b 0182 	mov r0,0x18e0
     7bc:	000b 1002 	movt r0,0x0
     7c0:	2e8b 0132 	mov r1,0x1374
     7c4:	200b 1002 	movt r1,0x0
     7c8:	5fcb 0ff2 	mov r2,0xfffe
     7cc:	5e2b 1ff2 	movt r2,0xfff1
     7d0:	0552      	jalr r1
     7d2:	20e2      	mov r1,r0
     7d4:	0023      	mov r0,0x1
     7d6:	040a      	eor r0,r1,r0
     7d8:	0316      	lsl r0,r0,0x18
     7da:	0306      	lsr r0,r0,0x18
     7dc:	4033      	sub r2,r0,0
     7de:	2500      	beq 828 <_ZN7missive7acquireEt+0x8c>
     7e0:	1c4b 0182 	mov r0,0x18e2
     7e4:	000b 1002 	movt r0,0x0
     7e8:	2d8b 0172 	mov r1,0x176c
     7ec:	200b 1002 	movt r1,0x0
     7f0:	5fcb 0ff2 	mov r2,0xfffe
     7f4:	5e2b 1ff2 	movt r2,0xfff1
     7f8:	0552      	jalr r1
     7fa:	1e5c 0500 	str r0,[fp,-0x4]
     7fe:	1e4c 0500 	ldr r0,[fp,-0x4]
     802:	358b 0132 	mov r1,0x13ac
     806:	200b 1002 	movt r1,0x0
     80a:	5fcb 0ff2 	mov r2,0xfffe
     80e:	5e2b 1ff2 	movt r2,0xfff1
     812:	0552      	jalr r1
     814:	1e4c 0500 	ldr r0,[fp,-0x4]
     818:	6033      	sub r3,r0,0
     81a:	0500      	beq 824 <_ZN7missive7acquireEt+0x88>
     81c:	1e4c 0500 	ldr r0,[fp,-0x4]
     820:	0213      	add r0,r0,-4
     822:	79e0      	b 914 <_ZN7missive7acquireEt+0x178>
     824:	0003      	mov r0,0x0
     826:	77e0      	b 914 <_ZN7missive7acquireEt+0x178>
     828:	4303      	mov r2,0x18
     82a:	3f2c 0501 	ldrh r1,[fp,-0xe]
     82e:	600b 0002 	mov r3,0x0
     832:	610b 1002 	movt r3,0x8
     836:	0512      	movfs r0,status
     838:	0392      	gid
     83a:	811f 2002 	movfs ip,config
     83e:	91ff 240a 	orr ip,ip,r3
     842:	810f 2002 	movts config,ip
     846:	0192      	gie
     848:	61eb 0ef2 	mov r3,0xef0f
     84c:	7feb 1ff2 	movt r3,0xffff
     850:	851f 2002 	movfs ip,status
     854:	900f 240a 	eor ip,ip,r0
     858:	91df 240a 	and ip,ip,r3
     85c:	900f 240a 	eor ip,ip,r0
     860:	850f 2002 	movts status,ip
     864:	08a7      	fmul r0,r2,r1
     866:	000b 1002 	movt r0,0x0
     86a:	6e0b 0022 	mov r3,0x270
     86e:	600b 18e2 	movt r3,0x8e00
     872:	5fcb 0ff2 	mov r2,0xfffe
     876:	5e2b 1ff2 	movt r2,0xfff1
     87a:	2512      	movfs r1,status
     87c:	0392      	gid
     87e:	811f 2002 	movfs ip,config
     882:	920f 240a 	eor ip,ip,r4
     886:	915f 240a 	and ip,ip,r2
     88a:	920f 240a 	eor ip,ip,r4
     88e:	810f 2002 	movts config,ip
     892:	0192      	gie
     894:	41eb 0ef2 	mov r2,0xef0f
     898:	5feb 1ff2 	movt r2,0xffff
     89c:	851f 2002 	movfs ip,status
     8a0:	908f 240a 	eor ip,ip,r1
     8a4:	915f 240a 	and ip,ip,r2
     8a8:	908f 240a 	eor ip,ip,r1
     8ac:	850f 2002 	movts status,ip
     8b0:	0d52      	jalr r3
     8b2:	1edc 0500 	str r0,[fp,-0x5]
     8b6:	0003      	mov r0,0x0
     8b8:	1ddc 0500 	str r0,[fp,-0x3]
     8bc:	3f2c 0501 	ldrh r1,[fp,-0xe]
     8c0:	1dcc 0500 	ldr r0,[fp,-0x3]
     8c4:	443a      	sub r2,r1,r0
     8c6:	2590      	blte 910 <_ZN7missive7acquireEt+0x174>
     8c8:	1dcc 0500 	ldr r0,[fp,-0x3]
     8cc:	0076      	lsl r0,r0,0x3
     8ce:	2056      	lsl r1,r0,0x2
     8d0:	043a      	sub r0,r1,r0
     8d2:	3ecc 0500 	ldr r1,[fp,-0x5]
     8d6:	041a      	add r0,r1,r0
     8d8:	20e2      	mov r1,r0
     8da:	0303      	mov r0,0x18
     8dc:	6d8b 0122 	mov r3,0x126c
     8e0:	600b 1002 	movt r3,0x0
     8e4:	5fcb 0ff2 	mov r2,0xfffe
     8e8:	5e2b 1ff2 	movt r2,0xfff1
     8ec:	0d52      	jalr r3
     8ee:	6033      	sub r3,r0,0
     8f0:	0a00      	beq 904 <_ZN7missive7acquireEt+0x168>
     8f2:	380b 0152 	mov r1,0x15c0
     8f6:	200b 1002 	movt r1,0x0
     8fa:	5fcb 0ff2 	mov r2,0xfffe
     8fe:	5e2b 1ff2 	movt r2,0xfff1
     902:	0552      	jalr r1
     904:	1dcc 0500 	ldr r0,[fp,-0x3]
     908:	0093      	add r0,r0,1
     90a:	1ddc 0500 	str r0,[fp,-0x3]
     90e:	d7e0      	b 8bc <_ZN7missive7acquireEt+0x120>
     910:	1ecc 0500 	ldr r0,[fp,-0x5]
     914:	5fcb 0ff2 	mov r2,0xfffe
     918:	5e2b 1ff2 	movt r2,0xfff1
     91c:	d6ec 2400 	ldrd lr,[sp,+0x5]
     920:	94cc 0401 	ldr r4,[sp,+0x9]
     924:	b41b 2405 	add sp,sp,40
     928:	194f 0402 	rts

0000092c <_ZN11missive_ref7acquireEt>:
     92c:	d6fc 2700 	strd lr,[sp],-0x5
     930:	94dc 0401 	str r4,[sp,+0x9]
     934:	f41b 2405 	add fp,sp,40
     938:	8112      	movfs r4,config
     93a:	8112      	movfs r4,config
     93c:	1f3c 0501 	strh r0,[fp,-0xe]
     940:	1f2c 0501 	ldrh r0,[fp,-0xe]
     944:	20b3      	sub r1,r0,1
     946:	3910      	bne 9b8 <_ZN11missive_ref7acquireEt+0x8c>
     948:	1c8b 0182 	mov r0,0x18e4
     94c:	000b 1002 	movt r0,0x0
     950:	2e8b 0132 	mov r1,0x1374
     954:	200b 1002 	movt r1,0x0
     958:	5fcb 0ff2 	mov r2,0xfffe
     95c:	5e2b 1ff2 	movt r2,0xfff1
     960:	0552      	jalr r1
     962:	20e2      	mov r1,r0
     964:	0023      	mov r0,0x1
     966:	040a      	eor r0,r1,r0
     968:	0316      	lsl r0,r0,0x18
     96a:	0306      	lsr r0,r0,0x18
     96c:	4033      	sub r2,r0,0
     96e:	2500      	beq 9b8 <_ZN11missive_ref7acquireEt+0x8c>
     970:	1ccb 0182 	mov r0,0x18e6
     974:	000b 1002 	movt r0,0x0
     978:	2d8b 0172 	mov r1,0x176c
     97c:	200b 1002 	movt r1,0x0
     980:	5fcb 0ff2 	mov r2,0xfffe
     984:	5e2b 1ff2 	movt r2,0xfff1
     988:	0552      	jalr r1
     98a:	1e5c 0500 	str r0,[fp,-0x4]
     98e:	1e4c 0500 	ldr r0,[fp,-0x4]
     992:	358b 0132 	mov r1,0x13ac
     996:	200b 1002 	movt r1,0x0
     99a:	5fcb 0ff2 	mov r2,0xfffe
     99e:	5e2b 1ff2 	movt r2,0xfff1
     9a2:	0552      	jalr r1
     9a4:	1e4c 0500 	ldr r0,[fp,-0x4]
     9a8:	6033      	sub r3,r0,0
     9aa:	0500      	beq 9b4 <_ZN11missive_ref7acquireEt+0x88>
     9ac:	1e4c 0500 	ldr r0,[fp,-0x4]
     9b0:	0213      	add r0,r0,-4
     9b2:	77e0      	b aa0 <_ZN11missive_ref7acquireEt+0x174>
     9b4:	0003      	mov r0,0x0
     9b6:	75e0      	b aa0 <_ZN11missive_ref7acquireEt+0x174>
     9b8:	4203      	mov r2,0x10
     9ba:	3f2c 0501 	ldrh r1,[fp,-0xe]
     9be:	600b 0002 	mov r3,0x0
     9c2:	610b 1002 	movt r3,0x8
     9c6:	0512      	movfs r0,status
     9c8:	0392      	gid
     9ca:	811f 2002 	movfs ip,config
     9ce:	91ff 240a 	orr ip,ip,r3
     9d2:	810f 2002 	movts config,ip
     9d6:	0192      	gie
     9d8:	61eb 0ef2 	mov r3,0xef0f
     9dc:	7feb 1ff2 	movt r3,0xffff
     9e0:	851f 2002 	movfs ip,status
     9e4:	900f 240a 	eor ip,ip,r0
     9e8:	91df 240a 	and ip,ip,r3
     9ec:	900f 240a 	eor ip,ip,r0
     9f0:	850f 2002 	movts status,ip
     9f4:	08a7      	fmul r0,r2,r1
     9f6:	000b 1002 	movt r0,0x0
     9fa:	6e0b 0022 	mov r3,0x270
     9fe:	600b 18e2 	movt r3,0x8e00
     a02:	5fcb 0ff2 	mov r2,0xfffe
     a06:	5e2b 1ff2 	movt r2,0xfff1
     a0a:	2512      	movfs r1,status
     a0c:	0392      	gid
     a0e:	811f 2002 	movfs ip,config
     a12:	920f 240a 	eor ip,ip,r4
     a16:	915f 240a 	and ip,ip,r2
     a1a:	920f 240a 	eor ip,ip,r4
     a1e:	810f 2002 	movts config,ip
     a22:	0192      	gie
     a24:	41eb 0ef2 	mov r2,0xef0f
     a28:	5feb 1ff2 	movt r2,0xffff
     a2c:	851f 2002 	movfs ip,status
     a30:	908f 240a 	eor ip,ip,r1
     a34:	915f 240a 	and ip,ip,r2
     a38:	908f 240a 	eor ip,ip,r1
     a3c:	850f 2002 	movts status,ip
     a40:	0d52      	jalr r3
     a42:	1edc 0500 	str r0,[fp,-0x5]
     a46:	0003      	mov r0,0x0
     a48:	1ddc 0500 	str r0,[fp,-0x3]
     a4c:	3f2c 0501 	ldrh r1,[fp,-0xe]
     a50:	1dcc 0500 	ldr r0,[fp,-0x3]
     a54:	443a      	sub r2,r1,r0
     a56:	2390      	blte a9c <_ZN11missive_ref7acquireEt+0x170>
     a58:	1dcc 0500 	ldr r0,[fp,-0x3]
     a5c:	0096      	lsl r0,r0,0x4
     a5e:	3ecc 0500 	ldr r1,[fp,-0x5]
     a62:	041a      	add r0,r1,r0
     a64:	20e2      	mov r1,r0
     a66:	0203      	mov r0,0x10
     a68:	6d8b 0122 	mov r3,0x126c
     a6c:	600b 1002 	movt r3,0x0
     a70:	5fcb 0ff2 	mov r2,0xfffe
     a74:	5e2b 1ff2 	movt r2,0xfff1
     a78:	0d52      	jalr r3
     a7a:	6033      	sub r3,r0,0
     a7c:	0a00      	beq a90 <_ZN11missive_ref7acquireEt+0x164>
     a7e:	308b 0162 	mov r1,0x1684
     a82:	200b 1002 	movt r1,0x0
     a86:	5fcb 0ff2 	mov r2,0xfffe
     a8a:	5e2b 1ff2 	movt r2,0xfff1
     a8e:	0552      	jalr r1
     a90:	1dcc 0500 	ldr r0,[fp,-0x3]
     a94:	0093      	add r0,r0,1
     a96:	1ddc 0500 	str r0,[fp,-0x3]
     a9a:	d9e0      	b a4c <_ZN11missive_ref7acquireEt+0x120>
     a9c:	1ecc 0500 	ldr r0,[fp,-0x5]
     aa0:	5fcb 0ff2 	mov r2,0xfffe
     aa4:	5e2b 1ff2 	movt r2,0xfff1
     aa8:	d6ec 2400 	ldrd lr,[sp,+0x5]
     aac:	94cc 0401 	ldr r4,[sp,+0x9]
     ab0:	b41b 2405 	add sp,sp,40
     ab4:	194f 0402 	rts

00000ab8 <_ZN11missive_grp7acquireEt>:
     ab8:	d6fc 2700 	strd lr,[sp],-0x5
     abc:	94dc 0401 	str r4,[sp,+0x9]
     ac0:	f41b 2405 	add fp,sp,40
     ac4:	8112      	movfs r4,config
     ac6:	8112      	movfs r4,config
     ac8:	1f3c 0501 	strh r0,[fp,-0xe]
     acc:	1f2c 0501 	ldrh r0,[fp,-0xe]
     ad0:	20b3      	sub r1,r0,1
     ad2:	3910      	bne b44 <_ZN11missive_grp7acquireEt+0x8c>
     ad4:	1d0b 0182 	mov r0,0x18e8
     ad8:	000b 1002 	movt r0,0x0
     adc:	2e8b 0132 	mov r1,0x1374
     ae0:	200b 1002 	movt r1,0x0
     ae4:	5fcb 0ff2 	mov r2,0xfffe
     ae8:	5e2b 1ff2 	movt r2,0xfff1
     aec:	0552      	jalr r1
     aee:	20e2      	mov r1,r0
     af0:	0023      	mov r0,0x1
     af2:	040a      	eor r0,r1,r0
     af4:	0316      	lsl r0,r0,0x18
     af6:	0306      	lsr r0,r0,0x18
     af8:	4033      	sub r2,r0,0
     afa:	2500      	beq b44 <_ZN11missive_grp7acquireEt+0x8c>
     afc:	1d4b 0182 	mov r0,0x18ea
     b00:	000b 1002 	movt r0,0x0
     b04:	2d8b 0172 	mov r1,0x176c
     b08:	200b 1002 	movt r1,0x0
     b0c:	5fcb 0ff2 	mov r2,0xfffe
     b10:	5e2b 1ff2 	movt r2,0xfff1
     b14:	0552      	jalr r1
     b16:	1e5c 0500 	str r0,[fp,-0x4]
     b1a:	1e4c 0500 	ldr r0,[fp,-0x4]
     b1e:	358b 0132 	mov r1,0x13ac
     b22:	200b 1002 	movt r1,0x0
     b26:	5fcb 0ff2 	mov r2,0xfffe
     b2a:	5e2b 1ff2 	movt r2,0xfff1
     b2e:	0552      	jalr r1
     b30:	1e4c 0500 	ldr r0,[fp,-0x4]
     b34:	6033      	sub r3,r0,0
     b36:	0500      	beq b40 <_ZN11missive_grp7acquireEt+0x88>
     b38:	1e4c 0500 	ldr r0,[fp,-0x4]
     b3c:	0213      	add r0,r0,-4
     b3e:	79e0      	b c30 <_ZN11missive_grp7acquireEt+0x178>
     b40:	0003      	mov r0,0x0
     b42:	77e0      	b c30 <_ZN11missive_grp7acquireEt+0x178>
     b44:	4303      	mov r2,0x18
     b46:	3f2c 0501 	ldrh r1,[fp,-0xe]
     b4a:	600b 0002 	mov r3,0x0
     b4e:	610b 1002 	movt r3,0x8
     b52:	0512      	movfs r0,status
     b54:	0392      	gid
     b56:	811f 2002 	movfs ip,config
     b5a:	91ff 240a 	orr ip,ip,r3
     b5e:	810f 2002 	movts config,ip
     b62:	0192      	gie
     b64:	61eb 0ef2 	mov r3,0xef0f
     b68:	7feb 1ff2 	movt r3,0xffff
     b6c:	851f 2002 	movfs ip,status
     b70:	900f 240a 	eor ip,ip,r0
     b74:	91df 240a 	and ip,ip,r3
     b78:	900f 240a 	eor ip,ip,r0
     b7c:	850f 2002 	movts status,ip
     b80:	08a7      	fmul r0,r2,r1
     b82:	000b 1002 	movt r0,0x0
     b86:	6e0b 0022 	mov r3,0x270
     b8a:	600b 18e2 	movt r3,0x8e00
     b8e:	5fcb 0ff2 	mov r2,0xfffe
     b92:	5e2b 1ff2 	movt r2,0xfff1
     b96:	2512      	movfs r1,status
     b98:	0392      	gid
     b9a:	811f 2002 	movfs ip,config
     b9e:	920f 240a 	eor ip,ip,r4
     ba2:	915f 240a 	and ip,ip,r2
     ba6:	920f 240a 	eor ip,ip,r4
     baa:	810f 2002 	movts config,ip
     bae:	0192      	gie
     bb0:	41eb 0ef2 	mov r2,0xef0f
     bb4:	5feb 1ff2 	movt r2,0xffff
     bb8:	851f 2002 	movfs ip,status
     bbc:	908f 240a 	eor ip,ip,r1
     bc0:	915f 240a 	and ip,ip,r2
     bc4:	908f 240a 	eor ip,ip,r1
     bc8:	850f 2002 	movts status,ip
     bcc:	0d52      	jalr r3
     bce:	1edc 0500 	str r0,[fp,-0x5]
     bd2:	0003      	mov r0,0x0
     bd4:	1ddc 0500 	str r0,[fp,-0x3]
     bd8:	3f2c 0501 	ldrh r1,[fp,-0xe]
     bdc:	1dcc 0500 	ldr r0,[fp,-0x3]
     be0:	443a      	sub r2,r1,r0
     be2:	2590      	blte c2c <_ZN11missive_grp7acquireEt+0x174>
     be4:	1dcc 0500 	ldr r0,[fp,-0x3]
     be8:	0076      	lsl r0,r0,0x3
     bea:	2056      	lsl r1,r0,0x2
     bec:	043a      	sub r0,r1,r0
     bee:	3ecc 0500 	ldr r1,[fp,-0x5]
     bf2:	041a      	add r0,r1,r0
     bf4:	20e2      	mov r1,r0
     bf6:	0303      	mov r0,0x18
     bf8:	6d8b 0122 	mov r3,0x126c
     bfc:	600b 1002 	movt r3,0x0
     c00:	5fcb 0ff2 	mov r2,0xfffe
     c04:	5e2b 1ff2 	movt r2,0xfff1
     c08:	0d52      	jalr r3
     c0a:	6033      	sub r3,r0,0
     c0c:	0a00      	beq c20 <_ZN11missive_grp7acquireEt+0x168>
     c0e:	250b 0162 	mov r1,0x1628
     c12:	200b 1002 	movt r1,0x0
     c16:	5fcb 0ff2 	mov r2,0xfffe
     c1a:	5e2b 1ff2 	movt r2,0xfff1
     c1e:	0552      	jalr r1
     c20:	1dcc 0500 	ldr r0,[fp,-0x3]
     c24:	0093      	add r0,r0,1
     c26:	1ddc 0500 	str r0,[fp,-0x3]
     c2a:	d7e0      	b bd8 <_ZN11missive_grp7acquireEt+0x120>
     c2c:	1ecc 0500 	ldr r0,[fp,-0x5]
     c30:	5fcb 0ff2 	mov r2,0xfffe
     c34:	5e2b 1ff2 	movt r2,0xfff1
     c38:	d6ec 2400 	ldrd lr,[sp,+0x5]
     c3c:	94cc 0401 	ldr r4,[sp,+0x9]
     c40:	b41b 2405 	add sp,sp,40
     c44:	194f 0402 	rts

00000c48 <_Z15add_out_missiveR7missive>:
     c48:	96fc 0700 	strd r4,[sp],-0x5
     c4c:	d67c 0400 	strd r6,[sp,+0x4]
     c50:	ad8b 0172 	mov r5,0x176c
     c54:	c0e2      	mov r6,r0
     c56:	0d4b 0192 	mov r0,0x196a
     c5a:	15fc 2400 	strd r8,[sp,+0x3]
     c5e:	557c 2400 	strd r10,[sp,+0x2]
     c62:	d4fc 2400 	strd lr,[sp,+0x1]
     c66:	000b 1002 	movt r0,0x0
     c6a:	a00b 1002 	movt r5,0x0
     c6e:	1552      	jalr r5
     c70:	ed0b 0192 	mov r7,0x1968
     c74:	070b 2142 	mov r8,0x1438
     c78:	200b 2002 	mov r9,0x0
     c7c:	488b 2142 	mov r10,0x1444
     c80:	80e2      	mov r4,r0
     c82:	e00b 1002 	movt r7,0x0
     c86:	000b 3002 	movt r8,0x0
     c8a:	3e0b 3ff2 	movt r9,0xfff0
     c8e:	400b 3002 	movt r10,0x0
     c92:	13ba      	sub r0,r4,r7
     c94:	1c00      	beq ccc <_Z15add_out_missiveR7missive+0x84>
     c96:	5033      	sub r2,r4,0
     c98:	0400      	beq ca0 <_Z15add_out_missiveR7missive+0x58>
     c9a:	721b 20ff 	add r11,r4,-4
     c9e:	03e0      	b ca4 <_Z15add_out_missiveR7missive+0x5c>
     ca0:	600b 2002 	mov r11,0x0
     ca4:	0e1b 0402 	add r0,r11,20
     ca8:	015f 0402 	jalr r8
     cac:	205a      	and r1,r0,r0
     cae:	2f00      	beq d0c <_Z15add_out_missiveR7missive+0xc4>
     cb0:	59c4      	ldr r2,[r6,0x3]
     cb2:	0544      	ldr r0,[r1,0x2]
     cb4:	480a      	eor r2,r2,r0
     cb6:	48df 008a 	and r2,r2,r9
     cba:	0510      	bne cc4 <_Z15add_out_missiveR7missive+0x7c>
     cbc:	0e1b 0400 	add r0,r11,4
     cc0:	095f 0402 	jalr r10
     cc4:	1113      	add r0,r4,2
     cc6:	1552      	jalr r5
     cc8:	80e2      	mov r4,r0
     cca:	e4e0      	b c92 <_Z15add_out_missiveR7missive+0x4a>
     ccc:	370b 00a2 	mov r1,0xab8
     cd0:	200b 1002 	movt r1,0x0
     cd4:	0023      	mov r0,0x1
     cd6:	0552      	jalr r1
     cd8:	a88b 0142 	mov r5,0x1444
     cdc:	e21b 0000 	add r7,r0,4
     ce0:	3a1b 0000 	add r1,r6,4
     ce4:	1ce2      	mov r0,r7
     ce6:	a00b 1002 	movt r5,0x0
     cea:	1552      	jalr r5
     cec:	3ce2      	mov r1,r7
     cee:	15ec 2400 	ldrd r8,[sp,+0x3]
     cf2:	d66c 0400 	ldrd r6,[sp,+0x4]
     cf6:	556c 2400 	ldrd r10,[sp,+0x2]
     cfa:	d4ec 2400 	ldrd lr,[sp,+0x1]
     cfe:	b41b 2405 	add sp,sp,40
     d02:	10e2      	mov r0,r4
     d04:	54e2      	mov r2,r5
     d06:	946c 0400 	ldrd r4,[sp,+0x0]
     d0a:	0942      	jr r2
     d0c:	05c4      	ldr r0,[r1,0x3]
     d0e:	188b 00c2 	mov r0,0xcc4
     d12:	000b 18e2 	movt r0,0x8e00
     d16:	0152      	jalr r0

00000d18 <_Z22call_handlers_of_groupR11missive_grp>:
     d18:	95fc 0700 	strd r4,[sp],-0x3
     d1c:	ad8b 0172 	mov r5,0x176c
     d20:	d57c 0400 	strd r6,[sp,+0x2]
     d24:	d4fc 2400 	strd lr,[sp,+0x1]
     d28:	c0e2      	mov r6,r0
     d2a:	a00b 1002 	movt r5,0x0
     d2e:	031b 0000 	add r0,r0,6
     d32:	1552      	jalr r5
     d34:	e10b 0192 	mov r7,0x1908
     d38:	80e2      	mov r4,r0
     d3a:	da1b 0000 	add r6,r6,4
     d3e:	e00b 1002 	movt r7,0x0
     d42:	133a      	sub r0,r4,r6
     d44:	1800      	beq d74 <_Z22call_handlers_of_groupR11missive_grp+0x5c>
     d46:	1033      	sub r0,r4,0
     d48:	1000      	beq d68 <_Z22call_handlers_of_groupR11missive_grp+0x50>
     d4a:	1144      	ldr r0,[r4,0x2]
     d4c:	200c 0001 	ldrb r1,[r0,+0x8]
     d50:	04b3      	sub r0,r1,1
     d52:	0720      	bgtu d60 <_Z22call_handlers_of_groupR11missive_grp+0x48>
     d54:	2456      	lsl r1,r1,0x2
     d56:	3cc1      	ldr r1,[r7,r1]
     d58:	0433      	sub r0,r1,0
     d5a:	0300      	beq d60 <_Z22call_handlers_of_groupR11missive_grp+0x48>
     d5c:	1213      	add r0,r4,-4
     d5e:	0552      	jalr r1
     d60:	1113      	add r0,r4,2
     d62:	1552      	jalr r5
     d64:	80e2      	mov r4,r0
     d66:	eee0      	b d42 <_Z22call_handlers_of_groupR11missive_grp+0x2a>
     d68:	11c4      	ldr r0,[r4,0x3]
     d6a:	188b 00c2 	mov r0,0xcc4
     d6e:	000b 18e2 	movt r0,0x8e00
     d72:	0152      	jalr r0
     d74:	d56c 0400 	ldrd r6,[sp,+0x2]
     d78:	d4ec 2400 	ldrd lr,[sp,+0x1]
     d7c:	b41b 2403 	add sp,sp,24
     d80:	946c 0400 	ldrd r4,[sp,+0x0]
     d84:	194f 0402 	rts

00000d88 <_Z16actors_main_loopv>:
     d88:	97fc 0700 	strd r4,[sp],-0x7
     d8c:	d77c 0400 	strd r6,[sp,+0x6]
     d90:	cb0b 0152 	mov r6,0x1558
     d94:	c00b 1002 	movt r6,0x0
     d98:	16fc 2400 	strd r8,[sp,+0x5]
     d9c:	567c 2400 	strd r10,[sp,+0x4]
     da0:	d5fc 2400 	strd lr,[sp,+0x3]
     da4:	8112      	movfs r4,config
     da6:	0c4b 0192 	mov r0,0x1962
     daa:	2d8b 0172 	mov r1,0x176c
     dae:	000b 1002 	movt r0,0x0
     db2:	200b 1002 	movt r1,0x0
     db6:	0552      	jalr r1
     db8:	ad8b 0172 	mov r5,0x176c
     dbc:	00ef 2002 	mov r8,r0
     dc0:	a00b 1002 	movt r5,0x0
     dc4:	e003      	mov r7,0x0
     dc6:	4c0b 0192 	mov r2,0x1960
     dca:	400b 1002 	movt r2,0x0
     dce:	413f 040a 	sub r2,r8,r2
     dd2:	1a00      	beq e06 <_Z16actors_main_loopv+0x7e>
     dd4:	603b 0400 	sub r3,r8,0
     dd8:	e808 0000 	beq fa8 <_Z16actors_main_loopv+0x220>
     ddc:	014c 0400 	ldr r0,[r8,+0x2]
     de0:	830b 20d2 	mov ip,0xd18
     de4:	800b 3002 	movt ip,0x0
     de8:	115f 0402 	jalr ip
     dec:	021b 04ff 	add r0,r8,-4
     df0:	e15c 0400 	str r7,[r8,+0x2]
     df4:	1952      	jalr r6
     df6:	211b 2400 	add r9,r8,2
     dfa:	04ef 0402 	mov r0,r9
     dfe:	1552      	jalr r5
     e00:	00ef 2002 	mov r8,r0
     e04:	e1e0      	b dc6 <_Z16actors_main_loopv+0x3e>
     e06:	0ccb 0192 	mov r0,0x1966
     e0a:	000b 1002 	movt r0,0x0
     e0e:	1552      	jalr r5
     e10:	2c8b 2192 	mov r9,0x1964
     e14:	400b 2002 	mov r10,0x0
     e18:	610b 2192 	mov r11,0x1908
     e1c:	00ef 2002 	mov r8,r0
     e20:	200b 3002 	movt r9,0x0
     e24:	5e0b 3ff2 	movt r10,0xfff0
     e28:	600b 3002 	movt r11,0x0
     e2c:	20bf 448a 	sub r17,r8,r9
     e30:	3c00      	beq ea8 <_Z16actors_main_loopv+0x120>
     e32:	603b 4400 	sub r19,r8,0
     e36:	b908 0000 	beq fa8 <_Z16actors_main_loopv+0x220>
     e3a:	011b 0400 	add r0,r8,2
     e3e:	1552      	jalr r5
     e40:	16dc 0400 	str r0,[sp,+0x5]
     e44:	014c 0400 	ldr r0,[r8,+0x2]
     e48:	e21b 04ff 	add r7,r8,-4
     e4c:	215f 008a 	and r1,r0,r10
     e50:	0b00      	beq e66 <_Z16actors_main_loopv+0xde>
     e52:	3c0b 01b2 	mov r1,0x1be0
     e56:	200b 1002 	movt r1,0x0
     e5a:	6286      	lsr r3,r0,0x14
     e5c:	242c 0001 	ldrh r1,[r1,+0x8]
     e60:	8cbf 200a 	sub ip,r3,r1
     e64:	1410      	bne e8c <_Z16actors_main_loopv+0x104>
     e66:	000c 0001 	ldrb r0,[r0,+0x8]
     e6a:	20bb 4000 	sub r17,r0,1
     e6e:	0920      	bgtu e80 <_Z16actors_main_loopv+0xf8>
     e70:	0056      	lsl r0,r0,0x2
     e72:	6c49 0400 	ldr r3,[r11,+r0]
     e76:	6c3b 4000 	sub r19,r3,0
     e7a:	0300      	beq e80 <_Z16actors_main_loopv+0xf8>
     e7c:	1ce2      	mov r0,r7
     e7e:	0d52      	jalr r3
     e80:	021b 04ff 	add r0,r8,-4
     e84:	1952      	jalr r6
     e86:	16cc 2400 	ldr r8,[sp,+0x5]
     e8a:	d1e0      	b e2c <_Z16actors_main_loopv+0xa4>
     e8c:	358b 0132 	mov r1,0x13ac
     e90:	00ef 0402 	mov r0,r8
     e94:	200b 1002 	movt r1,0x0
     e98:	0552      	jalr r1
     e9a:	290b 00c2 	mov r1,0xc48
     e9e:	1ce2      	mov r0,r7
     ea0:	200b 1002 	movt r1,0x0
     ea4:	0552      	jalr r1
     ea6:	f0e0      	b e86 <_Z16actors_main_loopv+0xfe>
     ea8:	0d4b 0192 	mov r0,0x196a
     eac:	000b 1002 	movt r0,0x0
     eb0:	1552      	jalr r5
     eb2:	070b 2142 	mov r8,0x1438
     eb6:	e70b 01c2 	mov r7,0x1c38
     eba:	420b 2192 	mov r10,0x1910
     ebe:	7feb 2ff2 	mov r11,0xffff
     ec2:	000b 3002 	movt r8,0x0
     ec6:	e00b 1002 	movt r7,0x0
     eca:	27eb 2002 	mov r9,0x3f
     ece:	400b 3002 	movt r10,0x0
     ed2:	61eb 3002 	movt r11,0xf
     ed6:	2d0b 0192 	mov r1,0x1968
     eda:	200b 1002 	movt r1,0x0
     ede:	20ba      	sub r1,r0,r1
     ee0:	6308 ffff 	beq da6 <_Z16actors_main_loopv+0x1e>
     ee4:	4033      	sub r2,r0,0
     ee6:	0400      	beq eee <_Z16actors_main_loopv+0x166>
     ee8:	021b 40ff 	add r16,r0,-4
     eec:	03e0      	b ef2 <_Z16actors_main_loopv+0x16a>
     eee:	000b 4002 	mov r16,0x0
     ef2:	811b 2000 	add ip,r0,2
     ef6:	95dc 2400 	str ip,[sp,+0x3]
     efa:	021b 0802 	add r0,r16,20
     efe:	165c 4400 	str r16,[sp,+0x4]
     f02:	015f 0402 	jalr r8
     f06:	005a      	and r0,r0,r0
     f08:	95cc 2400 	ldr ip,[sp,+0x3]
     f0c:	164c 4400 	ldr r16,[sp,+0x4]
     f10:	4f00      	beq fae <_Z16actors_main_loopv+0x226>
     f12:	2144      	ldr r1,[r0,0x2]
     f14:	5c24      	ldrh r2,[r7]
     f16:	2686      	lsr r1,r1,0x14
     f18:	04ce      	asr r0,r1,0x6
     f1a:	600b 0002 	mov r3,0x0
     f1e:	413a      	sub r2,r0,r2
     f20:	610b 1002 	movt r3,0x8
     f24:	1da4      	ldrh r0,[r7,0x3]
     f26:	0392      	gid
     f28:	211f 4002 	movfs r17,config
     f2c:	25ff 480a 	orr r17,r17,r3
     f30:	210f 4002 	movts config,r17
     f34:	0192      	gie
     f36:	0392      	gid
     f38:	611f 4002 	movfs r19,config
     f3c:	6dff 480a 	orr r19,r19,r3
     f40:	610f 4002 	movts config,r19
     f44:	0192      	gie
     f46:	0827      	fmul r0,r2,r0
     f48:	64df 008a 	and r3,r1,r9
     f4c:	5ca4      	ldrh r2,[r7,0x1]
     f4e:	4d3a      	sub r2,r3,r2
     f50:	2696      	lsl r1,r1,0x14
     f52:	411a      	add r2,r0,r2
     f54:	400b 1002 	movt r2,0x0
     f58:	4856      	lsl r2,r2,0x2
     f5a:	491f 040a 	add r2,r10,r2
     f5e:	49df 008a 	and r2,r2,r11
     f62:	28fa      	orr r1,r2,r1
     f64:	045c 4000 	str r16,[r1]
     f68:	3fcb 0ff2 	mov r1,0xfffe
     f6c:	10ef 0402 	mov r0,ip
     f70:	3e2b 1ff2 	movt r1,0xfff1
     f74:	0392      	gid
     f76:	611f 4002 	movfs r19,config
     f7a:	6e0f 480a 	eor r19,r19,r4
     f7e:	6cdf 480a 	and r19,r19,r1
     f82:	6e0f 480a 	eor r19,r19,r4
     f86:	610f 4002 	movts config,r19
     f8a:	0192      	gie
     f8c:	0392      	gid
     f8e:	211f 4002 	movfs r17,config
     f92:	260f 480a 	eor r17,r17,r4
     f96:	24df 480a 	and r17,r17,r1
     f9a:	260f 480a 	eor r17,r17,r4
     f9e:	210f 4002 	movts config,r17
     fa2:	0192      	gie
     fa4:	1552      	jalr r5
     fa6:	98e0      	b ed6 <_Z16actors_main_loopv+0x14e>
     fa8:	01cc 0400 	ldr r0,[r8,+0x3]
     fac:	02e0      	b fb0 <_Z16actors_main_loopv+0x228>
     fae:	01c4      	ldr r0,[r0,0x3]
     fb0:	188b 00c2 	mov r0,0xcc4
     fb4:	000b 18e2 	movt r0,0x8e00
     fb8:	0152      	jalr r0
     fba:	01a2      	nop

00000fbc <_Z17wait_for_got_irq2v>:
     fbc:	f55c 2700 	str fp,[sp],-0x2
     fc0:	f4ef 2402 	mov fp,sp
     fc4:	1c0b 01b2 	mov r0,0x1be0
     fc8:	000b 1002 	movt r0,0x0
     fcc:	01cc 0001 	ldr r0,[r0,+0xb]
     fd0:	2033      	sub r1,r0,0
     fd2:	0210      	bne fd6 <_Z17wait_for_got_irq2v+0x1a>
     fd4:	f8e0      	b fc4 <_Z17wait_for_got_irq2v+0x8>
     fd6:	01a2      	nop
     fd8:	f54c 2400 	ldr fp,[sp,+0x2]
     fdc:	b41b 2401 	add sp,sp,8
     fe0:	194f 0402 	rts

00000fe4 <bjk_send_irq>:
     fe4:	f75c 2700 	str fp,[sp],-0x6
     fe8:	f4ef 2402 	mov fp,sp
     fec:	1f3c 0400 	strh r0,[fp,+0x6]
     ff0:	04e2      	mov r0,r1
     ff2:	1e3c 0400 	strh r0,[fp,+0x4]
     ff6:	1f2c 0400 	ldrh r0,[fp,+0x6]
     ffa:	2296      	lsl r1,r0,0x14
     ffc:	5e2c 0400 	ldrh r2,[fp,+0x4]
    1000:	100b 0192 	mov r0,0x1980
    1004:	000b 1002 	movt r0,0x0
    1008:	081a      	add r0,r2,r0
    100a:	40e2      	mov r2,r0
    100c:	1feb 0ff2 	mov r0,0xffff
    1010:	01eb 1002 	movt r0,0xf
    1014:	085a      	and r0,r2,r0
    1016:	047a      	orr r0,r1,r0
    1018:	1edc 0400 	str r0,[fp,+0x5]
    101c:	1ecc 0400 	ldr r0,[fp,+0x5]
    1020:	3feb 0ff2 	mov r1,0xffff
    1024:	2014      	strb r1,[r0]
    1026:	1ecc 0400 	ldr r0,[fp,+0x5]
    102a:	0004      	ldrb r0,[r0]
    102c:	23bb 001f 	sub r1,r0,255
    1030:	0200      	beq 1034 <_HALF_BANK_SIZE_+0x34>
    1032:	fae0      	b 1026 <_HALF_BANK_SIZE_+0x26>
    1034:	1f2c 0400 	ldrh r0,[fp,+0x6]
    1038:	2296      	lsl r1,r0,0x14
    103a:	058b 0042 	mov r0,0x42c
    103e:	01eb 1002 	movt r0,0xf
    1042:	047a      	orr r0,r1,r0
    1044:	1e5c 0400 	str r0,[fp,+0x4]
    1048:	1e2c 0400 	ldrh r0,[fp,+0x4]
    104c:	2023      	mov r1,0x1
    104e:	042a      	lsl r0,r1,r0
    1050:	20e2      	mov r1,r0
    1052:	1e4c 0400 	ldr r0,[fp,+0x4]
    1056:	2054      	str r1,[r0]
    1058:	01a2      	nop
    105a:	f74c 2400 	ldr fp,[sp,+0x6]
    105e:	b41b 2403 	add sp,sp,24
    1062:	194f 0402 	rts
    1066:	01a2      	nop

00001068 <_Z41__static_initialization_and_destruction_0ii>:
    1068:	d57c 2700 	strd lr,[sp],-0x2
    106c:	f41b 2402 	add fp,sp,16
    1070:	1cdc 0500 	str r0,[fp,-0x1]
    1074:	3d5c 0500 	str r1,[fp,-0x2]
    1078:	1ccc 0500 	ldr r0,[fp,-0x1]
    107c:	20b3      	sub r1,r0,1
    107e:	d918 0000 	bne 1230 <_Z41__static_initialization_and_destruction_0ii+0x1c8>
    1082:	3d4c 0500 	ldr r1,[fp,-0x2]
    1086:	1feb 0ff2 	mov r0,0xffff
    108a:	443a      	sub r2,r1,r0
    108c:	d218 0000 	bne 1230 <_Z41__static_initialization_and_destruction_0ii+0x1c8>
    1090:	1b8b 0182 	mov r0,0x18dc
    1094:	000b 1002 	movt r0,0x0
    1098:	318b 0122 	mov r1,0x128c
    109c:	200b 1002 	movt r1,0x0
    10a0:	0552      	jalr r1
    10a2:	5b0b 0182 	mov r2,0x18d8
    10a6:	400b 1002 	movt r2,0x0
    10aa:	3b8b 0182 	mov r1,0x18dc
    10ae:	200b 1002 	movt r1,0x0
    10b2:	1a8b 0122 	mov r0,0x12d4
    10b6:	000b 1002 	movt r0,0x0
    10ba:	6a8b 0262 	mov r3,0x2654
    10be:	600b 18e2 	movt r3,0x8e00
    10c2:	0d52      	jalr r3
    10c4:	1c0b 0182 	mov r0,0x18e0
    10c8:	000b 1002 	movt r0,0x0
    10cc:	318b 0122 	mov r1,0x128c
    10d0:	200b 1002 	movt r1,0x0
    10d4:	0552      	jalr r1
    10d6:	5b0b 0182 	mov r2,0x18d8
    10da:	400b 1002 	movt r2,0x0
    10de:	3c0b 0182 	mov r1,0x18e0
    10e2:	200b 1002 	movt r1,0x0
    10e6:	1a8b 0122 	mov r0,0x12d4
    10ea:	000b 1002 	movt r0,0x0
    10ee:	6a8b 0262 	mov r3,0x2654
    10f2:	600b 18e2 	movt r3,0x8e00
    10f6:	0d52      	jalr r3
    10f8:	1c8b 0182 	mov r0,0x18e4
    10fc:	000b 1002 	movt r0,0x0
    1100:	318b 0122 	mov r1,0x128c
    1104:	200b 1002 	movt r1,0x0
    1108:	0552      	jalr r1
    110a:	5b0b 0182 	mov r2,0x18d8
    110e:	400b 1002 	movt r2,0x0
    1112:	3c8b 0182 	mov r1,0x18e4
    1116:	200b 1002 	movt r1,0x0
    111a:	1a8b 0122 	mov r0,0x12d4
    111e:	000b 1002 	movt r0,0x0
    1122:	6a8b 0262 	mov r3,0x2654
    1126:	600b 18e2 	movt r3,0x8e00
    112a:	0d52      	jalr r3
    112c:	1d0b 0182 	mov r0,0x18e8
    1130:	000b 1002 	movt r0,0x0
    1134:	318b 0122 	mov r1,0x128c
    1138:	200b 1002 	movt r1,0x0
    113c:	0552      	jalr r1
    113e:	5b0b 0182 	mov r2,0x18d8
    1142:	400b 1002 	movt r2,0x0
    1146:	3d0b 0182 	mov r1,0x18e8
    114a:	200b 1002 	movt r1,0x0
    114e:	1a8b 0122 	mov r0,0x12d4
    1152:	000b 1002 	movt r0,0x0
    1156:	6a8b 0262 	mov r3,0x2654
    115a:	600b 18e2 	movt r3,0x8e00
    115e:	0d52      	jalr r3
    1160:	0c0b 0192 	mov r0,0x1960
    1164:	000b 1002 	movt r0,0x0
    1168:	318b 0122 	mov r1,0x128c
    116c:	200b 1002 	movt r1,0x0
    1170:	0552      	jalr r1
    1172:	5b0b 0182 	mov r2,0x18d8
    1176:	400b 1002 	movt r2,0x0
    117a:	2c0b 0192 	mov r1,0x1960
    117e:	200b 1002 	movt r1,0x0
    1182:	1a8b 0122 	mov r0,0x12d4
    1186:	000b 1002 	movt r0,0x0
    118a:	6a8b 0262 	mov r3,0x2654
    118e:	600b 18e2 	movt r3,0x8e00
    1192:	0d52      	jalr r3
    1194:	0c8b 0192 	mov r0,0x1964
    1198:	000b 1002 	movt r0,0x0
    119c:	318b 0122 	mov r1,0x128c
    11a0:	200b 1002 	movt r1,0x0
    11a4:	0552      	jalr r1
    11a6:	5b0b 0182 	mov r2,0x18d8
    11aa:	400b 1002 	movt r2,0x0
    11ae:	2c8b 0192 	mov r1,0x1964
    11b2:	200b 1002 	movt r1,0x0
    11b6:	1a8b 0122 	mov r0,0x12d4
    11ba:	000b 1002 	movt r0,0x0
    11be:	6a8b 0262 	mov r3,0x2654
    11c2:	600b 18e2 	movt r3,0x8e00
    11c6:	0d52      	jalr r3
    11c8:	0d0b 0192 	mov r0,0x1968
    11cc:	000b 1002 	movt r0,0x0
    11d0:	318b 0122 	mov r1,0x128c
    11d4:	200b 1002 	movt r1,0x0
    11d8:	0552      	jalr r1
    11da:	5b0b 0182 	mov r2,0x18d8
    11de:	400b 1002 	movt r2,0x0
    11e2:	2d0b 0192 	mov r1,0x1968
    11e6:	200b 1002 	movt r1,0x0
    11ea:	1a8b 0122 	mov r0,0x12d4
    11ee:	000b 1002 	movt r0,0x0
    11f2:	6a8b 0262 	mov r3,0x2654
    11f6:	600b 18e2 	movt r3,0x8e00
    11fa:	0d52      	jalr r3
    11fc:	0d8b 0192 	mov r0,0x196c
    1200:	000b 1002 	movt r0,0x0
    1204:	318b 0122 	mov r1,0x128c
    1208:	200b 1002 	movt r1,0x0
    120c:	0552      	jalr r1
    120e:	5b0b 0182 	mov r2,0x18d8
    1212:	400b 1002 	movt r2,0x0
    1216:	2d8b 0192 	mov r1,0x196c
    121a:	200b 1002 	movt r1,0x0
    121e:	1a8b 0122 	mov r0,0x12d4
    1222:	000b 1002 	movt r0,0x0
    1226:	6a8b 0262 	mov r3,0x2654
    122a:	600b 18e2 	movt r3,0x8e00
    122e:	0d52      	jalr r3
    1230:	01a2      	nop
    1232:	d56c 2400 	ldrd lr,[sp,+0x2]
    1236:	b41b 2402 	add sp,sp,16
    123a:	194f 0402 	rts
    123e:	01a2      	nop

00001240 <_GLOBAL__sub_I___cxa_atexit>:
    1240:	d4fc 2700 	strd lr,[sp],-0x1
    1244:	f41b 2401 	add fp,sp,8
    1248:	3feb 0ff2 	mov r1,0xffff
    124c:	0023      	mov r0,0x1
    124e:	4d0b 0102 	mov r2,0x1068
    1252:	400b 1002 	movt r2,0x0
    1256:	0952      	jalr r2
    1258:	d4ec 2400 	ldrd lr,[sp,+0x1]
    125c:	b41b 2401 	add sp,sp,8
    1260:	194f 0402 	rts

00001264 <_ZN11missive_ref16init_missive_refEv.isra.1>:
    1264:	2003      	mov r1,0x0
    1266:	2054      	str r1,[r0]
    1268:	194f 0402 	rts

0000126c <_ZnwmPv>:
    126c:	f65c 2700 	str fp,[sp],-0x4
    1270:	f4ef 2402 	mov fp,sp
    1274:	1ddc 0400 	str r0,[fp,+0x3]
    1278:	3d5c 0400 	str r1,[fp,+0x2]
    127c:	1d4c 0400 	ldr r0,[fp,+0x2]
    1280:	f64c 2400 	ldr fp,[sp,+0x4]
    1284:	b41b 2402 	add sp,sp,16
    1288:	194f 0402 	rts

0000128c <_ZN6binderC1Ev>:
    128c:	d57c 2700 	strd lr,[sp],-0x2
    1290:	f41b 2402 	add fp,sp,16
    1294:	1cdc 0500 	str r0,[fp,-0x1]
    1298:	1ccc 0500 	ldr r0,[fp,-0x1]
    129c:	3c0b 0162 	mov r1,0x16e0
    12a0:	200b 1002 	movt r1,0x0
    12a4:	0552      	jalr r1
    12a6:	1ccc 0500 	ldr r0,[fp,-0x1]
    12aa:	0113      	add r0,r0,2
    12ac:	3c0b 0162 	mov r1,0x16e0
    12b0:	200b 1002 	movt r1,0x0
    12b4:	0552      	jalr r1
    12b6:	1ccc 0500 	ldr r0,[fp,-0x1]
    12ba:	218b 0132 	mov r1,0x130c
    12be:	200b 1002 	movt r1,0x0
    12c2:	0552      	jalr r1
    12c4:	01a2      	nop
    12c6:	d56c 2400 	ldrd lr,[sp,+0x2]
    12ca:	b41b 2402 	add sp,sp,16
    12ce:	194f 0402 	rts
    12d2:	01a2      	nop

000012d4 <_ZN6binderD1Ev>:
    12d4:	d57c 2700 	strd lr,[sp],-0x2
    12d8:	f41b 2402 	add fp,sp,16
    12dc:	1cdc 0500 	str r0,[fp,-0x1]
    12e0:	1ccc 0500 	ldr r0,[fp,-0x1]
    12e4:	0113      	add r0,r0,2
    12e6:	208b 0172 	mov r1,0x1704
    12ea:	200b 1002 	movt r1,0x0
    12ee:	0552      	jalr r1
    12f0:	1ccc 0500 	ldr r0,[fp,-0x1]
    12f4:	208b 0172 	mov r1,0x1704
    12f8:	200b 1002 	movt r1,0x0
    12fc:	0552      	jalr r1
    12fe:	01a2      	nop
    1300:	d56c 2400 	ldrd lr,[sp,+0x2]
    1304:	b41b 2402 	add sp,sp,16
    1308:	194f 0402 	rts

0000130c <_ZN6binder11init_binderEv>:
    130c:	967c 0700 	strd r4,[sp],-0x4
    1310:	d5fc 0400 	strd r6,[sp,+0x3]
    1314:	e50b 0172 	mov r7,0x1728
    1318:	d57c 2400 	strd lr,[sp,+0x2]
    131c:	80e2      	mov r4,r0
    131e:	20e2      	mov r1,r0
    1320:	e00b 1002 	movt r7,0x0
    1324:	171b 0401 	add r0,sp,14
    1328:	1d52      	jalr r7
    132a:	cc8b 0172 	mov r6,0x1764
    132e:	371b 0401 	add r1,sp,14
    1332:	c00b 1002 	movt r6,0x0
    1336:	10e2      	mov r0,r4
    1338:	1952      	jalr r6
    133a:	a08b 0172 	mov r5,0x1704
    133e:	171b 0401 	add r0,sp,14
    1342:	a00b 1002 	movt r5,0x0
    1346:	1552      	jalr r5
    1348:	30e2      	mov r1,r4
    134a:	171b 0401 	add r0,sp,14
    134e:	1d52      	jalr r7
    1350:	371b 0401 	add r1,sp,14
    1354:	1113      	add r0,r4,2
    1356:	1952      	jalr r6
    1358:	171b 0401 	add r0,sp,14
    135c:	1552      	jalr r5
    135e:	d5ec 0400 	ldrd r6,[sp,+0x3]
    1362:	d56c 2400 	ldrd lr,[sp,+0x2]
    1366:	b41b 2404 	add sp,sp,32
    136a:	946c 0400 	ldrd r4,[sp,+0x0]
    136e:	194f 0402 	rts
    1372:	01a2      	nop

00001374 <_ZN6binder8is_aloneEv>:
    1374:	957c 0700 	strd r4,[sp],-0x2
    1378:	ad8b 0172 	mov r5,0x176c
    137c:	d4fc 2400 	strd lr,[sp,+0x1]
    1380:	a00b 1002 	movt r5,0x0
    1384:	80e2      	mov r4,r0
    1386:	1552      	jalr r5
    1388:	303a      	sub r1,r4,r0
    138a:	0810      	bne 139a <_ZN6binder8is_aloneEv+0x26>
    138c:	1113      	add r0,r4,2
    138e:	1552      	jalr r5
    1390:	303a      	sub r1,r4,r0
    1392:	2003      	mov r1,0x0
    1394:	0023      	mov r0,0x1
    1396:	0412      	movne r0,r1
    1398:	02e0      	b 139c <_ZN6binder8is_aloneEv+0x28>
    139a:	0003      	mov r0,0x0
    139c:	d4ec 2400 	ldrd lr,[sp,+0x1]
    13a0:	b41b 2402 	add sp,sp,16
    13a4:	946c 0400 	ldrd r4,[sp,+0x0]
    13a8:	194f 0402 	rts

000013ac <_ZN6binder6let_goEv>:
    13ac:	96fc 0700 	strd r4,[sp],-0x5
    13b0:	d67c 0400 	strd r6,[sp,+0x4]
    13b4:	f00b 0172 	mov r7,0x1780
    13b8:	d57c 2400 	strd lr,[sp,+0x2]
    13bc:	17dc 2400 	str r8,[sp,+0x7]
    13c0:	e00b 1002 	movt r7,0x0
    13c4:	80e2      	mov r4,r0
    13c6:	1d52      	jalr r7
    13c8:	d113      	add r6,r4,2
    13ca:	ac8b 0172 	mov r5,0x1764
    13ce:	a00b 1002 	movt r5,0x0
    13d2:	38e2      	mov r1,r6
    13d4:	0113      	add r0,r0,2
    13d6:	1552      	jalr r5
    13d8:	18e2      	mov r0,r6
    13da:	1d52      	jalr r7
    13dc:	30e2      	mov r1,r4
    13de:	1552      	jalr r5
    13e0:	050b 2172 	mov r8,0x1728
    13e4:	30e2      	mov r1,r4
    13e6:	171b 0401 	add r0,sp,14
    13ea:	000b 3002 	movt r8,0x0
    13ee:	015f 0402 	jalr r8
    13f2:	371b 0401 	add r1,sp,14
    13f6:	10e2      	mov r0,r4
    13f8:	1552      	jalr r5
    13fa:	e08b 0172 	mov r7,0x1704
    13fe:	171b 0401 	add r0,sp,14
    1402:	e00b 1002 	movt r7,0x0
    1406:	1d52      	jalr r7
    1408:	30e2      	mov r1,r4
    140a:	171b 0401 	add r0,sp,14
    140e:	015f 0402 	jalr r8
    1412:	371b 0401 	add r1,sp,14
    1416:	18e2      	mov r0,r6
    1418:	1552      	jalr r5
    141a:	171b 0401 	add r0,sp,14
    141e:	1d52      	jalr r7
    1420:	d66c 0400 	ldrd r6,[sp,+0x4]
    1424:	17cc 2400 	ldr r8,[sp,+0x7]
    1428:	d56c 2400 	ldrd lr,[sp,+0x2]
    142c:	b41b 2405 	add sp,sp,40
    1430:	946c 0400 	ldrd r4,[sp,+0x0]
    1434:	194f 0402 	rts

00001438 <_ZN6binder12get_right_ptEv>:
    1438:	2d8b 0172 	mov r1,0x176c
    143c:	0113      	add r0,r0,2
    143e:	200b 1002 	movt r1,0x0
    1442:	0542      	jr r1

00001444 <_ZN6binder15bind_to_my_leftERS_>:
    1444:	96fc 0700 	strd r4,[sp],-0x5
    1448:	d67c 0400 	strd r6,[sp,+0x4]
    144c:	8c8b 0172 	mov r4,0x1764
    1450:	c4e2      	mov r6,r1
    1452:	d57c 2400 	strd lr,[sp,+0x2]
    1456:	a0e2      	mov r5,r0
    1458:	800b 1002 	movt r4,0x0
    145c:	15fc 2400 	strd r8,[sp,+0x3]
    1460:	20e2      	mov r1,r0
    1462:	18e2      	mov r0,r6
    1464:	1152      	jalr r4
    1466:	050b 2172 	mov r8,0x1728
    146a:	000b 3002 	movt r8,0x0
    146e:	34e2      	mov r1,r5
    1470:	171b 0401 	add r0,sp,14
    1474:	015f 0402 	jalr r8
    1478:	371b 0401 	add r1,sp,14
    147c:	1913      	add r0,r6,2
    147e:	1152      	jalr r4
    1480:	e08b 0172 	mov r7,0x1704
    1484:	e00b 1002 	movt r7,0x0
    1488:	171b 0401 	add r0,sp,14
    148c:	1d52      	jalr r7
    148e:	300b 0172 	mov r1,0x1780
    1492:	14e2      	mov r0,r5
    1494:	200b 1002 	movt r1,0x0
    1498:	0552      	jalr r1
    149a:	38e2      	mov r1,r6
    149c:	20ef 2002 	mov r9,r0
    14a0:	171b 0401 	add r0,sp,14
    14a4:	015f 0402 	jalr r8
    14a8:	371b 0401 	add r1,sp,14
    14ac:	051b 0400 	add r0,r9,2
    14b0:	1152      	jalr r4
    14b2:	171b 0401 	add r0,sp,14
    14b6:	1d52      	jalr r7
    14b8:	38e2      	mov r1,r6
    14ba:	171b 0401 	add r0,sp,14
    14be:	015f 0402 	jalr r8
    14c2:	371b 0401 	add r1,sp,14
    14c6:	14e2      	mov r0,r5
    14c8:	1152      	jalr r4
    14ca:	171b 0401 	add r0,sp,14
    14ce:	1d52      	jalr r7
    14d0:	d66c 0400 	ldrd r6,[sp,+0x4]
    14d4:	15ec 2400 	ldrd r8,[sp,+0x3]
    14d8:	d56c 2400 	ldrd lr,[sp,+0x2]
    14dc:	b41b 2405 	add sp,sp,40
    14e0:	946c 0400 	ldrd r4,[sp,+0x0]
    14e4:	194f 0402 	rts

000014e8 <_ZN5actorC1Ev>:
    14e8:	965c 0700 	str r4,[sp],-0x4
    14ec:	318b 0122 	mov r1,0x128c
    14f0:	80e2      	mov r4,r0
    14f2:	d6dc 2400 	str lr,[sp,+0x5]
    14f6:	f5dc 2400 	str fp,[sp,+0x3]
    14fa:	021b 0000 	add r0,r0,4
    14fe:	200b 1002 	movt r1,0x0
    1502:	0552      	jalr r1
    1504:	188b 0182 	mov r0,0x18c4
    1508:	000b 1002 	movt r0,0x0
    150c:	1054      	str r0,[r4]
    150e:	258b 0152 	mov r1,0x152c
    1512:	10e2      	mov r0,r4
    1514:	d6cc 2400 	ldr lr,[sp,+0x5]
    1518:	964c 0400 	ldr r4,[sp,+0x4]
    151c:	f5cc 2400 	ldr fp,[sp,+0x3]
    1520:	200b 1002 	movt r1,0x0
    1524:	b41b 2402 	add sp,sp,16
    1528:	0542      	jr r1
    152a:	01a2      	nop

0000152c <_ZN5actor10init_actorEv>:
    152c:	2003      	mov r1,0x0
    152e:	201c 0001 	strb r1,[r0,+0x8]
    1532:	209c 0001 	strb r1,[r0,+0x9]
    1536:	194f 0402 	rts
    153a:	01a2      	nop

0000153c <_ZN5actor12get_actor_idEv>:
    153c:	134b 0172 	mov r0,0x179a
    1540:	000b 1002 	movt r0,0x0
    1544:	0004      	ldrb r0,[r0]
    1546:	194f 0402 	rts
    154a:	01a2      	nop

0000154c <_ZN5actor13get_availableEv>:
    154c:	1b8b 0182 	mov r0,0x18dc
    1550:	000b 1002 	movt r0,0x0
    1554:	194f 0402 	rts

00001558 <_ZN5actor7releaseEv>:
    1558:	957c 0700 	strd r4,[sp],-0x2
    155c:	358b 0132 	mov r1,0x13ac
    1560:	a21b 0000 	add r5,r0,4
    1564:	d4fc 2400 	strd lr,[sp,+0x1]
    1568:	80e2      	mov r4,r0
    156a:	200b 1002 	movt r1,0x0
    156e:	14e2      	mov r0,r5
    1570:	0552      	jalr r1
    1572:	1044      	ldr r0,[r4]
    1574:	20c4      	ldr r1,[r0,0x1]
    1576:	10e2      	mov r0,r4
    1578:	0552      	jalr r1
    157a:	d4ec 2400 	ldrd lr,[sp,+0x1]
    157e:	b41b 2402 	add sp,sp,16
    1582:	34e2      	mov r1,r5
    1584:	488b 0142 	mov r2,0x1444
    1588:	946c 0400 	ldrd r4,[sp,+0x0]
    158c:	400b 1002 	movt r2,0x0
    1590:	0942      	jr r2
    1592:	01a2      	nop

00001594 <_ZN5actor14get_class_nameEv>:
    1594:	d4fc 2700 	strd lr,[sp],-0x1
    1598:	2044      	ldr r1,[r0]
    159a:	2444      	ldr r1,[r1]
    159c:	0552      	jalr r1
    159e:	223b 0000 	sub r1,r0,4
    15a2:	0820      	bgtu 15b2 <_ZN5actor14get_class_nameEv+0x1e>
    15a4:	3e0b 0182 	mov r1,0x18f0
    15a8:	0056      	lsl r0,r0,0x2
    15aa:	200b 1002 	movt r1,0x0
    15ae:	0441      	ldr r0,[r1,r0]
    15b0:	02e0      	b 15b4 <_ZN5actor14get_class_nameEv+0x20>
    15b2:	0003      	mov r0,0x0
    15b4:	b41b 2401 	add sp,sp,8
    15b8:	d46c 2400 	ldrd lr,[sp,+0x0]
    15bc:	194f 0402 	rts

000015c0 <_ZN7missiveC1Ev>:
    15c0:	965c 0700 	str r4,[sp],-0x4
    15c4:	3d0b 0142 	mov r1,0x14e8
    15c8:	d6dc 2400 	str lr,[sp,+0x5]
    15cc:	f5dc 2400 	str fp,[sp,+0x3]
    15d0:	200b 1002 	movt r1,0x0
    15d4:	80e2      	mov r4,r0
    15d6:	0552      	jalr r1
    15d8:	160b 0182 	mov r0,0x18b0
    15dc:	000b 1002 	movt r0,0x0
    15e0:	1054      	str r0,[r4]
    15e2:	200b 0162 	mov r1,0x1600
    15e6:	10e2      	mov r0,r4
    15e8:	d6cc 2400 	ldr lr,[sp,+0x5]
    15ec:	964c 0400 	ldr r4,[sp,+0x4]
    15f0:	f5cc 2400 	ldr fp,[sp,+0x3]
    15f4:	200b 1002 	movt r1,0x0
    15f8:	b41b 2402 	add sp,sp,16
    15fc:	0542      	jr r1
    15fe:	01a2      	nop

00001600 <_ZN7missive12init_missiveEv>:
    1600:	2003      	mov r1,0x0
    1602:	21d4      	str r1,[r0,0x3]
    1604:	2254      	str r1,[r0,0x4]
    1606:	194f 0402 	rts
    160a:	01a2      	nop

0000160c <_ZN7missive12get_actor_idEv>:
    160c:	136b 0172 	mov r0,0x179b
    1610:	000b 1002 	movt r0,0x0
    1614:	0004      	ldrb r0,[r0]
    1616:	194f 0402 	rts
    161a:	01a2      	nop

0000161c <_ZN7missive13get_availableEv>:
    161c:	1c0b 0182 	mov r0,0x18e0
    1620:	000b 1002 	movt r0,0x0
    1624:	194f 0402 	rts

00001628 <_ZN11missive_grpC1Ev>:
    1628:	965c 0700 	str r4,[sp],-0x4
    162c:	380b 0152 	mov r1,0x15c0
    1630:	d6dc 2400 	str lr,[sp,+0x5]
    1634:	f5dc 2400 	str fp,[sp,+0x3]
    1638:	200b 1002 	movt r1,0x0
    163c:	80e2      	mov r4,r0
    163e:	0552      	jalr r1
    1640:	338b 0182 	mov r1,0x189c
    1644:	10e2      	mov r0,r4
    1646:	200b 1002 	movt r1,0x0
    164a:	22dc 0200 	str r1,[r0],+0x5
    164e:	d6cc 2400 	ldr lr,[sp,+0x5]
    1652:	318b 0122 	mov r1,0x128c
    1656:	964c 0400 	ldr r4,[sp,+0x4]
    165a:	f5cc 2400 	ldr fp,[sp,+0x3]
    165e:	200b 1002 	movt r1,0x0
    1662:	b41b 2402 	add sp,sp,16
    1666:	0542      	jr r1

00001668 <_ZN11missive_grp12get_actor_idEv>:
    1668:	13ab 0172 	mov r0,0x179d
    166c:	000b 1002 	movt r0,0x0
    1670:	0004      	ldrb r0,[r0]
    1672:	194f 0402 	rts
    1676:	01a2      	nop

00001678 <_ZN11missive_grp13get_availableEv>:
    1678:	1d0b 0182 	mov r0,0x18e8
    167c:	000b 1002 	movt r0,0x0
    1680:	194f 0402 	rts

00001684 <_ZN11missive_refC1Ev>:
    1684:	965c 0700 	str r4,[sp],-0x4
    1688:	3d0b 0142 	mov r1,0x14e8
    168c:	d6dc 2400 	str lr,[sp,+0x5]
    1690:	f5dc 2400 	str fp,[sp,+0x3]
    1694:	200b 1002 	movt r1,0x0
    1698:	80e2      	mov r4,r0
    169a:	0552      	jalr r1
    169c:	310b 0182 	mov r1,0x1888
    16a0:	10e2      	mov r0,r4
    16a2:	200b 1002 	movt r1,0x0
    16a6:	21dc 0200 	str r1,[r0],+0x3
    16aa:	d6cc 2400 	ldr lr,[sp,+0x5]
    16ae:	2c8b 0122 	mov r1,0x1264
    16b2:	964c 0400 	ldr r4,[sp,+0x4]
    16b6:	f5cc 2400 	ldr fp,[sp,+0x3]
    16ba:	200b 1002 	movt r1,0x0
    16be:	b41b 2402 	add sp,sp,16
    16c2:	0542      	jr r1

000016c4 <_ZN11missive_ref12get_actor_idEv>:
    16c4:	138b 0172 	mov r0,0x179c
    16c8:	000b 1002 	movt r0,0x0
    16cc:	0004      	ldrb r0,[r0]
    16ce:	194f 0402 	rts
    16d2:	01a2      	nop

000016d4 <_ZN11missive_ref13get_availableEv>:
    16d4:	1c8b 0182 	mov r0,0x18e4
    16d8:	000b 1002 	movt r0,0x0
    16dc:	194f 0402 	rts

000016e0 <_ZN4kptrI6binderLZ19BINDER_BASE_POINTEREEC1Ev>:
    16e0:	f65c 2700 	str fp,[sp],-0x4
    16e4:	f4ef 2402 	mov fp,sp
    16e8:	1ddc 0400 	str r0,[fp,+0x3]
    16ec:	1dcc 0400 	ldr r0,[fp,+0x3]
    16f0:	2003      	mov r1,0x0
    16f2:	2034      	strh r1,[r0]
    16f4:	01a2      	nop
    16f6:	f64c 2400 	ldr fp,[sp,+0x4]
    16fa:	b41b 2402 	add sp,sp,16
    16fe:	194f 0402 	rts
    1702:	01a2      	nop

00001704 <_ZN4kptrI6binderLZ19BINDER_BASE_POINTEREED1Ev>:
    1704:	f65c 2700 	str fp,[sp],-0x4
    1708:	f4ef 2402 	mov fp,sp
    170c:	1ddc 0400 	str r0,[fp,+0x3]
    1710:	1dcc 0400 	ldr r0,[fp,+0x3]
    1714:	2003      	mov r1,0x0
    1716:	2034      	strh r1,[r0]
    1718:	01a2      	nop
    171a:	f64c 2400 	ldr fp,[sp,+0x4]
    171e:	b41b 2402 	add sp,sp,16
    1722:	194f 0402 	rts
    1726:	01a2      	nop

00001728 <_ZN4kptrI6binderLZ19BINDER_BASE_POINTEREEC1EPS0_>:
    1728:	f65c 2700 	str fp,[sp],-0x4
    172c:	f4ef 2402 	mov fp,sp
    1730:	1ddc 0400 	str r0,[fp,+0x3]
    1734:	3d5c 0400 	str r1,[fp,+0x2]
    1738:	1d4c 0400 	ldr r0,[fp,+0x2]
    173c:	3a0b 0182 	mov r1,0x18d0
    1740:	200b 1002 	movt r1,0x0
    1744:	2444      	ldr r1,[r1]
    1746:	00ba      	sub r0,r0,r1
    1748:	20e2      	mov r1,r0
    174a:	200b 1002 	movt r1,0x0
    174e:	1dcc 0400 	ldr r0,[fp,+0x3]
    1752:	2034      	strh r1,[r0]
    1754:	01a2      	nop
    1756:	f64c 2400 	ldr fp,[sp,+0x4]
    175a:	b41b 2402 	add sp,sp,16
    175e:	194f 0402 	rts
    1762:	01a2      	nop

00001764 <_ZN4kptrI6binderLZ19BINDER_BASE_POINTEREEaSERKS1_>:
    1764:	2424      	ldrh r1,[r1]
    1766:	2034      	strh r1,[r0]
    1768:	194f 0402 	rts

0000176c <_ZNK4kptrI6binderLZ19BINDER_BASE_POINTEREEcvPS0_Ev>:
    176c:	3a0b 0182 	mov r1,0x18d0
    1770:	200b 1002 	movt r1,0x0
    1774:	2444      	ldr r1,[r1]
    1776:	0024      	ldrh r0,[r0]
    1778:	041a      	add r0,r1,r0
    177a:	194f 0402 	rts
    177e:	01a2      	nop

00001780 <_ZN4kptrI6binderLZ19BINDER_BASE_POINTEREEptEv>:
    1780:	3a0b 0182 	mov r1,0x18d0
    1784:	200b 1002 	movt r1,0x0
    1788:	2444      	ldr r1,[r1]
    178a:	0024      	ldrh r0,[r0]
    178c:	041a      	add r0,r1,r0
    178e:	194f 0402 	rts
    1792:	01a2      	nop

Disassembly of section .ctors:

00001794 <.ctors>:
    1794:	1240      	blteu 17b8 <_ZN11missive_grp12THE_ACTOR_IDE+0x1b>
	...

Disassembly of section .data:

00001798 <umm_numblocks>:
    1798:	0400      	beq 17a0 <_ZN11missive_grp12THE_ACTOR_IDE+0x3>

0000179a <_ZN5actor12THE_ACTOR_IDE>:
    179a:	0201      	ldrb r0,[r0,r4]

0000179b <_ZN7missive12THE_ACTOR_IDE>:
    179b:	0302 0004 	*unknown*

0000179c <_ZN11missive_ref12THE_ACTOR_IDE>:
    179c:	0403      	mov r0,0x20

0000179d <_ZN11missive_grp12THE_ACTOR_IDE>:
    179d:	Address 0x000000000000179d is out of bounds.


Disassembly of section .rodata:

000017a0 <_ZTV11missive_ref-0xe0>:
    17a0:	4946      	lsr r2,r2,0xa
    17a2:	494e      	asr r2,r2,0xa
    17a4:	4853 4445 	*unknown*
    17a8:	2120      	bgtu 17ea <_ZN11missive_grp12THE_ACTOR_IDE+0x4d>
    17aa:	0a21      	ldrh r0,[r2,r4]
    17ac:	0000      	beq 17ac <_ZN11missive_grp12THE_ACTOR_IDE+0xf>
    17ae:	0000      	beq 17ae <_ZN11missive_grp12THE_ACTOR_IDE+0x11>
    17b0:	4f43      	mov r2,0x7a
    17b2:	4552 2820 	*unknown*
    17b6:	2c30      	bgteu 180e <_ZN11missive_grp12THE_ACTOR_IDE+0x71>
    17b8:	2930      	bgteu 180a <_ZN11missive_grp12THE_ACTOR_IDE+0x6d>
    17ba:	7320      	bgtu 18a0 <_ZTV11missive_grp+0xc>
    17bc:	6174      	strd r3,[r0,0x2]
    17be:	7472      	movgte r3,r5
    17c0:	6465      	ldrd r3,[r1],r0
    17c2:	000a      	eor r0,r0,r0
    17c4:	0000      	beq 17c4 <_ZN11missive_grp12THE_ACTOR_IDE+0x27>
    17c6:	0000      	beq 17c6 <_ZN11missive_grp12THE_ACTOR_IDE+0x29>
    17c8:	4f43      	mov r2,0x7a
    17ca:	4552 2820 	*unknown*
    17ce:	2c30      	bgteu 1826 <_ZN11missive_grp12THE_ACTOR_IDE+0x89>
    17d0:	2930      	bgteu 1822 <_ZN11missive_grp12THE_ACTOR_IDE+0x85>
    17d2:	5320      	bgtu 1878 <_ZN11missive_grp12THE_ACTOR_IDE+0xdb>
    17d4:	5741      	ldr r2,[r5,r6]
    17d6:	6320      	bgtu 189c <_ZTV11missive_grp+0x8>
    17d8:	726f 2065 	*unknown*
    17dc:	3028 312c 	bgtu 62703c <_PROG_SIZE_FOR_CORE_+0x52703c>
    17e0:	2029 4e49 	*unknown*
    17e4:	5449 4445 	*unknown*
    17e8:	000a      	eor r0,r0,r0
    17ea:	0000      	beq 17ea <_ZN11missive_grp12THE_ACTOR_IDE+0x4d>
    17ec:	0000      	beq 17ec <_ZN11missive_grp12THE_ACTOR_IDE+0x4f>
    17ee:	0000      	beq 17ee <_ZN11missive_grp12THE_ACTOR_IDE+0x51>
    17f0:	6f67      	fix r3,r3
    17f2:	5f74      	strd r2,[r7,0x6]
    17f4:	7269 3271 	*unknown*
    17f8:	003d 0000 	strh r0,[r0],+r0
    17fc:	0000      	beq 17fc <_ZN11missive_grp12THE_ACTOR_IDE+0x5f>
    17fe:	0000      	beq 17fe <_ZN11missive_grp12THE_ACTOR_IDE+0x61>
    1800:	4f43      	mov r2,0x7a
    1802:	4552 2820 	*unknown*
    1806:	2c30      	bgteu 185e <_ZN11missive_grp12THE_ACTOR_IDE+0xc1>
    1808:	2931      	strh r1,[r2,r2]
    180a:	7320      	bgtu 18f0 <kernel_class_names_arr>
    180c:	6174      	strd r3,[r0,0x2]
    180e:	7472      	movgte r3,r5
    1810:	6465      	ldrd r3,[r1],r0
    1812:	000a      	eor r0,r0,r0
    1814:	0000      	beq 1814 <_ZN11missive_grp12THE_ACTOR_IDE+0x77>
    1816:	0000      	beq 1816 <_ZN11missive_grp12THE_ACTOR_IDE+0x79>
    1818:	4f43      	mov r2,0x7a
    181a:	4552 2820 	*unknown*
    181e:	2c30      	bgteu 1876 <_ZN11missive_grp12THE_ACTOR_IDE+0xd9>
    1820:	2931      	strh r1,[r2,r2]
    1822:	5320      	bgtu 18c8 <_ZTV5actor+0xc>
    1824:	5741      	ldr r2,[r5,r6]
    1826:	6320      	bgtu 18ec <_ZN11missive_grp9AVAILABLEE+0x4>
    1828:	726f 2065 	*unknown*
    182c:	3028 302c 	bgtu 60708c <_PROG_SIZE_FOR_CORE_+0x50708c>
    1830:	2029 4e49 	*unknown*
    1834:	5449 4445 	*unknown*
    1838:	000a      	eor r0,r0,r0
    183a:	0000      	beq 183a <_ZN11missive_grp12THE_ACTOR_IDE+0x9d>
    183c:	0000      	beq 183c <_ZN11missive_grp12THE_ACTOR_IDE+0x9f>
    183e:	0000      	beq 183e <_ZN11missive_grp12THE_ACTOR_IDE+0xa1>
    1840:	4f43      	mov r2,0x7a
    1842:	4552 2820 	*unknown*
    1846:	2c30      	bgteu 189e <_ZTV11missive_grp+0xa>
    1848:	2931      	strh r1,[r2,r2]
    184a:	7320      	bgtu 1930 <kernel_received_arr+0x20>
    184c:	6e65      	ldrd r3,[r3],r4
    184e:	2074      	strd r1,[r0]
    1850:	2031      	strh r1,[r0,r0]
    1852:	7269 3271 	*unknown*
    1856:	000a      	eor r0,r0,r0
    1858:	617b 7463 	*unknown*
    185c:	726f 007d 	*unknown*
    1860:	6d7b 7369 	*unknown*
    1864:	6973 6576 	*unknown*
    1868:	007d 0000 	strd r0,[r0],+r0
    186c:	0000      	beq 186c <_ZN11missive_grp12THE_ACTOR_IDE+0xcf>
    186e:	0000      	beq 186e <_ZN11missive_grp12THE_ACTOR_IDE+0xd1>
    1870:	6d7b 7369 	*unknown*
    1874:	6973 6576 	*unknown*
    1878:	725f 6665 	*unknown*
    187c:	007d 0000 	strd r0,[r0],+r0

00001880 <_ZTV11missive_ref>:
	...
    1888:	16c4      	ldr r0,[r5,0x5]
    188a:	0000      	beq 188a <_ZTV11missive_ref+0xa>
    188c:	16d4      	str r0,[r5,0x5]
    188e:	0000      	beq 188e <_ZTV11missive_ref+0xe>
    1890:	1594      	strb r0,[r5,0x3]
	...

00001894 <_ZTV11missive_grp>:
	...
    189c:	1668 0000 	bgt 18c8 <_ZTV5actor+0xc>
    18a0:	1678 0000 	bgte 18cc <_ZTV5actor+0x10>
    18a4:	1594      	strb r0,[r5,0x3]
	...

000018a8 <_ZTV7missive>:
	...
    18b0:	160c 0000 	ldrb r0,[r5,+0x4]
    18b4:	161c 0000 	strb r0,[r5,+0x4]
    18b8:	1594      	strb r0,[r5,0x3]
	...

000018bc <_ZTV5actor>:
	...
    18c4:	153c 0000 	strh r0,[r5,+0x2]
    18c8:	154c 0000 	ldr r0,[r5,+0x2]
    18cc:	1594      	strb r0,[r5,0x3]
	...

Disassembly of section .bss:

000018d0 <BINDER_BASE_POINTER>:
	...

000018d8 <__dso_handle>:
    18d8:	0000      	beq 18d8 <__dso_handle>
	...

000018dc <_ZN5actor9AVAILABLEE>:
    18dc:	0000      	beq 18dc <_ZN5actor9AVAILABLEE>
	...

000018e0 <_ZN7missive9AVAILABLEE>:
    18e0:	0000      	beq 18e0 <_ZN7missive9AVAILABLEE>
	...

000018e4 <_ZN11missive_ref9AVAILABLEE>:
    18e4:	0000      	beq 18e4 <_ZN11missive_ref9AVAILABLEE>
	...

000018e8 <_ZN11missive_grp9AVAILABLEE>:
	...

000018f0 <kernel_class_names_arr>:
	...

00001908 <kernel_handlers_arr>:
	...

00001910 <kernel_received_arr>:
	...

00001950 <kernel_confirmed_arr>:
	...

00001960 <kernel_in_work>:
    1960:	0000      	beq 1960 <kernel_in_work>
	...

00001964 <kernel_local_work>:
    1964:	0000      	beq 1964 <kernel_local_work>
	...

00001968 <kernel_out_work>:
    1968:	0000      	beq 1968 <kernel_out_work>
	...

0000196c <kernel_sent_work>:
    196c:	0000      	beq 196c <kernel_sent_work>
	...

00001970 <heapInfo>:
	...

00001980 <bjk_irq_act>:
	...

00001990 <bjk_out_str>:
	...

00001b88 <bjk_dbg_call_stack_trace>:
	...

00001bd8 <bjk_trace_err>:
	...

00001be0 <bj_in_core_shd>:
	...

00001c30 <bj_off_core_pt>:
    1c30:	0000      	beq 1c30 <bj_off_core_pt>
	...

00001c34 <bj_write_rrarray>:
    1c34:	0000      	beq 1c34 <bj_write_rrarray>
	...

00001c38 <bj_glb_sys>:
	...

00001c40 <bjk_waiting_host_sync>:
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	4347      	fmsub r2,r0,r6
   2:	3a43      	mov r1,0xd2
   4:	2820      	bgtu 54 <irq9_entry+0x30>
   6:	7045      	ldr r3,[r4],r0
   8:	7069 6168 	*unknown*
   c:	796e      	asr r3,r6,0xb
   e:	7420      	bgtu f6 <irq9_entry+0xd2>
  10:	6f6f 636c 	*unknown*
  14:	6168 6e69 	bgt dcd2d6 <_PROG_SIZE_FOR_CORE_+0xccd2d6>
  18:	3220      	bgtu 7c <irq9_entry+0x58>
  1a:	3130      	bgteu 7c <irq9_entry+0x58>
  1c:	2e36      	lsl r1,r3,0x11
  1e:	3131      	strh r1,[r4,r2]
  20:	2029 2e35 	*unknown*
  24:	2e34      	strh r1,[r3,0x4]
  26:	0030      	bgteu 26 <irq9_entry+0x2>

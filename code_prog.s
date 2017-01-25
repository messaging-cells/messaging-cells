
bin/e_prog_18.elf:     file format elf32-epiphany


Disassembly of section ivt_reset:

00000000 <_start>:
   0:	80e8 0000 	b 100 <normal_start>

Disassembly of section ivt_software_exception:

00000004 <irq1_entry>:
   4:	cee8 0000 	b 1a0 <soft_exception_interruption>

Disassembly of section ivt_page_miss:

00000008 <irq2_entry>:
   8:	e4e8 0000 	b 1d0 <mem_fault_interruption>

Disassembly of section ivt_timer0:

0000000c <irq3_entry>:
   c:	fae8 0000 	b 200 <timer0_interruption>

Disassembly of section ivt_timer1:

00000010 <irq4_entry>:
  10:	10e8 0001 	b 230 <timer1_interruption>

Disassembly of section ivt_message:

00000014 <irq5_entry>:
  14:	26e8 0001 	b 260 <message_interruption>

Disassembly of section ivt_dma0:

00000018 <irq6_entry>:
  18:	3ce8 0001 	b 290 <dma0_interruption>

Disassembly of section ivt_dma1:

0000001c <irq7_entry>:
  1c:	52e8 0001 	b 2c0 <dma1_interruption>

Disassembly of section ivt_wand:

00000020 <irq8_entry>:
  20:	68e8 0001 	b 2f0 <wand_interruption>

Disassembly of section ivt_user:

00000024 <irq9_entry>:
  24:	7ee8 0001 	b 320 <user_interruption>

Disassembly of section workgroup_cfg:

00000028 <workgroup_cfg>:
	...

Disassembly of section ext_mem_cfg:

00000050 <ext_mem_cfg>:
	...

Disassembly of section loader_cfg:

00000058 <loader_cfg>:
	...

Disassembly of section .code_dram:

8e000000 <bjk_init_global>:
8e000000:	d67c 2700 	strd lr,[sp],-0x4
8e000004:	95fc 0400 	strd r4,[sp,+0x3]
8e000008:	f41b 2404 	add fp,sp,32
8e00000c:	a112      	movfs r5,config
8e00000e:	148b 0032 	mov r0,0x3a4
8e000012:	000b 18e2 	movt r0,0x8e00
8e000016:	9fcb 0ff2 	mov r4,0xfffe
8e00001a:	9e2b 1ff2 	movt r4,0xfff1
8e00001e:	0152      	jalr r0
8e000020:	0c0b 0062 	mov r0,0x660
8e000024:	000b 1002 	movt r0,0x0
8e000028:	2003      	mov r1,0x0
8e00002a:	2054      	str r1,[r0]
8e00002c:	0d0b 0062 	mov r0,0x668
8e000030:	000b 1002 	movt r0,0x0
8e000034:	2403      	mov r1,0x20
8e000036:	2034      	strh r1,[r0]
8e000038:	0d0b 0062 	mov r0,0x668
8e00003c:	000b 1002 	movt r0,0x0
8e000040:	2103      	mov r1,0x8
8e000042:	20b4      	strh r1,[r0,0x1]
8e000044:	0d0b 0062 	mov r0,0x668
8e000048:	000b 1002 	movt r0,0x0
8e00004c:	2083      	mov r1,0x4
8e00004e:	2134      	strh r1,[r0,0x2]
8e000050:	0d0b 0062 	mov r0,0x668
8e000054:	000b 1002 	movt r0,0x0
8e000058:	2083      	mov r1,0x4
8e00005a:	21b4      	strh r1,[r0,0x3]
8e00005c:	000b 0002 	mov r0,0x0
8e000060:	000b 18f2 	movt r0,0x8f00
8e000064:	2044      	ldr r1,[r0]
8e000066:	1bab 0cc2 	mov r0,0xccdd
8e00006a:	176b 1aa2 	movt r0,0xaabb
8e00006e:	443a      	sub r2,r1,r0
8e000070:	1000      	beq 8e000090 <bjk_init_global+0x90>
8e000072:	4003      	mov r2,0x0
8e000074:	2003      	mov r1,0x0
8e000076:	002b 0eb2 	mov r0,0xeb01
8e00007a:	15ab 1de2 	movt r0,0xdead
8e00007e:	650b 0062 	mov r3,0x628
8e000082:	600b 18e2 	movt r3,0x8e00
8e000086:	9fcb 0ff2 	mov r4,0xfffe
8e00008a:	9e2b 1ff2 	movt r4,0xfff1
8e00008e:	0d52      	jalr r3
8e000090:	0003      	mov r0,0x0
8e000092:	1ebc 0500 	strh r0,[fp,-0x5]
8e000096:	051f 0032 	movfs r0,coreid
8e00009a:	1ebc 0500 	strh r0,[fp,-0x5]
8e00009e:	1eac 0500 	ldrh r0,[fp,-0x5]
8e0000a2:	1fbc 0500 	strh r0,[fp,-0x7]
8e0000a6:	4103      	mov r2,0x8
8e0000a8:	2003      	mov r1,0x0
8e0000aa:	0d0b 0062 	mov r0,0x668
8e0000ae:	000b 1002 	movt r0,0x0
8e0000b2:	6a0b 0032 	mov r3,0x350
8e0000b6:	600b 1002 	movt r3,0x0
8e0000ba:	9fcb 0ff2 	mov r4,0xfffe
8e0000be:	9e2b 1ff2 	movt r4,0xfff1
8e0000c2:	0d52      	jalr r3
8e0000c4:	4d0b 0062 	mov r2,0x668
8e0000c8:	400b 1002 	movt r2,0x0
8e0000cc:	000b 0002 	mov r0,0x0
8e0000d0:	000b 18f2 	movt r0,0x8f00
8e0000d4:	00e4      	ldrd r0,[r0,0x1]
8e0000d6:	0874      	strd r0,[r2]
8e0000d8:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0000dc:	00c6      	lsr r0,r0,0x6
8e0000de:	000b 1002 	movt r0,0x0
8e0000e2:	20e2      	mov r1,r0
8e0000e4:	07e3      	mov r0,0x3f
8e0000e6:	045a      	and r0,r1,r0
8e0000e8:	2d0b 0062 	mov r1,0x668
8e0000ec:	200b 1002 	movt r1,0x0
8e0000f0:	2424      	ldrh r1,[r1]
8e0000f2:	20ba      	sub r1,r0,r1
8e0000f4:	0d0b 0062 	mov r0,0x668
8e0000f8:	000b 1002 	movt r0,0x0
8e0000fc:	01a4      	ldrh r0,[r0,0x3]
8e0000fe:	60e2      	mov r3,r0
8e000100:	400b 0002 	mov r2,0x0
8e000104:	410b 1002 	movt r2,0x8
8e000108:	0512      	movfs r0,status
8e00010a:	0392      	gid
8e00010c:	811f 2002 	movfs ip,config
8e000110:	917f 240a 	orr ip,ip,r2
8e000114:	810f 2002 	movts config,ip
8e000118:	0192      	gie
8e00011a:	01eb 4ef2 	mov r16,0xef0f
8e00011e:	1feb 5ff2 	movt r16,0xffff
8e000122:	251f 4002 	movfs r17,status
8e000126:	240f 480a 	eor r17,r17,r0
8e00012a:	245f 490a 	and r17,r17,r16
8e00012e:	240f 480a 	eor r17,r17,r0
8e000132:	250f 4002 	movts status,r17
8e000136:	25a7      	fmul r1,r1,r3
8e000138:	5fac 0500 	ldrh r2,[fp,-0x7]
8e00013c:	07e3      	mov r0,0x3f
8e00013e:	085a      	and r0,r2,r0
8e000140:	4d0b 0062 	mov r2,0x668
8e000144:	400b 1002 	movt r2,0x0
8e000148:	48a4      	ldrh r2,[r2,0x1]
8e00014a:	013a      	sub r0,r0,r2
8e00014c:	041a      	add r0,r1,r0
8e00014e:	1edc 0500 	str r0,[fp,-0x5]
8e000152:	1ecc 0500 	ldr r0,[fp,-0x5]
8e000156:	0093      	add r0,r0,1
8e000158:	2096      	lsl r1,r0,0x4
8e00015a:	000b 0002 	mov r0,0x0
8e00015e:	000b 18f2 	movt r0,0x8f00
8e000162:	241a      	add r1,r1,r0
8e000164:	0c0b 0062 	mov r0,0x660
8e000168:	000b 1002 	movt r0,0x0
8e00016c:	2054      	str r1,[r0]
8e00016e:	0c0b 0062 	mov r0,0x660
8e000172:	000b 1002 	movt r0,0x0
8e000176:	0044      	ldr r0,[r0]
8e000178:	2044      	ldr r1,[r0]
8e00017a:	1bab 0cc2 	mov r0,0xccdd
8e00017e:	176b 1aa2 	movt r0,0xaabb
8e000182:	443a      	sub r2,r1,r0
8e000184:	2d00      	beq 8e0001de <bjk_init_global+0x1de>
8e000186:	4003      	mov r2,0x0
8e000188:	2003      	mov r1,0x0
8e00018a:	004b 0eb2 	mov r0,0xeb02
8e00018e:	15ab 1de2 	movt r0,0xdead
8e000192:	850b 2062 	mov ip,0x628
8e000196:	800b 38e2 	movt ip,0x8e00
8e00019a:	9fcb 0ff2 	mov r4,0xfffe
8e00019e:	9e2b 1ff2 	movt r4,0xfff1
8e0001a2:	6512      	movfs r3,status
8e0001a4:	0392      	gid
8e0001a6:	011f 4002 	movfs r16,config
8e0001aa:	028f 480a 	eor r16,r16,r5
8e0001ae:	025f 480a 	and r16,r16,r4
8e0001b2:	028f 480a 	eor r16,r16,r5
8e0001b6:	010f 4002 	movts config,r16
8e0001ba:	0192      	gie
8e0001bc:	21eb 4ef2 	mov r17,0xef0f
8e0001c0:	3feb 5ff2 	movt r17,0xffff
8e0001c4:	051f 4002 	movfs r16,status
8e0001c8:	018f 480a 	eor r16,r16,r3
8e0001cc:	00df 490a 	and r16,r16,r17
8e0001d0:	018f 480a 	eor r16,r16,r3
8e0001d4:	050f 4002 	movts status,r16
8e0001d8:	115f 0402 	jalr ip
8e0001dc:	17e0      	b 8e00020a <bjk_init_global+0x20a>
8e0001de:	0512      	movfs r0,status
8e0001e0:	0392      	gid
8e0001e2:	211f 4002 	movfs r17,config
8e0001e6:	268f 480a 	eor r17,r17,r5
8e0001ea:	265f 480a 	and r17,r17,r4
8e0001ee:	268f 480a 	eor r17,r17,r5
8e0001f2:	210f 4002 	movts config,r17
8e0001f6:	0192      	gie
8e0001f8:	21eb 0ef2 	mov r1,0xef0f
8e0001fc:	3feb 1ff2 	movt r1,0xffff
8e000200:	4512      	movfs r2,status
8e000202:	480a      	eor r2,r2,r0
8e000204:	48da      	and r2,r2,r1
8e000206:	480a      	eor r2,r2,r0
8e000208:	4502      	movts status,r2
8e00020a:	4703      	mov r2,0x38
8e00020c:	2003      	mov r1,0x0
8e00020e:	050b 0062 	mov r0,0x628
8e000212:	000b 1002 	movt r0,0x0
8e000216:	6a0b 0032 	mov r3,0x350
8e00021a:	600b 1002 	movt r3,0x0
8e00021e:	9fcb 0ff2 	mov r4,0xfffe
8e000222:	9e2b 1ff2 	movt r4,0xfff1
8e000226:	0d52      	jalr r3
8e000228:	4a03      	mov r2,0x50
8e00022a:	2003      	mov r1,0x0
8e00022c:	1a0b 0052 	mov r0,0x5d0
8e000230:	000b 1002 	movt r0,0x0
8e000234:	6a0b 0032 	mov r3,0x350
8e000238:	600b 1002 	movt r3,0x0
8e00023c:	9fcb 0ff2 	mov r4,0xfffe
8e000240:	9e2b 1ff2 	movt r4,0xfff1
8e000244:	0d52      	jalr r3
8e000246:	050b 0062 	mov r0,0x628
8e00024a:	000b 1002 	movt r0,0x0
8e00024e:	3bab 0cc2 	mov r1,0xccdd
8e000252:	376b 1aa2 	movt r1,0xaabb
8e000256:	2054      	str r1,[r0]
8e000258:	050b 0062 	mov r0,0x628
8e00025c:	000b 1002 	movt r0,0x0
8e000260:	3a0b 0052 	mov r1,0x5d0
8e000264:	200b 1002 	movt r1,0x0
8e000268:	20d4      	str r1,[r0,0x1]
8e00026a:	050b 0062 	mov r0,0x628
8e00026e:	000b 1002 	movt r0,0x0
8e000272:	39ab 0ab2 	mov r1,0xabcd
8e000276:	312b 1672 	movt r1,0x6789
8e00027a:	22dc 0001 	str r1,[r0,+0xd]
8e00027e:	050b 0062 	mov r0,0x628
8e000282:	000b 1002 	movt r0,0x0
8e000286:	3fac 0500 	ldrh r1,[fp,-0x7]
8e00028a:	23bc 0002 	strh r1,[r0,+0x17]
8e00028e:	0c0b 0062 	mov r0,0x660
8e000292:	000b 1002 	movt r0,0x0
8e000296:	0044      	ldr r0,[r0]
8e000298:	250b 0062 	mov r1,0x628
8e00029c:	200b 1002 	movt r1,0x0
8e0002a0:	27ac 0002 	ldrh r1,[r1,+0x17]
8e0002a4:	2134      	strh r1,[r0,0x2]
8e0002a6:	01a2      	nop
8e0002a8:	0c0b 0062 	mov r0,0x660
8e0002ac:	000b 1002 	movt r0,0x0
8e0002b0:	0044      	ldr r0,[r0]
8e0002b2:	2124      	ldrh r1,[r0,0x2]
8e0002b4:	050b 0062 	mov r0,0x628
8e0002b8:	000b 1002 	movt r0,0x0
8e0002bc:	03ac 0002 	ldrh r0,[r0,+0x17]
8e0002c0:	843f 200a 	sub ip,r1,r0
8e0002c4:	f210      	bne 8e0002a8 <bjk_init_global+0x2a8>
8e0002c6:	0c0b 0062 	mov r0,0x660
8e0002ca:	000b 1002 	movt r0,0x0
8e0002ce:	0044      	ldr r0,[r0]
8e0002d0:	250b 0062 	mov r1,0x628
8e0002d4:	200b 1002 	movt r1,0x0
8e0002d8:	2154      	str r1,[r0,0x2]
8e0002da:	01a2      	nop
8e0002dc:	0c0b 0062 	mov r0,0x660
8e0002e0:	000b 1002 	movt r0,0x0
8e0002e4:	0044      	ldr r0,[r0]
8e0002e6:	2144      	ldr r1,[r0,0x2]
8e0002e8:	050b 0062 	mov r0,0x628
8e0002ec:	000b 1002 	movt r0,0x0
8e0002f0:	043f 400a 	sub r16,r1,r0
8e0002f4:	f410      	bne 8e0002dc <bjk_init_global+0x2dc>
8e0002f6:	0423      	mov r0,0x21
8e0002f8:	1d9c 0501 	strb r0,[fp,-0xb]
8e0002fc:	0c0b 0062 	mov r0,0x660
8e000300:	000b 1002 	movt r0,0x0
8e000304:	0044      	ldr r0,[r0]
8e000306:	3d8c 0501 	ldrb r1,[fp,-0xb]
8e00030a:	2314      	strb r1,[r0,0x6]
8e00030c:	0c0b 0062 	mov r0,0x660
8e000310:	000b 1002 	movt r0,0x0
8e000314:	0044      	ldr r0,[r0]
8e000316:	0304      	ldrb r0,[r0,0x6]
8e000318:	3d8c 0501 	ldrb r1,[fp,-0xb]
8e00031c:	243f 400a 	sub r17,r1,r0
8e000320:	f610      	bne 8e00030c <bjk_init_global+0x30c>
8e000322:	0c0b 0062 	mov r0,0x660
8e000326:	000b 1002 	movt r0,0x0
8e00032a:	0044      	ldr r0,[r0]
8e00032c:	2003      	mov r1,0x0
8e00032e:	2394      	strb r1,[r0,0x7]
8e000330:	01a2      	nop
8e000332:	0c0b 0062 	mov r0,0x660
8e000336:	000b 1002 	movt r0,0x0
8e00033a:	0044      	ldr r0,[r0]
8e00033c:	0384      	ldrb r0,[r0,0x7]
8e00033e:	2033      	sub r1,r0,0
8e000340:	f910      	bne 8e000332 <bjk_init_global+0x332>
8e000342:	01a2      	nop
8e000344:	9fcb 0ff2 	mov r4,0xfffe
8e000348:	9e2b 1ff2 	movt r4,0xfff1
8e00034c:	d66c 2400 	ldrd lr,[sp,+0x4]
8e000350:	95ec 0400 	ldrd r4,[sp,+0x3]
8e000354:	b41b 2404 	add sp,sp,32
8e000358:	194f 0402 	rts

8e00035c <abort>:
8e00035c:	d57c 2700 	strd lr,[sp],-0x2
8e000360:	f41b 2402 	add fp,sp,16

8e000364 <ck2_abort>:
8e000364:	ac8b e032 	mov r61,0x364
8e000368:	a00b f8e2 	movt r61,0x8e00
8e00036c:	14ef 1c02 	mov r0,r61
8e000370:	1cdc 0500 	str r0,[fp,-0x1]
8e000374:	5a0b 0052 	mov r2,0x5d0
8e000378:	400b 1002 	movt r2,0x0
8e00037c:	2283      	mov r1,0x14
8e00037e:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000382:	650b 0062 	mov r3,0x628
8e000386:	600b 18e2 	movt r3,0x8e00
8e00038a:	0d52      	jalr r3
8e00038c:	4003      	mov r2,0x0
8e00038e:	2003      	mov r1,0x0
8e000390:	002b 0002 	mov r0,0x1
8e000394:	15ab 1de2 	movt r0,0xdead
8e000398:	650b 0062 	mov r3,0x628
8e00039c:	600b 18e2 	movt r3,0x8e00
8e0003a0:	0d52      	jalr r3
8e0003a2:	00e0      	b 8e0003a2 <ck2_abort+0x3e>

8e0003a4 <bjk_set_sync_irq>:
8e0003a4:	f65c 2700 	str fp,[sp],-0x4
8e0003a8:	f4ef 2402 	mov fp,sp
8e0003ac:	0003      	mov r0,0x0
8e0003ae:	1ddc 0400 	str r0,[fp,+0x3]
8e0003b2:	090b 0012 	mov r0,0x148
8e0003b6:	000b 1002 	movt r0,0x0
8e0003ba:	0026      	lsr r0,r0,0x1
8e0003bc:	2116      	lsl r1,r0,0x8
8e0003be:	1d03      	mov r0,0xe8
8e0003c0:	247a      	orr r1,r1,r0
8e0003c2:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0003c6:	2054      	str r1,[r0]
8e0003c8:	01a2      	nop
8e0003ca:	f64c 2400 	ldr fp,[sp,+0x4]
8e0003ce:	b41b 2402 	add sp,sp,16
8e0003d2:	194f 0402 	rts
8e0003d6:	01a2      	nop

8e0003d8 <bjk_get_call_stack_trace>:
8e0003d8:	d4fc 2701 	strd lr,[sp],-0x9
8e0003dc:	f41b 2409 	add fp,sp,72
8e0003e0:	3c5c 0502 	str r1,[fp,-0x10]
8e0003e4:	1f3c 0503 	strh r0,[fp,-0x1e]
8e0003e8:	1c4c 0502 	ldr r0,[fp,-0x10]
8e0003ec:	2033      	sub r1,r0,0
8e0003ee:	0410      	bne 8e0003f6 <bjk_get_call_stack_trace+0x1e>
8e0003f0:	0003      	mov r0,0x0
8e0003f2:	15e8 0001 	b 8e00061c <bjk_get_call_stack_trace+0x244>
8e0003f6:	0003      	mov r0,0x0
8e0003f8:	1cdc 0500 	str r0,[fp,-0x1]
8e0003fc:	0003      	mov r0,0x0
8e0003fe:	1d5c 0500 	str r0,[fp,-0x2]
8e000402:	0003      	mov r0,0x0
8e000404:	1ddc 0500 	str r0,[fp,-0x3]
8e000408:	0003      	mov r0,0x0
8e00040a:	1fbc 0500 	strh r0,[fp,-0x7]
8e00040e:	1f2c 0503 	ldrh r0,[fp,-0x1e]
8e000412:	4033      	sub r2,r0,0
8e000414:	0410      	bne 8e00041c <bjk_get_call_stack_trace+0x44>
8e000416:	0003      	mov r0,0x0
8e000418:	02e8 0001 	b 8e00061c <bjk_get_call_stack_trace+0x244>
8e00041c:	0912      	movfs r0,pc
8e00041e:	00e2      	mov r0,r0
8e000420:	1cdc 0500 	str r0,[fp,-0x1]
8e000424:	14ef 0402 	mov r0,sp
8e000428:	1d5c 0500 	str r0,[fp,-0x2]
8e00042c:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000430:	2f8b 0082 	mov r1,0x87c
8e000434:	200b 18e2 	movt r1,0x8e00
8e000438:	0552      	jalr r1
8e00043a:	1ddc 0500 	str r0,[fp,-0x3]
8e00043e:	c7e8 0000 	b 8e0005cc <bjk_get_call_stack_trace+0x1f4>
8e000442:	3fac 0500 	ldrh r1,[fp,-0x7]
8e000446:	1f2c 0503 	ldrh r0,[fp,-0x1e]
8e00044a:	443a      	sub r2,r1,r0
8e00044c:	c608 0000 	beq 8e0005d8 <bjk_get_call_stack_trace+0x200>
8e000450:	1dcc 0500 	ldr r0,[fp,-0x3]
8e000454:	350b 0092 	mov r1,0x9a8
8e000458:	200b 18e2 	movt r1,0x8e00
8e00045c:	0552      	jalr r1
8e00045e:	1c3c 0501 	strh r0,[fp,-0x8]
8e000462:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e000466:	2033      	sub r1,r0,0
8e000468:	ba08 0000 	beq 8e0005dc <bjk_get_call_stack_trace+0x204>
8e00046c:	3c2c 0501 	ldrh r1,[fp,-0x8]
8e000470:	0023      	mov r0,0x1
8e000472:	045a      	and r0,r1,r0
8e000474:	000b 1002 	movt r0,0x0
8e000478:	4033      	sub r2,r0,0
8e00047a:	0f00      	beq 8e000498 <bjk_get_call_stack_trace+0xc0>
8e00047c:	1f2c 0503 	ldrh r0,[fp,-0x1e]
8e000480:	5c4c 0502 	ldr r2,[fp,-0x10]
8e000484:	20e2      	mov r1,r0
8e000486:	0ceb 0452 	mov r0,0x4567
8e00048a:	046b 1012 	movt r0,0x123
8e00048e:	650b 0062 	mov r3,0x628
8e000492:	600b 18e2 	movt r3,0x8e00
8e000496:	0d52      	jalr r3
8e000498:	1d4c 0500 	ldr r0,[fp,-0x2]
8e00049c:	1edc 0500 	str r0,[fp,-0x5]
8e0004a0:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e0004a4:	3ecc 0500 	ldr r1,[fp,-0x5]
8e0004a8:	041a      	add r0,r1,r0
8e0004aa:	1edc 0500 	str r0,[fp,-0x5]
8e0004ae:	1ecc 0500 	ldr r0,[fp,-0x5]
8e0004b2:	1d5c 0500 	str r0,[fp,-0x2]
8e0004b6:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e0004ba:	0066      	lsr r0,r0,0x3
8e0004bc:	1dbc 0501 	strh r0,[fp,-0xb]
8e0004c0:	1dac 0501 	ldrh r0,[fp,-0xb]
8e0004c4:	0216      	lsl r0,r0,0x10
8e0004c6:	020e      	asr r0,r0,0x10
8e0004c8:	3d1b 04f9 	add r1,fp,-54
8e0004cc:	3c5c 0501 	str r1,[fp,-0x8]
8e0004d0:	1cbc 0503 	strh r0,[fp,-0x19]
8e0004d4:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0004d8:	2f8b 0d42 	mov r1,0xd47c
8e0004dc:	3feb 1ff2 	movt r1,0xffff
8e0004e0:	2034      	strh r1,[r0]
8e0004e2:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0004e6:	0113      	add r0,r0,2
8e0004e8:	200b 0272 	mov r1,0x2700
8e0004ec:	2034      	strh r1,[r0]
8e0004ee:	1c4c 0501 	ldr r0,[fp,-0x8]
8e0004f2:	0024      	ldrh r0,[r0]
8e0004f4:	20e2      	mov r1,r0
8e0004f6:	200b 1002 	movt r1,0x0
8e0004fa:	1cac 0503 	ldrh r0,[fp,-0x19]
8e0004fe:	40e2      	mov r2,r0
8e000500:	00e3      	mov r0,0x7
8e000502:	085a      	and r0,r2,r0
8e000504:	00f6      	lsl r0,r0,0x7
8e000506:	000b 1002 	movt r0,0x0
8e00050a:	047a      	orr r0,r1,r0
8e00050c:	000b 1002 	movt r0,0x0
8e000510:	20e2      	mov r1,r0
8e000512:	200b 1002 	movt r1,0x0
8e000516:	1c4c 0501 	ldr r0,[fp,-0x8]
8e00051a:	2034      	strh r1,[r0]
8e00051c:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000520:	2113      	add r1,r0,2
8e000522:	1c4c 0501 	ldr r0,[fp,-0x8]
8e000526:	0113      	add r0,r0,2
8e000528:	0024      	ldrh r0,[r0]
8e00052a:	40e2      	mov r2,r0
8e00052c:	400b 1002 	movt r2,0x0
8e000530:	1cac 0503 	ldrh r0,[fp,-0x19]
8e000534:	0216      	lsl r0,r0,0x10
8e000536:	020e      	asr r0,r0,0x10
8e000538:	006e      	asr r0,r0,0x3
8e00053a:	000b 1002 	movt r0,0x0
8e00053e:	087a      	orr r0,r2,r0
8e000540:	000b 1002 	movt r0,0x0
8e000544:	000b 1002 	movt r0,0x0
8e000548:	0434      	strh r0,[r1]
8e00054a:	1d1b 04f9 	add r0,fp,-54
8e00054e:	20e2      	mov r1,r0
8e000550:	1ccc 0500 	ldr r0,[fp,-0x1]
8e000554:	598b 0072 	mov r2,0x7cc
8e000558:	400b 18e2 	movt r2,0x8e00
8e00055c:	0952      	jalr r2
8e00055e:	1fdc 0500 	str r0,[fp,-0x7]
8e000562:	1d4c 0500 	ldr r0,[fp,-0x2]
8e000566:	1ddc 0501 	str r0,[fp,-0xb]
8e00056a:	1dcc 0501 	ldr r0,[fp,-0xb]
8e00056e:	0113      	add r0,r0,2
8e000570:	0024      	ldrh r0,[r0]
8e000572:	1e5c 0501 	str r0,[fp,-0xc]
8e000576:	1e4c 0501 	ldr r0,[fp,-0xc]
8e00057a:	0216      	lsl r0,r0,0x10
8e00057c:	1e5c 0501 	str r0,[fp,-0xc]
8e000580:	1dcc 0501 	ldr r0,[fp,-0xb]
8e000584:	0024      	ldrh r0,[r0]
8e000586:	20e2      	mov r1,r0
8e000588:	1e4c 0501 	ldr r0,[fp,-0xc]
8e00058c:	00fa      	orr r0,r0,r1
8e00058e:	1e5c 0501 	str r0,[fp,-0xc]
8e000592:	1e4c 0501 	ldr r0,[fp,-0xc]
8e000596:	1cdc 0501 	str r0,[fp,-0x9]
8e00059a:	1ccc 0501 	ldr r0,[fp,-0x9]
8e00059e:	1cdc 0500 	str r0,[fp,-0x1]
8e0005a2:	1fac 0500 	ldrh r0,[fp,-0x7]
8e0005a6:	2093      	add r1,r0,1
8e0005a8:	3fbc 0500 	strh r1,[fp,-0x7]
8e0005ac:	0056      	lsl r0,r0,0x2
8e0005ae:	3c4c 0502 	ldr r1,[fp,-0x10]
8e0005b2:	041a      	add r0,r1,r0
8e0005b4:	3fcc 0500 	ldr r1,[fp,-0x7]
8e0005b8:	2054      	str r1,[r0]
8e0005ba:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0005be:	2f8b 0082 	mov r1,0x87c
8e0005c2:	200b 18e2 	movt r1,0x8e00
8e0005c6:	0552      	jalr r1
8e0005c8:	1ddc 0500 	str r0,[fp,-0x3]
8e0005cc:	1dcc 0500 	ldr r0,[fp,-0x3]
8e0005d0:	2033      	sub r1,r0,0
8e0005d2:	3818 ffff 	bne 8e000442 <bjk_get_call_stack_trace+0x6a>
8e0005d6:	04e0      	b 8e0005de <bjk_get_call_stack_trace+0x206>
8e0005d8:	01a2      	nop
8e0005da:	02e0      	b 8e0005de <bjk_get_call_stack_trace+0x206>
8e0005dc:	01a2      	nop
8e0005de:	040b 0062 	mov r0,0x620
8e0005e2:	000b 1002 	movt r0,0x0
8e0005e6:	0024      	ldrh r0,[r0]
8e0005e8:	40bb 0008 	sub r2,r0,65
8e0005ec:	1610      	bne 8e000618 <bjk_get_call_stack_trace+0x240>
8e0005ee:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0005f2:	268b 0042 	mov r1,0x434
8e0005f6:	200b 1002 	movt r1,0x0
8e0005fa:	0552      	jalr r1
8e0005fc:	1d5c 0501 	str r0,[fp,-0xa]
8e000600:	1fac 0500 	ldrh r0,[fp,-0x7]
8e000604:	2093      	add r1,r0,1
8e000606:	3fbc 0500 	strh r1,[fp,-0x7]
8e00060a:	0056      	lsl r0,r0,0x2
8e00060c:	3c4c 0502 	ldr r1,[fp,-0x10]
8e000610:	041a      	add r0,r1,r0
8e000612:	3d4c 0501 	ldr r1,[fp,-0xa]
8e000616:	2054      	str r1,[r0]
8e000618:	1fac 0500 	ldrh r0,[fp,-0x7]
8e00061c:	d4ec 2401 	ldrd lr,[sp,+0x9]
8e000620:	b41b 2409 	add sp,sp,72
8e000624:	194f 0402 	rts

8e000628 <bjk_abort>:
8e000628:	d5fc 2700 	strd lr,[sp],-0x3
8e00062c:	f41b 2403 	add fp,sp,24
8e000630:	1cdc 0500 	str r0,[fp,-0x1]
8e000634:	04e2      	mov r0,r1
8e000636:	5ddc 0500 	str r2,[fp,-0x3]
8e00063a:	1e3c 0500 	strh r0,[fp,-0x4]
8e00063e:	3ccc 0500 	ldr r1,[fp,-0x1]
8e000642:	0ceb 0452 	mov r0,0x4567
8e000646:	046b 1012 	movt r0,0x123
8e00064a:	443a      	sub r2,r1,r0
8e00064c:	0a00      	beq 8e000660 <bjk_abort+0x38>
8e00064e:	1e2c 0500 	ldrh r0,[fp,-0x4]
8e000652:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000656:	5b0b 0032 	mov r2,0x3d8
8e00065a:	400b 18e2 	movt r2,0x8e00
8e00065e:	0952      	jalr r2
8e000660:	050b 0062 	mov r0,0x628
8e000664:	000b 1002 	movt r0,0x0
8e000668:	3ccc 0500 	ldr r1,[fp,-0x1]
8e00066c:	2154      	str r1,[r0,0x2]
8e00066e:	0c0b 0062 	mov r0,0x660
8e000672:	000b 1002 	movt r0,0x0
8e000676:	0044      	ldr r0,[r0]
8e000678:	2033      	sub r1,r0,0
8e00067a:	1f00      	beq 8e0006b8 <bjk_abort+0x90>
8e00067c:	0c0b 0062 	mov r0,0x660
8e000680:	000b 1002 	movt r0,0x0
8e000684:	0044      	ldr r0,[r0]
8e000686:	2044      	ldr r1,[r0]
8e000688:	1bab 0cc2 	mov r0,0xccdd
8e00068c:	176b 1aa2 	movt r0,0xaabb
8e000690:	443a      	sub r2,r1,r0
8e000692:	1310      	bne 8e0006b8 <bjk_abort+0x90>
8e000694:	0c0b 0062 	mov r0,0x660
8e000698:	000b 1002 	movt r0,0x0
8e00069c:	0044      	ldr r0,[r0]
8e00069e:	3e2b 0ff2 	mov r1,0xfff1
8e0006a2:	2314      	strb r1,[r0,0x6]
8e0006a4:	01a2      	nop
8e0006a6:	0c0b 0062 	mov r0,0x660
8e0006aa:	000b 1002 	movt r0,0x0
8e0006ae:	0044      	ldr r0,[r0]
8e0006b0:	0304      	ldrb r0,[r0,0x6]
8e0006b2:	20bb 001e 	sub r1,r0,241
8e0006b6:	f810      	bne 8e0006a6 <bjk_abort+0x7e>
8e0006b8:	050b 0062 	mov r0,0x628
8e0006bc:	000b 1002 	movt r0,0x0
8e0006c0:	c0ef e002 	mov r62,r0
8e0006c4:	1ccc 0500 	ldr r0,[fp,-0x1]
8e0006c8:	e0ef e002 	mov r63,r0
8e0006cc:	0392      	gid
8e0006ce:	0fe2      	trap 0x3
8e0006d0:	0912      	movfs r0,pc
8e0006d2:	0152      	jalr r0
8e0006d4:	01a2      	nop
8e0006d6:	d5ec 2400 	ldrd lr,[sp,+0x3]
8e0006da:	b41b 2403 	add sp,sp,24
8e0006de:	194f 0402 	rts
8e0006e2:	01a2      	nop

8e0006e4 <bjk_wait_sync>:
8e0006e4:	d67c 2700 	strd lr,[sp],-0x4
8e0006e8:	f41b 2404 	add fp,sp,32
8e0006ec:	1ddc 0500 	str r0,[fp,-0x3]
8e0006f0:	04e2      	mov r0,r1
8e0006f2:	5edc 0500 	str r2,[fp,-0x5]
8e0006f6:	1c3c 0501 	strh r0,[fp,-0x8]
8e0006fa:	0c0b 0062 	mov r0,0x660
8e0006fe:	000b 1002 	movt r0,0x0
8e000702:	0044      	ldr r0,[r0]
8e000704:	2033      	sub r1,r0,0
8e000706:	0d10      	bne 8e000720 <bjk_wait_sync+0x3c>
8e000708:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e00070c:	5ecc 0500 	ldr r2,[fp,-0x5]
8e000710:	20e2      	mov r1,r0
8e000712:	15ab 00b2 	mov r0,0xbad
8e000716:	650b 0062 	mov r3,0x628
8e00071a:	600b 18e2 	movt r3,0x8e00
8e00071e:	0d52      	jalr r3
8e000720:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e000724:	2033      	sub r1,r0,0
8e000726:	0e00      	beq 8e000742 <bjk_wait_sync+0x5e>
8e000728:	1ecc 0500 	ldr r0,[fp,-0x5]
8e00072c:	2033      	sub r1,r0,0
8e00072e:	0a00      	beq 8e000742 <bjk_wait_sync+0x5e>
8e000730:	1c2c 0501 	ldrh r0,[fp,-0x8]
8e000734:	3ecc 0500 	ldr r1,[fp,-0x5]
8e000738:	5b0b 0032 	mov r2,0x3d8
8e00073c:	400b 18e2 	movt r2,0x8e00
8e000740:	0952      	jalr r2
8e000742:	0003      	mov r0,0x0
8e000744:	1cbc 0500 	strh r0,[fp,-0x1]
8e000748:	0392      	gid
8e00074a:	051f 0402 	movfs r0,imask
8e00074e:	1cbc 0500 	strh r0,[fp,-0x1]
8e000752:	1fcb 0032 	mov r0,0x3fe
8e000756:	050f 0402 	movts imask,r0
8e00075a:	050b 0062 	mov r0,0x628
8e00075e:	000b 1002 	movt r0,0x0
8e000762:	3dcc 0500 	ldr r1,[fp,-0x3]
8e000766:	2254      	str r1,[r0,0x4]
8e000768:	0c0b 0062 	mov r0,0x660
8e00076c:	000b 1002 	movt r0,0x0
8e000770:	0044      	ldr r0,[r0]
8e000772:	354b 0ff2 	mov r1,0xffaa
8e000776:	2394      	strb r1,[r0,0x7]
8e000778:	01a2      	nop
8e00077a:	0c0b 0062 	mov r0,0x660
8e00077e:	000b 1002 	movt r0,0x0
8e000782:	0044      	ldr r0,[r0]
8e000784:	0384      	ldrb r0,[r0,0x7]
8e000786:	213b 0015 	sub r1,r0,170
8e00078a:	f810      	bne 8e00077a <bjk_wait_sync+0x96>
8e00078c:	0192      	gie
8e00078e:	01b2      	idle
8e000790:	0392      	gid
8e000792:	1cac 0500 	ldrh r0,[fp,-0x1]
8e000796:	050f 0402 	movts imask,r0
8e00079a:	0c0b 0062 	mov r0,0x660
8e00079e:	000b 1002 	movt r0,0x0
8e0007a2:	0044      	ldr r0,[r0]
8e0007a4:	2003      	mov r1,0x0
8e0007a6:	2394      	strb r1,[r0,0x7]
8e0007a8:	01a2      	nop
8e0007aa:	0c0b 0062 	mov r0,0x660
8e0007ae:	000b 1002 	movt r0,0x0
8e0007b2:	0044      	ldr r0,[r0]
8e0007b4:	0384      	ldrb r0,[r0,0x7]
8e0007b6:	2033      	sub r1,r0,0
8e0007b8:	f910      	bne 8e0007aa <bjk_wait_sync+0xc6>
8e0007ba:	0192      	gie
8e0007bc:	01a2      	nop
8e0007be:	d66c 2400 	ldrd lr,[sp,+0x4]
8e0007c2:	b41b 2404 	add sp,sp,32
8e0007c6:	194f 0402 	rts
8e0007ca:	01a2      	nop

8e0007cc <find_call>:
8e0007cc:	f75c 2700 	str fp,[sp],-0x6
8e0007d0:	f4ef 2402 	mov fp,sp
8e0007d4:	1ddc 0400 	str r0,[fp,+0x3]
8e0007d8:	3d5c 0400 	str r1,[fp,+0x2]
8e0007dc:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0007e0:	1edc 0400 	str r0,[fp,+0x5]
8e0007e4:	040b 0062 	mov r0,0x620
8e0007e8:	000b 1002 	movt r0,0x0
8e0007ec:	2003      	mov r1,0x0
8e0007ee:	2034      	strh r1,[r0]
8e0007f0:	39e0      	b 8e000862 <find_call+0x96>
8e0007f2:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0007f6:	2024      	ldrh r1,[r0]
8e0007f8:	1d4c 0400 	ldr r0,[fp,+0x2]
8e0007fc:	0024      	ldrh r0,[r0]
8e0007fe:	443a      	sub r2,r1,r0
8e000800:	1310      	bne 8e000826 <find_call+0x5a>
8e000802:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000806:	0113      	add r0,r0,2
8e000808:	2024      	ldrh r1,[r0]
8e00080a:	1d4c 0400 	ldr r0,[fp,+0x2]
8e00080e:	0113      	add r0,r0,2
8e000810:	0024      	ldrh r0,[r0]
8e000812:	443a      	sub r2,r1,r0
8e000814:	0910      	bne 8e000826 <find_call+0x5a>
8e000816:	040b 0062 	mov r0,0x620
8e00081a:	000b 1002 	movt r0,0x0
8e00081e:	3dcb 01e2 	mov r1,0x1eee
8e000822:	2034      	strh r1,[r0]
8e000824:	23e0      	b 8e00086a <find_call+0x9e>
8e000826:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00082a:	2024      	ldrh r1,[r0]
8e00082c:	09eb 0192 	mov r0,0x194f
8e000830:	443a      	sub r2,r1,r0
8e000832:	1310      	bne 8e000858 <find_call+0x8c>
8e000834:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000838:	0113      	add r0,r0,2
8e00083a:	2024      	ldrh r1,[r0]
8e00083c:	004b 0042 	mov r0,0x402
8e000840:	443a      	sub r2,r1,r0
8e000842:	0b10      	bne 8e000858 <find_call+0x8c>
8e000844:	040b 0062 	mov r0,0x620
8e000848:	000b 1002 	movt r0,0x0
8e00084c:	2223      	mov r1,0x11
8e00084e:	2034      	strh r1,[r0]
8e000850:	0003      	mov r0,0x0
8e000852:	1edc 0400 	str r0,[fp,+0x5]
8e000856:	0ae0      	b 8e00086a <find_call+0x9e>
8e000858:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00085c:	0313      	add r0,r0,-2
8e00085e:	1edc 0400 	str r0,[fp,+0x5]
8e000862:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000866:	2033      	sub r1,r0,0
8e000868:	c510      	bne 8e0007f2 <find_call+0x26>
8e00086a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00086e:	f74c 2400 	ldr fp,[sp,+0x6]
8e000872:	b41b 2403 	add sp,sp,24
8e000876:	194f 0402 	rts
8e00087a:	01a2      	nop

8e00087c <find_rts>:
8e00087c:	f75c 2700 	str fp,[sp],-0x6
8e000880:	f4ef 2402 	mov fp,sp
8e000884:	1ddc 0400 	str r0,[fp,+0x3]
8e000888:	3dcc 0400 	ldr r1,[fp,+0x3]
8e00088c:	000b 0802 	mov r0,0x8000
8e000890:	041a      	add r0,r1,r0
8e000892:	1e5c 0400 	str r0,[fp,+0x4]
8e000896:	040b 0062 	mov r0,0x620
8e00089a:	000b 1002 	movt r0,0x0
8e00089e:	2003      	mov r1,0x0
8e0008a0:	2034      	strh r1,[r0]
8e0008a2:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0008a6:	1edc 0400 	str r0,[fp,+0x5]
8e0008aa:	49e0      	b 8e00093c <find_rts+0xc0>
8e0008ac:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0008b0:	2024      	ldrh r1,[r0]
8e0008b2:	09eb 0192 	mov r0,0x194f
8e0008b6:	443a      	sub r2,r1,r0
8e0008b8:	1110      	bne 8e0008da <find_rts+0x5e>
8e0008ba:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0008be:	0113      	add r0,r0,2
8e0008c0:	2024      	ldrh r1,[r0]
8e0008c2:	004b 0042 	mov r0,0x402
8e0008c6:	443a      	sub r2,r1,r0
8e0008c8:	0910      	bne 8e0008da <find_rts+0x5e>
8e0008ca:	040b 0062 	mov r0,0x620
8e0008ce:	000b 1002 	movt r0,0x0
8e0008d2:	3dcb 04e2 	mov r1,0x4eee
8e0008d6:	2034      	strh r1,[r0]
8e0008d8:	38e0      	b 8e000948 <find_rts+0xcc>
8e0008da:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0008de:	0024      	ldrh r0,[r0]
8e0008e0:	213b 003a 	sub r1,r0,466
8e0008e4:	2710      	bne 8e000932 <find_rts+0xb6>
8e0008e6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0008ea:	031b 00fe 	add r0,r0,-10
8e0008ee:	2024      	ldrh r1,[r0]
8e0008f0:	004b 0052 	mov r0,0x502
8e0008f4:	443a      	sub r2,r1,r0
8e0008f6:	1e10      	bne 8e000932 <find_rts+0xb6>
8e0008f8:	1ecc 0400 	ldr r0,[fp,+0x5]
8e0008fc:	001b 00ff 	add r0,r0,-8
8e000900:	2024      	ldrh r1,[r0]
8e000902:	01eb 0212 	mov r0,0x210f
8e000906:	443a      	sub r2,r1,r0
8e000908:	1510      	bne 8e000932 <find_rts+0xb6>
8e00090a:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00090e:	011b 00ff 	add r0,r0,-6
8e000912:	2024      	ldrh r1,[r0]
8e000914:	004b 0042 	mov r0,0x402
8e000918:	443a      	sub r2,r1,r0
8e00091a:	0c10      	bne 8e000932 <find_rts+0xb6>
8e00091c:	040b 0062 	mov r0,0x620
8e000920:	000b 1002 	movt r0,0x0
8e000924:	2823      	mov r1,0x41
8e000926:	2034      	strh r1,[r0]
8e000928:	1dcc 0400 	ldr r0,[fp,+0x3]
8e00092c:	1edc 0400 	str r0,[fp,+0x5]
8e000930:	0ce0      	b 8e000948 <find_rts+0xcc>
8e000932:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000936:	0113      	add r0,r0,2
8e000938:	1edc 0400 	str r0,[fp,+0x5]
8e00093c:	3ecc 0400 	ldr r1,[fp,+0x5]
8e000940:	1e4c 0400 	ldr r0,[fp,+0x4]
8e000944:	443a      	sub r2,r1,r0
8e000946:	b350      	bltu 8e0008ac <find_rts+0x30>
8e000948:	040b 0062 	mov r0,0x620
8e00094c:	000b 1002 	movt r0,0x0
8e000950:	0024      	ldrh r0,[r0]
8e000952:	20bb 0008 	sub r1,r0,65
8e000956:	0310      	bne 8e00095c <find_rts+0xe0>
8e000958:	0003      	mov r0,0x0
8e00095a:	21e0      	b 8e00099c <find_rts+0x120>
8e00095c:	3ecc 0400 	ldr r1,[fp,+0x5]
8e000960:	1e4c 0400 	ldr r0,[fp,+0x4]
8e000964:	443a      	sub r2,r1,r0
8e000966:	0910      	bne 8e000978 <find_rts+0xfc>
8e000968:	040b 0062 	mov r0,0x620
8e00096c:	000b 1002 	movt r0,0x0
8e000970:	2843      	mov r1,0x42
8e000972:	2034      	strh r1,[r0]
8e000974:	0003      	mov r0,0x0
8e000976:	13e0      	b 8e00099c <find_rts+0x120>
8e000978:	3ecc 0400 	ldr r1,[fp,+0x5]
8e00097c:	1dcc 0400 	ldr r0,[fp,+0x3]
8e000980:	043a      	sub r0,r1,r0
8e000982:	002e      	asr r0,r0,0x1
8e000984:	20b3      	sub r1,r0,1
8e000986:	0920      	bgtu 8e000998 <find_rts+0x11c>
8e000988:	040b 0062 	mov r0,0x620
8e00098c:	000b 1002 	movt r0,0x0
8e000990:	2863      	mov r1,0x43
8e000992:	2034      	strh r1,[r0]
8e000994:	0003      	mov r0,0x0
8e000996:	03e0      	b 8e00099c <find_rts+0x120>
8e000998:	1ecc 0400 	ldr r0,[fp,+0x5]
8e00099c:	f74c 2400 	ldr fp,[sp,+0x6]
8e0009a0:	b41b 2403 	add sp,sp,24
8e0009a4:	194f 0402 	rts

8e0009a8 <get_sp_disp>:
8e0009a8:	f55c 2701 	str fp,[sp],-0xa
8e0009ac:	f4ef 2402 	mov fp,sp
8e0009b0:	1ddc 0400 	str r0,[fp,+0x3]
8e0009b4:	1dcc 0400 	ldr r0,[fp,+0x3]
8e0009b8:	1cdc 0401 	str r0,[fp,+0x9]
8e0009bc:	1ccc 0401 	ldr r0,[fp,+0x9]
8e0009c0:	0213      	add r0,r0,-4
8e0009c2:	1cdc 0401 	str r0,[fp,+0x9]
8e0009c6:	1ccc 0401 	ldr r0,[fp,+0x9]
8e0009ca:	0024      	ldrh r0,[r0]
8e0009cc:	1cbc 0402 	strh r0,[fp,+0x11]
8e0009d0:	1ccc 0401 	ldr r0,[fp,+0x9]
8e0009d4:	00a4      	ldrh r0,[r0,0x1]
8e0009d6:	1c3c 0402 	strh r0,[fp,+0x10]
8e0009da:	040b 0062 	mov r0,0x620
8e0009de:	000b 1002 	movt r0,0x0
8e0009e2:	2003      	mov r1,0x0
8e0009e4:	2034      	strh r1,[r0]
8e0009e6:	3cac 0402 	ldrh r1,[fp,+0x11]
8e0009ea:	01eb 0f02 	mov r0,0xf00f
8e0009ee:	245a      	and r1,r1,r0
8e0009f0:	016b 0b02 	mov r0,0xb00b
8e0009f4:	443a      	sub r2,r1,r0
8e0009f6:	0a00      	beq 8e000a0a <get_sp_disp+0x62>
8e0009f8:	040b 0062 	mov r0,0x620
8e0009fc:	000b 1002 	movt r0,0x0
8e000a00:	2623      	mov r1,0x31
8e000a02:	2034      	strh r1,[r0]
8e000a04:	0003      	mov r0,0x0
8e000a06:	98e8 0000 	b 8e000b36 <get_sp_disp+0x18e>
8e000a0a:	3c2c 0402 	ldrh r1,[fp,+0x10]
8e000a0e:	000b 0ff2 	mov r0,0xff00
8e000a12:	245a      	and r1,r1,r0
8e000a14:	000b 0242 	mov r0,0x2400
8e000a18:	443a      	sub r2,r1,r0
8e000a1a:	0a00      	beq 8e000a2e <get_sp_disp+0x86>
8e000a1c:	040b 0062 	mov r0,0x620
8e000a20:	000b 1002 	movt r0,0x0
8e000a24:	2643      	mov r1,0x32
8e000a26:	2034      	strh r1,[r0]
8e000a28:	0003      	mov r0,0x0
8e000a2a:	86e8 0000 	b 8e000b36 <get_sp_disp+0x18e>
8e000a2e:	1ccc 0401 	ldr r0,[fp,+0x9]
8e000a32:	1fdc 0400 	str r0,[fp,+0x7]
8e000a36:	1ccc 0401 	ldr r0,[fp,+0x9]
8e000a3a:	0213      	add r0,r0,-4
8e000a3c:	1cdc 0401 	str r0,[fp,+0x9]
8e000a40:	1ccc 0401 	ldr r0,[fp,+0x9]
8e000a44:	0024      	ldrh r0,[r0]
8e000a46:	1cbc 0402 	strh r0,[fp,+0x11]
8e000a4a:	1ccc 0401 	ldr r0,[fp,+0x9]
8e000a4e:	00a4      	ldrh r0,[r0,0x1]
8e000a50:	1c3c 0402 	strh r0,[fp,+0x10]
8e000a54:	3cac 0402 	ldrh r1,[fp,+0x11]
8e000a58:	01eb 0f02 	mov r0,0xf00f
8e000a5c:	245a      	and r1,r1,r0
8e000a5e:	018b 0d02 	mov r0,0xd00c
8e000a62:	443a      	sub r2,r1,r0
8e000a64:	0900      	beq 8e000a76 <get_sp_disp+0xce>
8e000a66:	040b 0062 	mov r0,0x620
8e000a6a:	000b 1002 	movt r0,0x0
8e000a6e:	2663      	mov r1,0x33
8e000a70:	2034      	strh r1,[r0]
8e000a72:	0003      	mov r0,0x0
8e000a74:	61e0      	b 8e000b36 <get_sp_disp+0x18e>
8e000a76:	3c2c 0402 	ldrh r1,[fp,+0x10]
8e000a7a:	000b 0f02 	mov r0,0xf000
8e000a7e:	245a      	and r1,r1,r0
8e000a80:	000b 0202 	mov r0,0x2000
8e000a84:	443a      	sub r2,r1,r0
8e000a86:	0900      	beq 8e000a98 <get_sp_disp+0xf0>
8e000a88:	040b 0062 	mov r0,0x620
8e000a8c:	000b 1002 	movt r0,0x0
8e000a90:	2683      	mov r1,0x34
8e000a92:	2034      	strh r1,[r0]
8e000a94:	0003      	mov r0,0x0
8e000a96:	50e0      	b 8e000b36 <get_sp_disp+0x18e>
8e000a98:	1fcc 0400 	ldr r0,[fp,+0x7]
8e000a9c:	1edc 0400 	str r0,[fp,+0x5]
8e000aa0:	0003      	mov r0,0x0
8e000aa2:	1cbc 0401 	strh r0,[fp,+0x9]
8e000aa6:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000aaa:	0113      	add r0,r0,2
8e000aac:	0024      	ldrh r0,[r0]
8e000aae:	20e2      	mov r1,r0
8e000ab0:	1fe3      	mov r0,0xff
8e000ab2:	045a      	and r0,r1,r0
8e000ab4:	0076      	lsl r0,r0,0x3
8e000ab6:	20e2      	mov r1,r0
8e000ab8:	200b 1002 	movt r1,0x0
8e000abc:	1ecc 0400 	ldr r0,[fp,+0x5]
8e000ac0:	0024      	ldrh r0,[r0]
8e000ac2:	40e2      	mov r2,r0
8e000ac4:	100b 0032 	mov r0,0x380
8e000ac8:	085a      	and r0,r2,r0
8e000aca:	00ee      	asr r0,r0,0x7
8e000acc:	000b 1002 	movt r0,0x0
8e000ad0:	047a      	orr r0,r1,r0
8e000ad2:	000b 1002 	movt r0,0x0
8e000ad6:	1cbc 0401 	strh r0,[fp,+0x9]
8e000ada:	1d1b 0402 	add r0,fp,18
8e000ade:	0093      	add r0,r0,1
8e000ae0:	0004      	ldrb r0,[r0]
8e000ae2:	0046      	lsr r0,r0,0x2
8e000ae4:	0316      	lsl r0,r0,0x18
8e000ae6:	0306      	lsr r0,r0,0x18
8e000ae8:	20e2      	mov r1,r0
8e000aea:	0023      	mov r0,0x1
8e000aec:	045a      	and r0,r1,r0
8e000aee:	2033      	sub r1,r0,0
8e000af0:	1000      	beq 8e000b10 <get_sp_disp+0x168>
8e000af2:	1cac 0401 	ldrh r0,[fp,+0x9]
8e000af6:	20e2      	mov r1,r0
8e000af8:	200b 1002 	movt r1,0x0
8e000afc:	000b 0f82 	mov r0,0xf800
8e000b00:	1feb 1ff2 	movt r0,0xffff
8e000b04:	040a      	eor r0,r1,r0
8e000b06:	000b 1002 	movt r0,0x0
8e000b0a:	000b 1002 	movt r0,0x0
8e000b0e:	03e0      	b 8e000b14 <get_sp_disp+0x16c>
8e000b10:	1cac 0401 	ldrh r0,[fp,+0x9]
8e000b14:	1cbc 0401 	strh r0,[fp,+0x9]
8e000b18:	1cac 0401 	ldrh r0,[fp,+0x9]
8e000b1c:	000b 1002 	movt r0,0x0
8e000b20:	1ebc 0401 	strh r0,[fp,+0xd]
8e000b24:	040b 0062 	mov r0,0x620
8e000b28:	000b 1002 	movt r0,0x0
8e000b2c:	3dcb 03e2 	mov r1,0x3eee
8e000b30:	2034      	strh r1,[r0]
8e000b32:	1eac 0401 	ldrh r0,[fp,+0xd]
8e000b36:	0216      	lsl r0,r0,0x10
8e000b38:	020e      	asr r0,r0,0x10
8e000b3a:	f54c 2401 	ldr fp,[sp,+0xa]
8e000b3e:	b41b 2405 	add sp,sp,40
8e000b42:	194f 0402 	rts
8e000b46:	01a2      	nop

Disassembly of section .shared_dram:

8f000000 <BJK_OFF_CHIP_SHARED_MEM>:
	...

Disassembly of section .text:

00000100 <normal_start>:
 100:	be0b 27f2 	mov sp,0x7ff0
 104:	a00b 3002 	movt sp,0x0
 108:	e00b 2002 	mov fp,0x0
 10c:	1feb 0032 	mov r0,0x3ff
 110:	050f 0402 	movts imask,r0
 114:	048b 0012 	mov r0,0x124
 118:	000b 1002 	movt r0,0x0
 11c:	010f 0402 	movts iret,r0
 120:	01d2      	rti
 122:	01a2      	nop

00000124 <main_caller>:
 124:	030b 0052 	mov r0,0x518
 128:	000b 1002 	movt r0,0x0
 12c:	0152      	jalr r0
 12e:	01a2      	nop
 130:	1feb 0032 	mov r0,0x3ff
 134:	050f 0402 	movts imask,r0
 138:	0392      	gid
 13a:	0fe2      	trap 0x3
 13c:	01a2      	nop

0000013e <infn_loop>:
 13e:	00e0      	b 13e <infn_loop>
 140:	01a2      	nop
 142:	194f 0402 	rts
 146:	01d2      	rti

00000148 <sync_interruption>:
 148:	14fc 0500 	strd r0,[sp,-0x1]
 14c:	0512      	movfs r0,status
 14e:	211f 0402 	movfs r1,iret
 152:	b41b 24fc 	add sp,sp,-32
 156:	0192      	gie
 158:	157c 0400 	strd r0,[sp,+0x2]
 15c:	f5dc 2400 	str fp,[sp,+0x3]
 160:	f4ef 2402 	mov fp,sp
 164:	050b 0062 	mov r0,0x628
 168:	000b 1002 	movt r0,0x0
 16c:	010c 0006 	ldrb r0,[r0,+0x32]
 170:	0093      	add r0,r0,1
 172:	2316      	lsl r1,r0,0x18
 174:	2706      	lsr r1,r1,0x18
 176:	050b 0062 	mov r0,0x628
 17a:	000b 1002 	movt r0,0x0
 17e:	211c 0006 	strb r1,[r0,+0x32]
 182:	01a2      	nop
 184:	156c 0400 	ldrd r0,[sp,+0x2]
 188:	f5cc 2400 	ldr fp,[sp,+0x3]
 18c:	0392      	gid
 18e:	b41b 2404 	add sp,sp,32
 192:	0502      	movts status,r0
 194:	210f 0402 	movts iret,r1
 198:	14ec 0500 	ldrd r0,[sp,-0x1]
 19c:	01d2      	rti
 19e:	01a2      	nop

000001a0 <soft_exception_interruption>:
 1a0:	14fc 0500 	strd r0,[sp,-0x1]
 1a4:	0512      	movfs r0,status
 1a6:	211f 0402 	movfs r1,iret
 1aa:	b41b 24fd 	add sp,sp,-24
 1ae:	0192      	gie
 1b0:	f5dc 2400 	str fp,[sp,+0x3]
 1b4:	f4ef 2402 	mov fp,sp
 1b8:	01a2      	nop
 1ba:	f5cc 2400 	ldr fp,[sp,+0x3]
 1be:	0392      	gid
 1c0:	b41b 2403 	add sp,sp,24
 1c4:	0502      	movts status,r0
 1c6:	210f 0402 	movts iret,r1
 1ca:	14ec 0500 	ldrd r0,[sp,-0x1]
 1ce:	01d2      	rti

000001d0 <mem_fault_interruption>:
 1d0:	14fc 0500 	strd r0,[sp,-0x1]
 1d4:	0512      	movfs r0,status
 1d6:	211f 0402 	movfs r1,iret
 1da:	b41b 24fd 	add sp,sp,-24
 1de:	0192      	gie
 1e0:	f5dc 2400 	str fp,[sp,+0x3]
 1e4:	f4ef 2402 	mov fp,sp
 1e8:	01a2      	nop
 1ea:	f5cc 2400 	ldr fp,[sp,+0x3]
 1ee:	0392      	gid
 1f0:	b41b 2403 	add sp,sp,24
 1f4:	0502      	movts status,r0
 1f6:	210f 0402 	movts iret,r1
 1fa:	14ec 0500 	ldrd r0,[sp,-0x1]
 1fe:	01d2      	rti

00000200 <timer0_interruption>:
 200:	14fc 0500 	strd r0,[sp,-0x1]
 204:	0512      	movfs r0,status
 206:	211f 0402 	movfs r1,iret
 20a:	b41b 24fd 	add sp,sp,-24
 20e:	0192      	gie
 210:	f5dc 2400 	str fp,[sp,+0x3]
 214:	f4ef 2402 	mov fp,sp
 218:	01a2      	nop
 21a:	f5cc 2400 	ldr fp,[sp,+0x3]
 21e:	0392      	gid
 220:	b41b 2403 	add sp,sp,24
 224:	0502      	movts status,r0
 226:	210f 0402 	movts iret,r1
 22a:	14ec 0500 	ldrd r0,[sp,-0x1]
 22e:	01d2      	rti

00000230 <timer1_interruption>:
 230:	14fc 0500 	strd r0,[sp,-0x1]
 234:	0512      	movfs r0,status
 236:	211f 0402 	movfs r1,iret
 23a:	b41b 24fd 	add sp,sp,-24
 23e:	0192      	gie
 240:	f5dc 2400 	str fp,[sp,+0x3]
 244:	f4ef 2402 	mov fp,sp
 248:	01a2      	nop
 24a:	f5cc 2400 	ldr fp,[sp,+0x3]
 24e:	0392      	gid
 250:	b41b 2403 	add sp,sp,24
 254:	0502      	movts status,r0
 256:	210f 0402 	movts iret,r1
 25a:	14ec 0500 	ldrd r0,[sp,-0x1]
 25e:	01d2      	rti

00000260 <message_interruption>:
 260:	14fc 0500 	strd r0,[sp,-0x1]
 264:	0512      	movfs r0,status
 266:	211f 0402 	movfs r1,iret
 26a:	b41b 24fd 	add sp,sp,-24
 26e:	0192      	gie
 270:	f5dc 2400 	str fp,[sp,+0x3]
 274:	f4ef 2402 	mov fp,sp
 278:	01a2      	nop
 27a:	f5cc 2400 	ldr fp,[sp,+0x3]
 27e:	0392      	gid
 280:	b41b 2403 	add sp,sp,24
 284:	0502      	movts status,r0
 286:	210f 0402 	movts iret,r1
 28a:	14ec 0500 	ldrd r0,[sp,-0x1]
 28e:	01d2      	rti

00000290 <dma0_interruption>:
 290:	14fc 0500 	strd r0,[sp,-0x1]
 294:	0512      	movfs r0,status
 296:	211f 0402 	movfs r1,iret
 29a:	b41b 24fd 	add sp,sp,-24
 29e:	0192      	gie
 2a0:	f5dc 2400 	str fp,[sp,+0x3]
 2a4:	f4ef 2402 	mov fp,sp
 2a8:	01a2      	nop
 2aa:	f5cc 2400 	ldr fp,[sp,+0x3]
 2ae:	0392      	gid
 2b0:	b41b 2403 	add sp,sp,24
 2b4:	0502      	movts status,r0
 2b6:	210f 0402 	movts iret,r1
 2ba:	14ec 0500 	ldrd r0,[sp,-0x1]
 2be:	01d2      	rti

000002c0 <dma1_interruption>:
 2c0:	14fc 0500 	strd r0,[sp,-0x1]
 2c4:	0512      	movfs r0,status
 2c6:	211f 0402 	movfs r1,iret
 2ca:	b41b 24fd 	add sp,sp,-24
 2ce:	0192      	gie
 2d0:	f5dc 2400 	str fp,[sp,+0x3]
 2d4:	f4ef 2402 	mov fp,sp
 2d8:	01a2      	nop
 2da:	f5cc 2400 	ldr fp,[sp,+0x3]
 2de:	0392      	gid
 2e0:	b41b 2403 	add sp,sp,24
 2e4:	0502      	movts status,r0
 2e6:	210f 0402 	movts iret,r1
 2ea:	14ec 0500 	ldrd r0,[sp,-0x1]
 2ee:	01d2      	rti

000002f0 <wand_interruption>:
 2f0:	14fc 0500 	strd r0,[sp,-0x1]
 2f4:	0512      	movfs r0,status
 2f6:	211f 0402 	movfs r1,iret
 2fa:	b41b 24fd 	add sp,sp,-24
 2fe:	0192      	gie
 300:	f5dc 2400 	str fp,[sp,+0x3]
 304:	f4ef 2402 	mov fp,sp
 308:	01a2      	nop
 30a:	f5cc 2400 	ldr fp,[sp,+0x3]
 30e:	0392      	gid
 310:	b41b 2403 	add sp,sp,24
 314:	0502      	movts status,r0
 316:	210f 0402 	movts iret,r1
 31a:	14ec 0500 	ldrd r0,[sp,-0x1]
 31e:	01d2      	rti

00000320 <user_interruption>:
 320:	14fc 0500 	strd r0,[sp,-0x1]
 324:	0512      	movfs r0,status
 326:	211f 0402 	movfs r1,iret
 32a:	b41b 24fd 	add sp,sp,-24
 32e:	0192      	gie
 330:	f5dc 2400 	str fp,[sp,+0x3]
 334:	f4ef 2402 	mov fp,sp
 338:	01a2      	nop
 33a:	f5cc 2400 	ldr fp,[sp,+0x3]
 33e:	0392      	gid
 340:	b41b 2403 	add sp,sp,24
 344:	0502      	movts status,r0
 346:	210f 0402 	movts iret,r1
 34a:	14ec 0500 	ldrd r0,[sp,-0x1]
 34e:	01d2      	rti

00000350 <bj_memset>:
 350:	f45c 2701 	str fp,[sp],-0x8
 354:	f4ef 2402 	mov fp,sp
 358:	1edc 0400 	str r0,[fp,+0x5]
 35c:	04e2      	mov r0,r1
 35e:	5ddc 0400 	str r2,[fp,+0x3]
 362:	1c1c 0402 	strb r0,[fp,+0x10]
 366:	0003      	mov r0,0x0
 368:	1fdc 0400 	str r0,[fp,+0x7]
 36c:	0003      	mov r0,0x0
 36e:	1fdc 0400 	str r0,[fp,+0x7]
 372:	0ee0      	b 38e <bj_memset+0x3e>
 374:	3ecc 0400 	ldr r1,[fp,+0x5]
 378:	1fcc 0400 	ldr r0,[fp,+0x7]
 37c:	041a      	add r0,r1,r0
 37e:	3c0c 0402 	ldrb r1,[fp,+0x10]
 382:	2014      	strb r1,[r0]
 384:	1fcc 0400 	ldr r0,[fp,+0x7]
 388:	0093      	add r0,r0,1
 38a:	1fdc 0400 	str r0,[fp,+0x7]
 38e:	3fcc 0400 	ldr r1,[fp,+0x7]
 392:	1dcc 0400 	ldr r0,[fp,+0x3]
 396:	443a      	sub r2,r1,r0
 398:	ee50      	bltu 374 <bj_memset+0x24>
 39a:	01a2      	nop
 39c:	f44c 2401 	ldr fp,[sp,+0x8]
 3a0:	b41b 2404 	add sp,sp,32
 3a4:	194f 0402 	rts

000003a8 <_ZN4cla14fun1Ev>:
 3a8:	f65c 2700 	str fp,[sp],-0x4
 3ac:	f4ef 2402 	mov fp,sp
 3b0:	1ddc 0400 	str r0,[fp,+0x3]
 3b4:	050b 0062 	mov r0,0x628
 3b8:	000b 1002 	movt r0,0x0
 3bc:	376b 0ff2 	mov r1,0xffbb
 3c0:	201c 0006 	strb r1,[r0,+0x30]
 3c4:	01a2      	nop
 3c6:	f64c 2400 	ldr fp,[sp,+0x4]
 3ca:	b41b 2402 	add sp,sp,16
 3ce:	194f 0402 	rts
 3d2:	01a2      	nop

000003d4 <_ZN4cla1D1Ev>:
 3d4:	f65c 2700 	str fp,[sp],-0x4
 3d8:	f4ef 2402 	mov fp,sp
 3dc:	1ddc 0400 	str r0,[fp,+0x3]
 3e0:	050b 0062 	mov r0,0x628
 3e4:	000b 1002 	movt r0,0x0
 3e8:	3bab 0ff2 	mov r1,0xffdd
 3ec:	209c 0006 	strb r1,[r0,+0x31]
 3f0:	01a2      	nop
 3f2:	f64c 2400 	ldr fp,[sp,+0x4]
 3f6:	b41b 2402 	add sp,sp,16
 3fa:	194f 0402 	rts
 3fe:	01a2      	nop

00000400 <cpp_main>:
 400:	d57c 2700 	strd lr,[sp],-0x2
 404:	f41b 2402 	add fp,sp,16
 408:	1f9b 04ff 	add r0,fp,-1
 40c:	350b 0032 	mov r1,0x3a8
 410:	200b 1002 	movt r1,0x0
 414:	0552      	jalr r1
 416:	1f9b 04ff 	add r0,fp,-1
 41a:	3a8b 0032 	mov r1,0x3d4
 41e:	200b 1002 	movt r1,0x0
 422:	0552      	jalr r1
 424:	01a2      	nop
 426:	d56c 2400 	ldrd lr,[sp,+0x2]
 42a:	b41b 2402 	add sp,sp,16
 42e:	194f 0402 	rts
 432:	01a2      	nop

00000434 <find_interrupt_call>:
 434:	f75c 2700 	str fp,[sp],-0x6
 438:	f4ef 2402 	mov fp,sp
 43c:	1ddc 0400 	str r0,[fp,+0x3]
 440:	1dcc 0400 	ldr r0,[fp,+0x3]
 444:	1edc 0400 	str r0,[fp,+0x5]
 448:	040b 0062 	mov r0,0x620
 44c:	000b 1002 	movt r0,0x0
 450:	2003      	mov r1,0x0
 452:	2034      	strh r1,[r0]
 454:	51e0      	b 4f6 <find_interrupt_call+0xc2>
 456:	1ecc 0400 	ldr r0,[fp,+0x5]
 45a:	2024      	ldrh r1,[r0]
 45c:	1f8b 0142 	mov r0,0x14fc
 460:	443a      	sub r2,r1,r0
 462:	2c10      	bne 4ba <find_interrupt_call+0x86>
 464:	1ecc 0400 	ldr r0,[fp,+0x5]
 468:	0113      	add r0,r0,2
 46a:	2024      	ldrh r1,[r0]
 46c:	000b 0052 	mov r0,0x500
 470:	443a      	sub r2,r1,r0
 472:	2410      	bne 4ba <find_interrupt_call+0x86>
 474:	1ecc 0400 	ldr r0,[fp,+0x5]
 478:	021b 0000 	add r0,r0,4
 47c:	2024      	ldrh r1,[r0]
 47e:	024b 0052 	mov r0,0x512
 482:	443a      	sub r2,r1,r0
 484:	1b10      	bne 4ba <find_interrupt_call+0x86>
 486:	1ecc 0400 	ldr r0,[fp,+0x5]
 48a:	031b 0000 	add r0,r0,6
 48e:	2024      	ldrh r1,[r0]
 490:	03eb 0212 	mov r0,0x211f
 494:	443a      	sub r2,r1,r0
 496:	1210      	bne 4ba <find_interrupt_call+0x86>
 498:	1ecc 0400 	ldr r0,[fp,+0x5]
 49c:	001b 0001 	add r0,r0,8
 4a0:	2024      	ldrh r1,[r0]
 4a2:	004b 0042 	mov r0,0x402
 4a6:	443a      	sub r2,r1,r0
 4a8:	0910      	bne 4ba <find_interrupt_call+0x86>
 4aa:	040b 0062 	mov r0,0x620
 4ae:	000b 1002 	movt r0,0x0
 4b2:	3dcb 02e2 	mov r1,0x2eee
 4b6:	2034      	strh r1,[r0]
 4b8:	23e0      	b 4fe <find_interrupt_call+0xca>
 4ba:	1ecc 0400 	ldr r0,[fp,+0x5]
 4be:	2024      	ldrh r1,[r0]
 4c0:	09eb 0192 	mov r0,0x194f
 4c4:	443a      	sub r2,r1,r0
 4c6:	1310      	bne 4ec <find_interrupt_call+0xb8>
 4c8:	1ecc 0400 	ldr r0,[fp,+0x5]
 4cc:	0113      	add r0,r0,2
 4ce:	2024      	ldrh r1,[r0]
 4d0:	004b 0042 	mov r0,0x402
 4d4:	443a      	sub r2,r1,r0
 4d6:	0b10      	bne 4ec <find_interrupt_call+0xb8>
 4d8:	040b 0062 	mov r0,0x620
 4dc:	000b 1002 	movt r0,0x0
 4e0:	2423      	mov r1,0x21
 4e2:	2034      	strh r1,[r0]
 4e4:	0003      	mov r0,0x0
 4e6:	1edc 0400 	str r0,[fp,+0x5]
 4ea:	0ae0      	b 4fe <find_interrupt_call+0xca>
 4ec:	1ecc 0400 	ldr r0,[fp,+0x5]
 4f0:	0313      	add r0,r0,-2
 4f2:	1edc 0400 	str r0,[fp,+0x5]
 4f6:	1ecc 0400 	ldr r0,[fp,+0x5]
 4fa:	2033      	sub r1,r0,0
 4fc:	ad10      	bne 456 <find_interrupt_call+0x22>
 4fe:	1ecc 0400 	ldr r0,[fp,+0x5]
 502:	f74c 2400 	ldr fp,[sp,+0x6]
 506:	b41b 2403 	add sp,sp,24
 50a:	194f 0402 	rts
 50e:	01a2      	nop

00000510 <fun10>:
 510:	154b 00a2 	mov r0,0xaaa
 514:	194f 0402 	rts

00000518 <main>:
 518:	d5fc 2700 	strd lr,[sp],-0x3
 51c:	f41b 2403 	add fp,sp,24
 520:	000b 0002 	mov r0,0x0
 524:	000b 18e2 	movt r0,0x8e00
 528:	0152      	jalr r0
 52a:	0003      	mov r0,0x0
 52c:	1fbc 0500 	strh r0,[fp,-0x7]
 530:	051f 0032 	movfs r0,coreid
 534:	1fbc 0500 	strh r0,[fp,-0x7]
 538:	1fac 0500 	ldrh r0,[fp,-0x7]
 53c:	1cbc 0500 	strh r0,[fp,-0x1]
 540:	1cac 0500 	ldrh r0,[fp,-0x1]
 544:	2296      	lsl r1,r0,0x14
 546:	1f8b 0002 	mov r0,0xfc
 54a:	01eb 1002 	movt r0,0xf
 54e:	047a      	orr r0,r1,r0
 550:	1d5c 0500 	str r0,[fp,-0x2]
 554:	1d4c 0500 	ldr r0,[fp,-0x2]
 558:	1ddc 0500 	str r0,[fp,-0x3]
 55c:	050b 0062 	mov r0,0x628
 560:	000b 1002 	movt r0,0x0
 564:	202b 0be2 	mov r1,0xbe01
 568:	214b 1002 	movt r1,0xa
 56c:	2354      	str r1,[r0,0x6]
 56e:	050b 0062 	mov r0,0x628
 572:	000b 1002 	movt r0,0x0
 576:	204b 0be2 	mov r1,0xbe02
 57a:	214b 1002 	movt r1,0xa
 57e:	23d4      	str r1,[r0,0x7]
 580:	050b 0062 	mov r0,0x628
 584:	000b 1002 	movt r0,0x0
 588:	3dcb 00e2 	mov r1,0xeee
 58c:	21d4      	str r1,[r0,0x3]
 58e:	1e2b 0ff2 	mov r0,0xfff1
 592:	1f9c 0501 	strb r0,[fp,-0xf]
 596:	0c0b 0062 	mov r0,0x660
 59a:	000b 1002 	movt r0,0x0
 59e:	0044      	ldr r0,[r0]
 5a0:	3f8c 0501 	ldrb r1,[fp,-0xf]
 5a4:	2314      	strb r1,[r0,0x6]
 5a6:	0c0b 0062 	mov r0,0x660
 5aa:	000b 1002 	movt r0,0x0
 5ae:	0044      	ldr r0,[r0]
 5b0:	0304      	ldrb r0,[r0,0x6]
 5b2:	3f8c 0501 	ldrb r1,[fp,-0xf]
 5b6:	443a      	sub r2,r1,r0
 5b8:	f710      	bne 5a6 <main+0x8e>
 5ba:	0003      	mov r0,0x0
 5bc:	d5ec 2400 	ldrd lr,[sp,+0x3]
 5c0:	b41b 2403 	add sp,sp,24
 5c4:	194f 0402 	rts

Disassembly of section .bss:

000005c8 <__FIRST_PROG_VAR__>:
	...

000005d0 <bjk_dbg_call_stack_trace>:
	...

00000620 <bjk_trace_err>:
	...

00000628 <bj_in_core_shd>:
	...

00000660 <bj_off_core_pt>:
	...

00000668 <bj_glb_sys>:
	...

00000670 <aux_val>:
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

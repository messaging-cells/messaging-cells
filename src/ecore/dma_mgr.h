
// attribute.h

#ifndef BJ_DMA_MGR_H
#define BJ_DMA_MGR_H

#include "shared.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
  These defs can be or'd together to form a value suitable for
  the dma config reg.
*/
typedef enum
{
	BJ_DMA_ENABLE        = (1<<0),
	BJ_DMA_MASTER        = (1<<1),
	BJ_DMA_CHAIN         = (1<<2),
	BJ_DMA_STARTUP       = (1<<3),
	BJ_DMA_IRQEN         = (1<<4),
	BJ_DMA_BYTE          = (0<<5),
	BJ_DMA_HWORD         = (1<<5),
	BJ_DMA_WORD          = (2<<5),
	BJ_DMA_DWORD         = (3<<5),
	BJ_DMA_MSGMODE       = (1<<10),
	BJ_DMA_SHIFT_SRC_IN  = (1<<12),
	BJ_DMA_SHIFT_DST_IN  = (1<<13),
	BJ_DMA_SHIFT_SRC_OUT = (1<<14),
	BJ_DMA_SHIFT_DST_OUT = (1<<15),
} bj_dma_config_t;

typedef enum
{
	BJ_DMA_0 = 0,
	BJ_DMA_1 = 1,
} bj_dma_id_t;

struct bj_align(8) bj_dma_desc_def
{
	unsigned 	config;
	unsigned 	inner_stride;
	unsigned 	count;
	unsigned 	outer_stride;
	void* 		src_addr;
	void* 		dst_addr;
};
typedef struct bj_dma_desc_def bj_dam_desc_st;

/*
void e_dma_set_desc(
		e_dma_id_t chan,
		unsigned config,     e_dma_desc_t *next_desc,
		unsigned strd_i_src, unsigned strd_i_dst,
		unsigned count_i,    unsigned count_o,
		unsigned strd_o_src, unsigned strd_o_dst,
		void     *addr_src,  void *addr_dst,
		e_dma_desc_t *desc)
{
	e_dma_wait(chan);
	desc->config       = (((unsigned) next_desc) << 16) | config;
	desc->inner_stride = (strd_i_dst             << 16) | strd_i_src;
	desc->count        = (count_o                << 16) | count_i;
	desc->outer_stride = (strd_o_dst             << 16) | strd_o_src;
	desc->src_addr     = addr_src;
	desc->dst_addr     = addr_dst;

	return;
}


*/

#ifdef __cplusplus
}
#endif

#endif // BJ_DMA_MGR_H


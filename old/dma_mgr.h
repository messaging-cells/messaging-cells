
// attribute.h

#ifndef MC_DMA_MGR_H
#define MC_DMA_MGR_H

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
	MC_DMA_ENABLE        = (1<<0),
	MC_DMA_MASTER        = (1<<1),
	MC_DMA_CHAIN         = (1<<2),
	MC_DMA_STARTUP       = (1<<3),
	MC_DMA_IRQEN         = (1<<4),
	MC_DMA_BYTE          = (0<<5),
	MC_DMA_HWORD         = (1<<5),
	MC_DMA_WORD          = (2<<5),
	MC_DMA_DWORD         = (3<<5),
	MC_DMA_MSGMODE       = (1<<10),
	MC_DMA_SHIFT_SRC_IN  = (1<<12),
	MC_DMA_SHIFT_DST_IN  = (1<<13),
	MC_DMA_SHIFT_SRC_OUT = (1<<14),
	MC_DMA_SHIFT_DST_OUT = (1<<15),
} mc_dma_config_t;

typedef enum
{
	MC_DMA_0 = 0,
	MC_DMA_1 = 1,
} mc_dma_id_t;

struct mc_align(8) mc_dma_desc_def
{
	unsigned 	config;
	unsigned 	inner_stride;
	unsigned 	count;
	unsigned 	outer_stride;
	void* 		src_addr;
	void* 		dst_addr;
};
typedef struct mc_dma_desc_def mc_dam_desc_st;

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

#endif // MC_DMA_MGR_H


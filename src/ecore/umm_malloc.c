// ----------------------------------------------------------------------------
// umm_malloc.c - a memory allocator for embedded systems (microcontrollers)
//
// See copyright notice below
// ----------------------------------------------------------------------------
//
// R.Hempel 2007-09-22 - Original
// R.Hempel 2008-12-11 - Added MIT License biolerplate
//                     - realloc() now looks to see if previous block is free
//                     - made common operations functions            
// R.Hempel 2009-03-02 - Added macros to disable tasking
//                     - Added function to dump heap and check for valid free
//                        pointer
// R.Hempel 2009-03-09 - Changed name to umm_malloc to avoid conflicts with
//                        the mm_malloc() library functions
//                     - Added some test code to assimilate a free block
//                        with the very block if possible. Complicated and
//                        not worth the grief.
// D.Frank 2014-04-02  - Fixed heap configuration when UMM_TEST_MAIN is NOT set,
//                        added user-dependent configuration file umm_malloc_cfg.h
// ----------------------------------------------------------------------------
//
// This is a memory management library specifically designed to work with the
// ARM7 embedded processor, but it should work on many other 32 bit processors,
// as well as 16 and 8 bit devices.
//
// ACKNOWLEDGEMENTS
//
// Joerg Wunsch and the avr-libc provided the first malloc() implementation
// that I examined in detail.
//
// http://www.nongnu.org/avr-libc
//
// Doug Lea's paper on malloc() was another excellent reference and provides
// a lot of detail on advanced memory management techniques such as binning.
// 
// http://g.oswego.edu/dl/html/malloc.html
//
// Bill Dittman provided excellent suggestions, including macros to support
// using these functions in critical sections, and for optimizing realloc()
// further by checking to see if the previous block was free and could be 
// used for the new block size. This can help to reduce heap fragmentation
// significantly. 
//
// Yaniv Ankin suggested that a way to dump the current heap condition
// might be useful. I combined this with an idea from plarroy to also
// allow checking a free pointer to make sure it's valid.
//
// ----------------------------------------------------------------------------
// Copyright (c) 2007-2008 Ralph Hempel
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
// ----------------------------------------------------------------------------

#include <string.h>

#include "umm_malloc.h"

// ----------------------------------------------------------------------------

umm_block umm_heap[UMM_HEAP_NUM_BLOCKS];

const umm_idx_t umm_numblocks = (sizeof(umm_heap) / sizeof(umm_block));

#define UMM_NUMBLOCKS (umm_numblocks)

// ----------------------------------------------------------------------------

#define UMM_BLOCK(b)  (umm_heap[b])

#define UMM_NBLOCK(b) (UMM_BLOCK(b).header.used.next)
#define UMM_PBLOCK(b) (UMM_BLOCK(b).header.used.prev)
#define UMM_NFREE(b)  (UMM_BLOCK(b).body.free.next)
#define UMM_PFREE(b)  (UMM_BLOCK(b).body.free.prev)
#define UMM_DATA(b)   (UMM_BLOCK(b).body.data)

// ----------------------------------------------------------------------------
// One of the coolest things about this little library is that it's VERY
// easy to get debug information about the memory heap by simply iterating
// through all of the memory blocks.
//
// As you go through all the blocks, you can check to see if it's a free
// block by looking at the high order bit of the next block index. You can
// also see how big the block is by subtracting the next block index from
// the current block number.
//
// The umm_info function does all of that and makes the results available
// in the heapInfo structure.
// ----------------------------------------------------------------------------

UMM_HEAP_INFO heapInfo;

// ----------------------------------------------------------------------------
// local declarations

umm_opt_sz_fn static umm_idx_t 
umm_blocks( umm_size_t size );

umm_opt_sz_fn static void 
umm_make_new_block( umm_idx_t c, umm_idx_t blocks, umm_idx_t freemask );

umm_opt_sz_fn static void 
umm_disconnect_from_free_list( umm_idx_t c );

umm_opt_sz_fn static void 
umm_assimilate_up( umm_idx_t c );

umm_opt_sz_fn static umm_idx_t 
umm_assimilate_down( umm_idx_t c, umm_idx_t freemask );

// ----------------------------------------------------------------------------

void *
umm_info( void *ptr, int force ) {

   umm_idx_t blockNo = 0;

   // Protect the critical section...
   //
   UMM_CRITICAL_ENTRY();

   // Clear out all of the entries in the heapInfo structure before doing
   // any calculations..
   //
   umm_memset( (void*)(&heapInfo), 0, sizeof( heapInfo ) );

   UMM_DBG_LOG_FORCE( force, "\n\nDumping the umm_heap...\n" );

   UMM_DBG_LOG_FORCE( force, "|0x%p|B %5i|NB %5i|PB %5i|Z %5i|NF %5i|PF %5i|\n",
         (&UMM_BLOCK(blockNo)),
         blockNo,
         UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK,
         UMM_PBLOCK(blockNo),
         (UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK )-blockNo,
         UMM_NFREE(blockNo),
         UMM_PFREE(blockNo) );

   // Now loop through the block lists, and keep track of the number and size
   // of used and free blocks. The terminating condition is an nb pointer with
   // a value of zero...

   blockNo = UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK;

   while( UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK ) {
      ++heapInfo.totalEntries;
      heapInfo.totalBlocks += (UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK )-blockNo;

      // Is this a free block?

      if( UMM_NBLOCK(blockNo) & UMM_FREELIST_MASK ) {
         ++heapInfo.freeEntries;
         heapInfo.freeBlocks += (UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK )-blockNo;

         UMM_DBG_LOG_FORCE( force, "|0x%p|B %5i|NB %5i|PB %5i|Z %5i|NF %5i|PF %5i|\n",
               (&UMM_BLOCK(blockNo)),
               blockNo,
               UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK,
               UMM_PBLOCK(blockNo),
               (UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK )-blockNo,
               UMM_NFREE(blockNo),
               UMM_PFREE(blockNo) );

         // Does this block address match the ptr we may be trying to free?

         if( ptr == &UMM_BLOCK(blockNo) ) {

            // Release the critical section...
            //
            UMM_CRITICAL_EXIT();

            return( ptr );
         }
      } else {
         ++heapInfo.usedEntries;
         heapInfo.usedBlocks += (UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK )-blockNo;

         UMM_DBG_LOG_FORCE( force, "|0x%p|B %5i|NB %5i|PB %5i|Z %5i|\n",
               (&UMM_BLOCK(blockNo)),
               blockNo,
               UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK,
               UMM_PBLOCK(blockNo),
               (UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK )-blockNo );
      }

      blockNo = UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK;
   }

   // Update the accounting totals with information from the last block, the
   // rest must be free!

   heapInfo.freeBlocks  += UMM_NUMBLOCKS-blockNo;
   heapInfo.totalBlocks += UMM_NUMBLOCKS-blockNo;

   UMM_DBG_LOG_FORCE( force, "|0x%p|B %5i|NB %5i|PB %5i|Z %5i|NF %5i|PF %5i|\n",
         (&UMM_BLOCK(blockNo)),
         blockNo,
         UMM_NBLOCK(blockNo) & UMM_BLOCKNO_MASK,
         UMM_PBLOCK(blockNo),
         UMM_NUMBLOCKS-blockNo,
         UMM_NFREE(blockNo),
         UMM_PFREE(blockNo) );

   UMM_DBG_LOG_FORCE( force, "Total Entries %5i    Used Entries %5i    Free Entries %5i\n",
         heapInfo.totalEntries,
         heapInfo.usedEntries,
         heapInfo.freeEntries );

   UMM_DBG_LOG_FORCE( force, "Total Blocks  %5i    Used Blocks  %5i    Free Blocks  %5i\n",
         heapInfo.totalBlocks,
         heapInfo.usedBlocks,
         heapInfo.freeBlocks  );

   // Release the critical section...
   //
   UMM_CRITICAL_EXIT();

   return( umm_null );
}

// ----------------------------------------------------------------------------

static umm_idx_t 
umm_blocks( umm_size_t size ) {

   // The calculation of the block size is not too difficult, but there are
   // a few little things that we need to be mindful of.
   //
   // When a block removed from the free list, the space used by the free
   // pointers is available for data. That's what the first calculation
   // of size is doing.

   if( size <= (sizeof(((umm_block *)0)->body)) )
      return( 1 );

   // If it's for more than that, then we need to figure out the number of
   // additional whole blocks the size of an umm_block are required.

   size -= ( 1 + (sizeof(((umm_block *)0)->body)) );

   return( 2 + size/(sizeof(umm_block)) );
}

// ----------------------------------------------------------------------------

static void 
umm_make_new_block( umm_idx_t c, umm_idx_t blocks, umm_idx_t freemask ) {

   UMM_NBLOCK(c+blocks) = UMM_NBLOCK(c) & UMM_BLOCKNO_MASK;
   UMM_PBLOCK(c+blocks) = c;

   UMM_PBLOCK(UMM_NBLOCK(c) & UMM_BLOCKNO_MASK) = (c+blocks);
   UMM_NBLOCK(c)                                = (c+blocks) | freemask;
}

// ----------------------------------------------------------------------------

static void 
umm_disconnect_from_free_list( umm_idx_t c ) {
   // Disconnect this block from the FREE list

   UMM_NFREE(UMM_PFREE(c)) = UMM_NFREE(c);
   UMM_PFREE(UMM_NFREE(c)) = UMM_PFREE(c);

   // And clear the free block indicator

   UMM_NBLOCK(c) &= (~UMM_FREELIST_MASK);
}

// ----------------------------------------------------------------------------

static void 
umm_assimilate_up( umm_idx_t c ) {

   if( UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_FREELIST_MASK ) {
      // The next block is a free block, so assimilate up and remove it from
      // the free list

      UMM_DBG_LOG_DEBUG( "Assimilate up to next block, which is FREE\n" );

      // Disconnect the next block from the FREE list

      umm_disconnect_from_free_list( UMM_NBLOCK(c) );

      // Assimilate the next block with this one

      UMM_PBLOCK(UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_BLOCKNO_MASK) = c;
      UMM_NBLOCK(c) = UMM_NBLOCK(UMM_NBLOCK(c)) & UMM_BLOCKNO_MASK;
   } 
}

// ----------------------------------------------------------------------------

static umm_idx_t 
umm_assimilate_down( umm_idx_t c, umm_idx_t freemask ) {

   UMM_NBLOCK(UMM_PBLOCK(c)) = UMM_NBLOCK(c) | freemask;
   UMM_PBLOCK(UMM_NBLOCK(c)) = UMM_PBLOCK(c);

   return( UMM_PBLOCK(c) );
}

// ----------------------------------------------------------------------------

void 
umm_free( void *ptr ) {

   umm_idx_t c;

   // If we're being asked to free a NULL pointer, well that's just silly!

   if( (void *)umm_null == ptr ) {
      UMM_DBG_LOG_DEBUG( "free a null pointer -> do nothing\n" );

      return;
   }

   // FIXME: At some point it might be a good idea to add a check to make sure
   //        that the pointer we're being asked to free up is actually within
   //        the umm_heap!
   //
   // NOTE:  See the new umm_info() function that you can use to see if a ptr is
   //        on the free list!

   // Protect the critical section...
   //
   UMM_CRITICAL_ENTRY();

   // Figure out which block we're in. Note the use of truncated division...

   c = (ptr-(void *)(&(umm_heap[0])))/sizeof(umm_block);

   UMM_DBG_LOG_DEBUG( "Freeing block %6i\n", c );

   // Now let's assimilate this block with the next one if possible.

   umm_assimilate_up( c );

   // Then assimilate with the previous block if possible

   if( UMM_NBLOCK(UMM_PBLOCK(c)) & UMM_FREELIST_MASK ) {

      UMM_DBG_LOG_DEBUG( "Assimilate down to next block, which is FREE\n" );

      c = umm_assimilate_down(c, UMM_FREELIST_MASK);
   } else {
      // The previous block is not a free block, so add this one to the head
      // of the free list

      UMM_DBG_LOG_DEBUG( "Just add to head of free list\n" );

      UMM_PFREE(UMM_NFREE(0)) = c;
      UMM_NFREE(c)            = UMM_NFREE(0);
      UMM_PFREE(c)            = 0;
      UMM_NFREE(0)            = c;

      UMM_NBLOCK(c)          |= UMM_FREELIST_MASK;
   }

   // Release the critical section...
   //
   UMM_CRITICAL_EXIT();
}

// ----------------------------------------------------------------------------

void *
umm_malloc( umm_size_t size ) {

   umm_idx_t blocks;
   /* volatile --COMMENTED BY DFRANK because the version from FreeRTOS doesn't have it*/
   umm_idx_t blockSize = 0;

   umm_idx_t bestSize;
   umm_idx_t bestBlock;

   umm_idx_t cf;

   // the very first thing we do is figure out if we're being asked to allocate
   // a size of 0 - and if we are we'll simply return a null pointer. if not
   // then reduce the size by 1 byte so that the subsequent calculations on
   // the number of blocks to allocate are easier...

   if( 0 == size ) {
      UMM_DBG_LOG_DEBUG( "malloc a block of 0 bytes -> do nothing\n" );

      return( (void *)umm_null );
   }

   // Protect the critical section...
   //
   UMM_CRITICAL_ENTRY();

   blocks = umm_blocks( size );

   // Now we can scan through the free list until we find a space that's big
   // enough to hold the number of blocks we need.
   //
   // This part may be customized to be a best-fit, worst-fit, or first-fit
   // algorithm

   cf = UMM_NFREE(0);

   bestBlock = UMM_NFREE(0);
   bestSize  = 0x7FFF;

   while( UMM_NFREE(cf) ) {
      blockSize = (UMM_NBLOCK(cf) & UMM_BLOCKNO_MASK) - cf;

      UMM_DBG_LOG_TRACE( "Looking at block %6i size %6i\n", cf, blockSize );

#if defined UMM_FIRST_FIT
      // This is the first block that fits!
      if( (blockSize >= blocks) )
         break;
#elif defined UMM_BEST_FIT
      if( (blockSize >= blocks) && (blockSize < bestSize) ) {
         bestBlock = cf;
         bestSize  = blockSize;
      }
#endif

      cf = UMM_NFREE(cf);
   }

   if( 0x7FFF != bestSize ) {
      cf        = bestBlock;
      blockSize = bestSize;
   }

   if( UMM_NBLOCK(cf) & UMM_BLOCKNO_MASK ) {
      // This is an existing block in the memory heap, we just need to split off
      // what we need, unlink it from the free list and mark it as in use, and
      // link the rest of the block back into the freelist as if it was a new
      // block on the free list...

      if( blockSize == blocks ) {
         // It's an exact fit and we don't neet to split off a block.
         UMM_DBG_LOG_DEBUG( "Allocating %6i blocks starting at %6i - exact\n", blocks, cf );

         // Disconnect this block from the FREE list

         umm_disconnect_from_free_list( cf );

      } else {
         // It's not an exact fit and we need to split off a block.
         UMM_DBG_LOG_DEBUG( "Allocating %6i blocks starting at %6i - existing\n", blocks, cf );

         umm_make_new_block( cf, blockSize-blocks, UMM_FREELIST_MASK );

         cf += blockSize-blocks;
      }
   } else {
      // We're at the end of the heap - allocate a new block, but check to see if
      // there's enough memory left for the requested block! Actually, we may need
      // one more than that if we're initializing the umm_heap for the first
      // time, which happens in the next conditional...

      if( UMM_NUMBLOCKS <= cf+blocks+1 ) {
         UMM_DBG_LOG_DEBUG(  "Can't allocate %5i blocks at %5i\n", blocks, cf );

         // Release the critical section...
         //
         UMM_CRITICAL_EXIT();

         return( (void *)umm_null );
      }

      // Now check to see if we need to initialize the free list...this assumes
      // that the BSS is set to 0 on startup. We should rarely get to the end of
      // the free list so this is the "cheapest" place to put the initialization!

      if( 0 == cf ) {
         UMM_DBG_LOG_DEBUG( "Initializing malloc free block pointer\n" );
         UMM_NBLOCK(0) = 1;
         UMM_NFREE(0)  = 1;
         cf            = 1;
      }

      UMM_DBG_LOG_DEBUG( "Allocating %6i blocks starting at %6i - new     \n", blocks, cf );

      UMM_NFREE(UMM_PFREE(cf)) = cf+blocks;

      umm_memcpy( (void*)(&UMM_BLOCK(cf+blocks)), (void*)(&UMM_BLOCK(cf)), sizeof(umm_block) );

      UMM_NBLOCK(cf)           = cf+blocks;
      UMM_PBLOCK(cf+blocks)    = cf;
   }

   // Release the critical section...
   //
   UMM_CRITICAL_EXIT();

   return( (void *)&UMM_DATA(cf) );
}

// ----------------------------------------------------------------------------

void *
umm_realloc( void *ptr, umm_size_t size ) {

   umm_idx_t blocks;
   umm_idx_t blockSize;

   umm_idx_t c;

   umm_size_t curSize;

   // This code looks after the case of a NULL value for ptr. The ANSI C
   // standard says that if ptr is NULL and size is non-zero, then we've
   // got to work the same a malloc(). If size is also 0, then our version
   // of malloc() returns a NULL pointer, which is OK as far as the ANSI C
   // standard is concerned.

   if( ((void *)umm_null == ptr) ) {
      UMM_DBG_LOG_DEBUG( "realloc the NULL pointer - call malloc()\n" );

      return( umm_malloc(size) );
   }

   // Now we're sure that we have a non_NULL ptr, but we're not sure what
   // we should do with it. If the size is 0, then the ANSI C standard says that
   // we should operate the same as free.

   if( 0 == size ) {
      UMM_DBG_LOG_DEBUG( "realloc to 0 size, just free the block\n" );

      umm_free( ptr );

      return( (void *)umm_null );
   }

   // Protect the critical section...
   //
   UMM_CRITICAL_ENTRY();

   // Otherwise we need to actually do a reallocation. A naiive approach
   // would be to malloc() a new block of the correct size, copy the old data
   // to the new block, and then free the old block.
   //
   // While this will work, we end up doing a lot of possibly unnecessary
   // copying. So first, let's figure out how many blocks we'll need.

   blocks = umm_blocks( size );

   // Figure out which block we're in. Note the use of truncated division...

   c = (ptr-(void *)(&(umm_heap[0])))/sizeof(umm_block);

   // Figure out how big this block is...

   blockSize = (UMM_NBLOCK(c) - c);

   // Figure out how many bytes are in this block

   curSize   = (blockSize*sizeof(umm_block))-(sizeof(((umm_block *)0)->header));

   // Ok, now that we're here, we know the block number of the original chunk
   // of memory, and we know how much new memory we want, and we know the original
   // block size...

   if( blockSize == blocks ) {
      // This space intentionally left blank - return the original pointer!

      UMM_DBG_LOG_DEBUG( "realloc the same size block - %i, do nothing\n", blocks );

      // Release the critical section...
      //
      UMM_CRITICAL_EXIT();

      return( ptr );
   }

   // Now we have a block size that could be bigger or smaller. Either
   // way, try to assimilate up to the next block before doing anything...
   //
   // If it's still too small, we have to free it anyways and it will save the
   // assimilation step later in free :-)

   umm_assimilate_up( c );

   // Now check if it might help to assimilate down, but don't actually
   // do the downward assimilation unless the resulting block will hold the
   // new request! If this block of code runs, then the new block will
   // either fit the request exactly, or be larger than the request.

   if( (UMM_NBLOCK(UMM_PBLOCK(c)) & UMM_FREELIST_MASK) &&
         (blocks <= (UMM_NBLOCK(c)-UMM_PBLOCK(c)))    ) {

      // Check if the resulting block would be big enough...

      UMM_DBG_LOG_DEBUG( "realloc() could assimilate down %i blocks - fits!\n\r", 
			c-UMM_PBLOCK(c) );

      // Disconnect the previous block from the FREE list

      umm_disconnect_from_free_list( UMM_PBLOCK(c) );

      // Connect the previous block to the next block ... and then
      // realign the current block pointer

      c = umm_assimilate_down(c, 0);

      // Move the bytes down to the new block we just created, but be sure to move
      // only the original bytes.

      umm_memmove( (void *)&UMM_DATA(c), ptr, curSize );

      // And don't forget to adjust the pointer to the new block location!

      ptr    = (void *)&UMM_DATA(c);
   }

   // Now calculate the block size again...and we'll have three cases

   blockSize = (UMM_NBLOCK(c) - c);

   if( blockSize == blocks ) {
      // This space intentionally left blank - return the original pointer!

      UMM_DBG_LOG_DEBUG( "realloc the same size block - %i, do nothing\n", blocks );

   } else if (blockSize > blocks ) {
      // New block is smaller than the old block, so just make a new block
      // at the end of this one and put it up on the free list...

      UMM_DBG_LOG_DEBUG( "realloc %i to smaller block %i, shrink & free the leftover bits\n",
			blockSize, blocks );

      umm_make_new_block( c, blocks, 0 );

      umm_free( (void *)&UMM_DATA(c+blocks) );
   } else {
      // New block is bigger than the old block...

      void *oldptr = ptr;

      UMM_DBG_LOG_DEBUG( "realloc %i to bigger block %i, make new, copy & free the old\n",
			blockSize, blocks );

      // Now umm_malloc() a new/ one, copy the old data to the new block, and
      // free up the old block, but only if the malloc was sucessful!

      if( (ptr = umm_malloc( size )) ) {
         umm_memcpy( ptr, oldptr, curSize );
      }

      umm_free( oldptr );
   }

   // Release the critical section...
   //
   UMM_CRITICAL_EXIT();

   return( ptr );
}

// ----------------------------------------------------------------------------


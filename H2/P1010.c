void put_there(void* block_ptr, size_t alloc_size)
{
    size_t current_size = GET_SIZE(block_prt);

    if(current_size < (DSIZE + WSIZE))
    {
        PUT(HDRP(block_ptr), PACK(alloc_size,1));
        PUT(FTRP(block_ptr), PACK(alloc_size,1));
    }
    else
    {
        PUT(HDRP(block_ptr),PACK(alloc_size,1)); // Place contents in block
        PUT(FTRP(block_ptr),PACK(alloc_size,1));    // Place contents in block after previous entry
        block_ptr = NEXT_BLKP(block_ptr);   // increment block to next block

        /* Since current_size > the block size and the block 1
        *  is already holding a value,the new block will be fragmented
        */
        PUT(HRP(block_ptr),PACK(current_size-alloc_size, 0));
        PUT(FTRP(block_ptr),PACK(current_size-alloc_size, 0));
    }
}

#ifndef __LINUX_SLOB_DEF_H
#define __LINUX_SLOB_DEF_H

#ifndef ARCH_KMALLOC_MINALIGN
#define ARCH_KMALLOC_MINALIGN __alignof__(unsigned long)
#endif

#ifndef ARCH_SLAB_MINALIGN
#define ARCH_SLAB_MINALIGN __alignof__(unsigned long)
#endif

void *kmem_cache_alloc_node(struct kmem_cache *, gfp_t flags, int node);

static __always_inline void *kmem_cache_alloc(struct kmem_cache *cachep,
					      gfp_t flags)
{
	return kmem_cache_alloc_node(cachep, flags, -1);
}

void *__kmalloc_node(size_t size, gfp_t flags, int node);

static __always_inline void *kmalloc_node(size_t size, gfp_t flags, int node)
{
	return __kmalloc_node(size, flags, node);
}

/**
 * kmalloc - allocate memory
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kcalloc).
 *
 * kmalloc is the normal method of allocating memory
 * in the kernel.
 */
static __always_inline void *kmalloc(size_t size, gfp_t flags)
{//kmalloc和get_free_page申请的内存位于物理内存映射区域，而且在物理上也是连续的，它们与真实的物理地址只有一个固定的偏移，因此存在较简单的转换关系，
	return __kmalloc_node(size, flags, -1);
}

static __always_inline void *__kmalloc(size_t size, gfp_t flags)
{
	return kmalloc(size, flags);
}

#endif /* __LINUX_SLOB_DEF_H */

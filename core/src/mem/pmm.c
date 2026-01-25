#include <mem/pmm.h>

uint64_t pmmTotalPages, pmmMmSize, pmmMmPages;
uint8_t* pmmMemmap;

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request mmRequest = {
    .id = LIMINE_MEMMAP_REQUEST_ID,
    .revision = 0
};

void* pmmAllocPage() {
    for (size_t i = 0; i < pmmTotalPages; i++) {
        if (!BIT_TEST(pmmMemmap, i)) {
            BIT_SET(pmmMemmap, i);
            return (void*)(i * PAGE_SIZE);
        }
    } return NULL;
}

void pmmFreePage(void* addr) {
    uint64_t page = (uint64_t)addr / PAGE_SIZE;
    BIT_CLEAR(pmmMemmap, page);
}

void InitPmm() {
    struct limine_memmap_response *mm = mmRequest.response;
    if (!mm) panic("No memmap found!");

    struct limine_memmap_entry* lastEntry = mm->entries[mm->entry_count - 1];
    pmmTotalPages = (lastEntry->base + lastEntry->length) / PAGE_SIZE;
    pmmMmSize = (pmmTotalPages + 7) >> 3;
    pmmMmPages = (pmmMmSize + PAGE_SIZE - 1) / PAGE_SIZE;

    uint64_t mmAddr = 0;
    for (size_t i = 0; i < mm->entry_count; i++) {
        struct limine_memmap_entry* entry = mm->entries[i];
        if (entry->type != LIMINE_MEMMAP_USABLE) continue;

        if (entry->length >= pmmMmPages * PAGE_SIZE) {
            mmAddr = entry->base;
            entry->base += pmmMmPages * PAGE_SIZE;
            entry->length -= pmmMmPages * PAGE_SIZE;
            break;
        }
    } if (!mmAddr) panic("No space for memmap found!");

    pmmMemmap = (uint8_t*)mmAddr;
    memset(pmmMemmap, 0xff, pmmMmSize);

    for (size_t i = 0; i < mm->entry_count; i++) {
        struct limine_memmap_entry* entry = mm->entries[i];
        if (entry->type != LIMINE_MEMMAP_USABLE) continue;

        uint64_t start = entry->base;
        uint64_t end = start + entry->length;

        for (uint64_t addr = start; addr < end; addr += PAGE_SIZE) {
            uint64_t page = addr / PAGE_SIZE;
            BIT_CLEAR(pmmMemmap, page);
        }
    }

    for (uint16_t i = 0; i < 256; i++)
        BIT_SET(pmmMemmap, i);
}

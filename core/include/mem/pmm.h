#pragma once
#include <stdint.h>
#include <stddef.h>
#include <limine.h>
#include <kernel/panic.h>
#include <drivers/display.h>

void* pmmAllocPage();
void pmmFreePage(void* addr);
void InitPmm();

#define PAGE_SIZE 4096
#define PAGES_PER_BUCKET 8

#define BIT_SET(bm, i)   (bm[(i) >> 3] |=  (1 << ((i) & 7)))
#define BIT_CLEAR(bm, i) (bm[(i) >> 3] &= ~(1 << ((i) & 7)))
#define BIT_TEST(bm, i)  (bm[(i) >> 3] &   (1 << ((i) & 7)))

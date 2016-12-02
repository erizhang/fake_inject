//fake_inject.h
#ifndef __FAKE_INJECT_H__
#define __FAKE_INJECT_H__

#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif

#define JUMP_CODE_MAX   0x05
#define JUMP_CODE_CMD   0xE9
#define JUMP_CODE_RET   0xC3

typedef struct FakeInfo {
  void *funcAddr;
  unsigned char byteCode[5];
} FakeInfo;

#define SET_FAKE_INJECT(FUNCNAME, FAKENAME) \
	FakeInfo FUNCNAME##_info;  \
	set_fake((void*)FUNCNAME, (void *)FAKENAME, &(FUNCNAME##_info));
#define RESET_FAKE_INJECT(FUNCNAME)\
	reset_fake(&FUNCNAME##_info);
  

extern void set_fake(void *funcAddr, void *FakeAddr, FakeInfo *si);
extern void reset_fake(FakeInfo *si);

static void set_jump_code(void *codeAddr, char jumpCode[JUMP_CODE_MAX]) {
  int pagesize = sysconf(_SC_PAGE_SIZE);
  if (mprotect((void*) ((unsigned long) codeAddr & (~(pagesize - 1))), pagesize, PROT_READ | PROT_WRITE | PROT_EXEC) != 0) {
    return;
  }
  memcpy(codeAddr, jumpCode, JUMP_CODE_MAX);
}

void set_fake(void *funcAddr, void *FakeAddr, FakeInfo *si) {
    char jumpCode[JUMP_CODE_MAX] = {JUMP_CODE_CMD};
    unsigned long  dist = (unsigned long)FakeAddr - (unsigned long)funcAddr - 5;

    memcpy((void *)&jumpCode[1], (void *)&dist, sizeof(void *));
    si->funcAddr = funcAddr;
    memcpy((void *)&si->byteCode[0], (void *)funcAddr, JUMP_CODE_MAX);

    set_jump_code(funcAddr, jumpCode);
}

void reset_fake(FakeInfo *si)
{
    char   jumpCode[JUMP_CODE_MAX];
    memcpy((void *)&jumpCode, (void *)&si->byteCode[0], JUMP_CODE_MAX);
    set_jump_code(si->funcAddr, jumpCode);
}

#ifdef __cplusplus
}
#endif


#endif /* __FAKE_INJECT_H__ */

#ifndef AMDILC_H_
#define AMDILC_H_

#include <stdio.h>
#include <stdint.h>
#define VK_NO_PROTOTYPES
#include "vulkan/vulkan.h"

// TODO pack resource IDs
#define ILC_ATOMIC_COUNTER_ID  (0)  // 0
#define ILC_BASE_SAMPLER_ID    (1)  // 1-16
#define ILC_BASE_RESOURCE_ID   (17) // 17+

#define ILC_MAX_STRIDE_CONSTANTS    (8)

typedef struct _IlcBinding {
    uint32_t index;
    VkDescriptorType descriptorType;
    int strideIndex; // Stride location in push constants (<0 means non-existent)
} IlcBinding;

typedef struct _IlcInput {
    uint32_t locationIndex;
    uint8_t interpMode;
} IlcInput;

typedef struct _IlcShader {
    unsigned codeSize;
    uint32_t* code;
    unsigned bindingCount;
    IlcBinding* bindings;
    unsigned inputCount;
    IlcInput* inputs;
    char* name;
} IlcShader;

IlcShader ilcCompileShader(
    const void* code,
    unsigned size);

IlcShader ilcCompileRectangleGeometryShader(
    unsigned psInputCount,
    const IlcInput* psInputs);

void ilcDisassembleShader(
    FILE* file,
    const void* code,
    unsigned size);

#endif // AMDILC_H_

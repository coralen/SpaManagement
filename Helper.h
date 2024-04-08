#ifndef _HELPER_H
#define _HELPER_H

#define CODE 3
#define CODE_EXPECTED "XXX"
#define TOTAL_CODE 5
#define MAX_STRING 255
#define MIN_TREATMENTS_FOR_AWARD 5

#define STRINGIFY(x) #x  // Macro to turn a value into a string
#define SCANF_FORMAT "%254[^\n]"  // Create the scanf format string, assuming MAX_STRING is 256

#define CHECK_NULL(ptr) if ((ptr) == NULL) return; //Macro to check if pointer is NULL

#define TREATMENT_TYPE_SWITCH_CASE(type, funcMassage, inputMassage, funcHotStones, inputHotStones, funcMeniPedi, inputMeniPedi) \
    switch (type) { \
        case eMassage: \
            funcMassage(inputMassage); \
            break; \
        case eHotStones: \
            funcHotStones(inputHotStones); \
            break; \
        case eMeniPedi: \
            funcMeniPedi(inputMeniPedi); \
            break; \
    }

    
#endif

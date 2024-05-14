/** 
 * @file VM_required.h
 * @brief Header file defining prototypes for functions required by the VM state machine implementation.
 */

#ifndef VM_REQUIRED_H_
#define VM_REQUIRED_H_

#include "../src/sc_types.h"
#include "VM.h"

#ifdef __cplusplus
extern "C"
{
#endif 

/** 
 * @file
 * This header defines prototypes for all functions that are required by the state machine implementation.
 *
 * This state machine makes use of operations declared in the state machine's interface or internal scopes. Thus, the function prototypes:
 * - vM_select_product
 * - vM_return_credit
 * are defined.
 *
 * These functions will be called during a 'run to completion step' (runCycle) of the statechart. 
 * There are some constraints that have to be considered for the implementation of these functions:
 * - never call the statechart API functions from within these functions.
 * - make sure that the execution time is as short as possible.
 */

/**
 * @brief Selects a product in the VM.
 * @param handle Pointer to the VM instance.
 * @param product The product to be selected.
 */
extern void vM_select_product(VM* handle, const sc_integer product);

/**
 * @brief Returns credit in the VM.
 * @param handle Pointer to the VM instance.
 * @param credit The amount of credit to be returned.
 */
extern void vM_return_credit(VM* handle, const sc_integer credit);

#ifdef __cplusplus
}
#endif 

#endif /* VM_REQUIRED_H_ */


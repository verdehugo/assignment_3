/** 
 * @file VM.h
 * @brief Header file for the VM state machine.
 */

#ifndef VM_H_
#define VM_H_

#ifdef __cplusplus
extern "C" { 
#endif

/**
 * @struct VM
 * @brief Type declaration of the data structure for the VM state machine.
 */
typedef struct VM VM;

/**
 * @struct VMIfaceBut
 * @brief Type declaration of the data structure for the VMIfaceBut interface scope.
 */
typedef struct VMIfaceBut VMIfaceBut;

/**
 * @struct VMInternal
 * @brief Type declaration of the data structure for the VMInternal interface scope.
 */
typedef struct VMInternal VMInternal;

/* Additional macros and definitions */

/**
 * @enum VMEventID
 * @brief Enum of event names in the statechart.
 */
typedef enum  {
    VM_invalid_event = SC_INVALID_EVENT_VALUE,
    VM_but_coin1,
    VM_but_coin2,
    VM_but_browse,
    VM_but_enter
} VMEventID;

/* More enum and struct declarations */

/**
 * @brief Initializes the VM state machine data structures. Must be called before first usage.
 * @param handle Pointer to the VM instance.
 */
extern void vM_init(VM* handle);

/**
 * @brief Activates the state machine.
 * @param handle Pointer to the VM instance.
 */
extern void vM_enter(VM* handle);

/**
 * @brief Deactivates the state machine.
 * @param handle Pointer to the VM instance.
 */
extern void vM_exit(VM* handle);

/* Additional function declarations */

#ifdef __cplusplus
}
#endif

#endif /* VM_H_ */


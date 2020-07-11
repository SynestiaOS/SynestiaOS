.global cpu_context_switch_to
cpu_context_switch_to:
    bx lr
    nop
//
//    //save cpsr
//    //save r2-r12
//    mrs   r2, cpsr
//    stmfd sp!, {r2}
//
//    //r0 Current Thread Pointer
//    //r1 Switch Thread Pointer
//    mov r2, #0
//    cmp r2, r0
//    beq cpu_restore_context
//    nop
//
//cpu_save_context:
//
//cpu_restore_context:
//
//    //Change To SVC Mode
//    mrs r2, cpsr
//    bic r2, #0x1F
//    orr r2, #0x13
//    msr cpsr, r2
//
//    //Restore Stack
//    mov sp, r1
//    ldmfd sp!, {r0}
//    msr spsr, r0
//    ldmfd sp!, {r0-r12, lr}
//
//    //Restore CPSR
//    ldmfd sp!, {r2}
//
//cpu_restore_irq_cpsr:
//    mrs r10, cpsr
//    bic r10, #0x1F
//    orr r10, #0x12
//    msr cpsr, r10
//
//    ldmfd sp!, {r10}
//    msr cpsr, r10
//    nop
//
//    bx lr
//    nop

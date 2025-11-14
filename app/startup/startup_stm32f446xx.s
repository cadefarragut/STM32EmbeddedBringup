    .syntax unified
    .cpu cortex-m4
    .thumb

    .extern SystemInit
    .extern main

    .section .isr_vector,"a",%progbits
    .type g_pfnVectors, %object

g_pfnVectors:
    .word _estack
    .word Reset_Handler
    .word Default_Handler    /* NMI */
    .word Default_Handler    /* HardFault */
    .word Default_Handler    /* MemManage */
    .word Default_Handler    /* BusFault */
    .word Default_Handler    /* UsageFault */
    .word 0
    .word 0
    .word 0
    .word 0
    .word Default_Handler    /* SVC */
    .word Default_Handler    /* DebugMon */
    .word 0
    .word Default_Handler    /* PendSV */
    .word Default_Handler    /* SysTick */
    /* (you can leave the rest as Default_Handler for now) */

    .size g_pfnVectors, .-g_pfnVectors

    .text
    .thumb
    .thumb_func
Reset_Handler:
    /* Copy .data from flash to RAM: r0=src, r1=dst, r2=end */
    ldr   r0, =_sidata
    ldr   r1, =_sdata
    ldr   r2, =_edata
copy_data:
    cmp   r1, r2
    bcc   copy_word        /* while (dst < end) */
    b     zero_bss
copy_word:
    ldr   r3, [r0], #4
    str   r3, [r1], #4
    b     copy_data

zero_bss:
    /* Zero .bss: r0=start, r1=end */
    ldr   r0, =_sbss
    ldr   r1, =_ebss
zero_loop:
    cmp   r0, r1
    bcc   zero_store       /* while (p < end) */
    b     call_systeminit
zero_store:
    movs  r2, #0
    str   r2, [r0], #4
    b     zero_loop

call_systeminit:
    bl    SystemInit
    bl    main

hang:
    b     hang

    .thumb_func
Default_Handler:
    b     Default_Handler

    .extern _estack
    .extern _sidata
    .extern _sdata
    .extern _edata
    .extern _sbss
    .extern _ebss


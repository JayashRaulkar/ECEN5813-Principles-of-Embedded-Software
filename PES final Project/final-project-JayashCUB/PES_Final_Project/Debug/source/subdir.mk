################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/delay.c \
../source/main.c \
../source/mtb.c \
../source/mycbfifo.c \
../source/myi2c.c \
../source/mymma.c \
../source/myuart.c \
../source/semihost_hardfault.c 

C_DEPS += \
./source/delay.d \
./source/main.d \
./source/mtb.d \
./source/mycbfifo.d \
./source/myi2c.d \
./source/mymma.d \
./source/myuart.d \
./source/semihost_hardfault.d 

OBJS += \
./source/delay.o \
./source/main.o \
./source/mtb.o \
./source/mycbfifo.o \
./source/myi2c.o \
./source/mymma.o \
./source/myuart.o \
./source/semihost_hardfault.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\nxp\myWorkspace_gittest\PES_Final_Project\board" -I"C:\nxp\myWorkspace_gittest\PES_Final_Project\source" -I"C:\nxp\myWorkspace_gittest\PES_Final_Project" -I"C:\nxp\myWorkspace_gittest\PES_Final_Project\drivers" -I"C:\nxp\myWorkspace_gittest\PES_Final_Project\CMSIS" -I"C:\nxp\myWorkspace_gittest\PES_Final_Project\utilities" -I"C:\nxp\myWorkspace_gittest\PES_Final_Project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/delay.d ./source/delay.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/mycbfifo.d ./source/mycbfifo.o ./source/myi2c.d ./source/myi2c.o ./source/mymma.d ./source/mymma.o ./source/myuart.d ./source/myuart.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o

.PHONY: clean-source


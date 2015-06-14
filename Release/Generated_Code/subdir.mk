################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/RxBuf.c \
../Generated_Code/Vectors.c 

OBJS += \
./Generated_Code/AS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/RxBuf.o \
./Generated_Code/Vectors.o 

C_DEPS += \
./Generated_Code/AS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/RxBuf.d \
./Generated_Code/Vectors.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Sources" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



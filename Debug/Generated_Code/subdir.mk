################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/AS1.c \
../Generated_Code/BitIoLdd1.c \
../Generated_Code/BitIoLdd2.c \
../Generated_Code/BitIoLdd3.c \
../Generated_Code/BitIoLdd4.c \
../Generated_Code/BitIoLdd5.c \
../Generated_Code/CS1.c \
../Generated_Code/Cpu.c \
../Generated_Code/FreeCntrLdd1.c \
../Generated_Code/FreeRunning.c \
../Generated_Code/GPIOEN.c \
../Generated_Code/GPIOEggDir.c \
../Generated_Code/GPIOEggStep.c \
../Generated_Code/GPIOPenDir.c \
../Generated_Code/GPIOPenStep.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/PWMPenServo.c \
../Generated_Code/PwmLdd1.c \
../Generated_Code/RxBuf.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/Vectors.c \
../Generated_Code/WAIT1.c 

OBJS += \
./Generated_Code/AS1.o \
./Generated_Code/BitIoLdd1.o \
./Generated_Code/BitIoLdd2.o \
./Generated_Code/BitIoLdd3.o \
./Generated_Code/BitIoLdd4.o \
./Generated_Code/BitIoLdd5.o \
./Generated_Code/CS1.o \
./Generated_Code/Cpu.o \
./Generated_Code/FreeCntrLdd1.o \
./Generated_Code/FreeRunning.o \
./Generated_Code/GPIOEN.o \
./Generated_Code/GPIOEggDir.o \
./Generated_Code/GPIOEggStep.o \
./Generated_Code/GPIOPenDir.o \
./Generated_Code/GPIOPenStep.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/PWMPenServo.o \
./Generated_Code/PwmLdd1.o \
./Generated_Code/RxBuf.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/Vectors.o \
./Generated_Code/WAIT1.o 

C_DEPS += \
./Generated_Code/AS1.d \
./Generated_Code/BitIoLdd1.d \
./Generated_Code/BitIoLdd2.d \
./Generated_Code/BitIoLdd3.d \
./Generated_Code/BitIoLdd4.d \
./Generated_Code/BitIoLdd5.d \
./Generated_Code/CS1.d \
./Generated_Code/Cpu.d \
./Generated_Code/FreeCntrLdd1.d \
./Generated_Code/FreeRunning.d \
./Generated_Code/GPIOEN.d \
./Generated_Code/GPIOEggDir.d \
./Generated_Code/GPIOEggStep.d \
./Generated_Code/GPIOPenDir.d \
./Generated_Code/GPIOPenStep.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/PWMPenServo.d \
./Generated_Code/PwmLdd1.d \
./Generated_Code/RxBuf.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/Vectors.d \
./Generated_Code/WAIT1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\DevApp\Eclipse_Kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\DevApp\Eclipse_Kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Sources" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



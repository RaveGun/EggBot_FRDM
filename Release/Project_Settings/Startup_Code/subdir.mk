################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c 

OBJS += \
./Project_Settings/Startup_Code/startup.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/startup.o: ../Project_Settings/Startup_Code/startup.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Sources" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Generated_Code" -std=gnu11 -Wno-unused-parameter -Wno-sign-compare -MMD -MP -MF"$(@:%.o=%.d)" -MT"Project_Settings/Startup_Code/startup.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/Events.c \
../Sources/Functions.c \
../Sources/main.c 

CPP_SRCS += \
../Sources/AccelStepper.cpp \
../Sources/EggBot.cpp \
../Sources/SerialCommand.cpp 

OBJS += \
./Sources/AccelStepper.o \
./Sources/EggBot.o \
./Sources/Events.o \
./Sources/Functions.o \
./Sources/SerialCommand.o \
./Sources/main.o 

C_DEPS += \
./Sources/Events.d \
./Sources/Functions.d \
./Sources/main.d 

CPP_DEPS += \
./Sources/AccelStepper.d \
./Sources/EggBot.d \
./Sources/SerialCommand.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\eclipse_kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Sources" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



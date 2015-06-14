################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/AccelStepper.c \
../Sources/Events.c \
../Sources/main.c 

CPP_SRCS += \
../Sources/EggBot.cpp \
../Sources/Functions.cpp \
../Sources/SerialCommand.cpp 

OBJS += \
./Sources/AccelStepper.o \
./Sources/EggBot.o \
./Sources/Events.o \
./Sources/Functions.o \
./Sources/SerialCommand.o \
./Sources/main.o 

C_DEPS += \
./Sources/AccelStepper.d \
./Sources/Events.d \
./Sources/main.d 

CPP_DEPS += \
./Sources/EggBot.d \
./Sources/Functions.d \
./Sources/SerialCommand.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\DevApp\Eclipse_Kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\DevApp\Eclipse_Kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Sources" -I"Y:/Works/wrsp_kepler_mbed/PEX_C_Project/Generated_Code" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.o: ../Sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra  -g3 -DDEBUG -I../Generated_Code -I../Sources -I../Project_Settings/Startup_Code -I"C:\DevApp\Eclipse_Kepler\ProcessorExpert/lib/Kinetis/iofiles" -I"C:\DevApp\Eclipse_Kepler\ProcessorExpert/lib/Kinetis/pdd/inc" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



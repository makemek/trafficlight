################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/traffic_light/traffic_light.cpp 

OBJS += \
./src/traffic_light/traffic_light.o 

CPP_DEPS += \
./src/traffic_light/traffic_light.d 


# Each subdirectory must supply rules for building sources it contributes
src/traffic_light/%.o: ../src/traffic_light/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -D__NEWLIB__ -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC17XX__ -I"C:\Users\Apipol\Documents\LPCXpresso_7.3.0_186\workspace\lpc_board_nxp_lpcxpresso_1769\inc" -I"C:\Users\Apipol\Documents\LPCXpresso_7.3.0_186\workspace\lpc_chip_175x_6x\inc" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AD9523/AD9523.c 

OBJS += \
./src/AD9523/AD9523.o 

C_DEPS += \
./src/AD9523/AD9523.d 


# Each subdirectory must supply rules for building sources it contributes
src/AD9523/%.o: ../src/AD9523/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"H:\sdr\zc702_sdr\sdr_sw\src\AD8366" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD8366" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9122" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9523" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9548" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9643" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\ADF4351" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\Common" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9122" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9523" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9548" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9643" -I"H:\sdr\zc702_sdr\sdr_sw\src\ADF4351" -I"H:\sdr\zc702_sdr\sdr_sw\src\Common" -c -fmessage-length=0 -I../../sdr_sw_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



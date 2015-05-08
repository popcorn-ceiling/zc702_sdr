################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Common/adc_core.c \
../src/Common/dac_core.c \
../src/Common/echo.c \
../src/Common/eeprom.c \
../src/Common/fifo.c \
../src/Common/i2c_axi.c \
../src/Common/i2c_ps7.c \
../src/Common/main.c \
../src/Common/platform.c \
../src/Common/platform_zynq.c \
../src/Common/spi_interface.c \
../src/Common/xcomm.c 

OBJS += \
./src/Common/adc_core.o \
./src/Common/dac_core.o \
./src/Common/echo.o \
./src/Common/eeprom.o \
./src/Common/fifo.o \
./src/Common/i2c_axi.o \
./src/Common/i2c_ps7.o \
./src/Common/main.o \
./src/Common/platform.o \
./src/Common/platform_zynq.o \
./src/Common/spi_interface.o \
./src/Common/xcomm.o 

C_DEPS += \
./src/Common/adc_core.d \
./src/Common/dac_core.d \
./src/Common/echo.d \
./src/Common/eeprom.d \
./src/Common/fifo.d \
./src/Common/i2c_axi.d \
./src/Common/i2c_ps7.d \
./src/Common/main.d \
./src/Common/platform.d \
./src/Common/platform_zynq.d \
./src/Common/spi_interface.d \
./src/Common/xcomm.d 


# Each subdirectory must supply rules for building sources it contributes
src/Common/%.o: ../src/Common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"H:\sdr\zc702_sdr\sdr_sw\src\AD8366" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD8366" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9122" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9523" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9548" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\AD9643" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\ADF4351" -I"H:\sdr\zc702_sdr\sdr_sw\Debug\src\Common" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9122" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9523" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9548" -I"H:\sdr\zc702_sdr\sdr_sw\src\AD9643" -I"H:\sdr\zc702_sdr\sdr_sw\src\ADF4351" -I"H:\sdr\zc702_sdr\sdr_sw\src\Common" -c -fmessage-length=0 -I../../sdr_sw_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



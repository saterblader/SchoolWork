################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/Button.c \
../Generated_Code/Button_Init.c \
../Generated_Code/Cpu.c \
../Generated_Code/Encoder_A0.c \
../Generated_Code/Encoder_A1.c \
../Generated_Code/Encoder_B0.c \
../Generated_Code/Encoder_B1.c \
../Generated_Code/IMU_LCD.c \
../Generated_Code/IR_Range_In.c \
../Generated_Code/IR_Range_Out.c \
../Generated_Code/Motor_A_En.c \
../Generated_Code/Motor_A_Ph.c \
../Generated_Code/Motor_B_En.c \
../Generated_Code/Motor_B_Ph.c \
../Generated_Code/PE_LDD.c \
../Generated_Code/Sample_IR.c \
../Generated_Code/TU1.c \
../Generated_Code/TU2.c \
../Generated_Code/TU3.c \
../Generated_Code/Vectors.c \
../Generated_Code/WiFi.c \
../Generated_Code/WiFi_PD.c 

OBJS += \
./Generated_Code/Button.o \
./Generated_Code/Button_Init.o \
./Generated_Code/Cpu.o \
./Generated_Code/Encoder_A0.o \
./Generated_Code/Encoder_A1.o \
./Generated_Code/Encoder_B0.o \
./Generated_Code/Encoder_B1.o \
./Generated_Code/IMU_LCD.o \
./Generated_Code/IR_Range_In.o \
./Generated_Code/IR_Range_Out.o \
./Generated_Code/Motor_A_En.o \
./Generated_Code/Motor_A_Ph.o \
./Generated_Code/Motor_B_En.o \
./Generated_Code/Motor_B_Ph.o \
./Generated_Code/PE_LDD.o \
./Generated_Code/Sample_IR.o \
./Generated_Code/TU1.o \
./Generated_Code/TU2.o \
./Generated_Code/TU3.o \
./Generated_Code/Vectors.o \
./Generated_Code/WiFi.o \
./Generated_Code/WiFi_PD.o 

C_DEPS += \
./Generated_Code/Button.d \
./Generated_Code/Button_Init.d \
./Generated_Code/Cpu.d \
./Generated_Code/Encoder_A0.d \
./Generated_Code/Encoder_A1.d \
./Generated_Code/Encoder_B0.d \
./Generated_Code/Encoder_B1.d \
./Generated_Code/IMU_LCD.d \
./Generated_Code/IR_Range_In.d \
./Generated_Code/IR_Range_Out.d \
./Generated_Code/Motor_A_En.d \
./Generated_Code/Motor_A_Ph.d \
./Generated_Code/Motor_B_En.d \
./Generated_Code/Motor_B_Ph.d \
./Generated_Code/PE_LDD.d \
./Generated_Code/Sample_IR.d \
./Generated_Code/TU1.d \
./Generated_Code/TU2.d \
./Generated_Code/TU3.d \
./Generated_Code/Vectors.d \
./Generated_Code/WiFi.d \
./Generated_Code/WiFi_PD.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -I"E:/Kinetis/KL05_Robot/Static_Code/PDD" -I"E:/Kinetis/KL05_Robot/Static_Code/IO_Map" -I"E:/Kinetis/KL05_Robot/Sources" -I"E:/Kinetis/KL05_Robot/Generated_Code" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



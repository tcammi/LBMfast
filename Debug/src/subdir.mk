################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/LBMfast.cpp \
../src/grid.cpp \
../src/helper.cpp \
../src/init.cpp \
../src/lbmSteps.cpp 

OBJS += \
./src/LBMfast.o \
./src/grid.o \
./src/helper.o \
./src/init.o \
./src/lbmSteps.o 

CPP_DEPS += \
./src/LBMfast.d \
./src/grid.d \
./src/helper.d \
./src/init.d \
./src/lbmSteps.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



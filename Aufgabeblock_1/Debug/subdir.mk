################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Fahrrad.cpp \
../Fahrzeug.cpp \
../PKW.cpp \
../main.cpp 

OBJS += \
./Fahrrad.o \
./Fahrzeug.o \
./PKW.o \
./main.o 

CPP_DEPS += \
./Fahrrad.d \
./Fahrzeug.d \
./PKW.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



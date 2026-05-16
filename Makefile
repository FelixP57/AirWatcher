CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I. -I./controller -I./data -I./model -I./service -I./vue

# Source files
SRCS = main.cpp \
       data/CleanerDAO.cpp \
       data/MeasurementDAO.cpp \
       data/SensorDAO.cpp \
       data/UserDAO.cpp \
       model/Attribute.cpp \
       model/Cleaner.cpp \
       model/Measurement.cpp \
       model/PrivateUser.cpp \
       model/Provider.cpp \
       model/Sensor.cpp \
       model/User.cpp 
#       controller/AirQualityController.cpp \
#       controller/AuthController.cpp \
#       controller/CleanerController.cpp \
#       controller/MainController.cpp \
#       controller/SensorController.cpp \
#       service/AirQualityService.cpp \
#       service/CleanerService.cpp \
#       service/PointsService.cpp \
#       service/SensorAnalysisService.cpp \
#       vue/ConsoleView.cpp \
#       vue/MenuAdmin.cpp \
#       vue/MenuProvider.cpp \
#       vue/MenuUser.cpp

# Generate object files in same folder as .cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = myprogram

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all

.PHONY: all clean re

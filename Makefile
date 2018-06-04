CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 -ggdb
EXECUTABLE=rousemat
SOURCES=./src/main.cpp ./src/Calendar/CCalendar.cpp ./src/Date/CDate.cpp ./src/Date/CDuration.cpp ./src/Event/CEvent.cpp ./src/Event/CEventEditor.cpp ./src/Exporters/CCalendarExportDefault.cpp
REPEATSTRATEGIES=./src/RepeatStrategies/CEventRepeatBase.cpp ./src/RepeatStrategies/CEventRepeatAfter.cpp ./src/RepeatStrategies/CEventRepeatDayInMonth.cpp ./src/RepeatStrategies/CEventRepeatWork.cpp ./src/RepeatStrategies/CEventRepeatDisabled.cpp
UI=./src/UI/CCommandInterpreter.cpp ./src/UI/CViewDay.cpp ./src/UI/CViewWeek.cpp ./src/UI/CViewMonth.cpp ./src/UI/CViewYear.cpp ./src/UI/CViewVector.cpp

all: $(SOURCES:.cpp=.o)
    $(CXX) $(SOURCES:.cpp=.o) -o $(EXECUTABLE)
clean:
    $(RM) $(SOURCES:.cpp=.o) $(EXECUTABLE)
run:
    ./$(EXECUTABLE)
%.o: %.cpp
    $(CXX) $(CXXFLAGS) $@ -c

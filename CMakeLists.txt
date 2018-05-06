cmake_minimum_required(VERSION 3.8)
project(sem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CDate.cpp CDate.h CEventBase.cpp CEventBase.h CSuggestor.h CCalendar.cpp CCalendar.h CCommandInterpreter.cpp CCommandInterpreter.h utils.cpp utils.h CCalendarExportBase.h)
add_executable(sem ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.8)
project(sem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Date/CDate.cpp Date/CDate.h Event/CEvent.cpp Event/CEvent.h utils/CSuggestor.h Calendar/CCalendar.cpp Calendar/CCalendar.h UI/CCommandInterpreter.cpp UI/CCommandInterpreter.h utils/utils.cpp utils/utils.h Exporters/CCalendarExportBase.h TransferStrategies/CEventTransferBase.h RepeatStrategies/CEventRepeatBase.h RepeatStrategies/CEventRepeatDayInMonth.cpp RepeatStrategies/CEventRepeatDayInMonth.h RepeatStrategies/CEventRepeatAfter.cpp RepeatStrategies/CEventRepeatAfter.h RepeatStrategies/CEventRepeatDisabled.cpp RepeatStrategies/CEventRepeatDisabled.h TransferStrategies/CEventTransferDisabled.cpp TransferStrategies/CEventTransferDisabled.h RepeatStrategies/CEventRepeatBase.cpp UI/CViewBase.cpp UI/CViewBase.h UI/CViewDay.cpp UI/CViewDay.h UI/CViewYear.cpp UI/CViewYear.h UI/CViewMonth.cpp UI/CViewMonth.h UI/CViewWeek.cpp UI/CViewWeek.h Date/CDuration.cpp Date/CDuration.h)
add_executable(sem ${SOURCE_FILES})
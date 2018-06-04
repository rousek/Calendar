cmake_minimum_required(VERSION 3.8)
project(sem)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Date/CDate.cpp Date/CDate.h Event/CEvent.cpp Event/CEvent.h utils/CSuggestor.h Calendar/CCalendar.cpp Calendar/CCalendar.h UI/CCommandInterpreter.cpp UI/CCommandInterpreter.h utils/utils.cpp utils/utils.h Exporters/CCalendarExportBase.h RepeatStrategies/CEventRepeatBase.h RepeatStrategies/CEventRepeatDayInMonth.cpp RepeatStrategies/CEventRepeatDayInMonth.h RepeatStrategies/CEventRepeatAfter.cpp RepeatStrategies/CEventRepeatAfter.h RepeatStrategies/CEventRepeatDisabled.cpp RepeatStrategies/CEventRepeatDisabled.h RepeatStrategies/CEventRepeatBase.cpp UI/CViewBase.h UI/CViewYear.cpp UI/CViewYear.h UI/CViewMonth.cpp UI/CViewMonth.h UI/CViewWeek.cpp UI/CViewWeek.h Date/CDuration.cpp Date/CDuration.h UI/CViewTime.h UI/CViewVector.cpp UI/CViewVector.h Event/CEventEditor.cpp Event/CEventEditor.h Exporters/CCalendarExportDefault.cpp Exporters/CCalendarExportDefault.h UI/CViewDay.cpp UI/CViewDay.h RepeatStrategies/CEventRepeatWork.cpp RepeatStrategies/CEventRepeatWork.h)
add_executable(sem ${SOURCE_FILES})
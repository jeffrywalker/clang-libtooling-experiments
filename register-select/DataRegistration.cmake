include_directories(${CMAKE_CURRENT_LIST_DIR})

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterFrontendAction.h
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterASTConsumer.h
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterVisitor.h
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterUtils.h
    ${CMAKE_CURRENT_LIST_DIR}/Options.h
    ${CMAKE_CURRENT_LIST_DIR}/Config.h
    ${CMAKE_CURRENT_LIST_DIR}/Context.h
    ${CMAKE_CURRENT_LIST_DIR}/DataRegister.h # ABC

    ${CMAKE_CURRENT_LIST_DIR}/ClassField.h

    ${CMAKE_CURRENT_LIST_DIR}/RegisteredVariable.h

    ${CMAKE_CURRENT_LIST_DIR}/Logger.h
    ${CMAKE_CURRENT_LIST_DIR}/Writer.h

)

list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterFrontendAction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterASTConsumer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterVisitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/DataRegisterUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Options.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Config.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Context.cpp

    ${CMAKE_CURRENT_LIST_DIR}/ClassField.cpp

    ${CMAKE_CURRENT_LIST_DIR}/RegisteredVariable.cpp

    ${CMAKE_CURRENT_LIST_DIR}/Logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Writer.cpp
)
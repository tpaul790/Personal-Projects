cmake_minimum_required(VERSION 3.27)
project(Produse)

set(CMAKE_CXX_STANDARD 17)

add_executable(Produse main.cpp
        Domain/Produs.h
        Domain/Produs.cpp
        Teste/teste.h
        Teste/teste.cpp
        Repo/RepoFile.h
        Repo/RepoFile.cpp
        Exceptii/RepoException.h
        Exceptii/ServiceException.h
        Validator/Validator.h
        Validator/Validator.cpp
        Service/Service.h
        Service/Service.cpp
        GUI/ProdusGui.h
        GUI/ProdusGui.cpp
        TableModel/TableModel.cpp
        Utilitati/utils.h
        Utilitati/utils.cpp
        Abstract/ActiuneUndo.h
        Abstract/ActiuneUndo.cpp
        Abstract/ActiuneRedo.h
        Abstract/ActiuneRedo.cpp
        GUI/FiltreGui.h
        GUI/FiltreGui.cpp
        Observer/Observable.h
        Observer/Observer.h
        Observer/Observable.cpp
        Repo/CosProduse.h
        Repo/CosProduse.cpp
        GUI/CosGui.h
        GUI/CosGui.cpp
        GUI/StatisticiGui.h
        GUI/StatisticiGui.cpp
)

set(CMAKE_PREFIX_PATH "/Users/titienipaul/Downloads/Qt/6.8.0/macos/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(Produse
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
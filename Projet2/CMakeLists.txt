cmake_minimum_required(VERSION 2.6)
#Déclaration du projet

project(Compilation)


add_executable(

        build

        include/Env.c

        include/Function.c

        include/Variable.c

        include/test.c

        include/Stack.c

        include/Ast.c
        include/Pascal.h include/Pascal.c)
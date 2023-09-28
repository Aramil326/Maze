CC = gcc -std=c++17
WWW = -Wall -Werror -Wextra
OS := $(shell uname)

ifeq ($(OS),Linux)
	CHFLAGS = -lgtest -lpthread -lrt -lm -lsubunit -lstdc++
else
	CHFLAGS = -lgtest -lm -lstdc++
endif

PROJECT_SOURCES =         controller/controller.cc \
                          model/maze_model/maze_model.cc \
                          model/facade/facade.cc \
                          model/model_loader/model_loader.cc \
                          model/matrix/matrix.cc \
                          model/maze_generator/maze_generator.cc \
                          model/maze_solver/maze_solver.cc \

all: clean install gcov_report

clean:
	rm -rf *.o unit_tests/unit_test
	rm -rf unit_tests/*.gcno unit_tests/*gcda unit_tests/*.gcov gcov program
	rm -rf report report.info

tests: clean
	$(CC) unit_tests/unit_test.cc $(PROJECT_SOURCES) -o unit_tests/unit_test $(CHFLAGS)
	./unit_tests/unit_test
	rm -rf unit_tests/unit_test

gcov_report:
	$(CC) --coverage unit_tests/unit_test.cc $(PROJECT_SOURCES) $(CHFLAGS) -o unit_tests/unit_test
	./unit_tests/unit_test
	lcov -t "./unit_tests" -o report.info --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html
	rm -rf *.gcno *gcda *.gcov gcov

install:
	rm -rf myapp_release
	rm -rf instal_release
	mkdir instal_release
	mkdir myapp_release
	cd instal_release && \
		cmake -DCMAKE_BUILD_TYPE=Release -D EXECUTABLE_OUTPUT_PATH="../myapp_release" ../ &&  \
		cmake --build ../instal_release/. && \
		rm -rf ../instal_release

uninstall:
	rm -rf myapp_release

dist: install
	tar -cf my_app.tar.gz myapp_release/
	rm -rf myapp_release

dvi:
	open dvi.md

style:
	clang-format -style=google -n \
	controller/controller.cc \
	controller/controller.h \
	model/facade/facade.cc \
	model/facade/facade.h \
	model/matrix/matrix.cc \
	model/matrix/matrix.h \
	model/maze_generator/maze_generator.cc \
	model/maze_generator/maze_generator.h \
	model/maze_model/maze_model.cc \
	model/maze_model/maze_model.h \
	model/maze_solver/error_solve_type.h \
	model/maze_solver/maze_solver.cc \
	model/maze_solver/maze_solver.h \
	model/model_loader/error_load_type.h \
	model/model_loader/model_loader.cc \
	model/model_loader/model_loader.h \
	unit_tests/unit_test.cc \
	view/maze_view/maze_field.cc \
	view/maze_view/maze_field.h \
	view/maze_view/maze_scene.cc \
	view/maze_view/maze_scene.h \
	main.cc
































test:
	g++ cpu.t.cpp ../cpu.cpp ../Memory.cpp ../Graphics.cpp ../Cart.cpp ../Bootstrap.cpp -DGTEST_USE_OWN_TR1_TUPLE=1 `sdl2-config --libs` -lgtest_main -lgtest -lgmock --std=c++11 -o run_tests.bin
	./run_tests.bin

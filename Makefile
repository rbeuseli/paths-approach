taus.exe : taus.cpp path.cpp path.hpp
	g++ -o taus.exe taus.cpp path.cpp

clean:
	rm *.exe *.so *.d *.pcm

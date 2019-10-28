TARGET = a.out

CC = clang
CXX = clang++

CFLAGS = -Wall -Wextra -march=x86-64
CXXFLAGS = $(CFLAGS) -std=c++98
DFLAGS = -g -O0 -D_DEBUG=1
RFLAGS = -O3 -DNDEBUG=1
ALUSANFLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak
TSANFLAGS = -fsanitize=thread

CPPLIST = main.cpp gtest.cpp
LDLIBS = -lgtest


all: linux64_debug linux64_release

clean:
	rm $(TARGET)

linux64_debug:
	$(CXX) $(CPPLIST) $(CXXFLAGS) $(DFLAGS) $(LDLIBS)

linux64_release:
	$(CXX) $(CPPLIST) $(CXXFLAGS) $(RFLAGS) $(LDLIBS)

test:
	$(MAKE) linux64_debug && $(MAKE) alusan && $(MAKE) tsan

alusan: clean
	echo "[[[   Adress Leak Undefined sanitizer   ]]]"
	$(CXX) $(CPPLIST) $(CXXFLAGS) $(DFLAGS) $(ALUSANFLAGS) $(LDLIBS)
	./$(TARGET)

tsan: clean
	echo "[[[   Thread sanitizer   ]]]"
	$(CXX) $(CPPLIST) $(CXXFLAGS) $(DFLAGS) $(TSANFLAGS) $(LDLIBS)
	./$(TARGET)

ifeq ($(BREAKPAD_DIR),)
    BREAKPAD_DIR := ../google-breakpad
endif

# No user-servicable parts after this point.
BREAKPAD_LIBS := $(BREAKPAD_DIR)/src/libbreakpad.a \
    		$(BREAKPAD_DIR)/src/third_party/libdisasm/libdisasm.a

OBJS := simple_code_module.o breakpad_symbolicate.o
BIN := breakpad-symbolicate
CXXFLAGS := -std=c++0x -I$(BREAKPAD_DIR)/src

all: $(BIN)

$(BIN): $(OBJS) $(BREAKPAD_LIBS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) $(BIN)

.PHONY: clean distclean


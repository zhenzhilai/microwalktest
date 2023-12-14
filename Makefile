# This Makefile can be used with GNU Make or BSD Make

# override as desired
TYPE=kem
SCHEME=kyber512
IMPLEMENTATION=clean
KAT_RNG=nist

#SCHEME_DIR=../crypto_$(TYPE)/$(SCHEME)/$(IMPLEMENTATION)
SCHEME_DIR=./src/$(SCHEME)
SCHEME_UPPERCASE=$(shell echo $(SCHEME) | tr a-z A-Z | sed 's/-//g')
IMPLEMENTATION_UPPERCASE=$(shell echo $(IMPLEMENTATION) | tr a-z A-Z | sed 's/-//g')

TEST_COMMON_DIR=./src/test/common
COMMON_DIR=./src/common
COMMON_FILES=$(COMMON_DIR)/aes.c $(COMMON_DIR)/sha2.c $(COMMON_DIR)/fips202.c $(COMMON_DIR)/nistseedexpander.c $(COMMON_DIR)/sp800-185.c
COMMON_HEADERS=$(COMMON_DIR)/*.h
DEST_DIR=./bin

SCHEME_LIBRARY=$(SCHEME_DIR)/lib$(SCHEME)_$(IMPLEMENTATION).a
SCHEME_FILES=$(wildcard $(SCHEME_DIR)/*.[chsS])

# #########################
# #########################
# build testvec
# #########################
# #########################

# # This -Wall was supported by the European Commission through the ERC Starting Grant 805031 (EPOQUE)
# # CFLAGS=-O0 -Wall -Wextra -Wpedantic -Wvla -Werror -std=c99 \
# # 	   -Wundef -Wshadow -Wcast-align -Wpointer-arith -Wmissing-prototypes\
# # 	   -fstrict-aliasing -fno-common -pipe \
# # 	   -I$(COMMON_DIR) $(EXTRAFLAGS)
# CFLAGS=-O0 -std=c99 \
# 	   -fstrict-aliasing -fno-common -pipe \
# 	   -I$(COMMON_DIR) $(EXTRAFLAGS)

# # Number of tests run for functests
# NTESTS=1


# all: $(DEST_DIR)/testvectors_$(SCHEME)_$(IMPLEMENTATION)

# .PHONY: build-scheme
# build-scheme: $(SCHEME_LIBRARY)

# $(SCHEME_LIBRARY): $(SCHEME_FILES)
# 	cd $(SCHEME_DIR) && $(MAKE)

# .PHONY: clean-scheme
# clean-scheme:
# 	cd $(SCHEME_DIR) && $(MAKE) clean


# .PHONY: testvectors
# testvectors: $(DEST_DIR)/testvectors_$(SCHEME)_$(IMPLEMENTATION)

# $(DEST_DIR)/testvectors_$(SCHEME)_$(IMPLEMENTATION): $(SCHEME_LIBRARY) ./src/my_lib.c $(COMMON_FILES) $(COMMON_DIR)/randombytes.c $(COMMON_HEADERS)
# 	mkdir -p $(DEST_DIR)
# 	$(CC) $(CFLAGS) -DPQCLEAN_NAMESPACE=PQCLEAN_$(SCHEME_UPPERCASE)_$(IMPLEMENTATION_UPPERCASE) -I$(SCHEME_DIR) ./src/my_lib.c $(COMMON_FILES) $(COMMON_DIR)/randombytes.c -o $@ -L$(SCHEME_DIR) -l$(SCHEME)_$(IMPLEMENTATION)

##########################
##########################
# build libso
##########################
##########################

CFLAGS=-O0 -fPIC -g -I$(COMMON_DIR) $(EXTRAFLAGS)
LDFLAGS=-shared

# SOURCES=$(shell echo src/*.c)
# OBJECTS=$(SOURCES:.c=.o)

TARGET=libexample.so

all: $(TARGET)

.PHONY: build-scheme
build-scheme: $(SCHEME_LIBRARY)

$(SCHEME_LIBRARY): $(SCHEME_FILES)
	cd $(SCHEME_DIR) && $(MAKE)

.PHONY: clean-scheme
clean-scheme:
	cd $(SCHEME_DIR) && $(MAKE) clean

.PHONY: libso
libso: $(TARGET)

##randombytes

# $(TARGET): $(SCHEME_LIBRARY) ./src/my_lib.c $(COMMON_FILES) $(COMMON_DIR)/randombytes.c $(COMMON_HEADERS)
# 	$(CC) $(CFLAGS) -DPQCLEAN_NAMESPACE=PQCLEAN_$(SCHEME_UPPERCASE)_$(IMPLEMENTATION_UPPERCASE) -I$(SCHEME_DIR) ./src/my_lib.c $(COMMON_FILES) $(COMMON_DIR)/randombytes.c -o $@ -L$(SCHEME_DIR) -l$(SCHEME)_$(IMPLEMENTATION) $(LDFLAGS)

##norandombytes
$(TARGET): $(SCHEME_LIBRARY) ./src/my_lib.c $(COMMON_FILES) $(TEST_COMMON_DIR)/notrandombytes.c $(COMMON_HEADERS)
 	$(CC) $(CFLAGS) -DPQCLEAN_NAMESPACE=PQCLEAN_$(SCHEME_UPPERCASE)_$(IMPLEMENTATION_UPPERCASE) -I$(SCHEME_DIR) ./src/my_lib.c $(COMMON_FILES) $(TEST_COMMON_DIR)/notrandombytes.c -o $@ -L$(SCHEME_DIR) -l$(SCHEME)_$(IMPLEMENTATION) $(LDFLAGS)


##########################
##########################
# clean
##########################
##########################


.PHONY: clean
clean:

	$(RM) $(DEST_DIR)/testvectors_$(SCHEME)_$(IMPLEMENTATION)
	$(RM) $(TARGET)

.PHONY: distclean
distclean:
	$(RM) -r $(DEST_DIR)

export SHEN_C_HOME=${CURDIR}
SRC_ROOT=src/c
BIN_ROOT=bin
OBJ_ROOT=obj
TEST_SRC_ROOT=test/c
PROFILE_ROOT=prof

SRCS=$(wildcard ${SRC_ROOT}/*.c)
SRC_OBJS=$(patsubst ${SRC_ROOT}/%.c, obj/%.o, $(SRCS))
TARGET=${BIN_ROOT}/shen-c
PROFILE=${PROFILE_ROOT}/shen-c.prof
PROFILE_TEXT=${PROFILE_ROOT}/shen-c.prof.txt
PROFILE_PDF=${PROFILE_ROOT}/shen-c.prof.pdf
PROFILE_SIGNAL=${PROFILE_ROOT}/shen-c.prof.0
PROFILE_SIGNAL_TEXT=${PROFILE_ROOT}/shen-c.prof.0.txt

CC=clang

#SGI MIPS
#CC=c99
#CFLAGS=-O3 -64 -DGC_IRIX_THREADS=1 -DNO_EXECUTE_PERMISSION=1 -I /usr/local/include
#LIBS=-L/usr/local/lib 
#LIBS=-L/usr/local/lib -lgc

# linux
# need _XOPEN_SOURCE to guarantee sigjmp_buf used in place of jmp_buf
# need _GNU_SOURCE for SA_RESTART - gnu c has become ridiculous!

CC=gcc
CFLAGS=-std=c99 -O3 -I /usr/local/include -D _POSIX_C_SOURCE=200112L  -D _GNU_SOURCE
LIBS=-L/usr/local/lib -lgc -lpthread -ldl

$(shell mkdir -p obj bin)

all: ${TARGET} 

${TARGET}: ${SRC_OBJS}
#	cc -g -O0 -std=c99 -fsanitize=address -lgc -o $@ $^
#	cc -g -O0 -std=c99 -lgc -lprofiler -Wl,-no_pie -o $@ $^
#	cc -g -O0 -std=c99 -lgc -o $@ $^
#	cc -O2 -std=c99 -lgc -o $@ $^
#	cc -g -O3 -std=c99 -lgc -lprofiler -Wl,-no_pie -o $@ $^
#	${CC} -O3 -lgc -o $@ $^
#	gcc-6 -g -O3 -std=c99 -L /usr/local/lib -lgc -lprofiler -Wl,-no_pie -o $@ $^
#	gcc-6 -O3 -std=c99 -L /usr/local/lib -lgc -o $@ $^
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^ /usr/local/lib/libgc.a

${OBJ_ROOT}/%.o: $(SRC_ROOT)/%.c
#	cc -g -O0 -std=c99 -Weverything -Wno-static-in-inline -Wno-padded -Wno-reserved-id-macro -Wno-used-but-marked-unused -fsanitize=address -fno-omit-frame-pointer -c -o $@ $<
#	cc -g -O0 -std=c99 -c -o $@ $<
#	cc -O2 -std=c99 -fno-optimize-sibling-calls -c -o $@ $<
#	${CC} -O3 -fno-optimize-sibling-calls -c -o $@ $<
#	gcc-6 -g -O3 -std=c99 -fno-optimize-sibling-calls -Wall -I /usr/local/include/gc -c -o $@ $<
#	gcc-6 -O3 -std=c99 -fno-optimize-sibling-calls -Wall -I /usr/local/include/gc -c -o $@ $<
	$(CC) $(CFLAGS) -c -o $@ $<

repl: ${TARGET}
	${TARGET}

rrepl: ${TARGET}
	rlwrap -n ${TARGET}

gperf: ${TARGET}
	mkdir -p prof
	env CPUPROFILE=${PROFILE} ${TARGET}

gperf_signal: ${TARGET}
	rm ${PROFILE}
	mkdir -p prof
	env CPUPROFILE=${PROFILE} CPUPROFILESIGNAL=12 ${TARGET}

pprof:
	pprof ${TARGET} ${PROFILE}

pprof_text:
	pprof ${TARGET} ${PROFILE} --text > ${PROFILE_TEXT}

pprof_signal_text:
	pprof ${TARGET} ${PROFILE_SIGNAL} --text > ${PROFILE_SIGNAL_TEXT}

pprof_pdf:
	pprof ${TARGET} ${PROFILE} --pdf > ${PROFILE_PDF}

clean:
	rm -R obj
	rm -R bin

.PHONY: repl rrepl clean pprof pprof_text pprof_signal_text pprof_pdf

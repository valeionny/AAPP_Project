
SRCDIR = src
INCDIR = include
OBJDIR = build
BINDIR = bin

CC = g++
CFLAGS = -I$(INCDIR) -fopenmp

DATASETOBJS = $(addprefix $(OBJDIR)/, create_dataset.o dataset_creation.o \
                                     file_procs.o)
SERIALOBJS = $(addprefix $(OBJDIR)/, run_serial.o serial.o file_procs.o)
PARALLELOBJS = $(addprefix $(OBJDIR)/, run_parallel.o parallel.o \
                                      file_procs.o)
RANDOMIZEDOBJS = $(addprefix $(OBJDIR)/, run_randomized.o randomized.o \
                                        parallel.o file_procs.o)
TESTSERIALOBJS = $(addprefix $(OBJDIR)/, test_serial.o serial.o \
                                        file_procs.o time_benchmark.o)
TESTPARALLELOBJS = $(addprefix $(OBJDIR)/, test_parallel.o parallel.o \
                                          file_procs.o time_benchmark.o)
TESTRANDOMIZEDOBJS=$(addprefix $(OBJDIR)/, test_randomized.o randomized.o \
                                 parallel.o time_benchmark.o file_procs.o)

all: dataset serial parallel randomized testserial testparallel testrandomized

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

dataset: $(DATASETOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/create_dataset $^

serial: $(SERIALOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/run_serial $^

parallel: $(PARALLELOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/run_parallel $^

randomized: $(RANDOMIZEDOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/run_randomized $^

testserial: $(TESTSERIALOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/test_serial $^

testparallel: $(TESTPARALLELOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/test_parallel $^

testrandomized: $(TESTRANDOMIZEDOBJS) | $(BINDIR)
	$(CC) $(CFLAGS) -o $(BINDIR)/test_randomized $^

clean:
	rm -rf $(BINDIR) $(OBJDIR)


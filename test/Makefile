.SUFFIXES: -omp -ompd -gomp -domp -dgomp -asm -dasm
CC = gcc

OPENMP	 = -fopenmp
CFLAGS   = -Wall -O -std=c99 -march=native -I.
CLIBS    = -L$(MINIOMP)/lib -lminiomp

.c-omp: 
	$(CC) $(CFLAGS) $(OPENMP) $< -o $@ $(CLIBS) 
.c-ompd:
	$(CC) $(CFLAGS) $(OPENMP) -g $< -o $@ $(CLIBS)
.c-gomp: 
	$(CC) $(CFLAGS) $(OPENMP) -D GOMP $< -o $@ 

.c-asm: 
	$(CC) $(CFLAGS) $(OPENMP) -c -S $< -o $@ $(CLIBS) 

.c-domp: 
	$(CC) -D_DISPLAY_ $(CFLAGS) $(OPENMP) $< -o $@ $(CLIBS) -lX11 -L/usr/X11R6/lib

.c-dgomp: 
	$(CC) -D_DISPLAY_ $(CFLAGS) $(OPENMP) $< -o $@ -lX11 -L/usr/X11R6/lib

.c-dasm: 
	$(CC) -D_DISPLAY_ $(CFLAGS) $(OPENMP) -c -S $< -o $@ $(CLIBS) 

clean:
	rm -rf *-omp *-gomp *-asm *-domp *-dgomp *-ompd

ultraclean:
	rm -rf *-omp *-gomp *-asm *-domp *-dgomp *-ompd *.prv *.pcf *.row TRACE.mpits set-0 TRACE.sym

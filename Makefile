CC=gcc
CFLAGS=-g -Wall -fopenmp
DEPS = Lab3IO.c

main: Lab3_baseline_ompsolution.c omp_GaussJordanStatic.c omp_GaussJordanDynamic.c omp_GaussJordanGuided.c omp_GaussJordanAuto.c omp_GaussJordanNone.c omp_GaussJordanDDG.c omp_GaussJordanDDN.c omp_GaussJordanDGG.c omp_GaussJordanNDD.c
	$(CC) -o baseline Lab3_baseline_ompsolution.c $(DEPS) $(CFLAGS)
	$(CC) -o static omp_GaussJordanStatic.c $(DEPS) $(CFLAGS)
	$(CC) -o dynamic omp_GaussJordanDynamic.c $(DEPS) $(CFLAGS)
	$(CC) -o guided omp_GaussJordanGuided.c $(DEPS) $(CFLAGS)
	$(CC) -o auto omp_GaussJordanAuto.c $(DEPS) $(CFLAGS)
	$(CC) -o none omp_GaussJordanNone.c $(DEPS) $(CFLAGS)
	$(CC) -o ddg omp_GaussJordanDDG.c $(DEPS) $(CFLAGS)
	$(CC) -o ddn omp_GaussJordanDDN.c $(DEPS) $(CFLAGS)
	$(CC) -o dgg omp_GaussJordanDGG.c $(DEPS) $(CFLAGS)
	$(CC) -o ndd omp_GaussJordanNDD.c $(DEPS) $(CFLAGS)

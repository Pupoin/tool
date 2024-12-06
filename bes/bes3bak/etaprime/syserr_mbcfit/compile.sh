# . /publicfs/ucas/user/yuanchy8/root/root_v6.24.06/bin/thisroot.sh
. /publicfs/ucas/user/yuanchy8/root/root_v6.24.08/bin/thisroot.sh
# g++ fit_0.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_0.o
# g++ fit_1.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_1.o
# g++ fit_2.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_2.o
# g++ fit_3.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_3.o
# g++ fit_4.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_4.o

g++ fit_0_patchE0.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_0_patchE0.o
g++ fit_1_patchE0.C $(root-config --cflags --libs)   -lRooFitCore -lRooFit -o fit_1_patchE0.o


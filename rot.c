#include    <stdio.h>
#include    <math.h>
#include    <time.h>

char *mtx1[] = {
    "               ",
    "               ",
    "    #######    ",
    "    #######    ",
    "    #######    ",
    "    #######    ",
    "    #######    ",
    "    #######    ",
    "    #######    ",
    "               ",
    "               ",
};
char *mtx2[] = {
    "                       ",
    "                       ",
    "                       ",
    "                       ",
    "    ###############    ",
    "    #      #      #    ",
    "    #  ##  #      #    ",
    "    # #### #      #    ",
    "    # #### #      #    ",
    "    #  ##  #      #    ",
    "    #      #      #    ",
    "    ###############    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    #      #      #    ",
    "    ###############    ",
    "                       ",
    "                       ",
    "                       ",
    "                       ",
};
void printRotated(double thet, int w, int h, int c[], char *m[]);
char getValue(int w, int h, double vec[], char *m[]);

int main(int argc, char **argv)
{
    int n = 32;
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    int i = 0;
    while (1) {
        long nsec = t.tv_nsec + 16666667L;
        if (nsec > 1000000000L) {
            t = (struct timespec){t.tv_sec + 1, nsec % 1000000000L};
        } else {
            t = (struct timespec){t.tv_sec, nsec};
        }
        printf("time: %lld %ld\n", (long long) t.tv_sec, t.tv_nsec);
        double thet = M_PI * (i / (double) 128);
        i = (i + 1) % 256;
        printRotated(thet, 22, 22, (int []){11, 11}, mtx2);
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &t, NULL);
        clock_gettime(CLOCK_MONOTONIC, &t);
    }
}

void printRotated(double thet, int w, int h, int c[], char *m[])
{
    double sinthet = sin(-thet);
    double costhet = cos(-thet);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int vec[] = {x - c[0], y - c[1]};
            double rot[] = {costhet*vec[0] + sinthet*vec[1], -sinthet*vec[0] + costhet*vec[1]};
            char v = getValue(w, h, (double[]){rot[0] + c[0], rot[1] + c[1]}, m);
            printf("%c%c", v, v);
        }
        putchar('\n');
    }
}

char getValue(int w, int h, double vec[], char *m[])
{
    int x = (int) (vec[0] + 0.5);
    int y = (int) (vec[1] + 0.5);
    if (!m || x >= w || y >= h || x < 0 || y < 0)
        return ' ';
    return m[y][x];
}

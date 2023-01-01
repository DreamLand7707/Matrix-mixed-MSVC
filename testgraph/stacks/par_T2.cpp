#include <cmath>
#include <cstdio>
#define PI 3.1415926
int main(void)
{
    FILE *file = NULL;
    file = fopen("E:\\PCL2\\.minecraft\\versions\\1.17.1-Fabric 0.14.8-OptiFine_H2_pre1\\saves\\particle\\datapacks\\particles\\data\\particlea\\functions\\parti.mcfunction", "w+");
    double a[3]{};
    int max = 100;
    double t = 0;

    for (int i = 0; i < max; t += 2 * PI / max, i++)
    {

        a[0] = sqrt(PI * PI - (t - PI) - (t - PI)) * sin(16 * t);
        a[1] = 4 * t;
        a[2] = sqrt(PI * PI - (t - PI) - (t - PI)) * cos(16 * t);

        fprintf(file, "setblock ~%d ~ ~ minecraft:command_block{Command:\"clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\"} replace\n", i + 2);
        fprintf(file, "setblock ~%d ~2 ~ minecraft:command_block{Command:\"particle end_rod ~%.3lf ~%.3lf ~%.3lf 0 0 0 0 1 force\"} replace\n", i + 2, a[0] - i - 2, a[1] - 2, a[2]);
    }

    fclose(file);
    return 0;
    /// particle <PID> <x> <y> <z> <dx> <dy> <dz> <speed> <count> <force|normal> <player>
}
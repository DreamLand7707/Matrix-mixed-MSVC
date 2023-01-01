#include <basic_ma1.h>
#include <string.h>
int main(void)
{
    int mode;
    int count;
    int b_count;
    int com_perb;
    double point[2][3]{};
    double kb[3][2]{};
    double tmin = 1, tmax = 11, dt = (tmax - tmin) / count;
    char names[60]{};
    char manames[60]{};
    FILE *pa = NULL;
    FILE *fa1 = NULL;
    FILE *fa2 = NULL;

    printf("Please putin mode<1/2>:");
    scanf("%d", &mode);

    if (mode == 1)
    {
        for (int i1 = 0;; i1++)
        {
            printf("Please putin the messages of particles:\n");
            printf("<Pcou>_<Bcou>_<Nnam>_<Coo1>_<Coo2>:\n");

            scanf("%d", &count);
            scanf("%d", &b_count);
            scanf("%s", names);
            if (strlen(names) && names[0] != '&')
                names[strlen(names)] = '/';
            else
                names[0] = '\0';
            dt = (tmax - tmin) / count;
            sprintf(manames, "./command/main%d.mcfunction", i1);
            pa = fopen(manames, "w+");

            for (int i = 0; i < 2; i++)
                scanf("%lf%lf%lf", &point[i][0], &point[i][1], &point[i][2]);
            double *A_ = (double *)malloc(4 * sizeof(double));
            double *b = (double *)malloc(2 * sizeof(double));
            Mat A{}, B{}, C{};

            for (int i = 0; i < 3; i++)
            {
                int t = 0;
                A_[0] = tmin, A_[1] = 1, A_[2] = tmax, A_[3] = 1;
                b[0] = point[0][i], b[1] = point[1][i];
                matr_init(&A, 2, 2, A_, 4);
                matr_init(&B, 2, 1, b, 2);
                t = matr_perf_sol(&A, &B, 1e-6, &C);
                kb[i][0] = C.pos[C.count_l - 1][0], kb[i][1] = C.pos[C.count_l - 1][1];
                matr_free(&A);
                matr_free(&B);
                matr_free(&C);
            }
            free(A_);
            free(b);

            char file_name[60]{};

            com_perb = count / b_count;

            double stat = tmin;
            double x, y, z;
            FILE *mcf = NULL;
            for (int i = 0; i < b_count; i++)
            {
                static double nt = dt;
                static double x, y, z;
                sprintf(file_name, "./command/d%d.%d.mcfunction", i1, i + 1);
                mcf = fopen(file_name, "w+");
                for (int j = 0; j < (i == (b_count - 1) ? ((count % b_count) ? (count % b_count + com_perb) : com_perb) : (com_perb)); j++)
                {
                    x = kb[0][0] * nt + kb[0][1];
                    y = kb[1][0] * nt + kb[1][1];
                    z = kb[2][0] * nt + kb[2][1];
                    fprintf(mcf, "particle minecraft:end_rod %f %f %f 0 0 0 0 1 force\n", x, y, z);
                    nt += dt;
                }
                fclose(mcf);
                fprintf(pa, "setblock ~%d ~2 ~ minecraft:command_block{Command:\"function particles:%sd%d.%d\"} replace\n", 2 + i, names, i1, i + 1);
                fprintf(pa, "setblock ~%d ~ ~ minecraft:command_block{Command:\"clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\"} replace\n", 2 + i, i + 1);
            }
            fprintf(pa, "clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\n");
            fprintf(pa, "setblock ~1 ~ ~ minecraft:command_block{Command:\"clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\"} replace\n");
            fprintf(pa, "setblock ~%d ~ ~ minecraft:command_block{Command:\"fill ~ ~ ~ ~-%d ~2 ~ minecraft:air replace\"} replace\n", 2 + b_count, 1 + b_count);
            fclose(pa);
            printf("\n\nfunction particles:%smain%d\n\n", names, i1);
        }
    }
    if (mode == 2)
    {
        for (int i2 = 0;; i2++)
        {
            int line_count;
            printf("Please putin the message of file:\n");
            printf("<Pcou>_<Bcou>_<Nnam>_<Llinc>:\n");
            freopen("CON", "r", stdin);
            // 即文件读取，每行六个值，先预处理，而后处理
            scanf("%d", &count);
            scanf("%d", &b_count);
            scanf("%s", names);
            scanf("%d", &line_count);
            fa1 = fopen("./sourfile/$coord.txt", "w+");
            freopen("./sourfile/coords.txt", "r", stdin);
            for (int i = 0; i < line_count; i++)
            {
                for (int i = 0; i < 2; i++)
                    scanf("%lf%lf%lf", &point[i][0], &point[i][1], &point[i][2]);
                fprintf(fa1, "%d %d %s %lf %lf %lf %lf %lf %lf\n",
                        count, b_count, names, point[0][0], point[0][1], point[0][2], point[1][0], point[1][1], point[1][2]);
            }
            fclose(fa1);
            freopen("./sourfile/$coord.txt", "r", stdin);
            for (int i1 = 0; i1 < line_count; i1++)
            {
                scanf("%d", &count);
                scanf("%d", &b_count);
                scanf("%s", names);
                if (strlen(names) && names[0] != '&')
                    names[strlen(names)] = '/';
                else
                    names[0] = '\0';
                dt = (tmax - tmin) / count;
                sprintf(manames, "./command/main%d.mcfunction", i1);
                pa = fopen(manames, "w+");

                for (int i = 0; i < 2; i++)
                    scanf("%lf%lf%lf", &point[i][0], &point[i][1], &point[i][2]);
                double *A_ = (double *)malloc(4 * sizeof(double));
                double *b = (double *)malloc(2 * sizeof(double));
                Mat A{}, B{}, C{};

                for (int i = 0; i < 3; i++)
                {
                    int t = 0;
                    A_[0] = tmin, A_[1] = 1, A_[2] = tmax, A_[3] = 1;
                    b[0] = point[0][i], b[1] = point[1][i];
                    matr_init(&A, 2, 2, A_, 4);
                    matr_init(&B, 2, 1, b, 2);
                    t = matr_perf_sol(&A, &B, 1e-6, &C);
                    kb[i][0] = C.pos[C.count_l - 1][0], kb[i][1] = C.pos[C.count_l - 1][1];
                    matr_free(&A);
                    matr_free(&B);
                    matr_free(&C);
                }
                free(A_);
                free(b);

                char file_name[60]{};

                com_perb = count / b_count;

                double stat = tmin;
                double x, y, z;
                FILE *mcf = NULL;
                double nt = tmin;
                for (int i = 0; i < b_count; i++)
                {
                    static double x, y, z;
                    sprintf(file_name, "./command/d%d.%d.mcfunction", i1, i + 1);
                    mcf = fopen(file_name, "w+");
                    for (int j = 0; j < (i == (b_count - 1) ? ((count % b_count) ? (count % b_count + com_perb) : com_perb) : (com_perb)); j++)
                    {
                        x = kb[0][0] * nt + kb[0][1];
                        y = kb[1][0] * nt + kb[1][1];
                        z = kb[2][0] * nt + kb[2][1];
                        fprintf(mcf, "particle minecraft:end_rod %f %f %f 0 0 0 0 1 force\n", x, y, z);
                        nt += dt;
                    }
                    fclose(mcf);
                    fprintf(pa, "setblock ~%d ~2 ~ minecraft:command_block{Command:\"function particles:%sd%d.%d\"} replace\n", 2 + i, names, i1, i + 1);
                    fprintf(pa, "setblock ~%d ~ ~ minecraft:command_block{Command:\"clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\"} replace\n", 2 + i, i + 1);
                }
                fprintf(pa, "clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\n");
                fprintf(pa, "setblock ~1 ~ ~ minecraft:command_block{Command:\"clone ~ ~1 ~ ~ ~1 ~ ~1 ~1 ~ replace move\"} replace\n");
                fprintf(pa, "setblock ~%d ~ ~ minecraft:command_block{Command:\"fill ~ ~ ~ ~-%d ~2 ~ minecraft:air replace\"} replace\n", 2 + b_count, 1 + b_count);
                fclose(pa);
                printf("\nfunction particles:%smain%d\n", names, i1);
            }
        }
    }

    return 0;
}
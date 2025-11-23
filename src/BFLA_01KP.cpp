#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cfloat>
#include <string.h>

#define rdint(i) (rand()%i)  // Generate a random integer from 0 to i-1
#define rdft() ((double)rdint(16384)/(16383.0))  // Generate a uniform random value in [0,1]

#define DIMENSION 1000  // Problem dimension
#define POPSIZE 20
#define MAXITERA 200  // Maximum iterations
#define RUNS 10  // Number of runs
#define lb (-5)
#define ub 5

#define D 0.01
#define C1 1
#define C2 2
#define C3 0.1
#define C4 0.2
#define C5 2

#define A 5.0
#define PI 3.14159265358979323846
#define Pm 0.003

struct indi
{
    double dv[DIMENSION];     //Decision variable
    int bdv[DIMENSION];       //store binary Decision variable
    int fs;                   //fitness score
} individual[POPSIZE], offspring[POPSIZE], ei1, ei2, GBest;

char filename1[] = "../instances/Instance_01KP_36/ikp132.txt";
char filename2[] = "../results/statistics/BMS.txt";
char filename3[] = "../results/convergence/cvg_np30_ikp132.txt";
FILE *fp1 = NULL;
FILE *fp2 = NULL;
FILE *fp3 = NULL;
int capmax, useless;
int weight[DIMENSION];
int price[DIMENSION];
double Mean, Std, Usetime, Rate, Worst;
int best[RUNS+1];
int indexVD[DIMENSION];
int HundResult[RUNS][MAXITERA];  // Results of MAXITERA iterations for RUNS runs

double dv_m[DIMENSION];
double dv1_m[DIMENSION];
double dv2_m[DIMENSION];
double J[DIMENSION];  // Diffusion flux
double DRF[DIMENSION];
double MS;
double Qeo[DIMENSION];

// Precomputed constants
double OneByMIT = 1.0 / MAXITERA;
double OneByPOP = 1.0 / POPSIZE;
double TwoByPOP = OneByPOP * 2;
int PopByTwo = POPSIZE / 2;
double OneByRUNS = 1.0 / RUNS;

// Function declarations
void create_directory(const char* path);
void load_file();
void select_sort(double *arr, int * index);
void initialize();
int decimal_to_binary(double decimal);
double lf_1(double x, double a);
void cal_price(int num);
int cal_weight(int num);
void get_mean();
double euclidean_distance(double *arrX, double *arrY);
void FGRA(int num);
void GOA(int num);
void DO(double tf);
void EO(double tf);
void SSO(double tf);
void data_summary();
void store_file();
void obra(int num);

// Transfer function declarations
double s_shaped_1(double x);
double s_shaped_2(double x);
double s_shaped_3(double x);
double s_shaped_4(double x);
double u_shaped_1(double x);
double u_shaped_2(double x);
double u_shaped_3(double x);
double u_shaped_4(double x);
double v_shaped_1(double x);
double v_shaped_2(double x);
double v_shaped_3(double x);
double v_shaped_4(double x);
double t_shaped_1(double x);
double t_shaped_2(double x);
double t_shaped_3(double x);
double t_shaped_4(double x);

// Create directory if it doesn't exist
void create_directory(const char* path)
{
    char dir_path[512];
    int i;
    strncpy(dir_path, path, sizeof(dir_path) - 1);
    dir_path[sizeof(dir_path) - 1] = '\0';
    
    // Extract directory path from file path
    for (i = (int)strlen(dir_path) - 1; i >= 0; i--) {
        if (dir_path[i] == '/' || dir_path[i] == '\\') {
            dir_path[i] = '\0';
            break;
        }
    }
    
    if (i > 0) {
        // Create directory using system command
        char cmd[1024];
#ifdef _WIN32
        sprintf(cmd, "if not exist \"%s\" mkdir \"%s\"", dir_path, dir_path);
#else
        sprintf(cmd, "mkdir -p \"%s\" 2>/dev/null", dir_path);
#endif
        system(cmd);
    }
}

int main()
{
    srand(time(NULL));
    
    // Create output directories if they don't exist
    create_directory(filename2);
    create_directory(filename3);
    
    load_file();
    double vd[DIMENSION];
    for (int i = 0; i < DIMENSION; i++)
    {
        indexVD[i] = i;
        vd[i] = price[i] / (double)(weight[i]);
    }
    select_sort(vd, indexVD);
    time_t first, second;
    first = clock();
    for (int u = 0; u < RUNS; u++)
    {
        initialize();  
        for (int t = 0; t < MAXITERA; t++)
        {
            get_mean();
            double tf = sinh(t * OneByMIT);
            if (tf < 0.9) DO(tf);
            else if (tf < 1) EO(tf);
            else SSO(tf);
            for (int i = 0; i < POPSIZE; i++)
            {
                obra(i);
                for (int j = 0; j < DIMENSION; j++)
                {
                    offspring[i].bdv[j] = decimal_to_binary(offspring[i].dv[j]);
                    if (rdft() < Pm) offspring[i].bdv[j] = 1 - offspring[i].bdv[j];
                }
                FGRA(i);
                GOA(i);
                cal_price(i);
                if (offspring[i].fs > individual[i].fs)
                {  
                    individual[i] = offspring[i];
                    if (i < PopByTwo && individual[i].fs > ei1.fs) ei1 = individual[i];
                    if (i >= PopByTwo && individual[i].fs > ei2.fs) ei2 = individual[i];
                }                
            }
            if (ei1.fs > ei2.fs) GBest = ei1; else GBest = ei2;
            HundResult[u][t] = GBest.fs;
        }
        best[u] = GBest.fs;
    }
    second = clock();
    Usetime = (double)(second - first) / (CLOCKS_PER_SEC * RUNS);
    data_summary();
    store_file();
    return 0;
}

int decimal_to_binary(double decimal)
{
    if(rdft() >= lf_1(decimal, 3))
        return 0;
    else 
        return 1;             
}

void load_file()
{
    if((fp1 = fopen(filename1, "r")) == NULL) printf("ERROR");
    fscanf(fp1,"%d",&useless);
    fscanf(fp1,"%d",&useless);
    fscanf(fp1,"%d", &capmax);
    for (int i = 0; i < DIMENSION; i++)
    {
        fscanf(fp1,"%d", price + i);
        fscanf(fp1,"%d", weight + i);
    }
    fclose(fp1);
}

void data_summary()
{
    best[RUNS] = best[0]; Worst = best[0];
    Mean = best[0]; Rate = 1;
    for(int i = 1; i < RUNS; i++)
    {
        if (best[i] > best[RUNS])
        {
            best[RUNS] = best[i];
            Rate = 1;
        }
        else if (best[i] == best[RUNS]) Rate += 1;
        Mean += best[i];
    }
    for (int i = 1; i < RUNS; i++)
        if (best[i] < Worst) Worst = best[i];
    Mean = Mean * OneByRUNS;
    Rate = Rate * OneByRUNS * 100;
    double sumSquaredDiff = 0.0;
    for (int i = 0; i < RUNS; ++i) {
        double diff = best[i] - Mean;
        sumSquaredDiff += diff * diff;
    }
    double variance = sumSquaredDiff * OneByRUNS;
    Std = sqrt(variance);
}

void store_file()
{
    if((fp2 = fopen(filename2, "a+")) == NULL)
    {
        printf("ERROR");
        exit(0);
    }
    fprintf(fp2, "Best:%d    ", best[RUNS]);
    fprintf(fp2, "Worst:%lf   ", Worst);
    fprintf(fp2, "Mean:%lf    ", Mean);
    fprintf(fp2, "Rate:%lf    ", Rate);
    fprintf(fp2, "Std:%lf    ", Std);
    fprintf(fp2, "Time:%lf\n", Usetime);
    fclose(fp2);
    if((fp3 = fopen(filename3, "w+")) == NULL)
    {
        printf("ERROR3");
        exit(0);
    }
    for (int i = 0; i < RUNS; i++){
        fprintf(fp3, "run%d ", i+1);
        for(int j = 0; j < MAXITERA; j++){
            fprintf(fp3, "%d ", HundResult[i][j]);
        }
        fprintf(fp3,"\n");
    }
    fclose(fp3);
}

void SSO(double tf)
{
    double tdo = C5 * tf - rdft();
    double dof = exp(-(C2*tf - rdft()) * C2);
    double OneByTF = 1.0 / tf;
    for (int i = 0; i < PopByTwo; i++)
    {
        MS = exp(-GBest.fs / (individual[i].fs + DBL_EPSILON));
        int dfg = (rdft() < rdft()) ? -1 : 1;
        double distance = D / euclidean_distance(GBest.dv, individual[i].dv);
        for (int j = 0; j < DIMENSION; j++)
        {
            J[j] = (dv1_m[j] - dv_m[j]) * distance;
            DRF[j] = exp(-J[j] * OneByTF);
            Qeo[j] = dfg * DRF[j] * rdft();
            offspring[i].dv[j] = GBest.dv[j] + Qeo[j] * individual[i].dv[j] + Qeo[j] * (MS * GBest.dv[j] - individual[i].dv[j]);
        }         
    }
    for (int i = PopByTwo; i < POPSIZE; i++)
    {
        MS = exp(-GBest.fs / (individual[i].fs + DBL_EPSILON));
        int dfg = (rdft() < rdft()) ? -1 : 1;
        double distance = D / euclidean_distance(GBest.dv, individual[i].dv);
        for (int j = 0; j < DIMENSION; j++)
        {
            J[j] = (dv2_m[j] - dv_m[j]) * distance;
            DRF[j] = exp(-J[j] * OneByTF);
            Qeo[j] = dfg * DRF[j] * rdft();
            offspring[i].dv[j] = GBest.dv[j] + Qeo[j] * individual[i].dv[j] + Qeo[j] * (MS * GBest.dv[j] - individual[i].dv[j]);
        }         
    }
}

void EO(double tf)
{
    double tdo = C5 * tf - rdft();
    double dof = exp(-(C2*tf - rdft()) * C2);
    double OneByTF = 1.0 / tf;
    
    for (int i = 0; i < PopByTwo; i++)
    {
        MS = exp(-ei1.fs / (individual[i].fs + DBL_EPSILON));
        int dfg = (rdft() < rdft()) ? -1 : 1;
        double distance = D / euclidean_distance(ei1.dv, individual[i].dv);
        for (int j = 0; j < DIMENSION; j++)
        {
            J[j] = (dv1_m[j] - ei1.dv[j]) * distance;
            DRF[j] = exp(-J[j] * OneByTF);
            Qeo[j] = dfg * DRF[j] * rdft();
            offspring[i].dv[j] = ei1.dv[j] + Qeo[j] * individual[i].dv[j] + Qeo[j] * (MS * ei1.dv[j] - individual[i].dv[j]);
        }         
    }
    for (int i = PopByTwo; i < POPSIZE; i++)
    {
        MS = exp(-ei2.fs / (individual[i].fs + DBL_EPSILON));
        int dfg = (rdft() < rdft()) ? -1 : 1;
        double distance = D / euclidean_distance(ei2.dv, individual[i].dv);
        for (int j = 0; j < DIMENSION; j++)
        {
            J[j] = (dv2_m[j] - ei2.dv[j]) * distance;
            DRF[j] = exp(-J[j] * OneByTF);
            Qeo[j] = dfg * DRF[j] * rdft();
            offspring[i].dv[j] = ei2.dv[j] + Qeo[j] * individual[i].dv[j] + Qeo[j] * (MS * ei2.dv[j] - individual[i].dv[j]);
        }         
    } 
}

void DO(double tf)
{
    double dof = exp(-(C2*tf - rdft()) * C2);
    double tdo = C5 * tf - rdft();
    int transferN = round(PopByTwo * rdft() * (C4 - C3) + PopByTwo * C3);
    if (tdo < rdft())
    {               
        for (int i = 0; i < transferN; i++)
        {
            int dfg = (rdft() < rdft()) ? -1 : 1;
            double distance = D / euclidean_distance(ei2.dv, individual[i].dv);
            for (int j = 0; j < DIMENSION; j++)
            {
                J[j] = (dv1_m[j] - dv2_m[j]) * distance;
                offspring[i].dv[j] = ei2.dv[j] + dfg * dof * rdft() * (J[j] * ei2.dv[j] - individual[i].dv[j]);
            }         
        }
        for (int i = transferN; i < PopByTwo; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                double p = rdft(); 
                double r3 = rdft();
                if (p < 0.8) offspring[i].dv[j] = ei1.dv[j];
                else if (p < 0.9) offspring[i].dv[j] = individual[i].dv[j] + dof * (lb + (ub-lb)*r3);
                else offspring[i].dv[j] = individual[i].dv[j];
            }
        }
        for (int i = PopByTwo; i < POPSIZE; i++)
        {
            double r4 = rdft();
            for (int j = 0; j < DIMENSION; j++)
                offspring[i].dv[j] = ei2.dv[j] + dof * ((ub-lb)*r4 + lb);
        }
    }else{
        for (int i = PopByTwo; i < PopByTwo + transferN; i++)
        {
            int dfg = (rdft() < rdft()) ? -1 : 1;
            double distance = D / euclidean_distance(ei1.dv, individual[i].dv);
            for (int j = 0; j < DIMENSION; j++)
            {
                J[j] = (dv2_m[j] - dv1_m[j]) * distance;
                offspring[i].dv[j] = ei1.dv[j] + dfg * dof * rdft() * (J[j] * ei1.dv[j] - individual[i].dv[j]);
            }         
        }
        for (int i = PopByTwo + transferN; i < POPSIZE; i++)
        {
            for (int j = 0; j < DIMENSION; j++)
            {
                double p = rdft(); 
                double r3 = rdft();
                if (p < 0.8) offspring[i].dv[j] = ei2.dv[j];
                else if (p < 0.9) offspring[i].dv[j] = individual[i].dv[j] + dof * (lb+(ub-lb)*r3);
                else offspring[i].dv[j] = individual[i].dv[j];
            }
        }
        for (int i = 0; i < PopByTwo; i++)
        {
            double r4 = rdft();
            for (int j = 0; j < DIMENSION; j++)
                offspring[i].dv[j] = ei1.dv[j] + dof * ((ub-lb)*r4 + lb);
        }
    }
}

double euclidean_distance(double *arrX, double *arrY)
{
    double result = 0;
    for (int j = 0; j < DIMENSION; j++)
        result += (arrX[j] - arrY[j]) * (arrX[j] - arrY[j]);
    return sqrt(result) + DBL_EPSILON;
}

void get_mean()
{
    for (int j = 0; j < DIMENSION; j++)
    {
        dv1_m[j] = 0; dv2_m[j] = 0; dv_m[j] = 0;
        for (int i = 0; i < POPSIZE; i++)
        {
            if (i < PopByTwo) dv1_m[j] += individual[i].dv[j];
            else  dv2_m[j] += individual[i].dv[j];
        }
        dv_m[j] = (dv1_m[j] + dv2_m[j]) * OneByPOP;
        dv1_m[j] = dv1_m[j] * TwoByPOP;
        dv2_m[j] = dv2_m[j] * TwoByPOP;
    }
}

int cal_weight(int num)
{
    int result = 0;
    for (int i = 0; i < DIMENSION; i++)
    {
        result += offspring[num].bdv[i] * weight[i];
    }
    return result;
}

void cal_price(int num)
{
    offspring[num].fs = 0;
    for (int i = 0; i < DIMENSION; i++)
        offspring[num].fs += offspring[num].bdv[i] * price[i];
}

void FGRA(int num)
{
    int total_weight = cal_weight(num);
    if (total_weight > capmax)
    {
        for (int j = DIMENSION - 1; j >= 0; j--)
        {
            if (1 == offspring[num].bdv[indexVD[j]] && total_weight > capmax)
            {
                offspring[num].bdv[indexVD[j]] = 0;
                total_weight -= weight[indexVD[j]];
            }
            if (total_weight <= capmax) break;           
        }
    }
}

void GOA(int num)
{
    int total_weight = cal_weight(num);
    for (int j = 0; j < DIMENSION; j++)
    {
        if (total_weight + weight[indexVD[j]] <= capmax && 0 == offspring[num].bdv[indexVD[j]])
        {
            offspring[num].bdv[indexVD[j]] = 1;
            total_weight += weight[indexVD[j]];
        }
    }
}

void initialize()
{
    ei1.fs = 0;
    ei2.fs = 0;
    for(int i = 0; i < POPSIZE; i++)
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            offspring[i].dv[j] = lb + rdft() * (ub - lb);
            offspring[i].bdv[j] = decimal_to_binary(offspring[i].dv[j]);
            if (rdft() < Pm) offspring[i].bdv[j] = 1 - offspring[i].bdv[j];
        }
        FGRA(i);
        GOA(i);
        cal_price(i);
        if (i < PopByTwo && ei1.fs < offspring[i].fs) ei1 = offspring[i];
        if (i >= PopByTwo && ei2.fs < offspring[i].fs) ei2 = offspring[i];
    }
    if (ei1.fs > ei2.fs) GBest = ei1; else GBest = ei2;
    for(int i = 0; i < POPSIZE; i++)
        individual[i] = offspring[i];
}

void select_sort(double *arr, int * index)
{
    for (int i = 0; i < DIMENSION - 1; i++)
    {
        int k = i;
        for (int j = i+1; j < DIMENSION; j++)
            if (arr[k] < arr[j]) k = j;
        double temp_arr = arr[i];
        int temp_index = index[i];
        arr[i] = arr[k];
        index[i] = index[k];
        arr[k] = temp_arr;
        index[k] = temp_index;
    }
}

void obra(int num)
{
    int FU,FL;
    if (rdft() < rdft())
    {
        for (int j = 0; j < DIMENSION; j++)
        {
            FU = offspring[num].dv[j] > ub;
            FL = offspring[num].dv[j] < lb;
            if (0 != FU + FL) offspring[num].dv[j] = ub * FU + lb * FL;
        }
    }
    else{
        for (int j = 0; j < DIMENSION; j++)
        {
            FU = offspring[num].dv[j] > ub;
            FL = offspring[num].dv[j] < lb;
            if (0 != FU + FL) offspring[num].dv[j] = lb + (ub - lb) * rdft();              
        }
    } 
}

// Transfer functions
double s_shaped_1(double x)
{
    return (double)1 / (1 + exp(-2*x));
}

double s_shaped_2(double x)
{
    return (double)1 / (1 + exp(-x));
}

double s_shaped_3(double x)
{
    return (double)1 / (1 + exp(-x/2));
}

double s_shaped_4(double x)
{
    return (double)1 / (1 + exp(-x/3));
}

double v_shaped_1(double x)
{
    return (double)fabs(erf((sqrt(PI) / 2) * x));
}

double v_shaped_2(double x)
{
    return (double)fabs(tanh(x));
}

double v_shaped_3(double x)
{
    return (double)fabs(x / sqrt(1 + pow(x,2)));
}

double v_shaped_4(double x)
{
    return (double)fabs((2/PI) * atan((PI/2) * x));
}

double u_shaped_1(double x)
{
    return (double)pow(fabs(x), 1.5);
}

double u_shaped_2(double x)
{
    return (double)pow(fabs(x), 2);
}

double u_shaped_3(double x)
{
    return (double)pow(fabs(x), 3);
}

double u_shaped_4(double x)
{
    return (double)pow(fabs(x), 4);
}

double t_shaped_1(double x)
{
    return pow(fabs(x), 0.5) / pow(fabs(A), 0.5);
}

double t_shaped_2(double x)
{
    return (fabs(x) / fabs(A));
}

double t_shaped_3(double x)
{
    return pow(fabs(x), 0.33) / pow(fabs(A), 0.33);
}

double t_shaped_4(double x)
{
    return pow(fabs(x), 0.25) / pow(fabs(A), 0.25);
}

// Function for y = log_a((a - 1)/(2A)x + (a + 1)/2), a = 2,3,4,5
// Positive logarithm
double lf_1(double x, double a) {
    return log((a - 1) / (2 * A) * x + (a + 1) / 2) / log(a);
}

#include <stdio.h>
#include <math.h>

typedef struct{
    double x;
    double y;
} Vector;

typedef struct{
    Vector position;
    Vector acceleration;
    Vector velocity;
} PointObject;

struct unchanged_values {
    const double G;
    const double M_Earth;
};

typedef struct{
    double current;
    double delta;
    double simulation;
} SimulationTime;

void calculate_physics(PointObject *obj, struct unchanged_values consts, double delta);

int main(void)
{

    // расстояние — метры (m)
    // время — секунды (s)
    // скорость — метры/секунду (m/s)
    // ускорение — метры/секунду² (m/s²)
    // масса — килограммы (kg)
    // сила — ньютоны (N)

    // Const values
    struct unchanged_values constants = { 6.6743e-11, 5.972e24 };

    // Create an object
    PointObject object;

    // Ask (x, y) values from user
    printf("X-position (metres): ");
    scanf("%lf", &object.position.x);

    printf("Y-position (metres): ");
    scanf("%lf", &object.position.y);

    // Ask velocity values from user
    printf("X-velocity (m/s): ");
    scanf("%lf", &object.velocity.x);

    printf("Y-velocity (m/s): ");
    scanf("%lf", &object.velocity.y);

    // Creat a common time variable
    SimulationTime t;
    t.current = 0;

    // Ask time values from user
    printf("Delta time (seconds): ");
    scanf("%lf", &t.delta);

    printf("Simulation time (seconds): ");
    scanf("%lf", &t.simulation);

    FILE *file = fopen("orbit.csv", "w");
    if (file == NULL) {
        printf("Couldn't open a file!\n");
        return 1;
    }

    fprintf(file, "time,x,y\n");
    fprintf(file, "%lf,%lf,%lf\n", t.current, object.position.x, object.position.y);

    printf("Time, x, y\n");
    printf("%lf %.2f %.2f\n", t.current, object.position.x, object.position.y);

    // simulation_time
    while (t.current < t.simulation)
    {
        calculate_physics(&object, constants, t.delta);
        t.current += t.delta;

        fprintf(file, "%lf,%lf,%lf\n", t.current, object.position.x, object.position.y);
        printf("%lf, %.lf, %.lf\n", t.current, object.position.x, object.position.y);

    }
}

void calculate_physics(PointObject *obj, struct unchanged_values consts, double delta)
{

    double r;
    double a;

    // Сalculating the radius with help of hypotenuse formulas
    r = hypot(obj->position.x, obj->position.y);

    if (r > 0)
    {
        // Calculating a common acceleration
        a = consts.G * (consts.M_Earth / ( r * r ));
    }
    else
    {
        printf("Coordinates x and y can't be 0\n");
    }

    // Calculate which part of the gravitational acceleration is directed along x, and which is along y.
    obj->acceleration.x = a * (-obj->position.x / r);
    obj->acceleration.y = a * (-obj->position.y / r);

    // Изменяю скорость за еденицу времени в зависимости от того какое ускорение направлено на эту ось
    // Здесь мы пытаемся понять как изменится изначально заданная скорость с появлением ускорения 
    // направленного именно на эту ось x или y за единицу времени
    obj->velocity.x += obj->acceleration.x * delta;
    obj->velocity.y += obj->acceleration.y * delta;

    // Изменяю положение обьекта по осям взависимости от того как изменилась его скорость за еденицу времени
    obj->position.x += (obj->velocity.x * delta);
    obj->position.y += (obj->velocity.y * delta);
}

// gcc orbit.c -o orbit -lm && ./orbit

#include "solver.h"

#include <math.h>

#include <iostream>

void solver::test_solver(double x, DoubleCall f) {
    double x1 = x;
    double y = f(x);
    std::cout << y << std::endl;
}

/*
 if (algo == "rk4") {
    // 4th order Runge-Kutta
    k1 = velocity;
    other->compute_acceleration(position, k1v);

    k2 = k1 + dt / 2 * k1v;
    Pos_temp = dt / 2 * k1 + position;
    other->compute_acceleration(Pos_temp, k2v);

    k3 = k1 + dt / 2 * k2v;
    Pos_temp = dt / 2 * k2 + position;
    other->compute_acceleration(Pos_temp, k3v);

    k4 = k1 + dt * k3v;
    Pos_temp = dt / 2 * k3 + position;
    other->compute_acceleration(Pos_temp, k4v);

    k5 = k1 + dt * k4v;
    Pos_temp = dt / 2 * k4 + position;
    other->compute_acceleration(Pos_temp, k5v);

    vec3D xn, vn;
    xn = position + dt / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
    vn = velocity + dt / 6 * (k1v + 2 * k2v + 2 * k3v + k4v);
    position << xn;
    velocity << vn;
}

else if (algo == "rkf45a13") {
    // 4(5)th order Runge-Kutta-Fehlberg with alpha2=1/3
    k1 = velocity;
    other->compute_acceleration(position, k1v);

    k2 = k1 + dt * 2. / 9. * k1v;
    Pos_temp = dt * 2. / 9. * k1 + position;
    other->compute_acceleration(Pos_temp, k2v);

    k3 = k1 + dt / 12. * k2v + dt * 1. / 4. * k1v;
    Pos_temp = dt / 12. * k2 + dt * 1. / 4. * k1 + position;
    other->compute_acceleration(Pos_temp, k3v);

    k4 = k1 + dt * 69. / 128. * k3v - dt * 243. / 128. * k2v + dt * 135. / 64. * k1v;
    Pos_temp = dt * 69. / 128. * k3 - dt * 243. / 128. * k2 + dt * 135. / 64. * k1 + position;
    other->compute_acceleration(Pos_temp, k4v);

    k5 = k1 - dt * 17. / 12. * k4v + dt * 27. / 4. * k3v - dt * 27. / 5. * k2v + dt * 16. / 15. * k1v;
    Pos_temp = -dt * 17. / 12. * k4 + dt * 27. / 4. * k3 - dt * 27. / 5. * k2 + dt * 16. / 15. * k1 + position;
    other->compute_acceleration(Pos_temp, k5v);

    k6 = k1 + dt * 65. / 432. * k5v - dt * 5. / 16. * k4v + dt * 13. / 16. * k3v + dt * 4. / 27. * k2v + dt * 5. / 144. * k1v;
    Pos_temp = dt * 65. / 432. * k5 - dt * 5. / 16. * k4 + dt * 13. / 16. * k3 + dt * 4. / 27. * k2 + dt * 5. / 144. * k1v + position;
    other->compute_acceleration(Pos_temp, k6v);

    vec3D xn, vn;
    xn = position + dt * (47. / 450. * k1 + 0. * k2 + 12. / 25. * k3 + 32. / 255. * k4 + 1. / 30. * k5 + 6. / 25. * k6);
    vn = velocity + dt * (47. / 450. * k1v + 0. * k2v + 12. / 25. * k3v + 32. / 255. * k4v + 1. / 30. * k5v + 6. / 25. * k6v);
    position << xn;
    velocity << vn;
}

else if (algo == "rkf45a38") {
    // 4(5)th order Runge-Kutta-Fehlberg with alpha2=1/3
    k1 = velocity;
    other->compute_acceleration(position, k1v);

    k2 = k1 + dt * 1. / 4. * k1v;
    Pos_temp = dt * 1. / 4. * k1 + position;
    other->compute_acceleration(Pos_temp, k2v);

    k3 = k1 + dt * 3. / 32. * k2v + dt * 9. / 32. * k1v;
    Pos_temp = dt * 3. / 32. * k2 + dt * 9. / 32. * k1 + position;
    other->compute_acceleration(Pos_temp, k3v);

    k4 = k1 + dt * 1932. / 2197. * k3v - dt * 7200. / 2197. * k2v + dt * 7296. / 2197. * k1v;
    Pos_temp = dt * 1932. / 2197. * k3 - dt * 7200. / 2197. * k2 + dt * 7296. / 2197. * k1 + position;
    other->compute_acceleration(Pos_temp, k4v);

    k5 = k1 + dt * 439. / 216. * k4v - dt * 8. * k3v + dt * 3680. / 513. * k2v - dt * 845. / 4104. * k1v;
    Pos_temp = +dt * 439. / 216. * k4 - dt * 8. * k3 + dt * 3680. / 513. * k2 - dt * 845. / 4104. * k1 + position;
    other->compute_acceleration(Pos_temp, k5v);

    k6 = k1 - dt * 8. / 27. * k5v + dt * 2. * k4v - dt * 3544. / 2565. * k3v + dt * 1859. / 4104. * k2v - dt * 11. / 40. * k1v;
    Pos_temp = -dt * 8. / 27. * k5 + dt * 2. * k4 - dt * 3544. / 2565. * k3 + dt * 1859. / 4104. * k2 - dt * 11. / 40. * k1v + position;
    other->compute_acceleration(Pos_temp, k6v);

    vec3D xn, vn;
    xn = position + dt * (16. / 135. * k1 + 0. * k2 + 6656. / 12825. * k3 + 28561. / 56430. * k4 - 9. / 50. * k5 + 2. / 55. * k6);
    vn = velocity + dt * (16. / 135. * k1v + 0. * k2v + 6656. / 12825. * k3v + 28561. / 56430. * k4v - 9. / 50. * k5v + 2. / 55. * k6v);
    position << xn;
    velocity << vn;
}
*/
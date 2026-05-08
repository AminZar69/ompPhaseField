#ifndef COMMON_H
#define COMMON_H

constexpr int nx = 256;
constexpr int ny = 256;

extern const int    tf;
extern const int    step;

extern const double r;
extern const double rhoL;
extern const double rhoH;
extern const double drho3;
extern const double tauH;
extern const double tauL;
extern const double sigma;
extern const double w;
extern const double beta;
extern const double kappa;
extern const double m;
extern const double w_c;

extern const int    ex[9];
extern const int    ey[9];
extern const double wa[9];

extern int t;

extern int is_solid_node[(nx + 2)][(ny + 2)];


extern double h[(nx + 2)][(ny + 2)][9];
extern double g[(nx + 2)][(ny + 2)][9];


extern double phi[(nx + 2)][(ny + 2)];
extern double p[(nx + 2)][(ny + 2)];
extern double mu[(nx + 2)][(ny + 2)];
extern double dphidx[(nx + 2)][(ny + 2)];
extern double dphidy[(nx + 2)][(ny + 2)];
extern double rho[(nx + 2)][(ny + 2)];
extern double ux[(nx + 2)][(ny + 2)];
extern double uy[(nx + 2)][(ny + 2)];
extern double ni[(nx + 2)][(ny + 2)];
extern double nj[(nx + 2)][(ny + 2)];

#endif

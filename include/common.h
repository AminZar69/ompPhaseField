#ifndef Common_H
#define Common_H
const int nx=256;
const int ny=256;
//extern const int numThreads;
extern const int tf;
extern const int step;
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

extern const int ex[9];
extern const int ey[9];
extern const double wa[9];

extern int t;
extern int is_solid_node[nx+2][ny+2];
extern double h[9][(nx + 2)][(ny + 2)], g[9][(nx + 2)][(ny + 2)];
extern double phi[(nx + 2)][(ny + 2)], p[nx+1][ny+1], mu[nx+1][ny+1], dphidx[nx+1][ny+1], dphidy[nx+1][ny+1];
extern double rho[nx+1][ny+1], ux[nx+1][ny+1], uy[nx+1][ny+1], ni[nx+1][ny+1], nj[nx+1][ny+1]; 

#endif
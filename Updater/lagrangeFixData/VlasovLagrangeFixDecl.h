#ifndef VLASOV_LAGRANGE_FIX_H 
#define VLASOV_LAGRANGE_FIX_H 

#include <../../Lib/gkyl_ipow.h> 

extern "C" { 

double gkyl_ipow(double base, int exp);

void VlasovLagrangeFixSer1x1v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x1v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x1v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x2v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x2v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x2v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x3v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x3v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer1x3v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer2x2v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer2x2v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer2x2v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer2x3v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer2x3v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixSer3x3v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x1v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x1v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x1v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x2v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x2v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x2v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x3v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x3v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax1x3v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax2x2v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax2x2v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax2x2v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax2x3v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax2x3v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax2x3v3p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax3x3v1p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

void VlasovLagrangeFixMax3x3v2p(double *dm0, double *dm1, double *dm2, double *lo, double *L, double *Nv, double *vc, double *f);

} 
#endif

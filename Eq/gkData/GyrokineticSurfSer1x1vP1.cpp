#include <GyrokineticModDecl.h> 
double GyrokineticSurf1x1vSer_X_P1_Bvars_0(const double q_, const double m_, const double cflL, const double cflR, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[4]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = 0.3535533905932737*Gradpar[0]*wv; 

  double alpha[2]; 
  alpha[0] = Gradpar[0]*wv; 
#if upwindType == SURFAVG 
  if (alpha0>0) { 
  incr[0] = 0.3535533905932737*alpha[0]*(1.732050807568877*fl[1]+fl[0])*dfac_x; 
  incr[1] = -0.3535533905932737*alpha[0]*(3.0*fl[1]+1.732050807568877*fl[0])*dfac_x; 
  incr[2] = 0.3535533905932737*alpha[0]*(1.732050807568877*fl[3]+fl[2])*dfac_x; 
  incr[3] = -0.3535533905932737*alpha[0]*(3.0*fl[3]+1.732050807568877*fl[2])*dfac_x; 
  } else { 
  incr[0] = -0.3535533905932737*alpha[0]*(1.732050807568877*fr[1]-1.0*fr[0])*dfac_x; 
  incr[1] = 0.3535533905932737*alpha[0]*(3.0*fr[1]-1.732050807568877*fr[0])*dfac_x; 
  incr[2] = -0.3535533905932737*alpha[0]*(1.732050807568877*fr[3]-1.0*fr[2])*dfac_x; 
  incr[3] = 0.3535533905932737*alpha[0]*(3.0*fr[3]-1.732050807568877*fr[2])*dfac_x; 
  }
#elif upwindType == QUAD 
double fupwind[2];
double fupwindQuad[2];
double alphaQuad;
  alphaQuad = 0.7071067811865475*alpha[0]; 
  fupwindQuad[0] = 0.5*(((-0.8660254037844386*(fr[3]+fl[3]))+0.5*fr[2]-0.5*fl[2]+0.8660254037844386*(fr[1]+fl[1])-0.5*fr[0]+0.5*fl[0])*sgn(alphaQuad)+0.8660254037844386*fr[3]-0.8660254037844386*fl[3]-0.5*(fr[2]+fl[2])-0.8660254037844386*fr[1]+0.8660254037844386*fl[1]+0.5*(fr[0]+fl[0])); 
  alphaQuad = 0.7071067811865475*alpha[0]; 
  fupwindQuad[1] = 0.5*((0.8660254037844386*(fr[3]+fl[3])-0.5*fr[2]+0.5*fl[2]+0.8660254037844386*(fr[1]+fl[1])-0.5*fr[0]+0.5*fl[0])*sgn(alphaQuad)-0.8660254037844386*fr[3]+0.8660254037844386*fl[3]+0.5*(fr[2]+fl[2])-0.8660254037844386*fr[1]+0.8660254037844386*fl[1]+0.5*(fr[0]+fl[0])); 
  fupwind[0] = 0.7071067811865475*(fupwindQuad[1]+fupwindQuad[0]); 
  fupwind[1] = 0.7071067811865475*(fupwindQuad[1]-1.0*fupwindQuad[0]); 
  incr[0] = 0.5*alpha[0]*fupwind[0]*dfac_x; 
  incr[1] = -0.8660254037844386*alpha[0]*fupwind[0]*dfac_x; 
  incr[2] = 0.5*alpha[0]*fupwind[1]*dfac_x; 
  incr[3] = -0.8660254037844386*alpha[0]*fupwind[1]*dfac_x; 

#endif 
  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += incr[1]; 
  outl[2] += -1.0*incr[2]; 
  outl[3] += incr[3]; 
  return std::abs(alpha0); 
} 
double GyrokineticSurf1x1vSer_Vpar_P1_Bvars_0(const double q_, const double m_, const double cflL, const double cflR, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[4]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = -(0.4330127018922193*Gradpar[0]*Phi[1]*dfac_x*q_)/m_; 

  double alpha[2]; 
  alpha[0] = -(1.224744871391589*Gradpar[0]*Phi[1]*dfac_x*q_)/m_; 
#if upwindType == SURFAVG 
  if (alpha0>0) { 
  incr[0] = 0.3535533905932737*alpha[0]*(1.732050807568877*fl[2]+fl[0])*dfac_v; 
  incr[1] = 0.3535533905932737*alpha[0]*(1.732050807568877*fl[3]+fl[1])*dfac_v; 
  incr[2] = -0.3535533905932737*alpha[0]*(3.0*fl[2]+1.732050807568877*fl[0])*dfac_v; 
  incr[3] = -0.3535533905932737*alpha[0]*(3.0*fl[3]+1.732050807568877*fl[1])*dfac_v; 
  } else { 
  incr[0] = -0.3535533905932737*alpha[0]*(1.732050807568877*fr[2]-1.0*fr[0])*dfac_v; 
  incr[1] = -0.3535533905932737*alpha[0]*(1.732050807568877*fr[3]-1.0*fr[1])*dfac_v; 
  incr[2] = 0.3535533905932737*alpha[0]*(3.0*fr[2]-1.732050807568877*fr[0])*dfac_v; 
  incr[3] = 0.3535533905932737*alpha[0]*(3.0*fr[3]-1.732050807568877*fr[1])*dfac_v; 
  }
#elif upwindType == QUAD 
double fupwind[2];
double fupwindQuad[2];
double alphaQuad;
  alphaQuad = 0.7071067811865475*alpha[0]; 
  fupwindQuad[0] = 0.5*(((-0.8660254037844386*(fr[3]+fl[3]))+0.8660254037844386*(fr[2]+fl[2])+0.5*fr[1]-0.5*(fl[1]+fr[0])+0.5*fl[0])*sgn(alphaQuad)+0.8660254037844386*fr[3]-0.8660254037844386*(fl[3]+fr[2])+0.8660254037844386*fl[2]-0.5*(fr[1]+fl[1])+0.5*(fr[0]+fl[0])); 
  alphaQuad = 0.7071067811865475*alpha[0]; 
  fupwindQuad[1] = 0.5*((0.8660254037844386*(fr[3]+fl[3]+fr[2]+fl[2])-0.5*(fr[1]+fr[0])+0.5*(fl[1]+fl[0]))*sgn(alphaQuad)-0.8660254037844386*(fr[3]+fr[2])+0.8660254037844386*(fl[3]+fl[2])+0.5*(fr[1]+fl[1]+fr[0]+fl[0])); 
  fupwind[0] = 0.7071067811865475*(fupwindQuad[1]+fupwindQuad[0]); 
  fupwind[1] = 0.7071067811865475*(fupwindQuad[1]-1.0*fupwindQuad[0]); 
  incr[0] = 0.5*alpha[0]*fupwind[0]*dfac_v; 
  incr[1] = 0.5*alpha[0]*fupwind[1]*dfac_v; 
  incr[2] = -0.8660254037844386*alpha[0]*fupwind[0]*dfac_v; 
  incr[3] = -0.8660254037844386*alpha[0]*fupwind[1]*dfac_v; 

#endif 
  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += -1.0*incr[1]; 
  outl[2] += incr[2]; 
  outl[3] += incr[3]; 
  return std::abs(alpha0); 
} 
double GyrokineticSurf1x1vSer_X_P1_Bvars_1(const double q_, const double m_, const double cflL, const double cflR, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[4]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = -0.3535533905932737*(1.732050807568877*Gradpar[1]-1.0*Gradpar[0])*wv; 

  double alpha[2]; 
  alpha[0] = (Gradpar[0]-1.732050807568877*Gradpar[1])*wv; 
#if upwindType == SURFAVG 
  if (alpha0>0) { 
  incr[0] = 0.3535533905932737*alpha[0]*(1.732050807568877*fl[1]+fl[0])*dfac_x; 
  incr[1] = -0.3535533905932737*alpha[0]*(3.0*fl[1]+1.732050807568877*fl[0])*dfac_x; 
  incr[2] = 0.3535533905932737*alpha[0]*(1.732050807568877*fl[3]+fl[2])*dfac_x; 
  incr[3] = -0.3535533905932737*alpha[0]*(3.0*fl[3]+1.732050807568877*fl[2])*dfac_x; 
  } else { 
  incr[0] = -0.3535533905932737*alpha[0]*(1.732050807568877*fr[1]-1.0*fr[0])*dfac_x; 
  incr[1] = 0.3535533905932737*alpha[0]*(3.0*fr[1]-1.732050807568877*fr[0])*dfac_x; 
  incr[2] = -0.3535533905932737*alpha[0]*(1.732050807568877*fr[3]-1.0*fr[2])*dfac_x; 
  incr[3] = 0.3535533905932737*alpha[0]*(3.0*fr[3]-1.732050807568877*fr[2])*dfac_x; 
  }
#elif upwindType == QUAD 
double fupwind[2];
double fupwindQuad[2];
double alphaQuad;
  alphaQuad = 0.7071067811865475*alpha[0]; 
  fupwindQuad[0] = 0.5*(((-0.8660254037844386*(fr[3]+fl[3]))+0.5*fr[2]-0.5*fl[2]+0.8660254037844386*(fr[1]+fl[1])-0.5*fr[0]+0.5*fl[0])*sgn(alphaQuad)+0.8660254037844386*fr[3]-0.8660254037844386*fl[3]-0.5*(fr[2]+fl[2])-0.8660254037844386*fr[1]+0.8660254037844386*fl[1]+0.5*(fr[0]+fl[0])); 
  alphaQuad = 0.7071067811865475*alpha[0]; 
  fupwindQuad[1] = 0.5*((0.8660254037844386*(fr[3]+fl[3])-0.5*fr[2]+0.5*fl[2]+0.8660254037844386*(fr[1]+fl[1])-0.5*fr[0]+0.5*fl[0])*sgn(alphaQuad)-0.8660254037844386*fr[3]+0.8660254037844386*fl[3]+0.5*(fr[2]+fl[2])-0.8660254037844386*fr[1]+0.8660254037844386*fl[1]+0.5*(fr[0]+fl[0])); 
  fupwind[0] = 0.7071067811865475*(fupwindQuad[1]+fupwindQuad[0]); 
  fupwind[1] = 0.7071067811865475*(fupwindQuad[1]-1.0*fupwindQuad[0]); 
  incr[0] = 0.5*alpha[0]*fupwind[0]*dfac_x; 
  incr[1] = -0.8660254037844386*alpha[0]*fupwind[0]*dfac_x; 
  incr[2] = 0.5*alpha[0]*fupwind[1]*dfac_x; 
  incr[3] = -0.8660254037844386*alpha[0]*fupwind[1]*dfac_x; 

#endif 
  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += incr[1]; 
  outl[2] += -1.0*incr[2]; 
  outl[3] += incr[3]; 
  return std::abs(alpha0); 
} 
double GyrokineticSurf1x1vSer_Vpar_P1_Bvars_1(const double q_, const double m_, const double cflL, const double cflR, const double *w, const double *dxv, const double amax_in, const double *Bmag, const double *BmagInv, const double *Gradpar, const double *BdriftX, const double *BdriftY, const double *Phi, const double *fl, const double *fr, double *outl, double *outr) 
{ 
// w[NDIM]: Cell-center coordinates. dxv[NDIM]: Cell spacing. H/f: Input Hamiltonian/distribution function. out: Incremented output 
  double dfac_x = 2.0/dxv[0]; 
  double dfac_v = 2.0/dxv[1]; 
  double wx = w[0]; 
  double wv = w[1]; 
  double wv2 = wv*wv; 
  double dfac_v2 = dfac_v*dfac_v; 
  double q2 = q_*q_; 
  double incr[4]; 
  // surface-averaged phase velocity in this direction 
  double alpha0 = -(0.4330127018922193*Gradpar[0]*Phi[1]*dfac_x*q_)/m_; 

  double alpha[2]; 
  alpha[0] = -(1.224744871391589*Gradpar[0]*Phi[1]*dfac_x*q_)/m_; 
  alpha[1] = -(1.224744871391589*Gradpar[1]*Phi[1]*dfac_x*q_)/m_; 
#if upwindType == SURFAVG 
  if (alpha0>0) { 
  incr[0] = 0.3535533905932737*(1.732050807568877*(alpha[1]*fl[3]+alpha[0]*fl[2])+alpha[1]*fl[1]+alpha[0]*fl[0])*dfac_v; 
  incr[1] = 0.3535533905932737*(1.732050807568877*(alpha[0]*fl[3]+alpha[1]*fl[2])+alpha[0]*fl[1]+fl[0]*alpha[1])*dfac_v; 
  incr[2] = -0.3535533905932737*(3.0*(alpha[1]*fl[3]+alpha[0]*fl[2])+1.732050807568877*(alpha[1]*fl[1]+alpha[0]*fl[0]))*dfac_v; 
  incr[3] = -0.3535533905932737*(3.0*(alpha[0]*fl[3]+alpha[1]*fl[2])+1.732050807568877*(alpha[0]*fl[1]+fl[0]*alpha[1]))*dfac_v; 
  } else { 
  incr[0] = -0.3535533905932737*(1.732050807568877*(alpha[1]*fr[3]+alpha[0]*fr[2])-1.0*(alpha[1]*fr[1]+alpha[0]*fr[0]))*dfac_v; 
  incr[1] = -0.3535533905932737*(1.732050807568877*(alpha[0]*fr[3]+alpha[1]*fr[2])-1.0*(alpha[0]*fr[1]+fr[0]*alpha[1]))*dfac_v; 
  incr[2] = 0.3535533905932737*(3.0*(alpha[1]*fr[3]+alpha[0]*fr[2])-1.732050807568877*(alpha[1]*fr[1]+alpha[0]*fr[0]))*dfac_v; 
  incr[3] = 0.3535533905932737*(3.0*(alpha[0]*fr[3]+alpha[1]*fr[2])-1.732050807568877*(alpha[0]*fr[1]+fr[0]*alpha[1]))*dfac_v; 
  }
#elif upwindType == QUAD 
double fupwind[2];
double fupwindQuad[2];
double alphaQuad;
  alphaQuad = 0.7071067811865475*alpha[0]-0.7071067811865475*alpha[1]; 
  fupwindQuad[0] = 0.5*(((-0.8660254037844386*(fr[3]+fl[3]))+0.8660254037844386*(fr[2]+fl[2])+0.5*fr[1]-0.5*(fl[1]+fr[0])+0.5*fl[0])*sgn(alphaQuad)+0.8660254037844386*fr[3]-0.8660254037844386*(fl[3]+fr[2])+0.8660254037844386*fl[2]-0.5*(fr[1]+fl[1])+0.5*(fr[0]+fl[0])); 
  alphaQuad = 0.7071067811865475*(alpha[1]+alpha[0]); 
  fupwindQuad[1] = 0.5*((0.8660254037844386*(fr[3]+fl[3]+fr[2]+fl[2])-0.5*(fr[1]+fr[0])+0.5*(fl[1]+fl[0]))*sgn(alphaQuad)-0.8660254037844386*(fr[3]+fr[2])+0.8660254037844386*(fl[3]+fl[2])+0.5*(fr[1]+fl[1]+fr[0]+fl[0])); 
  fupwind[0] = 0.7071067811865475*(fupwindQuad[1]+fupwindQuad[0]); 
  fupwind[1] = 0.7071067811865475*(fupwindQuad[1]-1.0*fupwindQuad[0]); 
  incr[0] = 0.5*(alpha[1]*fupwind[1]+alpha[0]*fupwind[0])*dfac_v; 
  incr[1] = 0.5*(alpha[0]*fupwind[1]+fupwind[0]*alpha[1])*dfac_v; 
  incr[2] = -0.8660254037844386*(alpha[1]*fupwind[1]+alpha[0]*fupwind[0])*dfac_v; 
  incr[3] = -0.8660254037844386*(alpha[0]*fupwind[1]+fupwind[0]*alpha[1])*dfac_v; 

#endif 
  outr[0] += incr[0]; 
  outr[1] += incr[1]; 
  outr[2] += incr[2]; 
  outr[3] += incr[3]; 

  outl[0] += -1.0*incr[0]; 
  outl[1] += -1.0*incr[1]; 
  outl[2] += incr[2]; 
  outl[3] += incr[3]; 
  return std::abs(alpha0); 
} 
